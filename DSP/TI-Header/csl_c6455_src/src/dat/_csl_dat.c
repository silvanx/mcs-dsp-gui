/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/*  ============================================================================
 *   @file  _csl_dat.c
 *
 *   @path  $(CSLPATH)\src\dst
 *
 *   @desc  This file defines section information
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  16-Jul-2004 Ruchika Kharwar File Created.
 *
 * =============================================================================
 */
 
#include <csl_dat.h>
#include <_csl_dat.h>
#pragma DATA_SECTION (_CSL_datStateStruct, ".bss:csl_section:dat");
CSL_DatStateStruct _CSL_datStateStruct;
