/**
 * @file data.h
 * @brief Abstraction of some basic data manipulation
 *
 * This header file provides an abstraction of the basic data manipulation,
 * converting data from int to ASCII, and vice-versa
 *
 * @author Mohammed Abdelalim
 * @date 24/10/2020
 *
 */

#ifndef __data_H__
#define __data_H__

#include <math.h>

/**
 * @brief Converts given data from integer to ASCII string
 *
 * Given a pointer to a char dataset, this will set a provided
 * index into that dataset to the value provided.
 * Regarding the signed numbers, the function handles the base 10 signed numbers only.
 *
 * @param data The int number to be converted
 * @param ptr Pointer to data array
 * @param base Base to convert to
 *
 * @return length of the converted data.
 */
uint8 my_itoa(int32 data, uint8 * ptr, uint32 base);

/**
 * @brief Converts given data from ASCII string to integer
 *
 * Given a pointer to a char dataset, this will set a provided
 * index into that dataset to the value provided.
 * The function handles the base 10 signed numbers.
 *
 * @param ptr Pointer to the string to be converted
 * @param digits Number of digits in the character set
 * @param value Base to convert to
 *
 * @return the converted integer.
 */
int32 my_atoi(uint8 * ptr, uint8 digits, uint32 base);

/**
 * @brief Calculates the power of a nymber
 * 
 * @param number The base number
 * @param power The power factor
 *
 * @return the result.
 */
int32 powerFunction(int32 number, uint8 power);
#endif

