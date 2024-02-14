/*******************************************************************************
 * File  : template.h       
 * Author: phamtien758      
 * Brief : The template header file
 ******************************************************************************/

#ifndef TEMPLATE_H
#define TEMPLATE_H

/*** INCLUDE ******************************************************************/
#include "header.h"

/*** DEFINE *******************************************************************/
#define NOTHING    0

/*** TYPEDEF ******************************************************************/

/*
 * @brief This is structure named struct1
 */
typedef struct
{
    uint8 Data_u8;    /* Data */
}struct1;

/*** EXTERN *******************************************************************/

extern uint8 State_u8;

/*** PROTOTYPE ****************************************************************/

/* Function 1 */
void func1(void);

#endif /* TEMPLATE_H */