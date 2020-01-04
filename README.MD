# T-Wristband

## 1.Install the following dependency library files:
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
- [PCF8563_Library](https://github.com/lewisxhe/PCF8563_Library)

## 2.TFT_eSPI settings
- Install TFT_eSPI, in `TFT_eSPI/User_Setup_Select.h`, comment out the default settings `#include <User_Setup.h>` , select `#include <User_Setups/Setup26_TTGO_T_Wristband.h.h>` , Save Settings.

  * If `Setup26_TTGO_T_Wristband.h.h` is not found, manually move `User_Setups\ Setup26_TTGO_T_Wristband.h` to `C:\Users\UserName\Documents\Arduino\libraries\ TFT_eSPI\User_Setups`

- Configure TFT_eSPI as shown below
![](image/1.jpg)

### 3. Precautions
- **WiFiManager** is used for WiFi settings by default. Please connect to `T-Wristband` hotspot for network configuration for the first time.
- The OTA update and upgrade is enabled by default. After the WiFi configuration is complete, you can select `T-Wristband` from the port in the Arduino IDE to perform wireless upgrades to get rid of the constraints of downloading the data cable. ***Please update your own code. Please keep the ota upgrade part, otherwise the upgrade may cause failure Air upgrade again***
![](image/2.jpg)

- Touch and hold the button for three seconds to reset the WiFi and restart. After resetting, you need to configure again.
- Note that `WiFiManager` uses the development branch. Please make sure that the [development branch](https://github.com/tzapu/WiFiManager/tree/development) is cloned, otherwise it will not compile successfully. There is a WiFiManager library used in the libdeps directory. **If you cannot compile, please copy the files in the libdeps directory to `C:\Documents\Arduino\libraries`**

## 4.Board choose
- The board can choose `ESP32 Dev Module`, other settings can keep the default

## 5.Pinout

| Name           | Pin    |
| -------------- | ------ |
| TFT Driver     | ST7735 |
| TFT_MISO       | N/A    |
| TFT_MOSI       | 19     |
| TFT_SCLK       | 18     |
| TFT_CS         | 5      |
| TFT_DC         | 23     |
| TFT_RST        | 26     |
| TFT_BL         | 27     |
| Touchpad       | 33     |
| Touchpad Power | 25     |
| IMU Interrupt  | 38     |
| RTC Interrupt  | 34     |
| Battery ADC    | 35     |
| VBUS ADC       | 36     |
| I2C_SDA        | 21     |
| I2C_SCL        | 22     |
| LED            | 4      |