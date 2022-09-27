*********
MAX3010X
*********

.. note::

    使用之前，请先安装 :ref:`快速开始 <安装依赖库>` 。

概况
======

本文档是 `T-Wristband-MAX3010X <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX3010X>`_ 示例说明。用于指导用户如何使用 ``T-Wristband`` 的 MAX3010X 传感器。

Arduino
========

板子可以选择 ``ESP32 Dev Module``，其他设置可以保持默认。

.. warning::

    ``T-Wristband`` 没有使用 PSRAM，请勿开启 PSRAM，和调用 PSRAM 的功能函数。

更多心率示例请参考 `SparkFun_MAX3010x_Sensor_Library <https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library>`_ 。

数据手册
=========

* `ESP32-PICO-D4`_ (Datasheet)
* `ST7735`_ (Datasheet)
* `MAX30102`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_cn.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _MAX30102: https://datasheets.maximintegrated.com/en/ds/MAX30102.pdf

引脚定义
========

============= ====
Name          Pin
------------- ----
MAX3010X_SDA  15
------------- ----
MAX3010X_SCL  13
------------- ----
MAX3010X_IRQ  4
============= ====
