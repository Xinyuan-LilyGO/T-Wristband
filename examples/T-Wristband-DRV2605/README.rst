*********
DRV2605
*********

.. note::

    Before using it, please install :ref:`Get Started <Install dependent libraries>`.

Introduction
=============

This document is `T-Wristband-DRV2605 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-DRV2605>`_ example description. DRV2605 Haptic Module for instructing the user how to use the ``T-Wristband``.

Arduino
========

``T-Wristband`` can choose ``ESP32 Dev Module``, and other settings can be kept as default.

.. warning::

    ``T-Wristband`` does not use PSRAM, please do not enable PSRAM, and call PSRAM functions.

For more DRV2605 examples, please refer to `Adafruit_DRV2605_Library <https://github.com/adafruit/Adafruit_DRV2605_Library>`_ .

Related Function Switch
========================

Some functions can be enabled or disabled by modifying the relevant macros in |l_github_Wristband-DRV2605.ino|_.

DRV2605 Haptic Module
----------------------

The ``ENABLE_DRV2605`` macro is used to enable the DRV2605 haptic module and is enabled by default.

.. literalinclude:: ../../../examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino
    :linenos:
    :language: c
    :lines: 13-13
    :lineno-start: 13

Hardware Test
---------------

The ``FACTORY_HW_TEST`` macro is used to test whether the hardware status of the bracelet is normal. It is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino
    :linenos:
    :language: c
    :lines: 14-14
    :lineno-start: 14

OTA update
-----------

The ``ARDUINO_OTA_UPDATE`` macro is used to enable the OTA update function, which is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino
    :linenos:
    :language: c
    :lines: 15-15
    :lineno-start: 15

.. _l_github_Wristband-DRV2605.ino: https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-DRV2605/T-Wristband-DRV2605.ino
.. |l_github_Wristband-DRV2605.ino| replace:: T-Wristband-DRV2605.ino

User Manual
============

OTA update:

    1. Touch and hold the button for three seconds to do a ``WiFi`` reset.
    #. Select ``T-Wristband`` in the ``Arduino IDE`` port to upgrade over the air, as shown below:

        .. image:: ../../../docs/_static/readme/2.jpg

.. note::

    Enable ``ARDUINO_OTA_UPDATE`` macro OTA update is valid.

Datasheet
==========

* `ESP32-PICO-D4`_ (Datasheet)
* `ST7735`_ (Datasheet)
* `DRV2605`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _DRV2605: https://www.ti.com/lit/ds/symlink/drv2605.pdf?ts=1662177472179&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FDRV2605

Pinout
===========

======== ====
Name     Pin
-------- ----
DRV_SDA  15
-------- ----
DRV_SCL  13
======== ====
