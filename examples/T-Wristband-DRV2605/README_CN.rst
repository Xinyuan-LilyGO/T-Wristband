*********
DRV2605
*********

.. note::

    使用之前，请先安装 :ref:`快速开始 <安装依赖库>` 。

概况
======

本文档是 `T-Wristband-DRV2605 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-DRV2605>`_ 示例说明。用于指导用户如何使用 ``T-Wristband`` 的 DRV2605 触觉模块。

Arduino
========

板子可以选择 ``ESP32 Dev Module``，其他设置可以保持默认。

.. warning::

    ``T-Wristband`` 没有使用 PSRAM，请勿开启 PSRAM，和调用 PSRAM 的功能函数。

更多心率示例请参考 `Adafruit_DRV2605_Library <https://github.com/adafruit/Adafruit_DRV2605_Library>`_ 。

相关功能开关
============

通过修改 `T-Wristband-DRV2605.ino <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino>`_ 中的相关宏，使能或者失能某些功能。

DRV2605 触觉模块
----------------------

``ENABLE_DRV2605`` 宏用于使能 DRV2605 触觉模块，默认打开。

.. literalinclude:: ../../../examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino
    :linenos:
    :language: c
    :lines: 13-13
    :lineno-start: 13

测试手环的硬件状态是否正常
-----------------------------

``FACTORY_HW_TEST`` 宏用于测试手环的硬件状态是否正常，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino
    :linenos:
    :language: c
    :lines: 14-14
    :lineno-start: 14

OTA 更新
---------

``ARDUINO_OTA_UPDATE`` 宏用于开启 OTA 更新功能，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino
    :linenos:
    :language: c
    :lines: 15-15
    :lineno-start: 15

使用说明
=========

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
* `DRV2605`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_cn.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _DRV2605: https://www.ti.com/lit/ds/symlink/drv2605.pdf?ts=1662177472179&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FDRV2605

引脚定义
========

======== ====
Name     Pin
-------- ----
DRV_SDA  15
-------- ----
DRV_SCL  13
======== ====
