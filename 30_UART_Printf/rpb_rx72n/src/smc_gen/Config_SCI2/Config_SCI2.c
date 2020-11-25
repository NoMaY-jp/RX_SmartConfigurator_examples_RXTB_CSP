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
* File Name    : Config_SCI2.c
* Version      : 1.9.1
* Device(s)    : R5F572NNHxFB
* Description  : This file implements device driver for Config_SCI2.
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
#include "Config_SCI2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t * gp_sci2_tx_address;                /* SCI2 transmit buffer address */
volatile uint16_t  g_sci2_tx_count;                   /* SCI2 transmit data number */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI2_Create
* Description  : This function initializes the SCI2 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI2_Create(void)
{
    /* Cancel SCI stop state */
    MSTP(SCI2) = 0U;

    /* Set interrupt priority */
    IPR(SCI2, TXI2) = _0F_SCI_PRIORITY_LEVEL15;

    /* Clear the control register */
    SCI2.SCR.BYTE = 0x00U;

    /* Set clock enable */
    SCI2.SCR.BYTE = _00_SCI_INTERNAL_SCK_UNUSED;

    /* Clear the SIMR1.IICM, SPMR.CKPH, and CKPOL bit, and set SPMR */
    SCI2.SIMR1.BIT.IICM = 0U;
    SCI2.SPMR.BYTE = _00_SCI_RTS | _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;

    /* Set control registers */
    SCI2.SMR.BYTE = _02_SCI_CLOCK_PCLK_16 | _00_SCI_MULTI_PROCESSOR_DISABLE | _00_SCI_STOP_1 | 
                    _00_SCI_PARITY_DISABLE | _00_SCI_DATA_LENGTH_8 | _00_SCI_ASYNCHRONOUS_OR_I2C_MODE;
    SCI2.SCMR.BYTE = _00_SCI_SERIAL_MODE | _00_SCI_DATA_INVERT_NONE | _00_SCI_DATA_LSB_FIRST | 
                     _10_SCI_DATA_LENGTH_8_OR_7 | _62_SCI_SCMR_DEFAULT;
    SCI2.SEMR.BYTE = _00_SCI_BIT_MODULATION_DISABLE | _08_SCI_6_BASE_CLOCK;

    /* Set bit rate */
    SCI2.BRR = 0x40U;

    /* Set TXD2 pin */
    MPC.P13PFS.BYTE = 0x0AU;
    PORT1.PODR.BYTE |= 0x08U;
    PORT1.PDR.BYTE |= 0x08U;

    R_Config_SCI2_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI2_Start
* Description  : This function starts the SCI2 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI2_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI2, TXI2) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI2, TXI2) = 1U;
    ICU.GENBL0.BIT.EN4 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI2_Stop
* Description  : This function stop the SCI2 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI2_Stop(void)
{
    /* Set TXD2 pin */
    PORT1.PMR.BYTE &= 0xF7U;

    /* Disable serial transmit */
    SCI2.SCR.BIT.TE = 0U;

    /* Disable SCI interrupt */
    SCI2.SCR.BIT.TIE = 0U;
    IEN(SCI2, TXI2) = 0U;
    ICU.GENBL0.BIT.EN4 = 0U;
    IR(SCI2, TXI2) = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI2_Serial_Send
* Description  : This function transmits SCI2data
* Arguments    : tx_buf -
*                    transfer buffer pointer (Not used when transmit data handled by DMAC/DTC)
*                tx_num -
*                    buffer size (Not used when transmit data handled by DMAC/DTC)
* Return Value : status -
*                    MD_OK or MD_ARGERROR
***********************************************************************************************************************/

MD_STATUS R_Config_SCI2_Serial_Send(uint8_t * const tx_buf, uint16_t tx_num)
{
    MD_STATUS status = MD_OK;

    if (1U > tx_num)
    {
        status = MD_ARGERROR;
    }
    else
    {
        gp_sci2_tx_address = tx_buf;
        g_sci2_tx_count = tx_num;

        /* Set TXD2 pin */
        PORT1.PMR.BYTE |= 0x08U;
        SCI2.SCR.BYTE |= 0xA0U;
    }

    return (status);
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
