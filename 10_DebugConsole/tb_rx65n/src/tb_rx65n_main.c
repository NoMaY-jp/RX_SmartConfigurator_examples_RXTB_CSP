/***********************************************************************
*
*  FILE        : tb_rx65n_main.cpp
*  DATE        : 2019-02-26
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "tbrx65ndef.h"

int main(void)
{
    LED0 = LED_ON;

    for (;;)
    {
        printf( "Hello World\r\n" );

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;

        R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );
        LED0 = ~LED0;
    }
}
