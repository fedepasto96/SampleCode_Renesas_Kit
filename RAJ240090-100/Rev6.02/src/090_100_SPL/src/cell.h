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
* Renesas reserves the right, without notice, to make changes to this 
* software and to discontinue the availability of this software.  
* By using this software, you agree to the additional terms and 
* conditions found by accessing the following link:
* http://www.renesas.com/disclaimer
******************************************************************************/
/*""FILE COMMENT""*******************************************************
* System Name	: RAJ240090 Sample Code
* File Name		: cell.h
* Version		: 1.00
* Contents		: 
* Programmer		: Yasuo Usuda
* Note			: 
*""FILE COMMENT END""**********************************************************/

#ifndef _CELL_H
#define _CELL_H

#ifdef	_CELL
#define		GLOBAL
#else
#define		GLOBAL	extern
#endif	/* _CELL */

// - Control flag definition -
typedef struct
{
	BYTE f_2ndthe	:1;		// bit  0 : 2nd Th using flag
	BYTE f_cben		:1;		// bit  1 : Cell balancing enable
	BYTE f_calib1p	:1;		// bit  2 : Calibration 1 point flag
	BYTE f_initcap	:1;		// bit  3 : InitCap table using flag
	BYTE f_sysconen	:1;		// bit  4 : SYS-connect using flag
	BYTE f_bcvden	:1;		// bit  5 : Battery Cell Voltage Detection using flag
	BYTE f_tvden	:1;		// bit  6 : Temperature Voltage Detection using flag
	BYTE f_usedfdat	:1;		// bit  7 : Initialize with Flexible data using flag
	BYTE f_impen	:1;		// bit  8 : IMP calc enable flag
	BYTE DUMMY9		:1;		// bit  9 : Resreved
	BYTE DUMMY10	:1;		// bit 10 : Resreved
	BYTE DUMMY11	:1;		// bit 11 : Resreved
	BYTE DUMMY12	:1;		// bit 12 : Resreved
	BYTE DUMMY13	:1;		// bit 13 : Resreved
	BYTE DUMMY14	:1;		// bit 14 : Resreved
	BYTE DUMMY15	:1;		// bit 15 : Reserved
}_ST_CTLFLG1;

