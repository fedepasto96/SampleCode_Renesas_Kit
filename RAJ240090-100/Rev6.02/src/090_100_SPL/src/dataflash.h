/******************************************************************************
* DISCLAIMER                                                                    *
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
* File Name		: Dataflash.h
* Version		: 1.00
* Contents		: Flash memory control functions header file
* Programmer		: Yasuo Usuda
* Note			: 
************************************************************************
* Copyright(C) 2016, 2019 RENESAS ELECTRONICS CORPORATION
************************************************************************
 * History			: 2016.02.15 Ver 1.00
 *					:  New Create
 *					: 
*""FILE COMMENT END""**************************************************/
#ifndef _DATAFLASH_H
#define _DATAFLASH_H


#ifdef	_DATAFLASH
#define		GLOBAL
#else
#define		GLOBAL	extern
#endif	/* _DATAFLASH */



// - DataFlash data definition -
typedef struct
{
	//  ===== Initial Calibration Data =====
	WORD	d_LV[10];							// [20byte] AD converted value for calibration voltage LV
	WORD	Reserved1[6];						// [12byte] reserved
	WORD	d_HV[10];							// [20byte] AD converted value for calibration voltage HV
	WORD	Reserved2[6];						// [12byte] reserved
	WORD	d_LVREF[10];						// [20byte] Calibration voltage LV [1mV]
	WORD	Reserved3[6];						// [12byte] reserved
	WORD	d_HVREF[10];						// [20byte] Calibration voltage value HV [1mV]
	WORD	Reserved4[6];						// [12byte] reserved
	WORD	d_V12LV;							// [2byte] AD converted value for VIN12 calibration voltage LV
	WORD	d_V12HV;							// [2byte] AD converted value for VIN12 calibration voltage HV
	WORD	d_V12LVREF;							// [2byte] VIN12 calibration voltage value LV [1mV]
	WORD	d_V12HVREF;							// [2byte] VIN12 calibration voltage value HV [1mV]

	DWORD	d_0A;								// [4byte] Current counter value for initial calibration 0A
	DWORD	d_CURR;								// [4byte] Discharge current counter value for initial calibration
	WORD	d_CURRREF;							// [2byte] Reference current value for initial calibration
	WORD	d_CALTH;							// [2byte] Initial calibration value for temperature
	WORD	d_CALTHREF;							// [2byte] Initial calibration reference value for temperature
	WORD	d_TCLV;								// [2byte] AD converted value for Total cell voltage calibration voltage LV
	WORD	d_TCHV;								// [2byte] AD converted value for Total cell voltage calibration voltage HV
	WORD	d_TCLVREF;							// [2byte] Total cell voltage calibration voltage value LV [1mV]
	WORD	d_TCHVREF;							// [2byte] Total cell voltage calibration voltage value HV [1mV]
	WORD	d_MCUBG;							// [2byte] Initial calibration value for MCU BG
	WORD	d_CREG2;							// [2byte] Initial calibration value for CREG2

} _ST_FLASH_OWN;
//__directmap _ST_FLASH_OWN u_fo_rom = { 0x0F1800 };		// FlashROM own data the top of the area:DataFlashMemory Block2
#pragma address u_fo_rom = 0xF1800
GLOBAL  _ST_FLASH_OWN u_fo_rom;				// FlashROM own data the top of the area

GLOBAL _ST_FLASH_OWN u_fo_ram;					// FlashROM own data the top of the area:RAM for DataFlashMemory Block2

// ROM area
#define D_R_LV			u_fo_rom.d_LV			// [20byte] AD converted value for calibration voltage LV
#define D_R_HV			u_fo_rom.d_HV			// [20byte] AD converted value for calibration voltage HV
#define D_R_LVREF		u_fo_rom.d_LVREF		// [20byte] Calibration voltage LV [1mV]
#define D_R_HVREF		u_fo_rom.d_HVREF		// [20byte] Calibration voltage HV [1mV]
#define D_R_V12LV		u_fo_rom.d_V12LV		// [2byte] AD converted value for VIN12 calibration voltage LV
#define D_R_V12HV		u_fo_rom.d_V12HV		// [2byte] AD converted value for VIN12 calibration voltage HV
#define D_R_V12LVREF	u_fo_rom.d_V12LVREF		// [2byte] Pack voltage calibration voltage value LV [1mV]
#define D_R_V12HVREF	u_fo_rom.d_V12HVREF		// [2byte] Pack voltage calibration voltage value HV [1mV]

#define D_R_0A			u_fo_rom.d_0A			// [4byte] Current counter value for initial calibration 0A
#define D_R_CURR		u_fo_rom.d_CURR			// [4byte] Discharge current counter value for initial calibration
#define D_R_CURRREF		u_fo_rom.d_CURRREF		// [2byte] Reference current value for initial calibration
#define D_R_CALTH		u_fo_rom.d_CALTH		// [2byte] Initial calibration value for temperature
#define D_R_CALTHREF	u_fo_rom.d_CALTHREF		// [2byte] Initial calibration reference value for temperature

