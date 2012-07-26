/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
 /** ===========================================================================
 *
 *   @file  edmaCommon.h
 *
 *   @path  $(CSLPATH)\example\mcbsp\mcbsp_edma\src
 *
 *   @desc  Header for the Example of MCBSP
 * ============================================================================
 */
 
 /* ===========================================================================
 *  Revision History
 *  ===============
 *  9-Aug-2006 RR File Created.
 *  ============================================================================
 */

#ifndef _EDMACOMMON_H_
#define _EDMACOMMON_H_

#include <csl_edma3.h>
#include <csl_intc.h>
#include <soc.h>
#include <stdio.h>
#include <csl_mcbsp.h>
#include <cslr_dev.h>

#define InvokeHandle(num)       TccHandlerTable[num]()

typedef void (* EdmaTccHandler)(void);

/* Funtion which registers individual event handlers in a table */
void eventEdmaHandler(void *);
void EdmaEventHook(int , EdmaTccHandler);


#endif  /* _EDMACOMMON_H_ */
