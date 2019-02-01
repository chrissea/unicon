/*******************************************************************************
* File Name: count_time_from_first_edge.h  
* Version 3.0
*
*  Description:
*   Contains the function prototypes and constants available to the counter
*   user module.
*
*   Note:
*    None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
    
#if !defined(CY_COUNTER_count_time_from_first_edge_H)
#define CY_COUNTER_count_time_from_first_edge_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 count_time_from_first_edge_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Counter_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */

/* Error message for removed count_time_from_first_edge_CounterUDB_sCTRLReg_ctrlreg through optimization */
#ifdef count_time_from_first_edge_CounterUDB_sCTRLReg_ctrlreg__REMOVED
    #error Counter_v3_0 detected with a constant 0 for the enable, a \
                                constant 0 for the count or constant 1 for \
                                the reset. This will prevent the component from\
                                operating.
#endif /* count_time_from_first_edge_CounterUDB_sCTRLReg_ctrlreg__REMOVED */


/**************************************
*           Parameter Defaults        
**************************************/

#define count_time_from_first_edge_Resolution            16u
#define count_time_from_first_edge_UsingFixedFunction    1u
#define count_time_from_first_edge_ControlRegRemoved     0u
#define count_time_from_first_edge_COMPARE_MODE_SOFTWARE 0u
#define count_time_from_first_edge_CAPTURE_MODE_SOFTWARE 0u
#define count_time_from_first_edge_RunModeUsed           1u


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Mode API Support
 * Backup structure for Sleep Wake up operations
 *************************************************************************/
typedef struct
{
    uint8 CounterEnableState; 
    uint16 CounterUdb;         /* Current Counter Value */

    #if (!count_time_from_first_edge_ControlRegRemoved)
        uint8 CounterControlRegister;               /* Counter Control Register */
    #endif /* (!count_time_from_first_edge_ControlRegRemoved) */

}count_time_from_first_edge_backupStruct;


/**************************************
 *  Function Prototypes
 *************************************/
void    count_time_from_first_edge_Start(void) ;
void    count_time_from_first_edge_Stop(void) ;
void    count_time_from_first_edge_SetInterruptMode(uint8 interruptsMask) ;
uint8   count_time_from_first_edge_ReadStatusRegister(void) ;
#define count_time_from_first_edge_GetInterruptSource() count_time_from_first_edge_ReadStatusRegister()
#if(!count_time_from_first_edge_ControlRegRemoved)
    uint8   count_time_from_first_edge_ReadControlRegister(void) ;
    void    count_time_from_first_edge_WriteControlRegister(uint8 control) \
        ;
#endif /* (!count_time_from_first_edge_ControlRegRemoved) */
#if (!(count_time_from_first_edge_UsingFixedFunction && (CY_PSOC5A)))
    void    count_time_from_first_edge_WriteCounter(uint16 counter) \
            ; 
#endif /* (!(count_time_from_first_edge_UsingFixedFunction && (CY_PSOC5A))) */
uint16  count_time_from_first_edge_ReadCounter(void) ;
uint16  count_time_from_first_edge_ReadCapture(void) ;
void    count_time_from_first_edge_WritePeriod(uint16 period) \
    ;
uint16  count_time_from_first_edge_ReadPeriod( void ) ;
#if (!count_time_from_first_edge_UsingFixedFunction)
    void    count_time_from_first_edge_WriteCompare(uint16 compare) \
        ;
    uint16  count_time_from_first_edge_ReadCompare( void ) \
        ;
#endif /* (!count_time_from_first_edge_UsingFixedFunction) */

#if (count_time_from_first_edge_COMPARE_MODE_SOFTWARE)
    void    count_time_from_first_edge_SetCompareMode(uint8 compareMode) ;
#endif /* (count_time_from_first_edge_COMPARE_MODE_SOFTWARE) */
#if (count_time_from_first_edge_CAPTURE_MODE_SOFTWARE)
    void    count_time_from_first_edge_SetCaptureMode(uint8 captureMode) ;
