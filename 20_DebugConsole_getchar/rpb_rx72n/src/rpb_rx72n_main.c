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
