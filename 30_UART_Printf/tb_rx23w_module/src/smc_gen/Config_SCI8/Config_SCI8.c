/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_SCI8.c
* Component Version: 1.11.0
* Device(s)        : R5F523W8CxLN
* Description      : This file implements device driver for Config_SCI8.
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "Config_SCI8.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_sci8_tx_address;                /* SCI8 transmit buffer address */
volatile uint16_t  g_sci8_tx_count;                   /* SCI8 transmit data number */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI8_Create
* Description  : This function initializes the SCI8 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI8_Create(void)
{
    /* Cancel SCI stop state */
    MSTP(SCI8) = 0U;

    /* Set interrupt priority */
    IPR(SCI8,TXI8) = _0F_SCI_PRIORITY_LEVEL15;

    /* Clear the control register */
    SCI8.SCR.BYTE = 0x00U;

    /* Set clock enable */
    SCI8.SCR.BYTE = _00_SCI_INTERNAL_SCK_UNUSED;

    /* Clear the SIMR1.IICM, SPMR.CKPH, and CKPOL bit, and set SPMR */
    SCI8.SIMR1.BIT.IICM = 0U;
    SCI8.SPMR.BYTE = _00_SCI_RTS | _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;

    /* Set control registers */
    SCI8.SMR.BYTE = _02_SCI_CLOCK_PCLK_16 | _00_SCI_MULTI_PROCESSOR_DISABLE | _00_SCI_STOP_1 | 
                    _00_SCI_PARITY_DISABLE | _00_SCI_DATA_LENGTH_8 | _00_SCI_ASYNCHRONOUS_OR_I2C_MODE;
    SCI8.SCMR.BYTE = _00_SCI_SERIAL_MODE | _00_SCI_DATA_INVERT_NONE | _00_SCI_DATA_LSB_FIRST | 
                     _10_SCI_DATA_LENGTH_8_OR_7 | _62_SCI_SCMR_DEFAULT;
    SCI8.SEMR.BYTE = _00_SCI_BIT_MODULATION_DISABLE | _10_SCI_8_BASE_CLOCK | _00_SCI_BAUDRATE_SINGLE;

    /* Set bit rate */
    SCI8.BRR = 0x0AU;

    /* Set TXD8 pin */
    MPC.PC7PFS.BYTE = 0x0AU;
    PORTC.PODR.BYTE |= 0x80U;
    PORTC.PDR.BYTE |= 0x80U;

    R_Config_SCI8_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI8_Start
* Description  : This function starts the SCI8 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI8_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI8,TXI8) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI8,TXI8) = 1U;
    IEN(SCI8,TEI8) = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI8_Stop
* Description  : This function stops the SCI8 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI8_Stop(void)
{
    /* Set TXD8 pin */
    PORTC.PMR.BYTE &= 0x7FU;

    /* Disable serial transmit */
    SCI8.SCR.BIT.TE = 0U;

    /* Disable SCI interrupt */
    SCI8.SCR.BIT.TIE = 0U;
    IEN(SCI8,TXI8) = 0U;
    IEN(SCI8,TEI8) = 0U;
    IR(SCI8,TXI8) = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI8_Serial_Send
* Description  : This function transmits SCI8 data
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DMAC/DTC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DMAC/DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/

MD_STATUS R_Config_SCI8_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (1U > tx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_sci8_tx_address = tx_buf;
        g_sci8_tx_count = tx_num;

        /* Set TXD8 pin */
        PORTC.PMR.BYTE |= 0x80U;

        SCI8.SCR.BIT.TIE = 1U;
        SCI8.SCR.BIT.TE = 1U;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
