*********
MAX30208
*********

.. note::

    Before using it, please install :ref:`Get Started <Install dependent libraries>`.

Introduction
=============

This document is a `T-Wristband-MAX30208 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX30208>`_ example description. A MAX30208 sensor for instructing the user on how to use the ``T-Wristband``.

Arduino
========

``T-Wristband`` can choose ``ESP32 Dev Module``, and other settings can be kept as default.

.. warning::

    ``T-Wristband`` does not use PSRAM, please do not enable PSRAM, and call PSRAM functions.

Related Function Switch
========================

By modifying `T-Wristband-MAX30208.ino <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino>`_ The related macros in _ enable or disable certain functions.

Hardware Test
---------------

The ``FACTORY_HW_TEST`` macro is used to test whether the hardware status of the bracelet is normal. It is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino
    :linenos:
    :language: c
    :lines: 16-16
    :lineno-start: 16

OTA update
-----------

The ``ARDUINO_OTA_UPDATE`` macro is used to enable the OTA update function, which is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino
    :linenos:
    :language: c
    :lines: 17-17
    :lineno-start: 17

.. _l_github_Wristband-MPU9250.ino: https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MAX30208/T-Wristband-MAX30208.ino
.. |l_github_Wristband-MPU9250.ino| replace:: T-Wristband-MAX30208.ino

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
* `MAX30208`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _MAX30208: https://datasheets.maximintegrated.com/en/ds/MAX30208.pdf

Pinout
===========

======== ====
Name     Pin
-------- ----
DRV_SDA  15
-------- ----
DRV_SCL  13
======== ====
