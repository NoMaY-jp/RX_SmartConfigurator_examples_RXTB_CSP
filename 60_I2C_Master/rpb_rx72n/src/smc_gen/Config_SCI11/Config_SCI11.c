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
* File Name    : Config_SCI11.c
* Version      : 1.9.1
* Device(s)    : R5F572NNHxFB
* Description  : This file implements device driver for Config_SCI11.
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
#include "Config_SCI11.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t   g_sci11_iic_transmit_receive_flag; /* SCI11 transmit receive flag for I2C */
volatile uint8_t   g_sci11_iic_cycle_flag;            /* SCI11 start stop flag for I2C */
volatile uint8_t   g_sci11_slave_address;             /* SCI11 target slave address */
volatile uint8_t * gp_sci11_tx_address;               /* SCI11 transmit buffer address */
volatile uint16_t  g_sci11_tx_count;                  /* SCI11 transmit data number */
volatile uint8_t * gp_sci11_rx_address;               /* SCI11 receive buffer address */
volatile uint16_t  g_sci11_rx_count;                  /* SCI11 receive data number */
volatile uint16_t  g_sci11_rx_length;                 /* SCI11 receive data length */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI11_Create
* Description  : This function initializes the SCI11 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI11_Create(void)
{
    /* Cancel SCI stop state */
    MSTP(SCI11) = 0U;

    /* Set interrupt priority */
    IPR(SCI11, RXI11) = _0F_SCI_PRIORITY_LEVEL15;
    IPR(SCI11, TXI11) = _0F_SCI_PRIORITY_LEVEL15;

    /* Clear the control register */
    SCI11.SCR.BYTE = 0x00U;

    /* Initialize SSCL and SSDA pins to high impedance */
    SCI11.SIMR3.BYTE = _C0_SCI_SSCL_HIGH_IMPEDANCE | _30_SCI_SSDA_HIGH_IMPEDANCE;

    /* Set up transfer or reception format in SMR and SCMR */
    SCI11.SMR.BYTE = _00_SCI_CLOCK_PCLK | _00_SCI_ASYNCHRONOUS_OR_I2C_MODE;
    SCI11.SCMR.BIT.SMIF = 0U;
    SCI11.SCMR.BIT.SINV = 0U;
    SCI11.SCMR.BIT.SDIR = 1U;

    /* Set bit rate */
    SCI11.BRR = 0x25U;
    SCI11.SEMR.BYTE = _00_SCI_NOISE_FILTER_DISABLE | _00_SCI_BIT_MODULATION_DISABLE;
    SCI11.SIMR1.BYTE |= (_01_SCI_IIC_MODE | _00_SCI_NONE);
    SCI11.SIMR2.BYTE |= (_00_SCI_ACK_NACK_INTERRUPTS | _02_SCI_SYNCHRONIZATION | _20_SCI_NACK_TRANSMISSION);
    SCI11.SPMR.BYTE = _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;
    SCI11.SCR.BYTE = _10_SCI_RECEIVE_ENABLE | _20_SCI_TRANSMIT_ENABLE | _40_SCI_RXI_ERI_ENABLE | _80_SCI_TXI_ENABLE | 
                     _04_SCI_TEI_INTERRUPT_ENABLE;

    /* Set SSCL11 pin */
    MPC.PB6PFS.BYTE = 0x24U;
    PORTB.ODR1.BYTE |= 0x10U;
    PORTB.PMR.BYTE |= 0x40U;

    /* Set SSDA11 pin */
    MPC.PB7PFS.BYTE = 0x24U;
    PORTB.ODR1.BYTE |= 0x40U;
    PORTB.PMR.BYTE |= 0x80U;

    R_Config_SCI11_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI11_Start
* Description  : This function starts the SCI11 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI11_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI11,TXI11) = 0U;
    IR(SCI11,RXI11) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI11,TXI11) = 1U;
    ICU.GENAL0.BIT.EN12 = 1U;
    IEN(SCI11,RXI11) = 1U;
    ICU.GENAL0.BIT.EN13 = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI11_Stop
* Description  : This function stops the SCI11 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI11_Stop(void)
{
    IR(SCI11,TXI11) = 0U;
    IEN(SCI11,TXI11) = 0U;
    ICU.GENAL0.BIT.EN12 = 0U;
    IR(SCI11,RXI11) = 0U;
    IEN(SCI11,RXI11) = 0U;
    ICU.GENAL0.BIT.EN13 = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI11_IIC_StartCondition
* Description  : This function generates IIC start condition
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI11_IIC_StartCondition(void)
{
    SCI11.SIMR3.BYTE = _01_SCI_START_CONDITION_ON | _10_SCI_SSDA_START_RESTART_STOP_CONDITION | 
                       _40_SCI_SSCL_START_RESTART_STOP_CONDITION;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI11_IIC_StopCondition
* Description  : This function generates IIC stop condition
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI11_IIC_StopCondition(void)
{
    SCI11.SIMR3.BYTE = _04_SCI_STOP_CONDITION_ON | _10_SCI_SSDA_START_RESTART_STOP_CONDITION | 
                       _40_SCI_SSCL_START_RESTART_STOP_CONDITION;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI11_IIC_Master_Send
* Description  : This function sends simple IIC(SCI11) data to slave device
* Arguments    : adr -
*                    slave device address
*                tx_buf -
*                    transfer buffer pointer (Not used when receive data handled by DTC or DMAC)
*                tx_num -
*                    buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI11_IIC_Master_Send(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{
    if (tx_num < 1U)
    {
        return;
    }

    gp_sci11_tx_address = tx_buf;
    g_sci11_tx_count = tx_num;
    g_sci11_slave_address = adr;
    g_sci11_iic_transmit_receive_flag = _80_SCI_IIC_TRANSMISSION;
    g_sci11_iic_cycle_flag = _80_SCI_IIC_START_CYCLE;

    /* Generate start condition */
    R_Config_SCI11_IIC_StartCondition();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI11_IIC_Master_Receive
* Description  : This function receives simple IIC(SCI11) data from slave device
* Arguments    : adr -
*                    slave device address
*                rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC or DMAC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DTC or DMAC)
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI11_IIC_Master_Receive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num)
{
    if (rx_num < 1U)
    {
        return;
    }

    g_sci11_rx_length = rx_num;
    g_sci11_rx_count = 0;
    gp_sci11_rx_address = rx_buf;
    g_sci11_slave_address = adr;
    g_sci11_iic_transmit_receive_flag = _00_SCI_IIC_RECEPTION;
    g_sci11_iic_cycle_flag = _80_SCI_IIC_START_CYCLE;

    /* Generate start condition */
    R_Config_SCI11_IIC_StartCondition();
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

