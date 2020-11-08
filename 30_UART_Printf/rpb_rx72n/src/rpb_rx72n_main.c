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

U_CONFIG_UART_PRINTF_IMPL( SCI2, 128 /* transmit buffer size */ );

int main(void)
{
    LED0 = LED_ON;

    for (;;)
    {
        Printf( SCI2, "Hello World\r\n" );

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;
    }
}
