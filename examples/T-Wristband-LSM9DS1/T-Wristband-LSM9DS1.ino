
#include <pcf8563.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <Wire.h>
#include <WiFi.h>
#include "sensor.h"
#include "esp_adc_cal.h"
#include "ttgo.h"
#include "charge.h"
#include <SparkFunLSM9DS1.h>

//! Uncomment this line and a hardware test will be conducted
// #define FACTORY_HW_TEST

//! Uncomment this line and use WiFi for OTA update
// #define ARDUINO_OTA_UPDATE

//! Uncomment this line and Bluetooth will be used to transfer IMU data
#define ENABLE_BLE_DATA_TRANSMISSION

// Uncomment this line and the sensor will be used
// #define ENABLE_SENSOR

/*
You need to know using the following functions.
These three methods are all set as protection members in the original SparkFun_LSM9DS1_Arduino_Library.
If you need to use them, you need to put the three methods into public members.
This is just for faster sensor testing. Low current consumption

!!! In actual test, LSM9DS1 consumes about 1 mA !!!

!!!In the actual test, the LSM9DS1 consumes about 1 mA of current.
    If you do not turn them off, it will consume about 4~6mA!!!

**/
// #define USE_PROTECTED_MEMBERS




#ifdef ENABLE_BLE_DATA_TRANSMISSION
#ifndef ENABLE_SENSOR
#define ENABLE_SENSOR
#endif
#endif

#ifndef ST7735_SLPIN
#define ST7735_SLPIN    0x10
#define ST7735_DISPOFF  0x28
#endif

#define TP_PIN_PIN          33
#define I2C_SDA_PIN         21
#define I2C_SCL_PIN         22
#define RTC_INT_PIN         34
#define BATT_ADC_PIN        35
#define TP_PWR_PIN          25
#define LED_PIN             4
#define CHARGE_PIN          32
#define INT1_PIN_THS        38
#define INT2_PIN_DRDY       39
#define INTM_PIN_THS        37
#define RDYM_PIN            36
#define MOTOR_PIN           14

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h
PCF8563_Class rtc;
LSM9DS1 imu; // Create an LSM9DS1 object to use from here on.


char buff[256];
bool rtcIrq = false;
bool initial = 1;
bool otaStart = false;

uint8_t func_select = 0;
uint8_t omm = 99;
uint8_t xcolon = 0;
uint32_t targetTime = 0;       // for next 1 second timeout
uint32_t colour = 0;
int vref = 1100;

bool pressed = false;
uint32_t pressedTime = 0;
bool charge_indication = false;
bool charge_show = false;
uint8_t hh, mm, ss ;

#ifdef ARDUINO_OTA_UPDATE
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//  git clone -b development https://github.com/tzapu/WiFiManager.git
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager
WiFiManager wifiManager;

void configModeCallback (WiFiManager *myWiFiManager)
{
    Serial.println("Entered config mode");
    Serial.println(WiFi.softAPIP());
    //if you used auto generated SSID, print it
    Serial.println(myWiFiManager->getConfigPortalSSID());

    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE);
    tft.drawString("Connect hotspot name ",  20, tft.height() / 2 - 20);
    tft.drawString("configure wrist",  35, tft.height() / 2  + 20);
    tft.setTextColor(TFT_GREEN);
    tft.drawString("\"T-Wristband\"",  40, tft.height() / 2 );

}


void drawProgressBar(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h, uint8_t percentage, uint16_t frameColor, uint16_t barColor)
{
    if (percentage == 0) {
        tft.fillRoundRect(x0, y0, w, h, 3, TFT_BLACK);
    }
    uint8_t margin = 2;
    uint16_t barHeight = h - 2 * margin;
    uint16_t barWidth = w - 2 * margin;
    tft.drawRoundRect(x0, y0, w, h, 3, frameColor);
    tft.fillRect(x0 + margin, y0 + margin, barWidth * percentage / 100.0, barHeight, barColor);
}


#endif  /*ARDUINO_OTA_UPDATE*/


#ifdef  ENABLE_BLE_DATA_TRANSMISSION
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>

