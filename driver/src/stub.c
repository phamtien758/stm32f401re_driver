/*******************************************************************************
 * File  : stub.c       
 * Author: phamtien758      
 * Brief : Stub source file
 ******************************************************************************/

/*** INCLUDE ******************************************************************/

#include "stub.h"

/*** DEFINE *******************************************************************/

/*** VARIABLES ****************************************************************/

/*** PROTOTYPE ****************************************************************/

/*** STATIC FUNCTION **********************************************************/

/*** FUNCTIONS ****************************************************************/

/**
  * @brief   Select port for Exti line interrupt
  * @note    None
  * @param   ExtiNum_e Exti line number
  * @param   Port_e    Portx
  * @retval  None
  */       
void Sys_ExIntCfg(Sys_Exti ExtiNum_e, Sys_Port Port_e)
{
    uint8 RegIndex_u8;
    uint8 ExtiIndex_u8;

    RegIndex_u8 = (uint8)ExtiNum_e / (uint8)SYSCFG_EXTICR_NUM_EXTI;
    ExtiIndex_u8 = (uint8)ExtiNum_e % (uint8)SYSCFG_EXTICR_NUM_EXTI;

    SYSCFG->EXTICR[RegIndex_u8] |= (Port_e << \
                                    SYSCFG_EXTICR_EXTI_POS(ExtiIndex_u8));
}