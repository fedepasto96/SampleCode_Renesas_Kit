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
* File Name		: afe1.h
* Version		: 1.00
* Contents		: afe function header file
* Programmer	: Yasuo Usuda
* Note			: 
************************************************************************
* Copyright(C) 2016, 2019 RENESAS ELECTRONICS CORPORATION
************************************************************************
 * History			: 2016.02.15 Ver 1.00
 *					:  New Create
 *					: 
*""FILE COMMENT END""**************************************************/
#ifndef _AFE_H_1
#define _AFE_H_1 

/************************************WINDOW 1*************************/
#define AFE_OCOCON	AFEREG06					//(F0506)
#define AFE_BUFCON	AFEREG07					//(F0507)
#define AFE_AWDTMON0	AFEREG08				//(F0508)
#define AFE_AWDTMON1	AFEREG09				//(F0509)
#define AFE_AWDTMON2	AFEREG0A				//(F050A)
#define AFE_APCLKCON	AFEREG0B				//(F050B)
#define AFE_HVEG	AFEREG18					//(F0518)
#define AFE_HVDT	AFEREG19					//(F0519)
#define AFE_PONEG	AFEREG1A					//(F051A)
#define AFE_PONMON	AFEREG1B					//(F051B)
#define AFE_DADCON0	AFEREG20					//(F0520)
#define AFE_DADCON1	AFEREG21					//(F0521)
#define AFE_DADCON2	AFEREG22					//(F0522)
#define AFE_DADORL	AFEREG24					//(F0524)
#define AFE_DADORH	AFEREG25					//(F0525)
#define AFE_DADRL	AFEREG26					//(F0526)
#define AFE_DADRH	AFEREG27					//(F0527)
#define AFE_DIMPRL	AFEREG28					//(F0528)
#define AFE_DIMPRH	AFEREG29					//(F0529)
#define AFE_VDET	AFEREG30					//(F0530)
#define AFE_OVUVDET	AFEREG31					//(F0531)
#define AFE_VDCT	AFEREG32					//(F0532)
#define AFE_OVTHL	AFEREG33					//(F0533)
#define AFE_OVTHH	AFEREG34					//(F0534)
#define AFE_UVTHL	AFEREG35					//(F0535)
#define AFE_UVTHH	AFEREG36					//(F0536)
#define AFE_OVSTS0	AFEREG38					//(F0538)
#define AFE_OVSTS1	AFEREG39					//(F0539)
#define AFE_UVSTS0	AFEREG3B					//(F053B)
#define AFE_UVSTS1	AFEREG3C					//(F053C)
#define AFE_VDCLR	AFEREG3E					//(F053E)
#define	AFE_VDIT	AFEREG3F					//(F053F)
#define AFE_OTUTDET	AFEREG42					//(F0542)
#define AFE_OTTHL	AFEREG43					//(F0532)
#define AFE_OTTHH	AFEREG44					//(F0533)
#define AFE_UTTHL	AFEREG45					//(F0534)
#define AFE_UTTHH	AFEREG46					//(F0535)
#define AFE_TDSTS	AFEREG47					//(F0536)
#define AFE_DOCCAL	AFEREG61					//(F0561)
#define AFE_COCCAL	AFEREG63					//(F0563)
#define AFE_DOC3DCON	AFEREG64				//(F0564)
#define AFE_DOC4DCON	AFEREG65				//(F0565)
#define AFE_DOC3DTIME1	AFEREG66				//(F0566)
#define AFE_DOC3DTIME2	AFEREG67				//(F0567)
#define AFE_DOC4DTIME1	AFEREG68				//(F0568)
#define AFE_DOC4DTIME2	AFEREG69				//(F0569)
#define AFE_OCDICON	AFEREG6B					//(F056B)
#define AFE_WUDICON	AFEREG6C					//(F056C)
#define AFE_DWUCAL	AFEREG6E					//(F056E)
#define AFE_DWUACAL	AFEREG6F					//(F056F)
#define AFE_CWUCAL	AFEREG70					//(F0570)
#define AFE_CWUACAL	AFEREG71					//(F0571)
#define AFE_DBPTCAL	AFEREG72					//(F0572)
#define AFE_DBPTACAL	AFEREG73				//(F0573)

									// - (F0506) OCOCON -
#define		AOCO_EN			0b00000001			// AOCO enable
#define		AOCO_DIS		0b00000000			// AOCO disable
#define		ALOCO_EN		0b00000010			// ALOCO enable
#define		ALOCO_DIS		0b00000000			// ALOCO disable

									// - (F0507) BUFCON -
