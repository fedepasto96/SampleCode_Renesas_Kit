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
* File Name		: mode.c
* Contents		: mode function source file
* Device		: RAJ240090/100
* Compiler		: CC-RL (V.4.01)
* Note			: 
*""FILE COMMENT END""**********************************************************/


#define _MODE_C

/***********************************************************************
** Include files
***********************************************************************/
#include "define.h"								// union/define definition
#include "dataflash.h"							// DataFlash data definition
#include "ram.h"								// ram.c
#include "datcalc_spl.h"						// datcalc_spl.c
#include "mcu.h"								// mcu.c
#include "afe.h"								// afe.c
#include "smbus.h"								// smbus.c
#include "smbus_ex.h"							// smbus_lnv.c

#include "mode.h"
#include "cell.h"

#include "kousei.h"
#include "dataflash.h"
#include "afe1.h"

/***********************************************************************
** Pragma directive
***********************************************************************/

/***********************************************************************
** Announcement of internal function prototype
***********************************************************************/
static void FullCharge(void);					// Full Charge Processing
static void Set_ODC(void);						// Set OverDischargeCurrent
static void Chgwait_Chk(void);					// Charge wait Check
static void MainMode_Chk(void);					// MainMode Check
static void Set_FET(void);						// Set FET
void Set_CCCV(void);							// Set CCCV


// - Internal variable -
static _SHORT2CHAR	_tfc_cnt;					// Full Charge check count
static BYTE		alow_cnt;						// Discharge stop count
static BYTE		afcdc_cnt;						// Discharge detection count(FC)
static BYTE		aocc_cnt1,aocc_cnt2;			// OverChgCurr count
static BYTE		aodc_cnt1,aodc_cnt2;			// OverDisCurr count
static BYTE		aoccrel_cnt;					// OverChgCurr release count
static BYTE		aodcrel_cnt;					// OverDisCurr release count
static BYTE		ascrel_cnt;						// ShortCurr release count
static BYTE		aov_cnt;						// Over voltage release count

WORD			tcom14_new;						// CC/CV data update
WORD			tcom15_new;						// CC/CV data update



