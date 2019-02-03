/*******************************************************************************
* File Name: count_time_to_transmit_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
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

#include "count_time_to_transmit.h"

static count_time_to_transmit_backupStruct count_time_to_transmit_backup;


/*******************************************************************************
* Function Name: count_time_to_transmit_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  count_time_to_transmit_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void count_time_to_transmit_SaveConfig(void) 
{
    #if (!count_time_to_transmit_UsingFixedFunction)

        count_time_to_transmit_backup.CounterUdb = count_time_to_transmit_ReadCounter();

        #if(!count_time_to_transmit_ControlRegRemoved)
            count_time_to_transmit_backup.CounterControlRegister = count_time_to_transmit_ReadControlRegister();
        #endif /* (!count_time_to_transmit_ControlRegRemoved) */

    #endif /* (!count_time_to_transmit_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_to_transmit_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  count_time_to_transmit_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void count_time_to_transmit_RestoreConfig(void) 
{      
    #if (!count_time_to_transmit_UsingFixedFunction)

       count_time_to_transmit_WriteCounter(count_time_to_transmit_backup.CounterUdb);

        #if(!count_time_to_transmit_ControlRegRemoved)
            count_time_to_transmit_WriteControlRegister(count_time_to_transmit_backup.CounterControlRegister);
        #endif /* (!count_time_to_transmit_ControlRegRemoved) */

    #endif /* (!count_time_to_transmit_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: count_time_to_transmit_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  count_time_to_transmit_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void count_time_to_transmit_Sleep(void) 
{
    #if(!count_time_to_transmit_ControlRegRemoved)
        /* Save Counter's enable state */
        if(count_time_to_transmit_CTRL_ENABLE == (count_time_to_transmit_CONTROL & count_time_to_transmit_CTRL_ENABLE))
        {
            /* Counter is enabled */
            count_time_to_transmit_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            count_time_to_transmit_backup.CounterEnableState = 0u;
        }
    #else
        count_time_to_transmit_backup.CounterEnableState = 1u;
        if(count_time_to_transmit_backup.CounterEnableState != 0u)
        {
            count_time_to_transmit_backup.CounterEnableState = 0u;
        }
    #endif /* (!count_time_to_transmit_ControlRegRemoved) */
    
    count_time_to_transmit_Stop();
    count_time_to_transmit_SaveConfig();
}


/*******************************************************************************
* Function Name: count_time_to_transmit_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  count_time_to_transmit_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void count_time_to_transmit_Wakeup(void) 
{
    count_time_to_transmit_RestoreConfig();
    #if(!count_time_to_transmit_ControlRegRemoved)
        if(count_time_to_transmit_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            count_time_to_transmit_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!count_time_to_transmit_ControlRegRemoved) */
    
}


/* [] END OF FILE */
