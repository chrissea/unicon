/*******************************************************************************
* File Name: comm_state_toggle_timer.c  
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

#include "comm_state_toggle_timer.h"

uint8 comm_state_toggle_timer_initVar = 0u;


/*******************************************************************************
* Function Name: comm_state_toggle_timer_Init
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
void comm_state_toggle_timer_Init(void) 
{
        #if (!comm_state_toggle_timer_UsingFixedFunction && !comm_state_toggle_timer_ControlRegRemoved)
            uint8 ctrl;
        #endif /* (!comm_state_toggle_timer_UsingFixedFunction && !comm_state_toggle_timer_ControlRegRemoved) */
        
        #if(!comm_state_toggle_timer_UsingFixedFunction) 
            /* Interrupt State Backup for Critical Region*/
            uint8 comm_state_toggle_timer_interruptState;
        #endif /* (!comm_state_toggle_timer_UsingFixedFunction) */
        
        #if (comm_state_toggle_timer_UsingFixedFunction)
            /* Clear all bits but the enable bit (if it's already set for Timer operation */
            comm_state_toggle_timer_CONTROL &= comm_state_toggle_timer_CTRL_ENABLE;
            
            /* Clear the mode bits for continuous run mode */
            #if (CY_PSOC5A)
                comm_state_toggle_timer_CONTROL2 &= ((uint8)(~comm_state_toggle_timer_CTRL_MODE_MASK));
            #endif /* (CY_PSOC5A) */
            #if (CY_PSOC3 || CY_PSOC5LP)
                comm_state_toggle_timer_CONTROL3 &= ((uint8)(~comm_state_toggle_timer_CTRL_MODE_MASK));                
            #endif /* (CY_PSOC3 || CY_PSOC5LP) */
            /* Check if One Shot mode is enabled i.e. RunMode !=0*/
            #if (comm_state_toggle_timer_RunModeUsed != 0x0u)
                /* Set 3rd bit of Control register to enable one shot mode */
                comm_state_toggle_timer_CONTROL |= comm_state_toggle_timer_ONESHOT;
            #endif /* (comm_state_toggle_timer_RunModeUsed != 0x0u) */
            
            /* Set the IRQ to use the status register interrupts */
            comm_state_toggle_timer_CONTROL2 |= comm_state_toggle_timer_CTRL2_IRQ_SEL;
            
            /* Clear and Set SYNCTC and SYNCCMP bits of RT1 register */
            comm_state_toggle_timer_RT1 &= ((uint8)(~comm_state_toggle_timer_RT1_MASK));
            comm_state_toggle_timer_RT1 |= comm_state_toggle_timer_SYNC;     
                    
            /*Enable DSI Sync all all inputs of the Timer*/
            comm_state_toggle_timer_RT1 &= ((uint8)(~comm_state_toggle_timer_SYNCDSI_MASK));
            comm_state_toggle_timer_RT1 |= comm_state_toggle_timer_SYNCDSI_EN;

        #else
            #if(!comm_state_toggle_timer_ControlRegRemoved)
            /* Set the default compare mode defined in the parameter */
            ctrl = comm_state_toggle_timer_CONTROL & ((uint8)(~comm_state_toggle_timer_CTRL_CMPMODE_MASK));
            comm_state_toggle_timer_CONTROL = ctrl | comm_state_toggle_timer_DEFAULT_COMPARE_MODE;
            
            /* Set the default capture mode defined in the parameter */
            ctrl = comm_state_toggle_timer_CONTROL & ((uint8)(~comm_state_toggle_timer_CTRL_CAPMODE_MASK));
            
            #if( 0 != comm_state_toggle_timer_CAPTURE_MODE_CONF)
                comm_state_toggle_timer_CONTROL = ctrl | comm_state_toggle_timer_DEFAULT_CAPTURE_MODE;
            #else
                comm_state_toggle_timer_CONTROL = ctrl;
            #endif /* 0 != comm_state_toggle_timer_CAPTURE_MODE */ 
            
            #endif /* (!comm_state_toggle_timer_ControlRegRemoved) */
        #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
        
        /* Clear all data in the FIFO's */
        #if (!comm_state_toggle_timer_UsingFixedFunction)
            comm_state_toggle_timer_ClearFIFO();
        #endif /* (!comm_state_toggle_timer_UsingFixedFunction) */
        
        /* Set Initial values from Configuration */
        comm_state_toggle_timer_WritePeriod(comm_state_toggle_timer_INIT_PERIOD_VALUE);
        #if (!(comm_state_toggle_timer_UsingFixedFunction && (CY_PSOC5A)))
            comm_state_toggle_timer_WriteCounter(comm_state_toggle_timer_INIT_COUNTER_VALUE);
        #endif /* (!(comm_state_toggle_timer_UsingFixedFunction && (CY_PSOC5A))) */
        comm_state_toggle_timer_SetInterruptMode(comm_state_toggle_timer_INIT_INTERRUPTS_MASK);
        
        #if (!comm_state_toggle_timer_UsingFixedFunction)
            /* Read the status register to clear the unwanted interrupts */
            (void)comm_state_toggle_timer_ReadStatusRegister();
            /* Set the compare value (only available to non-fixed function implementation */
            comm_state_toggle_timer_WriteCompare(comm_state_toggle_timer_INIT_COMPARE_VALUE);
            /* Use the interrupt output of the status register for IRQ output */
            
            /* CyEnterCriticalRegion and CyExitCriticalRegion are used to mark following region critical*/
            /* Enter Critical Region*/
            comm_state_toggle_timer_interruptState = CyEnterCriticalSection();
            
            comm_state_toggle_timer_STATUS_AUX_CTRL |= comm_state_toggle_timer_STATUS_ACTL_INT_EN_MASK;
            
            /* Exit Critical Region*/
            CyExitCriticalSection(comm_state_toggle_timer_interruptState);
            
        #endif /* (!comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_Enable
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
void comm_state_toggle_timer_Enable(void) 
{
    /* Globally Enable the Fixed Function Block chosen */
    #if (comm_state_toggle_timer_UsingFixedFunction)
        comm_state_toggle_timer_GLOBAL_ENABLE |= comm_state_toggle_timer_BLOCK_EN_MASK;
        comm_state_toggle_timer_GLOBAL_STBY_ENABLE |= comm_state_toggle_timer_BLOCK_STBY_EN_MASK;
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */  
        
    /* Enable the counter from the control register  */
    /* If Fixed Function then make sure Mode is set correctly */
    /* else make sure reset is clear */
    #if(!comm_state_toggle_timer_ControlRegRemoved || comm_state_toggle_timer_UsingFixedFunction)
        comm_state_toggle_timer_CONTROL |= comm_state_toggle_timer_CTRL_ENABLE;                
    #endif /* (!comm_state_toggle_timer_ControlRegRemoved || comm_state_toggle_timer_UsingFixedFunction) */
    
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_Start
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
*  comm_state_toggle_timer_initVar: Is modified when this function is called for the  
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void comm_state_toggle_timer_Start(void) 
{
    if(comm_state_toggle_timer_initVar == 0u)
    {
        comm_state_toggle_timer_Init();
        
        comm_state_toggle_timer_initVar = 1u; /* Clear this bit for Initialization */        
    }
    
    /* Enable the Counter */
    comm_state_toggle_timer_Enable();        
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_Stop
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
void comm_state_toggle_timer_Stop(void) 
{
    /* Disable Counter */
    #if(!comm_state_toggle_timer_ControlRegRemoved || comm_state_toggle_timer_UsingFixedFunction)
        comm_state_toggle_timer_CONTROL &= ((uint8)(~comm_state_toggle_timer_CTRL_ENABLE));        
    #endif /* (!comm_state_toggle_timer_ControlRegRemoved || comm_state_toggle_timer_UsingFixedFunction) */
    
    /* Globally disable the Fixed Function Block chosen */
    #if (comm_state_toggle_timer_UsingFixedFunction)
        comm_state_toggle_timer_GLOBAL_ENABLE &= ((uint8)(~comm_state_toggle_timer_BLOCK_EN_MASK));
        comm_state_toggle_timer_GLOBAL_STBY_ENABLE &= ((uint8)(~comm_state_toggle_timer_BLOCK_STBY_EN_MASK));
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_SetInterruptMode
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
void comm_state_toggle_timer_SetInterruptMode(uint8 interruptsMask) 
{
    comm_state_toggle_timer_STATUS_MASK = interruptsMask;
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_ReadStatusRegister
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
uint8   comm_state_toggle_timer_ReadStatusRegister(void) 
{
    return comm_state_toggle_timer_STATUS;
}


#if(!comm_state_toggle_timer_ControlRegRemoved)
/*******************************************************************************
* Function Name: comm_state_toggle_timer_ReadControlRegister
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
uint8   comm_state_toggle_timer_ReadControlRegister(void) 
{
    return comm_state_toggle_timer_CONTROL;
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_WriteControlRegister
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
void    comm_state_toggle_timer_WriteControlRegister(uint8 control) 
{
    comm_state_toggle_timer_CONTROL = control;
}

#endif  /* (!comm_state_toggle_timer_ControlRegRemoved) */


#if (!(comm_state_toggle_timer_UsingFixedFunction && (CY_PSOC5A)))
/*******************************************************************************
* Function Name: comm_state_toggle_timer_WriteCounter
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
void comm_state_toggle_timer_WriteCounter(uint16 counter) \
                                   
{
    #if(comm_state_toggle_timer_UsingFixedFunction)
        /* assert if block is already enabled */
        CYASSERT (0u == (comm_state_toggle_timer_GLOBAL_ENABLE & comm_state_toggle_timer_BLOCK_EN_MASK));
        /* If block is disabled, enable it and then write the counter */
        comm_state_toggle_timer_GLOBAL_ENABLE |= comm_state_toggle_timer_BLOCK_EN_MASK;
        CY_SET_REG16(comm_state_toggle_timer_COUNTER_LSB_PTR, (uint16)counter);
        comm_state_toggle_timer_GLOBAL_ENABLE &= ((uint8)(~comm_state_toggle_timer_BLOCK_EN_MASK));
    #else
        CY_SET_REG16(comm_state_toggle_timer_COUNTER_LSB_PTR, counter);
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
}
#endif /* (!(comm_state_toggle_timer_UsingFixedFunction && (CY_PSOC5A))) */


/*******************************************************************************
* Function Name: comm_state_toggle_timer_ReadCounter
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
uint16 comm_state_toggle_timer_ReadCounter(void) 
{
    /* Force capture by reading Accumulator */
    /* Must first do a software capture to be able to read the counter */
    /* It is up to the user code to make sure there isn't already captured data in the FIFO */
    #if(comm_state_toggle_timer_UsingFixedFunction)
		(void)CY_GET_REG16(comm_state_toggle_timer_COUNTER_LSB_PTR);
	#else
		(void)CY_GET_REG8(comm_state_toggle_timer_COUNTER_LSB_PTR_8BIT);
	#endif/* (comm_state_toggle_timer_UsingFixedFunction) */
    
    /* Read the data from the FIFO (or capture register for Fixed Function)*/
    #if(comm_state_toggle_timer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(comm_state_toggle_timer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(comm_state_toggle_timer_STATICCOUNT_LSB_PTR));
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_ReadCapture
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
uint16 comm_state_toggle_timer_ReadCapture(void) 
{
    #if(comm_state_toggle_timer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(comm_state_toggle_timer_STATICCOUNT_LSB_PTR));
    #else
        return (CY_GET_REG16(comm_state_toggle_timer_STATICCOUNT_LSB_PTR));
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_WritePeriod
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
void comm_state_toggle_timer_WritePeriod(uint16 period) 
{
    #if(comm_state_toggle_timer_UsingFixedFunction)
        CY_SET_REG16(comm_state_toggle_timer_PERIOD_LSB_PTR,(uint16)period);
    #else
        CY_SET_REG16(comm_state_toggle_timer_PERIOD_LSB_PTR, period);
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_ReadPeriod
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
uint16 comm_state_toggle_timer_ReadPeriod(void) 
{
    #if(comm_state_toggle_timer_UsingFixedFunction)
        return ((uint16)CY_GET_REG16(comm_state_toggle_timer_PERIOD_LSB_PTR));
    #else
        return (CY_GET_REG16(comm_state_toggle_timer_PERIOD_LSB_PTR));
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
}


#if (!comm_state_toggle_timer_UsingFixedFunction)
/*******************************************************************************
* Function Name: comm_state_toggle_timer_WriteCompare
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
void comm_state_toggle_timer_WriteCompare(uint16 compare) \
                                   
{
    #if(comm_state_toggle_timer_UsingFixedFunction)
        CY_SET_REG16(comm_state_toggle_timer_COMPARE_LSB_PTR, (uint16)compare);
    #else
        CY_SET_REG16(comm_state_toggle_timer_COMPARE_LSB_PTR, compare);
    #endif /* (comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_ReadCompare
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
uint16 comm_state_toggle_timer_ReadCompare(void) 
{
    return (CY_GET_REG16(comm_state_toggle_timer_COMPARE_LSB_PTR));
}


#if (comm_state_toggle_timer_COMPARE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: comm_state_toggle_timer_SetCompareMode
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
void comm_state_toggle_timer_SetCompareMode(uint8 compareMode) 
{
    /* Clear the compare mode bits in the control register */
    comm_state_toggle_timer_CONTROL &= ((uint8)(~comm_state_toggle_timer_CTRL_CMPMODE_MASK));
    
    /* Write the new setting */
    comm_state_toggle_timer_CONTROL |= compareMode;
}
#endif  /* (comm_state_toggle_timer_COMPARE_MODE_SOFTWARE) */


#if (comm_state_toggle_timer_CAPTURE_MODE_SOFTWARE)
/*******************************************************************************
* Function Name: comm_state_toggle_timer_SetCaptureMode
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
void comm_state_toggle_timer_SetCaptureMode(uint8 captureMode) 
{
    /* Clear the capture mode bits in the control register */
    comm_state_toggle_timer_CONTROL &= ((uint8)(~comm_state_toggle_timer_CTRL_CAPMODE_MASK));
    
    /* Write the new setting */
    comm_state_toggle_timer_CONTROL |= ((uint8)((uint8)captureMode << comm_state_toggle_timer_CTRL_CAPMODE0_SHIFT));
}
#endif  /* (comm_state_toggle_timer_CAPTURE_MODE_SOFTWARE) */


/*******************************************************************************
* Function Name: comm_state_toggle_timer_ClearFIFO
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
void comm_state_toggle_timer_ClearFIFO(void) 
{

    while(0u != (comm_state_toggle_timer_ReadStatusRegister() & comm_state_toggle_timer_STATUS_FIFONEMP))
    {
        (void)comm_state_toggle_timer_ReadCapture();
    }

}
#endif  /* (!comm_state_toggle_timer_UsingFixedFunction) */


/* [] END OF FILE */

