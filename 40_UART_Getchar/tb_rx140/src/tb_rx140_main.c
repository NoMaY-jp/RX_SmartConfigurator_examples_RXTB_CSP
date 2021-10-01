/***********************************************************************
*
*  FILE        : tb_rx140_main.cpp
*  DATE        : 2021-10-01
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "tbrx140def.h"

// Note
// 1. This example uses MCU's SCI5 (TxD5/RxD5 = Pmod's Pin4/Pin3)
//    and the UART is configured with 9600 baud.

U_CONFIG_UART_PRINTF_IMPL(  SCI5, 128 /* transmit buffer size */ );
U_CONFIG_UART_GETCHAR_IMPL( SCI5, 128 /* receive ring buffer size */ );

int main(void)
{
    char c;

    for (;;)
    {
        Printf( SCI5, "Please enter a character:\r\n" );

        c = Getchar( SCI5 );

        Printf( SCI5, "\r\nNow %c is entered.\r\n\r\n", c );
    }
}
