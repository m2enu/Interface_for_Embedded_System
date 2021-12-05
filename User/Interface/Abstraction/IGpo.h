/**
 * @file    IGpo.c
 * @brief   Interface of abstraction layer for General Purpose Output peripheral
 */
#ifndef I_GPO_H_INCLUDE
#define I_GPO_H_INCLUDE

#include <stdint.h>
#include <stdbool.h>

/** GPO level enumeration */
typedef enum GpoLevel
{
    GPO_LEVEL_LOW,      /**< Low level */
    GPO_LEVEL_HIGH,     /**< High level */
} GpoLevel;

/* Forward declaration */
struct IGpoMethod;

/** GPO interface */
typedef struct IGpo
{
    const struct IGpoMethod*    pMethod;        /**< Pointer to method for IGpo interface */
    const GpoLevel              LevelOutputOn;  /**< Output ON level */
    const void*                 pExtraInfo;     /**< Pointer to extra configuration for GPO */
} IGpo;

/** GPO interface method */
typedef struct IGpoMethod
{
    void    (*On)(const IGpo* pThis);       /**< Outputs ON level */
    void    (*Off)(const IGpo* pThis);      /**< Outputs OFF level */
    void    (*Toggle)(const IGpo* pThis);   /**< Toggles output level */
    bool    (*IsOn)(const IGpo* pThis);     /**< Returns true if output level is ON */
    bool    (*IsOff)(const IGpo* pThis);    /**< Returns true if output level is OFF */
} IGpoMethod;

/**
 * @brief   Interface to output GPO ON
 * @param   pThis   Pointer to IGpo interface
 */
void IGpoOn(const IGpo* pThis);

/**
 * @brief   Interface to output GPO OFF
 * @param   pThis   Pointer to IGpo interface
 */
void IGpoOff(const IGpo* pThis);

/**
 * @brief   Interface to toggle GPO
 * @param   pThis   Pointer to IGpo interface
 */
void IGpoToggle(const IGpo* pThis);

/**
 * @brief   Interface to get whether the output status is ON
 * @param   pThis   Pointer to IGpo interface
 * @return  Output status is ON or not
 * @retval  true    Output status is ON
 * @retval  false   Output status is NOT ON
 */
bool IGpoIsOn(const IGpo* pThis);

/**
 * @brief   Interface to get whether the output status is OFF
 * @param   pThis   Pointer to IGpo interface
 * @return  Output status is OFF or not
 * @retval  true    Output status is OFF
 * @retval  false   Output status is NOT OFF
 */
bool IGpoIsOff(const IGpo* pThis);

#endif
