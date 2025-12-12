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
* System Name	: RAJ240090/100 sample program
* File Name		: smbus_ex.c
* Contents		: SMBus extra functions
* Device		: RAJ240090/100
* Compiler		: CC-RL (V.4.01)
* Note			: 
*""FILE COMMENT END""**********************************************************/
#define _SMBUS_EX


/***********************************************************************
** Include files
***********************************************************************/
#include "define.h"													// union/define definition
#include "dataflash.h"												// DataFlash data definition
#include "kousei.h"													// Initial calibration
#include "ram.h"													// ram.c
#include "smbus.h"													// smbus.c
#include "smbus_ex.h"												// smbus_ex.c
#include "afe.h"
#include "mcu.h"
#include "cell.h"


#include <string.h>


/***********************************************************************
** Internal function prototype declaration
***********************************************************************/
static void Ext_Func(void);
static void Write_CalRef(void);
static void Read_CalRef(void);

#pragma	inline_asm	SW_RESET
void SW_RESET(void)
{
	.DB2 0x0FFFF;
}

static _SHORT2CHAR				tcom57;								// calibration reference value interface
#define t_com57 tcom57.us
#define a_com57 tcom57.uc



// Firmware version
const __near WORD		Version = 0x0620;

// - SMBus command table -
const _ST_SMB scom_no_tbl[] =
{
	{ WORD_R_W		, 1,	(BYTE*)&t_com00 },						// 00 FUNC : ExtraFunction()
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 01 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 02 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 03 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 04 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 05 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 06 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 07 reserved
	{ RW_SADCHK		, 1,	(BYTE*)&t_com08 },						// 08 Temperature()
	{ RW_SADCHK		, 1,	(BYTE*)&t_com09 },						// 09 Voltage()
	{ RW_SADCHK		, 1,	(BYTE*)&t_com0a },						// 0A Current()
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 0B reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 0C reserved
	{ RW_SADCHK	, 1,		(BYTE*)&t_com0d },						// 0D RelativeStateOfCharge()
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 0E reserved
	{ RW_SADCHK	, 1,		(BYTE*)&t_com0fc },						// 0F RemainingCapacity()
	{ RW_SADCHK	, 1,		(BYTE*)&t_com10c },						// 10 FullChargeCapacity()
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 11 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 12 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 13 reserved
	{ RW_SADCHK	, 1,		(BYTE*)&t_com14 },						// 14 ChargingCurrent()
	{ RW_SADCHK	, 1,		(BYTE*)&t_com15 },						// 15 ChargingVoltage()
	{ RW_SADCHK	, 1,		(BYTE*)&t_com16 },						// 16 BatteryStatus
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 17 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 18 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 19 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 1A reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 1B reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 1C reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 1D reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 1E reserved
	{ RW_SADCHK		, 1,	(BYTE __far*)&CONFLG },					// 1F Control Flag Status
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 20 reserved
	{ RB_SADCHK	, 32,		(BYTE __far*)&Dev_NAME },				// 21 DeviceName()
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 22 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 23 reserved
	{ RB_SADCHK	, 4	,		(BYTE*)&t_com24 },						// 24 ExtendedCurrent()
	{ RW_SADCHK		, 1,	(BYTE*)&t_com25 },						// 25 InternalTemperature()
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 26 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 27 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 28 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 29 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 2A reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 2B reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 2C reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 2D reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 2E reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 2F reserved
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[0]) },					// 30 cell1 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[1]) },					// 31 cell2 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[2]) },					// 32 cell3 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[3]) },					// 33 cell4 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[4]) },					// 34 cell5 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[5]) },					// 35 cell6 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[6]) },					// 36 cell7 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[7]) },					// 37 cell8 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[8]) },					// 38 cell9 voltage
	{ RW_SADCHK		, 1,	(BYTE*)&(tvolt[9]) },					// 39 cell10 voltage
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 3A reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 3B reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 3C reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 3D reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 3E reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 3F reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 40 reserved
	{ RW_SADCHK	, 1,		(BYTE*)&amode },						// 41 mode
	{ RW_SADCHK		, 1,	(BYTE*)&ttcv },							// 42 Total Cell Voltage
	{ RW_SADCHK		, 1,	(BYTE*)&tvin12v },						// 43 VIN12Voltage
	{ RW_SADCHK		, 1,	(BYTE*)&t_com44 },						// 44 2nd Thermistor
	{ RW_SADCHK	, 1,	(BYTE*)&tpacksts },							// 45 PackStatus
	{ RW_SADCHK	, 1,	(BYTE*)&t_com46 },							// 46 BatteryStatus
	{ RW_SADCHK	, 1,	(BYTE*)&t_com47 },							// 47 Battery Impedance()
	{ RW_SADCHK	, 1,	(BYTE*)&t_com48 },							// 48 BatteryUsageCondition:: Total Storage time
	{ RW_SADCHK	, 1,	(BYTE*)&t_com49 },							// 49 BatteryUsageCondition:: Total Charged Capacity
	{ RW_SADCHK	, 1,	(BYTE*)&t_com4a },							// 4A BatteryUsageCondition:: Storage time at high voltage
	{ RW_SADCHK	, 1,	(BYTE*)&t_com4b },							// 4B BatteryUsageCondition:: Storage time at high temperature
	{ RW_SADCHK	, 1,	(BYTE*)&t_com4c },							// 4C BatteryUsageCondition:: Storage time at high voltage & high temp
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 4D reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 4E reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 4F reserved
	{ WORD_R_W	, 1,		(BYTE*)&asout1[1] },					// 50 AFE Serial write
	{ WORD_R_W	, 1,		(BYTE*)&asout2[1] },					// 51 AFE Serial read(address set)
	{ RW_SADCHK	, 1,		(BYTE*)&a_com52},						// 52 AFE Serial read
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 53 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 54 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 55 reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 56 reserved
	{ WORD_R_W, 1,	(BYTE*)&t_com57 },								// 57 InitCalib reference
	{ WORD_R_W, 1,	(BYTE*)&t_com58 },								// 58 Initial Calibration
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 59 reserved
	{ WORD_R_W	, 1,		(BYTE*)&t_com5a },						// 5A Flash update 
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 5B reserved 
	{ RW_SADCHK		, 1,	(BYTE __far*)&D_SERIES },				// 5C Number of cell
	{ WORD_R_W	, 1,		(BYTE*)&t_com5d },						// 5D Software Reset
	{ WORD_R_W	, 1,		(BYTE*)&t_com5e },						// 5E Flash erase
	{ RW_SADCHK	, 1,		(BYTE*)&Version },						// 5F Firmware Version
	
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[0]) },					// 60 AD value of cell 1
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[1]) },					// 61 AD value of cell 2
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[2]) },					// 62 AD value of cell 3
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[3]) },					// 63 AD value of cell 4
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[4]) },					// 64 AD value of cell 5
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[5]) },					// 65 AD value of cell 6
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[6]) },					// 66 AD value of cell 7
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[7]) },					// 67 AD value of cell 8
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[8]) },					// 68 AD value of cell 9
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_cell[9]) },					// 69 AD value of cell 10
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 6A reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 6B reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 6C reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 6D reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 6E reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 6F reserved
	
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 70 reserved
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_therm) },					// 71 AD value of AN0
	{ RW_SADCHK		, 1,	(BYTE*)&(ad_therm2) },					// 72 AD value of AN1
	{ RW_SADCHK		, 1,	(BYTE*)&ad_pack },						// 73 AD value of PACK voltage
	{ RW_SADCHK		, 1,	(BYTE*)&ad_tmcubg },					// 74 MCU BG
	{ RW_SADCHK		, 1,	(BYTE*)&ad_tcreg2},						// 75 CREG2
	{ RB_SADCHK		, 4,	(BYTE*)&lcurr_ad },						// 76 Current CC measurement
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 77 reserved
	{ RW_SADCHK		, 1,	(BYTE*)&(lsum_main1) },					// 78 Checksum(main)
	{ RW_SADCHK		, 1,	(BYTE*)&(lsum_main2) },					// 79 Checksum(fixed data)
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 7A reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 7B reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 7C reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 7D reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 7E reserved
	{ COMDAT_ERR, 0xFF,		(BYTE*)NULL },							// 7F reserved
};


