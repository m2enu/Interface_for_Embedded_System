/**
 * @file    TimerHandler.c
 * @brief   Interrupt Handler for Timer peripheral
 */
#include "TimerHandler.h"
#include "stm32f4xx_hal.h"
#include "CGpo.h"
#include <stddef.h>

/** GPO interface for onboard LED */
static const IGpo* pGpoLed = NULL;

void TimerHandlerConstruct(const IGpo* const pGpo)
{
    pGpoLed = pGpo;
}

/**
 * @brief   Period elapsed callback in non blocking mode
 * @param   p_htim  Pointer to timer handle
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *p_htim)
{
    if (p_htim->Instance == TIM3)
    {
        IGpoToggle(pGpoLed);
    }
}

