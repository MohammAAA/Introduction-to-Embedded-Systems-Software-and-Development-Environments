/******************************************************************************
 * Copyright (C) 2017 by Alex Fosdick - University of Colorado
 *
 * Redistribution, modification or use of this software in source or binary
 * forms is permitted as long as the files maintain this copyright. Users are 
 * permitted to modify this and use it to learn about the field of embedded
 * software. Alex Fosdick and the University of Colorado are not liable for any
 * misuse of this material. 
 *
 *****************************************************************************/
/**
 * @file memory.h
 * @brief Abstraction of memory read, write, and manipulation operations
 *
 * This header file provides an abstraction of reading,
 * writing, and memory manipulation via function calls. 
 *
 * @author Alex Fosdick
 * @date 1/4/2017
 * @edited 24/10/2020 by Mohammed Abdelalim
 *
 */
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stddef.h>
#include <stdlib.h>

typedef unsigned char uint8;
typedef char int8;
typedef long int int32;
typedef int int16;
typedef unsigned int uint32;

/**
 * @brief Sets a value of a data array 
 *
 * Given a pointer to a char dataset, this will set a provided
 * index into that dataset to the value provided.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 * @param value Value to write the location
 *
 * @return void.
 */
void set_value(char * ptr, unsigned int index, char value);

/**
 * @brief Clear a value of a data array 
 *
 * Given a pointer to a char dataset, this will clear a provided
 * index into that dataset to the value zero.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return void.
 */
void clear_value(char * ptr, unsigned int index);

/**
 * @brief Returns a value of a data array 
 *
 * Given a pointer to a char dataset, this will read the provided
 * index into that dataset and return the value.
 *
 * @param ptr Pointer to data array
 * @param index Index into pointer array to set value
 *
 * @return Value to be read.
 */
char get_value(char * ptr, unsigned int index);

/**
 * @brief Sets data array elements to a value
 *
 * Given a pointer to a char dataset, this will set a number of elements
 * from a provided data array to the given value. The length is determined
 * by the provided size parameter.
 *
 * @param ptr Pointer to data array
 * @param value value to write in the locaiton
 * @param size Number of elements to set to value
 *
 * @return void.
 */
void set_all(char * ptr, char value, unsigned int size);

/**
 * @brief Clears elements in a data array
 *
 * Given a pointer to a char dataset, this will set a clear a number
 * of elements given the size provided. Clear means to set to zero. 
 *
 * @param ptr Pointer to data array
 * @param size Number of elements to set to zero
 *
 * @return void.
 */
void clear_all(char * ptr, unsigned int size);

///////////////////////////////// Added Code //////////////////////////////////
/**
 * @brief Moves data from source location with specific length to destination 
 *
 * This function takes two byte pointers (one source and one destination)
 * and a length of bytes to move from the source location to the destination.
 * The behavior should handle overlap of source and destination.
 * Copy should occur with no data corruption
 *
 * @param src Pointer to the source location
 * @param dst Pointer to the destination
 * @param length The data length in bytes
 *
 * @return Pointer to the destination.
 */
uint8 * my_memmove(uint8 * src, uint8 * dst, uint8 length);

/**
 * @brief Copies data from source location with specific length to destination 
 *
 * This function takes two byte pointers (one source and one destination)
 * and a length of bytes to copy from the source location to the destination.
 * The behavior is undefined if there is overlap of source and destination,
 * copy should still occur, but will likely corrupt your data.
 *
 * @param src Pointer to the source location
 * @param dst Pointer to the destination
 * @param length The data length in bytes
 *
 * @return Pointer to the destination.
 */
uint8 * my_memcopy(uint8 * src, uint8 * dst, uint8 length);

/**
 * @brief Sets a certain value to certain locations starting from a source address 
 *
 * This function should take a pointer to a source memory location, a length in bytes
 * and set all locations of that memory to a given value.
 *
 * @param src Pointer to the source location
 * @param length The data length in bytes
 * @param value The value to be set
 *
 * @return Pointer to the source.
 */
uint8 * my_memset(uint8 * src, uint8 length, uint8 value);

/**
 * @brief clears certain locations starting from a source address 
 *
 * This function should take a pointer to a source memory location, a length in bytes
 * and zero out all of this memory
 *
 * @param src Pointer to the source location
 * @param length The data length in bytes
 *
 * @return Pointer to the source.
 */
uint8 * my_memzero(uint8 * src, uint8 length);

/**
 * @brief reverses the order of data stored in specific memory locations 
 *
 * This function should take a pointer to a source memory location, a length in bytes
 * and reverse the order of all of these bytes.
 *
 * @param src Pointer to the source location
 * @param length The data length in bytes
 *
 * @return Pointer to the source.
 */
uint8 * my_reverse(uint8 * src, uint8 length);

/**
 * @brief allocates dynamic memory 
 *
 * This function should take number of words to allocate in dynamic memory
 *
 * @param length Number of words (consider the word = 1 byte)
 *
 * @return Pointer to the source when successful allocation, or a Null pointer if not successful.
 */
int32 * reserve_words(uint8 length);

/**
 * @brief frees dynamic memory
 *
 * This function should take pointer to the source memory and free this allocated memory
 *
 * @param src Pointer to the source location
 *
 * @return void
 */
void free_words(int32 * src);

#endif /* __MEMORY_H__ */
