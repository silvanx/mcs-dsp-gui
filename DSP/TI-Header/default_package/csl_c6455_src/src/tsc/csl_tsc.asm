*****************************************************************************
*   Copyright (c) Texas Instruments Inc 2002, 2003, 2004,2005
*
*   Use of this software is controlled by the terms and conditions found
*   in the license agreement under which this software has been supplied
*   provided
*****************************************************************************

****************************************************************************
*   @file  csl_tsc.asm
*
*   @path  $(CSLPATH)\src\tsc
*
*   @desc  Assembly file for functional layer of TSC CSL
****************************************************************************

    .global _CSL_tscEnable  
    .sect ".text:cslsys_section:tsc"

_CSL_tscEnable:
        BNOP            B3, 4           ; 
        MVC             A4,     TSCL    ; Initiate CPU Timer by writing to TSCL 

    .global _CSL_tscRead
    .sect ".text:cslsys_section:tsc"
_CSL_tscRead:
         BNOP    B3,     2       ; Branch Return Pointer
        MVC     TSCL,   B0      ; Read TSCL
        MVC     TSCH,   B1      ; Read TSCH
	||  MV      B0, A4
        MV      B1, A5

            