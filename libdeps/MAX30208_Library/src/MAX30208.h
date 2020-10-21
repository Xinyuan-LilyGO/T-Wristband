/////////////////////////////////////////////////////////////////
/*
MIT License

Copyright (c) 2020 lewis he

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

MAX30208.h - MAX30208_Library
Created by Lewis he on July 31, 2020.
github:https://github.com/lewisxhe/MAX30208_Library
*/
/////////////////////////////////////////////////////////////////
#pragma once

#include <Arduino.h>
#include <Wire.h>

/*SENSOR SLAVE ADDRESS*/
#define MAX30208_DEFAULT_ADDRESS         (0x51)
#define MAX30208_DEFAULT_PART_IDENTIFIER (0x30)
/*INTERRUPT AND STATUS*/
#define MAX30208_INTERRUPT_STATUS        (0x00)
#define MAX30208_INTERRUPT_ENABLE        (0x01)


#define MAX30208_INT_STATUS_AFULL        (0x80)
#define MAX30208_INT_STATUS_TEMP_LOW     (0x04)
#define MAX30208_INT_STATUS_TEMP_HIGH    (0x02)
#define MAX30208_INT_STATUS_TEMP_RDY     (0x01)


/*FIFO*/
#define MAX30208_FIFO_WRITE_POINTER      (0x04)
#define MAX30208_FIFO_READ_POINTER       (0x05)
#define MAX30208_FIFO_OVERFLOW_COUNTER   (0x06)
#define MAX30208_FIFO_DATA_COUNTER       (0x07)
#define MAX30208_FIFO_DATA               (0x08)
#define MAX30208_FIFO_CONFIGURATION1     (0x09)
#define MAX30208_FIFO_CONFIGURATION2     (0x0A)

/*SYSTEM*/
#define MAX30208_SYSTEM_REG              (0x0C)

/*TEMPERATURE*/
#define MAX30208_ALARM_HIGH_MSB          (0x10)
#define MAX30208_ALARM_HIGH_LSB          (0x11)
#define MAX30208_ALARM_LOW_MSB           (0x12)
#define MAX30208_ALARM_LOW_LSB           (0x13)
#define MAX30208_TEMP_SENSOR_SETUP       (0x14)

/*GPIO*/
#define MAX30208_GPIO_SETUP_REG          (0x20)
#define MAX30208_GPIO_CONTROL            (0x21)

/*IDENTIFIERS*/
#define MAX30208_PART_ID1                (0x31)
#define MAX30208_PART_ID2                (0x32)
#define MAX30208_PART_ID3                (0x33)
#define MAX30208_PART_ID4                (0x34)
#define MAX30208_PART_ID5                (0x35)
#define MAX30208_PART_ID6                (0x36)
#define MAX30208_PART_IDENTIFIER         (0xFF)
#define MAX30208_PART_IDENTIFIER_VAL     (0x30)

#ifdef DBG_PORT
#define DBG(fmt,...)    DBG_PORT.printf("[%s] " fmt "\n",__func__,##__VA_ARGS__)
#else
#define DBG(fmt,...)
#endif

class MAX30208_Class
{
public :
    bool begin(TwoWire &w, uint8_t address = MAX30208_DEFAULT_ADDRESS);

    // Configuration
    void softReset(void);

    //Interrupts
    uint8_t getINT(void);

    //Enable/disable individual interrupts
    void enableAFULL(void);

    void disableAFULL(void);

    void enableTEMPHIGH(void);

    void disableTEMPHIGH(void);

    void enableTEMPLOW(void);

    void disableTEMPLOW(void);

    void enableDATARDY(void);

    void disableDATARDY(void);

    void enableInterrup(void);

    //FIFO Configure
    void clearFIFO(void);

    void configureFifo(uint8_t mask);

    uint8_t fifoAvailable(void);

    uint8_t updateFifo(uint8_t *data, uint8_t len);

    void startConvert(void);

    // Detecting ID/Revision
    uint8_t getPartID(void);

    uint8_t readPartID(void);

    void setAlarmHigh(float high);

    void setAlarmLow(float low);

    //Read the FIFO Write Pointer
    uint8_t getWritePointer(void);

    //Read the FIFO Read Pointer
    uint8_t getReadPointer(void);

    uint8_t check(void);

    uint8_t available(void);

    void nextSample(void);

    float readTemperature(void);

    float readTemperatureF(void);
private:

    float getTemp(uint8_t msb, uint8_t lsb);

    //Given a register, read it, mask it, and then set the thing
    void bitMask(uint8_t reg, uint8_t mask, uint8_t thing);

    //
    // Low-level I2C Communication
    //
    uint8_t readRegister8( uint8_t reg);


    void writeRegister8(uint8_t reg, uint8_t value);


#define STORAGE_SIZE        32

    typedef struct Record {
        uint8_t buffer[STORAGE_SIZE];
        uint8_t head;
        uint8_t tail;
    } sense_struct; //This is our circular buffer of readings from the sensor

    sense_struct sense;

    float temperature[16];

    TwoWire *_i2cPort;      //The generic connection to user's chosen I2C hardware
    uint8_t _i2caddr;
};
