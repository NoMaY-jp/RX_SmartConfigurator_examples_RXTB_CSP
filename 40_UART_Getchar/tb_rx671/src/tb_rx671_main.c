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

U_CONFIG_UART_PRINTF_IMPL(  SCI1, 128 /* transmit buffer size */ );
U_CONFIG_UART_GETCHAR_IMPL( SCI1, 128 /* receive ring buffer size */ );

int main(void)
{
    char c;

    for (;;)
    {
        Printf( SCI1, "Please enter a character:\r\n" );

        c = Getchar( SCI1 );

        Printf( SCI1, "\r\nNow %c is entered.\r\n\r\n", c );
    }
}