// - FlashROM fixed data definition -
typedef struct
{
	// Voltage
	WORD	d_NORMAL_CV;		// 0x1C400 [2byte] Charging voltage
								// 0x1C401
	WORD	d_NORMAL_CC;		// 0x1C402 [2byte] Charging current
								// 0x1C403
	WORD	d_CHGWAIT_CC;		// 0x1C404 [2byte] Charging current at Charge Wait
								// 0x1C405
	WORD	d_FULLCHGHV;		// 0x1C406 [2byte] Fullcharge judgement voltage
								// 0x1C407
	WORD	d_FULLCHG_TV;		// 0x1C408 [2byte] Fullcharge taper voltage
								// 0x1C409
	WORD	d_FULLCHG_CURR;		// 0x1C40A [2byte] Fullcharge judgement current
								// 0x1C40B 
	WORD	d_FULLCHG_T;		// 0x1C40C [2byte] Fullcharge judgement time
								// 0x1C40D
	WORD	d_DISSTOPV;			// 0x1C40E [2byte] Discharge stop voltage
								// 0x1C40F
	WORD	d_PDVOLT;			// 0x1C410 [2byte] Power Down voltage
								// 0x1C411
	WORD	d_0PVOLT;			// 0x1C412 [2byte] 0% voltage
								// 0x1C413
	// Current
	WORD	d_DCDET;			// 0x1C414 [2byte] Discharge detection current
								// 0x1C415
	WORD	d_CCDET;			// 0x1C416 [2byte] Charge detection current
								// 0x1C417
	WORD	d_SLPCURR;			// 0x1C418 [2byte] Sleep Current
								// 0x1C419
	WORD	d_MSKCURR;			// 0x1C41A [2byte] Mask Current
								// 0x1C41B
	// Temperature
	// Discharge over temp
	_SBYTE	d_DOTH;				// 0x1C41C [1byte] Discharge over temperature (H)
	_SBYTE	d_DOTL;				// 0x1C41D [1byte] Discharge over temperature (L)
	_SBYTE	d_DTH_hys;			// 0x1C41E [1byte] Discharge over temperature release hysteresis
	BYTE	d_rsv_01;			// 0x1C41F [1byte] Reserved(Padding)
	// Charge over temp
	_SBYTE	d_COTH;				// 0x1C420 [1byte] Charge Over temperature (H)
	_SBYTE	d_COTL;				// 0x1C421 [1byte] Charge Over temperature (L)
	_SBYTE	d_CTH_hys;			// 0x1C422 [1byte] Charge Over temperature release hysteresis
	_SBYTE	d_rsv_02;			// 0x1C423 [1byte] Reserved(Padding)
	// Charge over temp
	BYTE	d_2NDTHM;			// 0x1C424 [1byte] 2nd Thermistor over temperature
	BYTE	d_2NDTHM_hys;		// 0x1C425 [1byte] 2nd Thermistor release temperature
	
	
	WORD	d_THERM_TBL[8];		// 0x1C426 [16byte] Thermistor table
								//    |
								// 0x1C435
	WORD	d_ttempidx[8];		// 0x1C436 [16byte] Thermistor characteristic temperature index table
								//    |
								// 0x1C445
	WORD	d_2NDTHERM_TBL[8];	// 0x1C446 [16byte] 2nd Thermistor table
								//    |
								// 0x1C455
	
	WORD	d_2ndttempidx[8];	// 0x1C456 [16byte] 2nd Thermistor characteristic temperature index table
								//    |
								// 0x1C465
	
	// Device info
	BYTE	d_SERIES;			// 0x1C466 [1byte] Series number of Cell
	BYTE	d_rsv_03;			// 0x1C467 [1byte] Reserved(Padding)
	BYTE	d_MF_NAME[32];		// 0x1C468 [32byte] 0x20:ManufacutereName
								//    |	
								// 0x1C487
	BYTE	d_Dev_NAME[32];		// 0x1C488 [32byte] 0x21:DeviceName
								//    |	
								// 0x1C4A7			
	BYTE	d_Dev_chem[4];		// 0x1C4A8 [4byte] 0x22:DeviceChemistry
								// 0x1C4A9
								// 0x1C4AA
								// 0x1C4AB
	BYTE	d_SMB_addr;			// 0x1C4AC [1byte] SMBus slave address
	BYTE	d_rsv_04;			// 0x1C4AD [1byte] Reserved(Padding)
	_ST_CTLFLG1	d_CTLFLG1;		// 0x1C4AE [2byte] Control flag 1
								// 0x1C4AF
	
	// Capacity
	BYTE	d_INIT_RSOC;		// 0x1C4B0 [1byte] Initial RelativeStateOfCharge
	BYTE	d_rsv_05;			// 0x1C4B1 [1byte] Reserved(Padding)
	WORD	d_INIT_FCC;			// 0x1C4B2 [2byte] Initial FullChargeCapacity
								// 0x1C4B3
	WORD	d_CCP_V;			// 0x1C4B4 [2byte] Capacity correction point voltage
								// 0x1C4B5
	BYTE	d_CCP_lvl;			// 0x1C4B6 [1byte] Capacity correction point level
	BYTE	d_rsv_06;			// 0x1C4B7 [1byte] Reserved(Padding)
	
	BYTE	INITCAP_tbl[6];		// 0x1C4B8 [6byte] Initial capacity table
								// 0x1C4B9
								// 0x1C4BA
								// 0x1C4BB
								// 0x1C4BC
								// 0x1C4BD
	WORD	INITV_tbl[6];		// 0x1C4BE [12byte] Initial voltage table
								//    |	
								// 0x1C4C9
	// Protection (Firmware)							
	WORD	d_CBONV;			// 0x1C4CA [2byte] Cell balancing ON voltage
								// 0x1C4CB
	WORD	d_CBOFFV;			// 0x1C4CC [2byte] Cell balancing OFF voltage
								// 0x1C4CD
	WORD	d_CBENVH;			// 0x1C4CE [2byte] Cell balancing enable voltage(H)
								// 0x1C4CF
	WORD	d_CBENVL;			// 0x1C4D0 [2byte] Cell balancing enable voltage(L)
								// 0x1C4D1
	WORD	d_OVERCH1;			// 0x1C4D2 [2byte] Charge over current 1
								// 0x1C4D3
	BYTE	d_OCC1JT;			// 0x1C4D4 [1byte] Charge over current 1 judgement time
	BYTE	d_rsv_07;			// 0x1C4D5 [1byte] Reserved(Padding)
	WORD	d_OVERCH2;			// 0x1C4D6 [2byte] Charge over current 2
								// 0x1C4D7
	BYTE	d_OCC2JT;			// 0x1C4D8 [1byte] Charge over current 2 judgement time
	BYTE	d_rsv_08;			// 0x1C4D9 [1byte] Reserved(Padding)
	WORD	d_OVERDI1;			// 0x1C4DA [2byte] Discharge over current 1
								// 0x1C4DB
	BYTE	d_ODC1JT;			// 0x1C4DC [1byte] Discharge over current 1 judgement time
	BYTE	d_rsv_09;			// 0x1C4DD [1byte] Reserved(Padding)
	WORD	d_OVERDI2;			// 0x1C4DE [2byte] Discharge over current 2
								// 0x1C4DF
	BYTE	d_ODC2JT;			// 0x1C4E0 [1byte] Discharge over current 2 judgement time
	BYTE	d_rsv_0A;			// 0x1C4E1 [1byte] Reserved(Padding)
	
	WORD	d_CHGPV;			// 0x1C4E2 [2byte] Charge protection voltage
								// 0x1C4E3
	BYTE	d_CHGPVJT;			// 0x1C4E4 [1byte] Charge protection voltage judgment time
	BYTE	d_rsv_27;			// 0x1C4E5 [1byte] Reserved
	
	// Protection (Hardware)
	_STC_BIT	d_HWOCDFLG;		// 0x1C4E6 [1byte] HW OCD Protection control flag
	BYTE	d_SCDCON;			// 0x1C4E7 [1byte] HW SCDCON setting
	BYTE	d_SCDTIME;			// 0x1C4E8 [1byte] HW SCDTIME setting
	BYTE	d_DOC1DCON;			// 0x1C4E9 [1byte] HW DOC1DCON setting
	BYTE	d_DOC2DCON;			// 0x1C4EA [1byte] HW DOC2DCON setting
	BYTE	d_DOC3DCON;			// 0x1C4EB [1byte] HW DOC3DCON setting
	BYTE	d_DOC4DCON;			// 0x1C4EC [1byte] HW DOC4DCON setting
	BYTE	d_DOC1DTIME1;		// 0x1C4ED [1byte] HW DOC1DTIME setting
	BYTE	d_DOC1DTIME2;		// 0x1C4EE [1byte] HW DOC1DTIME setting
	BYTE	d_DOC2DTIME1;		// 0x1C4EF [1byte] HW DOC2DTIME setting
	BYTE	d_DOC2DTIME2;		// 0x1C4F0 [1byte] HW DOC2DTIME setting
	BYTE	d_DOC3DTIME1;		// 0x1C4F1 [1byte] HW DOC3DTIME setting
	BYTE	d_DOC3DTIME2;		// 0x1C4F2 [1byte] HW DOC3DTIME setting
	BYTE	d_DOC4DTIME1;		// 0x1C4F3 [1byte] HW DOC4DTIME setting
	BYTE	d_DOC4DTIME2;		// 0x1C4F4 [1byte] HW DOC4DTIME setting
	BYTE	d_COCDCON;			// 0x1C4F5 [1byte] HW COCDCON setting
	BYTE	d_COCDTIME;			// 0x1C4F6 [1byte] HW COCDTIME setting
	BYTE	d_rsv_10;			// 0x1C4F7 [1byte] Reserved
	
	//Impedance Calculation
	WORD    d_INIT_IMP;			// 0x1C4F8 [2byte] INIT IMP [0.1mOhm]
								// 0x1C4F9
	WORD    d_IMP_CURR;			// 0x1C4FA [1byte] IMP current [mA]
								// 0x1C4FB
	BYTE    d_RSOC_IMP;			// 0x1C4FC [1byte] RSOC IMP  [%]
	_SBYTE  d_IMP_TEMPL;		// 0x1C4FD [1byte] IMP Temp L [degC]
	_SBYTE  d_IMP_TEMPH;		// 0x1C4FE [1byte] IMP Temp H [degC]
	BYTE	d_STR_TEMP;			// 0x1C4FF [1byte] Storage temp
	WORD	d_STR_DLTV;			// 0x1C500 [2byte] Storage delta Volt
								// 0x1C501	
	// BCVD Function
	BYTE	d_OVUVDET;			// 0x1C502 [1byte] Over/Under Voltage Detection Control Register
	BYTE	d_VDCT;				// 0x1C503 [1byte] Voltage detection AD conversion time Register
	BYTE	d_VDIT;				// 0x1C504 [1byte] Voltage Detection Interval Time Register
	BYTE	d_rsv_28;			// 0x1C505 [1byte] Reserved
	WORD	d_UVDH;				// 0x1C506 [2byte] Under Voltage Detection Threshold
								// 0x1C507
	WORD	d_OVDH;				// 0x1C508 [2byte] Over Voltage Detection Threshold
								// 0x1C509
	
	BYTE	d_OTUTDET;			// 0x1C50A [1byte] Over/Under temperature  Detection Control Register
	BYTE	d_rsv_29;			// 0x1C50B [1byte] Reserved
	WORD	d_UTDH;				// 0x1C50C [2byte] Under Temperature Detection Threshold
								// 0x1C50D
	WORD	d_OTDH;				// 0x1C50E [2byte] Over Temperature Detection Threshold
								// 0x1C50F
}_ST_FIXED_DATA;

