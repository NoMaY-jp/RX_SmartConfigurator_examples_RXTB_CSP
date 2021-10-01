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
    char c;
    int i;

    for (;;)
    {
        printf( "Please enter a character:\r\n" );

        for (i = 0; i < 3; i++)
        {
            R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

            if (is_getchar_ready())
            {
                c = getchar();
                printf( "\r\nYeah, %c is entered.\r\n\r\n", c );

                R_BSP_SoftwareDelay( 1000, BSP_DELAY_MILLISECS );

                break;
            }
        }
    }
}
