/*******************************************************************************
* File Name: Communication_State.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Communication_State_H) /* Pins Communication_State_H */
#define CY_PINS_Communication_State_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Communication_State_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Communication_State__PORT == 15 && ((Communication_State__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Communication_State_Write(uint8 value);
void    Communication_State_SetDriveMode(uint8 mode);
uint8   Communication_State_ReadDataReg(void);
uint8   Communication_State_Read(void);
void    Communication_State_SetInterruptMode(uint16 position, uint16 mode);
uint8   Communication_State_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Communication_State_SetDriveMode() function.
     *  @{
     */
        #define Communication_State_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Communication_State_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Communication_State_DM_RES_UP          PIN_DM_RES_UP
        #define Communication_State_DM_RES_DWN         PIN_DM_RES_DWN
        #define Communication_State_DM_OD_LO           PIN_DM_OD_LO
        #define Communication_State_DM_OD_HI           PIN_DM_OD_HI
        #define Communication_State_DM_STRONG          PIN_DM_STRONG
        #define Communication_State_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Communication_State_MASK               Communication_State__MASK
#define Communication_State_SHIFT              Communication_State__SHIFT
#define Communication_State_WIDTH              1u

/* Interrupt constants */
#if defined(Communication_State__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Communication_State_SetInterruptMode() function.
     *  @{
     */
        #define Communication_State_INTR_NONE      (uint16)(0x0000u)
        #define Communication_State_INTR_RISING    (uint16)(0x0001u)
        #define Communication_State_INTR_FALLING   (uint16)(0x0002u)
        #define Communication_State_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Communication_State_INTR_MASK      (0x01u) 
#endif /* (Communication_State__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Communication_State_PS                     (* (reg8 *) Communication_State__PS)
/* Data Register */
#define Communication_State_DR                     (* (reg8 *) Communication_State__DR)
/* Port Number */
#define Communication_State_PRT_NUM                (* (reg8 *) Communication_State__PRT) 
/* Connect to Analog Globals */                                                  
#define Communication_State_AG                     (* (reg8 *) Communication_State__AG)                       
/* Analog MUX bux enable */
#define Communication_State_AMUX                   (* (reg8 *) Communication_State__AMUX) 
/* Bidirectional Enable */                                                        
#define Communication_State_BIE                    (* (reg8 *) Communication_State__BIE)
/* Bit-mask for Aliased Register Access */
#define Communication_State_BIT_MASK               (* (reg8 *) Communication_State__BIT_MASK)
/* Bypass Enable */
#define Communication_State_BYP                    (* (reg8 *) Communication_State__BYP)
/* Port wide control signals */                                                   
#define Communication_State_CTL                    (* (reg8 *) Communication_State__CTL)
/* Drive Modes */
#define Communication_State_DM0                    (* (reg8 *) Communication_State__DM0) 
#define Communication_State_DM1                    (* (reg8 *) Communication_State__DM1)
#define Communication_State_DM2                    (* (reg8 *) Communication_State__DM2) 
/* Input Buffer Disable Override */
#define Communication_State_INP_DIS                (* (reg8 *) Communication_State__INP_DIS)
/* LCD Common or Segment Drive */
#define Communication_State_LCD_COM_SEG            (* (reg8 *) Communication_State__LCD_COM_SEG)
/* Enable Segment LCD */
#define Communication_State_LCD_EN                 (* (reg8 *) Communication_State__LCD_EN)
/* Slew Rate Control */
#define Communication_State_SLW                    (* (reg8 *) Communication_State__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Communication_State_PRTDSI__CAPS_SEL       (* (reg8 *) Communication_State__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Communication_State_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Communication_State__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Communication_State_PRTDSI__OE_SEL0        (* (reg8 *) Communication_State__PRTDSI__OE_SEL0) 
#define Communication_State_PRTDSI__OE_SEL1        (* (reg8 *) Communication_State__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Communication_State_PRTDSI__OUT_SEL0       (* (reg8 *) Communication_State__PRTDSI__OUT_SEL0) 
#define Communication_State_PRTDSI__OUT_SEL1       (* (reg8 *) Communication_State__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Communication_State_PRTDSI__SYNC_OUT       (* (reg8 *) Communication_State__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Communication_State__SIO_CFG)
    #define Communication_State_SIO_HYST_EN        (* (reg8 *) Communication_State__SIO_HYST_EN)
    #define Communication_State_SIO_REG_HIFREQ     (* (reg8 *) Communication_State__SIO_REG_HIFREQ)
    #define Communication_State_SIO_CFG            (* (reg8 *) Communication_State__SIO_CFG)
    #define Communication_State_SIO_DIFF           (* (reg8 *) Communication_State__SIO_DIFF)
#endif /* (Communication_State__SIO_CFG) */

/* Interrupt Registers */
#if defined(Communication_State__INTSTAT)
    #define Communication_State_INTSTAT            (* (reg8 *) Communication_State__INTSTAT)
    #define Communication_State_SNAP               (* (reg8 *) Communication_State__SNAP)
    
	#define Communication_State_0_INTTYPE_REG 		(* (reg8 *) Communication_State__0__INTTYPE)
#endif /* (Communication_State__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Communication_State_H */


/* [] END OF FILE */
