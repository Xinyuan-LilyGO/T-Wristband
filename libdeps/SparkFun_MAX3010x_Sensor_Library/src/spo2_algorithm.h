/** \file algorithm.h ******************************************************
*
* Project: MAXREFDES117#
* Filename: algorithm.h
* Description: This module is the heart rate/SpO2 calculation algorithm header file
*
* Revision History:
*\n 1-18-2016 Rev 01.00 SK Initial release.
*\n
*
* --------------------------------------------------------------------
*
* This code follows the following naming conventions:
*
*\n char              ch_pmod_value
*\n char (array)      s_pmod_s_string[16]
*\n float             f_pmod_value
*\n int32_t           n_pmod_value
*\n int32_t (array)   an_pmod_value[16]
*\n int16_t           w_pmod_value
*\n int16_t (array)   aw_pmod_value[16]
*\n uint16_t          uw_pmod_value
*\n uint16_t (array)  auw_pmod_value[16]
*\n uint8_t           uch_pmod_value
*\n uint8_t (array)   auch_pmod_buffer[16]
*\n uint32_t          un_pmod_value
*\n int32_t *         pn_pmod_value
*
* ------------------------------------------------------------------------- */
/*******************************************************************************
* Copyright (C) 2015 Maxim Integrated Products, Inc., All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included
* in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
* OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
* Except as contained in this notice, the name of Maxim Integrated
* Products, Inc. shall not be used except as stated in the Maxim Integrated
* Products, Inc. Branding Policy.
*
* The mere transfer of this software does not imply any licenses
* of trade secrets, proprietary technology, copyrights, patents,
* trademarks, maskwork rights, or any other form of intellectual
* property whatsoever. Maxim Integrated Products, Inc. retains all
* ownership rights.
*******************************************************************************
*/
#ifndef SPO2_ALGORITHM_H_
#define SPO2_ALGORITHM_H_

#include <Arduino.h>

#define FreqS 25    //sampling frequency
#define BUFFER_SIZE (FreqS * 4) 
#define MA4_SIZE 4 // DONOT CHANGE
//#define min(x,y) ((x) < (y) ? (x) : (y)) //Defined in Arduino.h

//uch_spo2_table is approximated as  -45.060*ratioAverage* ratioAverage + 30.354 *ratioAverage + 94.845 ;
const uint8_t uch_spo2_table[184]={ 95, 95, 95, 96, 96, 96, 97, 97, 97, 97, 97, 98, 98, 98, 98, 98, 99, 99, 99, 99, 
              99, 99, 99, 99, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
              100, 100, 100, 100, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 98, 98, 98, 97, 97, 
              97, 97, 96, 96, 96, 96, 95, 95, 95, 94, 94, 94, 93, 93, 93, 92, 92, 92, 91, 91, 
              90, 90, 89, 89, 89, 88, 88, 87, 87, 86, 86, 85, 85, 84, 84, 83, 82, 82, 81, 81, 
              80, 80, 79, 78, 78, 77, 76, 76, 75, 74, 74, 73, 72, 72, 71, 70, 69, 69, 68, 67, 
              66, 66, 65, 64, 63, 62, 62, 61, 60, 59, 58, 57, 56, 56, 55, 54, 53, 52, 51, 50, 
              49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 31, 30, 29, 
              28, 27, 26, 25, 23, 22, 21, 20, 19, 17, 16, 15, 14, 12, 11, 10, 9, 7, 6, 5, 
              3, 2, 1 } ;
static  int32_t an_x[ BUFFER_SIZE]; //ir
static  int32_t an_y[ BUFFER_SIZE]; //red


#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
//Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
//To solve this problem, 16-bit MSB of the sampled data will be truncated.  Samples become 16-bit data.
void maxim_heart_rate_and_oxygen_saturation(uint16_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint16_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid);
#else
void maxim_heart_rate_and_oxygen_saturation(uint32_t *pun_ir_buffer, int32_t n_ir_buffer_length, uint32_t *pun_red_buffer, int32_t *pn_spo2, int8_t *pch_spo2_valid, int32_t *pn_heart_rate, int8_t *pch_hr_valid);
#endif

void maxim_find_peaks(int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height, int32_t n_min_distance, int32_t n_max_num);
void maxim_peaks_above_min_height(int32_t *pn_locs, int32_t *n_npks,  int32_t  *pn_x, int32_t n_size, int32_t n_min_height);
void maxim_remove_close_peaks(int32_t *pn_locs, int32_t *pn_npks, int32_t *pn_x, int32_t n_min_distance);
void maxim_sort_ascend(int32_t  *pn_x, int32_t n_size);
void maxim_sort_indices_descend(int32_t  *pn_x, int32_t *pn_indx, int32_t n_size);

#endif /* ALGORITHM_H_ */

