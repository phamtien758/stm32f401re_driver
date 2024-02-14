/*******************************************************************************
 * File  : external_interrupt.h    
 * Author: phamtien758      
 * Brief : The external interrupt header file
 ******************************************************************************/

#ifndef EXTERNAL_INTERRUPT_H
#define EXTERNAL_INTERRUPT_H

/*** INCLUDE ************************************/

#include "stm32f401re.h"

/*** DEFINE ************************************/

/*** TYPEDEF ************************************/
/*
 * @Exti_Line_def
 * @brief Exti line number
 */
typedef enum
{
    EXTI_LINE0  = 0U,     /* Exti line 0 */
    EXTI_LINE1  = 1U,     /* Exti line 1 */
    EXTI_LINE2  = 2U,     /* Exti line 2 */
    EXTI_LINE3  = 3U,     /* Exti line 3 */
    EXTI_LINE4  = 4U,     /* Exti line 4 */
    EXTI_LINE5  = 5U,     /* Exti line 5 */
    EXTI_LINE6  = 6U,     /* Exti line 6 */
    EXTI_LINE7  = 7U,     /* Exti line 7 */
    EXTI_LINE8  = 8U,     /* Exti line 8 */
    EXTI_LINE9  = 9U,     /* Exti line 9 */
    EXTI_LINE10 = 10U,    /* Exti line 10 */
    EXTI_LINE11 = 11U,    /* Exti line 11 */
    EXTI_LINE12 = 12U,    /* Exti line 12 */
    EXTI_LINE13 = 13U,    /* Exti line 13 */
    EXTI_LINE14 = 14U,    /* Exti line 14 */
    EXTI_LINE15 = 15U,    /* Exti line 15 */
    EXTI_LINE16 = 16U,    /* Exti line 16 */
    EXTI_LINE17 = 17U,    /* Exti line 17 */
    EXTI_LINE18 = 18U,    /* Exti line 18 */
    EXTI_LINE21 = 21U,    /* Exti line 21 */
    EXTI_LINE22 = 22U     /* Exti line 22 */
} Exti_Line;

/*
 * @Exti_Edge_def
 * @brief External interrupt edge triggers
 */
typedef enum
{
	EXTI_EDGE_FALL      = 0,    /* Falling edge */
	EXTI_EDGE_RISE      = 1,    /* Rising edge */
	EXTI_EDGE_FALLRISE  = 2,    /* Both falling and rising edge */
}Exti_Edge;

/*
 * @brief Pointer to user's handler function
 */
typedef void (*ExtFuncHandler)(Exti_Line);

/*** PROTOTYPE ****************************/

/* Enable external interrupt */
ReturnType Exti_IntEnable(Exti_Line LineNum_e, ExtFuncHandler p_Func);

/* Disable external interrupt */
ReturnType Exti_IntDisable(Exti_Line LineNum_e);

/* Enable event */
ReturnType Exti_EventEnable(Exti_Line LineNum_e);

/* Disable event */
ReturnType Exti_EventDisable(Exti_Line LineNum_e);

/* Select trigger edges */
ReturnType Exti_EdgeCfg(Exti_Line LineNum_e, Exti_Edge EdgeCfg_e);

/* Generate interrupt/event by software */
ReturnType Exti_SoftIntGenerate(Exti_Line LineNum_e);

/* Clear pending status */
ReturnType Exti_ClearPending(Exti_Line LineNum_e);

/* Return pending value of external interrupts */
uint32   Exti_GetPending(void);

/* Override weak Exti line handlers (0-15) */
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);

#endif /* EXTERNAL_INTERRUPT_H */