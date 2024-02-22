/*******************************************************************************
 * File  : gpio.c       
 * Author: phamtien758      
 * Brief : The Gpio source file
 ******************************************************************************/

/*** INCLUDE ************************************/

#include "gpio.h"

/*** DEFINE *******************************************************************/

/*** VARIABLES ****************************************************************/

/*
 * @brief Point to user's handler
 */
static GpioFuncHandler p_GpioHandler = NULL;

/*** PROTOTYPE ****************************************************************/

static void Gpio_ExtInit(Gpio_PinNum PinNum_e, Gpio_ExtEdge ExtEdge_e, \
                         GpioFuncHandler p_Handler);

/*** STATIC FUNCTION **********************************************************/

/**
  * @brief   Initialize external interrupt for gpio pin
  * @param   PinNum_e    Gpio pin number. It is Gpio_PinNum enum type.
  * @param   ExtEdge_e   Trigger edge for external interrupt.
  * @param   p_Handler   Function pointer pointer to user's handler function
  * @retval  None
  */
static void Gpio_ExtInit(Gpio_PinNum PinNum_e, Gpio_ExtEdge ExtEdge_e, \
                         GpioFuncHandler p_Handler)
{
    Exti_Line Line_e = (Exti_Line)PinNum_e;
    Exti_Edge Edge_e = (Exti_Edge)ExtEdge_e;

    /* Enable Exti line corresponds to pin.
       Function handler initialize */
    Exti_IntEnable(Line_e, Gpio_ExtHandler);
    p_GpioHandler = p_Handler;

    /* Choose Edge detected */
    Exti_EdgeCfg(Line_e, Edge_e);
}

/*** FUNCTIONS ****************************************************************/

/**
  * @brief   Gpio pin initialization
  * @note    None
  * @param   p_Gpio_st    Pointer to GPIOx address.
  * @param   p_GpioCfg_st Pointer to a structure that contains the configuration
  *                       information for the specified pin.
  * @retval  RET_OK - Pin has initialized success
  *          RET_NOT_OK - Pin has initialized fail
  */ 
ReturnType Gpio_Init(Gpio_RegDef *p_Gpio_st, const Gpio_Config *p_GpioCfg_st)
{
    uint32 TempValue_u32;
    ReturnType RetValue = RET_OK;

    if(FALSE == Gpio_IsLocked(p_Gpio_st, p_GpioCfg_st->Gpio_PinNum_e))
    {
        /* Pin alternate function configuration */
        /* Because each pin consume 4 bits in AFR register,
           so from Pin number 8 onward, 
           configuration value will be write to AFRH */
        if(GPIO_PINNUM_8 <= p_GpioCfg_st->Gpio_PinNum_e)
        {
            TempValue_u32 = p_GpioCfg_st->Gpio_PinAltFun_e << \
                            GPIO_AFRH_BIT_POS(p_GpioCfg_st->Gpio_PinNum_e);
            /* Because number of bit is larger than 1,
                so need to clear before write */
            p_Gpio_st->AFRH &= ~GPIO_AFRH_BIT_MASK(p_GpioCfg_st->Gpio_PinNum_e);
            p_Gpio_st->AFRH |= TempValue_u32;
        }
        else
        {
            TempValue_u32 = p_GpioCfg_st->Gpio_PinAltFun_e << \
                            GPIO_AFRL_BIT_POS(p_GpioCfg_st->Gpio_PinNum_e);
            /* Because number of bit is larger than 1,
                so need to clear before write */
            p_Gpio_st->AFRL &= ~GPIO_AFRL_BIT_MASK(p_GpioCfg_st->Gpio_PinNum_e);
            p_Gpio_st->AFRL |= TempValue_u32;
        }

        /* Pin mode Configuration */
        TempValue_u32 = p_GpioCfg_st->Gpio_PinMode_e << \
                        GPIO_MODER_BIT_POS(p_GpioCfg_st->Gpio_PinNum_e);
        /* Because number of bit is larger than 1,
           so need to clear before write */
        p_Gpio_st->MODER &= ~GPIO_MODER_BIT_MASK(p_GpioCfg_st->Gpio_PinNum_e);
        p_Gpio_st->MODER |= TempValue_u32;

        /* Pin output type Configuration */
        TempValue_u32 = p_GpioCfg_st->Gpio_PinOutType_e << \
                        GPIO_MODER_BIT_POS(p_GpioCfg_st->Gpio_PinNum_e);
        p_Gpio_st->OTYPER |= TempValue_u32;

        /* Pin output speed configuration */
        TempValue_u32 = p_GpioCfg_st->Gpio_PinSpeed_e << \
                        GPIO_MODER_BIT_POS(p_GpioCfg_st->Gpio_PinNum_e);
        /* Because number of bit is larger than 1,
           so need to clear before write */
        p_Gpio_st->OSPEEDR &= ~GPIO_MODER_BIT_MASK(p_GpioCfg_st->Gpio_PinNum_e);
        p_Gpio_st->OSPEEDR |= TempValue_u32;

        /* Pin pull-up pull-down configuration */
        TempValue_u32 = p_GpioCfg_st->Gpio_PinPuPd_e << \
                        GPIO_MODER_BIT_POS(p_GpioCfg_st->Gpio_PinNum_e);
        /* Because number of bit is larger than 1, 
           so need to clear before write */
        p_Gpio_st->PUPDR &= ~GPIO_MODER_BIT_MASK(p_GpioCfg_st->Gpio_PinNum_e);
        p_Gpio_st->PUPDR |= TempValue_u32;

        /* External interrupt configuration */
        if(ENABLE == (p_GpioCfg_st->Gpio_ExIntEnable_u8))
        {
            if(GPIO_MODE_IN == p_GpioCfg_st->Gpio_PinMode_e)
            {
                Gpio_ExtInit(p_GpioCfg_st->Gpio_PinNum_e, \
                             p_GpioCfg_st->Gpio_ExIntEdge_e, \
                             p_GpioCfg_st->Gpio_ExIntCallback);
            }
            else
            {
                RetValue = RET_NOT_OK;
            }
        }
        else
        {
            /* do nothing */
        }
    }
    else
    {
        /* Gpio pin locked */
        RetValue = RET_NOT_OK;
    }

    return RetValue;
}

