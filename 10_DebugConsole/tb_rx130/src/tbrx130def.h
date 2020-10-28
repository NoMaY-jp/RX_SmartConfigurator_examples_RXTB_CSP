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
* File Name    : tbrx130def.h
* Device(s)    : R5F51308ADFP
* Tool-Chain   : CCRX
* H/W Platform : Target Board for RX130
* Description  : Defines macros relating to the Target Board for RX130 user LEDs and switches
***********************************************************************************************************************/

/**********************************************************************************************************************
* History : DD.MM.YYYY Version  Description
*         : 15.09.2017 1.00     First Release
***********************************************************************************************************************/
/* Multiple inclusion prevention macro */
#ifndef TBRX130_H
#define TBRX130_H

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/* General Values */
#define LED_ON          (0)
#define LED_OFF         (1)
#define SW1_PUSH        (0)
#define SW1_RELEASE     (1)

/* Switches */
#define SW1             (PORTB.PIDR.BIT.B1)

/* LED port settings */
#define LED0            (PORTD.PODR.BIT.B6)
#define LED1            (PORTD.PODR.BIT.B7)

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
