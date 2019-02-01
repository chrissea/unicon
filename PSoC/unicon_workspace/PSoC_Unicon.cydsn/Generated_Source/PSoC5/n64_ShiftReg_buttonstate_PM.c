/*******************************************************************************
* File Name: n64_ShiftReg_buttonstate_PM.c
* Version 2.30
*
* Description:
*  This file provides the API source code for sleep mode support for Shift
*  Register component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "n64_ShiftReg_buttonstate.h"

static n64_ShiftReg_buttonstate_BACKUP_STRUCT n64_ShiftReg_buttonstate_backup =
{
    n64_ShiftReg_buttonstate_DISABLED,

    ((uint32) n64_ShiftReg_buttonstate_DEFAULT_A0),
    ((uint32) n64_ShiftReg_buttonstate_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint32) n64_ShiftReg_buttonstate_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_SaveConfig
********************************************************************************
*
* Summary:
*  Saves Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    n64_ShiftReg_buttonstate_backup.saveSrA0Reg   = CY_GET_REG32(n64_ShiftReg_buttonstate_SHIFT_REG_LSB_PTR);
    n64_ShiftReg_buttonstate_backup.saveSrA1Reg   = CY_GET_REG32(n64_ShiftReg_buttonstate_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        n64_ShiftReg_buttonstate_backup.saveSrIntMask = n64_ShiftReg_buttonstate_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores Shift Register configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG32(n64_ShiftReg_buttonstate_SHIFT_REG_LSB_PTR, n64_ShiftReg_buttonstate_backup.saveSrA0Reg);
    CY_SET_REG32(n64_ShiftReg_buttonstate_SHIFT_REG_VALUE_LSB_PTR, n64_ShiftReg_buttonstate_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        n64_ShiftReg_buttonstate_SR_STATUS_MASK = ((uint8) n64_ShiftReg_buttonstate_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_Sleep
********************************************************************************
*
* Summary:
*  Prepare the component to enter a Sleep mode.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_Sleep(void) 
{
    n64_ShiftReg_buttonstate_backup.enableState = ((uint8) n64_ShiftReg_buttonstate_IS_ENABLED);

    n64_ShiftReg_buttonstate_Stop();
    n64_ShiftReg_buttonstate_SaveConfig();
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_Wakeup(void) 
{
    n64_ShiftReg_buttonstate_RestoreConfig();

    if(0u != n64_ShiftReg_buttonstate_backup.enableState)
    {
        n64_ShiftReg_buttonstate_Enable();
    }
}


/* [] END OF FILE */
