/***********************************************************************
*
*  FILE        : rpb_rx72n_main.cpp
*  DATE        : 2020-11-07
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "rpbrx72ndef.h"

U_CONFIG_UART_PRINTF_IMPL(  SCI2, 128 /* transmit buffer size */ );
U_CONFIG_UART_GETCHAR_IMPL( SCI2, 128 /* receive ring buffer size */ );

int main(void)
{
    char c;

    for (;;)
    {
        Printf( SCI2, "Please enter a character:\r\n" );

        c = Getchar( SCI2 );

        Printf( SCI2, "\r\nNow %c is entered.\r\n\r\n", c );
    }
}
