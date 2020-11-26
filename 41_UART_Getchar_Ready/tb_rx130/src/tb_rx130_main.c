/***********************************************************************
*
*  FILE        : tb_rx130_main.cpp
*  DATE        : 2019-02-26
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "tbrx130def.h"

U_CONFIG_UART_PRINTF_IMPL(  SCI1, 128 /* transmit buffer size */ );
U_CONFIG_UART_GETCHAR_IMPL( SCI1, 128 /* receive ring buffer size */ );

int main(void)
{
    char c;
    int i;

    for (;;)
    {
        Printf( SCI1, "Please enter a character:\r\n" );

        for (i = 0; i < 3; i++)
        {
            R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

            if (Is_Getchar_Ready( SCI1 ))
            {
                c = Getchar( SCI1 );
                Printf( SCI1, "\r\nYeah, %c is entered.\r\n\r\n", c );

                R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

                break;
            }
        }
    }
}
