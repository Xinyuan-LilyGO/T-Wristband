*********
LSM9DS1
*********

.. note::

    Before using it, please install :ref:`Get Started <Install dependent libraries>`.

Introduction
=============

This document is `T-Wristband-LSM9DS1 <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-LSM9DS1>`_ example description. LSM9DS1 sensor for instructing the user how to use the ``T-Wristband``.

Arduino
========

``T-Wristband`` can choose ``ESP32 Dev Module``, and other settings can be kept as default.

.. warning::

    ``T-Wristband`` does not use PSRAM, please do not enable PSRAM, and call PSRAM functions.

Related Function Switch
========================

By modifying `T-Wristband-LSM9DS1.ino <https://github.com/Xinyuan-LilyGO/LilyGo-T-Wristband/tree/master/examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino>`_ The related macros in _ enable or disable certain functions.

Hardware Test
---------------

The ``FACTORY_HW_TEST`` macro is used to test whether the hardware status of the bracelet is normal. It is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 14-14
    :lineno-start: 14

BLE transmits IMU data
-----------------------

The ``ENABLE_BLE_DATA_TRANSMISSION`` macro is used to test the BLE transfer IMU data example, which is disabled by default.

You can use ``nRF Connect``, ``LightBlue`` and other APPs to connect to view the data.

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 20-20
    :lineno-start: 20

Enable LSM9DS1 sensor function
-------------------------------

The ``ENABLE_SENSOR`` macro is used to enable the LSM9DS1 sensor function. Off by default.

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 23-23
    :lineno-start: 23

Enable LSM9DS1 sensor shutdown mode function
---------------------------------------------

The ``USE_PROTECTED_MEMBERS`` macro is used to enable the LSM9DS1 sensor shutdown mode function. Off by default.

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 37-37
    :lineno-start: 37

.. note::

    Before use, please make sure that you have changed the three member methods of SparkFun_LSM9DS1_Arduino_Library to common member methods, or directly use the library file in `libdeps`.

OTA update
-----------

The ``ARDUINO_OTA_UPDATE`` macro is used to enable the OTA update function, which is disabled by default.

.. literalinclude:: ../../../examples/T-Wristband-LSM9DS1/T-Wristband-LSM9DS1.ino
    :linenos:
    :language: c
    :lines: 17-17
    :lineno-start: 17

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
* `LSM9DS1`_ (Datasheet)

.. _ESP32-PICO-D4: https://www.espressif.com.cn/sites/default/files/documentation/esp32-pico-d4_datasheet_en.pdf
.. _ST7735: http://www.displayfuture.com/Display/datasheet/controller/ST7735.pdf
.. _LSM9DS1: https://www.st.com/resource/en/datasheet/lsm9ds1.pdf

Pinout
===========

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
