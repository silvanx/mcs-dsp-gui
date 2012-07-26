/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ========================================================================== 
 */

/** ===========================================================================
 * @file csl_tmrInit.c
 *
 * @brief File for functional layer of CSL API CSL_tmrInit()
 * 
 * @path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrInit() function definition & it's associated
 *       functions 
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 * 1-Sept-2004 HMM File Created.
 * 29-Jul-2005 PSK Updated changes acooriding to revised timer spec. The number
 *                 convention TIM12, TIM34 are changed to TIMLO and TIMHI.   
 * ============================================================================
 */

#include <csl_tmr.h>

/** ============================================================================
 *   @n@b CSL_tmrInit
 *
 *   @b Description
 *   @n This is the initialization function for the Timer CSL.The function 
 *      must be called before calling any other API from this CSL.
 *      This function is idem-potent. Currently, the function just return
 *      status CSL_SOK, without doing anything.
 *
 *   @b Arguments
 *   @verbatim
        pContext    Pointer to module-context. As timer doesn't have any context 
                    based information user is expected to pass NULL.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The CSL for Timer is initialized
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            CSL_tmrInit();
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION(CSL_tmrInit, ".text:csl_section:tmr");
CSL_Status CSL_tmrInit (
    CSL_TmrContext *pContext
)
{
    CSL_Status st = CSL_SOK;
    
    return st;
}

