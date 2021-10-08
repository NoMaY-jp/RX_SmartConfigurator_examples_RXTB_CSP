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
    int i;

    for (;;)
    {
        Printf( SCI8, "Please enter a character:\r\n" );

        for (i = 0; i < 3; i++)
        {
            R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

            if (Is_Getchar_Ready( SCI8 ))
            {
                c = Getchar( SCI8 );
                Printf( SCI8, "\r\nYeah, %c is entered.\r\n\r\n", c );

                R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

                break;
            }
        }
    }
}