/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: Mode Check Processing Function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Mode_Chk(void)
*-------------------------------------------------------------------
* Function			: Judge mode transition from each mode.
*					: 
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
void Mode_Chk(void)
{
	
	// - All -> PowerDown -
	if( t_com24 <= 0 )						// Not charging
	{
		if(tminv < D_PDVOLT )				// Less than power down Voltage ?
		{
			PowerDown();					// PowerDown function
		}
	}
	
	// - Judgement process of each mode -
	switch( amode )
	{
	case M_WAKE:								// WakeUp
		Chgwait_Chk();							// Charge Wait Check
		if( amode == M_WAKE )					// WakeUp ?
		{
			if( tmaxv >= FULLCHGHV && f_discharge == OFF)				// Full charge determination voltage or more ?
			{
				amode = M_TERM;					// Mode to Charge Terminate
				afet = FET_D;					// FET control [C=OFF,D=ON]
				Set_FET();
				FullCharge();					// Full Charge Processing
			} else {							// Not Full Charge
				amode = M_DIS;					// Mode to Discharging
				afet = FET_CD;					// FET control [C=ON ,D=ON]
				Set_FET();
			}
		}
		break;

	case M_DIS:									// Discharge
		
		if( f_charge == ON )					// Charging current detection ?
		{
			if((adegree >= COTH) || (adegree < COTL))		// Rechargeable temperature range ?
			{
				amode = M_COH;								// Mode to Charge OverHeat
				f_over_tmp =ON;								// Set OTA Alarm
				f_crelearn = OFF;                           // Charge relearning flag = OFF
				relcap_c = 0;					        	// Reset relearn capacity
				afet = FET_D;								// FET control [C=OFF,D=ON]
				Set_FET();
			}else {
			
				amode = M_CHG;					// Mode to Charging
				afet = FET_CD;					// FET control [C=ON ,D=ON]
				Set_FET();
			}
			alow_cnt = 0;						// Clear Discharge stop count
		} else {								// Charging current undetected
			// - Discharging -> ChargeWait -
			if( tminv < DISSTOPV )				// Less than discharge stop voltage ?
			{
				alow_cnt++;						// Discharge stop count + 1
				if( alow_cnt == 4 )				// Discharge stop count = 4 ?
				{
					alow_cnt = 0;				// Clear Discharge stop count
					lrc_w = 0;					// Clear Correction capacity
					
					amode = M_CWIT;				// Mode to ChargeWait
					afet = FET_C;				// FET control [C=ON ,D=OFF]
					Set_FET();
				}
			} else {							// Discharge stop voltage or more
				alow_cnt = 0;					// Clear Discharge stop count
			}
		}
		MainMode_Chk();							// MainMode Check
		break;

	case M_CHG:									// Charging
		// - Charging -> Discharging -
		if( f_discharge == ON )					// Discharge current detection ?
		{
			amode = M_DIS;						// Mode to Discharging
			afet = FET_CD;						// FET control [C=ON ,D=ON]
			Set_FET();
			MainMode_Chk();						// MainMode Check
			break;
		} else {								// Not detect discharge
			Chgwait_Chk();
		}
		
		// - Charging -> Charge OverHeat -
		if((adegree >= COTH) || (adegree < COTL))		// Rechargeable temperature range ?
		{
			amode = M_COH;								// Mode to Charge OverHeat
			f_over_tmp =ON;								// Set OTA Alarm
			f_crelearn = OFF;							// Charge relearning flag = OFF
			relcap_c = 0;					        	// Reset relearn capacity
			afet = FET_D;								// FET control [C=OFF,D=ON]
			Set_FET();
		}
		
		// - Charging -> ChargeTerminate -
		if( f_over_chg == ON )					// Full charge detection ?
		{
			amode = M_TERM;						// Mode to ChargeTerminate
			afet = FET_D;						// FET control [C=OFF,D=ON]
			Set_FET();
			MainMode_Chk();						// MainMode Check
			break;
		}
		
		MainMode_Chk();							// MainMode Check
		break;

	case M_TERM:								// Charge terminate

		if( f_discharge == ON )					// Discharge current detection ?
		{
			afcdc_cnt++;						// Discharge detection count(FC) + 1
			if( afcdc_cnt == 8 )				// Discharge detection count(FC) = 8 ?
			{
				afcdc_cnt = 0;					// Clear Discharge detection count(FC)
				amode = M_DIS;					// Mode to Discharging
				afet = FET_CD;					// FET control [C=ON ,D=ON]
				Set_FET();
			}
		} else {								// Discharge undetected
			afcdc_cnt = 0;						// Clear Discharge detection count(FC)
		}
		
		MainMode_Chk();							// MainMode Check
		break;

	case M_CWIT:								// Charge wait
		if( f_charge == ON && tminv >= DISSTOPV)	// Charging current detection & tminv is more than discharge stop voltage ?
		{
			amode = M_CHG;						// Mode to Charging
			afet = FET_CD;						// FET control [C=ON ,D=ON]
			Set_FET();
		}
		//PreChg_Chk();							// PreCharge Check
		Slow_Chk();								// Slow mode check
		
		break;
/*
	case M_PREC:								// Pre charge

		if( tminv >= PRECHGHV)					// minV >= PreCharge voltage ?
		{
			amode = M_CWIT;						// Mode to ChargeWait
			afet = FET_C;						// FET control [C=ON ,D=OFF]
			Set_FET();
		}

		break;
*/
	case M_COH:									// Over heat release temp
			if(f_discharge == ON || (adegree < (COTH - CTH_hys))
				&& (adegree >= (COTL + CTH_hys)))
			{
				amode = M_WAKE;					// Mode to WakeUp
				f_over_tmp =OFF;				// Clear OTA Alarm
			}
			
			if((adegree >= DOTH) || (adegree < DOTL))		// Check temperature range
			{
				amode = M_DOH;								// Mode to Charge OverHeat
				afet = FET_OFF;								// FET control [C=OFF,D=OFF]
				Set_FET();
			}
			
			if(F_2NDTHE == ON)
			{
				if(adegree2 >= D_2NDTHM)		//  check temperature range
				{
					amode = M_FOH;								// Mode to 2nd TH OverHeat
					afet = FET_OFF;								// FET control [C=OFF,D=OFF]
					Set_FET();
				}
			}
			
		break;
		
	case M_DOH:									// Over heat release temp
			if((adegree < (DOTH - DTH_hys))
				&& (adegree >= (DOTL + DTH_hys)))
			{
				amode = M_COH;								// Mode to Charge OverHeat
				afet = FET_D;								// FET control [C=OFF,D=ON]
				Set_FET();
			} 
			if(F_2NDTHE == ON)
			{
				if(adegree2 >= D_2NDTHM)						// Rechargeable temperature range ?
				{
					amode = M_FOH;								// Mode to 2nd TH OverHeat
					afet = FET_OFF;								// FET control [C=OFF,D=OFF]
					Set_FET();
				}
			}
			
		break;

	case M_OCC:									// Over charge current
		if( f_discharge == ON )					// Discharge current detection ?
		{
			aoccrel_cnt = 0;						// Clear OverChgCurr release count
			f_occ_alarm = OFF;					// Clear OCC Alarm
			amode = M_WAKE;						// Mode to WakeUp
		}
		if( t_com24 < 100 )						// Curr less than 100mA ?
		{
			aoccrel_cnt++;						// OverChgCurr release count + 1
			if( aoccrel_cnt == 40 )				// 10s elapsed ?
			{
				aoccrel_cnt = 0;				// Clear OverChgCurr release count
				f_occ_alarm = OFF;				// Clear OCC Alarm
				amode = M_WAKE;					// Mode to WakeUp
			}
		}
		break;

	case M_ODC:									// Over discharge current
		if( labsc < 100 )						// Curr less than 100mA ?
		{
			aodcrel_cnt++;						// OverDisCurr release count + 1
			if( aodcrel_cnt == 40 )				// 30s elapsed ?
			{
				aodcrel_cnt = 0;				// Clear OverDisCurr release count
				f_odc_alarm = OFF;				// Clear ODC Alarm
				amode = M_WAKE;					// Mode to WakeUp
			}
		}
		
		if( f_charge == ON )					// Charging current detection ?
		{
			aodcrel_cnt = 0;					// Clear OverDisCurr release count
			f_odc_alarm = OFF;					// Clear ODC Alarm
			amode = M_WAKE;						// Mode to WakeUp
		}
		break;

	case M_SHC:									// Short current
		if( labsc < 100 )						// Curr less than 100mA ?
		{
			ascrel_cnt++;						// Shortcurr release count + 1
			if( ascrel_cnt == 40 )				// 10s elapsed ?
			{
				ascrel_cnt = 0;					// Clear Shortcurr release count
				f_short_alarm = OFF;			// Clear SC Alarm 
				amode = M_WAKE;					// Mode to WakeUp
			}
		}
		if( f_charge == ON )					// Charging current detection ?
		{
			ascrel_cnt = 0;						// Clear Shortcurr release count
			f_short_alarm = OFF;				// Clear SC Alarm
			amode = M_WAKE;						// Mode to WakeUp
		}
		break;
		
	case M_OV:
	
		if( tmaxv < FULLCHGHV || f_discharge == ON)
		{
			f_ov_alarm = OFF;					// Clear OV Alarm
			amode = M_WAKE;						// Move to WakeUp
		}
		
		break;
		
	case M_FOH:									// 2nd Th over heat
		// Discharge over heat mode check -
		if(F_2NDTHE == ON)
		{
		
			if( adegree2 < (D_2NDTHM - D_2NDTHM_hys) )					// FET temp < FET-off rel.T ?
			{
				if( adegree >= DOTH					// Out of range of Dischg temp?
					|| adegree < DOTL )
				{
					amode = M_DOH;					// DischargeOverHeat mode
				
				} else {							// In the range of DOH
					amode = M_WAKE;					// WakeUp mode
					f_over_tmp =OFF;				// Clear OTA Alarm
				}
			}
		}
		break;

	default:
		break;
	}
	
	aafe = afet;
	
	if( f_cfctl == ON )							// C-FET=ON ?
	{
		f_cfet = ON;							// Set PackStatus:CFET
	} else {									// C-FET=OFF
		f_cfet = OFF;							// Clear PackStatus:CFET
	}

	if( f_dfctl == ON )							// D-FET=ON ?
	{
		f_dfet = ON;							// Set PackStatus:DFET
	} else {									// D-FET=OFF
		f_dfet = OFF;							// Clear PackStatus:DFET
	}
	
	Set_CCCV();									// Set CC & CV by different condition
}


