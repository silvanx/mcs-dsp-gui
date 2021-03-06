; * ============================================================================
; * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006, 2007
; *
; * Use of this software is controlled by the terms and conditions found
; * in the license agreement under which this software has been supplied.
; * ============================================================================

; * ============================================================================
; * @brief Interrupt vector file for TMS320C6454 . 
; *
; * @file  intvecs.asm
; *
; * @verbatim
;   This file contains interrupt service table.  The CPU interrupt 4 vector 
;   contains interrupt4 function. 
;   @endverbatim
; *
; * ============================================================================

; Global symbols defined here and exported out of this file
   .global _intcVectorTable
   .global _c_int00
   .global _interrupt4        
   .global _interrupt5
   .global _interrupt6
   .global _interrupt7
   .global _interrupt8


; This is a macro that instantiates one entry in the interrupt service table.
VEC_ENTRY .macro addr
    STW   B0,*--B15
    MVKL  addr,B0
    MVKH  addr,B0
    B     B0
    LDW   *B15++,B0
    NOP   2
    NOP   
    NOP   
   .endm

; This is a dummy interrupt service routine used to initialize the IST.
_vec_dummy:
  B    B3
  NOP  5

; This is the actual interrupt service table (IST). 
 .sect ".intvecs"
 .align 1024

_intcVectorTable:
_vector0:   VEC_ENTRY _c_int00      ;RESET
_vector1:   VEC_ENTRY _vec_dummy    ;NMI
_vector2:   VEC_ENTRY _vec_dummy    ;RSVD
_vector3:   VEC_ENTRY _vec_dummy    ;RSVD
_vector4:   VEC_ENTRY _vec_dummy 	;not used
_vector5:   VEC_ENTRY _vec_dummy	;not used
_vector6:   VEC_ENTRY _interrupt6	;Interrupt6 ISR
_vector7:   VEC_ENTRY _vec_dummy	;not used
_vector8:   VEC_ENTRY _interrupt8	;Interrupt8 ISR
_vector9:   VEC_ENTRY _vec_dummy
_vector10:  VEC_ENTRY _vec_dummy
_vector11:  VEC_ENTRY _vec_dummy
_vector12:  VEC_ENTRY _vec_dummy
_vector13:  VEC_ENTRY _vec_dummy
_vector14:  VEC_ENTRY _vec_dummy
_vector15:  VEC_ENTRY _vec_dummy

;* =============================================================================
 

