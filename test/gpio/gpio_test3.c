/*******************************************************************************
 * File  : gpio_test3.c       
 * Author: phamtien758      
 * Brief : Test Gpio_ReadPin function
 ******************************************************************************/

#include "gpio.h"
#include "stub.h"

void delay(uint32 times)
{
    for (uint32 i = 0; i < times; i++);
}

Gpio_Config ConfigLed = 
{
    .Gpio_PinNum_e       = GPIO_PINNUM_5,      /* Onboard LED2 is on PA_5 pin */
    .Gpio_PinMode_e      = GPIO_MODE_OUT,
    .Gpio_PinSpeed_e     = GPIO_OUTSPEED_LOW,
    .Gpio_PinPuPd_e      = GPIO_PULLUPDOWN_NOPULL,
    .Gpio_PinOutType_e   = GPIO_OUTTYPE_PUSPUL,
    .Gpio_PinAltFun_e    = GPIO_ALTFUN_0,
    .Gpio_ExIntEnable_u8 = DISABLE,
    .Gpio_ExIntEdge_e    = EXTI_EDGE_FALL,
    .Gpio_ExIntCallback  = NULL
};

Gpio_Config ConfigButton = 
{
    .Gpio_PinNum_e       = GPIO_PINNUM_13,     /* User button is on PC_13 pin */
    .Gpio_PinMode_e      = GPIO_MODE_IN,
    .Gpio_PinSpeed_e     = GPIO_OUTSPEED_LOW,
    .Gpio_PinPuPd_e      = GPIO_PULLUPDOWN_NOPULL, /* Choose no register because board has pull-up register already */
    .Gpio_PinOutType_e   = GPIO_OUTTYPE_PUSPUL,
    .Gpio_PinAltFun_e    = GPIO_ALTFUN_0,
    .Gpio_ExIntEnable_u8 = DISABLE,
    .Gpio_ExIntEdge_e    = GPIO_EXTEDGE_FALL,
    .Gpio_ExIntCallback  = NULL
};

int main(void)
{
    RCC_GPIOA_CLK_EN();
    RCC_GPIOC_CLK_EN();
    Gpio_Init(GPIOA, &ConfigLed);
    Gpio_Init(GPIOC, &ConfigButton);
    while(1)
    {
        if(GPIO_RESET == Gpio_ReadPin(GPIOC, GPIO_PINNUM_13))
        {
            Gpio_WritePin(GPIOA, GPIO_PINNUM_5, GPIO_SET);
        }
        else
        {
            Gpio_WritePin(GPIOA, GPIO_PINNUM_5, GPIO_RESET);
        }
    }

    return 0;
}