/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: SMBus received data storage processing
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void StoreRcvData(void)
 *--------------------------------------------------------------------------
 * Function			: Store received data for SMBus Write command to each command
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *-------------------------------------------------------------------------- 
 *""FUNC COMMENT END""*****************************************************/
void StoreRcvData(void)
{
	BYTE	*apwork;												// Work pointer
	_SBYTE	al1;													// Loop counter
	_UDWORD AFE_ADDR = 0x000F0500;
	_UDWORD tmp;
	
	switch( arcv_cmd )												// What's Received command ?
	{
		
		// Extension command to append here
		case 0x00:													// ExtraFunction()
			Ext_Func();
			break;

		case 0x50:
			asout1[0] = asmbuf[2]; // dummy
			asout1[1] = asmbuf[1]; // address
			asout1[2] = asmbuf[0]; // data
			tmp = AFE_ADDR+asmbuf[1];
			AFE_WR(*(__far BYTE*)tmp,asout1[2]);
			break;
			
		case 0x51:
			asout2[0] = asmbuf[2]; // dummy
			asout2[1] = asmbuf[1]; // address
			asout2[2] = asmbuf[0]; // dummy
			tmp = AFE_ADDR+asmbuf[1];
			AFE_RD(*(__far BYTE*)tmp,a_com52);
			break;
			
		case 0x58:													// Initial calibration
			if( f_calibmode == ON )									// Now initial calibration mode ?
			{
				acalib_id = asmbuf[1];								// Store received data
				acalib_sts = asmbuf[0];
				if( acalib_sts == 0x01 )							// Make initial calibration ?
				{
					f_calib = ON;									// Set InitCalib req. flag
				}
			}
			break;

		case 0x57:													// Write InitCalib ref. value
			if( f_calibmode == ON )									// Now InitCalib mode ?
			{
				Write_CalRef();										// InitCalib ref. writing
			}
			break;

		case 0x5a:
			if( asmbuf[0] == 0x23 && asmbuf[1] == 0x45 )
			{
				f_flashup = ON;										// Set Flash update mode req.
			}
			break;
			
		case 0x5d:													// Software Reset
			if( asmbuf[0] == 0x56 && asmbuf[1] == 0x78 )
			{
				SW_RESET();
			}
			
		case 0x5e:													// Erase DataFlash
			if( asmbuf[0] == 0x12 && asmbuf[1] == 0x34 )
			{
				FlashErase_Own();									// Erase Own data (DataFlash).
			}
			else if( asmbuf[0] == 0xAB && asmbuf[1] == 0xCD )
			{
				FlashErase_Log();									// Erase Log data (DataFlash).
			}
			break;
		

		default:													// Other
			apwork = (BYTE *)ssmbdata.aadr;							// Set data address to pointer
			for( al1=arem_cc; al1!=(_SBYTE)0xFF; al1-- )
			{
				*apwork = asmbuf[al1];								// Store received data
				apwork++;											// To next pointer
			}
			break;
	}
}


