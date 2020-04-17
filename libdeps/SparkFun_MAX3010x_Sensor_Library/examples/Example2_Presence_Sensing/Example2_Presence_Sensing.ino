/*
  MAX30105 Breakout: Take IR reading to sense presence
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  This takes an average reading at power up and if the reading changes more than 100
  then print 'Something is there!'.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.

*/

#include <Wire.h>
#include "MAX30105.h"

MAX30105 particleSensor;

long samplesTaken = 0; //Counter for calculating the Hz or read rate
long unblockedValue; //Average IR at power up
long startTime; //Used to calculate measurement rate

void setup()
{
  Serial.begin(9600);
  Serial.println("MAX30105 Presence Sensing Example");

  // Initialize sensor
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  //Setup to sense up to 18 inches, max LED brightness
  byte ledBrightness = 0xFF; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  int sampleRate = 400; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 2048; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

  particleSensor.setPulseAmplitudeRed(0); //Turn off Red LED
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  //Take an average of IR readings at power up
  unblockedValue = 0;
  for (byte x = 0 ; x < 32 ; x++)
  {
    unblockedValue += particleSensor.getIR(); //Read the IR value
  }
  unblockedValue /= 32;

  startTime = millis();
}

void loop()
{
  samplesTaken++;

  Serial.print("IR[");
  Serial.print(particleSensor.getIR());
  Serial.print("] Hz[");
  Serial.print((float)samplesTaken / ((millis() - startTime) / 1000.0), 2);
  Serial.print("]");

  long currentDelta = particleSensor.getIR() - unblockedValue;

  Serial.print(" delta[");
  Serial.print(currentDelta);
  Serial.print("]");

  if (currentDelta > (long)100)
  {
    Serial.print(" Something is there!");
  }

  Serial.println();
}
