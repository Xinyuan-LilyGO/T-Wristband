# T-Wristband

## 1.Install the following dependency library files:
- [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)

## 2.TFT_eSPI settings
- Install TFT_eSPI, in `TFT_eSPI/User_Setup_Select.h`, comment out the default settings `#include <User_Setup.h>` , select `#include <User_Setups/Setup26_TTGO_T_Wristband.h.h>` , Save Settings.

  * If `Setup26_TTGO_T_Wristband.h.h` is not found, manually move `User_Setups\ Setup26_TTGO_T_Wristband.h` to `C:\Users\UserName\Documents\Arduino\libraries\ TFT_eSPI\User_Setups`

## 3.Board choose
- The board can choose `ESP32 Dev Module`, other settings can keep the default

| Name          | Pin    |
| ------------- | ------ |
| TFT Driver    | ST7735 |
| TFT_MISO      | N/A    |
| TFT_MOSI      | 19     |
| TFT_SCLK      | 18     |
| TFT_CS        | 5      |
| TFT_DC        | 23     |
| TFT_RST       | 26     |
| TFT_BL        | 27     |
| Touchpad      | 33     |
| IMU Interrupt | 4      |
| RTC Interrupt | 34     |
| Battery ADC   | 35     |
| VBUS ADC      | 36     |
| I2C_SDA       | 21     |
| I2C_SCL       | 22     |