/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: SMBus command exist check
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: BYTE ComExist_Chk(void)
 *--------------------------------------------------------------------------
 * Function			: Check whether command exists when receiveing
 *					:  the command, and set "ssmbdata".
 *					: And execute command own function if there is.
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: 0=Without command, 1=with command
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
BYTE ComExist_Chk(void)
{
	if( arcv_cmd < 0x80 )											// Command is 0x00`0x7F ?
	{
		ssmbdata = scom_no_tbl[arcv_cmd];							// Set command information

		//You need to add function here if there is command that needs flexible
		//	  length data.

	} else {
		ssmbdata.arcv_mod = COMDAT_ERR;								// Error
	}

	if( ssmbdata.arcv_mod != COMDAT_ERR )							// Command is correct ?
	{
		arem_cc = ssmbdata.acrem;									// Set communication data length
		return 1;
	} else {
		return 0;
	}
}



/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: SMBus Read data setting
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void SetSMBusRead(void)
 *--------------------------------------------------------------------------
 * Function			: Set Read data to SMBus send buffer
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
void SetSMBusRead(void)
{
	BYTE	aspfunc_mode=0;											// You need to set aspfunc_mode to Nonzero if there is special operation in buffer management 
																	
	BYTE __far	*apwork;												// work pointer
	_SBYTE	al1;													// loop counter

//	apwork = (BYTE *)ssmbdata.aadr;									// Set data address to pointer
	apwork = (BYTE __far*)ssmbdata.aadr;									// Set data address to pointer

	switch( arcv_cmd )														
																	// Check command needs calc.
	{
		case 0x57:													// InitCalib ref. value
			Read_CalRef();
			break;	
	
		default:													// If you would like to add function you can describe code
		break;
	}

		//	 You need to add function here if there is command that needs special
		//	  setting.

	switch(aspfunc_mode)
	{
	case 0:
																	// When you don't need the special setting.
		if( ssmbdata.arcv_mod == RB_SADCHK)							// BlockRead ?
																	//
		{
			// Set commnication data length
			asmbuf[ssmbdata.acrem] = ssmbdata.acrem;
			for( al1=ssmbdata.acrem-1; al1>=0; al1--)
			{
				asmbuf[al1] = *apwork;								// set data to send buffer
				apwork++;
			}
		} else {													// ReadWord
			for( al1=ssmbdata.acrem; al1>=0; al1--)
			{
				asmbuf[al1] = *apwork;								// Set data to send buffer
				apwork++;
			}
		}
		break;

	}
}




