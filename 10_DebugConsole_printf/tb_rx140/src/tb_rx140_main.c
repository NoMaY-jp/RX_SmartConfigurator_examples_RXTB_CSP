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
