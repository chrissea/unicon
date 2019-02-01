/*******************************************************************************
* File Name: n64_Receive_Delay_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "n64_Receive_Delay.h"

static n64_Receive_Delay_backupStruct n64_Receive_Delay_backup;


/*******************************************************************************
* Function Name: n64_Receive_Delay_SaveConfig
********************************************************************************
*
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
*  n64_Receive_Delay_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void n64_Receive_Delay_SaveConfig(void) 
{
    #if (!n64_Receive_Delay_UsingFixedFunction)
        n64_Receive_Delay_backup.TimerUdb = n64_Receive_Delay_ReadCounter();
        n64_Receive_Delay_backup.InterruptMaskValue = n64_Receive_Delay_STATUS_MASK;
        #if (n64_Receive_Delay_UsingHWCaptureCounter)
            n64_Receive_Delay_backup.TimerCaptureCounter = n64_Receive_Delay_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!n64_Receive_Delay_UDB_CONTROL_REG_REMOVED)
            n64_Receive_Delay_backup.TimerControlRegister = n64_Receive_Delay_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: n64_Receive_Delay_RestoreConfig
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
*  n64_Receive_Delay_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void n64_Receive_Delay_RestoreConfig(void) 
{   
    #if (!n64_Receive_Delay_UsingFixedFunction)

        n64_Receive_Delay_WriteCounter(n64_Receive_Delay_backup.TimerUdb);
        n64_Receive_Delay_STATUS_MASK =n64_Receive_Delay_backup.InterruptMaskValue;
        #if (n64_Receive_Delay_UsingHWCaptureCounter)
            n64_Receive_Delay_SetCaptureCount(n64_Receive_Delay_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!n64_Receive_Delay_UDB_CONTROL_REG_REMOVED)
            n64_Receive_Delay_WriteControlRegister(n64_Receive_Delay_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: n64_Receive_Delay_Sleep
********************************************************************************
*
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
*  n64_Receive_Delay_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void n64_Receive_Delay_Sleep(void) 
{
    #if(!n64_Receive_Delay_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(n64_Receive_Delay_CTRL_ENABLE == (n64_Receive_Delay_CONTROL & n64_Receive_Delay_CTRL_ENABLE))
        {
            /* Timer is enabled */
            n64_Receive_Delay_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            n64_Receive_Delay_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    n64_Receive_Delay_Stop();
    n64_Receive_Delay_SaveConfig();
}


/*******************************************************************************
* Function Name: n64_Receive_Delay_Wakeup
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
*  n64_Receive_Delay_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void n64_Receive_Delay_Wakeup(void) 
{
    n64_Receive_Delay_RestoreConfig();
    #if(!n64_Receive_Delay_UDB_CONTROL_REG_REMOVED)
        if(n64_Receive_Delay_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                n64_Receive_Delay_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
