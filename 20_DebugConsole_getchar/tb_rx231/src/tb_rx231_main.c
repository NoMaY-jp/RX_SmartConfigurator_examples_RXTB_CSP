/***********************************************************************
*
*  FILE        : tb_rx231_main.cpp
*  DATE        : 2019-02-26
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_smc_entry.h"
#include "tbrx231def.h"

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
