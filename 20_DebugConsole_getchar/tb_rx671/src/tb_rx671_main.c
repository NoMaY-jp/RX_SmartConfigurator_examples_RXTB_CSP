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

int main(void)
{
    char c;

    for (;;)
    {
        printf( "Please enter a character:\r\n" );

        c = getchar();

        printf( "\r\nNow %c is entered.\r\n\r\n", c );
    }
}
