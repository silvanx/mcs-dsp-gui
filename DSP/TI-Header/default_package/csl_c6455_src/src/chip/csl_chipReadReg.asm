;/*   ==========================================================
; *   Copyright (c) Texas Instruments Inc , 2004, 2005
; *
; *   Use of this software is controlled by the terms and conditions found
; *   in the license agreement under which this software has been supplied
; *   priovided
; *   ==========================================================
;*/
;/** @file csl_chipReadReg.asm
; *
; *  @brief CSL chip APIs
; *
; *   @path  $(CSLPATH)\chip\src
; *
; *  Description
; *	- API for reading of the control registers is defined here 
; *  @date 15th Apr, 2004
; */
;/* =============================================================================
; *  Revision History
; *  ===============
; *  07-Mar-2006 ds  Added a dummy code chipReadNone2, 
; *                  before ILC read 
; *                  
; *  19-May-2006 NG  chipReadREP moved from 32 to 15
; *                  Added a dummy code chipReadNone6 before chipReadTSR
; *                  
; * =============================================================================
; */
	; A0 contains the Register to be read 
	.global _CSL_chipReadReg
_CSL_chipReadReg:
    mvk 12, a1
  ||mvkl chipRegTable,b0 ; The offset of the case is attempted to be obtained here
    mvkh chipRegTable,b0
    shl a4,3,a4
    add .s2 a4,b0,b0
	bnop b0,4
	nop
  ||nop
  ||nop
  ||nop
  ||nop
  ||nop
  nop	
  ||nop
  ||nop	
  ||nop
  mvk 1, a4
 
chipRegTable:
chipReadAMR:
	bnop __end, 4
	mvc .s2 amr,b5

chipReadCSR:
	bnop __end, 4
	mvc .s2 csr,b5

chipReadIFR:
chipReadISR:
	bnop __end, 4
	mvc .s2 ifr,b5
	
chipReadICR:
	bnop __end, 4
	mvc .s2 ifr,b5

chipReadIER:
	bnop __end, 4
	mvc .s2 ier,b5

chipReadISTP:
	bnop __end, 4
	mvc .s2 istp,b5
	
chipReadIRP:
	bnop __end, 4
	mvc .s2 irp,b5

chipReadNRP:
chipReadERP:
	bnop __end, 4
	mvc .s2 nrp,b5

chipReadNone0:
	bnop __end, 4
 	mpy 1,a4,a4

chipReadNone1:
	bnop __end, 4
	mpy 1,a4,a4
	
chipReadTSCL:
	bnop __end, 4
	mvc  tscl,b5

chipReadTSCH:
	bnop __end, 4
	mvc  tsch,b5

chipReadNone2:
	bnop __end, 4
 	mpy 1,a4,a4
 		
chipReadILC:
	bnop __end, 4
	mvc .s2 ilc,b5

chipReadRILC:
	bnop __end, 4
	mvc .s2 rilc,b5

chipReadREP:
	bnop __end, 4
	mvc .s2 rep,b5

chipReadPCE1:	
	bnop __end, 4
	mvc .s2 pce1,b5
	
chipReadDNUM:
	bnop __end, 4
	mvc .s2 dnum,b5
	
chipReadNone3:
	bnop __end, 4
	mpy 1,a4,a4
	
chipReadNone4:
	
	bnop __end, 4
	mpy 1,a4,a4
	
chipReadNone5:
	bnop __end, 4
	mpy 1,a4,a4

chipReadSSR:
	bnop __end, 4
	mvc .s2 ssr,b5

chipReadGPLYA:	
	bnop __end, 4
	mvc .s2 gplya,b5

chipReadGPLYB:
	bnop __end, 4	
	mvc .s2 gplyb,b5
	
chipReadGFPGFR:
	bnop __end, 4
	mvc .s2 gfpgfr,b5

chipReadNone6:
	bnop __end, 4
	mpy 1,a4,a4
	
chipReadTSR:	
	bnop __end, 4
	mvc .s2 tsr,b5

chipReadITSR:
	bnop __end, 4	
	mvc .s2 itsr,b5

chipReadNTSR:
	bnop __end, 4
	mvc .s2 ntsr,b5

chipReadEFR:
chipReadECR:
	bnop __end, 4
	mvc .s2 efr,b5
	
chipReadNone7:
	bnop __end, 4
	mpy 1,a4,a4

chipReadIERR:
	bnop __end, 4
	mvc .s2 ierr,b5

__end:
	b b3    
	mv .s1 b5,a4
	nop 4
