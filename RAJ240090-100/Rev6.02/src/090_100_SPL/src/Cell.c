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
* File Name		: cell.c
* Contents		: cell function source file
* Device		: RAJ240090
* Compiler		: CC-RL (V.4.01)
* Note			: 
*""FILE COMMENT END""**********************************************************/

#define _CELL

/***********************************************************************
** Include files
***********************************************************************/
#include "define.h"								// union/define definition
#include "cell.h"								// cell.c

#include <string.h>


/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: Fixed Data Check Process
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		:  BYTE InitFixed_Chk(void)
 *--------------------------------------------------------------------------
 * Function			: Check whether there are some fixed data or not
 *					: Even if there is just one vacant data, FALSE is returned.
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: TRUE=There are all necessary data.
 *					: FALSE=There are some vacant data.
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
 * History			: 2016.02.15 Ver 1.00
 *					:  New Create
 *					: 
 *""FUNC COMMENT END""*****************************************************/
BYTE InitFixed_Chk(void)
{
	BYTE	al1;
//	_ST_CTLFLG1 tmp = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	
	// Voltage,Current,Temperature
	if( NORMAL_CV == 0xFFFF )								// NORMAL_CV is vacant ?
	{
		return FALSE;
	}
	
	if( NORMAL_CC == 0xFFFF )								// NORMAL_CC is vacant ?
	{
		return FALSE;
	}
	
	if( CHGWAIT_CC == 0xFFFF )								// CHGWAIT_CC is vacant ?
	{
		return FALSE;
	}
	
	if( FULLCHGHV == 0xFFFF )								// FULLCHGHV is vacant ?
	{
		return FALSE;
	}
	
	if( FULLCHG_TV == 0xFFFF )								// FULLCHG_TV is vacant ?
	{
		return FALSE;
	}
	
	if( FULLCHG_CURR == 0xFFFF )							// FULLCHG_CURR is vacant ?
	{
		return FALSE;
	}
	
	if( FULLCHG_T == 0xFFFF )								// FULLCHG_T is vacant ?
	{
		return FALSE;
	}
	
	if( DISSTOPV == 0xFFFF )								// DISSTOPV is vacant ?
	{
		return FALSE;
	}
	
	if( D_PDVOLT == 0xFFFF )								// D_PDVOLT is vacant ?
	{
		return FALSE;
	}
	
	if( D_0PVOLT == 0xFFFF )								// D_0PVOLT is vacant ?
	{
		return FALSE;
	}
	
	if( D_DCDET == 0xFFFF )									// D_DCDET is vacant ?
	{
		return FALSE;
	}
	
	if( D_CCDET == 0xFFFF )									// D_CCDET is vacant ?
	{
		return FALSE;
	}
	
	if( D_SLPCURR == 0xFFFF )								// D_SLPCURR is vacant ?
	{
		return FALSE;
	}
	
	if( D_MSKCURR == 0xFFFF )								// D_MSKCURR is vacant ?
	{
		return FALSE;
	}
	
	if( DOTH == 0xFF )										// DOTH is vacant ?
	{
		return FALSE;
	}
	
	if( DOTL == 0xFF )										// DOTH is vacant ?
	{
		return FALSE;
	}
	
	if( DTH_hys == 0xFF )									// DTH_hys is vacant ?
	{
		return FALSE;
	}
	
	if( COTH == 0xFF )										// COTH is vacant ?
	{
		return FALSE;
	}
	
	if( COTL == 0xFF )										// COTH is vacant ?
	{
		return FALSE;
	}
	
	if( CTH_hys == 0xFF )									// CTH_hys is vacant ?
	{
		return FALSE;
	}
	
	if( D_2NDTHM == 0xFF )									// D_2NDTHM is vacant ?
	{
		return FALSE;
	}
	
	if( D_2NDTHM_hys == 0xFF )								// D_2NDTHM_hys is vacant ?
	{
		return FALSE;
	}
															// THERM_TBL are vacant ?
	for(al1 = 0; al1 < (sizeof(THERM_TBL)/sizeof(WORD)); al1++)			
	{
		if(THERM_TBL[al1] == 0xFFFF)
		{
			return FALSE;
		}
	}
															// ttempidx are vacant ?
	for(al1 = 0; al1 < (sizeof(ttempidx)/sizeof(WORD)); al1++)				
	{
		if(ttempidx[al1] == 0xFFFF)
		{
			return FALSE;
		}
	}
	
															// D_2NDTHERM_TBL are vacant ?
	for(al1 = 0; al1 < (sizeof(D_2NDTHERM_TBL)/sizeof(WORD)); al1++)
	{
		if(D_2NDTHERM_TBL[al1] == 0xFFFF)
		{
			return FALSE;
		}
	}
	
															// D_2ndttempidx are vacant ?
	for(al1 = 0; al1 < (sizeof(D_2ndttempidx)/sizeof(WORD)); al1++)
	{
		if(D_2ndttempidx[al1] == 0xFFFF)
		{
			return FALSE;
		}
	}
	
	// Device info
	if( D_SERIES == 0xFF )									// D_SERIES value is vacant ?
	{
		return FALSE;
	}
	
															// MF_NAME are vacant ?
	for(al1 = 0; al1 < (sizeof(MF_NAME)/sizeof(BYTE)); al1++)
	{
		if(MF_NAME[al1] == 0xFF)
		{
			return FALSE;
		}
	}
	
															// Dev_NAME are vacant ?
	for(al1 = 0; al1 < (sizeof(Dev_NAME)/sizeof(BYTE)); al1++)
	{
		if(Dev_NAME[al1] == 0xFF)
		{
			return FALSE;
		}
	}
	
															// Dev_chem are vacant ?
	for(al1 = 0; al1 < (sizeof(Dev_chem)/sizeof(BYTE)); al1++)
	{
		if(Dev_chem[al1] == 0xFF)
		{
			return FALSE;
		}
	}
	
	if( SMB_addr == 0xFF)									// SMB_addr value is vacant ?
	{
		return FALSE;
	}

	// Since All control flag sets 1 CONFLG data is 0xFFFF. Skip CONFLG data check.    
//	if( memcmp((__near _ST_CTLFLG1 *)&tmp, (__near _ST_CTLFLG1 *)&CONFLG, sizeof(_ST_CTLFLG1)) != 0)		// CONFLG value is vacant ?
//	{
//		return FALSE;
//	}
	
	
	// Capacity
	if( INIT_RSOC == 0xFF )									// INIT_RSOC is vacant ?
	{
		return FALSE;
	}
	
	if( INIT_FCC == 0xFFFF )								// INIT_FCC is vacant ?
	{
		return FALSE;
	}
	
	if( CCP_V == 0xFFFF )									// CCP_V is vacant ?
	{
		return FALSE;
	}
	
	if( CCP_lvl == 0xFF )									// CCP_lvl is vacant ?
	{
		return FALSE;
	}
	
															// INITCAP_TBL are vacant ?
	for(al1 = 0; al1 < ( sizeof(INITCAP_TBL)/sizeof(BYTE) ); al1++)	{
		if(INITCAP_TBL[al1] == 0xFF)
		{
			return FALSE;
		}
	}
															// INITV_TBL are vacant ?
	for(al1 = 0; al1 < ( sizeof(INITV_TBL)/sizeof(WORD) ); al1++)	{
		if(INITV_TBL[al1] == 0xFFFF)
		{
			return FALSE;
		}
	}
	
	// Protection
	if( D_CBONV == 0xFFFF )									// D_CBONV is vacant ?
	{
		return FALSE;
	}
	
	if( D_CBOFFV == 0xFFFF )								// D_CBOFFV is vacant ?
	{
		return FALSE;
	}
	
	if( D_CBENVH == 0xFFFF )								// D_CBENVH is vacant ?
	{
		return FALSE;
	}
	
	if( D_CBENVL == 0xFFFF )								// D_CBENVL is vacant ?
	{
		return FALSE;
	}
	
	if( OVERCH1 == 0xFFFF )									// OVERCH1 is vacant ?
	{
		return FALSE;
	}
	
	if( OCC1JT == 0xFF )									// OCC1JT is vacant ?
	{
		return FALSE;
	}
	
	if( OVERCH2 == 0xFFFF )									// OVERCH2 is vacant ?
	{
		return FALSE;
	}
	
	if( OCC2JT == 0xFF )									// OCC2JT is vacant ?
	{
		return FALSE;
	}
	
	if( OVERDI1 == 0xFFFF )									// OVERDI1 is vacant ?
	{
		return FALSE;
	}
	
	if( ODC1JT == 0xFF )									// ODC1JT is vacant ?
	{
		return FALSE;
	}
	
	if( OVERDI2 == 0xFFFF )									// OVERDI2 is vacant ?
	{
		return FALSE;
	}
	
	if( ODC2JT == 0xFF )									// ODC2JT is vacant ?
	{
		return FALSE;
	}
	
	if( CHGPV == 0xFFFF )									// CHGPV is vacant ?
	{
		return FALSE;
	}
	
	if( CHGPVJT == 0xFF )									// CHGPVJT is vacant ?
	{
		return FALSE;
	}
		
	if( D_INIT_IMP == 0xFFFF )								// D_INIT_IMP are vacant ? 
	{
		return FALSE;
	}
	
	if( D_IMP_CURR == 0xFF )								// D_IMP_CURR are vacant ?
	{
		return FALSE;
	}
	
	if( D_RSOC_IMP == 0xFF )								// D_RSOC_IMP are vacant ?
	{
		return FALSE;
	}
		
	if( D_IMP_TEMPL == 0xFF )								// D_IMP_TEMPL are vacant ?
	{
		return FALSE;
	}
	
	if( D_IMP_TEMPH == 0xFF )								// D_IMP_TEMPH are vacant ?
	{
		return FALSE;
	}
	if( D_STR_TEMP == 0xFF )								// D_STR_TEMP are vacant ?
	{
		return FALSE;
	}
	if( D_STR_DLTV == 0xFFFF )								// D_STR_DLTV are vacant ?
	{
		return FALSE;
	}
	
	return TRUE;											// there are All necessary data
	
}