#define		BUFON1_EN		0b00000001			// BUFON1 enable
#define		BUFON1_DIS		0b00000000			// BUFON1 disable
#define		BUFON2_EN		0b00000010			// BUFON2 enable
#define		BUFON2_DIS		0b00000000			// BUFON2 disable
#define		BUFON3_EN		0b00000100			// BUFON3 enable
#define		BUFON3_DIS		0b00000000			// BUFON3 disable
#define		BUFON4_EN		0b00001000			// BUFON4 enable
#define		BUFON4_DIS		0b00000000			// BUFON4 disable
#define		BUFON5_EN		0b00010000			// BUFON5 enable
#define		BUFON5_DIS		0b00000000			// BUFON5 disable
#define		VCPON_EN		0b10000000			// VCPON enable
#define		VCPON_DIS		0b00000000			// VCPON disable

									// - (F050B) APCLKCON -
#define		ADDETLM_EN		0b00000001			// ADDETLM enable
#define		ADDETLM_DIS		0b00000000			// ADDETLM disable
#define		CCLM_EN			0b00000100			// CCLM enable
#define		CCLM_DIS		0b00000000			// CCLM disable
#define		FETLM_EN		0b00001000			// FETLM enable
#define		FETLM_DIS		0b00000000			// FETLM disable
#define		PWMCKDIS_EN		0b00010000			// PWMCKDIS enable
#define		PWMCKDIS_DIS	0b00000000			// PWMCKDIS disable

									// - (F0520) DADCON0 -
#define		DTBST			0b00000001			// Cell voltage auto measurement start for DBPT
#define		DADEN			0b00000010			// Cell voltage auto measurement enable for DBPT
#define		DADOCOFF		0b00000100			// Offset of cell voltage for DBPT

									// - (F0521) DADCON1 -
#define		OFFSET_SEL		0b00000000			// Offset voltage measurement
#define		CELL1_SEL		0b00000001			// Cell 1 voltage measurement
#define		CELL2_SEL		0b00000010			// Cell 2 voltage measurement
#define		CELL3_SEL		0b00000011			// Cell 3 voltage measurement
#define		CELL4_SEL		0b00000100			// Cell 4 voltage measurement
#define		CELL5_SEL		0b00000101			// Cell 5 voltage measurement
#define		CELL6_SEL		0b00000110			// Cell 6 voltage measurement
#define		CELL7_SEL		0b00000111			// Cell 7 voltage measurement
#define		CELL8_SEL		0b00001000			// Cell 8 voltage measurement
#define		CELL9_SEL		0b00001001			// Cell 9 voltage measurement
#define		CELL10_SEL		0b00001010			// Cell 10 voltage measurement
#define		PACK_SEL		0b00001011			// Pack voltage measurement
#define		PON_SEL			0b00001100			// PON pin input voltage measurement
#define		ALLCELL_SEL		0b00001101			// Total cell  voltage measurement

									// - (F0522) DADCON2 -
#define		ADTIME1			0b00000000			// AD time(1msec)
#define		ADTIME2			0b00000001			// AD time(2msec)
#define		ADTIME4			0b00000010			// AD time(4msec)
#define		ADTIME8			0b00000011			// AD time(8msec)
#define		ADWAITTIME1		0b00000000			// AD Wait time(80usec)
#define		ADWAITTIME2		0b00010000			// AD Wait time(120usec)
#define		ADWAITTIME3		0b00100000			// AD Wait time(160usec)
#define		ADWAITTIME4		0b00110000			// AD Wait time(200usec)
#define		ADWAITTIME5		0b01000000			// AD Wait time(250usec)
#define		ADWAITTIME6		0b01010000			// AD Wait time(500usec)
#define		ADWAITTIME7		0b01100000			// AD Wait time(750usec)
#define		ADWAITTIME8		0b01110000			// AD Wait time(1000usec)


									// - (F0530) VDET -
#define		VDET_EN			0b00000001			// Battery cell voltage detection enable
#define		VDET_DIS		0b00000000			// Battery cell voltage detection disable

									// - (F0531) OVUVDET -
