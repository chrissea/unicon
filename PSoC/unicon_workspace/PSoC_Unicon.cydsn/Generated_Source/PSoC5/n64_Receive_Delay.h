/*******************************************************************************
* File Name: n64_Receive_Delay.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_n64_Receive_Delay_H)
#define CY_TIMER_n64_Receive_Delay_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 n64_Receive_Delay_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define n64_Receive_Delay_Resolution                 8u
#define n64_Receive_Delay_UsingFixedFunction         1u
#define n64_Receive_Delay_UsingHWCaptureCounter      0u
#define n64_Receive_Delay_SoftwareCaptureMode        0u
#define n64_Receive_Delay_SoftwareTriggerMode        0u
#define n64_Receive_Delay_UsingHWEnable              0u
#define n64_Receive_Delay_EnableTriggerMode          0u
#define n64_Receive_Delay_InterruptOnCaptureCount    0u
#define n64_Receive_Delay_RunModeUsed                1u
#define n64_Receive_Delay_ControlRegRemoved          0u

#if defined(n64_Receive_Delay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define n64_Receive_Delay_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (n64_Receive_Delay_UsingFixedFunction)
    #define n64_Receive_Delay_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define n64_Receive_Delay_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End n64_Receive_Delay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!n64_Receive_Delay_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (n64_Receive_Delay_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!n64_Receive_Delay_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}n64_Receive_Delay_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    n64_Receive_Delay_Start(void) ;
void    n64_Receive_Delay_Stop(void) ;

void    n64_Receive_Delay_SetInterruptMode(uint8 interruptMode) ;
uint8   n64_Receive_Delay_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define n64_Receive_Delay_GetInterruptSource() n64_Receive_Delay_ReadStatusRegister()

#if(!n64_Receive_Delay_UDB_CONTROL_REG_REMOVED)
    uint8   n64_Receive_Delay_ReadControlRegister(void) ;
    void    n64_Receive_Delay_WriteControlRegister(uint8 control) ;
#endif /* (!n64_Receive_Delay_UDB_CONTROL_REG_REMOVED) */

uint8  n64_Receive_Delay_ReadPeriod(void) ;
void    n64_Receive_Delay_WritePeriod(uint8 period) ;
uint8  n64_Receive_Delay_ReadCounter(void) ;
void    n64_Receive_Delay_WriteCounter(uint8 counter) ;
uint8  n64_Receive_Delay_ReadCapture(void) ;
void    n64_Receive_Delay_SoftwareCapture(void) ;

#if(!n64_Receive_Delay_UsingFixedFunction) /* UDB Prototypes */
    #if (n64_Receive_Delay_SoftwareCaptureMode)
        void    n64_Receive_Delay_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!n64_Receive_Delay_UsingFixedFunction) */

    #if (n64_Receive_Delay_SoftwareTriggerMode)
        void    n64_Receive_Delay_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (n64_Receive_Delay_SoftwareTriggerMode) */

    #if (n64_Receive_Delay_EnableTriggerMode)
        void    n64_Receive_Delay_EnableTrigger(void) ;
        void    n64_Receive_Delay_DisableTrigger(void) ;
    #endif /* (n64_Receive_Delay_EnableTriggerMode) */


    #if(n64_Receive_Delay_InterruptOnCaptureCount)
        void    n64_Receive_Delay_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (n64_Receive_Delay_InterruptOnCaptureCount) */

    #if (n64_Receive_Delay_UsingHWCaptureCounter)
        void    n64_Receive_Delay_SetCaptureCount(uint8 captureCount) ;
        uint8   n64_Receive_Delay_ReadCaptureCount(void) ;
    #endif /* (n64_Receive_Delay_UsingHWCaptureCounter) */

    void n64_Receive_Delay_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void n64_Receive_Delay_Init(void)          ;
