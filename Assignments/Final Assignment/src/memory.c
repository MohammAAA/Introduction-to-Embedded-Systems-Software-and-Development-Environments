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
 * @file memory.c
 * @brief Abstraction of memory read, write, and manipulation operations
 *
 * This implementation file provides an abstraction of reading and
 * writing to memory via function calls.
 * 
 * @author Alex Fosdick
 * @date 1/4/2017
 * @edited 24/10/2020 by Mohammed Abdelalim
 *
 */
#include "../include/common/memory.h"
#include <stddef.h>

/***********************************************************
 Function Definitions
***********************************************************/
void set_value(char * ptr, unsigned int index, char value){
  ptr[index] = value;
}

void clear_value(char * ptr, unsigned int index){
  set_value(ptr, index, 0);
}

char get_value(char * ptr, unsigned int index){
  return ptr[index];
}

void set_all(char * ptr, char value, unsigned int size){
  unsigned int i;
  for(i = 0; i < size; i++) {
    set_value(ptr, i, value);
  }
}

void clear_all(char * ptr, unsigned int size){
  set_all(ptr, 0, size);
}

uint8 * my_memmove(uint8 * src, uint8 * dst, uint8 length){
	
	int16 datatoMove[length];
	// Copy to buffer
	my_memcopy(src, datatoMove, length);
	
	// Copy from buffer to destination
	my_memcopy(datatoMove, dst, length);
   
    return dst;
}

uint8 * my_memcopy(uint8 * src, uint8 * dst, uint8 length){
    for (int dataCount=0; dataCount<length; dataCount++){
        *(dst+dataCount) = *(src+dataCount);
    }    
    return dst;
}

uint8 * my_memset(uint8 * src, uint8 length, uint8 value){
    for (int cellCount=0; cellCount<length; cellCount++){
        *(src+cellCount) = value;
    }
    return src;
}

uint8 * my_memzero(uint8 * src, uint8 length){
     for (int cellCount=0; cellCount<length; cellCount++){
        *(src+cellCount) = 0;
    }
    return src;
}

uint8 * my_reverse(uint8 * src, uint8 length){
    uint8 numberOfSwapOperations = length/2;
    uint8 temp=0;
    for (int counter=0; counter<numberOfSwapOperations; counter++){
        temp = *(src + counter);
        *(src+counter) = *(src+length-1-counter);
        *(src+length-1-counter) = temp;
    }
    return src;
}

int32 * reserve_words(uint8 length){
    if (((int32 *) malloc(length)) != NULL){
        return ((int32 *) malloc(length));
    }
    else return NULL;
}

void free_words(int32 * src){
    free((void *)src);
}

