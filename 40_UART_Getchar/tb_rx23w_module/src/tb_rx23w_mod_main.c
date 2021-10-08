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
// 1. This example uses MCU's SCI8 (TxD8/RxD8 = On board FT234's RXD/TXD)
//    and the UART is configured with 9600 baud.

U_CONFIG_UART_PRINTF_IMPL(  SCI8, 128 /* transmit buffer size */ );
U_CONFIG_UART_GETCHAR_IMPL( SCI8, 128 /* receive ring buffer size */ );

int main(void)
{
    char c;

    for (;;)
    {
        Printf( SCI8, "Please enter a character:\r\n" );

        c = Getchar( SCI8 );

        Printf( SCI8, "\r\nNow %c is entered.\r\n\r\n", c );
    }
}
