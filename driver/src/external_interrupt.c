/*******************************************************************************
 * File  : external_interrupt.c       
 * Author: phamtien758      
 * Brief : The external interrupt source file
 ******************************************************************************/

/*** INCLUDE ******************************************************************/

#include "external_interrupt.h"

/*** DEFINE *******************************************************************/

/*** VARIABLE *****************************************************************/

/*
 * @brief  Contains the base address of EXTI
 */
static Exti_RegDef *p_ExtiBase_st = EXTI;

/*
 * @brief  Pointer to external interrupt handler
 */
static ExtFuncHandler p_Handler = NULL;

/*** PROTOTYPE ****************************************************************/

static ReturnType Exti_CheckLineValid(Exti_Line LineNum_e);

/*** STATIC FUNCTION **********************************************************/

/**
  * @brief  Function checks the accuracy of Exti line. Wrong Exti line may cause
  *         the microcontroller to operate incorrectly.
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @retval RET_OK - Exti line is valid
  *         RET_NOT_OK - Exti line is invalid
  */ 
static ReturnType Exti_CheckLineValid(Exti_Line LineNum_e)
{
    ReturnType RetValue;

    if(((EXTI_LINE0 <= LineNum_e) && (EXTI_LINE18 >= LineNum_e)) || \
       (EXTI_LINE21 == LineNum_e) || (EXTI_LINE22 == LineNum_e))
    {
        RetValue = RET_OK;
    }
    else
    {
        RetValue = RET_NOT_OK;
    }

    return RetValue;
}

/*** FUNCTIONS ****************************************************************/

/**
  * @brief  Enable external interrupt
  * @note   None
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @param  p_Func       User's handler function
  * @retval RET_OK - Enable successful
  *         RET_NOT_OK - Enable unsuccessful
  */
ReturnType Exti_IntEnable(Exti_Line LineNum_e, ExtFuncHandler p_Func)
{
    ReturnType RetValue;
    
    RetValue = Exti_CheckLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_IMR |= EXTI_IMR_BIT_MASK(LineNum_e);
        p_Handler = p_Func;
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

/**
  * @brief  Disable external interrupt
  * @note   None
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @retval RET_OK - Disable successful
  *         RET_NOT_OK - Disable unsuccessful
  */ 
ReturnType Exti_IntDisable(Exti_Line LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_CheckLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_IMR &= ~EXTI_IMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

/**
  * @brief  Enable event
  * @note   None
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @retval RET_OK - Enable successful
  *         RET_NOT_OK - Enable unsuccessful
  */ 
ReturnType Exti_EventEnable(Exti_Line LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_CheckLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_EMR |= EXTI_EMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

/**
  * @brief  Disable event
  * @note   None
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @retval RET_OK - Disable successful
  *         RET_NOT_OK - Disable unsuccessful
  */ 
ReturnType Exti_EventDisable(Exti_Line LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_CheckLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_EMR &= ~EXTI_EMR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

/**
  * @brief  Edge trigger config
  * @note   None
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @param  EdgeCfg_e   Edge trigger.
  *                     This parameter can be one of following values:
  *         @arg EXTI_EDGE_FALL - 
  *         @arg EXTI_EDGE_RISE
  *         @arg EXTI_EDGE_FALLRISE
  * @retval RET_OK - Enable successful
  *         RET_NOT_OK - Enable unsuccessful
  */ 
ReturnType Exti_EdgeCfg(Exti_Line LineNum_e, Exti_Edge EdgeCfg_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_CheckLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        if(EXTI_EDGE_FALL == EdgeCfg_e)
        {
            p_ExtiBase_st->EXTI_FTSR |= EXTI_FTSR_BIT_MASK(LineNum_e);
            p_ExtiBase_st->EXTI_RTSR &= ~EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else if(EXTI_EDGE_RISE == EdgeCfg_e)
        {
            p_ExtiBase_st->EXTI_FTSR &= ~EXTI_FTSR_BIT_MASK(LineNum_e);
            p_ExtiBase_st->EXTI_RTSR |= EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else if(EXTI_EDGE_FALLRISE == EdgeCfg_e)
        {
            p_ExtiBase_st->EXTI_FTSR |= EXTI_FTSR_BIT_MASK(LineNum_e);
            p_ExtiBase_st->EXTI_RTSR |= EXTI_RTSR_BIT_MASK(LineNum_e);
        }
        else
        {
            /* Do nothing */
        }   
    }

    return RetValue;
}

/**
  * @brief  Clear pending bit
  * @note   None
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @retval RET_OK - Clear successful
  *         RET_NOT_OK - Clear unsuccessful
  */
ReturnType Exti_ClearPending(Exti_Line LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_CheckLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_PR |= EXTI_PR_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

/**
  * @brief  Generate interrupt/event by software
  * @note   None
  * @param  Exti_Line  Exti line number.
  *                      This parameter can be one of following values:
  *         @arg EXTI_LINE0
  *         @arg EXTI_LINE1
  *         @arg EXTI_LINE2
  *         @arg EXTI_LINE3
  *         @arg EXTI_LINE4
  *         @arg EXTI_LINE5
  *         @arg EXTI_LINE6
  *         @arg EXTI_LINE7
  *         @arg EXTI_LINE8
  *         @arg EXTI_LINE9
  *         @arg EXTI_LINE10
  *         @arg EXTI_LINE11
  *         @arg EXTI_LINE12
  *         @arg EXTI_LINE13
  *         @arg EXTI_LINE14
  *         @arg EXTI_LINE15
  *         @arg EXTI_LINE16
  *         @arg EXTI_LINE17
  *         @arg EXTI_LINE18
  *         @arg EXTI_LINE21
  *         @arg EXTI_LINE22
  * @retval RET_OK - Generate successful
  *         RET_NOT_OK - Generate unsuccessful
  */
ReturnType Exti_SoftIntGenerate(Exti_Line LineNum_e)
{
    ReturnType RetValue;
    
    RetValue = Exti_CheckLineValid(LineNum_e);

    if(RET_OK == RetValue)
    {
        p_ExtiBase_st->EXTI_SWIER |= EXTI_SWIER_BIT_MASK(LineNum_e);
    }
    else
    {
        /* Do nothing */
    }

    return RetValue;
}

/**
  * @brief  Returns a value that tells us which Exti lines are pending
  * @note   None
  * @param  void
  * @retval uint32 - Value of the pending register
  */
uint32 Exti_GetPending(void)
{
    return (uint32)(p_ExtiBase_st->EXTI_PR);
}

/*
 * @brief Function handler for EXTI0
 */
void EXTI0_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE0);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE0);
    }
}

/*
 * @brief Function handler for EXTI1
 */
void EXTI1_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE1);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE1);
    }
}