#define D_R_TCLV		u_fo_rom.d_TCLV			// [2byte] AD converted value for Total cell voltage calibration voltage LV
#define D_R_TCHV		u_fo_rom.d_TCHV			// [2byte] AD converted value for Total cell voltage calibration voltage HV
#define D_R_TCLVREF		u_fo_rom.d_TCLVREF		// [2byte] Total cell voltage calibration voltage value LV [1mV]
#define D_R_TCHVREF		u_fo_rom.d_TCHVREF		// [2byte] Total cell voltage calibration voltage value HV [1mV]

#define D_R_MCUBG		u_fo_rom.d_MCUBG		// [2byte] Initial calibration value for MCU BG
#define D_R_CREG2		u_fo_rom.d_CREG2		// [2byte] Initial calibration value for CREG2


// RAM area
#define D_LV			u_fo_ram.d_LV			// [20byte] AD converted value for calibration voltage LV
#define D_HV			u_fo_ram.d_HV			// [20byte] AD converted value for calibration voltage HV
#define D_LVREF			u_fo_ram.d_LVREF		// [20byte] Calibration voltage LV [1mV]
#define D_HVREF			u_fo_ram.d_HVREF		// [20byte] Calibration voltage HV [1mV]
#define D_V12LV			u_fo_ram.d_V12LV		// [2byte] AD converted value for VIN12 calibration voltage LV
#define D_V12HV			u_fo_ram.d_V12HV		// [2byte] AD converted value for VIN12 calibration voltage HV
#define D_V12LVREF		u_fo_ram.d_V12LVREF		// [2byte] VVIN12 calibration voltage value LV [1mV]
#define D_V12HVREF		u_fo_ram.d_V12HVREF		// [2byte] VIN12 calibration voltage value HV [1mV]

#define D_0A			u_fo_ram.d_0A			// [4byte] Current counter value for initial calibration 0A
#define D_CURR			u_fo_ram.d_CURR			// [4byte] Discharge current counter value for initial calibration
#define D_CURRREF		u_fo_ram.d_CURRREF		// [2byte] Reference current value for initial calibration
#define D_CALTH			u_fo_ram.d_CALTH		// [2byte] Initial calibration value for temperature
#define D_CALTHREF		u_fo_ram.d_CALTHREF		// [2byte] Initial calibration reference value for temperature

#define D_TCLV		u_fo_ram.d_TCLV				// [2byte] AD converted value for Total cell voltage calibration voltage LV
#define D_TCHV		u_fo_ram.d_TCHV				// [2byte] AD converted value for Total cell voltage calibration voltage HV
#define D_TCLVREF		u_fo_ram.d_TCLVREF		// [2byte] Total cell voltage calibration voltage value LV [1mV]
#define D_TCHVREF		u_fo_ram.d_TCHVREF		// [2byte] Total cell voltage calibration voltage value HV [1mV]

#define D_MCUBG		u_fo_ram.d_MCUBG			// [2byte] Initial calibration value for MCU BG
#define D_CREG2		u_fo_ram.d_CREG2			// [2byte] Initial calibration value for CREG2


GLOBAL BYTE DF_Write(void);						// Write DataFlash
void DF_Read(void);								// Read DataFlash
GLOBAL void DF_Erase_Confirm(void);				// Confirm erase DataFlash
void DFW_Index(void);
BYTE FlashErase_Chk(void);
void FlashErase_blk(BYTE aerase_no);


GLOBAL BYTE adfflg;								// Flags for DataFlash
GLOBAL __far BYTE	*apdfadr;					// DataFlash address pointer
GLOBAL BYTE	adfidx;								// DataFlash index


// - bit / 共用体変数定義 -
// - bit / union variable definition -
												// Flags for DataFlash
#define f_dfreq		DEF_BIT0(&adfflg)			// DataFlash書換要求フラグ
												// DataFlash update request
#define f_dfe		DEF_BIT1(&adfflg)			// DataFlash消去中フラグ
												// DataFlash erasing flag
#define f_dffail	DEF_BIT2(&adfflg)			// DataFlash故障フラグ
												// DataFlash failure flag
#define f_dfe_areq	DEF_BIT3(&adfflg)			// BlockA消去要求フラグ
												// BlockA erase request flag
#define f_dfe_breq	DEF_BIT4(&adfflg)			// BlockB消去要求フラグ
												// BlockB erase request flag
// - Define定義 -
// - Define definition -
#define	BLOCK_A		0xF1000						// Block A Erase address
#define BLOCK_B		0xF1400						// Block B Erase address
#define BLOCK_A_ST	0xF1040						// Block A Data start address
#define BLOCK_B_ST	0xF1440						// Block B Data start address
#define DF_ST_OFF	0x0040						// DataFlash data start offset

#define DFBLOCK		10							// DataFlash使用エリア数
												// Number of area of DataFlash
#define DF_LEN		96							// DataFlashエリア単位サイズ
												// Unit of DataFlash area

#define W_OK		0xA0						// Write OK
#define W_NG		0x07						// Write NG
#define AREA_NG		0x08						// 書込前にデータあり
												// Data exist before write
												
/***********************************************************************
Global functions
***********************************************************************/
GLOBAL BYTE FlashWrite(__far BYTE *apadr, BYTE *apdata, BYTE abytecnt);
GLOBAL void FlashErase_Own(void);
GLOBAL void FlashErase_Log(void);
void Waittimer_us(BYTE ainval);
void Calc_Checksum(void);

#undef		GLOBAL

#endif

