# Interface for Embedded Systems

- This software supplies the OOP-like interface for Embedded Systems in C Language.
- The concrete class is implemented for NUCLEO-F446RE: keep in your mind they are only example.

# Features

- OOP-like interface for peripherals of Embedded Systems in C Language.
- The application code that uses this interface will have much less modification even if the CPU in your system is changed to another vendor (e.g. STM32 to PIC).


# Requirements

- C99 or above

# Author / License

- [m2enu](https://github.com/m2enu)
- This software is under [MIT License](https://github.com/m2enu/Interface_for_Embedded_System/blob/main/LICENSE)

# Installation

- Clone this repository and place source files in your source code directory.

# Usage

- Describe usage `IGpo` interface (General Purpose Output) as example.

## Interface definition

- `IGpo` interface is defined in `User/Interface/Abstraction/IGpo.h` as below.
- The prefix `I` means `Interface`.

```c
typedef struct IGpo
{
    const struct IGpoMethod*    pMethod;
    const GpoLevel              LevelOutputOn;
    const void*                 pExtraInfo;
} IGpo;
```

| Member        | Description                                       |
|---------------|---------------------------------------------------|
| pMethod       | A pointer to method table to control GPO pin.     |
| LevelOutputOn | Definition of pin level for `ON` state.           |
| pExtraInfo    | An extra configuration for each concrete class.   |

- `pExtraInfo` is defined as generic pointer (`void*` pointer) to store variant type: because each concrete class has different type of configurations.
- Note that you can specify `NULL` for `pExtraInfo` if no configuration is necessary for concrete class.

## Use the interface in user application

- An example is shown in `User/Handler/TimerHandler.c`.

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *p_htim)
{
    if (p_htim->Instance == TIM3)
    {
        IGpoToggle(pGpoLed);    /* Invoke GPO toggle via interface */
    }
}
```

- Each methods in `IGpo` interface must be invoked by `IGpoXxx` functions that is implemented in `IGpo.c`.
- These APIs are must be called by specifying a pointer to the instance that implements `IGpo` interface as 1st argument.
- These APIs will validate the instance then invoke each methods via `pMethod` pointer in `IGpo`.

## Concrete class implementation

- An example is shown in `User/Interface/Concrete/ARM_CM4F/CGpo.c` for ARM Cortex M4F.
- The prefix `C` means `Concrete`.

```c
static const IGpoExtraInfo exinfGreenLed = {GPIOA, GPIO_PIN_5};
const IGpo InstGpoGreenLed = {
    &GPO_METHOD,    /* Pointer to interface method table */
    GPO_LEVEL_HIGH, /* Output ON level */
    &exinfGreenLed  /* Extra configuration */
};
```

- In this example, `IGpoExtraInfo` structure is specified for `pExtraInfo` to store the register address and pin number for each GPO pin.

- `GPO_METHOD` is defined as below.

```c
static const IGpoMethod GPO_METHOD = {
    &CGpoOn,
    &CGpoOff,
    &CGpoToggle,
    &CGpoIsOn,
    &CGpoIsOff,
};
```

- Each functions are implemented to control GPO pins like below.

```c
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
```

## When CPU is changed

- You will have to modify `CGpo.c` to fit the new CPU, but will not have to modify your application code.
- For example, if `pLed` is defined as LED control pin in the application:

    * Following concrete code must be modified to fit the new CPU.

    ```c
    static const ExtraInfoForPic exinfGreenLed = {
        GPIO_GROUP_A    /* Just an example */
    };
    const IGpo GreenLed = {
        &GPO_METHOD,
        GPO_LEVEL_HIGH,
        &exinfGreenLed
    };
    static void CGpoOnForPic(const IGpo* pThis)
    {
        /* pThis may have CPU specific extra configuration */
        const ExtraInfoForPic* pExinf = (const ExtraInfoForPic*)pThis->pExtraInfo;
        /* Control output pin */
        GPIO_PIN_WRITE(pExinf->PinNumber, HIGH);
    }
    ```

    * But you will not have to modify your application: because application code is abstracted by `IGpo` interface.

    ```c
    /* The entity of `GreenLed` is implemented in concrete class so
     * application only need to care the interface.
     */
    extern const IGpo GreenLed;
    IGpoOn(&GreenLed);
    ```

# TODO

- [ ] Unit tests