void n64_Receive_Delay_Enable(void)        ;
void n64_Receive_Delay_SaveConfig(void)    ;
void n64_Receive_Delay_RestoreConfig(void) ;
void n64_Receive_Delay_Sleep(void)         ;
void n64_Receive_Delay_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define n64_Receive_Delay__B_TIMER__CM_NONE 0
#define n64_Receive_Delay__B_TIMER__CM_RISINGEDGE 1
#define n64_Receive_Delay__B_TIMER__CM_FALLINGEDGE 2
#define n64_Receive_Delay__B_TIMER__CM_EITHEREDGE 3
#define n64_Receive_Delay__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define n64_Receive_Delay__B_TIMER__TM_NONE 0x00u
#define n64_Receive_Delay__B_TIMER__TM_RISINGEDGE 0x04u
#define n64_Receive_Delay__B_TIMER__TM_FALLINGEDGE 0x08u
#define n64_Receive_Delay__B_TIMER__TM_EITHEREDGE 0x0Cu
#define n64_Receive_Delay__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define n64_Receive_Delay_INIT_PERIOD             28u
#define n64_Receive_Delay_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << n64_Receive_Delay_CTRL_CAP_MODE_SHIFT))
#define n64_Receive_Delay_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << n64_Receive_Delay_CTRL_TRIG_MODE_SHIFT))
#if (n64_Receive_Delay_UsingFixedFunction)
    #define n64_Receive_Delay_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << n64_Receive_Delay_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << n64_Receive_Delay_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define n64_Receive_Delay_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << n64_Receive_Delay_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << n64_Receive_Delay_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << n64_Receive_Delay_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (n64_Receive_Delay_UsingFixedFunction) */
