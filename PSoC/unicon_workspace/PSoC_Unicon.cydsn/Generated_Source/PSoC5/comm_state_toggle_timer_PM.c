/*******************************************************************************
* File Name: comm_state_toggle_timer_PM.c  
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

#include "comm_state_toggle_timer.h"

static comm_state_toggle_timer_backupStruct comm_state_toggle_timer_backup;


/*******************************************************************************
* Function Name: comm_state_toggle_timer_SaveConfig
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
*  comm_state_toggle_timer_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void comm_state_toggle_timer_SaveConfig(void) 
{
    #if (!comm_state_toggle_timer_UsingFixedFunction)

        comm_state_toggle_timer_backup.CounterUdb = comm_state_toggle_timer_ReadCounter();

        #if(!comm_state_toggle_timer_ControlRegRemoved)
            comm_state_toggle_timer_backup.CounterControlRegister = comm_state_toggle_timer_ReadControlRegister();
        #endif /* (!comm_state_toggle_timer_ControlRegRemoved) */

    #endif /* (!comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_RestoreConfig
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
*  comm_state_toggle_timer_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void comm_state_toggle_timer_RestoreConfig(void) 
{      
    #if (!comm_state_toggle_timer_UsingFixedFunction)

       comm_state_toggle_timer_WriteCounter(comm_state_toggle_timer_backup.CounterUdb);

        #if(!comm_state_toggle_timer_ControlRegRemoved)
            comm_state_toggle_timer_WriteControlRegister(comm_state_toggle_timer_backup.CounterControlRegister);
        #endif /* (!comm_state_toggle_timer_ControlRegRemoved) */

    #endif /* (!comm_state_toggle_timer_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_Sleep
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
*  comm_state_toggle_timer_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void comm_state_toggle_timer_Sleep(void) 
{
    #if(!comm_state_toggle_timer_ControlRegRemoved)
        /* Save Counter's enable state */
        if(comm_state_toggle_timer_CTRL_ENABLE == (comm_state_toggle_timer_CONTROL & comm_state_toggle_timer_CTRL_ENABLE))
        {
            /* Counter is enabled */
            comm_state_toggle_timer_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            comm_state_toggle_timer_backup.CounterEnableState = 0u;
        }
    #else
        comm_state_toggle_timer_backup.CounterEnableState = 1u;
        if(comm_state_toggle_timer_backup.CounterEnableState != 0u)
        {
            comm_state_toggle_timer_backup.CounterEnableState = 0u;
        }
    #endif /* (!comm_state_toggle_timer_ControlRegRemoved) */
    
    comm_state_toggle_timer_Stop();
    comm_state_toggle_timer_SaveConfig();
}


/*******************************************************************************
* Function Name: comm_state_toggle_timer_Wakeup
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
*  comm_state_toggle_timer_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void comm_state_toggle_timer_Wakeup(void) 
{
    comm_state_toggle_timer_RestoreConfig();
    #if(!comm_state_toggle_timer_ControlRegRemoved)
        if(comm_state_toggle_timer_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            comm_state_toggle_timer_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!comm_state_toggle_timer_ControlRegRemoved) */
    
}


/* [] END OF FILE */