/**
  * @brief   Read data from pin in input mode
  * @note    None
  * @param   p_Gpio_st   Pointer to GPIOx address.
  * @param   PinNum_e    Gpio pin number. It is Gpio_PinNum enum type.
  *                      This parameter can be one of following values:
  *         @arg GPIO_PINNUM_0
  *         @arg GPIO_PINNUM_1
  *         @arg GPIO_PINNUM_2
  *         @arg GPIO_PINNUM_3
  *         @arg GPIO_PINNUM_4
  *         @arg GPIO_PINNUM_5
  *         @arg GPIO_PINNUM_6
  *         @arg GPIO_PINNUM_7
  *         @arg GPIO_PINNUM_8
  *         @arg GPIO_PINNUM_9
  *         @arg GPIO_PINNUM_10
  *         @arg GPIO_PINNUM_11
  *         @arg GPIO_PINNUM_12
  *         @arg GPIO_PINNUM_13
  *         @arg GPIO_PINNUM_14
  *         @arg GPIO_PINNUM_15
  * @retval  0 - Pin is low level
  *          1 - Pin is high level
  */ 
uint8 Gpio_ReadPin(const Gpio_RegDef *p_Gpio_st, Gpio_PinNum PinNum_e)
{
    uint8 Value_u8;
    Value_u8 = (uint8)(((p_Gpio_st->IDR) >> GPIO_IDR_BIT_POS(PinNum_e) & \
                           MASK_OF_PIN_IN_GPIO_IDR));

    return Value_u8;
}

/**
  * @brief   Write data to pin that is output mode
  * @note    None
  * @param   p_Gpio_st    Pointer to GPIOx address.
  * @param   PinNum_e    Gpio pin number. It is Gpio_PinNum enum type.
  *                      This parameter can be one of following values:
  *         @arg GPIO_PINNUM_0
  *         @arg GPIO_PINNUM_1
  *         @arg GPIO_PINNUM_2
  *         @arg GPIO_PINNUM_3
  *         @arg GPIO_PINNUM_4
  *         @arg GPIO_PINNUM_5
  *         @arg GPIO_PINNUM_6
  *         @arg GPIO_PINNUM_7
  *         @arg GPIO_PINNUM_8
  *         @arg GPIO_PINNUM_9
  *         @arg GPIO_PINNUM_10
  *         @arg GPIO_PINNUM_11
  *         @arg GPIO_PINNUM_12
  *         @arg GPIO_PINNUM_13
  *         @arg GPIO_PINNUM_14
  *         @arg GPIO_PINNUM_15
  * @param   Value_u8   Data that writes to pin. It is Gpio_PinState enum type.
  *                     This parameter can be one of following values:
  *         @arg GPIO_RESET    Write 0 to output pin
  *         @arg GPIO_SET      Write 1 to output pin
  * @retval  None
  */
void Gpio_WritePin(Gpio_RegDef *p_Gpio_st,
                   Gpio_PinNum PinNum_e,
                   Gpio_PinState Value_u8)
{
    if(GPIO_RESET == Value_u8)
    {
        p_Gpio_st->BSRR = GPIO_BSRR_BR_BIT_MASK(PinNum_e);
    }
    else if (GPIO_SET == Value_u8)
    {
        p_Gpio_st->BSRR = GPIO_BSRR_BS_BIT_MASK(PinNum_e);
    }
    else
    {
        /* Do nothing */
    }
}

