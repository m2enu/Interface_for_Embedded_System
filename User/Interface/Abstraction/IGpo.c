/**
 * @file    IGpo.c
 * @brief   Interface of abstraction layer for General Purpose Output peripheral
 */
#include "IGpo.h"
#include <stddef.h>

/**
 * @brief   Returns true if specified instance is invalid
 * @param   pThis   Instance of IGpo interface
 * @return  Validation result
 * @retval  true    Specified instance is invalid
 * @retval  false   Specified instance is valid
 */
static inline bool isInvalidInstance(const IGpo* const pThis);

void IGpoOn(const IGpo* pThis)
{
    if (isInvalidInstance(pThis) || (pThis->pMethod->On == NULL))
    {
        return;
    }
    (*pThis->pMethod->On)(pThis);
}

void IGpoOff(const IGpo* pThis)
{
    if (isInvalidInstance(pThis) || (pThis->pMethod->Off == NULL))
    {
        return;
    }
    (*pThis->pMethod->Off)(pThis);
}

void IGpoToggle(const IGpo* pThis)
{
    if (isInvalidInstance(pThis) || (pThis->pMethod->Toggle == NULL))
    {
        return;
    }
    (*pThis->pMethod->Toggle)(pThis);
}

bool IGpoIsOn(const IGpo* pThis)
{
    if (isInvalidInstance(pThis) || (pThis->pMethod->IsOn == NULL))
    {
        return false;
    }
    return (*pThis->pMethod->IsOn)(pThis);
}

bool IGpoIsOff(const IGpo* pThis)
{
    if (isInvalidInstance(pThis) || (pThis->pMethod->IsOff == NULL))
    {
        return false;
    }
    return (*pThis->pMethod->IsOff)(pThis);
}

static inline bool isInvalidInstance(const IGpo* const pThis)
{
    return (pThis == NULL) || (pThis->pMethod == NULL);
}

