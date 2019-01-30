/*******************************************************************************
* File Name: Console_fb.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_Console_fb_H)
#define CY_ISR_Console_fb_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Console_fb_Start(void);
void Console_fb_StartEx(cyisraddress address);
void Console_fb_Stop(void);

CY_ISR_PROTO(Console_fb_Interrupt);

void Console_fb_SetVector(cyisraddress address);
cyisraddress Console_fb_GetVector(void);

void Console_fb_SetPriority(uint8 priority);
uint8 Console_fb_GetPriority(void);

void Console_fb_Enable(void);
uint8 Console_fb_GetState(void);
void Console_fb_Disable(void);

void Console_fb_SetPending(void);
void Console_fb_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Console_fb ISR. */
#define Console_fb_INTC_VECTOR            ((reg32 *) Console_fb__INTC_VECT)

/* Address of the Console_fb ISR priority. */
#define Console_fb_INTC_PRIOR             ((reg8 *) Console_fb__INTC_PRIOR_REG)

/* Priority of the Console_fb interrupt. */
#define Console_fb_INTC_PRIOR_NUMBER      Console_fb__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Console_fb interrupt. */
#define Console_fb_INTC_SET_EN            ((reg32 *) Console_fb__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Console_fb interrupt. */
#define Console_fb_INTC_CLR_EN            ((reg32 *) Console_fb__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Console_fb interrupt state to pending. */
#define Console_fb_INTC_SET_PD            ((reg32 *) Console_fb__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Console_fb interrupt. */
#define Console_fb_INTC_CLR_PD            ((reg32 *) Console_fb__INTC_CLR_PD_REG)


#endif /* CY_ISR_Console_fb_H */


/* [] END OF FILE */
