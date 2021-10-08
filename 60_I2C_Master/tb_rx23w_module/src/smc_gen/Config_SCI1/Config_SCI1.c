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
* File Name        : Config_SCI1.c
* Component Version: 1.11.0
* Device(s)        : R5F523W8CxLN
* Description      : This file implements device driver for Config_SCI1.
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
#include "Config_SCI1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
volatile uint8_t   g_sci1_iic_transmit_receive_flag; /* SCI1 transmit receive flag for I2C */
volatile uint8_t   g_sci1_iic_cycle_flag;            /* SCI1 start stop flag for I2C */
volatile uint8_t   g_sci1_slave_address;             /* SCI1 target slave address */
volatile uint8_t * gp_sci1_tx_address;               /* SCI1 transmit buffer address */
volatile uint16_t  g_sci1_tx_count;                  /* SCI1 transmit data number */
volatile uint8_t * gp_sci1_rx_address;               /* SCI1 receive buffer address */
volatile uint16_t  g_sci1_rx_count;                  /* SCI1 receive data number */
volatile uint16_t  g_sci1_rx_length;                 /* SCI1 receive data length */
/* Start user code for global. Do not edit comment generated here */

#define R_Config_SCI1_IIC_Master_Send R_Config_SCI1_IIC_Master_Send__unused
void R_Config_SCI1_IIC_Master_Send__unused(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num);