#endif /* (count_time_from_first_edge_CAPTURE_MODE_SOFTWARE) */
void count_time_from_first_edge_ClearFIFO(void)     ;
void count_time_from_first_edge_Init(void)          ;
void count_time_from_first_edge_Enable(void)        ;
void count_time_from_first_edge_SaveConfig(void)    ;
void count_time_from_first_edge_RestoreConfig(void) ;
void count_time_from_first_edge_Sleep(void)         ;
void count_time_from_first_edge_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Counter__CompareModes, Used in Compare Mode retained for backward compatibility of tests*/
#define count_time_from_first_edge__B_COUNTER__LESS_THAN 1
#define count_time_from_first_edge__B_COUNTER__LESS_THAN_OR_EQUAL 2
#define count_time_from_first_edge__B_COUNTER__EQUAL 0
#define count_time_from_first_edge__B_COUNTER__GREATER_THAN 3
#define count_time_from_first_edge__B_COUNTER__GREATER_THAN_OR_EQUAL 4
#define count_time_from_first_edge__B_COUNTER__SOFTWARE 5

/* Enumerated Type Counter_CompareModes */
#define count_time_from_first_edge_CMP_MODE_LT 1u
#define count_time_from_first_edge_CMP_MODE_LTE 2u
#define count_time_from_first_edge_CMP_MODE_EQ 0u
#define count_time_from_first_edge_CMP_MODE_GT 3u
#define count_time_from_first_edge_CMP_MODE_GTE 4u
#define count_time_from_first_edge_CMP_MODE_SOFTWARE_CONTROLLED 5u

/* Enumerated Type B_Counter__CaptureModes, Used in Capture Mode retained for backward compatibility of tests*/
#define count_time_from_first_edge__B_COUNTER__NONE 0
#define count_time_from_first_edge__B_COUNTER__RISING_EDGE 1
#define count_time_from_first_edge__B_COUNTER__FALLING_EDGE 2
#define count_time_from_first_edge__B_COUNTER__EITHER_EDGE 3
#define count_time_from_first_edge__B_COUNTER__SOFTWARE_CONTROL 4

/* Enumerated Type Counter_CompareModes */
#define count_time_from_first_edge_CAP_MODE_NONE 0u
#define count_time_from_first_edge_CAP_MODE_RISE 1u
#define count_time_from_first_edge_CAP_MODE_FALL 2u
#define count_time_from_first_edge_CAP_MODE_BOTH 3u
#define count_time_from_first_edge_CAP_MODE_SOFTWARE_CONTROLLED 4u


/***************************************
 *  Initialization Values
 **************************************/
#define count_time_from_first_edge_CAPTURE_MODE_CONF       0u
#define count_time_from_first_edge_INIT_PERIOD_VALUE       720u
#define count_time_from_first_edge_INIT_COUNTER_VALUE      720u
#if (count_time_from_first_edge_UsingFixedFunction)
#define count_time_from_first_edge_INIT_INTERRUPTS_MASK    ((uint8)((uint8)0u << count_time_from_first_edge_STATUS_ZERO_INT_EN_MASK_SHIFT))
#else
#define count_time_from_first_edge_INIT_COMPARE_VALUE      0u
#define count_time_from_first_edge_INIT_INTERRUPTS_MASK ((uint8)((uint8)0u << count_time_from_first_edge_STATUS_ZERO_INT_EN_MASK_SHIFT) | \
        ((uint8)((uint8)0u << count_time_from_first_edge_STATUS_CAPTURE_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << count_time_from_first_edge_STATUS_CMP_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << count_time_from_first_edge_STATUS_OVERFLOW_INT_EN_MASK_SHIFT)) | \
        ((uint8)((uint8)0u << count_time_from_first_edge_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT)))
#define count_time_from_first_edge_DEFAULT_COMPARE_MODE    0u

#if( 0 != count_time_from_first_edge_CAPTURE_MODE_CONF)
    #define count_time_from_first_edge_DEFAULT_CAPTURE_MODE    ((uint8)((uint8)0u << count_time_from_first_edge_CTRL_CAPMODE0_SHIFT))
#else    
    #define count_time_from_first_edge_DEFAULT_CAPTURE_MODE    (0u )
#endif /* ( 0 != count_time_from_first_edge_CAPTURE_MODE_CONF) */

#endif /* (count_time_from_first_edge_UsingFixedFunction) */


/**************************************
 *  Registers
 *************************************/
