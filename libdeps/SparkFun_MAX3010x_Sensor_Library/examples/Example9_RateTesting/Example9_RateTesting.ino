/*
  MAX30105 Breakout: Take readings from the FIFO
  By: Nathan Seidle @ SparkFun Electronics
  Date: April 8th, 2018
  https://github.com/sparkfun/MAX30105_Breakout

  Push the MAX30105 as fast as it will go!

  We used a Teensy 3.2 for testing. This will configure the MAX3010x and
  output at approximately 3200Hz.

  On an Uno the fastest we can read is 2700Hz.

  Setting required:
  Sample average has a direct impact on max read amount. Set to 1 for max speed.
  The pulsewidth must be as short as possible. Set to 69.
  ledMode must be 1 for 3200Hz. If ledMode is set to 2 max is 1600Hz.
  Run at 400kHz I2C communication speed.
  Print serial at 115200.

  Any serial printing will slow the reading of data and may cause the FIFO to overflow.
  Keep your prints small.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA) - Pin 18 on Teensy
  -SCL = A5 (or SCL) - Pin 19 on Teensy
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

void setup()
{
  Serial.begin(115200);
  while(!Serial); //We must wait for Teensy to come online
  Serial.println("Max sample rate example");

  // Initialize sensor
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  //Setup to sense up to 18 inches, max LED brightness
  byte ledBrightness = 0xFF; //Options: 0=Off to 255=50mA
  byte sampleAverage = 1; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 1; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 3200; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 69; //Options: 69, 118, 215, 411
  int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
}

void loop()
{
  byte samplesTaken = 0;
  long startTime = micros();

  while(samplesTaken < 10)
  {
    particleSensor.check(); //Check the sensor, read up to 3 samples
    while (particleSensor.available()) //do we have new data?
    {
      samplesTaken++;
      particleSensor.getFIFOIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample
    }
  }

  long endTime = micros();

  Serial.print("samples[");
  Serial.print(samplesTaken);

  Serial.print("] Hz[");
  Serial.print((float)samplesTaken / ((endTime - startTime) / 1000000.0), 2);
  Serial.print("]");

  Serial.println();
}
