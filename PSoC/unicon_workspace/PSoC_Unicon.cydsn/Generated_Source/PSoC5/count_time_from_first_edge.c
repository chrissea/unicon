/*******************************************************************************
* File Name: count_time_from_first_edge.c  
* Version 3.0
*
*  Description:
*     The Counter component consists of a 8, 16, 24 or 32-bit counter with
*     a selectable period between 2 and 2^Width - 1.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "count_time_from_first_edge.h"

uint8 count_time_from_first_edge_initVar = 0u;


/*******************************************************************************
* Function Name: count_time_from_first_edge_Init
********************************************************************************
* Summary:
*     Initialize to the schematic state
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void count_time_from_first_edge_Init(void) 
{
        #if (!count_time_from_first_edge_UsingFixedFunction && !count_time_from_first_edge_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!count_time_from_first_edge_UsingFixedFunction && !count_time_from_first_edge_ControlRegRemoved) */
        
        #if(!count_time_from_first_edge_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 count_time_from_first_edge_interruptState;
        #endif /* (!count_time_from_first_edge_UsingFixedFunction) */
        
        #if (count_time_from_first_edge_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            count_time_from_first_edge_CONTROL &= count_time_from_first_edge_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                count_time_from_first_edge_CONTROL2 &= ((uint8)(~count_time_from_first_edge_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                count_time_from_first_edge_CONTROL3 &= ((uint8)(~count_time_from_first_edge_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (count_time_from_first_edge_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                count_time_from_first_edge_CONTROL |= count_time_from_first_edge_ONESHOT;
            #endif /* (count_time_from_first_edge_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            count_time_from_first_edge_CONTROL2 |= count_time_from_first_edge_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            count_time_from_first_edge_RT1 &= ((uint8)(~count_time_from_first_edge_RT1_MASK));
            count_time_from_first_edge_RT1 |= count_time_from_first_edge_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            count_time_from_first_edge_RT1 &= ((uint8)(~count_time_from_first_edge_SYNCDSI_MASK));
            count_time_from_first_edge_RT1 |= count_time_from_first_edge_SYNCDSI_EN;

        #else
            #if(!count_time_from_first_edge_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = count_time_from_first_edge_CONTROL & ((uint8)(~count_time_from_first_edge_CTRL_CMPMODE_MASK));
            count_time_from_first_edge_CONTROL = ctrl | count_time_from_first_edge_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = count_time_from_first_edge_CONTROL & ((uint8)(~count_time_from_first_edge_CTRL_CAPMODE_MASK));
            
            #if( 0 != count_time_from_first_edge_CAPTURE_MODE_CONF)
                count_time_from_first_edge_CONTROL = ctrl | count_time_from_first_edge_DEFAULT_CAPTURE_MODE;
            #else
                count_time_from_first_edge_CONTROL = ctrl;
            #endif /* 0 != count_time_from_first_edge_CAPTURE_MODE */ 
            
            #endif /* (!count_time_from_first_edge_ControlRegRemoved) */
        #endif /* (count_time_from_first_edge_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!count_time_from_first_edge_UsingFixedFunction)
            count_time_from_first_edge_ClearFIFO();
        #endif /* (!count_time_from_first_edge_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        count_time_from_first_edge_WritePeriod(count_time_from_first_edge_INIT_PERIOD_VALUE);
        #if (!(count_time_from_first_edge_UsingFixedFunction && (CY_PSOC5A)))
            count_time_from_first_edge_WriteCounter(count_time_from_first_edge_INIT_COUNTER_VALUE);
        #endif /* (!(count_time_from_first_edge_UsingFixedFunction && (CY_PSOC5A))) */
        count_time_from_first_edge_SetInterruptMode(count_time_from_first_edge_INIT_INTERRUPTS_MASK);
        
        #if (!count_time_from_first_edge_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)count_time_from_first_edge_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            count_time_from_first_edge_WriteCompare(count_time_from_first_edge_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            count_time_from_first_edge_interruptState = CyEnterCriticalSection();
            
            count_time_from_first_edge_STATUS_AUX_CTRL |= count_time_from_first_edge_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(count_time_from_first_edge_interruptState);
            
        #endif /* (!count_time_from_first_edge_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_Enable
********************************************************************************
* Summary:
*     Enable the Counter
* 
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: 
*   If the Enable mode is set to Hardware only then this function has no effect 
*   on the operation of the counter.
*
*******************************************************************************/
void count_time_from_first_edge_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (count_time_from_first_edge_UsingFixedFunction)
        count_time_from_first_edge_GLOBAL_ENABLE |= count_time_from_first_edge_BLOCK_EN_MASK;
        count_time_from_first_edge_GLOBAL_STBY_ENABLE |= count_time_from_first_edge_BLOCK_STBY_EN_MASK;
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!count_time_from_first_edge_ControlRegRemoved || count_time_from_first_edge_UsingFixedFunction)
        count_time_from_first_edge_CONTROL |= count_time_from_first_edge_CTRL_ENABLE;                
    #endif /* (!count_time_from_first_edge_ControlRegRemoved || count_time_from_first_edge_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_Start
