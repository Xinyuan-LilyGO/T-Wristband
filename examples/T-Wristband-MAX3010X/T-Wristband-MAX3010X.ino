
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <Wire.h>

#define LED_PIN             4

#define HEATRATE_SDA        15
#define HEATRATE_SCL        13
#define HEATRATE_INT        4

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#include "MAX30105.h"
#include "heartRate.h"

MAX30105 particleSensor;

const uint8_t RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
uint8_t rates[RATE_SIZE]; //Array of heart rates
uint8_t rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

char buff[256];


void setup(void)
{
    Serial.begin(115200);

    tft.init();
    tft.setRotation(1);
    tft.setTextColor(TFT_GREEN, TFT_BLACK); // Note: the new fonts do not draw the background colour
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 0);

    pinMode(LED_PIN, OUTPUT);

    Wire1.begin(HEATRATE_SDA, HEATRATE_SCL);
    // Initialize sensor
    if (!particleSensor.begin(Wire1, 400000)) { //Use default I2C port, 400kHz speed
        tft.setTextColor(TFT_RED, TFT_BLACK); // Note: the new fonts do not draw the background colour
        tft.println("MAX30105 was not found");
        delay(10000);   //delay ten sec to restart
        esp_restart();
    }

    particleSensor.setup(); //Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}



void loop()
{
    long irValue = particleSensor.getIR();

    if (checkForBeat(irValue) == true) {
        //We sensed a beat!
        long delta = millis() - lastBeat;
        lastBeat = millis();

        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20) {
            rates[rateSpot++] = (uint8_t)beatsPerMinute; //Store this reading in the array
            rateSpot %= RATE_SIZE; //Wrap variable

            //Take average of readings
            beatAvg = 0;
            for (uint8_t x = 0 ; x < RATE_SIZE ; x++)
                beatAvg += rates[x];
            beatAvg /= RATE_SIZE;
        }
    }

    tft.fillScreen(TFT_BLACK);
    snprintf(buff, sizeof(buff), "IR=%lu BPM=%.2f", irValue, beatsPerMinute);
    tft.drawString(buff, 0, 0);
    snprintf(buff, sizeof(buff), "Avg BPM=%d", beatAvg);
    tft.drawString(buff, 0, 16);

    if (irValue < 50000)
        digitalWrite(LED_PIN, 0);
    else
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}