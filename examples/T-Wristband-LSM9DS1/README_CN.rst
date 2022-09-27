*********
LSM9DS1
*********

.. note::

    使用之前，请先安装 :ref:`快速开始 <安装依赖库>` 。

概况
======

本文档是 `T-Wristband-LSM9DS1 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-LSM9DS1>`_ 示例说明。用于指导用户如何使用 ``T-Wristband`` 的 LSM9DS1 传感器。

Arduino
========

板子可以选择 ``ESP32 Dev Module``，其他设置可以保持默认。

.. warning::

    ``T-Wristband`` 没有使用 PSRAM，请勿开启 PSRAM，和调用 PSRAM 的功能函数。

相关功能开关
============

通过修改 `T-Wristband-LSM9DS1.ino <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino>`_ 中的相关宏，使能或者失能某些功能。

测试手环的硬件状态是否正常
-----------------------------

``FACTORY_HW_TEST`` 宏用于测试手环的硬件状态是否正常，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 14-14
    :lineno-start: 14

测试 BLE 传输 IMU 数据
-----------------------

``ENABLE_BLE_DATA_TRANSMISSION`` 宏用于测试BLE传输IMU数据示例，默认关闭。

可以使用 ``nRF Connect``， ``LightBlue`` 等 APP 进行连接查看数据。

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 20-20
    :lineno-start: 20

开启 LSM9DS1 传感器功能
-----------------------

``ENABLE_SENSOR`` 宏用于开启 LSM9DS1 传感器功能。默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 23-23
    :lineno-start: 23

开启 LSM9DS1 传感器关断模式功能
-------------------------------

``USE_PROTECTED_MEMBERS`` 宏用于开启 LSM9DS1 传感器关断模式功能。默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 37-37
    :lineno-start: 37

.. note::

    使用前请确保你已经将 SparkFun_LSM9DS1_Arduino_Library 三个成员方法更改为共有成员方法，或者直接使用 `libdeps` 内的库文件。

OTA 更新
---------

``ARDUINO_OTA_UPDATE`` 宏用于开启 OTA 更新功能，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 17-17
    :lineno-start: 17

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
* `LSM9DS1`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_cn.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _LSM9DS1: https://www.st.com/resource/en/datasheet/lsm9ds1.pdf

引脚定义
========

================== ======
Name               Pin
------------------ ------
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
RTC Interrupt      34    
Battery ADC        35    
I2C_SDA            21    
I2C_SCL            22    
CHARGE Indication  32    
IMU INT1           38    
IMU INT2           39    
IMU INTM           37    
IMU RDY            36    
================== ======
