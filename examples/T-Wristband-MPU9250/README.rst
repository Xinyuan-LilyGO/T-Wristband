*********
MPU9250
*********

.. note::

    Before using it, please install :ref:`Get Started <Install dependent libraries>`.

Introduction
=============

This document is `T-Wristband-MPU9250 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MPU9250>`_ example description. MPU9250 sensor for instructing the user how to use the ``T-Wristband``.

Arduino
========

``T-Wristband`` can choose ``ESP32 Dev Module``, and other settings can be kept as default.

.. warning::

    ``T-Wristband`` does not use PSRAM, please do not enable PSRAM, and call PSRAM functions.

Related Function Switch
========================

Enable or disable certain functions by modifying the relevant macros in |l_github_Wristband-MPU9250.ino|_.

Hardware Test
---------------

The ``FACTORY_HW_TEST`` macro is used to test whether the hardware status of the bracelet is normal. It is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-MPU9250/T-Wristband-MPU9250.ino
    :linenos:
    :language: c
    :lines: 14-14
    :lineno-start: 14

OTA update
-----------

The ``ARDUINO_OTA_UPDATE`` macro is used to enable the OTA update function, which is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-MPU9250/T-Wristband-MPU9250.ino
    :linenos:
    :language: c
    :lines: 17-17
    :lineno-start: 17

.. _l_github_Wristband-MPU9250.ino: https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-MPU9250/T-Wristband-MPU9250.ino
.. |l_github_Wristband-MPU9250.ino| replace:: T-Wristband-MPU9250.ino

User Manual
============

Touch the button to switch to the next function when a press is detected:

    1. Press for the first time to view the nine-axis sensor information
    #. Press it a second time to enter deep sleep
    #. During deep sleep, touch again to wake up the bracelet

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
* `MPU9250`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _MPU9250: https://invensense.tdk.com/wp-content/uploads/2015/02/PS-MPU-9250A-01-v1.1.pdf

Pinout
===========

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

    The vibration module is driven using IO4, which is incorporated with the LED.