#define SENSOR_SERVICE_UUID                 "4fafc301-1fb5-459e-8fcc-c5c9c331914b"
#define SENSOR_CHARACTERISTIC_UUID          "beb5483c-36e1-4688-b7f5-ea07361b26a8"
static BLECharacteristic *pSensorCharacteristic = nullptr;
static BLEDescriptor  *pSensorDescriptor = nullptr;

static bool deviceConnected = false;
static bool enableNotify = false;

class DeviceServerCallbacks: public BLEServerCallbacks
{
    void onConnect(BLEServer *pServer)
    {
        deviceConnected = true;
        Serial.println("Device connect");
    };

    void onDisconnect(BLEServer *pServer)
    {
        deviceConnected = false;
        enableNotify = false;
        Serial.println("Device disconnect");
    }
};

class SensorDescriptorCallbacks: public BLEDescriptorCallbacks
{
    void onWrite(BLEDescriptor *pDescriptor)
    {
        uint8_t *value = pDescriptor->getValue();
        Serial.print("SensorDescriptorCallbacks:");
        enableNotify = value[0] ? true : false;
    }
    void onRead(BLEDescriptor *pDescriptor)
    {

    }
};
#endif


void setupBLE()
{
#ifdef  ENABLE_BLE_DATA_TRANSMISSION
    BLEDevice::init("T-Wristband");


    BLEServer *pServer = BLEDevice::createServer();

    pServer->setCallbacks(new DeviceServerCallbacks());

    /*Sensor Service*/
    BLEService *pSensorService = pServer->createService(SENSOR_SERVICE_UUID);

    pSensorCharacteristic = pSensorService->createCharacteristic(
                                SENSOR_CHARACTERISTIC_UUID,
                                BLECharacteristic::PROPERTY_READ   |
                                BLECharacteristic::PROPERTY_NOTIFY
                            );
    pSensorCharacteristic->addDescriptor(new BLE2902());

    pSensorDescriptor = pSensorCharacteristic->getDescriptorByUUID("2902");

    pSensorDescriptor->setCallbacks(new SensorDescriptorCallbacks());

    pSensorService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();

    pAdvertising->addServiceUUID(SENSOR_SERVICE_UUID);

    pAdvertising->setScanResponse(true);

    pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue

    pAdvertising->setMinPreferred(0x12);

    BLEDevice::startAdvertising();

#endif
}


void configureLSM9DS1Interrupts()
{
    /////////////////////////////////////////////
    // Configure INT1 - Gyro & Accel Threshold //
    /////////////////////////////////////////////
    // For more information on setting gyro interrupt, threshold,
    // and configuring the intterup, see the datasheet.
    // We'll configure INT_GEN_CFG_G, INT_GEN_THS_??_G,
    // INT_GEN_DUR_G, and INT1_CTRL.
    // 1. Configure the gyro interrupt generator:
    //  - ZHIE_G: Z-axis high event (more can be or'd together)
    //  - false: and/or (false = OR) (not applicable)
    //  - false: latch interrupt (false = not latched)
    imu.configGyroInt(ZHIE_G, false, false);
    // 2. Configure the gyro threshold
    //   - 500: Threshold (raw value from gyro)
    //   - Z_AXIS: Z-axis threshold
    //   - 10: duration (based on ODR)
    //   - true: wait (wait duration before interrupt goes low)
    imu.configGyroThs(500, Z_AXIS, 10, true);
    // 3. Configure accelerometer interrupt generator:
    //   - XHIE_XL: x-axis high event
    //     More axis events can be or'd together
    //   - false: OR interrupts (N/A, since we only have 1)
    imu.configAccelInt(XHIE_XL, false);
    // 4. Configure accelerometer threshold:
    //   - 20: Threshold (raw value from accel)
    //     Multiply this value by 128 to get threshold value.
    //     (20 = 2600 raw accel value)
    //   - X_AXIS: Write to X-axis threshold
    //   - 10: duration (based on ODR)
    //   - false: wait (wait [duration] before interrupt goes low)
    imu.configAccelThs(20, X_AXIS, 1, false);
    // 5. Configure INT1 - assign it to gyro interrupt
    //   - XG_INT1: Says we're configuring INT1
    //   - INT1_IG_G | INT1_IG_XL: Sets interrupt source to
    //     both gyro interrupt and accel
    //   - INT_ACTIVE_LOW: Sets interrupt to active low.
    //         (Can otherwise be set to INT_ACTIVE_HIGH.)
    //   - INT_PUSH_PULL: Sets interrupt to a push-pull.
    //         (Can otherwise be set to INT_OPEN_DRAIN.)
    imu.configInt(XG_INT1, INT1_IG_G | INT_IG_XL, INT_ACTIVE_LOW, INT_PUSH_PULL);

    ////////////////////////////////////////////////
    // Configure INT2 - Gyro and Accel Data Ready //
    ////////////////////////////////////////////////
    // Configure interrupt 2 to fire whenever new accelerometer
    // or gyroscope data is available.
    // Note XG_INT2 means configuring interrupt 2.
    // INT_DRDY_XL is OR'd with INT_DRDY_G
    imu.configInt(XG_INT2, INT_DRDY_XL | INT_DRDY_G, INT_ACTIVE_LOW, INT_PUSH_PULL);

    //////////////////////////////////////
    // Configure Magnetometer Interrupt //
    //////////////////////////////////////
    // 1. Configure magnetometer interrupt:
    //   - XIEN: axis to be monitored. Can be an or'd combination
    //     of XIEN, YIEN, or ZIEN.
    //   - INT_ACTIVE_LOW: Interrupt goes low when active.
    //   - true: Latch interrupt
    imu.configMagInt(XIEN, INT_ACTIVE_LOW, true);
    // 2. Configure magnetometer threshold.
    //   There's only one threshold value for all 3 mag axes.
    //   This is the raw mag value that must be exceeded to
    //   generate an interrupt.
    imu.configMagThs(10000);

}

