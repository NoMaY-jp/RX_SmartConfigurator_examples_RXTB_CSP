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

R_CONFIG_SCI_SEND_IMPL( SCI1, 128 /* transmit buffer size */ );

int main(void)
{
    LED0 = LED_ON;

    for (;;)
    {
        Printf( SCI1, "Hello World\r\n" );

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;
    }
}