/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Create
* Description  : This function initializes the SCI1 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_Create(void)
{
    /* Cancel SCI stop state */
    MSTP(SCI1) = 0U;

    /* Set interrupt priority */
    IPR(SCI1,RXI1) = _0F_SCI_PRIORITY_LEVEL15;

    /* Clear the control register */
    SCI1.SCR.BYTE = 0x00U;

    /* Initialize SSCL and SSDA pins to high impedance */
    SCI1.SIMR3.BYTE = _C0_SCI_SSCL_HIGH_IMPEDANCE | _30_SCI_SSDA_HIGH_IMPEDANCE;

    /* Set up transfer or reception format in SMR and SCMR */
    SCI1.SMR.BYTE = _01_SCI_CLOCK_PCLK_4 | _00_SCI_ASYNCHRONOUS_OR_I2C_MODE;
    SCI1.SCMR.BIT.SMIF = 0U;
    SCI1.SCMR.BIT.SINV = 0U;
    SCI1.SCMR.BIT.SDIR = 1U;

    /* Set bit rate */
    SCI1.BRR = 0x01U;
    SCI1.SEMR.BYTE = _00_SCI_NOISE_FILTER_DISABLE | _00_SCI_BIT_MODULATION_DISABLE;
    SCI1.SIMR1.BYTE |= (_01_SCI_IIC_MODE | _00_SCI_NONE);
    SCI1.SIMR2.BYTE |= (_00_SCI_ACK_NACK_INTERRUPTS | _02_SCI_SYNCHRONIZATION | _20_SCI_NACK_TRANSMISSION);
    SCI1.SPMR.BYTE = _00_SCI_CLOCK_NOT_INVERTED | _00_SCI_CLOCK_NOT_DELAYED;
    SCI1.SCR.BYTE = _10_SCI_RECEIVE_ENABLE | _20_SCI_TRANSMIT_ENABLE | _40_SCI_RXI_ERI_ENABLE | _80_SCI_TXI_ENABLE | 
                    _04_SCI_TEI_INTERRUPT_ENABLE;

    /* Set SSCL1 pin */
    MPC.P30PFS.BYTE = 0x0AU;
    PORT3.ODR0.BYTE |= 0x01U;
    PORT3.PMR.BYTE |= 0x01U;

    /* Set SSDA1 pin */
    MPC.P16PFS.BYTE = 0x0AU;
    PORT1.ODR1.BYTE |= 0x10U;
    PORT1.PMR.BYTE |= 0x40U;

    R_Config_SCI1_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Start
* Description  : This function starts the SCI1 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_Start(void)
{
    /* Clear interrupt flag */
    IR(SCI1,TXI1) = 0U;
    IR(SCI1,RXI1) = 0U;

    /* Enable SCI interrupt */
    IEN(SCI1,TXI1) = 1U;
    IEN(SCI1,TEI1) = 1U;
    IEN(SCI1,RXI1) = 1U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_Stop
* Description  : This function stops the SCI1 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_Stop(void)
{
    /* Clear interrupt flag */
    IR(SCI1,TXI1) = 0U;
    IR(SCI1,RXI1) = 0U;

    /* Disable SCI interrupt */
    IEN(SCI1,TXI1) = 0U;
    IEN(SCI1,TEI1) = 0U;
    IEN(SCI1,RXI1) = 0U;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_IIC_StartCondition
* Description  : This function generates IIC start condition
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_IIC_StartCondition(void)
{
    SCI1.SIMR3.BYTE = _01_SCI_START_CONDITION_ON | _10_SCI_SSDA_START_RESTART_STOP_CONDITION | 
                      _40_SCI_SSCL_START_RESTART_STOP_CONDITION;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_IIC_StopCondition
* Description  : This function generates IIC stop condition
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_IIC_StopCondition(void)
{
    SCI1.SIMR3.BYTE = _04_SCI_STOP_CONDITION_ON | _10_SCI_SSDA_START_RESTART_STOP_CONDITION | 
                      _40_SCI_SSCL_START_RESTART_STOP_CONDITION;
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_IIC_Master_Send
* Description  : This function sends simple IIC(SCI1) data to slave device
* Arguments    : adr -
*                    slave device address
*                tx_buf -
*                    transfer buffer pointer (Not used when receive data handled by DTC/DMAC)
*                tx_num -
*                    buffer size (Not used when receive data handled by DTC/DMAC)
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_IIC_Master_Send(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{
    if (tx_num < 1U)
    {
        return;
    }

    gp_sci1_tx_address = tx_buf;
    g_sci1_tx_count = tx_num;
    g_sci1_slave_address = adr;
    g_sci1_iic_transmit_receive_flag = _80_SCI_IIC_TRANSMISSION;
    g_sci1_iic_cycle_flag = _80_SCI_IIC_START_CYCLE;

    /* Generate start condition */
    R_Config_SCI1_IIC_StartCondition();
}

/***********************************************************************************************************************
* Function Name: R_Config_SCI1_IIC_Master_Receive
* Description  : This function receives simple IIC(SCI1) data from slave device
* Arguments    : adr -
*                    slave device address
*                rx_buf -
*                    receive buffer pointer (Not used when receive data handled by DTC/DMAC)
*                rx_num -
*                    buffer size (Not used when receive data handled by DTC/DMAC)
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI1_IIC_Master_Receive(uint8_t adr, uint8_t * const rx_buf, uint16_t rx_num)
{
    if (rx_num < 1U)
    {
        return;
    }

    g_sci1_rx_length = rx_num;
    g_sci1_rx_count = 0;
    gp_sci1_rx_address = rx_buf;
    g_sci1_slave_address = adr;
    g_sci1_iic_transmit_receive_flag = _00_SCI_IIC_RECEPTION;
    g_sci1_iic_cycle_flag = _80_SCI_IIC_START_CYCLE;

    /* Generate start condition */
    R_Config_SCI1_IIC_StartCondition();
}

/* Start user code for adding. Do not edit comment generated here */

#undef R_Config_SCI1_IIC_Master_Send

void R_Config_SCI1_IIC_Master_Send(uint8_t adr, uint8_t * const tx_buf, uint16_t tx_num)
{
#if 0 /* For Renesas HS3001 humidity and temperature sensor (A Renesas QuickConnect IoT Pmod) */
    if (tx_num < 1U)
    {
        return;
    }
#endif /* #if 0 */

    gp_sci1_tx_address = tx_buf;
    g_sci1_tx_count = tx_num;
    g_sci1_slave_address = adr;
    g_sci1_iic_transmit_receive_flag = _80_SCI_IIC_TRANSMISSION;
    g_sci1_iic_cycle_flag = _80_SCI_IIC_START_CYCLE;

    /* Generate start condition */
    R_Config_SCI1_IIC_StartCondition();
}



/* End user code. Do not edit comment generated here */