uint16_t setupIMU()
{
    // Set up our Arduino pins connected to interrupts.
    // We configured all of these interrupts in the LSM9DS1
    // to be active-low.
    pinMode(INT2_PIN_DRDY, INPUT);
    pinMode(INT1_PIN_THS, INPUT);
    pinMode(INTM_PIN_THS, INPUT);

    // The magnetometer DRDY pin (RDY) is not configurable.
    // It is active high and always turned on.
    pinMode(RDYM_PIN, INPUT);

    // gyro.latchInterrupt controls the latching of the
    // gyro and accelerometer interrupts (INT1 and INT2).
    // false = no latching
    imu.settings.gyro.latchInterrupt = false;
    // Set gyroscope scale to +/-245 dps:
    imu.settings.gyro.scale = 245;
    // Set gyroscope (and accel) sample rate to 14.9 Hz
    imu.settings.gyro.sampleRate = 1;
    // Set accelerometer scale to +/-2g
    imu.settings.accel.scale = 2;
    // Set magnetometer scale to +/- 4g
    imu.settings.mag.scale = 4;
    // Set magnetometer sample rate to 0.625 Hz
    imu.settings.mag.sampleRate = 0;

    // Call imu.begin() to initialize the sensor and instill
    // it with our new settings.
    bool r =  imu.begin(LSM9DS1_AG_ADDR(1), LSM9DS1_M_ADDR(1), Wire); // set addresses and wire port
    if (r) {
        imu.sleepGyro(false);
        return true;
    }
    return false;

}




void scanI2Cdevice(void)
{
    uint8_t err, addr;
    int nDevices = 0;
    for (addr = 1; addr < 127; addr++) {
        Wire.beginTransmission(addr);
        err = Wire.endTransmission();
        if (err == 0) {
            Serial.print("I2C device found at address 0x");
            if (addr < 16)
                Serial.print("0");
            Serial.print(addr, HEX);
            Serial.println(" !");
            nDevices++;
        } else if (err == 4) {
            Serial.print("Unknow error at address 0x");
            if (addr < 16)
                Serial.print("0");
            Serial.println(addr, HEX);
        }
    }
    if (nDevices == 0)
        Serial.println("No I2C devices found\n");
    else
        Serial.println("Done\n");
}


