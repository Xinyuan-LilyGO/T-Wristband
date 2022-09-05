************
Get Started
************

This document is intended to guide users to build a software environment for T-Wristband hardware development.

Introduction
=============

T-Wristband supports the following features:

    * ESP32-PICO-D4
    * 9-axis Digital Motion Processor(PMU9250 or LSM9DS1)
    * PCF8563 Real-Time Clock
    * 0.96-inch IPS(80 * 160)
    * 120mAh Rechargeable Lithium Battery
    * TP4054 Battery Charging Chip
    * TTP223 Touch Button
    * MAX30102(optional)
    * DRV2605(optional)

What You Need
==============

Hardware:

* T-Wristband
* Programmer
* Computer running Windows, Linux, or macOS

Software:

* arduino
* platformio

.. todo: 开发板简介

Install prerequisites
======================

Please complete the installation of the tool first. The specific steps are as follows:

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

Install serial driver
======================

Due to the shortage of chips and the price increase, T-Wristband's programmer has used cp21xx or ch340. You need to install the corresponding driver according to different Programmers.

* `CP21xx Drivers`_
* `CH340 Drivers`_

.. _CP21xx Drivers: https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers
.. _CH340 Drivers: http://www.wch-ic.com/search?q=ch340&t=downloads

Install dependent libraries
============================

T-Wristband requires the following dependency library support, users can use the library to manage the installation.

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

    `libdeps <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/libdeps>`_ saves the required dependencies, and `libdeps <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/libdeps>`_ directory to ``C:\<UserName>\Documents\Arduino\libraries`` directory.

Configure TFT_eSPI
===================

.. note::

    If you use the library files in the `libdeps <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/libdeps>`_ directory, you can skip this step

Modify the ``C:\<UserName>\Documents\Arduino\libraries\TFT_eSPI\User_Setup_Select.h`` file:

* Comment out the line ``#include <User_Setup.h>``
* Find the line ``#include <User_Setups/Setup26_TTGO_T_Wristband.h>`` and uncomment the previous

.. warning:: 

    If the screen has reversed colors, please refer to :ref:`Troubleshooting <tft_issue>`

Build example
==============

Open the corresponding example, select ``ESP32 Dev Module`` for the development board model, and keep other settings as default.

.. warning::

    T-Wristband does not use PSRAM, please do not enable PSRAM and call PSRAM related functions.

Programmer burning
===================

Using the Programmer, connect it to the T-Wristband via a cable.

OTA update
===========

T-Wristband does not have an onboard usb to ttl chip due to space problems, and it is inconvenient to open the shell to use the Programmer to burn. It is more convenient to choose OTA to upgrade.

#. Open ``ARDUINO_OTA_UPDATE`` in the source code, enable the OTA upgrade function, and use the Programmer to download the firmware.
#. ``WiFi`` reset by touching and holding the button for three seconds
#. Select ``T-Wristband`` in Arduino IDE port for over-the-air upgrade

Pin layout
===========

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