/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: Full Charge Processing Function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void FullCharge(void)
*-------------------------------------------------------------------
* Function			: Function of when full charge is judged.
*					: 
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
static void FullCharge(void)
{
	WORD twork;
	WORD FCClimit;
	
	f_over_chg = ON;							// Set OVER_CHARGED_ALARM
	f_fullchg = ON;								// Set FULLY_CHARGED bit
	
	if(relcap_c == 0)                           // If relearn capacity is reset to 0 during abnormal condition?
	{
		t_com0fc = t_com10c;                    // RC = original FCC
		
	}else{
		twork = (WORD)(relcap_c/ 14400);        // New FCC calculation
		FCClimit = (WORD)((long)t_com10c * 70 / 100);	// FCC limit calculation
		if (twork < FCClimit)					// New FCC < 70% of original FCC ?
		{
			t_com10c = FCClimit;				// New FCC = 70% of original FCC
			t_com0fc = t_com10c;				// New RC = New FCC
		}else{
			t_com10c = (WORD)(relcap_c/ 14400);	// New FCC = Relearn capacity
			t_com0fc = (WORD)(relcap_c/ 14400);	// New RC =  Relearn capacity
		}
	}
	lrc_w = (long)t_com10c * 14400;				// Correction capacity calculation
	t_com0d = 100;								// RSOC = 100%
	t_com14 = 0;								// ChargingCurrent() = 0
	t_com15 = 0;								// ChargingVotlage() = 0
}

