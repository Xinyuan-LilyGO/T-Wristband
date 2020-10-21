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

MAX30208.cpp - MAX30208_Library
Created by Lewis he on July 31, 2020.
github:https://github.com/lewisxhe/MAX30208_Library
*/
/////////////////////////////////////////////////////////////////

#include "MAX30208.h"

#define MAX30208_INT_A_FULL_MASK                    (~0x08)
#define MAX30208_INT_TEMP_LOW_MASK                  (~0x04)
#define MAX30208_INT_TEMP_HIGH_MASK                 (~0x02)
#define MAX30208_INT_TEMP_RDY_MASK                  (~0x01)

#define MAX30208_INT_A_FULL_ENABLE                  (0x80)
#define MAX30208_INT_TEMP_LOW_ENABLE                (0x04)
#define MAX30208_INT_TEMP_HIGH_ENABLE               (0x02)
#define MAX30208_INT_TEMP_RDY_ENABLE                (0x01)

#define MAX30208_INT_DISABLE                        (0x00)


#define GPIO0_MODE_SETUP_MASK                       (~0x03)
#define GPIO0_INPUT_MODE_EANBLE                     (0x00)
#define GPIO0_OUTPUT_MODE_EANBLE                    (0x01)
#define GPIO0_INPUT_PULLDOWM_EANBLE                 (0x02)
#define GPIO0_INT_MODE_EANBLE                       (0x03)


bool MAX30208_Class::begin(TwoWire &w, uint8_t address)
{
    _i2cPort = &w;
    _i2caddr = address;
    _i2cPort->begin();

    // Step 1: Initial Communication and Verification
    // Check that a MAX30208 is connected
    if (readPartID() != MAX30208_PART_IDENTIFIER_VAL) {
        // Error -- Part ID read from MAX30208 does not match expected part ID.
        // This may mean there is a physical connectivity problem (broken wire, unpowered, etc).
        return false;
    }

    // getPartID(); //It's useless

    // softReset();

    getINT();

    clearFIFO();

    memset(&sense, 0, sizeof(sense));

    return true;
}


// Configuration
void MAX30208_Class::softReset(void)
{
    writeRegister8(MAX30208_SYSTEM_REG, 1);
    delay(50);
}


//Interrupts
uint8_t MAX30208_Class::getINT(void)
{
    uint8_t val;
    val = readRegister8(MAX30208_INTERRUPT_STATUS);
    DBG("0x%x", val);
    return val;
}

void MAX30208_Class::enableAFULL(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_A_FULL_MASK, MAX30208_INT_A_FULL_ENABLE);
}

void MAX30208_Class::disableAFULL(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_A_FULL_MASK, MAX30208_INT_DISABLE);
}

void MAX30208_Class::enableTEMPHIGH(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_TEMP_HIGH_MASK, MAX30208_INT_TEMP_HIGH_ENABLE);
}

void MAX30208_Class::disableTEMPHIGH(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_TEMP_HIGH_MASK, MAX30208_INT_DISABLE);
}

void MAX30208_Class::enableTEMPLOW(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_TEMP_LOW_MASK, MAX30208_INT_TEMP_LOW_ENABLE);
}

void MAX30208_Class::disableTEMPLOW(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_TEMP_LOW_MASK, MAX30208_INT_DISABLE);
}

void MAX30208_Class::enableDATARDY(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_TEMP_RDY_MASK, MAX30208_INT_TEMP_RDY_ENABLE);
}

void MAX30208_Class::disableDATARDY(void)
{
    bitMask(MAX30208_INTERRUPT_ENABLE, MAX30208_INT_TEMP_RDY_MASK, MAX30208_INT_DISABLE);
}

void MAX30208_Class::enableInterrup()
{
    bitMask(MAX30208_GPIO_SETUP_REG, GPIO0_MODE_SETUP_MASK, GPIO0_INT_MODE_EANBLE);
}

void MAX30208_Class::clearFIFO(void)
{
    // writeRegister8(MAX30208_FIFO_READ_POINTER, 0);
}

void MAX30208_Class::configureFifo(uint8_t mask)
{
    bitMask(MAX30208_FIFO_CONFIGURATION2, mask, 1);
}

uint8_t MAX30208_Class::fifoAvailable(void)
{
    if (readRegister8(MAX30208_FIFO_OVERFLOW_COUNTER) != 0) {
        return 32;
    }
    return readRegister8(MAX30208_FIFO_DATA_COUNTER);
}

uint8_t MAX30208_Class::updateFifo(uint8_t *data, uint8_t len)
{
    // DBG(" ");
    _i2cPort->beginTransmission(_i2caddr);
    _i2cPort->write(MAX30208_FIFO_DATA);
    _i2cPort->endTransmission(false);
    _i2cPort->requestFrom((uint8_t)_i2caddr, len); // Request 1 byte
    uint8_t i = 0;
    while (_i2cPort->available()) {
        data[i++] = _i2cPort->read();
    }
    return i;
}

void MAX30208_Class::startConvert(void)
{
    writeRegister8(MAX30208_TEMP_SENSOR_SETUP, 0x01);
}