void wifi_scan()
{
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.setTextSize(1);

    tft.drawString("Scan Network", tft.width() / 2, tft.height() / 2);

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    int16_t n = WiFi.scanNetworks();
    tft.fillScreen(TFT_BLACK);
    if (n == 0) {
        tft.drawString("no networks found", tft.width() / 2, tft.height() / 2);
    } else {
        tft.setTextDatum(TL_DATUM);
        tft.setCursor(0, 0);
        for (int i = 0; i < n; ++i) {
            sprintf(buff,
                    "[%d]:%s(%d)",
                    i + 1,
                    WiFi.SSID(i).c_str(),
                    WiFi.RSSI(i));
            Serial.println(buff);
            tft.println(buff);
        }
    }
    WiFi.mode(WIFI_OFF);
}



void factoryTest()
{
    scanI2Cdevice();
    delay(2000);

    tft.fillScreen(TFT_BLACK);
    tft.drawString("RTC Interrupt self test", 0, 0);

    int yy = 2019, mm = 5, dd = 15, h = 2, m = 10, s = 0;
    rtc.begin(Wire);
    rtc.setDateTime(yy, mm, dd, h, m, s);
    delay(500);
    RTC_Date dt = rtc.getDateTime();
    if (dt.year != yy || dt.month != mm || dt.day != dd || dt.hour != h || dt.minute != m) {
        tft.setTextColor(TFT_RED, TFT_BLACK);
        tft.fillScreen(TFT_BLACK);
        tft.drawString("Write DateTime FAIL", 0, 0);
    } else {
        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.fillScreen(TFT_BLACK);
        tft.drawString("Write DateTime PASS", 0, 0);
    }

    delay(2000);

    //! RTC Interrupt Test
    pinMode(RTC_INT_PIN, INPUT_PULLUP); //need change to rtc_pin
    attachInterrupt(RTC_INT_PIN, [] {
        rtcIrq = 1;
    }, FALLING);

    rtc.disableAlarm();

    rtc.setDateTime(2019, 4, 7, 9, 5, 57);

    rtc.setAlarmByMinutes(6);

    rtc.enableAlarm();

    for (;;) {
        snprintf(buff, sizeof(buff), "%s", rtc.formatDateTime());
        Serial.print("\t");
        Serial.println(buff);
        tft.fillScreen(TFT_BLACK);
        tft.drawString(buff, 0, 0);

        if (rtcIrq) {
            rtcIrq = 0;
            detachInterrupt(RTC_INT_PIN);
            rtc.resetAlarm();
            break;
        }
        delay(1000);
    }
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.fillScreen(TFT_BLACK);
    tft.drawString("RTC Interrupt PASS", 0, 0);
    delay(2000);

    wifi_scan();
    delay(2000);
}

void setupWiFi()
{
#ifdef ARDUINO_OTA_UPDATE
    WiFiManager wifiManager;
    //set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    wifiManager.setAPCallback(configModeCallback);
    wifiManager.setBreakAfterConfig(true);          // Without this saveConfigCallback does not get fired
    wifiManager.autoConnect("T-Wristband");
#endif
}

void setupOTA()
{
#ifdef ARDUINO_OTA_UPDATE
    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    ArduinoOTA.setHostname("T-Wristband");

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";

        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);
        otaStart = true;
        tft.fillScreen(TFT_BLACK);
        tft.drawString("Updating...", tft.width() / 2 - 20, 55 );
    })
    .onEnd([]() {
        Serial.println("\nEnd");
        delay(500);
    })
    .onProgress([](unsigned int progress, unsigned int total) {
        // Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        int percentage = (progress / (total / 100));
        tft.setTextDatum(TC_DATUM);
        tft.setTextPadding(tft.textWidth(" 888% "));
        tft.drawString(String(percentage) + "%", 145, 35);
        drawProgressBar(10, 30, 120, 15, percentage, TFT_WHITE, TFT_BLUE);
    })
    .onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");

        tft.fillScreen(TFT_BLACK);
        tft.drawString("Update Failed", tft.width() / 2 - 20, 55 );
        delay(3000);
        otaStart = false;
        initial = 1;
        targetTime = millis() + 1000;
        tft.fillScreen(TFT_BLACK);
        tft.setTextDatum(TL_DATUM);
        omm = 99;
    });

    ArduinoOTA.begin();
#endif
}


