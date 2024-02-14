/*******************************************************************************
 * File  : type.h       
 * Author: phamtien758      
 * Brief : Definition of type used for driver
 ******************************************************************************/

#ifndef TYPE_H
#define TYPE_H

/* Typedef of data types in ARM GCC compiler */
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;

#define _R    volatile const
#define _W    volatile
#define _RW   volatile

#define ENABLE  1
#define DISABLE 0

#define TRUE    1
#define FALSE   0

#define SET    1
#define RESET  0

#define NULL    ((void*)0)

/*
 * @brief Return state of functions
 */
typedef enum
{
    RET_NOT_OK = 0,    /* Function has performed unsuccessfully */
    RET_OK     = 1     /* Function has performed successfully */
}ReturnType; 

#endif /* TYPE_H */
