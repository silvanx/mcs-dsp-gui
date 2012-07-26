/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================ 
 */

/** =========================================================================== 
 * @file csl_tmrClose.c
 *
 * @brief File for functional layer of CSL API CSL_tmrClose() 
 * 
 * @path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrClose() function definition & it's associated
 *       functions
 * ============================================================================      
 */

/* ============================================================================
 * Revision History
 * ===============
 * 1-Sept-2004 HMM File Created.
 * ============================================================================
 */

#include <csl_tmr.h>

/** ============================================================================
 *   @n@b CSL_tmrClose.c
 *
 *   @b Description
 *   @n This function marks that CSL for the Timer instance is closed.
 *      CSL for the timer instance need to be reopened before using any
 *      timer CSL API.
 *
 *   @b Arguments
 *   @verbatim
            hTmr         Pointer to the object that holds reference to the 
                         instance of TIMER requested after the call 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Timer is closed
 *                                               successfully
 *
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  1. The Timer CSL APIs can not be called until the Timer CSL is 
 *          reopened again using CSL_tmrOpen()
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            CSL_tmrClose(hTmr);
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_tmrClose, ".text:csl_section:tmr");
CSL_Status CSL_tmrClose (
    CSL_TmrHandle hTmr
)
{
    CSL_Status st;

    if (hTmr != NULL) {
        hTmr->regs = (CSL_TmrRegsOvly)NULL;
        hTmr->perNum = (CSL_InstNum)-1;
      
        st = CSL_SOK;
    } 
    else {
        st = CSL_ESYS_BADHANDLE;
    }

    return st;
}

