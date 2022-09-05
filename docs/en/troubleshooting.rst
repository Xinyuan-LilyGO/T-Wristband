****************
Troubleshooting
****************

Hardware
=========

.. _tft_issue:

New version screens (with green labels) require configuration changes
----------------------------------------------------------------------

Due to supply problems, the new version of the screen and the old version of the screen configuration is different. The current (2022-09-05) shipments are all new version screens.

.. image:: ../_static/readme/new_version_green_tag.png

For different versions of the screen, you need to change the macro definition in ``C:\<UserName>\Documents\Arduino\libraries\TFT_eSPI\User_Setups\Setup26_TTGO_T_Wristband.h``:

* New version screen (with green label)

.. image:: ../_static/readme/new_version.png

* old version screen

.. image:: ../_static/readme/older_version.png

How to differentiate LSM9DS1 from MPU9250 sensor?
--------------------------------------------------

Please see the upper right half of the board below to distinguish:

.. image:: ../_static/readme/3.jpg
