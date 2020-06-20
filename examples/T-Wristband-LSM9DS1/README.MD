## **English | [中文](../../docs/lsm9ds1_cn.md)**

1. Install the corresponding driver according to the serial communication board you use
   - [CP21xx Drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
   - [CH340 Drivers](http://www.wch-ic.com/search?q=ch340&t=downloads)

2. Install the dependent libraries in the following list, the required library files have been placed in the `libdeps` by default, please copy all the files in the`libdeps` directory to `C:\<UserName>\Documents\Arduino\libraries` In the catalog
   - [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
   - [PCF8563_Library](https://github.com/lewisxhe/PCF8563_Library)
   - [WiFiManager for esp32](https://github.com/tzapu/WiFiManager)
   - [SparkFun_LSM9DS1_Arduino_Library](https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library)

3. Configure the TFT header file (**If you use the library file in the `libdeps` directory, you can skip this step**)
   - Find the **TFT_eSPI** directory in your library folder directory
   - Find `User_Setup_Select.h` in the root directory of **TFT_eSPI** and open it for editing
   - Comment out the file header `#include <User_Setup.h>`
   - Find `#includen <User_Setups/Setup26_TTGO_T_Wristband.h>`, cancel the previous comment, save and exit
   - The final effect is as follows:
        ![](../../image/1.jpg)

4. The board choose **ESP32 Dev Module**, other settings can be kept as default, note that `T-Wristband` does not use PSRAM, please do not turn on PSRAM, and call PSRAM function

5. The `ARDUINO_OTA_UPDATE` macro is used for **WiFiManager** and **OTA update**, the default is off, if you need to open, please open in `sketch`
   - When `ARDUINO_OTA_UPDATE` is turned on, touch and hold the button for three seconds to reset `WiFi`
   - After enabling OTA update, you can select `T-Wristband` in the Arduino IDE port for over-the-air upgrade, as shown below
        ![](../../image/2.jpg)

6. The `FACTORY_HW_TEST` macro is used to test whether the hardware status of the bracelet is normal, and it is closed by default. If you need to open it, please open it in ` sketch`
   
7. Touch the button to switch to the next function when a press is detected
   - Press for the first time to view the nine-axis sensor information
   - Press it a second time to enter deep sleep
   - During deep sleep, touch again to wake up the bracelet

8. The `ENABLE_BLE_DATA_TRANSMISSION` macro is used to test the BLE transmission IMU data example. It is closed by default. You can use APPs such as `nRF Connect` and `LightBlue` to connect to view data


9. The `ENABLE_SENSOR` macro is used to enable the LSM9DS1 sensor function. It is disabled by default

10. The `USE_PROTECTED_MEMBERS` macro is used to enable the LSM9DS1 sensor shutdown mode function. It is disabled by default. Before using, please make sure that you have changed the three member methods of `SparkFun_LSM9DS1_Arduino_Library` to the common member method, or directly use the library file in `libdeps`

## Datasheet
- [LSM9DS1 Sensor](https://www.st.com/resource/en/datasheet/lsm9ds1.pdf)
- [ST7735](http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf)
- [ESP32-PICO-D4](https://www.espressif.com/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf)


## Pin definition

| Name              | Pin    |
| ----------------- | ------ |
| TFT Driver        | ST7735 |
| TFT_MISO          | N/A    |
| TFT_MOSI          | 19     |
| TFT_SCLK          | 18     |
| TFT_CS            | 5      |
| TFT_DC            | 23     |
| TFT_RST           | 26     |
| TFT_BL            | 27     |
| Touchpad          | 33     |
| Touchpad Power    | 25     |
| RTC Interrupt     | 34     |
| Battery ADC       | 35     |
| I2C_SDA           | 21     |
| I2C_SCL           | 22     |
| CHARGE Indication | 32     |
| IMU INT1          | 38     |
| IMU INT2          | 39     |
| IMU INTM          | 37     |
| IMU RDY           | 36     |