********************************************************************************
* Summary:
*  Enables the counter for operation 
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Global variables:
*  count_time_from_first_edge_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void count_time_from_first_edge_Start(void) 
{
    if(count_time_from_first_edge_initVar == 0u)
    {
        count_time_from_first_edge_Init();
        
        count_time_from_first_edge_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    count_time_from_first_edge_Enable();        
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_Stop
********************************************************************************
* Summary:
* Halts the counter, but does not change any modes or disable interrupts.
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
* Side Effects: If the Enable mode is set to Hardware only then this function
*               has no effect on the operation of the counter.
*
*******************************************************************************/
void count_time_from_first_edge_Stop(void) 
{
    /* Disable Counter */
    #if(!count_time_from_first_edge_ControlRegRemoved || count_time_from_first_edge_UsingFixedFunction)
        count_time_from_first_edge_CONTROL &= ((uint8)(~count_time_from_first_edge_CTRL_ENABLE));        
    #endif /* (!count_time_from_first_edge_ControlRegRemoved || count_time_from_first_edge_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (count_time_from_first_edge_UsingFixedFunction)
        count_time_from_first_edge_GLOBAL_ENABLE &= ((uint8)(~count_time_from_first_edge_BLOCK_EN_MASK));
        count_time_from_first_edge_GLOBAL_STBY_ENABLE &= ((uint8)(~count_time_from_first_edge_BLOCK_STBY_EN_MASK));
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_SetInterruptMode
********************************************************************************
* Summary:
* Configures which interrupt sources are enabled to generate the final interrupt
*
* Parameters:  
*  InterruptsMask: This parameter is an or'd collection of the status bits
*                   which will be allowed to generate the counters interrupt.   
*
* Return: 
*  void
*
*******************************************************************************/
void count_time_from_first_edge_SetInterruptMode(uint8 interruptsMask) 
{
    count_time_from_first_edge_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_ReadStatusRegister
********************************************************************************
* Summary:
*   Reads the status register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the status register
*
* Side Effects:
*   Status register bits may be clear on read. 
*
*******************************************************************************/
uint8   count_time_from_first_edge_ReadStatusRegister(void) 
{
    return count_time_from_first_edge_STATUS;
}


#if(!count_time_from_first_edge_ControlRegRemoved)
/*******************************************************************************
* Function Name: count_time_from_first_edge_ReadControlRegister
********************************************************************************
* Summary:
*   Reads the control register and returns it's state. This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
uint8   count_time_from_first_edge_ReadControlRegister(void) 
{
    return count_time_from_first_edge_CONTROL;
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_WriteControlRegister
********************************************************************************
* Summary:
*   Sets the bit-field of the control register.  This function should use
*       defined types for the bit-field information as the bits in this
*       register may be permuteable.
*
* Parameters:  
*  void
*
* Return: 
*  (uint8) The contents of the control register
*
*******************************************************************************/
void    count_time_from_first_edge_WriteControlRegister(uint8 control) 
{
    count_time_from_first_edge_CONTROL = control;
}

#endif  /* (!count_time_from_first_edge_ControlRegRemoved) */


#if (!(count_time_from_first_edge_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: count_time_from_first_edge_WriteCounter
********************************************************************************
* Summary:
*   This funtion is used to set the counter to a specific value
*
* Parameters:  
*  counter:  New counter value. 
*
* Return: 
*  void 
*
*******************************************************************************/
void count_time_from_first_edge_WriteCounter(uint16 counter) \
                                   
{
    #if(count_time_from_first_edge_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (count_time_from_first_edge_GLOBAL_ENABLE & count_time_from_first_edge_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        count_time_from_first_edge_GLOBAL_ENABLE |= count_time_from_first_edge_BLOCK_EN_MASK;
        CY_SET_REG16(count_time_from_first_edge_COUNTER_LSB_PTR, (uint16)counter);
        count_time_from_first_edge_GLOBAL_ENABLE &= ((uint8)(~count_time_from_first_edge_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(count_time_from_first_edge_COUNTER_LSB_PTR, counter);
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */
}
#endif /* (!(count_time_from_first_edge_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: count_time_from_first_edge_ReadCounter
********************************************************************************
* Summary:
* Returns the current value of the counter.  It doesn't matter
* if the counter is enabled or running.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) The present value of the counter.
*
*******************************************************************************/
uint16 count_time_from_first_edge_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(count_time_from_first_edge_UsingFixedFunction)
		(void)CY_GET_REG16(count_time_from_first_edge_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(count_time_from_first_edge_COUNTER_LSB_PTR_8BIT);
	#endif/* (count_time_from_first_edge_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(count_time_from_first_edge_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(count_time_from_first_edge_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(count_time_from_first_edge_STATICCOUNT_LSB_PTR));
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_ReadCapture
********************************************************************************
* Summary:
*   This function returns the last value captured.
*
* Parameters:  
*  void
*
* Return: 
*  (uint16) Present Capture value.
*
*******************************************************************************/
uint16 count_time_from_first_edge_ReadCapture(void) 
{
    #if(count_time_from_first_edge_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(count_time_from_first_edge_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(count_time_from_first_edge_STATICCOUNT_LSB_PTR));
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_WritePeriod
********************************************************************************
* Summary:
* Changes the period of the counter.  The new period 
* will be loaded the next time terminal count is detected.
*
* Parameters:  
*  period: (uint16) A value of 0 will result in
*         the counter remaining at zero.  
*
* Return: 
*  void
*
*******************************************************************************/
void count_time_from_first_edge_WritePeriod(uint16 period) 
{
    #if(count_time_from_first_edge_UsingFixedFunction)
        CY_SET_REG16(count_time_from_first_edge_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(count_time_from_first_edge_PERIOD_LSB_PTR, period);
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_ReadPeriod
********************************************************************************
* Summary:
* Reads the current period value without affecting counter operation.
*
* Parameters:  
*  void:  
*
* Return: 
*  (uint16) Present period value.
*
*******************************************************************************/
uint16 count_time_from_first_edge_ReadPeriod(void) 
{
    #if(count_time_from_first_edge_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(count_time_from_first_edge_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(count_time_from_first_edge_PERIOD_LSB_PTR));
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */
}


#if (!count_time_from_first_edge_UsingFixedFunction)
/*******************************************************************************
* Function Name: count_time_from_first_edge_WriteCompare
********************************************************************************
* Summary:
* Changes the compare value.  The compare output will 
* reflect the new value on the next UDB clock.  The compare output will be 
* driven high when the present counter value compares true based on the 
* configured compare mode setting. 
*
* Parameters:  
*  Compare:  New compare value. 
*
* Return: 
*  void
*
*******************************************************************************/
void count_time_from_first_edge_WriteCompare(uint16 compare) \
                                   
{
    #if(count_time_from_first_edge_UsingFixedFunction)
        CY_SET_REG16(count_time_from_first_edge_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(count_time_from_first_edge_COMPARE_LSB_PTR, compare);
    #endif /* (count_time_from_first_edge_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_from_first_edge_ReadCompare
********************************************************************************
* Summary:
* Returns the compare value.
*
* Parameters:  
*  void:
*
* Return: 
*  (uint16) Present compare value.
*
*******************************************************************************/
uint16 count_time_from_first_edge_ReadCompare(void) 
{
    return (CY_GET_REG16(count_time_from_first_edge_COMPARE_LSB_PTR));
}


#if (count_time_from_first_edge_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: count_time_from_first_edge_SetCompareMode
********************************************************************************
* Summary:
*  Sets the software controlled Compare Mode.
*
* Parameters:
*  compareMode:  Compare Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void count_time_from_first_edge_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    count_time_from_first_edge_CONTROL &= ((uint8)(~count_time_from_first_edge_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    count_time_from_first_edge_CONTROL |= compareMode;
}
#endif  /* (count_time_from_first_edge_COMPARE_MODE_SOFTWARE) */


#if (count_time_from_first_edge_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: count_time_from_first_edge_SetCaptureMode
********************************************************************************
* Summary:
*  Sets the software controlled Capture Mode.
*
* Parameters:
*  captureMode:  Capture Mode Enumerated Type.
*
* Return:
*  void
*
*******************************************************************************/
void count_time_from_first_edge_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    count_time_from_first_edge_CONTROL &= ((uint8)(~count_time_from_first_edge_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    count_time_from_first_edge_CONTROL |= ((uint8)((uint8)captureMode << count_time_from_first_edge_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (count_time_from_first_edge_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: count_time_from_first_edge_ClearFIFO
********************************************************************************
* Summary:
*   This function clears all capture data from the capture FIFO
*
* Parameters:  
*  void:
*
* Return: 
*  None
*
*******************************************************************************/
void count_time_from_first_edge_ClearFIFO(void) 
{

    while(0u != (count_time_from_first_edge_ReadStatusRegister() & count_time_from_first_edge_STATUS_FIFONEMP))
    {
        (void)count_time_from_first_edge_ReadCapture();
    }

}
#endif  /* (!count_time_from_first_edge_UsingFixedFunction) */


/* [] END OF FILE */

