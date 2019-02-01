/*******************************************************************************
* File Name: n64_ShiftReg_buttonstate.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "n64_ShiftReg_buttonstate.h"

uint8 n64_ShiftReg_buttonstate_initVar = 0u;


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  n64_ShiftReg_buttonstate_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_Start(void) 
{
    if(0u == n64_ShiftReg_buttonstate_initVar)
    {
        n64_ShiftReg_buttonstate_Init();
        n64_ShiftReg_buttonstate_initVar = 1u; /* Component initialized */
    }

    n64_ShiftReg_buttonstate_Enable();
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    n64_ShiftReg_buttonstate_SR_CONTROL |= n64_ShiftReg_buttonstate_CLK_EN;

    n64_ShiftReg_buttonstate_EnableInt();
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_Init(void) 
{
    n64_ShiftReg_buttonstate_SetIntMode(n64_ShiftReg_buttonstate_INT_SRC);
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    n64_ShiftReg_buttonstate_SR_CONTROL &= ((uint8) ~n64_ShiftReg_buttonstate_CLK_EN);
    n64_ShiftReg_buttonstate_DisableInt();
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    n64_ShiftReg_buttonstate_SR_AUX_CONTROL |= n64_ShiftReg_buttonstate_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    n64_ShiftReg_buttonstate_SR_AUX_CONTROL &= ((uint8) ~n64_ShiftReg_buttonstate_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 n64_ShiftReg_buttonstate_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = n64_ShiftReg_buttonstate_RET_FIFO_NOT_DEFINED;

    #if(0u != n64_ShiftReg_buttonstate_USE_INPUT_FIFO)
        if(n64_ShiftReg_buttonstate_IN_FIFO == fifoId)
        {
            switch(n64_ShiftReg_buttonstate_GET_IN_FIFO_STS)
            {
                case n64_ShiftReg_buttonstate_IN_FIFO_FULL :
                    result = n64_ShiftReg_buttonstate_RET_FIFO_FULL;
                    break;

                case n64_ShiftReg_buttonstate_IN_FIFO_EMPTY :
                    result = n64_ShiftReg_buttonstate_RET_FIFO_EMPTY;
                    break;

                case n64_ShiftReg_buttonstate_IN_FIFO_PARTIAL:
                    result = n64_ShiftReg_buttonstate_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = n64_ShiftReg_buttonstate_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != n64_ShiftReg_buttonstate_USE_INPUT_FIFO) */

    if(n64_ShiftReg_buttonstate_OUT_FIFO == fifoId)
    {
        switch(n64_ShiftReg_buttonstate_GET_OUT_FIFO_STS)
        {
            case n64_ShiftReg_buttonstate_OUT_FIFO_FULL :
                result = n64_ShiftReg_buttonstate_RET_FIFO_FULL;
                break;

            case n64_ShiftReg_buttonstate_OUT_FIFO_EMPTY :
                result = n64_ShiftReg_buttonstate_RET_FIFO_EMPTY;
                break;

            case n64_ShiftReg_buttonstate_OUT_FIFO_PARTIAL :
                result = n64_ShiftReg_buttonstate_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = n64_ShiftReg_buttonstate_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_SetIntMode(uint8 interruptSource) 
{
    n64_ShiftReg_buttonstate_SR_STATUS_MASK &= ((uint8) ~n64_ShiftReg_buttonstate_INTS_EN_MASK);          /* Clear existing int */
    n64_ShiftReg_buttonstate_SR_STATUS_MASK |= (interruptSource & n64_ShiftReg_buttonstate_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 n64_ShiftReg_buttonstate_GetIntStatus(void) 
{
    return(n64_ShiftReg_buttonstate_SR_STATUS & n64_ShiftReg_buttonstate_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void n64_ShiftReg_buttonstate_WriteRegValue(uint32 shiftData)
                                                                     
{
    CY_SET_REG32(n64_ShiftReg_buttonstate_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != n64_ShiftReg_buttonstate_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: n64_ShiftReg_buttonstate_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus n64_ShiftReg_buttonstate_WriteData(uint32 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(n64_ShiftReg_buttonstate_RET_FIFO_FULL != (n64_ShiftReg_buttonstate_GetFIFOStatus(n64_ShiftReg_buttonstate_IN_FIFO)))
        {
            CY_SET_REG32(n64_ShiftReg_buttonstate_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != n64_ShiftReg_buttonstate_USE_INPUT_FIFO) */


#if(0u != n64_ShiftReg_buttonstate_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: n64_ShiftReg_buttonstate_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint32 n64_ShiftReg_buttonstate_ReadData(void) 
    {
        return(CY_GET_REG32(n64_ShiftReg_buttonstate_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != n64_ShiftReg_buttonstate_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: n64_ShiftReg_buttonstate_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint32 n64_ShiftReg_buttonstate_ReadRegValue(void) 
{
    uint32 result;

    /* Clear FIFO before software capture */
    while(n64_ShiftReg_buttonstate_RET_FIFO_EMPTY != n64_ShiftReg_buttonstate_GetFIFOStatus(n64_ShiftReg_buttonstate_OUT_FIFO))
    {
        (void) CY_GET_REG32(n64_ShiftReg_buttonstate_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(n64_ShiftReg_buttonstate_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG32(n64_ShiftReg_buttonstate_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (n64_ShiftReg_buttonstate_SR_SIZE % 8u))
        result &= ((uint32) n64_ShiftReg_buttonstate_SR_MASK);
    #endif /* (0u != (n64_ShiftReg_buttonstate_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
