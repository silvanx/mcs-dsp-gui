/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspClose.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspClose()
 *
 */

/* =============================================================================
 * Revision History
 * ================
 *  June 29,2004 Pratheesh Gangadhar - Created
 * 
 * =============================================================================
 */
  
#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspClose
 *
 *   @b Description
 *   @n Unreserves the MCBSP identified by the handle passed.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status 
 *   @li                    CSL_SOK            - close successful
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspClose() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  The mcbsp CSL APIs can not be called until the mcbsp CSL is reopened 
 *       again using CSL_mcbspOpen()
 *       
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_mcbspHandle  hMcbsp;
            ...
            CSL_mcbspClose(hMcbsp);
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspClose, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspClose (
    CSL_McbspHandle    hMcbsp
)
{
    CSL_Status  status;
    
    if (hMcbsp != NULL) {
        hMcbsp->regs    = (CSL_McbspRegsOvly) NULL;
        hMcbsp->perNum  = (CSL_InstNum) - 1;
        status          = CSL_SOK;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }

    return status;
}
