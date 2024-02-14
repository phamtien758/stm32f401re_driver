/*******************************************************************************
 * File  : gpio_test5.c       
 * Author: phamtien758      
 * Brief : Test two external interrupt in same EXTI15_10 Irq
 ******************************************************************************/

#include "gpio.h"
#include "stub.h"
#include "interrupt.h"

void Button_Handler(Gpio_PinNum LineNum_e);

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

Gpio_Config ConfigButton1 = 
{
    .Gpio_PinNum_e       = GPIO_PINNUM_13,     /* User button on PC_13 pin */
    .Gpio_PinMode_e      = GPIO_MODE_IN,
    .Gpio_PinSpeed_e     = GPIO_OUTSPEED_LOW,
    .Gpio_PinPuPd_e      = GPIO_PULLUPDOWN_NOPULL, /* Choose no register because board has pull-up register already */
    .Gpio_PinOutType_e   = GPIO_OUTTYPE_PUSPUL,
    .Gpio_PinAltFun_e    = GPIO_ALTFUN_0,
    .Gpio_ExIntEnable_u8 = ENABLE,
    .Gpio_ExIntEdge_e    = GPIO_EXTEDGE_RISE,
    .Gpio_ExIntCallback  = Button_Handler
};

Gpio_Config ConfigButton2 = 
{
    .Gpio_PinNum_e       = GPIO_PINNUM_10,     /* Button on PC_10 pin */
    .Gpio_PinMode_e      = GPIO_MODE_IN,
    .Gpio_PinSpeed_e     = GPIO_OUTSPEED_LOW,
    .Gpio_PinPuPd_e      = GPIO_PULLUPDOWN_PULLUP, /* Choose no register because used external register */
    .Gpio_PinOutType_e   = GPIO_OUTTYPE_PUSPUL,
    .Gpio_PinAltFun_e    = GPIO_ALTFUN_0,
    .Gpio_ExIntEnable_u8 = ENABLE,
    .Gpio_ExIntEdge_e    = GPIO_EXTEDGE_RISE,
    .Gpio_ExIntCallback  = Button_Handler
};

int main(void)
{
    RCC_GPIOA_CLK_EN();
    RCC_GPIOC_CLK_EN();
    RCC_SYSCFG_CLK_EN();

    Nvic_EnableIrq(IRQ_NUM_EXTI15_10);
    Sys_ExIntCfg(SYS_EXTI10, SYS_PORTC);
    Sys_ExIntCfg(SYS_EXTI13, SYS_PORTC);
    
    Gpio_Init(GPIOA, &ConfigLed);
    Gpio_Init(GPIOC, &ConfigButton1);
    Gpio_Init(GPIOC, &ConfigButton2);

    while(1);

    return 0;
}

void Button_Handler(Gpio_PinNum LineNum_e)
{
    if(GPIO_PINNUM_13 == LineNum_e)
    {
        Gpio_WritePin(GPIOA, GPIO_PINNUM_5, GPIO_SET);
    }
    else if (GPIO_PINNUM_10 == LineNum_e)
    {
        Gpio_WritePin(GPIOA, GPIO_PINNUM_5, GPIO_RESET);
    }
}