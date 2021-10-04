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
// 1. This example uses MCU's SCI5 (TxD5/RxD5 = Pmod's Pin4/Pin3)
//    and the UART is configured with 9600 baud.

U_CONFIG_UART_PRINTF_IMPL(  SCI5, 128 /* transmit buffer size */ );
U_CONFIG_UART_GETCHAR_IMPL( SCI5, 128 /* receive ring buffer size */ );

int main(void)
{
    char c;
    int i;

    for (;;)
    {
        Printf( SCI5, "Please enter a character:\r\n" );

        for (i = 0; i < 3; i++)
        {
            R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

            if (Is_Getchar_Ready( SCI5 ))
            {
                c = Getchar( SCI5 );
                Printf( SCI5, "\r\nYeah, %c is entered.\r\n\r\n", c );

                R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

                break;
            }
        }
    }
}