void setupADC()
{
    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize((adc_unit_t)ADC_UNIT_1, (adc_atten_t)ADC1_CHANNEL_6, (adc_bits_width_t)ADC_WIDTH_BIT_12, 1100, &adc_chars);
    //Check type of calibration value used to characterize ADC
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
        vref = adc_chars.vref;
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\n", adc_chars.coeff_a, adc_chars.coeff_b);
    } else {
        Serial.println("Default Vref: 1100mV");
    }
}

void setupRTC()
{
    rtc.begin(Wire);
    //Check if the RTC clock matches, if not, use compile time
    rtc.check();

    RTC_Date datetime = rtc.getDateTime();
    hh = datetime.hour;
    mm = datetime.minute;
    ss = datetime.second;
}

void setup(void)
{
    Serial.begin(115200);

    tft.init();
    tft.setRotation(1);
    tft.setSwapBytes(true);
    tft.pushImage(0, 0,  160, 80, ttgo);

    /*
    Reduce the brightness,
    can significantly reduce the current consumption
    when bright screen
    If you need to uncomment the comment
    */
    // ledcSetup(0, 1000, 8);
    // ledcAttachPin(TFT_BL, 0);
    // ledcWrite(0, 10);

    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
    Wire.setClock(400000);

#ifdef FACTORY_HW_TEST
    factoryTest();
#endif

    setupRTC();

#ifdef ENABLE_SENSOR

    // Turn on the IMU with configureIMU() (defined above)
    // check the return status of imu.begin() to make sure
    // it's connected.
    uint16_t status = setupIMU();
    if (status == false) {
        Serial.print("Failed to connect to IMU: 0x");
        Serial.println(status, HEX);
        while (1) ;
    }
#endif

    // After turning the IMU on, configure the interrupts:
    // configureLSM9DS1Interrupts();

    // Corrected ADC reference voltage
    setupADC();

    setupWiFi();

    setupOTA();

    setupBLE();

    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour

    targetTime = millis() + 1000;

    pinMode(TP_PIN_PIN, INPUT);
    //! Must be set to pull-up output mode in order to wake up in deep sleep mode
    pinMode(TP_PWR_PIN, PULLUP);
    digitalWrite(TP_PWR_PIN, HIGH);

    // Set the indicator to output
    pinMode(LED_PIN, OUTPUT);

    // Set the motor drive to output, if you have this module
    pinMode(MOTOR_PIN, OUTPUT);

    // Charging instructions, it is connected to IO32,
    // when it changes, you need to change the flag to know whether charging is in progress
    pinMode(CHARGE_PIN, INPUT_PULLUP);
    attachInterrupt(CHARGE_PIN, [] {
        charge_indication = true;
    }, CHANGE);

    // Check the charging instructions, if he is low, if it is true, then it is charging
    if (digitalRead(CHARGE_PIN) == LOW) {
        charge_indication = true;
    }

    // Lower MCU frequency can effectively reduce current consumption and heat
    setCpuFrequencyMhz(80);
}

String getVoltage()
{
    uint16_t v = analogRead(BATT_ADC_PIN);
    float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
    return String(battery_voltage) + "V";
}

