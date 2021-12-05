/**
 * @file    CGpo.c
 * @brief   Concrete of General Purpose Output interface
 */
#include "CGpo.h"
#include "stm32f4xx_hal.h"

/** Extra configuration for IGpo interface */
typedef struct IGpoExtraInfo
{
    GPIO_TypeDef*           pPeriReg;   /**< GPIO Peripheral register address */
    const uint16_t          Pin;        /**< GPIO Pin number */
} IGpoExtraInfo;

/**
 * @brief   Acquire GPO ON state of specified IGpo interface
 * @return  ON state enumeration
 * @retval  GPIO_PIN_SET    ON state is high
 * @retval  GPIO_PIN_RESET  ON state is low
 */
static inline GPIO_PinState ToOnState(const IGpo* pThis);

/**
 * @brief   Acquire GPO OFF state of specified IGpo interface
 * @return  ON state enumeration
 * @retval  GPIO_PIN_SET    OFF state is high
 * @retval  GPIO_PIN_RESET  OFF state is low
 */
static inline GPIO_PinState ToOffState(const IGpo* pThis);

/**
 * @brief   Interface to output GPO ON
 * @param   pThis   Pointer to IGpo interface
 */
static void CGpoOn(const IGpo* pThis);

/**
 * @brief   Interface to output GPO OFF
 * @param   pThis   Pointer to IGpo interface
 */
static void CGpoOff(const IGpo* pThis);

/**
 * @brief   Interface to toggle GPO
 * @param   pThis   Pointer to IGpo interface
 */
static void CGpoToggle(const IGpo* pThis);

/**
 * @brief   Interface to get whether the output status is ON
 * @param   pThis   Pointer to IGpo interface
 * @return  Output status is ON or not
 * @retval  true    Output status is ON
 * @retval  false   Output status is OFF
 */
static bool CGpoIsOn(const IGpo* pThis);

/**
 * @brief   Interface to get whether the output status is OFF
 * @param   pThis   Pointer to IGpo interface
 * @return  Output status is OFF or not
 * @retval  true    Output status is OFF
 * @retval  false   Output status is ON
 */
static bool CGpoIsOff(const IGpo* pThis);

/** Entity of IGpo interface method */
static const IGpoMethod GPO_METHOD = {
    &CGpoOn,
    &CGpoOff,
    &CGpoToggle,
    &CGpoIsOn,
    &CGpoIsOff,
};

const IGpo* CGpoAsBlueLamp(void)
{
    static const IGpoExtraInfo exinf = {GPIOA, GPIO_PIN_5};
    static const IGpo ret = {
        &GPO_METHOD,        /* Pointer to interface method table */
        GPO_LEVEL_HIGH,     /* Output ON level */
        &exinf              /* Extra configuration */
    };
    return &ret;
}

static inline GPIO_PinState ToOnState(const IGpo* pThis)
{
    if (pThis->LevelOutputOn == GPO_LEVEL_HIGH)
    {
        return GPIO_PIN_SET;
    }
    return GPIO_PIN_RESET;
}

static inline GPIO_PinState ToOffState(const IGpo* pThis)
{
    if (pThis->LevelOutputOn == GPO_LEVEL_HIGH)
    {
        return GPIO_PIN_RESET;
    }
    return GPIO_PIN_SET;
}

static void CGpoOn(const IGpo* pThis)
{
    if ((pThis == NULL) || (pThis->pExtraInfo == NULL))
    {
        return;
    }
    const IGpoExtraInfo* pExinf = (const IGpoExtraInfo*)pThis->pExtraInfo;
    GPIO_PinState state = ToOnState(pThis);
    HAL_GPIO_WritePin(pExinf->pPeriReg, pExinf->Pin, state);
}

static void CGpoOff(const IGpo* pThis)
{
    if ((pThis == NULL) || (pThis->pExtraInfo == NULL))
    {
        return;
    }
    const IGpoExtraInfo* pExinf = (const IGpoExtraInfo*)pThis->pExtraInfo;
    GPIO_PinState state = ToOffState(pThis);
    HAL_GPIO_WritePin(pExinf->pPeriReg, pExinf->Pin, state);
}

static void CGpoToggle(const IGpo* pThis)
{
    if ((pThis == NULL) || (pThis->pExtraInfo == NULL))
    {
        return;
    }
    const IGpoExtraInfo* pExinf = (const IGpoExtraInfo*)pThis->pExtraInfo;
    HAL_GPIO_TogglePin(pExinf->pPeriReg, pExinf->Pin);
}

static bool CGpoIsOn(const IGpo* pThis)
{
    if ((pThis == NULL) || (pThis->pExtraInfo == NULL))
    {
        return false;
    }
    const IGpoExtraInfo* pExinf = (const IGpoExtraInfo*)pThis->pExtraInfo;
    GPIO_PinState state = HAL_GPIO_ReadPin(pExinf->pPeriReg, pExinf->Pin);
    GPIO_PinState stateOn = ToOnState(pThis);
    return (state == stateOn);
}

static bool CGpoIsOff(const IGpo* pThis)
{
    if ((pThis == NULL) || (pThis->pExtraInfo == NULL))
    {
        return false;
    }
    const IGpoExtraInfo* pExinf = (const IGpoExtraInfo*)pThis->pExtraInfo;
    GPIO_PinState state = HAL_GPIO_ReadPin(pExinf->pPeriReg, pExinf->Pin);
    GPIO_PinState stateOff = ToOffState(pThis);
    return (state == stateOff);
}