/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: Charge Wait Check Processing Function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Chgwait_Chk(void)
*-------------------------------------------------------------------
* Function			: Check Charge Wait.
*					: 
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
static void Chgwait_Chk(void)
{
	if( tminv < DISSTOPV)						// Discharge stop voltage less than voltage ?
	{
		amode = M_CWIT;								// Mode to Charge Wait
		afet = FET_C;								// FET control [C=ON,D=OFF]
		Set_FET();
		lrc_w = 0;									// Clear Correction capacity
	}
}


/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: OverDischargeCurrent Set Processing Function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Set_ODC(void)
*-------------------------------------------------------------------
* Function			: Set to OverDischargeCurrent.
*					: 
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
static void Set_ODC(void)
{
	amode = M_ODC;								// Mode to OverDischargeCurrent
	f_odc_alarm = ON;							// Set ODC Alarm
	afet = FET_C;								// FET control [C=ON ,D=OFF]
	Set_FET();
}


/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: MainMode Check Processing Function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void MainMode_Chk(void)
*-------------------------------------------------------------------
* Function			: Judge mode transition from main mode to abnormal mode.
*					: 
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
static void MainMode_Chk(void)
{
	// - Main -> Sleep
	Slow_Chk();									// Slow mode check
	if( f_slow == ON )							// Become slow mode ?
	{
		amode = M_ALON;							// Stand Alone mode
		afet |= FET_D;							// FET [C=previous,D=ON]
		Set_FET();
	}

	// - Main -> Discharge Over Heat -
	if((adegree >= DOTH) || (adegree < DOTL))		// Check temperature range
	{
		amode = M_DOH;								// Mode to Charge OverHeat
		f_over_tmp =ON;								// Set OTA Alarm
		f_crelearn = OFF;                           // Charge relearning flag = OFF
		relcap_c = 0;					        	// Reset relearn capacity
		afet = FET_OFF;								// FET control [C=OFF,D=OFF]
		Set_FET();
	}

	// - Main -> OverChargeCurrent 1-
	if( f_charge == ON )						// Charging current detection ?
	{
		if( labsc >= OVERCH1 )					// OverChargeCurrent detection ?
		{
			aocc_cnt1++;							// OverChgCurr release count + 1
			if( aocc_cnt1 == OCC1JT )				// OCC determination time elapsed ?
			{
				aocc_cnt1 = 0;					// Clear OverChgCurr release count
				amode = M_OCC;					// Mode to OverChargeCurrent
				f_occ_alarm = ON;				// Set OCC Alarm
				f_crelearn = OFF;				// Charge relearning flag = OFF
				relcap_c = 0;					// Reset relearn capacity
				afet = FET_D;					// FET control [C=OFF,D=ON]
				Set_FET();
			}
		} else {								// OCC undetected
			aocc_cnt1 = 0;						// Clear OverChgCurr release count
		}
	} else {
		aocc_cnt1 = 0;							// Clear OverChgCurr release count
	}
	
	// - Main -> OverChargeCurrent 2-
	if( f_charge == ON )						// Charging current detection ?
	{
		if( labsc >= OVERCH2 )					// OverChargeCurrent detection ?
		{
			aocc_cnt2++;						// OverChgCurr release count + 1
			if( aocc_cnt2 == OCC2JT )			// OCC determination time elapsed ?
			{
				aocc_cnt2 = 0;					// Clear OverChgCurr release count
				amode = M_OCC;					// Mode to OverChargeCurrent
				f_occ_alarm = ON;				// Set OCC Alarm
				f_crelearn = OFF;				// Charge relearning flag = OFF
				relcap_c = 0;					// Reset relearn capacity
				afet = FET_D;					// FET control [C=OFF,D=ON]
				Set_FET();
			}
		} else {								// OCC undetected
			aocc_cnt2 = 0;						// Clear OverChgCurr release count
		}
	} else {
		aocc_cnt2 = 0;							// Clear OverChgCurr release count
	}
	
	// - Main -> OverDischargeCurrent 1-
	if( f_discharge == ON )						// Discharge current detection ?
	{
		if( labsc >= OVERDI1 )					// OverDischargeCurrent more ?
		{
			aodc_cnt1++;						// OverDisCurr release count + 1
			if( aodc_cnt1 == ODC1JT )			// ODC determination time elapsed ?
			{
				aodc_cnt1 = 0;					// Clear OverDisCurr release count
				Set_ODC();						// Set OverDischargeCurrent
			}
		} else {								// ODC undetected
			aodc_cnt1 = 0;						// Clear OverDisCurr release count
		}
	}
	
	// - Main -> OverDischargeCurrent 2-
	if( f_discharge == ON )						// Discharge current detection ?
	{
		if( labsc >= OVERDI2 )					// OverDischargeCurrent more ?
		{
			aodc_cnt2++;						// OverDisCurr release count + 1
			if( aodc_cnt2 == ODC2JT )			// ODC determination time elapsed ?
			{
				aodc_cnt2 = 0;					// Clear OverDisCurr release count
				Set_ODC();						// Set OverDischargeCurrent
			}
		} else {								// ODC undetected
			aodc_cnt2 = 0;						// Clear OverDisCurr release count
		}
	}
	
	// - Main -> OverVoltage -
	if( f_charge == ON )						// Charge current detection ?
	{
		if( tmaxv >= CHGPV )					// OverVoltage more ?
		{
			aov_cnt++;							// OverVoltage release count + 1
			if( aov_cnt == CHGPVJT )			// OV determination time elapsed ?
			{
				aov_cnt = 0;					// Clear OverVoltage release count
				amode = M_OV;					// Mode to OverVoltage
				f_ov_alarm = ON;				// Set OV Alarm
				f_crelearn = OFF;				// Charge relearning flag = OFF
				relcap_c = 0;					// Reset relearn capacity
				afet = FET_D;					// FET control [C=OFF,D=ON]
				Set_FET();
				
			}
		} else {									// OV undetected
			aov_cnt = 0;							// Clear OverVoltage release count
		}
	}
	
	if(F_2NDTHE == ON)
	{
	
		// - Main -> 2nd TH Over Heat -
		if((adegree2 >= D_2NDTHM))						// Check  temperature range
		{
			amode = M_FOH;								// Mode to 2nd TH OverHeat
			f_over_tmp =ON;								// Set OTA Alarm
			f_crelearn = OFF;							// Charge relearning flag = OFF
			relcap_c = 0;					        	// Reset relearn capacity
			afet = FET_OFF;								// FET control [C=OFF,D=OFF]
			Set_FET();
		}
	}

}

