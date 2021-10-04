/***********************************************************************
*
*  FILE        : tb_rx671_main.cpp
*  DATE        : 2021-09-28
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "tbrx671def.h"

// Note
// 1. This example uses MCU's SCI5 (TxD5 = Pmod's Pin4)
//    and the UART is configured with 9600 baud.

U_CONFIG_UART_PRINTF_IMPL( SCI5, 128 /* transmit buffer size */ );

int main(void)
{
    LED0 = LED_ON;

    for (;;)
    {
        Printf( SCI5, "Hello World\r\n" );

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;
    }
}