#pragma address u_fd = 0x01C400
GLOBAL _ST_FIXED_DATA __far u_fd;

// Voltage,current,temperature
#define	NORMAL_CV		u_fd.d_NORMAL_CV	// [2byte] Charging voltage
#define	NORMAL_CC		u_fd.d_NORMAL_CC	// [2byte] Charging current
#define	CHGWAIT_CC		u_fd.d_CHGWAIT_CC	// [2byte] Charging current at Charge Wait
#define	FULLCHGHV		u_fd.d_FULLCHGHV	// [2byte] Fullcharge judgement voltage
#define	FULLCHG_TV		u_fd.d_FULLCHG_TV	// [2byte] Fullcharge taper voltage
#define	FULLCHG_CURR	u_fd.d_FULLCHG_CURR // [2byte] Fullcharge judgement current
#define	FULLCHG_T		u_fd.d_FULLCHG_T	// [2byte] Fullcharge judgement time
#define	DISSTOPV		u_fd.d_DISSTOPV		// [2byte] Discharge stop voltage
#define	D_PDVOLT		u_fd.d_PDVOLT		// [2byte] Power Down voltage
#define	D_0PVOLT		u_fd.d_0PVOLT		// [2byte] 0% voltage
#define	D_DCDET			u_fd.d_DCDET		// [2byte] Discharge detection current
#define	D_CCDET			u_fd.d_CCDET		// [2byte] Charge detection current
#define	D_SLPCURR		u_fd.d_SLPCURR		// [2byte] Sleep Current
#define	D_MSKCURR		u_fd.d_MSKCURR		// [2byte] Mask Current
#define	DOTH			u_fd.d_DOTH			// [1byte] Discharge over temperature (H)
#define	DOTL			u_fd.d_DOTL			// [1byte] Discharge over temperature (L)
#define	DTH_hys			u_fd.d_DTH_hys		// [1byte] Discharge over temperature release hysteresis
#define	COTH			u_fd.d_COTH			// [1byte] Charge over temperature (H)
#define	COTL			u_fd.d_COTL			// [1byte] Charge over temperature (L)
#define	CTH_hys			u_fd.d_CTH_hys		// [1byte] Charge over temperature release hysteresis
#define	D_2NDTHM		u_fd.d_2NDTHM		// [1byte] 2nd Thermistor over temperature
#define	D_2NDTHM_hys	u_fd.d_2NDTHM_hys	// [1byte] 2nd Thermistor release temperature
#define	THERM_TBL		u_fd.d_THERM_TBL	// [16byte] Thermistor table
#define	ttempidx		u_fd.d_ttempidx		// [16byte] Thermistor characteristic temperature index table
#define	D_2NDTHERM_TBL	u_fd.d_2NDTHERM_TBL	// [16byte] 2nd Thermistor table
#define	D_2ndttempidx	u_fd.d_2ndttempidx	// [16byte] 2nd Thermistor characteristic temperature index table

