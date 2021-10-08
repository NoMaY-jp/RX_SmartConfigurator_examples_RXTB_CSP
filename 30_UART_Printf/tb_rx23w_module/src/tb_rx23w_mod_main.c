/***********************************************************************
*
*  FILE        : tb_rx23w_mod_main.cpp
*  DATE        : 2021-10-08
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "tbrx23wmdef.h"

// Note
// 1. This example uses MCU's SCI8 (TxD8 = On board FT234's RXD)
//    and the UART is configured with 9600 baud.

U_CONFIG_UART_PRINTF_IMPL(  SCI8, 128 /* transmit buffer size */ );

int main(void)
{
    LED0 = LED_ON;

    for (;;)
    {
        Printf( SCI8, "Hello World\r\n" );

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;
    }
}
