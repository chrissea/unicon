/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include <stdlib.h>
#include <CyLib.h>

//serial receive ISR
CY_ISR(RX_INT){
    uint8_t RxData = UART_ReadRxData();
    LCD_PutChar(RxData);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    rx_int_StartEx(RX_INT);  // start RX interrupt
    //UART_SetRxInterruptMode(UART_RX_STS_FIFO_NOTEMPTY);
    UART_Start();
    UART_ClearRxBuffer();
    
    ShiftReg_fwd_Init();
    ShiftReg_rev_Init();
    
    LCD_Start();					    // initialize lcd
	LCD_ClearDisplay();
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
