/**
 * @file Electronica2022Demo-esp-holtek.c
 * @brief BM32S2031
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright 2022 Ineltek Italy S.r.l.
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#include <dirent.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "bsp_board.h"
#include "bsp_lcd.h"
#include "bsp_btn.h"
#include "bsp_lcd.h"
#include "bsp_storage.h"
#include "lv_port.h"
#include "lv_port_fs.h"
#include "lvgl.h"
#include "driver/gpio.h"

#define SENSOR_OUTPUT 38 // pin at which the sensor output is attached to

const lv_point_t points_array[] =  {{160, 120}};
static void image_display(void);

lv_obj_t * label1;
lv_obj_t * btn;

static int last_sensor_state;

static lv_style_t style_pr;
static lv_style_t style_def;


void  sensor_read(lv_indev_drv_t * drv, lv_indev_data_t*data){
    int btn_pr = gpio_get_level(SENSOR_OUTPUT); 

    if(btn_pr!=last_sensor_state){ // Enter only if the state is changed, otherwise it keeps calling the 
        if(btn_pr > 0) {               /*Is the button pressed? If so, add the state PRESSED to it, to see the change in appearance*/
            lv_label_set_text(label1, "FREE");
            lv_obj_clear_state(btn,  LV_STATE_PRESSED );
        } else {
            lv_label_set_text(label1, "DETECTED");
            lv_obj_add_state(btn,  LV_STATE_PRESSED );           
        }
        last_sensor_state=btn_pr;
    }

}


void app_main(void)
{
    ESP_ERROR_CHECK(bsp_board_init());
    ESP_ERROR_CHECK(bsp_spiffs_init_default());

    ESP_ERROR_CHECK(lv_port_init());
    ESP_ERROR_CHECK(lv_port_fs_init());
    bsp_lcd_set_backlight(true);
    
    //*** SENSOR as indev 

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);      /*Basic initialization*/
    indev_drv.type = LV_INDEV_TYPE_BUTTON;  /* Sensor as simple on/off button */
    indev_drv.read_cb =sensor_read;        
    /*Register the driver in LVGL and save the created input device object*/
    lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);
    lv_indev_set_button_points(my_indev, points_array);


    //*** STYLE and TRANSITION effects
    
    static const lv_style_prop_t props[] = {LV_STYLE_BG_COLOR, LV_STYLE_BORDER_COLOR, LV_STYLE_BORDER_WIDTH, 0};
    /* A default transition
     * Make it fast (100ms) and start with no delay */
    static lv_style_transition_dsc_t trans_def;
    lv_style_transition_dsc_init(&trans_def, props, lv_anim_path_linear, 100, 0, NULL);
    
    /* A special transition when going to pressed state
     * Make it slow (500 ms) but start  without delay*/
    static lv_style_transition_dsc_t trans_pr;
    lv_style_transition_dsc_init(&trans_pr, props, lv_anim_path_linear, 500, 0, NULL);


    lv_style_init(&style_def);
    lv_style_set_transition(&style_def, &trans_def);
    lv_style_set_bg_color(&style_def, lv_color_hex(0x458b00));
    lv_style_set_border_width(&style_def, 2);
    lv_style_set_border_color(&style_def, lv_color_black());
    lv_style_set_radius(&style_def, 200);
    lv_style_set_text_font(&style_def, &lv_font_montserrat_28); // You need to enable the the font in the menuconfig first!


    lv_style_init(&style_pr);
    lv_style_set_bg_color(&style_pr, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_border_width(&style_pr, 6);
    lv_style_set_border_color(&style_pr, lv_palette_darken(LV_PALETTE_RED, 3));
    lv_style_set_transition(&style_pr, &trans_pr);


    last_sensor_state = 0;


    image_display();

    do {
        lv_task_handler();
    } while (vTaskDelay(1), true);
}



static void image_display(void)
{
    btn = lv_btn_create(lv_scr_act());
    lv_obj_set_size(btn, lv_pct(60), lv_pct(80));
    lv_obj_set_style_border_width(btn, 0, LV_STATE_DEFAULT);
    lv_obj_align(btn, LV_ALIGN_CENTER, 0, 0);

    lv_obj_add_style(btn, &style_def, 0);
    lv_obj_add_style(btn, &style_pr, LV_STATE_PRESSED);
    label1 = lv_label_create(btn);
    lv_obj_set_align(label1, LV_ALIGN_CENTER); 
    lv_label_set_text(label1, "Initializing");
 
}