#define		OVUVDET_INIT	0b11110001			// Cell voltage detection disable, cell1 voltage measurement
#define		OVUVDET_MSK		0b11110000			// Mask voltage detection setting
#define		UVDET_EN		0b00000000			// Under voltage detection enable
#define		UVDET_DIS		0b10000000			// Under voltage detection disable
#define		OVDET_EN		0b00000000			// Over voltage detection enable
#define		OVDET_DIS		0b01000000			// Over voltage detection disable
#define		UVDF_EN			0b00000000			// Discharge FET control with the under voltage detection enabled
#define		UVDF_DIS		0b00100000			// Discharge FET control with the under voltage detection disabled
#define		OVCF_EN			0b00000000			// Charge FET control with the over voltage detection enabled
#define		OVCF_DIS		0b00010000			// Charge FET control with the over voltage detection disabled

									// - (F0532) VDCT -

#define		VDTIME1		0b00000000			// AD conversion time(1msec)
#define		VDTIME2		0b00000001			// AD conversion time(2msec)
#define		VDTIME4		0b00000010			// AD conversion time(4msec)
#define		VDTIME8		0b00000011			// AD conversion time(8msec)
#define		VDWAITTIME1	0b00000000			// AD Wait time(80usec)
#define		VDWAITTIME2	0b00010000			// AD Wait time(120usec)
#define		VDWAITTIME3	0b00100000			// AD Wait time(160usec)
#define		VDWAITTIME4	0b00110000			// AD Wait time(200usec)
#define		VDWAITTIME5	0b01000000			// AD Wait time(250usec)
#define		VDWAITTIME6	0b01010000			// AD Wait time(500usec)
#define		VDWAITTIME7	0b01100000			// AD Wait time(750usec)
#define		VDWAITTIME8	0b01110000			// AD Wait time(1000usec)

									// - (F0532) VDCLR -
#define		VDCLR_CLR	0b00000001			// Clear voltage detection flag

									// - (F0542) OTUTDET -
#define		OTUTDET_INIT	0b11110000			// temperature detection disable, temperature measurement disable
#define		OTUTDET_MSK		0b11110011			// Mask temperature detection and AN pin setting
#define		AN0TDEN_EN		0b00000001			// Control of over/under temperature detection by the AN0 port voltage enable
#define		AN0TDEN_DIS		0b00000000			// Control of over/under temperature detection by the AN0 port voltage disable
#define		TDCF_EN			0b00000000			// Charge FET control with the over/under temperature detection enabled
#define		TDCF_DIS		0b00010000			// Charge FET control with the over/under temperature detection disabled
#define		TDDF_EN			0b00000000			// Discharge FET control with the over/under temperature detection enabled
#define		TDDF_DIS		0b00100000			// Discharge FET control with the over/under temperature detection disabled
#define		OTDEN_EN		0b00000000			// Over temperature detection enabled
#define		OTDEN_DIS		0b01000000			// Over temperature detection disabled
#define		UTDEN_EN		0b00000000			// Under temperature detection enabled
#define		UTDEN_DIS		0b10000000			// Under temperature detection disabled

									// - (F0561) DOC1CAL -
#define		DOC1CAL_EN		0b10000000			// Discharge over current 1 Calibraton enable
#define		DOC1CAL_DIS		0b00000000			// Discharge over current 1 Calibraton disable

									// - (F0563) COCCAL -
#define		COCCAL_EN		0b10000000			// Charge over current Calibraton enable
#define		COCCAL_DIS		0b00000000			// Charge over current Calibraton disable

									// - (F0564) DOC 3 control-
#define		DOC3EN			0b10000000			// Discharge over current detection enabled
#define		DOC3FETEN		0b01000000			// Discharge FET control enabled
#define		DOC3CMPV		0b00100010			// Discharge over current setting (2.5[mV] * (n-1) + 15[mV] = 100[mV] )(n = 22)

									// - (F0565) DOC 4 control-
#define		DOC4EN			0b10000000			// Discharge over current detection enabled
#define		DOC4FETEN		0b01000000			// Discharge FET control enabled
#define		DOC4CMPV		0b00100010			// Discharge over current setting (2.5[mV] * (n-1) + 15[mV] = 100[mV] )(n = 22)

									// - (F056B) OCDWUICON -
#define		INT_SCEN		0b00000001			// SC interrupt enable
#define		INT_DOC1EN		0b00000010			// DOC1 interrupt enable
#define		INT_DOC2EN		0b00000100			// DOC2 interrupt enable
#define		INT_COCEN		0b00001000			// COC interrupt enable
#define		INT_DOC3EN		0b00010000			// DOC3 interrupt enable
#define		INT_DOC4EN		0b00100000			// DOC4 interrupt enable

#endif
