# Demo Espressif/Holtek Electronica 2022 
This repo containes the files used for the Electronica 2022 trade fair demo.
The demo is based on an Esp-box which mounts an ESP32-S3-WROOM SoC. The ESP-Box back connector is used to link the three pins as showed in the table below. 

|ESP-BOX | BM32S2031 | Description|
|---|---|---|
| VDD | VDD | 3.3V Supply |
| GND | GND | Ground |
| GPIO 38 | D or I/O out | Sensor output pin |

![Block_diagram](./images/blocks.png)

The code is forked from the example [image_display](https://github.com/espressif/esp-box/tree/master/examples/image_display) in the Esp-Box example folder. 

## Get started

You will need:
* Esp-box
* BM32S2031 module
* A few cables


For a general getting started tutorial you can check here [Get started with Esp-box](https://fbez.github.io/documentation/ESP-Box-getting-started.html). The important thing to notice is that generally you need to copy the components directory in your project or download the dependencies through the component registry, but for sake of easiness, these folders have already been included in this repo. Before moving on, go through the tutorial, compile and flash the `image_display` example. 

Solder one end of the cables to the module and connect them as shown in the table above. 

Clone the repo in your system
```git clone --recursive https://github.com/Ineltek-IT/Electronica2022Demo-esp-holtek.git```
Move to the `Electronica2022Demo-esp-holtek` directory and open the workspace in vscode. At this point you should be able to call `ESP-IDF: Build, Flash and start monitor on your device`.

At this point you should see the button staying green ("Free") if no object is directly in front of it, while turning red ("Detected") if there something facing it. The typical detection distance is 80cm. 


![free_detected](./images/freeDetected.png)




## References
* [Get started with Esp-box](https://fbez.github.io/documentation/ESP-Box-getting-started.html)
* [BM32S2031 Datasheet](https://www.holtek.com/documents/10179/116711/BM32S2031-1v100.pdf)
* [Ineltek website](https://www.ineltek.com/it/)
* [Holtek website](https://www.holtek.com/)
* [Espressif website](https://www.espressif.com/)