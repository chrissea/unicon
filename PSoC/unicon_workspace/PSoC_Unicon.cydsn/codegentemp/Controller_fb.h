/*******************************************************************************
* File Name: Controller_fb.h
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
#if !defined(CY_ISR_Controller_fb_H)
#define CY_ISR_Controller_fb_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void Controller_fb_Start(void);
void Controller_fb_StartEx(cyisraddress address);
void Controller_fb_Stop(void);

CY_ISR_PROTO(Controller_fb_Interrupt);

void Controller_fb_SetVector(cyisraddress address);
cyisraddress Controller_fb_GetVector(void);

void Controller_fb_SetPriority(uint8 priority);
uint8 Controller_fb_GetPriority(void);

void Controller_fb_Enable(void);
uint8 Controller_fb_GetState(void);
void Controller_fb_Disable(void);

void Controller_fb_SetPending(void);
void Controller_fb_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the Controller_fb ISR. */
#define Controller_fb_INTC_VECTOR            ((reg32 *) Controller_fb__INTC_VECT)

/* Address of the Controller_fb ISR priority. */
#define Controller_fb_INTC_PRIOR             ((reg8 *) Controller_fb__INTC_PRIOR_REG)

/* Priority of the Controller_fb interrupt. */
#define Controller_fb_INTC_PRIOR_NUMBER      Controller_fb__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable Controller_fb interrupt. */
#define Controller_fb_INTC_SET_EN            ((reg32 *) Controller_fb__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the Controller_fb interrupt. */
#define Controller_fb_INTC_CLR_EN            ((reg32 *) Controller_fb__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the Controller_fb interrupt state to pending. */
#define Controller_fb_INTC_SET_PD            ((reg32 *) Controller_fb__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the Controller_fb interrupt. */
#define Controller_fb_INTC_CLR_PD            ((reg32 *) Controller_fb__INTC_CLR_PD_REG)


#endif /* CY_ISR_Controller_fb_H */


/* [] END OF FILE */
