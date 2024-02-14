/*******************************************************************************
 * File  : stub.h       
 * Author: phamtien758      
 * Brief : Stub
 ******************************************************************************/

#ifndef STUB_H
#define STUB_H

#include "stm32f401re.h"

/*
 * Gpio clock enable macros
 */
#define RCC_GPIOA_CLK_EN()    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN_MASK)
#define RCC_GPIOB_CLK_EN()    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN_MASK)
#define RCC_GPIOC_CLK_EN()    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN_MASK)
#define RCC_GPIOD_CLK_EN()    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN_MASK)
#define RCC_GPIOE_CLK_EN()    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN_MASK)
#define RCC_GPIOH_CLK_EN()    (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN_MASK)

/*
 * I2c clock enable macros
 */
#define RCC_I2C1_CLK_EN()     (RCC->APB1ENR |= RCC_APB1ENR_I2C1EN_MASK)
#define RCC_I2C2_CLK_EN()     (RCC->APB1ENR |= RCC_APB1ENR_I2C2EN_MASK)
#define RCC_I2C3_CLK_EN()     (RCC->APB1ENR |= RCC_APB1ENR_I2C3EN_MASK)

/*
 * Usart clock enable macros
 */
#define RCC_USART1_CLK_EN()   (RCC->APB2ENR |= RCC_APB2ENR_USART1EN_MASK)
#define RCC_USART2_CLK_EN()   (RCC->APB1ENR |= RCC_APB1ENR_USART2EN_MASK)
#define RCC_USART6_CLK_EN()   (RCC->APB2ENR |= RCC_APB2ENR_USART6EN_MASK)

/*
 * Spi clock enable macros
 */
#define RCC_SPI1_CLK_EN()     (RCC->APB2ENR |= RCC_APB2ENR_SPI1EN_MASK)
#define RCC_SPI2_CLK_EN()     (RCC->APB1ENR |= RCC_APB1ENR_SPI2EN_MASK)
#define RCC_SPI3_CLK_EN()     (RCC->APB1ENR |= RCC_APB1ENR_SPI3EN_MASK)
#define RCC_SPI4_CLK_EN()     (RCC->APB2ENR |= RCC_APB2ENR_SPI4EN_MASK)

/*
 * Syscfg clock enable macros
 */
#define RCC_SYSCFG_CLK_EN()   (RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN_MASK)

/*
 * Gpio clock disable macros
 */
#define RCC_GPIOA_CLK_DIS()    (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN_MASK)
#define RCC_GPIOB_CLK_DIS()    (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN_MASK)
#define RCC_GPIOC_CLK_DIS()    (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN_MASK)
#define RCC_GPIOD_CLK_DIS()    (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN_MASK)
#define RCC_GPIOE_CLK_DIS()    (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN_MASK)
#define RCC_GPIOH_CLK_DIS()    (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN_MASK)

/*
 * I2c clock disable macros
 */
#define RCC_I2C1_CLK_DIS()     (RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN_MASK)
#define RCC_I2C2_CLK_DIS()     (RCC->APB1ENR &= ~RCC_APB1ENR_I2C2EN_MASK)
#define RCC_I2C3_CLK_DIS()     (RCC->APB1ENR &= ~RCC_APB1ENR_I2C3EN_MASK)

/*
 * Usart clock disable macros
 */
#define RCC_USART1_CLK_DIS()   (RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN_MASK)
#define RCC_USART2_CLK_DIS()   (RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN_MASK)
#define RCC_USART6_CLK_DIS()   (RCC->APB2ENR &= ~RCC_APB2ENR_USART6EN_MASK)

/*
 * Spi clock disable macros
 */
#define RCC_SPI1_CLK_DIS()     (RCC->APB2ENR &= ~RCC_APB2ENR_SPI1EN_MASK)
#define RCC_SPI2_CLK_DIS()     (RCC->APB1ENR &= ~RCC_APB1ENR_SPI2EN_MASK)
#define RCC_SPI3_CLK_DIS()     (RCC->APB1ENR &= ~RCC_APB1ENR_SPI3EN_MASK)
#define RCC_SPI4_CLK_DIS()     (RCC->APB2ENR &= ~RCC_APB2ENR_SPI4EN_MASK)

/*
 * Syscfg clock disable macros
 */
#define RCC_SYSCFG_CLK_DIS()   (RCC->APB2ENR &= ~RCC_APB2ENR_SYSCFGEN_MASK)

/*
 * Peripheral reset functions
 */
static inline void Rcc_GpioA_Reset(void)
{
	Rcc_RegDef *p_Rcc_Base_st = RCC;
	p_Rcc_Base_st->AHB1RSTR |= RCC_AHB1RSTR_GPIOARST_MASK;
	p_Rcc_Base_st->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOARST_MASK;
}

static inline void Rcc_GpioB_Reset(void)
{
	Rcc_RegDef *p_Rcc_Base_st = RCC;
	p_Rcc_Base_st->AHB1RSTR |= RCC_AHB1RSTR_GPIOBRST_MASK;
	p_Rcc_Base_st->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOBRST_MASK;
}

static inline void Rcc_GpioC_Reset(void)
{
	Rcc_RegDef *p_Rcc_Base_st = RCC;
	p_Rcc_Base_st->AHB1RSTR |= RCC_AHB1RSTR_GPIOCRST_MASK;
	p_Rcc_Base_st->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOCRST_MASK;
}

static inline void Rcc_GpioD_Reset(void)
{
	Rcc_RegDef *p_Rcc_Base_st = RCC;
	p_Rcc_Base_st->AHB1RSTR |= RCC_AHB1RSTR_GPIODRST_MASK;
	p_Rcc_Base_st->AHB1RSTR &= ~RCC_AHB1RSTR_GPIODRST_MASK;
}

static inline void Rcc_GpioE_Reset(void)
{
	Rcc_RegDef *p_Rcc_Base_st = RCC;
	p_Rcc_Base_st->AHB1RSTR |= RCC_AHB1RSTR_GPIOERST_MASK;
	p_Rcc_Base_st->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOERST_MASK;
}

static inline void Rcc_GpioH_Reset(void)
{
	Rcc_RegDef *p_Rcc_Base_st = RCC;
	p_Rcc_Base_st->AHB1RSTR |= RCC_AHB1RSTR_GPIOHRST_MASK;
	p_Rcc_Base_st->AHB1RSTR &= ~RCC_AHB1RSTR_GPIOHRST_MASK;
}

/* Stub of SYSCFG */
typedef enum
{
	SYS_EXTI0  = 0U,
	SYS_EXTI1  = 1U,
	SYS_EXTI2  = 2U,
	SYS_EXTI3  = 3U,
	SYS_EXTI4  = 4U,
	SYS_EXTI5  = 5U,
	SYS_EXTI6  = 6U,
	SYS_EXTI7  = 7U,
	SYS_EXTI8  = 8U,
	SYS_EXTI9  = 9U,
	SYS_EXTI10 = 10U,
	SYS_EXTI11 = 11U,
	SYS_EXTI12 = 12U,
	SYS_EXTI13 = 13U,
	SYS_EXTI14 = 14U,
	SYS_EXTI15 = 15U
}Sys_Exti;

typedef enum
{
	SYS_PORTA = 0,
	SYS_PORTB = 1,
	SYS_PORTC = 2,
	SYS_PORTD = 3,
	SYS_PORTE = 4,
	SYS_PORTH = 7
}Sys_Port;

void Sys_ExIntCfg(Sys_Exti ExtiNum_e, Sys_Port Port_e);

#endif /* STUB_H_ */