// Device info
#define	D_SERIES		u_fd.d_SERIES				// [1byte] Series number of Cell
#define MF_NAME			u_fd.d_MF_NAME				// [32byte] ManufacutereName
#define Dev_NAME		u_fd.d_Dev_NAME				// [32byte] DeviceName
#define Dev_chem		u_fd.d_Dev_chem				// [4byte]  DeviceChemistry
#define	SMB_addr		u_fd.d_SMB_addr				// [1byte] SMBus slave address

#define CONFLG			u_fd.d_CTLFLG1				// [2byte] Control flag 1
#define F_2NDTHE		u_fd.d_CTLFLG1.f_2ndthe		// bit 0
#define F_CBEN			u_fd.d_CTLFLG1.f_cben		// bit 1
#define F_CALIB1P		u_fd.d_CTLFLG1.f_calib1p	// bit 2
#define	F_INITCAP		u_fd.d_CTLFLG1.f_initcap	// bit 3
#define	F_SYSCONEN		u_fd.d_CTLFLG1.f_sysconen	// bit 4
#define	F_BCVDEN		u_fd.d_CTLFLG1.f_bcvden		// bit 5
#define	F_TVDEN			u_fd.d_CTLFLG1.f_tvden		// bit 6
#define	F_USEDFDAT		u_fd.d_CTLFLG1.f_usedfdat	// bit 7
#define	F_IMPEN			u_fd.d_CTLFLG1.f_impen		// bit 8


