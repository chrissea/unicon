/*******************************************************************************
* File Name: System_Clock_Slow.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_System_Clock_Slow_H)
#define CY_CLOCK_System_Clock_Slow_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void System_Clock_Slow_Start(void) ;
void System_Clock_Slow_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void System_Clock_Slow_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void System_Clock_Slow_StandbyPower(uint8 state) ;
void System_Clock_Slow_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 System_Clock_Slow_GetDividerRegister(void) ;
void System_Clock_Slow_SetModeRegister(uint8 modeBitMask) ;
void System_Clock_Slow_ClearModeRegister(uint8 modeBitMask) ;
uint8 System_Clock_Slow_GetModeRegister(void) ;
void System_Clock_Slow_SetSourceRegister(uint8 clkSource) ;
uint8 System_Clock_Slow_GetSourceRegister(void) ;
#if defined(System_Clock_Slow__CFG3)
void System_Clock_Slow_SetPhaseRegister(uint8 clkPhase) ;
uint8 System_Clock_Slow_GetPhaseRegister(void) ;
#endif /* defined(System_Clock_Slow__CFG3) */

#define System_Clock_Slow_Enable()                       System_Clock_Slow_Start()
#define System_Clock_Slow_Disable()                      System_Clock_Slow_Stop()
#define System_Clock_Slow_SetDivider(clkDivider)         System_Clock_Slow_SetDividerRegister(clkDivider, 1u)
#define System_Clock_Slow_SetDividerValue(clkDivider)    System_Clock_Slow_SetDividerRegister((clkDivider) - 1u, 1u)
#define System_Clock_Slow_SetMode(clkMode)               System_Clock_Slow_SetModeRegister(clkMode)
#define System_Clock_Slow_SetSource(clkSource)           System_Clock_Slow_SetSourceRegister(clkSource)
#if defined(System_Clock_Slow__CFG3)
#define System_Clock_Slow_SetPhase(clkPhase)             System_Clock_Slow_SetPhaseRegister(clkPhase)
#define System_Clock_Slow_SetPhaseValue(clkPhase)        System_Clock_Slow_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(System_Clock_Slow__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define System_Clock_Slow_CLKEN              (* (reg8 *) System_Clock_Slow__PM_ACT_CFG)
#define System_Clock_Slow_CLKEN_PTR          ((reg8 *) System_Clock_Slow__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define System_Clock_Slow_CLKSTBY            (* (reg8 *) System_Clock_Slow__PM_STBY_CFG)
#define System_Clock_Slow_CLKSTBY_PTR        ((reg8 *) System_Clock_Slow__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define System_Clock_Slow_DIV_LSB            (* (reg8 *) System_Clock_Slow__CFG0)
#define System_Clock_Slow_DIV_LSB_PTR        ((reg8 *) System_Clock_Slow__CFG0)
#define System_Clock_Slow_DIV_PTR            ((reg16 *) System_Clock_Slow__CFG0)

/* Clock MSB divider configuration register. */
#define System_Clock_Slow_DIV_MSB            (* (reg8 *) System_Clock_Slow__CFG1)
#define System_Clock_Slow_DIV_MSB_PTR        ((reg8 *) System_Clock_Slow__CFG1)

/* Mode and source configuration register */
#define System_Clock_Slow_MOD_SRC            (* (reg8 *) System_Clock_Slow__CFG2)
#define System_Clock_Slow_MOD_SRC_PTR        ((reg8 *) System_Clock_Slow__CFG2)

#if defined(System_Clock_Slow__CFG3)
/* Analog clock phase configuration register */
#define System_Clock_Slow_PHASE              (* (reg8 *) System_Clock_Slow__CFG3)
#define System_Clock_Slow_PHASE_PTR          ((reg8 *) System_Clock_Slow__CFG3)
#endif /* defined(System_Clock_Slow__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define System_Clock_Slow_CLKEN_MASK         System_Clock_Slow__PM_ACT_MSK
#define System_Clock_Slow_CLKSTBY_MASK       System_Clock_Slow__PM_STBY_MSK

/* CFG2 field masks */
#define System_Clock_Slow_SRC_SEL_MSK        System_Clock_Slow__CFG2_SRC_SEL_MASK
#define System_Clock_Slow_MODE_MASK          (~(System_Clock_Slow_SRC_SEL_MSK))

#if defined(System_Clock_Slow__CFG3)
/* CFG3 phase mask */
#define System_Clock_Slow_PHASE_MASK         System_Clock_Slow__CFG3_PHASE_DLY_MASK
#endif /* defined(System_Clock_Slow__CFG3) */

#endif /* CY_CLOCK_System_Clock_Slow_H */


/* [] END OF FILE */
