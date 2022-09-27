*********
MPU9250
*********

.. note::

    使用之前，请先安装 :ref:`快速开始 <安装依赖库>` 。

概况
======

本文档是 `T-Wristband-MPU9250 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MPU9250>`_ 示例说明。用于指导用户如何使用 ``T-Wristband`` 的 MPU9250 传感器。

Arduino
========

板子可以选择 ``ESP32 Dev Module``，其他设置可以保持默认。

.. warning::

    ``T-Wristband`` 没有使用 PSRAM，请勿开启 PSRAM，和调用 PSRAM 的功能函数。

相关功能开关
============

通过修改 |l_github_Wristband-MPU9250.ino|_ 中的相关宏，使能或者失能某些功能。

测试手环的硬件状态是否正常
--------------------------

``FACTORY_HW_TEST`` 宏用于测试手环的硬件状态是否正常，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-MPU9250/T-Wristband-MPU9250.ino
    :linenos:
    :language: c
    :lines: 14-14
    :lineno-start: 14

启用 OTA 更新
--------------

``ARDUINO_OTA_UPDATE`` 宏用于开启 OTA 更新功能，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-MPU9250/T-Wristband-MPU9250.ino
    :linenos:
    :language: c
    :lines: 17-17
    :lineno-start: 17

.. _l_github_Wristband-MPU9250.ino: https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MPU9250/T-Wristband-MPU9250.ino
.. |l_github_Wristband-MPU9250.ino| replace:: T-Wristband-MPU9250.ino

使用说明
=========

触摸按钮当检测到按下则切换功能:

    1. 按下第一次 将查看九轴传感器信息
    #. 按下第二次 将进入深度睡眠
    #. 在深度睡眠中，再次触摸唤醒手环

OTA 更新:

    1. 触摸按住按钮三秒钟，进行 ``WiFi`` 重置。
    #. 在 ``Arduino IDE`` 端口中选择 ``T-Wristband`` 进行空中升级，如下图：

        .. image:: ../../../docs/_static/readme/2.jpg

.. note::

    使能 ``ARDUINO_OTA_UPDATE`` 宏 OTA 更新才有效。

数据手册
=========

* `ESP32-PICO-D4`_ (Datasheet)
* `ST7735`_ (Datasheet)
* `MPU9250`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_cn.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _MPU9250: https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf

引脚定义
========

================== =======
Name               Pin
------------------ -------
TFT Driver         ST7735
TFT_MISO           N/A
TFT_MOSI           19
TFT_SCLK           18
TFT_CS             5
TFT_DC             23
TFT_RST            26
TFT_BL             27
Touchpad           33
Touchpad Power     25
IMU Interrupt      38
RTC Interrupt      34
Battery ADC        35
VBUS ADC           36
I2C SDA            21
I2C SCL            22
LED and Vibration  4
CHARGE Indication  38
================== =======

.. note::

    振动模块使用IO4进行驱动，与 LED 合并在一起。