/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: FET Set Processing Function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Set_FET(void)
*-------------------------------------------------------------------
* Function			: Set to FET.
*					: 
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
static void Set_FET(void)
{
	AFE_WR(AFE_FCON,afet);
}

/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: ALARM Check Processing Function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Alarm_Chk(void)
*-------------------------------------------------------------------
* Function			: Judge the Alarm of BatteryStatus() except
*					:  depending on mode.
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
void Alarm_Chk(void)
{
	WORD	twork;

	// - OVER_CHARGED_ALARM -
	if( f_over_chg == ON )						// Full charge detection ?
	{
		if( t_com24 <= 0 )						// Not charging ?
		{
			f_over_chg = OFF;					// Clear OVER_CHARGED_ALARM
		}
	} else {									// Not OVER_CHARGED_ALARM
		if((afet & FET_C) == FET_C )			// C-FET = ON ?
		{
			if( f_charge == ON )				// Charging current detection ?
			{
				if( f_fullchg == ON )			// FULLY_CHARGED = ON ?
				{
					if( t_com0fc >= t_com10c )	// RC >= FCC ?
					{
						FullCharge();			// Full Charge Processing
					}
				} else {						// FULLY_CHARGED = OFF
					twork = NORMAL_CV;// / D_SERIES;
												// MaxV >= Single cell CV-FCtaperV
												// & Full Charge Current less than ?
					if((tmaxv >= (twork-FULLCHG_TV)) && (labsc < FULLCHG_CURR))
					{
						tfc_cnt ++;				// Full Charge check count + 1
												// Full charge determination time elapsed ?
						if( tfc_cnt == FULLCHG_T )
						{
							tfc_cnt = 0;		// Clear Full Charge check count
							FullCharge();		// Full Charge Processing
						}
					} else {
						if( tfc_cnt != 0 )		// Full Charge check count = 0 ?
						{
							tfc_cnt --;			// Full Charge check count - 1
						}
					}
				}
			} else {							// Charging current undetected
				tfc_cnt = 0;					// Clear Full Charge check count
			}
		}
	}
	
	// - FULLY_DISCHARGED (STATUS) -
	if( f_fulldis == ON )						// FULLY_DISCHARGED = ON ?
	{
		if( f_charge == ON )					// Charging ?
		{
			f_fulldis = OFF;					// Clear the STATUS
		}
	}

	// - FULLY_CHARGED (STATUS) -
	if( f_fullchg == ON )						// FULLY_CHARGED = ON ?
	{
		if(f_discharge == ON)					// Discharging ?
		{
			f_fullchg = OFF;					// Clear the STATUS
		}
	}
	
	// - DISCHARGING (STATUS) -
	if( t_com24 < 0 )							// Now discharging ?
	{
		f_dischg = ON;							// Set the STATUS
	} else {									// Not discharging
		f_dischg = OFF;							// Clear the STATUS
	}
	
}

