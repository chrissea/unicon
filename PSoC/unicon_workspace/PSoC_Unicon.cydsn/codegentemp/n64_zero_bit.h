/*******************************************************************************
* File Name: n64_zero_bit.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_n64_zero_bit_H)
#define CY_SHIFTREG_n64_zero_bit_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define n64_zero_bit_FIFO_SIZE          (4u)
#define n64_zero_bit_USE_INPUT_FIFO     (0u)
#define n64_zero_bit_USE_OUTPUT_FIFO    (0u)
#define n64_zero_bit_SR_SIZE            (4u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint8 saveSrA0Reg;
    uint8 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint8 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} n64_zero_bit_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  n64_zero_bit_Start(void)                              ;
void  n64_zero_bit_Stop(void)                               ;
void  n64_zero_bit_Init(void)                               ;
void  n64_zero_bit_Enable(void)                             ;
void  n64_zero_bit_RestoreConfig(void)                      ;
void  n64_zero_bit_SaveConfig(void)                         ;
void  n64_zero_bit_Sleep(void)                              ;
void  n64_zero_bit_Wakeup(void)                             ;
void  n64_zero_bit_EnableInt(void)                          ;
void  n64_zero_bit_DisableInt(void)                         ;
void  n64_zero_bit_SetIntMode(uint8 interruptSource)        ;
uint8 n64_zero_bit_GetIntStatus(void)                       ;
void  n64_zero_bit_WriteRegValue(uint8 shiftData) \
                                                                ;
uint8 n64_zero_bit_ReadRegValue(void) ;
uint8    n64_zero_bit_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != n64_zero_bit_USE_INPUT_FIFO)
    cystatus n64_zero_bit_WriteData(uint8 shiftData) \
                                                                ;
#endif /* (0u != n64_zero_bit_USE_INPUT_FIFO) */

#if(0u != n64_zero_bit_USE_OUTPUT_FIFO)
    uint8 n64_zero_bit_ReadData(void) ;
#endif /* (0u != n64_zero_bit_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 n64_zero_bit_initVar;


/***************************************
*           API Constants
***************************************/

#define n64_zero_bit_LOAD                   (0x01u)
#define n64_zero_bit_STORE                  (0x02u)
#define n64_zero_bit_RESET                  (0x04u)

#define n64_zero_bit_IN_FIFO                (0x01u)
#define n64_zero_bit_OUT_FIFO               (0x02u)

#define n64_zero_bit_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define n64_zero_bit_RET_FIFO_NOT_EMPTY     (0x01u)

