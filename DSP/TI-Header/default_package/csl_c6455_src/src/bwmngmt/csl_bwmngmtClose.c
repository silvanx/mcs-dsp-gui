/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * priovided
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_bwmngmtClose.c
 *
 *   @path  $(CSLPATH)\src\bwmngmt
 *
 *   @desc  File for functional layer of CSL API CSL_bwmngmtClose()
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  03-Jun-2004 Chad Courtney File Created
 *  11-Apr-2005 Brn Updated the file for doxygen compatibiliy
 *  31-Jan-2006 ds  Added error checking  
 * =============================================================================
 */

#include <csl_bwmngmt.h>

/** ============================================================================
 *   @n@b CSL_bwmngmtClose
 *
 *   @b Description
 *   @n This function closes the specified instance of BWMNGMT.
 *
 *   @b Arguments
 *   @verbatim
         hBwmngmt           Handle to the BWMNGMT instance
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *                          CSL_SOK            - Close successful
 *                          CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_bwmngmtInit() and @a CSL_bwmngmtOpen() must be called 
 *       successfully in that order before @a CSL_bwmngmtClose() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
      CSL_BwmngmtHandle hBwmngmt;
      ...  
      CSL_bwmngmtClose(hBwmngmt);
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_bwmngmtClose, ".text:csl_section:bwmngmt");
CSL_Status CSL_bwmngmtClose (
    CSL_BwmngmtHandle hBwmngmt
)
{
    /* indicate in the CSL global data structure that the peripheral
     * has been unreserved 
     */
    CSL_Status  status = CSL_SOK;
    
    if (hBwmngmt != NULL) {
        hBwmngmt->regs        = (CSL_BwmngmtRegsOvly) NULL;
        hBwmngmt->bwmngmtNum  = (CSL_InstNum) - 1;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }

    return status;
}

