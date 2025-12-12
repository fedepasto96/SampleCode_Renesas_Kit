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
* File Name		: define.h
* Version		: 1.00
* Contents		: define functions header file
* Programmer	: Yasuo Usuda
* Note			: 
************************************************************************
* Copyright(C) 2016, 2019 RENESAS ELECTRONICS CORPORATION
************************************************************************
 * History			: 2016.02.15 Ver 1.00
 *					:  New Create
 *					: 
*""FILE COMMENT END""**************************************************/
#ifndef _DEFINE_H
#define _DEFINE_H


// - includes -
#include "iodefine.h"

#define DI      __DI
#define EI      __EI
#define HALT    __halt
#define NOP     __nop
#define STOP    __stop


// - define -
#define ON		1
#define OFF		0
#define HI		1
#define LOW		0

#define NULL	0
#define TRUE	1
#define FALSE	0

#define ABS(a)	((a)>0 ?(a) : -(a))				// absolute value calcuation


// - typedef -
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;

typedef signed char		_SBYTE;
typedef unsigned char	_UBYTE;
typedef signed short	_SWORD;
typedef unsigned short	_UWORD;
typedef signed int		_SINT;
typedef unsigned int	_UINT;
typedef signed long		_SDWORD;
typedef unsigned long	_UDWORD;

typedef char			BOOL;


//typedef void const Func(void);					// for function pointer table


// - smbus related items -
typedef struct									// smbus function data
{
	BYTE	arcv_mod;							// recv mode(00H;00H-08H)
	BYTE	acrem;								// remaining data num
	BYTE __far	*aadr;							// access address

} _ST_SMB;

enum{ 											// - arcv_mod status -
	SADCHK,										// slave address check
	COMCHK,										// Command judgement
	WORD_R_W,									// Read/Write judgement
	RW_SADCHK,									// ReadWord SlaveAddress judgement
	R_WORD,										// Read data send
	W_WORD,										// Write data recv
	RB_SADCHK,									// ReadBlock SlaveAddress judgement
	W_BLK_CHK,									// WriteBlock data num check
	COMDAT_ERR									// error function
};


typedef struct {
	unsigned char	l;
	unsigned char	h;
} _ST_SHORT2CHAR_HL;

typedef union {									// WORD or BYTE[2]
	unsigned short	us;
	unsigned char	uc[sizeof(unsigned short)];
	_ST_SHORT2CHAR_HL hl;
} _SHORT2CHAR;

typedef union {									// DWORD or WORD[2] or BYTE[4]
	unsigned long	ul;
	unsigned short	us[2];
	unsigned char	uc[sizeof(unsigned long)];
} _LONG2CHAR;


typedef struct
{
	unsigned char bit0			:1;	
	unsigned char bit1			:1;
	unsigned char bit2			:1;
	unsigned char bit3			:1;
	unsigned char bit4			:1;
	unsigned char bit5			:1;
	unsigned char bit6			:1;
	unsigned char bit7			:1;
}_STC_BIT;

#define DEF_BIT7(pdata)	((volatile _STC_BIT*)(pdata))->bit7
#define DEF_BIT6(pdata)	((volatile _STC_BIT*)(pdata))->bit6
#define DEF_BIT5(pdata)	((volatile _STC_BIT*)(pdata))->bit5
#define DEF_BIT4(pdata)	((volatile _STC_BIT*)(pdata))->bit4
#define DEF_BIT3(pdata)	((volatile _STC_BIT*)(pdata))->bit3
#define DEF_BIT2(pdata)	((volatile _STC_BIT*)(pdata))->bit2
#define DEF_BIT1(pdata)	((volatile _STC_BIT*)(pdata))->bit1
#define DEF_BIT0(pdata)	((volatile _STC_BIT*)(pdata))->bit0

typedef struct
{
	unsigned char low			:4;	
	unsigned char high			:4;
}_STC_LH;
#define SET_LOW(pdata)	((_STC_LH*)(pdata))->low
#define SET_HIGH(pdata)	((_STC_LH*)(pdata))->high




#endif

