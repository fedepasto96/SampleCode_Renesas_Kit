/******************************************************************************
* DISCLAIMER																	*
* This software is supplied by Renesas Electronics Corp. and is only 
* intended for use with Renesas products. No other uses are authorized.
*
* This software is owned by Renesas Electronics Corp. and is protected under 
* all applicable laws, including copyright laws.
*
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES 
* REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, 
* INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
* PARTICULAR PURPOSE AND NON-INFRINGEMENT.	ALL SUCH WARRANTIES ARE EXPRESSLY 
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
* File Name		: ram.h
* Version		: 1.00
* Contents		: 
* Programmer	: Yasuo Usuda
* Note			: 
************************************************************************
* Copyright(C) 2016, 2019 RENESAS ELECTRONICS CORPORATION
************************************************************************
 * History			: 2016.02.15 Ver 1.00
 *					:  New Create
 *					: 
*""FILE COMMENT END""**************************************************/
#ifndef _RAM_H
#define _RAM_H


#ifdef	_RAM
#define			GLOBAL
#else
#define			GLOBAL	extern
#endif	/* _RAM */




/***********************************************************************
Global define
***********************************************************************/
// smbus data
GLOBAL _SHORT2CHAR		tcom00;											// 0x00:ex_func
#define t_com00			tcom00.us
#define a_com00			tcom00.uc
//GLOBAL WORD				t_com08;										// 0x08:Temperature()
//GLOBAL WORD				t_com09;										// 0x09:Voltage()
//GLOBAL short			t_com0a;										// 0x0A:Current()
//GLOBAL WORD				t_com0d;										// 0x0D:RelativeStateOfCharge()
//GLOBAL WORD				t_com0fc;										// 0x0F:RemainingCapacity() mAh
//GLOBAL WORD				t_com10c;										// 0x10:FullChargeCapacity() mAh
GLOBAL WORD				t_com14;										// 0x14:ChargingCurrent() mA
GLOBAL WORD				t_com15;										// 0x15:ChargingVoltage() mV
GLOBAL _SHORT2CHAR		tcom16;											// 0x16:BatteryStatus
#define t_com16			tcom16.us
#define a_com16			tcom16.uc
GLOBAL	_SDWORD			t_com24;										// 0x24:ExtendedCurrent()
#define f_ov_alarm		DEF_BIT0(&a_com16[1])							// OVER VOLTAGE
#define f_over_tmp		DEF_BIT6(&a_com16[0])							// OVER_TEMP_ALARM
#define f_odc_alarm		DEF_BIT5(&a_com16[0])							// Over Discharge Current Alarm
#define f_occ_alarm		DEF_BIT4(&a_com16[0])							// Over Charge Current Alarm
#define f_short_alarm	DEF_BIT3(&a_com16[0])							// Short Current Alarm
#define f_dischg		DEF_BIT2(&a_com16[0])							// DISCHARGING
#define f_fullchg		DEF_BIT1(&a_com16[0])							// FULLY_CHARGED
#define f_fulldis		DEF_BIT0(&a_com16[0])							// FULLY_DISCHARGED
GLOBAL WORD				t_com25;										// 0x25:Internal temperature
GLOBAL WORD				t_com44;										// 0x44:2nd Thermistor()
GLOBAL WORD				tpacksts;										// 0x45:PackStatus
#define f_dfet			DEF_BIT0(&tpacksts)								// DFET	1=ON, 0=OFF
#define f_cfet			DEF_BIT1(&tpacksts)								// CFET	1=ON, 0=OFF
#define f_sys_in		DEF_BIT2(&tpacksts)								// BI	1=Batt-in, 0=Batt-out
#define f_ccp			DEF_BIT3(&tpacksts)								// Capacity correction point flag	1=detect, 0=not detect
GLOBAL _SHORT2CHAR		tcom46;											// 0x46:CellBalancingStatus
#define t_com46			tcom46.us
#define a_com46			tcom46.uc
GLOBAL WORD				t_com5a;										// 0x5a:Flash update mode
GLOBAL WORD				t_com5d;										// 0x5d:Software Reset()
GLOBAL WORD				t_com5e;										// 0x5e:Flash erase mode

GLOBAL _SHORT2CHAR		tad_curr;
GLOBAL _LONG2CHAR		cc_curr;										// result of current multiplication
#define lcurr_ad		cc_curr.ul


GLOBAL BYTE			amodeflg1;
#define f_over_chg	DEF_BIT0(&amodeflg1)								// OVER_CHARGED_ALARM

// system counter
GLOBAL BYTE				aoffs_cnt;										// OffStateCounter
GLOBAL BYTE				asleep_cnt1,asleep_cnt2;						// Sleep counter


GLOBAL WORD				tvin12v;										// vin12 voltage

//#ifdef	TCV_EN
GLOBAL WORD				ttcv;											// Total cell voltage
//#endif

GLOBAL BYTE 			afet;											// FET status
GLOBAL BYTE				afet_real;										// FET status register read
GLOBAL BYTE				aafe;											// FET setting
#define f_cfctl			DEF_BIT1(&aafe)									// C-FET
#define f_dfctl			DEF_BIT0(&aafe)									// D-FET


// AD value
GLOBAL WORD				ad_cell[10];									// cell
GLOBAL WORD				ad_div[10];										// Difference
GLOBAL WORD				ad_imp[10];										// Impedance measurement
GLOBAL DWORD			ad_therm;										// thermister
GLOBAL DWORD			ad_therm2;										// thermister2
GLOBAL WORD				tethad;											// simple thermistor AD value
GLOBAL WORD				tadvregpull;									// VREG pullup AD value (AN0)
GLOBAL WORD				tadvregpull2;									// VREG pullup AD value (AN1)
GLOBAL WORD				ad_pack;										// PACK voltage
GLOBAL WORD				ad_itemp;										// Internal temperature
#ifdef	TCV_EN
GLOBAL WORD				ad_tcv;											// Total Cell Voltage
#endif