#if (count_time_from_first_edge_UsingFixedFunction)
    #define count_time_from_first_edge_STATICCOUNT_LSB     (*(reg16 *) count_time_from_first_edge_CounterHW__CAP0 )
    #define count_time_from_first_edge_STATICCOUNT_LSB_PTR ( (reg16 *) count_time_from_first_edge_CounterHW__CAP0 )
    #define count_time_from_first_edge_PERIOD_LSB          (*(reg16 *) count_time_from_first_edge_CounterHW__PER0 )
    #define count_time_from_first_edge_PERIOD_LSB_PTR      ( (reg16 *) count_time_from_first_edge_CounterHW__PER0 )
    /* MODE must be set to 1 to set the compare value */
    #define count_time_from_first_edge_COMPARE_LSB         (*(reg16 *) count_time_from_first_edge_CounterHW__CNT_CMP0 )
    #define count_time_from_first_edge_COMPARE_LSB_PTR     ( (reg16 *) count_time_from_first_edge_CounterHW__CNT_CMP0 )
    /* MODE must be set to 0 to get the count */
    #define count_time_from_first_edge_COUNTER_LSB         (*(reg16 *) count_time_from_first_edge_CounterHW__CNT_CMP0 )
    #define count_time_from_first_edge_COUNTER_LSB_PTR     ( (reg16 *) count_time_from_first_edge_CounterHW__CNT_CMP0 )
    #define count_time_from_first_edge_RT1                 (*(reg8 *) count_time_from_first_edge_CounterHW__RT1)
    #define count_time_from_first_edge_RT1_PTR             ( (reg8 *) count_time_from_first_edge_CounterHW__RT1)