/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: ExtraFunction processing
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void Ext_Func(void)
 *--------------------------------------------------------------------------
 * Function			: Exectute this function when received command is 0x40.
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *-------------------------------------------------------------------------- 
 *""FUNC COMMENT END""*****************************************************/
void Ext_Func(void)
{
	
	a_com00[0] = asmbuf[1];											// Store received data
	a_com00[1] = asmbuf[0];

	
		// Force PowerDown
		if( f_comjib == ON )										// Force PowerDown flag = ON ?
		{
			if( t_com00 == 0x6789 )									// Data is correct ?
			{
				PowerDown();										// PowerDown function
			} else {												// Data is wrong
				f_comjib = OFF;										// Clear the flag
			}
		} else {													// Force PowerDown flag = OFF
			if( t_com00 == 0x2345 )									// PowerDown req. command ?
			{
				f_comjib = ON;										// Set force PowerDown flag
			}
		}


		// - FET test function -
		if(f_fettst == ON && a_com00[1] == 0xFF )					// & high byte is 0xFF ?
			{
				afet = a_com00[0] & 0x03;							// Mask unnessary Bit
				
				AFE_WR(AFE_FCON,afet);
			}
		

		if( a_com00[1] == 0x12 )									// 0x12** command ?
		{
			switch( a_com00[0] )									// ** is ...
			{
			case 0x34:												// Force Sleep
				f_fcslp = ON;										// Set force sleep flag
				break;
			
			// - FET test function -
			case 0x35:												// FET control
				
				f_fettst = ON;										// FET test mode ON
				afet = FET_OFF;
				AFE_WR(AFE_FCON,afet);
				break;
				
			case 0x36:
			
				f_fettst = OFF;										// FET test mode OFF
				break;
				
			case 0x37:
					
				if( f_calibmode == ON )									// Now InitCalib mode ?
				{
					f_adccalib = ON;									// Set AD conversion flag in calibration
				}
				break;
				
			case 0x38:
				if( f_calibmode == ON)									// Now InitCalib mode ?
				{
					f_skipcalib = ON;									// Set Calibraion skip flag in calibration
				}
				break;
			
			case 0x39:
				f_comslp1 = ON;										// Set sleep mode current 1 flag
				break;
				
			case 0x3A:
				f_comslp2 = ON;										// Set sleep mode current 2 flag
				break;
				
			case 0x3B:
				f_dfreq = ON;										// DF update
				break;
				
			}
		}
	
}



/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: Calibration referenece value read processing
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void Read_CalRef(void)
 *--------------------------------------------------------------------------
 * Function			: 
