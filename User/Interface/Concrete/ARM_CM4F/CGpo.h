/**
 * @file    CGpo.c
 * @brief   Concrete of General Purpose Output interface
 */
#ifndef C_GPO_H_INCLUDE
#define C_GPO_H_INCLUDE

#include "IGpo.h"

/**
 * @brief   Acquire instance of IGpo for Green LED
 * @return  Pointer to the instance
 */
const IGpo* CGpoAsBlueLamp(void);

#endif