#else
    
    #if (count_time_from_first_edge_Resolution <= 8u) /* 8-bit Counter */
    
        #define count_time_from_first_edge_STATICCOUNT_LSB     (*(reg8 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define count_time_from_first_edge_STATICCOUNT_LSB_PTR ( (reg8 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define count_time_from_first_edge_PERIOD_LSB          (*(reg8 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define count_time_from_first_edge_PERIOD_LSB_PTR      ( (reg8 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define count_time_from_first_edge_COMPARE_LSB         (*(reg8 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define count_time_from_first_edge_COMPARE_LSB_PTR     ( (reg8 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define count_time_from_first_edge_COUNTER_LSB         (*(reg8 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define count_time_from_first_edge_COUNTER_LSB_PTR     ( (reg8 *)\
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #elif(count_time_from_first_edge_Resolution <= 16u) /* 16-bit Counter */
        #if(CY_PSOC3) /* 8-bit address space */ 
            #define count_time_from_first_edge_STATICCOUNT_LSB     (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define count_time_from_first_edge_STATICCOUNT_LSB_PTR ( (reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define count_time_from_first_edge_PERIOD_LSB          (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define count_time_from_first_edge_PERIOD_LSB_PTR      ( (reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define count_time_from_first_edge_COMPARE_LSB         (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define count_time_from_first_edge_COMPARE_LSB_PTR     ( (reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define count_time_from_first_edge_COUNTER_LSB         (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define count_time_from_first_edge_COUNTER_LSB_PTR     ( (reg16 *)\
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define count_time_from_first_edge_STATICCOUNT_LSB     (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define count_time_from_first_edge_STATICCOUNT_LSB_PTR ( (reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_F0_REG )
            #define count_time_from_first_edge_PERIOD_LSB          (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define count_time_from_first_edge_PERIOD_LSB_PTR      ( (reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_D0_REG )
            #define count_time_from_first_edge_COMPARE_LSB         (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define count_time_from_first_edge_COMPARE_LSB_PTR     ( (reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_D1_REG )
            #define count_time_from_first_edge_COUNTER_LSB         (*(reg16 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )  
            #define count_time_from_first_edge_COUNTER_LSB_PTR     ( (reg16 *)\
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */   
    #elif(count_time_from_first_edge_Resolution <= 24u) /* 24-bit Counter */
        
        #define count_time_from_first_edge_STATICCOUNT_LSB     (*(reg32 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define count_time_from_first_edge_STATICCOUNT_LSB_PTR ( (reg32 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
        #define count_time_from_first_edge_PERIOD_LSB          (*(reg32 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define count_time_from_first_edge_PERIOD_LSB_PTR      ( (reg32 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
        #define count_time_from_first_edge_COMPARE_LSB         (*(reg32 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define count_time_from_first_edge_COMPARE_LSB_PTR     ( (reg32 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
        #define count_time_from_first_edge_COUNTER_LSB         (*(reg32 *) \
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )  
        #define count_time_from_first_edge_COUNTER_LSB_PTR     ( (reg32 *)\
            count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )
    
    #else /* 32-bit Counter */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define count_time_from_first_edge_STATICCOUNT_LSB     (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define count_time_from_first_edge_STATICCOUNT_LSB_PTR ( (reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__F0_REG )
            #define count_time_from_first_edge_PERIOD_LSB          (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define count_time_from_first_edge_PERIOD_LSB_PTR      ( (reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D0_REG )
            #define count_time_from_first_edge_COMPARE_LSB         (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define count_time_from_first_edge_COMPARE_LSB_PTR     ( (reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__D1_REG )
            #define count_time_from_first_edge_COUNTER_LSB         (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )  
            #define count_time_from_first_edge_COUNTER_LSB_PTR     ( (reg32 *)\
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define count_time_from_first_edge_STATICCOUNT_LSB     (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define count_time_from_first_edge_STATICCOUNT_LSB_PTR ( (reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_F0_REG )
            #define count_time_from_first_edge_PERIOD_LSB          (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define count_time_from_first_edge_PERIOD_LSB_PTR      ( (reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_D0_REG )
            #define count_time_from_first_edge_COMPARE_LSB         (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define count_time_from_first_edge_COMPARE_LSB_PTR     ( (reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_D1_REG )
            #define count_time_from_first_edge_COUNTER_LSB         (*(reg32 *) \
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )  
            #define count_time_from_first_edge_COUNTER_LSB_PTR     ( (reg32 *)\
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */   
    #endif

	#define count_time_from_first_edge_COUNTER_LSB_PTR_8BIT     ( (reg8 *)\
                count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__A0_REG )
				
    #define count_time_from_first_edge_AUX_CONTROLDP0 \
        (*(reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #define count_time_from_first_edge_AUX_CONTROLDP0_PTR \
        ( (reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u0__DP_AUX_CTL_REG)
    
    #if (count_time_from_first_edge_Resolution == 16 || count_time_from_first_edge_Resolution == 24 || count_time_from_first_edge_Resolution == 32)
       #define count_time_from_first_edge_AUX_CONTROLDP1 \
           (*(reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
       #define count_time_from_first_edge_AUX_CONTROLDP1_PTR \
           ( (reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u1__DP_AUX_CTL_REG)
    #endif /* (count_time_from_first_edge_Resolution == 16 || count_time_from_first_edge_Resolution == 24 || count_time_from_first_edge_Resolution == 32) */
    
    #if (count_time_from_first_edge_Resolution == 24 || count_time_from_first_edge_Resolution == 32)
       #define count_time_from_first_edge_AUX_CONTROLDP2 \
           (*(reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
       #define count_time_from_first_edge_AUX_CONTROLDP2_PTR \
           ( (reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u2__DP_AUX_CTL_REG)
    #endif /* (count_time_from_first_edge_Resolution == 24 || count_time_from_first_edge_Resolution == 32) */
    
    #if (count_time_from_first_edge_Resolution == 32)
       #define count_time_from_first_edge_AUX_CONTROLDP3 \
           (*(reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
       #define count_time_from_first_edge_AUX_CONTROLDP3_PTR \
           ( (reg8 *) count_time_from_first_edge_CounterUDB_sC16_counterdp_u3__DP_AUX_CTL_REG)
    #endif /* (count_time_from_first_edge_Resolution == 32) */

#endif  /* (count_time_from_first_edge_UsingFixedFunction) */

#if (count_time_from_first_edge_UsingFixedFunction)
    #define count_time_from_first_edge_STATUS         (*(reg8 *) count_time_from_first_edge_CounterHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define count_time_from_first_edge_STATUS_MASK             (*(reg8 *) count_time_from_first_edge_CounterHW__SR0 )
    #define count_time_from_first_edge_STATUS_MASK_PTR         ( (reg8 *) count_time_from_first_edge_CounterHW__SR0 )
    #define count_time_from_first_edge_CONTROL                 (*(reg8 *) count_time_from_first_edge_CounterHW__CFG0)
    #define count_time_from_first_edge_CONTROL_PTR             ( (reg8 *) count_time_from_first_edge_CounterHW__CFG0)
    #define count_time_from_first_edge_CONTROL2                (*(reg8 *) count_time_from_first_edge_CounterHW__CFG1)
    #define count_time_from_first_edge_CONTROL2_PTR            ( (reg8 *) count_time_from_first_edge_CounterHW__CFG1)
    #if (CY_PSOC3 || CY_PSOC5LP)
        #define count_time_from_first_edge_CONTROL3       (*(reg8 *) count_time_from_first_edge_CounterHW__CFG2)
        #define count_time_from_first_edge_CONTROL3_PTR   ( (reg8 *) count_time_from_first_edge_CounterHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define count_time_from_first_edge_GLOBAL_ENABLE           (*(reg8 *) count_time_from_first_edge_CounterHW__PM_ACT_CFG)
    #define count_time_from_first_edge_GLOBAL_ENABLE_PTR       ( (reg8 *) count_time_from_first_edge_CounterHW__PM_ACT_CFG)
    #define count_time_from_first_edge_GLOBAL_STBY_ENABLE      (*(reg8 *) count_time_from_first_edge_CounterHW__PM_STBY_CFG)
    #define count_time_from_first_edge_GLOBAL_STBY_ENABLE_PTR  ( (reg8 *) count_time_from_first_edge_CounterHW__PM_STBY_CFG)
    

    /********************************
    *    Constants
    ********************************/

    /* Fixed Function Block Chosen */
    #define count_time_from_first_edge_BLOCK_EN_MASK          count_time_from_first_edge_CounterHW__PM_ACT_MSK
    #define count_time_from_first_edge_BLOCK_STBY_EN_MASK     count_time_from_first_edge_CounterHW__PM_STBY_MSK 
    
    /* Control Register Bit Locations */    
    /* As defined in Register Map, part of TMRX_CFG0 register */
    #define count_time_from_first_edge_CTRL_ENABLE_SHIFT      0x00u
    #define count_time_from_first_edge_ONESHOT_SHIFT          0x02u
    /* Control Register Bit Masks */
    #define count_time_from_first_edge_CTRL_ENABLE            ((uint8)((uint8)0x01u << count_time_from_first_edge_CTRL_ENABLE_SHIFT))         
    #define count_time_from_first_edge_ONESHOT                ((uint8)((uint8)0x01u << count_time_from_first_edge_ONESHOT_SHIFT))

    /* Control2 Register Bit Masks */
    /* Set the mask for run mode */
    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        #define count_time_from_first_edge_CTRL_MODE_SHIFT        0x01u    
        #define count_time_from_first_edge_CTRL_MODE_MASK         ((uint8)((uint8)0x07u << count_time_from_first_edge_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Use CFG2 Mode bits to set run mode */
        #define count_time_from_first_edge_CTRL_MODE_SHIFT        0x00u    
        #define count_time_from_first_edge_CTRL_MODE_MASK         ((uint8)((uint8)0x03u << count_time_from_first_edge_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    /* Set the mask for interrupt (raw/status register) */
    #define count_time_from_first_edge_CTRL2_IRQ_SEL_SHIFT     0x00u
    #define count_time_from_first_edge_CTRL2_IRQ_SEL          ((uint8)((uint8)0x01u << count_time_from_first_edge_CTRL2_IRQ_SEL_SHIFT))     
    
    /* Status Register Bit Locations */
    #define count_time_from_first_edge_STATUS_ZERO_SHIFT      0x07u  /* As defined in Register Map, part of TMRX_SR0 register */ 

    /* Status Register Interrupt Enable Bit Locations */
    #define count_time_from_first_edge_STATUS_ZERO_INT_EN_MASK_SHIFT      (count_time_from_first_edge_STATUS_ZERO_SHIFT - 0x04u)

    /* Status Register Bit Masks */                           
    #define count_time_from_first_edge_STATUS_ZERO            ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_ZERO_SHIFT))

    /* Status Register Interrupt Bit Masks*/
    #define count_time_from_first_edge_STATUS_ZERO_INT_EN_MASK       ((uint8)((uint8)count_time_from_first_edge_STATUS_ZERO >> 0x04u))
    
    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define count_time_from_first_edge_RT1_SHIFT            0x04u
    #define count_time_from_first_edge_RT1_MASK             ((uint8)((uint8)0x03u << count_time_from_first_edge_RT1_SHIFT))  /* Sync TC and CMP bit masks */
    #define count_time_from_first_edge_SYNC                 ((uint8)((uint8)0x03u << count_time_from_first_edge_RT1_SHIFT))
    #define count_time_from_first_edge_SYNCDSI_SHIFT        0x00u
    #define count_time_from_first_edge_SYNCDSI_MASK         ((uint8)((uint8)0x0Fu << count_time_from_first_edge_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    #define count_time_from_first_edge_SYNCDSI_EN           ((uint8)((uint8)0x0Fu << count_time_from_first_edge_SYNCDSI_SHIFT)) /* Sync all DSI inputs */
    
#else /* !count_time_from_first_edge_UsingFixedFunction */
    #define count_time_from_first_edge_STATUS               (* (reg8 *) count_time_from_first_edge_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define count_time_from_first_edge_STATUS_PTR           (  (reg8 *) count_time_from_first_edge_CounterUDB_sSTSReg_stsreg__STATUS_REG )
    #define count_time_from_first_edge_STATUS_MASK          (* (reg8 *) count_time_from_first_edge_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define count_time_from_first_edge_STATUS_MASK_PTR      (  (reg8 *) count_time_from_first_edge_CounterUDB_sSTSReg_stsreg__MASK_REG )
    #define count_time_from_first_edge_STATUS_AUX_CTRL      (*(reg8 *) count_time_from_first_edge_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define count_time_from_first_edge_STATUS_AUX_CTRL_PTR  ( (reg8 *) count_time_from_first_edge_CounterUDB_sSTSReg_stsreg__STATUS_AUX_CTL_REG)
    #define count_time_from_first_edge_CONTROL              (* (reg8 *) count_time_from_first_edge_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )
    #define count_time_from_first_edge_CONTROL_PTR          (  (reg8 *) count_time_from_first_edge_CounterUDB_sCTRLReg_ctrlreg__CONTROL_REG )


    /********************************
    *    Constants
    ********************************/
    /* Control Register Bit Locations */
    #define count_time_from_first_edge_CTRL_CAPMODE0_SHIFT    0x03u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_CTRL_RESET_SHIFT       0x06u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_CTRL_ENABLE_SHIFT      0x07u       /* As defined by Verilog Implementation */
    /* Control Register Bit Masks */
    #define count_time_from_first_edge_CTRL_CMPMODE_MASK      0x07u 
    #define count_time_from_first_edge_CTRL_CAPMODE_MASK      0x03u  
    #define count_time_from_first_edge_CTRL_RESET             ((uint8)((uint8)0x01u << count_time_from_first_edge_CTRL_RESET_SHIFT))  
    #define count_time_from_first_edge_CTRL_ENABLE            ((uint8)((uint8)0x01u << count_time_from_first_edge_CTRL_ENABLE_SHIFT)) 

    /* Status Register Bit Locations */
    #define count_time_from_first_edge_STATUS_CMP_SHIFT       0x00u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_STATUS_ZERO_SHIFT      0x01u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_STATUS_OVERFLOW_SHIFT  0x02u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_STATUS_UNDERFLOW_SHIFT 0x03u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_STATUS_CAPTURE_SHIFT   0x04u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_STATUS_FIFOFULL_SHIFT  0x05u       /* As defined by Verilog Implementation */
    #define count_time_from_first_edge_STATUS_FIFONEMP_SHIFT  0x06u       /* As defined by Verilog Implementation */
    /* Status Register Interrupt Enable Bit Locations - UDB Status Interrupt Mask match Status Bit Locations*/
    #define count_time_from_first_edge_STATUS_CMP_INT_EN_MASK_SHIFT       count_time_from_first_edge_STATUS_CMP_SHIFT       
    #define count_time_from_first_edge_STATUS_ZERO_INT_EN_MASK_SHIFT      count_time_from_first_edge_STATUS_ZERO_SHIFT      
    #define count_time_from_first_edge_STATUS_OVERFLOW_INT_EN_MASK_SHIFT  count_time_from_first_edge_STATUS_OVERFLOW_SHIFT  
    #define count_time_from_first_edge_STATUS_UNDERFLOW_INT_EN_MASK_SHIFT count_time_from_first_edge_STATUS_UNDERFLOW_SHIFT 
    #define count_time_from_first_edge_STATUS_CAPTURE_INT_EN_MASK_SHIFT   count_time_from_first_edge_STATUS_CAPTURE_SHIFT   
    #define count_time_from_first_edge_STATUS_FIFOFULL_INT_EN_MASK_SHIFT  count_time_from_first_edge_STATUS_FIFOFULL_SHIFT  
    #define count_time_from_first_edge_STATUS_FIFONEMP_INT_EN_MASK_SHIFT  count_time_from_first_edge_STATUS_FIFONEMP_SHIFT  
    /* Status Register Bit Masks */                
    #define count_time_from_first_edge_STATUS_CMP             ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_CMP_SHIFT))  
    #define count_time_from_first_edge_STATUS_ZERO            ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_ZERO_SHIFT)) 
    #define count_time_from_first_edge_STATUS_OVERFLOW        ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_OVERFLOW_SHIFT)) 
    #define count_time_from_first_edge_STATUS_UNDERFLOW       ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_UNDERFLOW_SHIFT)) 
    #define count_time_from_first_edge_STATUS_CAPTURE         ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_CAPTURE_SHIFT)) 
    #define count_time_from_first_edge_STATUS_FIFOFULL        ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_FIFOFULL_SHIFT))
    #define count_time_from_first_edge_STATUS_FIFONEMP        ((uint8)((uint8)0x01u << count_time_from_first_edge_STATUS_FIFONEMP_SHIFT))
    /* Status Register Interrupt Bit Masks  - UDB Status Interrupt Mask match Status Bit Locations */
    #define count_time_from_first_edge_STATUS_CMP_INT_EN_MASK            count_time_from_first_edge_STATUS_CMP                    
    #define count_time_from_first_edge_STATUS_ZERO_INT_EN_MASK           count_time_from_first_edge_STATUS_ZERO            
    #define count_time_from_first_edge_STATUS_OVERFLOW_INT_EN_MASK       count_time_from_first_edge_STATUS_OVERFLOW        
    #define count_time_from_first_edge_STATUS_UNDERFLOW_INT_EN_MASK      count_time_from_first_edge_STATUS_UNDERFLOW       
    #define count_time_from_first_edge_STATUS_CAPTURE_INT_EN_MASK        count_time_from_first_edge_STATUS_CAPTURE         
    #define count_time_from_first_edge_STATUS_FIFOFULL_INT_EN_MASK       count_time_from_first_edge_STATUS_FIFOFULL        
    #define count_time_from_first_edge_STATUS_FIFONEMP_INT_EN_MASK       count_time_from_first_edge_STATUS_FIFONEMP         
    

    /* StatusI Interrupt Enable bit Location in the Auxilliary Control Register */
    #define count_time_from_first_edge_STATUS_ACTL_INT_EN     0x10u /* As defined for the ACTL Register */
    
    /* Datapath Auxillary Control Register definitions */
    #define count_time_from_first_edge_AUX_CTRL_FIFO0_CLR         0x01u   /* As defined by Register map */
    #define count_time_from_first_edge_AUX_CTRL_FIFO1_CLR         0x02u   /* As defined by Register map */
    #define count_time_from_first_edge_AUX_CTRL_FIFO0_LVL         0x04u   /* As defined by Register map */
    #define count_time_from_first_edge_AUX_CTRL_FIFO1_LVL         0x08u   /* As defined by Register map */
    #define count_time_from_first_edge_STATUS_ACTL_INT_EN_MASK    0x10u   /* As defined for the ACTL Register */
    
#endif /* count_time_from_first_edge_UsingFixedFunction */

#endif  /* CY_COUNTER_count_time_from_first_edge_H */


/* [] END OF FILE */