/**
  * @brief   Toggle pin that is output mode
  * @note    None
  * @param   p_Gpio_st   Pointer to GPIOx address.
  * @param   PinNum_e    Gpio pin number. It is Gpio_PinNum enum type.
  *                      This parameter can be one of following values:
  *         @arg GPIO_PINNUM_0
  *         @arg GPIO_PINNUM_1
  *         @arg GPIO_PINNUM_2
  *         @arg GPIO_PINNUM_3
  *         @arg GPIO_PINNUM_4
  *         @arg GPIO_PINNUM_5
  *         @arg GPIO_PINNUM_6
  *         @arg GPIO_PINNUM_7
  *         @arg GPIO_PINNUM_8
  *         @arg GPIO_PINNUM_9
  *         @arg GPIO_PINNUM_10
  *         @arg GPIO_PINNUM_11
  *         @arg GPIO_PINNUM_12
  *         @arg GPIO_PINNUM_13
  *         @arg GPIO_PINNUM_14
  *         @arg GPIO_PINNUM_15
  * @retval  None
  */
void Gpio_TogglePin(Gpio_RegDef *p_Gpio_st, Gpio_PinNum PinNum_e)
{
    if(p_Gpio_st->ODR & GPIO_ODR_BIT_MASK(PinNum_e))
    {
        p_Gpio_st->BSRR = GPIO_BSRR_BR_BIT_MASK(PinNum_e);
    }
    else
    {
        p_Gpio_st->BSRR = GPIO_BSRR_BS_BIT_MASK(PinNum_e);
    }
}

/**
  * @brief   Check the pin that locked or not
  * @note    None
  * @param   p_Gpio_st   Pointer to GPIOx address.
  * @param   PinNum_e    Gpio pin number. It is Gpio_PinNum enum type.
  *                      This parameter can be one of following values:
  *         @arg GPIO_PINNUM_0
  *         @arg GPIO_PINNUM_1
  *         @arg GPIO_PINNUM_2
  *         @arg GPIO_PINNUM_3
  *         @arg GPIO_PINNUM_4
  *         @arg GPIO_PINNUM_5
  *         @arg GPIO_PINNUM_6
  *         @arg GPIO_PINNUM_7
  *         @arg GPIO_PINNUM_8
  *         @arg GPIO_PINNUM_9
  *         @arg GPIO_PINNUM_10
  *         @arg GPIO_PINNUM_11
  *         @arg GPIO_PINNUM_12
  *         @arg GPIO_PINNUM_13
  *         @arg GPIO_PINNUM_14
  *         @arg GPIO_PINNUM_15
  * @retval  TRUE - Pin locked
  *          FALSE - Pin didn't locked
  */
uint8 Gpio_IsLocked(Gpio_RegDef *p_Gpio_st, Gpio_PinNum PinNum_u8)
{
    uint8 RetValue_u8;
    if((0 != (p_Gpio_st->LCKR & GPIO_LCKR_LCKK_MASK)) && \
       (0 != (p_Gpio_st->LCKR & GPIO_LCKR_LCK_BIT_MASK(PinNum_u8))))
    {
        RetValue_u8 = TRUE;
    }
    else
    {
        RetValue_u8 = FALSE;
    }

    return RetValue_u8;
}

/**
  * @brief   Lock pin configuration,
  *          so unwanted changes to GPIO pin configuration can be avoid.
  * @note    None
  * @param   p_Gpio_st   Pointer to GPIOx address.
  * @param   PinNum_e    Gpio pin number. It is Gpio_PinNum enum type.
  *                      This parameter can be one of following values:
  *         @arg GPIO_PINNUM_0
  *         @arg GPIO_PINNUM_1
  *         @arg GPIO_PINNUM_2
  *         @arg GPIO_PINNUM_3
  *         @arg GPIO_PINNUM_4
  *         @arg GPIO_PINNUM_5
  *         @arg GPIO_PINNUM_6
  *         @arg GPIO_PINNUM_7
  *         @arg GPIO_PINNUM_8
  *         @arg GPIO_PINNUM_9
  *         @arg GPIO_PINNUM_10
  *         @arg GPIO_PINNUM_11
  *         @arg GPIO_PINNUM_12
  *         @arg GPIO_PINNUM_13
  *         @arg GPIO_PINNUM_14
  *         @arg GPIO_PINNUM_15
  * @retval  RET_OK - Pin has locked success
  *          RET_NOT_OK - Pin has locked fail
  */
ReturnType Gpio_PinCfgLock(Gpio_RegDef *p_Gpio_st, uint32 PinsToLock_u32)
{
    ReturnType RetValue = RET_OK;

    /* Lock write sequence */
    p_Gpio_st->LCKR = (GPIO_LCKR_LCKK_MASK | PinsToLock_u32);
    p_Gpio_st->LCKR = PinsToLock_u32;
    p_Gpio_st->LCKR = (GPIO_LCKR_LCKK_MASK | PinsToLock_u32);

    /* Read first time to make LCKR stable */
    (void)(p_Gpio_st->LCKR);
    if((GPIO_LCKR_LCKK_MASK | PinsToLock_u32) != (p_Gpio_st->LCKR))
    {
        RetValue = RET_NOT_OK;
    }
    else
    {
        /* do nothing */
    }

    return RetValue;
}

/**
  * @brief   Gpio handler is called by Exti handlers
  * @note    None
  * @param   ExtLine_e   Exti line number.
  * @retval  None
  */
void Gpio_ExtHandler(Exti_Line ExtLine_e)
{
    /* Call user's handler function */
    p_GpioHandler((Gpio_PinNum)ExtLine_e);
}