#define n64_zero_bit_RET_FIFO_PARTIAL       (0x01u)
#define n64_zero_bit_RET_FIFO_EMPTY         (0x02u)
#define n64_zero_bit_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define n64_zero_bit__LEFT 0
#define n64_zero_bit__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define n64_zero_bit_SR_MASK    (0xFu) /* Unsigned is added to parameter */
#define n64_zero_bit_INT_SRC    (1u)
#define n64_zero_bit_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define n64_zero_bit_SR_CONTROL_REG (* (reg8 *) \
                                           n64_zero_bit_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define n64_zero_bit_SR_CONTROL_PTR (  (reg8 *) \
                                           n64_zero_bit_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define n64_zero_bit_SR_STATUS_REG      (* (reg8 *) n64_zero_bit_bSR_StsReg__STATUS_REG)
#define n64_zero_bit_SR_STATUS_PTR      (  (reg8 *) n64_zero_bit_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define n64_zero_bit_SR_STATUS_MASK_REG (* (reg8 *) n64_zero_bit_bSR_StsReg__MASK_REG)
#define n64_zero_bit_SR_STATUS_MASK_PTR (  (reg8 *) n64_zero_bit_bSR_StsReg__MASK_REG)

/* Aux control register */
#define n64_zero_bit_SR_AUX_CONTROL_REG (* (reg8 *) n64_zero_bit_bSR_StsReg__STATUS_AUX_CTL_REG)
#define n64_zero_bit_SR_AUX_CONTROL_PTR (  (reg8 *) n64_zero_bit_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define n64_zero_bit_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define n64_zero_bit_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__F0_REG )

    #define n64_zero_bit_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__A0_REG )

    #define n64_zero_bit_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__A1_REG )

    #define n64_zero_bit_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__F1_REG )

#else
    #if(n64_zero_bit_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define n64_zero_bit_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define n64_zero_bit_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define n64_zero_bit_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define n64_zero_bit_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #elif(n64_zero_bit_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define n64_zero_bit_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__16BIT_F0_REG )

        #define n64_zero_bit_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__16BIT_A0_REG )

        #define n64_zero_bit_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__16BIT_A1_REG )

        #define n64_zero_bit_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(n64_zero_bit_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define n64_zero_bit_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__F0_REG )

        #define n64_zero_bit_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__A0_REG )

        #define n64_zero_bit_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__A1_REG )

        #define n64_zero_bit_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        n64_zero_bit_bSR_sC8_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define n64_zero_bit_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__32BIT_F0_REG )

        #define n64_zero_bit_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__32BIT_A0_REG )

        #define n64_zero_bit_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__32BIT_A1_REG )

        #define n64_zero_bit_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  n64_zero_bit_bSR_sC8_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (n64_zero_bit_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define n64_zero_bit_INTERRUPTS_ENABLE      (0x10u)
#define n64_zero_bit_LOAD_INT_EN            (0x01u)
#define n64_zero_bit_STORE_INT_EN           (0x02u)
#define n64_zero_bit_RESET_INT_EN           (0x04u)
#define n64_zero_bit_CLK_EN                 (0x01u)

#define n64_zero_bit_RESET_INT_EN_MASK      (0xFBu)
#define n64_zero_bit_LOAD_INT_EN_MASK       (0xFEu)
#define n64_zero_bit_STORE_INT_EN_MASK      (0xFDu)
#define n64_zero_bit_INTS_EN_MASK           (0x07u)

#define n64_zero_bit_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != n64_zero_bit_USE_INPUT_FIFO)

    #define n64_zero_bit_IN_FIFO_MASK       (0x18u)

    #define n64_zero_bit_IN_FIFO_FULL       (0x00u)
    #define n64_zero_bit_IN_FIFO_EMPTY      (0x01u)
    #define n64_zero_bit_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define n64_zero_bit_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != n64_zero_bit_USE_INPUT_FIFO) */

#define n64_zero_bit_OUT_FIFO_MASK          (0x60u)

#define n64_zero_bit_OUT_FIFO_EMPTY         (0x00u)
#define n64_zero_bit_OUT_FIFO_FULL          (0x01u)
#define n64_zero_bit_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define n64_zero_bit_OUT_FIFO_NOT_EMPTY     (0x02u)

#define n64_zero_bit_IN_FIFO_SHIFT_MASK     (0x03u)
#define n64_zero_bit_OUT_FIFO_SHIFT_MASK    (0x05u)

#define n64_zero_bit_DISABLED               (0u)
#define n64_zero_bit_DEFAULT_A0             (0u)
#define n64_zero_bit_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define n64_zero_bit_IS_ENABLED         (0u != (n64_zero_bit_SR_CONTROL & n64_zero_bit_CLK_EN))

#define n64_zero_bit_GET_OUT_FIFO_STS   ((n64_zero_bit_SR_STATUS & n64_zero_bit_OUT_FIFO_MASK) >> \
                                              n64_zero_bit_OUT_FIFO_SHIFT_MASK)

#define n64_zero_bit_GET_IN_FIFO_STS    ((n64_zero_bit_SR_STATUS & n64_zero_bit_IN_FIFO_MASK)  >> \
                                              n64_zero_bit_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define n64_zero_bit_SR_CONTROL     (n64_zero_bit_SR_CONTROL_REG)
#define n64_zero_bit_SR_STATUS      (n64_zero_bit_SR_STATUS_REG)
#define n64_zero_bit_SR_STATUS_MASK (n64_zero_bit_SR_STATUS_MASK_REG)
#define n64_zero_bit_SR_AUX_CONTROL (n64_zero_bit_SR_AUX_CONTROL_REG)

#define n64_zero_bit_IN_FIFO_SHFT_MASK  (n64_zero_bit_IN_FIFO_SHIFT_MASK)
#define n64_zero_bit_OUT_FIFO_SHFT_MASK (n64_zero_bit_OUT_FIFO_SHFIT_MASK)

#define n64_zero_bit_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_n64_zero_bit_H) */


/* [] END OF FILE */