#define n64_Receive_Delay_INIT_CAPTURE_COUNT      (2u)
#define n64_Receive_Delay_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << n64_Receive_Delay_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (n64_Receive_Delay_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define n64_Receive_Delay_STATUS         (*(reg8 *) n64_Receive_Delay_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define n64_Receive_Delay_STATUS_MASK    (*(reg8 *) n64_Receive_Delay_TimerHW__SR0 )
    #define n64_Receive_Delay_CONTROL        (*(reg8 *) n64_Receive_Delay_TimerHW__CFG0)
    #define n64_Receive_Delay_CONTROL2       (*(reg8 *) n64_Receive_Delay_TimerHW__CFG1)
    #define n64_Receive_Delay_CONTROL2_PTR   ( (reg8 *) n64_Receive_Delay_TimerHW__CFG1)
    #define n64_Receive_Delay_RT1            (*(reg8 *) n64_Receive_Delay_TimerHW__RT1)
    #define n64_Receive_Delay_RT1_PTR        ( (reg8 *) n64_Receive_Delay_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define n64_Receive_Delay_CONTROL3       (*(reg8 *) n64_Receive_Delay_TimerHW__CFG2)
        #define n64_Receive_Delay_CONTROL3_PTR   ( (reg8 *) n64_Receive_Delay_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define n64_Receive_Delay_GLOBAL_ENABLE  (*(reg8 *) n64_Receive_Delay_TimerHW__PM_ACT_CFG)
    #define n64_Receive_Delay_GLOBAL_STBY_ENABLE  (*(reg8 *) n64_Receive_Delay_TimerHW__PM_STBY_CFG)

    #define n64_Receive_Delay_CAPTURE_LSB         (* (reg16 *) n64_Receive_Delay_TimerHW__CAP0 )
    #define n64_Receive_Delay_CAPTURE_LSB_PTR       ((reg16 *) n64_Receive_Delay_TimerHW__CAP0 )
    #define n64_Receive_Delay_PERIOD_LSB          (* (reg16 *) n64_Receive_Delay_TimerHW__PER0 )
    #define n64_Receive_Delay_PERIOD_LSB_PTR        ((reg16 *) n64_Receive_Delay_TimerHW__PER0 )
    #define n64_Receive_Delay_COUNTER_LSB         (* (reg16 *) n64_Receive_Delay_TimerHW__CNT_CMP0 )
    #define n64_Receive_Delay_COUNTER_LSB_PTR       ((reg16 *) n64_Receive_Delay_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define n64_Receive_Delay_BLOCK_EN_MASK                     n64_Receive_Delay_TimerHW__PM_ACT_MSK
    #define n64_Receive_Delay_BLOCK_STBY_EN_MASK                n64_Receive_Delay_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define n64_Receive_Delay_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define n64_Receive_Delay_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define n64_Receive_Delay_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define n64_Receive_Delay_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define n64_Receive_Delay_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define n64_Receive_Delay_CTRL_ENABLE                        ((uint8)((uint8)0x01u << n64_Receive_Delay_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define n64_Receive_Delay_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define n64_Receive_Delay_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << n64_Receive_Delay_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define n64_Receive_Delay_CTRL_MODE_SHIFT                 0x01u
        #define n64_Receive_Delay_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << n64_Receive_Delay_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define n64_Receive_Delay_CTRL_RCOD_SHIFT        0x02u
        #define n64_Receive_Delay_CTRL_ENBL_SHIFT        0x00u
        #define n64_Receive_Delay_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define n64_Receive_Delay_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << n64_Receive_Delay_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define n64_Receive_Delay_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << n64_Receive_Delay_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define n64_Receive_Delay_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << n64_Receive_Delay_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define n64_Receive_Delay_CTRL_RCOD       ((uint8)((uint8)0x03u << n64_Receive_Delay_CTRL_RCOD_SHIFT))
        #define n64_Receive_Delay_CTRL_ENBL       ((uint8)((uint8)0x80u << n64_Receive_Delay_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define n64_Receive_Delay_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define n64_Receive_Delay_RT1_MASK                        ((uint8)((uint8)0x03u << n64_Receive_Delay_RT1_SHIFT))
    #define n64_Receive_Delay_SYNC                            ((uint8)((uint8)0x03u << n64_Receive_Delay_RT1_SHIFT))
    #define n64_Receive_Delay_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define n64_Receive_Delay_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << n64_Receive_Delay_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define n64_Receive_Delay_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << n64_Receive_Delay_SYNCDSI_SHIFT))

    #define n64_Receive_Delay_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << n64_Receive_Delay_CTRL_MODE_SHIFT))
    #define n64_Receive_Delay_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << n64_Receive_Delay_CTRL_MODE_SHIFT))
    #define n64_Receive_Delay_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << n64_Receive_Delay_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define n64_Receive_Delay_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define n64_Receive_Delay_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define n64_Receive_Delay_STATUS_TC_INT_MASK_SHIFT        (n64_Receive_Delay_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define n64_Receive_Delay_STATUS_CAPTURE_INT_MASK_SHIFT   (n64_Receive_Delay_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define n64_Receive_Delay_STATUS_TC                       ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_TC_SHIFT))
    #define n64_Receive_Delay_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define n64_Receive_Delay_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define n64_Receive_Delay_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define n64_Receive_Delay_STATUS              (* (reg8 *) n64_Receive_Delay_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define n64_Receive_Delay_STATUS_MASK         (* (reg8 *) n64_Receive_Delay_TimerUDB_rstSts_stsreg__MASK_REG)
    #define n64_Receive_Delay_STATUS_AUX_CTRL     (* (reg8 *) n64_Receive_Delay_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define n64_Receive_Delay_CONTROL             (* (reg8 *) n64_Receive_Delay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(n64_Receive_Delay_Resolution <= 8u) /* 8-bit Timer */
        #define n64_Receive_Delay_CAPTURE_LSB         (* (reg8 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define n64_Receive_Delay_CAPTURE_LSB_PTR       ((reg8 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define n64_Receive_Delay_PERIOD_LSB          (* (reg8 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define n64_Receive_Delay_PERIOD_LSB_PTR        ((reg8 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define n64_Receive_Delay_COUNTER_LSB         (* (reg8 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define n64_Receive_Delay_COUNTER_LSB_PTR       ((reg8 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(n64_Receive_Delay_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define n64_Receive_Delay_CAPTURE_LSB         (* (reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define n64_Receive_Delay_CAPTURE_LSB_PTR       ((reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define n64_Receive_Delay_PERIOD_LSB          (* (reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define n64_Receive_Delay_PERIOD_LSB_PTR        ((reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define n64_Receive_Delay_COUNTER_LSB         (* (reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define n64_Receive_Delay_COUNTER_LSB_PTR       ((reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define n64_Receive_Delay_CAPTURE_LSB         (* (reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define n64_Receive_Delay_CAPTURE_LSB_PTR       ((reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define n64_Receive_Delay_PERIOD_LSB          (* (reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define n64_Receive_Delay_PERIOD_LSB_PTR        ((reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define n64_Receive_Delay_COUNTER_LSB         (* (reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define n64_Receive_Delay_COUNTER_LSB_PTR       ((reg16 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(n64_Receive_Delay_Resolution <= 24u)/* 24-bit Timer */
        #define n64_Receive_Delay_CAPTURE_LSB         (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define n64_Receive_Delay_CAPTURE_LSB_PTR       ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define n64_Receive_Delay_PERIOD_LSB          (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define n64_Receive_Delay_PERIOD_LSB_PTR        ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define n64_Receive_Delay_COUNTER_LSB         (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define n64_Receive_Delay_COUNTER_LSB_PTR       ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define n64_Receive_Delay_CAPTURE_LSB         (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define n64_Receive_Delay_CAPTURE_LSB_PTR       ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define n64_Receive_Delay_PERIOD_LSB          (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define n64_Receive_Delay_PERIOD_LSB_PTR        ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define n64_Receive_Delay_COUNTER_LSB         (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define n64_Receive_Delay_COUNTER_LSB_PTR       ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define n64_Receive_Delay_CAPTURE_LSB         (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define n64_Receive_Delay_CAPTURE_LSB_PTR       ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define n64_Receive_Delay_PERIOD_LSB          (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define n64_Receive_Delay_PERIOD_LSB_PTR        ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define n64_Receive_Delay_COUNTER_LSB         (* (reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define n64_Receive_Delay_COUNTER_LSB_PTR       ((reg32 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define n64_Receive_Delay_COUNTER_LSB_PTR_8BIT       ((reg8 *) n64_Receive_Delay_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (n64_Receive_Delay_UsingHWCaptureCounter)
        #define n64_Receive_Delay_CAP_COUNT              (*(reg8 *) n64_Receive_Delay_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define n64_Receive_Delay_CAP_COUNT_PTR          ( (reg8 *) n64_Receive_Delay_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define n64_Receive_Delay_CAPTURE_COUNT_CTRL     (*(reg8 *) n64_Receive_Delay_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define n64_Receive_Delay_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) n64_Receive_Delay_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (n64_Receive_Delay_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define n64_Receive_Delay_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define n64_Receive_Delay_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << n64_Receive_Delay_CTRL_INTCNT_SHIFT))
    #define n64_Receive_Delay_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << n64_Receive_Delay_CTRL_TRIG_MODE_SHIFT))
    #define n64_Receive_Delay_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << n64_Receive_Delay_CTRL_TRIG_EN_SHIFT))
    #define n64_Receive_Delay_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << n64_Receive_Delay_CTRL_CAP_MODE_SHIFT))
    #define n64_Receive_Delay_CTRL_ENABLE                    ((uint8)((uint8)0x01u << n64_Receive_Delay_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define n64_Receive_Delay_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define n64_Receive_Delay_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_STATUS_TC_INT_MASK_SHIFT       n64_Receive_Delay_STATUS_TC_SHIFT
    #define n64_Receive_Delay_STATUS_CAPTURE_INT_MASK_SHIFT  n64_Receive_Delay_STATUS_CAPTURE_SHIFT
    #define n64_Receive_Delay_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define n64_Receive_Delay_STATUS_FIFOFULL_INT_MASK_SHIFT n64_Receive_Delay_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define n64_Receive_Delay_STATUS_TC                      ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define n64_Receive_Delay_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define n64_Receive_Delay_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define n64_Receive_Delay_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define n64_Receive_Delay_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define n64_Receive_Delay_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define n64_Receive_Delay_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << n64_Receive_Delay_STATUS_FIFOFULL_SHIFT))

    #define n64_Receive_Delay_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define n64_Receive_Delay_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define n64_Receive_Delay_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define n64_Receive_Delay_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define n64_Receive_Delay_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define n64_Receive_Delay_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_n64_Receive_Delay_H */


/* [] END OF FILE */