*					: Set InitCalib reference value of command specified
*					:  by "acalib_id"(Received by 0x58 command) to "t_com57"
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
void Read_CalRef(void)
{
	if( acalib_id < 0x0e )											// Voltage-related ?
	{
		if( acalib_id == 0x0c )										// LVall ?
		{
			t_com57 = D_LVREF[1];									// Set LV2
		} else {
			if( acalib_id == 0x0d )									// HVall ?
			{
				t_com57 = D_HVREF[1];								// Set HV2
			} else {
				if( acalib_id == 0x0a )								// LVIN12 ?
				{
					t_com57 = D_V12LVREF;							// Set LVIN12
				} else {
					if( acalib_id == 0x0b )							// HVIN12 ?
					{
						t_com57 = D_V12HVREF;						// Set HVIN12
					} else {
																	// Specified individual
						t_com57 = D_LVREF[acalib_id];
					}
				}
			}
		}
	} else {
		if( acalib_id == 0x0f )										// Current ?
		{
			t_com57 = D_CURRREF;
		} else {
			if( acalib_id == 0x10 )									// Temperature ?
			{
				t_com57 = D_CALTHREF;
			} else {												// Other(undefined)
				if( acalib_id < 0x2a)
				t_com57 = D_HVREF[acalib_id -0x20];					// HV 
				else{
					if(acalib_id == 0x2c)
					{
						t_com57 = D_TCLVREF;
					}else if(acalib_id == 0x2d)
					{
						t_com57 = D_TCHVREF;
					}else{
						t_com57 = 0xFFFF;
					}
				}
			}
		}
	}
}



/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: InitCalib reference value write function
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void WriteFlash_Calref(BYTE *apadr)
 *--------------------------------------------------------------------------
 * Function			: Write InitCalib reference value.
 *					: This function is called from Write_CalRef().
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: WORD *tpadr : Pointer to write address
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *-------------------------------------------------------------------------- 
 *""FUNC COMMENT END""*****************************************************/
void WriteFlash_CalRef(BYTE *apadr)
{
	FlashWrite( apadr, &a_com57[0], 2 );							// Write data of 2bytes at DataFlash area
	DFLEN = 1;														// Data flash access enable
	Waittimer_us(10);												// wait 10us
	memcpy( &u_fo_ram, &u_fo_rom, sizeof(u_fo_rom) );				// DataFlash own data -> RAM copy
	DFLEN = 0;														// Data flash access disable
}


/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: InitCalib reference value write function
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void Write_Calref(void)
 *--------------------------------------------------------------------------
 * Function			: Function when 0x58 command is received.
 *					: Write received data to InitCalib reference value
 *					:  of command specified by "acalib_id"(Received by
 *					:  0x57 command).
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: None
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: WriteFlash_Calref
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
void Write_CalRef(void)
{
	BYTE	al1;

	a_com57[0] = asmbuf[1];											// Store received data
	a_com57[1] = asmbuf[0];

	if( acalib_id < 0x0c )											// LVx / TotalLV / HV ?
	{
		if( acalib_id == 0x0a )										// LVIN12 ?
		{
			WriteFlash_CalRef((BYTE*)&D_R_V12LVREF);
		} else {
			if( acalib_id == 0x0b )									// HVIN12 ?
			{
				WriteFlash_CalRef((BYTE*)&D_R_V12HVREF);
			} else {
				WriteFlash_CalRef((BYTE*)&D_R_LVREF[acalib_id]);
			}
		}
	} else {
		if( acalib_id == 0x0c )										// LV all ?
		{
			for( al1=0; al1<D_SERIES; al1++ )		
																	// Write it continues number of cell
			{
				WriteFlash_CalRef((BYTE*)&D_R_LVREF[al1]);
			}
		} else {
			if( acalib_id == 0x0d )									// HV all ?
			{
				// Write it continues number of cell
				for( al1=0; al1<D_SERIES; al1++ )
				{
					WriteFlash_CalRef((BYTE*)&D_R_HVREF[al1]);
				}
			} else {
				if( acalib_id == 0x0f )								// Current ?
				{
					WriteFlash_CalRef((BYTE*)&D_R_CURRREF);
				} else {
					if( acalib_id == 0x10 )							// Temperature ?
					{
						WriteFlash_CalRef((BYTE*)&D_R_CALTHREF);
					}else if(acalib_id < 0x2a){
						WriteFlash_CalRef((BYTE*)&D_R_HVREF[acalib_id - 0x20]);		//HVx
					}else{											// acalib_id >= 2a
						
						if( acalib_id == 0x2c)
						{
							WriteFlash_CalRef((BYTE*)&D_R_TCLVREF);
						}
						
						if( acalib_id == 0x2d)
						{
							WriteFlash_CalRef((BYTE*)&D_R_TCHVREF);
						}
					}
				}
			}
		}
	}
}