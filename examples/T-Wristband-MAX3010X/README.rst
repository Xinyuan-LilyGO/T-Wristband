*********
MAX3010X
*********

.. note::

    Before using it, please install :ref:`Get Started <Install dependent libraries>`.

Introduction
=============

This document is `T-Wristband-MAX3010X <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX3010X>`_ example description. A MAX3010X sensor for instructing the user on how to use the ``T-Wristband``.

Arduino
========

``T-Wristband`` can choose ``ESP32 Dev Module``, and other settings can be kept as default.

For more heart rate examples, please refer to `SparkFun_MAX3010x_Sensor_Library <https://github.com/sparkfun/SparkFun_MAX3010x_Sensor_Library>`_ .

.. warning::

    ``T-Wristband`` does not use PSRAM, please do not enable PSRAM, and call PSRAM functions.

Datasheet
==========

* `ESP32-PICO-D4`_ (Datasheet)
* `ST7735`_ (Datasheet)
* `MAX30102`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _MAX30102: https://datasheets.maximintegrated.com/en/ds/MAX30102.pdf

Pinout
===========

============= ====
Name          Pin
------------- ----
MAX3010X_SDA  15
------------- ----
MAX3010X_SCL  13
------------- ----
MAX3010X_IRQ  4
============= ====