void RTC_Show()
{
    if (charge_indication) {
        charge_indication = false;
        if (digitalRead(CHARGE_PIN) == LOW) {
            tft.pushImage(140, 55, 16, 16, charge);
        } else {
            tft.fillRect(140, 55, 16, 16, TFT_BLACK);
        }
    }

    if (targetTime < millis()) {
        RTC_Date datetime = rtc.getDateTime();
        hh = datetime.hour;
        mm = datetime.minute;
        ss = datetime.second;
        targetTime = millis() + 1000;
        if (ss == 0 || initial) {
            initial = 0;
            tft.setTextColor(TFT_GREEN, TFT_BLACK);
            tft.setCursor (8, 60);
            tft.print(__DATE__); // This uses the standard ADAFruit small font
        }

        tft.setTextColor(TFT_BLUE, TFT_BLACK);
        tft.drawCentreString(getVoltage(), 120, 60, 1); // Next size up font 2


        // Update digital time
        uint8_t xpos = 6;
        uint8_t ypos = 0;
        if (omm != mm) { // Only redraw every minute to minimise flicker
            // Uncomment ONE of the next 2 lines, using the ghost image demonstrates text overlay as time is drawn over it
            tft.setTextColor(0x39C4, TFT_BLACK);  // Leave a 7 segment ghost image, comment out next line!
            //tft.setTextColor(TFT_BLACK, TFT_BLACK); // Set font colour to black to wipe image
            // Font 7 is to show a pseudo 7 segment display.
            // Font 7 only contains characters [space] 0 1 2 3 4 5 6 7 8 9 0 : .
            tft.drawString("88:88", xpos, ypos, 7); // Overwrite the text to clear it
            tft.setTextColor(0xFBE0, TFT_BLACK); // Orange
            omm = mm;

            if (hh < 10) xpos += tft.drawChar('0', xpos, ypos, 7);
            xpos += tft.drawNumber(hh, xpos, ypos, 7);
            xcolon = xpos;
            xpos += tft.drawChar(':', xpos, ypos, 7);
            if (mm < 10) xpos += tft.drawChar('0', xpos, ypos, 7);
            tft.drawNumber(mm, xpos, ypos, 7);
        }

        if (ss % 2) { // Flash the colon
            tft.setTextColor(0x39C4, TFT_BLACK);
            xpos += tft.drawChar(':', xcolon, ypos, 7);
            tft.setTextColor(0xFBE0, TFT_BLACK);
        } else {
            tft.drawChar(':', xcolon, ypos, 7);
        }
    }
}

void getIMU()
{
#ifdef ENABLE_SENSOR
    // Update the sensor values whenever new data is available
    if ( imu.gyroAvailable() ) {
        // To read from the gyroscope,  first call the
        // readGyro() function. When it exits, it'll update the
        // gx, gy, and gz variables with the most current data.
        imu.readGyro();
    } else {
        Serial.println("Invalid gyroscope");
    }
    if ( imu.accelAvailable() ) {
        // To read from the accelerometer, first call the
        // readAccel() function. When it exits, it'll update the
        // ax, ay, and az variables with the most current data.
        imu.readAccel();
    } else {
        Serial.println("Invalid accelerometer");
    }
    if ( imu.magAvailable() ) {
        // To read from the magnetometer, first call the
        // readMag() function. When it exits, it'll update the
        // mx, my, and mz variables with the most current data.
        imu.readMag();
    } else {
        Serial.println("Invalid magnetometer");
    }
#endif
}

void IMU_Show()
{

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(TL_DATUM);
#ifdef ENABLE_SENSOR
    getIMU();

    snprintf(buff, sizeof(buff), "--  ACC  GYR   MAG");
    tft.drawString(buff, 0, 0);
    snprintf(buff, sizeof(buff), "x %.2f  %.2f  %.2f", imu.calcAccel(imu.ax), imu.calcGyro(imu.gx), imu.calcMag(imu.mx));
    tft.drawString(buff, 0, 16);
    snprintf(buff, sizeof(buff), "y %.2f  %.2f  %.2f", imu.calcAccel(imu.ay), imu.calcGyro(imu.gy), imu.calcMag(imu.my));
    tft.drawString(buff, 0, 32);
    snprintf(buff, sizeof(buff), "z %.2f  %.2f  %.2f", imu.calcAccel(imu.az), imu.calcGyro(imu.gz), imu.calcMag(imu.mz));
    tft.drawString(buff, 0, 48);
    delay(200);
#else
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_RED, TFT_BLACK);
    tft.println("Sensor is not enable");
    delay(200);
#endif

}


void BLE_Transmission()
{
#ifdef ENABLE_BLE_DATA_TRANSMISSION
    typedef struct {
        float ax;
        float ay;
        float az;
        float gx;
        float gy;
        float gz;
        float mx;
        float my;
        float mz;
    } imu_data_t;

    static uint32_t updataRate = 0;

    if (millis() - updataRate < 1000) {
        return;
    }
    getIMU();

    updataRate = millis();

    if (deviceConnected && enableNotify) {
        // Create a structure to send data
        imu_data_t data;
        data.ax = imu.calcAccel(imu.ax);
        data.ay = imu.calcAccel(imu.ay);
        data.az = imu.calcAccel(imu.az);
        data.gx = imu.calcGyro(imu.gx);
        data.gy = imu.calcGyro(imu.gy);
        data.gz = imu.calcGyro(imu.gz);
        data.mx = imu.calcMag(imu.mx);
        data.my = imu.calcMag(imu.my);
        data.mx = imu.calcMag(imu.mx);

        pSensorCharacteristic->setValue((uint8_t *)&data, sizeof(imu_data_t));

        pSensorCharacteristic->notify();

        uint8_t *ptr = (uint8_t *)&data;
        Serial.print("[");
        Serial.print(millis());
        Serial.print("]");

        for (int i = 0; i < sizeof(data); ++i) {
            Serial.print(ptr[i], HEX);
            Serial.print(" ");
        }
        Serial.println();
    }
#endif
}


