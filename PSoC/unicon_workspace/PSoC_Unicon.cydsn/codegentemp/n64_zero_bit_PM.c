/*******************************************************************************
* File Name: n64_zero_bit_PM.c
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

#include "n64_zero_bit.h"

static n64_zero_bit_BACKUP_STRUCT n64_zero_bit_backup =
{
    n64_zero_bit_DISABLED,

    ((uint8) n64_zero_bit_DEFAULT_A0),
    ((uint8) n64_zero_bit_DEFAULT_A1),

    #if(CY_UDB_V0)
        ((uint8) n64_zero_bit_INT_SRC),
    #endif /* (CY_UDB_V0) */
};


/*******************************************************************************
* Function Name: n64_zero_bit_SaveConfig
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
void n64_zero_bit_SaveConfig(void) 
{
    /* Store working registers A0 and A1 */
    n64_zero_bit_backup.saveSrA0Reg   = CY_GET_REG8(n64_zero_bit_SHIFT_REG_LSB_PTR);
    n64_zero_bit_backup.saveSrA1Reg   = CY_GET_REG8(n64_zero_bit_SHIFT_REG_VALUE_LSB_PTR);

    #if(CY_UDB_V0)
        n64_zero_bit_backup.saveSrIntMask = n64_zero_bit_SR_STATUS_MASK;
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: n64_zero_bit_RestoreConfig
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
void n64_zero_bit_RestoreConfig(void) 
{
    /* Restore working registers A0 and A1 */
    CY_SET_REG8(n64_zero_bit_SHIFT_REG_LSB_PTR, n64_zero_bit_backup.saveSrA0Reg);
    CY_SET_REG8(n64_zero_bit_SHIFT_REG_VALUE_LSB_PTR, n64_zero_bit_backup.saveSrA1Reg);

    #if(CY_UDB_V0)
        n64_zero_bit_SR_STATUS_MASK = ((uint8) n64_zero_bit_backup.saveSrIntMask);
    #endif /* (CY_UDB_V0) */
}


/*******************************************************************************
* Function Name: n64_zero_bit_Sleep
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
void n64_zero_bit_Sleep(void) 
{
    n64_zero_bit_backup.enableState = ((uint8) n64_zero_bit_IS_ENABLED);

    n64_zero_bit_Stop();
    n64_zero_bit_SaveConfig();
}


/*******************************************************************************
* Function Name: n64_zero_bit_Wakeup
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
void n64_zero_bit_Wakeup(void) 
{
    n64_zero_bit_RestoreConfig();

    if(0u != n64_zero_bit_backup.enableState)
    {
        n64_zero_bit_Enable();
    }
}


/* [] END OF FILE */
