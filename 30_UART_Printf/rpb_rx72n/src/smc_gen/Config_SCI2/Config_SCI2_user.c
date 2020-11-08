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
* File Name    : Config_SCI2_user.c
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
extern volatile uint8_t * gp_sci2_tx_address;                /* SCI2 transmit buffer address */
extern volatile uint16_t  g_sci2_tx_count;                   /* SCI2 transmit data number */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_SCI2_Create_UserInit
* Description  : This function adds user code after initializing the SCI2 channel
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void R_Config_SCI2_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI2_transmit_interrupt
* Description  : This function is TXI2 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

#if FAST_INTERRUPT_VECTOR == VECT_SCI2_TXI2
#pragma interrupt r_Config_SCI2_transmit_interrupt(vect=VECT(SCI2,TXI2),fint)
#else
#pragma interrupt r_Config_SCI2_transmit_interrupt(vect=VECT(SCI2,TXI2))
#endif
static void r_Config_SCI2_transmit_interrupt(void)
{
    if (0U < g_sci2_tx_count)
    {
        SCI2.TDR = *gp_sci2_tx_address;
        gp_sci2_tx_address++;
        g_sci2_tx_count--;
    }
    else
    {
        SCI2.SCR.BIT.TIE = 0U;
        SCI2.SCR.BIT.TEIE = 1U;
    }
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI2_transmitend_interrupt
* Description  : This function is TEI2 interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

void r_Config_SCI2_transmitend_interrupt(void)
{
    /* Set TXD2 pin */
    PORT1.PMR.BYTE &= 0xF7U;

    SCI2.SCR.BIT.TIE = 0U;
    SCI2.SCR.BIT.TE = 0U;
    SCI2.SCR.BIT.TEIE = 0U;
    
    r_Config_SCI2_callback_transmitend();
}

/***********************************************************************************************************************
* Function Name: r_Config_SCI2_callback_transmitend
* Description  : This function is a callback function when SCI2 finishes transmission
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/

static void r_Config_SCI2_callback_transmitend(void)
{
    /* Start user code for r_Config_SCI2_callback_transmitend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */



