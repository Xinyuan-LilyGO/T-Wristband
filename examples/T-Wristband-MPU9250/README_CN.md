## **[English](README_CN.md) | 中文**

## 使用之前,请阅读下面的描述

1. 根据你使用的串口通讯板安装对应的驱动程序

    - [CP21xx Drivers](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers)
    - [CH340 Drivers](http://www.wch-ic.com/search?q=ch340&t=downloads)

2. 安装下面列表中的依赖库,默认已将所需要的库文件放置在`libdeps`目录中,请将`libdeps`目录内所有文件拷贝到`C:\<UserName>\Documents\Arduino\libraries`目录内

    - [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI)
    - [PCF8563_Library](https://github.com/lewisxhe/PCF8563_Library)

3. 配置TFT头文件(**如果使用`libdeps`目录中库文件,可以跳过这一步**)

    - 在你的库文件夹目录中找到**TFT_eSPI**目录
    - 在**TFT_eSPI**根目录中找到`User_Setup_Select.h`并且打开进行编辑
    - 将 文件头部`#include <User_Setup.h>` 注释掉
    - 找到 `#include <User_Setups/Setup26_TTGO_T_Wristband.h>`,取消前面的注释,保存退出
    - 最终效果如下图:
        ![](../../docs/_static/readme/1.jpg)

4. 板子可以选择**ESP32 Dev Module**，其他设置可以保持默认,注意 `T-Wristband` 没有使用PSRAM,请勿开启PSRAM,和调用PSRAM的功能函数

5. `ARDUINO_OTA_UPDATE` 宏用于**WiFiManager**和**OTA更新**,默认为关闭,如需开启请在`sketch`中开启

    - 当`ARDUINO_OTA_UPDATE`开启后,触摸按住按钮三秒钟进行`WiFi`重置
    - 开启OTA更新后,你可以在Arduino IDE端口中选择 `T-Wristband` 进行空中升级,如下图
        ![](../../docs/_static/readme/2.jpg)

6. `FACTORY_HW_TEST` 宏用于测试手环的硬件状态是否正常,默认关闭,如需开启请在`sketch`中开启
7. 触摸按钮当检测到按下则切换下一个功能
    - 按下第一次 将查看九轴传感器信息
    - 按下第二次 将进入深度睡眠
    - 在深度睡眠中,再次触碰 将唤醒手环

## 数据手册

- [MPU9250 Sensor](https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf)
- [ST7735](http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf)
- [ESP32-PICO-D4](https://www.espressif.com/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf)
- [DRV2605](https://www.ti.com/product/DRV2605)

## 引脚定义

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
| IMU Interrupt     | 38     |
| RTC Interrupt     | 34     |
| Battery ADC       | 35     |
| VBUS ADC          | 36     |
| I2C SDA           | 21     |
| I2C SCL           | 22     |
| LED and Vibration | 4      |
| CHARGE Indication | 38     |

> 振动模块 使用IO4进行驱动，与LED合并在一起


