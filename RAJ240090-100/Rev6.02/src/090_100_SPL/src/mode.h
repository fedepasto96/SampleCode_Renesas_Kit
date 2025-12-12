/*******************************************************************************
* Copyright(C) 2008, 2019 Renesas Electronics Corporation
* RENESAS ELECTRONICS CONFIDENTIAL AND PROPRIETARY
* This program must be used solely for the purpose for which
* it was furnished by Renesas Electronics Corporation. No part of this
* program may be reproduced or disclosed to others, in any
* form, without the prior written permission of Renesas Electronics
* Corporation.
*******************************************************************************
*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corp. and is only 
* intended for use with Renesas products. No other uses are authorized.
*
* This software is owned by Renesas Electronics Corp. and is protected under 
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY 
* DISCLAIMED.
*
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS 
* ELECTRONICS CORP. NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE 
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES 
* FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS 
* AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*
* http://www.renesas.com/disclaimer

*""FILE COMMENT""***************************************************************
* System Name	: RAJ240080 sample code
* File Name		: mode.h
* Contents		: mode function header file
* Device		: RAJ240080
* Compiler		: CC-RL (V.1.04)
* Note			: 
*""FILE COMMENT END""**********************************************************/

#ifndef _MODE_H
#define _MODE_H


#ifdef	_MODE_C
#define		GLOBAL
#else
#define		GLOBAL	extern
#endif	/* _MODE_C */


/***********************************************************************
Global functions
***********************************************************************/
GLOBAL void Mode_Chk(void);						// MainMode Check
GLOBAL void Alarm_Chk(void);					// Alarm Check
void Slow_Chk(void);							// Slow Check
GLOBAL void AFE_BCVD_EN(void);
GLOBAL void AFE_TVD_EN(void);
GLOBAL WORD Calcvolt_BCVD(WORD tvolt);
GLOBAL WORD Calcvolt_TVD(WORD ttemp);
GLOBAL void AFEWDT_EN(BYTE avalue);
GLOBAL void AFEWDT_DIS(void);
GLOBAL void AFEWDT_REFRESH(void);


/***********************************************************************
Global define
***********************************************************************/
GLOBAL BYTE		amodeflg;						// Flags for mode
												// Flags for mode (1)
#define	f_slow		DEF_BIT0(&amodeflg)			// Slow mode flag
#define f_crelearn 	DEF_BIT1(&amodeflg)			// Charging Relearn flag



#define tfc_cnt		_tfc_cnt.us
#define afc_cnt		_tfc_cnt.uc




/***********************************************************************
	Constant definitions
***********************************************************************/
												// - Mode -
#define M_INIT			0x00					// Init
#define M_WAKE			0x01					// Wake Up
#define M_DIS			0x02					// Discharging
#define M_CHG			0x03					// Charging
#define M_TERM			0x05					// Charge Terminate
#define M_CWIT			0x06					// Charge Wait
#define M_PREC			0x07					// Pre Charge
#define M_ALON			0x09					// Sleep
#define M_COH			0x10					// Charge Over Heat
#define M_DOH			0x11					// Discharge Over Heat
#define M_OCC			0x12					// Over Charge Current
#define M_ODC			0x13					// Over Discharge Current
#define M_SHC			0x14					// Short Current
#define M_OV			0x15					// Over Voltage
#define M_FOH			0x16					// 2nd TH Over Heat
#define M_DOWN			0x1E					// Power Down
#define M_CALIB			0x20					// Initial Calibration
#define M_FIXEDERR		0x99					// Fixed data error

#define	WDTCLEAR		0xFF

#undef		GLOBAL

#endif

