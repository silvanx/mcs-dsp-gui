/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/*
 *  @file  _csl_intcResourceAlloc.c
 *
 *  @brief   File for functional layer of CSL API for intc resource allocation
 *
 *  PATH  $(CSLPATH)\src\intc
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Jun-2004 Ruchika Kharwar File Created
 *
 * =============================================================================
 */

#include <csl_intc.h>
#include <_csl_intc.h>

#pragma DATA_SECTION (_CSL_intcAllocMask, ".bss:csl_section:intc");
CSL_BitMask32*   _CSL_intcAllocMask = NULL;

#pragma DATA_SECTION (_CSL_intcCpuIntrTable, ".bss:csl_section:intc");
CSL_IntcVect _CSL_intcCpuIntrTable;

#pragma DATA_SECTION (_CSL_intcEventOffsetMap, ".bss:csl_section:intc");
Int8 *_CSL_intcEventOffsetMap = NULL;

#pragma DATA_SECTION (_CSL_intcNumEvents, ".bss:csl_section:intc");
Uint16 _CSL_intcNumEvents;

#pragma DATA_SECTION (_CSL_intcEventHandlerRecord, ".bss:csl_section:intc");
CSL_IntcEventHandlerRecord* _CSL_intcEventHandlerRecord;