//#ifdef	MCUBG_EN
GLOBAL WORD				ad_tmcubg;										// MCU BG Voltage
//#endif

//#ifdef	CREG2_EN
GLOBAL WORD				ad_tcreg2;										// CREG2 Voltage
//#endif


//function flags
//volatile GLOBAL char afunction_flag_datas;
//#define f_curr_int		DEF_BIT0(&afunction_flag_datas)

volatile GLOBAL BYTE f_curr_int;

GLOBAL BYTE				a_com52;
GLOBAL BYTE				asout1[3],asout2[3];

// Voltage measurement relation
GLOBAL WORD				tvolt[10];										// single cell Voltage
GLOBAL BYTE				av_tbl[10];
GLOBAL WORD				tminv;											// Minimum cell voltage
GLOBAL WORD				tmaxv;											// Maximum cell voltage
GLOBAL BYTE				amnidx;											// MinV index
// Measurement Result
GLOBAL unsigned short tvt_ad;											// thermistor AD value
GLOBAL unsigned short tadv;												// thermistor voltage
GLOBAL _SBYTE	adegree,adegree2;										// Temperature[Ž]

// Measurement data
//GLOBAL WORD				tabsc;										// Current absolute value
GLOBAL DWORD			labsc;											// Current absolute value

GLOBAL _SHORT2CHAR 		tmode;
#define amode	tmode.uc[0]												// Mode number

//GLOBAL long		lrc_w;													// Charging learning RC integrated value
GLOBAL long		relcap_c;                                               // charging relearn capacity

GLOBAL BYTE		asys_in;												// SYS-connect

GLOBAL 	BYTE  acb_w,acb_w1;												// Cell balance select flag

// Impedance measurement relation
GLOBAL	BYTE	f_fd_imp;												// Fully discharge for impedance flag
GLOBAL	BYTE	f_imp_calc;												// Battery Impedance calculation flag 
GLOBAL	WORD	tcv1;													// V1
GLOBAL	WORD	tcv2;													// V2
GLOBAL	DWORD	lc1;													// C1
GLOBAL	BYTE	acellnum;												// Cell number
GLOBAL	BYTE	acurr_cnt;												// Charging time counter
GLOBAL	BYTE	acoff_cnt;												// CFET off timer

// BatteryUsageCondition
GLOBAL BYTE	ausage_cnt;													// 1sec timer for BatteryUsageCondition
GLOBAL WORD	tttlchg_w;													// Total Charged capacity working data
GLOBAL WORD	toldcap;													// Capacity to compare
GLOBAL BYTE	attlstr_w;													// Total Storage time
GLOBAL BYTE	astrv_w;													// Storage time of V >= CV/cell - Storage delta V current work
GLOBAL BYTE	astrvt_w;													// Storage time of T >= Storage temp current work
GLOBAL BYTE	astrt_w;													// Storage time of V >= CV/cell - Storage delta V & T >= Storage temp current work

typedef union {
	WORD	lsum[2];													// Checksum
} _CHECKSUM;
GLOBAL _CHECKSUM	ssum;
#define lsum_main1		ssum.lsum[0]									// FlashROM 1(FW) checksum
#define lsum_main2		ssum.lsum[1]									// FlashROM 2(Fixed data) checksum

typedef struct
{
	WORD		df_t_com08;												// 0x08:Temperature()
	WORD		df_t_com09;												// 0x09:Voltage()
	short		df_t_com0a;												// 0x0A:Current()
	WORD		df_t_com0d;												// 0x0D:RelativeStateOfCharge()
	WORD		df_t_com0fc;											// 0x0F:RemainingCapacity() mAh
	WORD		df_t_com10c;											// 0x10:FullChargeCapacity()
	long		df_lrc_w;												//      RC correction capacity
	WORD		df_t_com47;												// 0x47:Battery Impedance
	WORD		df_t_com48;												// 0x48:BatteryUsageCondition:: Total Charged Capacity
	WORD		df_t_com49;												// 0x49:BatteryUsageCondition:: Total Storage time
	WORD		df_t_com4a;												// 0x4A:BatteryUsageCondition:: Storage time at high voltage
	WORD		df_t_com4b;												// 0x4B:BatteryUsageCondition:: Storage time at high temperature
	WORD		df_t_com4c;												// 0x4C:BatteryUsageCondition:: Storage time at high voltage & high temp
	
}_DFDAT;

#define DFSIZE	sizeof(_DFDAT)											// DataFlash size

typedef union
{
	_DFDAT	sdfdat;														// Flexible data
	BYTE	uc[DFSIZE];													// Byte alignment
}_DF;

GLOBAL _DF	sdf;
#define adfdat			sdf.uc

#define	t_com08			sdf.sdfdat.df_t_com08
#define t_com09			sdf.sdfdat.df_t_com09
#define t_com0a			sdf.sdfdat.df_t_com0a
#define t_com0d			sdf.sdfdat.df_t_com0d
#define t_com0fc		sdf.sdfdat.df_t_com0fc
#define t_com10c		sdf.sdfdat.df_t_com10c
#define lrc_w			sdf.sdfdat.df_lrc_w
#define t_com47			sdf.sdfdat.df_t_com47

#define t_com48			sdf.sdfdat.df_t_com48
#define t_com49			sdf.sdfdat.df_t_com49
#define t_com4a			sdf.sdfdat.df_t_com4a
#define t_com4b			sdf.sdfdat.df_t_com4b
#define t_com4c			sdf.sdfdat.df_t_com4c


#undef	GLOBAL

#endif
