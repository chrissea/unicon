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

#define GAMECUBE 0 
#define N64      1

#define RX_BYTE_NUM 6

uint8_t target_console;
uint8_t from_controller[RX_BYTE_NUM];
uint8_t to_console[RX_BYTE_NUM];
int controller_byte_counter = 0;


//serial receive ISR
CY_ISR(UART_RX_INT){
    uint8_t RxData = UART_ReadRxData();
    LCD_PutChar(RxData);
    
    from_controller[controller_byte_counter] =  RxData;
    //controller_byte_counter++;
    // below is resetting the counter once full, but I've decided to do
    // that in the main loop below instead, when converting the data and
    // sending over to the console
    //controller_byte_counter += (controller_byte_counter == 6)? -6: 1;
}

// this timer should only run once
CY_ISR(n64_init_isr) {
    // disable timer1
    Timer_1_Stop();
    // enable timer2
    Timer_2_Enable();
    // enable counter
    count_time_to_transmit_Enable();
}

CY_ISR(comm_state_isr) {
    // constant value in this register
    n64_ShiftReg_commack_WriteRegValue(0x01050002);
    // update the value in the state register
    n64_ShiftReg_buttonstate_WriteData(0x10000000);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    uart_rx_int_StartEx(UART_RX_INT);  // start RX interrupt
    //UART_SetRxInterruptMode(UART_RX_STS_FIFO_NOTEMPTY);
    UART_Start();
    UART_ClearRxBuffer();
    
    LCD_Start();					    // initialize lcd
	LCD_ClearDisplay();
    
    // initialize all the N64 circuit components here
    n64_ShiftReg_buttonstate_Start();
    n64_ShiftReg_commack_Start();
    n64_one_bit_Start();
    n64_zero_bit_Start();
    count_time_to_transmit_Start();
    n64_ShiftReg_commack_WriteRegValue(0x01050002);
    n64_one_bit_WriteRegValue(0b0111);
    n64_zero_bit_WriteRegValue(0b0001);
    
    // set up the comm state pin to interrupt on falling edge
    // in order to reload the ShiftReg_buttonstate with data
    
    
    // target console would be selected by user, but hard-coded for now
    target_console = GAMECUBE;
    
    for(;;)
    {   
         
        
    }
}

/* [] END OF FILE */
