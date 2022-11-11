# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/Francesco/esp/esp-idf/components/bootloader/subproject"
  "C:/Users/Francesco/Desktop/EDE_ESP32S3Demo/Electronica2022Demo-esp-holtek/build/bootloader"
  "C:/Users/Francesco/Desktop/EDE_ESP32S3Demo/Electronica2022Demo-esp-holtek/build/bootloader-prefix"
  "C:/Users/Francesco/Desktop/EDE_ESP32S3Demo/Electronica2022Demo-esp-holtek/build/bootloader-prefix/tmp"
  "C:/Users/Francesco/Desktop/EDE_ESP32S3Demo/Electronica2022Demo-esp-holtek/build/bootloader-prefix/src/bootloader-stamp"
  "C:/Users/Francesco/Desktop/EDE_ESP32S3Demo/Electronica2022Demo-esp-holtek/build/bootloader-prefix/src"
  "C:/Users/Francesco/Desktop/EDE_ESP32S3Demo/Electronica2022Demo-esp-holtek/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/Francesco/Desktop/EDE_ESP32S3Demo/Electronica2022Demo-esp-holtek/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