uint8_t tempRegValue = 0;

void loop()
{
#ifdef ARDUINO_OTA_UPDATE
    ArduinoOTA.handle();
#endif

    //! If OTA starts, skip the following operation
    if (otaStart)
        return;

    if (digitalRead(TP_PIN_PIN) == HIGH) {
        if (!pressed) {
            initial = 1;
            targetTime = millis() + 1000;
            tft.fillScreen(TFT_BLACK);
            omm = 99;

            func_select = func_select + 1 > 3 ? 0 : func_select + 1;

            digitalWrite(MOTOR_PIN, HIGH);
            digitalWrite(LED_PIN, HIGH);
            delay(100);
            digitalWrite(LED_PIN, LOW);
            digitalWrite(MOTOR_PIN, LOW);

            pressed = true;
            pressedTime = millis();
            if (func_select == 2) {
                tft.setCursor(0, 30);
                tft.println("BLE Transmission,Now you can read it in your phone!");
            }
        } else {
#if defined(ARDUINO_OTA_UPDATE)
            if (millis() - pressedTime > 3000) {
                tft.fillScreen(TFT_BLACK);
                tft.drawString("Reset WiFi Setting",  20, tft.height() / 2 );
                delay(3000);
                wifiManager.resetSettings();
                wifiManager.erase(true);
                esp_restart();
            }
#endif
        }
    } else {
        pressed = false;
    }

    switch (func_select) {
    case 0:
        RTC_Show();
        break;
    case 1:
        IMU_Show();
        break;
    case 2:
        BLE_Transmission();
        break;
    case 3:

#if defined(ENABLE_SENSOR) && defined(USE_PROTECTED_MEMBERS)
        imu.settings.gyro.lowPowerEnable = true;
        imu.settings.gyro.enableX = false;
        imu.settings.gyro.enableY = false;
        imu.settings.gyro.enableZ = false;
        imu.settings.gyro.enabled = false;

        imu.settings.mag.enabled = false;
        imu.settings.mag.lowPowerEnable = true;
        imu.settings.mag.operatingMode = 11;

        imu.settings.accel.enabled = false;
        imu.settings.accel.enableX = false;
        imu.settings.accel.enableY = false;
        imu.settings.accel.enableZ = false;

        imu.settings.temp.enabled = false;

        /*

        You need to know using the following functions.
        These three methods are all set as protection members in the original SparkFun_LSM9DS1_Arduino_Library.
        If you need to use them, you need to put the three methods into public members.
        This is just for faster sensor testing. Low current consumption

        !!! In actual test, LSM9DS1 consumes about 1 mA !!!

        !!!In the actual test, the LSM9DS1 consumes about 1 mA of current.
            If you do not turn them off, it will consume about 4~6mA!!!

        **/

        imu.initMag();
        imu.initAccel();
        imu.initGyro();
#else
        imu.sleepGyro();
#endif

        tft.setTextColor(TFT_GREEN, TFT_BLACK);
        tft.setTextDatum(MC_DATUM);
        tft.drawString("Press again to wake up",  tft.width() / 2, tft.height() / 2 );
        Serial.println("Go to Sleep");
        delay(3000);
        tft.writecommand(ST7735_SLPIN);
        tft.writecommand(ST7735_DISPOFF);
        esp_sleep_enable_ext1_wakeup(GPIO_SEL_33, ESP_EXT1_WAKEUP_ANY_HIGH);
        delay(200);
        esp_deep_sleep_start();
        break;
    default:
        break;
    }
}