// Capacity
#define	INIT_RSOC		u_fd.d_INIT_RSOC			// [1byte] Initial RelativeStateOfCharge
#define	INIT_FCC		u_fd.d_INIT_FCC				// [2byte] Initial FullChargeCapacity
#define	CCP_V			u_fd.d_CCP_V				// [2byte] Capacity correction point voltage
#define	CCP_lvl			u_fd.d_CCP_lvl				// [1byte] Capacity correction point level

#define INITCAP_TBL		u_fd.INITCAP_tbl			// [6byte] Initial capacity table
#define INITV_TBL		u_fd.INITV_tbl				// [12byte] Initial voltage table

// Protection
#define D_CBONV			u_fd.d_CBONV				// [2byte] Cell balancing ON voltage
#define D_CBOFFV		u_fd.d_CBOFFV				// [2byte] Cell balancing OFF voltage
#define D_CBENVH		u_fd.d_CBENVH				// [2byte] Cell balancing enable voltage(H)
#define D_CBENVL		u_fd.d_CBENVL				// [2byte] Cell balancing enable voltage(L)

#define	OVERCH1			u_fd.d_OVERCH1				// [2byte] Charge over current 1
#define	OCC1JT			u_fd.d_OCC1JT				// [1byte] Charge over current 1 judgement time
#define	OVERCH2			u_fd.d_OVERCH2				// [2byte] Charge over current 2
#define	OCC2JT			u_fd.d_OCC2JT				// [1byte] Charge over current 2 judgement time

#define	OVERDI1			u_fd.d_OVERDI1				// [2byte] Discharge over current 1
#define	ODC1JT			u_fd.d_ODC1JT				// [1byte] Discharge over current 1 judgement time
#define	OVERDI2			u_fd.d_OVERDI2				// [2byte] Discharge over current 2
#define	ODC2JT			u_fd.d_ODC2JT				// [1byte] Discharge over current 2 judgement time
#define	CHGPV			u_fd.d_CHGPV				// [2byte] Charge protection voltage
#define	CHGPVJT			u_fd.d_CHGPVJT				// [1byte] Charge protection voltage judgment time

#define HWOCDFLG		u_fd.d_HWOCDFLG				// [1byte] HW OCD Control flag
#define F_HWOCDEN		u_fd.d_HWOCDFLG.bit0		// bit  0 : HW OCD EN FLAG

