/*******************************************************************************
* File Name: ShiftReg_rev_PM.c
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

#include "ShiftReg_rev.h"

static ShiftReg_rev_BACKUP_STRUCT ShiftReg_rev_backup =
{
    ShiftReg_rev_DISABLED,

    ((uint32) ShiftReg_rev_DEFAULT_A0),
    ((uint32) ShiftReg_rev_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint32) ShiftReg_rev_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: ShiftReg_rev_SaveConfig
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
void ShiftReg_rev_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    ShiftReg_rev_backup.saveSrA0Reg   = CY_GET_REG32(ShiftReg_rev_SHIFT_REG_LSB_PTR);
    ShiftReg_rev_backup.saveSrA1Reg   = CY_GET_REG32(ShiftReg_rev_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        ShiftReg_rev_backup.saveSrIntMask = ShiftReg_rev_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_rev_RestoreConfig
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
void ShiftReg_rev_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG32(ShiftReg_rev_SHIFT_REG_LSB_PTR, ShiftReg_rev_backup.saveSrA0Reg);
    CY_SET_REG32(ShiftReg_rev_SHIFT_REG_VALUE_LSB_PTR, ShiftReg_rev_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        ShiftReg_rev_SR_STATUS_MASK = ((uint8) ShiftReg_rev_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: ShiftReg_rev_Sleep
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
void ShiftReg_rev_Sleep(void) 
{
    ShiftReg_rev_backup.enableState = ((uint8) ShiftReg_rev_IS_ENABLED);

    ShiftReg_rev_Stop();
    ShiftReg_rev_SaveConfig();
}


/*******************************************************************************
* Function Name: ShiftReg_rev_Wakeup
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
void ShiftReg_rev_Wakeup(void) 
{
    ShiftReg_rev_RestoreConfig();

    if(0u != ShiftReg_rev_backup.enableState)
    {
        ShiftReg_rev_Enable();
    }
}


/* [] END OF FILE */