/*
 * @brief Function handler for EXTI2
 */
void EXTI2_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE2);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE2);
    }
}

/*
 * @brief Function handler for EXTI3
 */
void EXTI3_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE3);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE3);
    }
}

/*
 * @brief Function handler for EXTI4
 */
void EXTI4_IRQHandler(void)
{
    Exti_ClearPending(EXTI_LINE4);
    if(NULL != p_Handler)
    {
        p_Handler(EXTI_LINE4);
    }
}

/*
 * @brief Function handler for EXTI5 -> EXTI9
 */
void EXTI9_5_IRQHandler(void)
{
    uint32 PendValue_u32;
    Exti_Line Line_e;

    PendValue_u32 = Exti_GetPending();

    if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE5))
    {
        Line_e = EXTI_LINE5;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE6))
    {
        Line_e = EXTI_LINE6;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE7))
    {
        Line_e = EXTI_LINE7;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE8))
    {
        Line_e = EXTI_LINE8;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE9))
    {
        Line_e = EXTI_LINE9;
    }
    else
    {
        /* do nothing */
    }
    Exti_ClearPending(Line_e);
    if(NULL != p_Handler)
    {
        p_Handler(Line_e);
    }
}

/*
 * @brief Function handler for EXTI5 -> EXTI10
 */
void EXTI15_10_IRQHandler(void)
{
    uint32 PendValue_u32;
    Exti_Line Line_e;

    PendValue_u32 = Exti_GetPending();

    if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE10))
    {
        Line_e = EXTI_LINE10;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE11))
    {
        Line_e = EXTI_LINE11;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE12))
    {
        Line_e = EXTI_LINE12;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE13))
    {
        Line_e = EXTI_LINE13;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE14))
    {
        Line_e = EXTI_LINE14;
    }
    else if(PendValue_u32 & EXTI_PR_BIT_MASK(EXTI_LINE15))
    {
        Line_e = EXTI_LINE15;
    }
    else
    {
        /* do nothing */
    }
    Exti_ClearPending(Line_e);
    if(NULL != p_Handler)
    {
        p_Handler(Line_e);
    }
}