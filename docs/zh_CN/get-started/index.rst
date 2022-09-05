********
快速入门
********

本文档旨在指导用户搭建 T-Wristband 硬件开发的软件环境。

概述
====

T-Wristband 支持以下功能：

    * ESP32-PICO-D4
    * 9轴数字运动处理器（PMU9250 或者 LSM9DS1）
    * PCF8563 实时时钟芯片
    * 0.96英寸IPS（80 * 160）
    * 120mAh 可充电锂电池
    * TP4054 电池充电芯片
    * TTP223 触摸按键
    * MAX30102（可选）
    * DRV2605（可选）

准备工作
========

硬件：

* T-Wristband
* 烧录器
* 电脑（Windows、Linux 或 Mac OS）

软件：

* arduino
* platformio

.. todo: 开发板简介

安装准备
========

请先完成工具的安装，具体步骤见下：

+-------------------+-------------------+
| |arduino-logo|    | |platformio-logo| |
+-------------------+-------------------+
| `arduino`_        | `platformio`_     |
+-------------------+-------------------+

.. |arduino-logo| image:: ../../_static/arduino-logo.png
    :target: https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide

.. |platformio-logo| image:: ../../_static/platformio-logo.png
    :target: https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-platformio

.. _arduino: https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-arduino-ide
.. _platformio: https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html#installing-using-platformio

安装串口驱动
=============

因为芯片紧缺和涨价的原因，T-Wristband 的烧录器使用过 cp21xx 或者 ch340。需要根据不同的烧录器，安装对应的驱动程序。

* `CP21xx Drivers`_
* `CH340 Drivers`_

.. _CP21xx Drivers: https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
.. _CH340 Drivers: http://www.wch-ic.com/search?q=ch340&t=downloads

安装依赖库
==========

T-Wristband 需要以下依赖库支持，用户可以用过库管理安装。

* `TFT_eSPI`_
* `PCF8563_Library`_
* `WiFiManager for esp32`_
* `SparkFun_LSM9DS1_Arduino_Library`_
* `Adafruit_DRV2605_Library`_
* `SparkFun_MAX3010x_Sensor_Library`_

.. _TFT_eSPI: https://github.com/Bodmer/TFT_eSPI
.. _PCF8563_Library: https://github.com/lewisxhe/PCF8563_Library
.. _WiFiManager for esp32: https://github.com/tzapu/WiFiManager
.. _SparkFun_LSM9DS1_Arduino_Library: https://github.com/sparkfun/SparkFun_LSM9DS1_Arduino_Library
.. _Adafruit_DRV2605_Library: https://github.com/adafruit/Adafruit_DRV2605_Library
.. _SparkFun_MAX3010x_Sensor_Library: https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library

.. note::

    `libdeps <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/libdeps>`_ 保存了所需要的依赖库，将 `libdeps <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/libdeps>`_ 目录内所有文件拷贝到 ``C:\<UserName>\Documents\Arduino\libraries`` 目录即可。

配置 TFT_eSPI
==============

.. note::

    如果使用 `libdeps <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/libdeps>`_ 目录中库文件,可以跳过这一步

修改 ``C:\<UserName>\Documents\Arduino\libraries\TFT_eSPI\User_Setup_Select.h`` 文件：

* 将 ``#include <User_Setup.h>`` 这一行注释掉
* 找到 ``#include <User_Setups/Setup26_TTGO_T_Wristband.h>`` 这一行，取消前面的注释

.. warning:: 

    如果屏幕出现反色的现象，请参考 :ref:`故障排查 <tft_issue>`

编译例程
========

打开对应的例程，开发板型号选择 ``ESP32 Dev Module``，其他设置可以保持默认。

.. warning::

    T-Wristband 没有使用PSRAM，请勿开启 PSRAM 和调用 PSRAM 相关的功能函数。

烧录器烧录
==========

使用烧录器，通过排线连接到 T-Wristband 。

OTA升级
========

T-Wristband 因为空间的问题，没有板载 usb to ttl 芯片，使用烧录器烧录需要打开外壳，有一定的不便。
选择 OTA 的方式升级，更加的方便。

#. 将示例代码中的 ``ARDUINO_OTA_UPDATE`` 打开，开启 OTA 升级功能，使用烧录器下载固件。
#. 触摸按住按钮三秒钟进行 ``WiFi`` 重置
#. 在Arduino IDE端口中选择 ``T-Wristband`` 进行空中升级

管脚布局
========

==================== =========
Name                 Pin
==================== =========
TFT Driver           ST7735
TFT_MISO             N/A
TFT_MOSI             19
TFT_SCLK             18
TFT_CS               5
TFT_DC               23
TFT_RST              26
TFT_BL               27
Touchpad             33
Touchpad Power       25
RTC Interrupt        34
Battery ADC          35
I2C_SDA              21
I2C_SCL              22
CHARGE Indication    32
IMU INT1             38
IMU INT2             39
IMU INTM             37
IMU RDY              36
DRV_SDA              15
DRV_SCL              13
MAX3010X_SDA         15
MAX3010X_SCL         13
MAX3010X_IRQ         4
==================== =========

.. include:: datasheet.inc