// Detecting ID/Revision
uint8_t MAX30208_Class::getPartID(void)
{
    // It's useless
    // uint8_t partID[6];
    // partID[0] = readRegister8(MAX30208_PART_ID1);
    // partID[1] = readRegister8(MAX30208_PART_ID2);
    // partID[2] = readRegister8(MAX30208_PART_ID3);
    // partID[3] = readRegister8(MAX30208_PART_ID4);
    // partID[4] = readRegister8(MAX30208_PART_ID5);
    // partID[5] = readRegister8(MAX30208_PART_ID6);
    // for (int i = 0; i < 6; i++) {
    //     DBG("%x:", partID[i]);
    // }
    return 0;
}

uint8_t MAX30208_Class::readPartID(void)
{
    return readRegister8(MAX30208_PART_IDENTIFIER);
}

/*
    设备执行温度转换后，将温度值与存储在2字节警报高和2字节警报低寄存器中的用户定义的两个补码警报触发值进行比较（见图2）。
    AH的默认值为0x7FFF（+ 163.835°C），AL的默认值为0x8000（-163.840°C）。
        最高位为 正负度数
        0x7FFF(32767) / 163.835 = 200;
    MSB指示该值是正数还是负数。对于正数，MSB为0；对于负数，MSB为1。
    * */
void MAX30208_Class::setAlarmHigh(float high)
{
    high *= 200;
    uint8_t msb = (uint32_t)high >> 8;
    uint8_t lsb = (uint32_t)high & 0xFF;
    writeRegister8(MAX30208_ALARM_HIGH_MSB, msb);
    writeRegister8(MAX30208_ALARM_HIGH_LSB, lsb);
}

void MAX30208_Class::setAlarmLow(float low)
{
    low *= 200;
    uint8_t msb = (uint32_t)low >> 8 ;
    uint8_t lsb = (uint32_t)low & 0xFF;
    writeRegister8(MAX30208_ALARM_LOW_MSB, msb);
    writeRegister8(MAX30208_ALARM_LOW_LSB, lsb);
}

//Read the FIFO Write Pointer
uint8_t MAX30208_Class::getWritePointer(void)
{
    return readRegister8(MAX30208_FIFO_WRITE_POINTER) & 0x1F;
}

//Read the FIFO Read Pointer
uint8_t MAX30208_Class::getReadPointer(void)
{
    return readRegister8(MAX30208_FIFO_READ_POINTER) & 0x1F;
}

uint8_t MAX30208_Class::check(void)
{
    uint8_t len = fifoAvailable();
    if ((len % 2) != 0) {
        len -= 1;
    }
    DBG("fifoAvailable:%u tempAvailable:%u", len, len / 2);

    updateFifo(sense.buffer, len);
    for (uint8_t i = 0; i < len / 2; i += 2) {
        sense.head++;       //Advance the head of the storage struct
        sense.head %= 16;   //Wrap condition
        temperature[sense.head] = getTemp(sense.buffer[i], sense.buffer[i + 1]);
        // DBG("[%u] head:%u temperature:%.2f", i, sense.head, temperature[sense.head]);
    }
    return len / 2;
}




uint8_t MAX30208_Class::available(void)
{
    int8_t numberOfSamples = sense.head - sense.tail;
    if (numberOfSamples < 0) {
        numberOfSamples += 16;
    }
    return (numberOfSamples);
}

//Advance the tail
void MAX30208_Class::nextSample(void)
{
    if (available()) { //Only advance the tail if new data is available
        sense.tail++;
        sense.tail %= 16; //Wrap condition
    }
}

float MAX30208_Class::readTemperature(void)
{
    return temperature[sense.head];
}

float MAX30208_Class::readTemperatureF(void)
{
    float temp = readTemperature();
    if (temp == 0) {
        return 0;
    }
    return (temp * 1.8) + 32.0;
}

float MAX30208_Class::getTemp(uint8_t msb, uint8_t lsb)
{
    if (msb & 0x80) {
        return  0 - (((msb << 8) | (lsb)) * 0.005);
    }
    return ((msb << 8) | (lsb)) * 0.005;
}

//Given a register, read it, mask it, and then set the thing
void MAX30208_Class::bitMask(uint8_t reg, uint8_t mask, uint8_t thing)
{
    // Grab current register context
    uint8_t originalContents = readRegister8( reg);

    // Zero-out the portions of the register we're interested in
    originalContents = originalContents & mask;

    // Change contents
    writeRegister8( reg, originalContents | thing);
}

//
// Low-level I2C Communication
//
uint8_t MAX30208_Class::readRegister8( uint8_t reg)
{
    _i2cPort->beginTransmission(_i2caddr);
    _i2cPort->write(reg);
    _i2cPort->endTransmission(false);

    _i2cPort->requestFrom((uint8_t)_i2caddr, (uint8_t)1); // Request 1 byte
    if (_i2cPort->available()) {
        return (_i2cPort->read());
    }
    return (0); //Fail
}

void MAX30208_Class::writeRegister8(uint8_t reg, uint8_t value)
{
    _i2cPort->beginTransmission(_i2caddr);
    _i2cPort->write(reg);
    _i2cPort->write(value);
    _i2cPort->endTransmission();
}