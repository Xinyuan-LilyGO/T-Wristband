## **English | [中文](../../docs/drv2605_cn.md.md)**

1. Install the corresponding driver according to the serial communication board you use
   - [CP21xx Drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
   - [CH340 Drivers](http://www.wch-ic.com/search?q=ch340&t=downloads)

2. Install the dependent libraries in the following list, the required library files have been placed in the `libdeps` by default, please copy all the files in the`libdeps` directory to `C:\<UserName>\Documents\Arduino\libraries` In the catalog
   - [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
   - [Adafruit_DRV2605_Library](https://github.com/adafruit/Adafruit_DRV2605_Library)

3. Configure the TFT header file (**If you use the library file in the `libdeps` directory, you can skip this step**)
   - Find the **TFT_eSPI** directory in your library folder directory
   - Find `User_Setup_Select.h` in the root directory of **TFT_eSPI** and open it for editing
   - Comment out the file header `#include <User_Setup.h>`
   - Find `#includen <User_Setups/Setup26_TTGO_T_Wristband.h>`, cancel the previous comment, save and exit
   - The final effect is as follows:
        ![](../../image/1.jpg)

4. The board choose **ESP32 Dev Module**, other settings can be kept as default, note that `T-Wristband` does not use PSRAM, please do not turn on PSRAM, and call PSRAM function

5. For more heart rate examples, please refer to `Adafruit_DRV2605_Library`

## Datasheet
- [DRV2605](https://www.ti.com/product/DRV2605)
- [ST7735](http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf)
- [ESP32-PICO-D4](https://www.espressif.com/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf)

## Pin definition

| Name    | Pin |
| ------- | --- |
| DRV_SDA | 15  |
| DRV_SCL | 13  |
