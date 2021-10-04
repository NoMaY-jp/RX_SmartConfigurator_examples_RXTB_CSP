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
#include <string.h>

// Note
// 1. This example uses MCU's SCI5 (SSCL5/SSDA5 = Pmod's Pin3/Pin4)
//    and the UART is configured with 9600 baud.

U_CONFIG_I2C_MASTER_IMPL( SCI5 );

#if 1

int main(void) /* The following code is checked to be built and run */
{
    /* HS3001 data sheet: https://www.renesas.com/document/dst/hs300x-datasheet */
    uint8_t adr7_HS3001 = 0x44; /* The 7-bits address of the device */
    uint8_t ret_data[4];
    uint16_t status_bits, humidity_raw, temperature_raw;
    float humidity, temperature;

    U_Config_I2C_Master_Start( SCI5 );

    for (;;)
    {
        /* Measurement Requests */
        U_Config_I2C_Master_Send_Ex( SCI5, adr7_HS3001, NULL, 0, MD_WAIT_FINISH );

        /* Wait for the completion of measurement (the wait value is more than the minimal time) */
        R_BSP_SoftwareDelay( 100, BSP_DELAY_MILLISECS );

        /* Data Fetch */
        memset( ret_data, 0x00, sizeof(ret_data) ); /* Just clear before reception */
        U_Config_I2C_Master_Receive_Ex( SCI5, adr7_HS3001, ret_data, 4, MD_WAIT_FINISH );

        /* Get the result of measurement */
        status_bits = (ret_data[0] & 0xC0) >> 6;
        humidity_raw = ((ret_data[0] << 8) | ret_data[1]) & 0x3FFF;
        temperature_raw = ((ret_data[2] << 8) | ret_data[3]) >> 2;
        printf( "status bits     =  %1X\r\n", status_bits );
        printf( "humidity raw    =  0x%04X\r\n", humidity_raw );
        printf( "temperature raw =  0x%04X\r\n", temperature_raw );

        /* Calculate the result of measurement */
        humidity = (float)humidity_raw / (16384 - 1) * 100;
        temperature = (float)temperature_raw / (16384 -1) * 165 - 40;
        printf( "humidity        = %5.1f%%\r\n", humidity );
        printf( "temperature     = %5.1f\"C" "\r\n", temperature );

        R_BSP_SoftwareDelay( 3000, BSP_DELAY_MILLISECS );
        printf( "\r\n" );
    }
}

#else /* #if 1 */

int main(void) /* The following code is checked to be built only */
{
    /* ISL29034 data sheet: https://www.renesas.com/document/dst/isl29034-datasheet */
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

    U_Config_I2C_Master_Start( SCI5 );

    U_Config_I2C_Master_Send_Ex( SCI5, adr7_ISL29034, cmd_read_ID, sizeof(cmd_read_ID), MD_WAIT_FINISH );
    U_Config_I2C_Master_Receive_Ex( SCI5, adr7_ISL29034, ret_data1, sizeof(ret_data1), MD_WAIT_FINISH );
    printf( "Read the initial value of the ID register:        " );
    printf( "(val & 0xA8) = 0x%02X (expected: 0xA8)\r\n\r\n", ret_data1[0] & 0xA8 );

    U_Config_I2C_Master_Send_Ex( SCI5, adr7_ISL29034, cmd_clr_BOUT, sizeof(cmd_clr_BOUT), MD_WAIT_FINISH );
    printf( "Clear the BOUT bit (the bit7 of the ID register).\r\n\r\n" );

    U_Config_I2C_Master_Send_Ex( SCI5, adr7_ISL29034, cmd_read_ID, sizeof(cmd_read_ID), MD_WAIT_FINISH );
    U_Config_I2C_Master_Receive_Ex( SCI5, adr7_ISL29034, ret_data2, sizeof(ret_data2), MD_WAIT_FINISH );
    printf( "Read again the value of the ID register:          " );
    printf( "(val & 0xA8) = 0x%02X (expected: 0x28)\r\n\r\n", ret_data2[0] & 0xA8 );

    printf( "Done.\r\n" );
    for (;;)
    {
    }
}

#endif /* #if 1 */
