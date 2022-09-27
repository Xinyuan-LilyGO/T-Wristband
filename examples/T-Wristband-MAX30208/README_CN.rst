*********
MAX30208
*********

.. note::

    使用之前，请先安装 :ref:`快速开始 <安装依赖库>` 。

概况
======

本文档是 `T-Wristband-MAX30208 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX30208>`_ 示例说明。用于指导用户如何使用 ``T-Wristband`` 的 MAX30208 传感器。

Arduino
========

板子可以选择 ``ESP32 Dev Module``，其他设置可以保持默认。

.. warning::

    ``T-Wristband`` 没有使用 PSRAM，请勿开启 PSRAM，和调用 PSRAM 的功能函数。

相关功能开关
============

通过修改 `T-Wristband-MAX30208.ino <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino>`_ 中的相关宏，使能或者失能某些功能。

测试手环的硬件状态是否正常
--------------------------

``FACTORY_HW_TEST`` 宏用于测试手环的硬件状态是否正常，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino
    :linenos:
    :language: c
    :lines: 16-16
    :lineno-start: 16

启用 OTA 更新
--------------

``ARDUINO_OTA_UPDATE`` 宏用于开启 OTA 更新功能，默认关闭。

.. literalinclude:: ../../../examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino
    :linenos:
    :language: c
    :lines: 17-17
    :lineno-start: 17

.. _l_github_Wristband-MPU9250.ino: https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino
.. |l_github_Wristband-MPU9250.ino| replace:: T-Wristband-MAX30208.ino

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
* `MAX30208`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_cn.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _MAX30208: https://datasheets.maximintegrated.com/en/ds/MAX30208.pdf

引脚定义
========

======== ====
Name     Pin
-------- ----
DRV_SDA  15
-------- ----
DRV_SCL  13
======== ====
