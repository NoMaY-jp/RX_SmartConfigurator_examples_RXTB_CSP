/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
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
* Copyright (C) 2016, 2017 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : rpbx72ndef.h
* Device(s)    : R5F572NNHDFB
* Tool-Chain   : CCRX
* H/W Platform : RX72N Envision Kit
* Description  : Defines macros relating to the RX72N Envision Kit user LED
***********************************************************************************************************************/

/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 07.11.2020 1.00     First Release
***********************************************************************************************************************/
/* Multiple inclusion prevention macro */
#ifndef RPBRX72N_H
#define RPBRX72N_H

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* General Values */
#define LED_ON          (0)
#define LED_OFF         (1)
#define SW1_PUSH        (0)
#define SW1_RELEASE     (1)

/* Switches (and its notation in the User's Manual) */
#define SW1/*(SW2)*/	(PORT0.PIDR.BIT.B7)

/* LED port settings (and its notation in the User's Manual) */
#define LED0/*(LED2)*/	(PORT4.PODR.BIT.B0)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global variables
***********************************************************************************************************************/

/***********************************************************************************************************************
Exported global functions (to be accessed by other files)
***********************************************************************************************************************/

#endif
