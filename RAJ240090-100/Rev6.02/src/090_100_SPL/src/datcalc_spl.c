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
* File Name		: datcalc_spl.c
* Contents		: Data calculation function source file
* Device		: RAJ240090/100
* Compiler		: CC-RL (V.4.01)
* Note			: 
*""FILE COMMENT END""**********************************************************/

#define _DATCALC_SPL

#include "define.h"								// union/define definition
#include "datcalc.h"							// datcalc.c
#include "datcalc_spl.h"						// datcalc_spl.c
#include "dataflash.h"							// DataFlash data definition
#include "ram.h"								// ram.c
#include "smbus_ex.h"							// smbus_ex.c
#include "mcu.h"								// mcu.c
#include "afe.h"								// afe.c
#include "cell.h"								// cell.c
#include "mode.h"								// mode.c


/***********************************************************************
** Announcement of internal function prototype
***********************************************************************/
static void Calc_NormalRC(DWORD	lrc);


/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: RemainingCapacity() Calculation Function
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		:  void Make_RC(void)
 *--------------------------------------------------------------------------
 * Function			: Calculate RemainingCapacity() from RC integration work.
 *					: 
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: lrc_w		: RC integration work
 *					: 
 * Output			: t_com0fc	: RemainingCapacity() [mAh]
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
void Make_RC(void)
{
	WORD	twork;

	twork = (WORD)(lrc_w / (60*60*4));			// RC = RC_W / (60min*60sec*4)
	if( twork > t_com10c )						// RC > FCC ?
	{
		t_com0fc = t_com10c;					// RC = FCC
	} else {									// RC <= FCC
		t_com0fc = twork;
	}
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: Function of capacity calculation while
 * 					: discharging and voltage is higher than CP_H.
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void Calc_NormalRC(DWORD lrc)
 *--------------------------------------------------------------------------
 * Function			: It calculates capacity while discharging and
 *					:  the voltage is higher than CP_H.
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: lrc_w		: RC integration work
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: 
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
static void Calc_NormalRC(DWORD	lrc)
{
	long	lwork;

	lrc_w -= lrc;								// Substruct correction value
	lwork = (long)t_com10c * CCP_lvl * 144;		// Calculation the CCP capacity
	if((lrc_w < lwork) && (f_ccp == OFF))
	{
		lrc_w = lwork;
	}
	if(lrc_w < 0)
	{
		lrc_w = 0;
	}
}

/*""FUNC COMMENT""**********************************************************
 * ID				: 1.0
 * module outline	: RemainingCapacity() calculation function
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: void Calc_RC(void)
 *--------------------------------------------------------------------------
 * Function			: It calculates RemainingCapacity()
 *--------------------------------------------------------------------------
 * Argument			: None
 *--------------------------------------------------------------------------
 * Return			: None
 *--------------------------------------------------------------------------
 * Input			: None
 *					: 
 * Output			: t_com0fc	: RemainingCapacity() [mAh]
 *					: 
 *--------------------------------------------------------------------------
 * Used function	: Calc_NormalRC(), Make_RC()
 *					: 
 *--------------------------------------------------------------------------
 * Caution			: 
 *--------------------------------------------------------------------------
 *""FUNC COMMENT END""*****************************************************/
void Calc_RC(void)
{
	static BYTE	a0p_cnt;
	static BYTE	accp_cnt;

	if( f_fullchg == ON )						// After detecting FC ?
	{
		if( t_com24 <= 0 )						// Not charging ?
		{
			if( labsc > D_DCDET )				// Not discharging ?
			{
				f_fullchg = OFF;				// Full charge detection flag clear
			}
		}
	}
	
	if( t_com24 > 0 )							// Charging ?
	{
		if((f_ccp == ON) && (t_com0d >= CCP_lvl))
		{
			f_ccp = OFF;
		}
		lrc_w += labsc;							// Calc RC
		
		if( f_crelearn == ON )				    //  charge relarning flag is set? 
		{
			relcap_c += labsc;					//  Add up the absolute current for every 250ms
		}
		
	} else {									// Discharging or No current
		
		if( f_crelearn == ON )					//  Charge relearning flag is set?
		{
		    f_crelearn = OFF;					//  Charge relarning flag set to off
		    relcap_c = 0;  						//  Charge relearn capacity set to 0
		}
		
		
		if( f_ccp == OFF )						// Not detect CCP voltage ?
		{
			if( tminv < CCP_V )					// Less than Capacity correction point voltage
			{
				accp_cnt++;						// Increment CP_H det.counter

				if( accp_cnt >= 8 )				// Detect 8 times
				{
					accp_cnt = 0;				// Clear the counter
					f_ccp = ON;					// Set CCP detect flag
					if( t_com0d >= CCP_lvl )
					{
						lrc_w = (long)t_com10c * CCP_lvl * 144;	// Calculation the CCP capacity
					}
				} else {
					Calc_NormalRC(labsc);
				}
			} else {							// Capacity correction point voltage or more
				accp_cnt = 0;					// Clear the counter
				Calc_NormalRC(labsc);
			}
		} else {								// Already CCP is detected
			if( tminv < D_0PVOLT )				// lower than 0% voltage ?
			{
				a0p_cnt++;
				if( a0p_cnt >= 8 )				// Detect more than 8 times ?
				{
					f_crelearn = ON;            // Set charge relearn flag
					relcap_c = 0;			    // charge relearn capacity = 0 
					lrc_w = 0;
					t_com0fc = 0;				// RC[mAh] = 0
					f_fulldis = ON;				// Set FD flag
					f_fd_imp = ON;				// Set fully discharged flag for IMP Calc()
					return;
				}
			} else {							// Higher than 0% voltage
				a0p_cnt = 0;					// Clear 0% detection counter
				Calc_NormalRC(labsc);
			}
		}
	}
	Make_RC();									// Calculate RemainingCapacity
}

/*""FUNC COMMENT""***************************************************
* module outline	: Initial capacity setting function
*-------------------------------------------------------------------
* Include			: 
*-------------------------------------------------------------------
* Declaration		: void Init_Cap(void)
*-------------------------------------------------------------------
* Function			: Calculate and set the initial capacity from 
*					: Voltage-Capacity table.
*-------------------------------------------------------------------
* Return			: None
*-------------------------------------------------------------------
* Input				: None
* Output			: None
*-------------------------------------------------------------------
* Used function		: ReadVolt(), Make_RC()
*-------------------------------------------------------------------
* Caution			: 
*					: 
*""FUNC COMMENT END""**********************************************/
void Init_Cap(void)
{
	BYTE	aidx, aresult;

	CVT_Func();
															// Search using table
	for( aidx=0; tminv>=INITV_TBL[aidx+1] && aidx<4; aidx++ );
	
	if( tminv <= INITV_TBL[0] )								// Smaller than 0% voltage ?
	{
		lrc_w = 0;											// Set capacity to 0%
	} 
	else 
	{
		if( tminv >= INITV_TBL[5] )							// Bigger than 99% voltage ?
		{
															// Set capacity to 99%
			lrc_w = (long)t_com10c * 14256;					// (99/100*14400=14256)
		} 
		else
		{													// Not 0% and Not 99%
			aresult = (BYTE)((long)(INITCAP_TBL[aidx+1] - INITCAP_TBL[aidx])
						* (tminv - INITV_TBL[aidx])
						/ (INITV_TBL[aidx+1] - INITV_TBL[aidx])
						+ INITCAP_TBL[aidx]);
			// RC_w = FCC * aresult / 100 * 14400
			//		= FCC * aresult * 144
			lrc_w = (long)t_com10c * aresult * 144;
		}
	}
	
	Make_RC();												// Calculate RemainingCapacity
	Calc_RSOC();											// Calculate RSOC
	if( t_com0d  < CCP_lvl  ) 								// Less than Capacity correction point voltage
	{
		f_ccp = ON;
	}
}

/*""FUNC COMMENT""**********************************************************
 * module outline	: Impedance Calculation function 
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: static void Calc_IMP(void)
 *--------------------------------------------------------------------------
 * Function			: Impedance Calculation function 
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
void Calc_IMP(void)
{
	WORD	twork;
	
	if ( f_imp_calc == OFF )										// Battery Impedance Calculation is not started? 
	{
		if( f_fd_imp == ON )										// Fully Discharged?
		{
			if ( f_charge == ON )									// Charging ?
			{
				if( t_com0d >= D_RSOC_IMP )							// RSOC IMP is achieved?
				{
					if(( adegree >= D_IMP_TEMPL )
						&& ( adegree <= D_IMP_TEMPH ))				// Check temperature range
					{
						if( labsc >= D_IMP_CURR )					// Curr more than IMP current ?
						{
							acurr_cnt++;
							if( acurr_cnt >= 40 )					// 10s or more elapsed ?
							{
								tcv1 = tminv;						// Record Min cell voltage 
								acellnum = amnidx;					// Record Min cell index
								lc1 = labsc;						// Record current
								afet = FET_D;						// FET control [C=OFF,D=ON]
								AFE_WR(AFE_FCON,afet);				// STOP Charging
								f_imp_calc = ON;					// Set battery impedance calculation flag
							}
						}
					}
				}
				else {
					acurr_cnt = 0;									// Clear time counter for IMP current
				}
			}
			else if(f_discharge == ON)								// If system detects discharge during measurement
			{
				tcv1 = 0;											// Clear Min cell voltage 
				acellnum = 0;										// Clear Min cell index
				lc1 = 0;											// Clear current
				acoff_cnt = 0;										// Clear time counter for CFET OFF
				acurr_cnt = 0;										// Clear time counter for IMP current
				f_imp_calc = OFF;									// Clear impedance calculation flag
				f_fd_imp = OFF;										// Clear fully discharge flag for impedance
			}
		}
	} else {														// Battery Impedance Calculation is in progress
		if(f_discharge == ON)										// If system detects discharge during measurement
		{
			tcv1 = 0;												// Clear Min cell voltage 
			acellnum = 0;											// Clear Min cell index
			lc1 = 0;												// Clear current
			acoff_cnt = 0;											// Clear time counter for CFET OFF
			acurr_cnt = 0;											// Clear time counter for IMP current
			f_imp_calc = OFF;										// Clear impedance calculation flag
			f_fd_imp = OFF;											// Clear fully discharge flag for impedance
		}
		else
		{
			acoff_cnt++;
			if ( acoff_cnt == 4 )									// Wait for 1 sec
			{         
				tcv2 = tvolt[acellnum];								// Measure cell voltage at cell number
				twork = (WORD) ((long)(tcv1-tcv2) * 10000 / lc1);	// Battery Impedance calculation
				t_com47 = twork;
				afet = FET_CD;										// FET control [C=ON,D=ON]
				AFE_WR(AFE_FCON,afet);
				acoff_cnt = 0;										// Clear time counter for CFET OFF
				acurr_cnt = 0;										// Clear time counter for IMP current
				f_imp_calc = OFF;									// Clear impedance calculation flag
				f_fd_imp = OFF;										// Clear fully discharge flag for impedance
			}
		}
	}
}
/*""FUNC COMMENT""**********************************************************
 * module outline	: UsageCheck function
 *--------------------------------------------------------------------------
 * Include			: 
 *--------------------------------------------------------------------------
 * Declaration		: static void UsageCheck(void)
 *--------------------------------------------------------------------------
 * Function			: UsageCheck function 
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
void UsageCheck(void)
{
	if( ausage_cnt >= 120 )						// 2min has passed ?
	{
		ausage_cnt = 0;							// Clear 2min counter		
		// - Total charged cap. -
		if( toldcap < t_com0fc )				// Capacity increasing ?
		{
			tttlchg_w += t_com0fc - toldcap;	// Integrate to the work
			if( tttlchg_w >= 1000 )				// Increased more than 1Ah ?
			{
				tttlchg_w -= 1000;				// Decrease 1Ah from work
				if( t_com48 != 0xFFFF )			// Not overflow ?
				{
					t_com48++;					// Increment TotalChgCap
				}
			}
		}
		toldcap = t_com0fc;						// Save current capacity
		
		// - Total storaged time -
		attlstr_w++;							// Increment work counter
		if( attlstr_w == 30 )					// 60min has passed ?
		{
			attlstr_w = 0;						// Clear work counter
//			t_com49++;							// Increment total storage time
			if(t_com49 != 0xFFFF )				// Not overflow ?
			{
				t_com49++;	
			}
		}

		// - Storage time of Vcell >= TH &/or T>TH -
		if( tmaxv >= NORMAL_CV - D_STR_DLTV )	// MaxV >= Storage Condition HV?
		{
			astrv_w++;							// Increment work counter
			if( astrv_w == 30 )					// 60min has passed ?
			{
				astrv_w = 0;					// Clear work counter
				if( t_com4a != 0xFFFF )			// Not overflow ?
				{
					t_com4a++;					// Increment Storage Time HV
				}
			}
			if( adegree >= D_STR_TEMP )			// Temperature >= Storage Time HT?
			{
				astrvt_w++;						// Increment work counter
				if( astrvt_w == 30 )			// 60min has passed ?
				{
					astrvt_w = 0;				// Clear work counter
					if( t_com4c != 0xFFFF )		// Not overflow ?
					{
						t_com4c++;				// Increment Storage Time HT & HV
					}
				}

				astrt_w++;						// Increment work counter
				if( astrt_w == 30 )				// 60min has passed ?
				{
					astrt_w = 0;				// Clear work counter
					if( t_com4b != 0xFFFF )		// Not overflow ?
					{
						t_com4b++;				// Increment Storage Time HT
					}
				}
			}
		}
		else
		{										// MaxV < Storage Condition HV
			if( adegree >= D_STR_TEMP )			// Temperature >= StrCond.HT ?
			{
				astrt_w++;						// Increment work counter
				if( astrt_w == 30 )				// 60min has passed ?
				{
					astrt_w = 0;				// Clear work counter
					if( t_com4b != 0xFFFF )		// Not overflow ?
					{
						t_com4b++;				// Increment Storage Time HT
					}
				}
			}
		}
	}
}
