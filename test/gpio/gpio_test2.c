/*******************************************************************************
 * File  : gpio_test2.c       
 * Author: phamtien758      
 * Brief : Test Gpio_WritePin function
 ******************************************************************************/

#include "gpio.h"
#include "stub.h"

void delay(uint32 times)
{
    for (uint32 i = 0; i < times; i++);
}

Gpio_Config Config1 = 
{
    .Gpio_PinNum_e       = GPIO_PINNUM_5,      /* Onboard LED2 is on PA_5 pin */
    .Gpio_PinMode_e      = GPIO_MODE_OUT,
    .Gpio_PinSpeed_e     = GPIO_OUTSPEED_LOW,
    .Gpio_PinPuPd_e      = GPIO_PULLUPDOWN_NOPULL,
    .Gpio_PinOutType_e   = GPIO_OUTTYPE_PUSPUL,
    .Gpio_PinAltFun_e    = GPIO_ALTFUN_0,
    .Gpio_ExIntEnable_u8 = DISABLE,
    .Gpio_ExIntEdge_e    = GPIO_EXTEDGE_FALL,
    .Gpio_ExIntCallback  = NULL
};

int main(void)
{
    RCC_GPIOA_CLK_EN();
    Gpio_Init(GPIOA, &Config1);
    while(1)
    {
        Gpio_WritePin(GPIOA, GPIO_PINNUM_5, GPIO_SET);
        delay(100000);
        Gpio_WritePin(GPIOA, GPIO_PINNUM_5, GPIO_RESET);
        delay(100000);
    }

    return 0;
}