/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: Slow mode check function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Slow_Chk(void)
*-------------------------------------------------------------------
* Function			: Check the condition of slow mode.
*					:
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
void Slow_Chk(void)
{
	if( f_nosmb == ON )						// No SMBus communication ?
	{
		if(acccv_cnt >= 2 )					// & 1sec later to send CC/CV ?
		{
			if(f_charge == OFF )			// Not charging ?
			{
				if( f_discharge == OFF		// Not discharging
					|| labsc < D_SLPCURR )	// or less than leave current ?
				{
					f_slow = ON;			// Set slow flag
				}
			}
		}
	}
}

/*""FUNC COMMENT""***************************************************
* ID				: 1.0
* module outline	: Set CC & CV by different condition
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Set_CCCV(void)
*-------------------------------------------------------------------
* Function			: Set CC & CV by different condition.
*					:
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: 
* 					: 
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
void Set_CCCV(void)
{
	
	tcom14_new = t_com14;						// CC/CV backup
	tcom15_new = t_com15;
	

	if( f_cfctl == ON )							// C-FET=ON ?
	{

		if( f_fullchg == OFF )					// FULLY_CHARGED = OFF ?
		{

			tcom15_new = NORMAL_CV * D_SERIES;	// Set NormalCV * Serial number of cell

			// - CC setting -
			if( amode == M_CWIT )				// Charge Wait mode ?
			{
				tcom14_new = CHGWAIT_CC;		// ChargingCurrent(Charge Wait)
			} else {							// Not Charge Wait mode ?
				tcom14_new = NORMAL_CC;			// ChargingCurrent(Normal)
			}
		} else {								// FULLY_CHARGED = ON
			tcom14_new = 0;						// CC/CV = 0
			tcom15_new = 0;
		}

	}else										// C-FET=OFF
	{
		tcom15_new = 0;							// CV = 0
		tcom14_new = 0;							// CC = 0		
	}

	t_com14 = tcom14_new;
	t_com15 = tcom15_new;
	
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: AFE Battery Cell Voltage Detection setting Process
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void AFE_BCVD_EN(void)
 *--------------------------------------------------------------------------
* Function			: AFE Battery Cell Voltage Detection setting
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
void AFE_BCVD_EN(void)
{
	BYTE atmp,atmp1;
	WORD ttmp;
	
	AFE_WR(AFE_WINCHG,WINCHG_RM1);														// AFE Window 1
	AFE_WR(AFE_APCLKCON,ADDETLM_EN);													// voltage detection with ADC in Low power mode enable
	
	atmp1 = D_OVUVDET & OVUVDET_MSK;
	AFE_WR(AFE_OVUVDET,atmp1 | D_SERIES);
	AFE_WR(AFE_VDCT,D_VDCT);															// Conversion time, AD conversion Stabilization wait time setting

	if( (D_OVUVDET & UVDET_DIS) != UVDET_DIS)											// Battery Cell Voltage detection(Discharge) enable check ?
	{
		ttmp = Calcvolt_BCVD(D_UVDH);
	
		AFE_WR(AFE_UVTHL,ttmp & 0x00FF);												// Setting value(Low side)
		AFE_WR(AFE_UVTHH,ttmp >> 8);													// Setting value(High side)
	}

	if( (D_OVUVDET & OVDET_DIS) != OVDET_DIS)											// Battery Cell Voltage detection(Charge) enable check ?
	{
	
		ttmp = Calcvolt_BCVD(D_OVDH);
	
		AFE_WR(AFE_OVTHL,ttmp & 0x00FF);												// Setting value(Low side)
		AFE_WR(AFE_OVTHH,ttmp >> 8);													// Setting value(High side)
	}
	
//	if( D_VDIT == 0)
//	{
//		AFE_WR(AFE_VDIT,D_VDIT);														// Voltage detection time interval setting
//	}else {
//		atmp1 = D_VDIT--;
//		AFE_WR(AFE_VDIT,atmp1);															// Voltage detection time interval setting
//	}

	AFE_WR(AFE_VDIT,D_VDIT);
	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
	AFE_RD(AFE_AFMK1,atmp);																// Read AFMK1 registor
	AFE_WR(AFE_AFMK1,atmp | INT_VDETMSK);												// Battery Cell Voltage detection interrupt enabled
	AFE_WR(AFE_AFIF1,INT_VDETIR_W);
	
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: AFE Temperature Voltage Detection setting Process
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void AFE_TVD_EN(void)
 *--------------------------------------------------------------------------
* Function			: AFE Temperature Voltage Detection setting
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
void AFE_TVD_EN(void)
{
	BYTE atmp,atmp1;
	WORD ttmp;
	
	AFE_WR(AFE_WINCHG,WINCHG_RM1);														// AFE Window 1
	AFE_WR(AFE_APCLKCON,ADDETLM_EN);													// voltage detection with ADC in Low power mode enable
	
	
	atmp1 = D_OTUTDET & OTUTDET_MSK;
	AFE_WR(AFE_OTUTDET,atmp1);

	if( (D_OTUTDET & UTDEN_DIS) != UTDEN_DIS)													// Under Temperature detection enable ?
	{
		ttmp = Calcvolt_TVD(D_UTDH);
	
		AFE_WR(AFE_UTTHL,ttmp & 0x00FF);												// Setting value(Low side)
		AFE_WR(AFE_UTTHH,ttmp >> 8);													// Setting value(High side)
	}

	if( (D_OTUTDET & OTDEN_DIS) != OTDEN_DIS)													// Over Temperature detection enable ?
	{
	
		ttmp = Calcvolt_TVD(D_OTDH);
	
		AFE_WR(AFE_OTTHL,ttmp & 0x00FF);												// Setting value(Low side)
		AFE_WR(AFE_OTTHH,ttmp >> 8);													// Setting value(High side)
	}
	
//	if( D_VDIT == 0)
//	{
//		AFE_WR(AFE_VDIT,D_VDIT);														// Voltage detection time interval setting
//	}else {
//		atmp1 = D_VDIT--;
//		AFE_WR(AFE_VDIT,atmp1);															// Voltage detection time interval setting
//	}

	AFE_WR(AFE_VDIT,D_VDIT);
	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
	AFE_RD(AFE_AFMK1,atmp);																// Read AFMK1 registor
	AFE_WR(AFE_AFMK1,atmp | INT_VDETMSK);												// Battery Cell Voltage detection interrupt enabled
	AFE_WR(AFE_AFIF1,INT_VDETIR_W);
	
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: BCVD setting voltage calculation function
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: WORD Calcvolt_BCVD(WORD tvolt)
 *--------------------------------------------------------------------------
 * Function			: Calculate AD value based on BCVD setting voltage.
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: WORD tvolt: BCVD setting voltage
 *--------------------------------------------------------------------------
 * Return			: AD value
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
WORD Calcvolt_BCVD(WORD tvolt)
{
	
	long ttmp1;
	WORD ttmp2;
	
	if(F_CALIB1P == OFF)
	{
	// AD = (voltage - VrefL) * (VH - VL) / (VrefH - VrefL) + VL
	// *:Vx = Calibration AD value, Vrefx = Calibration reference voltage value
		ttmp1 = ((long)tvolt - D_LVREF[0]) * ( D_HV[0] - D_LV[0] );
		ttmp2 = D_HVREF[0] - D_LVREF[0];
		ttmp1 = ttmp1 / ttmp2;
		
		ttmp1 = (WORD)(ttmp1 + D_LV[0]);
	}else
	{
		ttmp1 = (WORD)((long)tvolt * D_HV[0] / D_HVREF[0]);
	}
	
	return ttmp1;
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: TVD setting voltage calculation function
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: WORD Calcvolt_TVD(WORD ttemp)
 *--------------------------------------------------------------------------
 * Function			: Calculate AD value based on TVD setting voltage.
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: WORD ttemp: TVD setting voltage
 *--------------------------------------------------------------------------
 * Return			: AD value
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
WORD Calcvolt_TVD(WORD ttemp)
{
	
	BYTE	aidx;														// refer index table
	BYTE	apull_L,apull_H;
	BYTE 	awinchg;
	WORD	tr1 = *(__far WORD*)0x01C840;								// internal pull-up resistance
	WORD	ttadvregpull;
	long 	ttmp1;
	WORD 	ttmp2,ttmp3;
	long 	lr2;														// thermistor resistance
	
	/* AFE Window Backup */
	AFE_RD(AFE_WINCHG,awinchg)											// AFE Window backup
	AFE_WR(AFE_WINCHG,WINCHG_RM0)
	// AD conversion for Pull-up voltage 
	AFE_WR(AFE_ADMSEL4,ADATOFF3 | ADATVREGpullAN0pull | ADATVREGpull);			
																		// Select offset & puli-up voltage
	AFE_WR(AFE_ADCON2,ADATWAITTIME1 | ADATTIME1);						// Select AD conver time and wait time
	AFE_WR(AFE_ADCON0,ADC_EN);											// AD enabled
	AFE_WR(AFE_ADCON1,ADC_THERMMODE);									// Start AD conversion (Thermistor mode)
	
	while( PIF9 == 0 ) ;												// AD complete ?
	PIF9 = 0;															// Clear Interrupt request flag(MCU)
		
	AFE_WR(AFE_AFIF0,INT_ADIR_W);										// Clear interrupt request flag(AFE)
	
	AFE_RD(AFE_ADRL4,apull_L);											// get AD value(Pull-up voltage)
	AFE_RD(AFE_ADRH4,apull_H);											// get AD value(Pull-up voltage)
	
	ttadvregpull = ((WORD)apull_H << 8) + apull_L;
	
	for( aidx=0; aidx<6 && ttemp>((long)ttempidx[aidx+1]); aidx++ );
	// Temp = (ThTbl[0]-r2)*(Thidx[1]-Thidx[0])/(ThTbl[0]-ThTbl[1])+Thidx[0]
	// *:ThTbl[x] = Thermistor table value, Thidx[x] = Temperature step value in Thermistor table
	ttmp1 = (ttemp - ttempidx[aidx] - tthoff)*((long)THERM_TBL[aidx]*10 - (long)THERM_TBL[aidx+1]*10);
	ttmp2 = ttempidx[aidx+1] - ttempidx[aidx];
	ttmp1 /= ttmp2;

	lr2 = ((long)THERM_TBL[aidx]*10) - ttmp1;					// thermistor resistance value
	
	// AD value = (thermistor resistance * VREG pull-up AD value) / (internal pull-up resistance + thermistor resistance)
	ttmp3 = (lr2 * ttadvregpull) / (lr2 + tr1);
	
	/* AFE Window Recover */
	AFE_WR(AFE_WINCHG,awinchg)											// AFE Window
	
	return ttmp3;
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: AFE initialize Process
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void AFE_init(void)
 *--------------------------------------------------------------------------
 * Function			: AFE initialize.
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
void AFEWDT_EN(BYTE avalue)
{	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
	// AFE interrupt request flag clear
	AFE_WR(AFE_AFIF1,INT_WDTIR_W); 														// AFE WDT interrupt request flag clear
	
	/* AFE WDT stop */
	AFE_WR(AFE_AWDTCON,WDT_MTRSEL_EN | avalue);															// AFE WDT setting
	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: AFE initialize Process
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void AFE_init(void)
 *--------------------------------------------------------------------------
 * Function			: AFE initialize.
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
void AFEWDT_DIS(void)
{	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
	// AFE interrupt request flag clear
	AFE_WR(AFE_AFIF1,INT_WDTIR_W); 														// AFE WDT interrupt request flag clear
	
	/* AFE WDT stop */
	AFE_WR(AFE_AWDTCON,WDT_STOP);														// AFE WDT stop
	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: AFE initialize Process
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void AFE_init(void)
 *--------------------------------------------------------------------------
 * Function			: AFE initialize.
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
void AFEWDT_REFRESH(void)
{	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
	AFE_WR(AFE_AWDTRF,WDTCLEAR);														// WDT refresh
	
	AFE_WR(AFE_WINCHG,WINCHG_RM0);														// AFE Window 0
	
}

