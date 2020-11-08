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

U_CONFIG_I2C_MASTER_IMPL( SCI11 );

int main(void)
{
    /* ISL29034 data sheet: https://www.renesas.com/jp/ja/doc/datasheet/isl29034.pdf */
    uint8_t adr7_ISL29034 = 0x44; /* The 7-bits address of the device */
    uint8_t cmd_read_ID[1] = {
        0x0F  /* Address of the ID register */
    };
    uint8_t cmd_clr_BOUT[2] = {
        0x0F, /* Address of the ID register */
        0x00  /* Write data (the BOUT bit is the bit7 of the ID register) */
    };
    uint8_t ret_data1[1] = { 0x00 }; /* Just clear before reception */
    uint8_t ret_data2[1] = { 0x00 }; /* Just clear before reception */

    printf( "Hit 'Enter' key to proceed the operation.\r\n" );
    getchar();

    U_Config_I2C_Master_Start( SCI11 );

    U_Config_I2C_Master_Send_UWT( SCI11, adr7_ISL29034, cmd_read_ID, sizeof(cmd_read_ID) );
    U_Config_I2C_Master_Receive_UWT( SCI11, adr7_ISL29034, ret_data1, sizeof(ret_data1) );
    printf( "Read the initial value of the ID register:        " );
    printf( "(val & 0xA8) = 0x%02x (expected: 0xA8)\r\n\r\n", ret_data1[0] & 0xA8 );

    U_Config_I2C_Master_Send_UWT( SCI11, adr7_ISL29034, cmd_clr_BOUT, sizeof(cmd_clr_BOUT) );
    printf( "Clear the BOUT bit (the bit7 of the ID register).\r\n\r\n" );

    U_Config_I2C_Master_Send_UWT( SCI11, adr7_ISL29034, cmd_read_ID, sizeof(cmd_read_ID) );
    U_Config_I2C_Master_Receive_UWT( SCI11, adr7_ISL29034, ret_data2, sizeof(ret_data2) );
    printf( "Read again the value of the ID register:          " );
    printf( "(val & 0xA8) = 0x%02x (expected: 0x28)\r\n\r\n", ret_data2[0] & 0xA8 );

    printf( "Done.\r\n" );
    for (;;)
    {
    }
}
