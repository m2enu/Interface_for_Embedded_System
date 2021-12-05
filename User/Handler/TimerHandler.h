/**
 * @file    TimerHandler.h
 * @brief   Interrupt Handler for Timer peripheral
 */
#ifndef TIMER_HANDLER_H_INCLUDE
#define TIMER_HANDLER_H_INCLUDE

#include "IGpo.h"

/**
 * @brief   Constructor for Timer Handler
 * @param   pGpo    Pointer to the instance that has IGpo interface
 */
void TimerHandlerConstruct(const IGpo* const pGpo);

#endif