// HW register setting
#define D_SCDCON		u_fd.d_SCDCON				// [1byte] Short-circuit Current detection Control Register
#define D_SCDTIME		u_fd.d_SCDTIME				// [1byte] Short-circuit Current detection Time setting Register
#define D_DOC1DCON		u_fd.d_DOC1DCON				// [1byte] Discharge Overcurrent Detection 1 Control Register
#define D_DOC2DCON		u_fd.d_DOC2DCON				// [1byte] Discharge Overcurrent Detection 2 Control Register
#define D_DOC3DCON		u_fd.d_DOC3DCON				// [1byte] Discharge Overcurrent Detection 3 Control Register
#define D_DOC4DCON		u_fd.d_DOC4DCON				// [1byte] Discharge Overcurrent Detection 4 Control Register
#define D_DOC1DTIME1	u_fd.d_DOC1DTIME1			// [1byte] Discharge Overcurrent Detection 1 Time Register 1
#define D_DOC1DTIME2	u_fd.d_DOC1DTIME2			// [1byte] Discharge Overcurrent Detection 1 Time Register 2
#define D_DOC2DTIME1	u_fd.d_DOC2DTIME1			// [1byte] Discharge Overcurrent Detection 2 Time Register 1
#define D_DOC2DTIME2	u_fd.d_DOC2DTIME2			// [1byte] Discharge Overcurrent Detection 2 Time Register 2
#define D_DOC3DTIME1	u_fd.d_DOC3DTIME1			// [1byte] Discharge Overcurrent Detection 3 Time Register 1
#define D_DOC3DTIME2	u_fd.d_DOC3DTIME2			// [1byte] Discharge Overcurrent Detection 3 Time Register 2
#define D_DOC4DTIME1	u_fd.d_DOC4DTIME1			// [1byte] Discharge Overcurrent Detection 4 Time Register 1
#define D_DOC4DTIME2	u_fd.d_DOC4DTIME2			// [1byte] Discharge Overcurrent Detection 4 Time Register 2
#define D_COCDCON		u_fd.d_COCDCON				// [1byte] Charge Overcurrent Detection Control Register
#define D_COCDTIME		u_fd.d_COCDTIME				// [1byte] Charge Overcurrent Detection Time Register

// Impedance Calculation
#define D_INIT_IMP		u_fd.d_INIT_IMP				// [2byte] INIT IMP [0.1mOhm]
#define D_IMP_CURR		u_fd.d_IMP_CURR				// [1byte] IMP current [mA]		
#define D_RSOC_IMP		u_fd.d_RSOC_IMP				// [1byte] RSOC IMP [%]
#define D_IMP_TEMPL		u_fd.d_IMP_TEMPL			// [1byte] IMP Temp L [degC]
#define D_IMP_TEMPH		u_fd.d_IMP_TEMPH			// [1byte] IMP Temp H [degC]

#define D_STR_TEMP		u_fd.d_STR_TEMP				// [1byte] Storage Temp[degC]
#define D_STR_DLTV		u_fd.d_STR_DLTV				// [2byte] Storage delta Volt[mV]


#define	D_OVUVDET		u_fd.d_OVUVDET				// [1byte] Over/Under Voltage Detection Control Register
#define	D_VDCT			u_fd.d_VDCT					// [1byte] Voltage detection AD conversion time Register
#define	D_VDIT			u_fd.d_VDIT					// [1byte] Voltage Detection Interval Time Register
#define	D_UVDH			u_fd.d_UVDH					// [2byte] Under Voltage Detection Threshold
#define	D_OVDH			u_fd.d_OVDH					// [2byte] Over Voltage Detection Threshold
#define	D_OTUTDET		u_fd.d_OTUTDET				// [1byte] Over/Under Tempeature Detection Control Register
#define	D_UTDH			u_fd.d_UTDH					// [2byte] Under Temperature Detection Threshold
#define	D_OTDH			u_fd.d_OTDH					// [2byte] Over Temperature Detection Threshold


/***********************************************************************
Global functions
***********************************************************************/
GLOBAL BYTE InitFixed_Chk(void);								// Check process on fixed data

#undef		GLOBAL

#endif
