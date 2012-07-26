/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnInit.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnInit ()
 *
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 * =============================================================================
 */
 
#include <csl_pwrdwn.h>

/**
 * ============================================================================
 *  @brief  Initializes the module
 *
 *  CSL_pwrdwnInit(..) initializes the PWRDWN module. 
 *  This function is idempotent -- calling it several times would
 *  have the same effect as calling it the first time.
 *  This function initializes the CSL data structures, and doesn't
 *  touches the hardware.
 * 
 *  @b Arguments
 *  @verbatim
       pContext    Pointer to module-context. As PWRDWN doesn't
                   have any context based information user is expected to pass
                   NULL.
    @endverbatim
 *
 *  <b> Return Value </b>  CSL_Status
 *  @li                        CSL_SOK - Always returns
 * 
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  The CSL for PWRDWN is initialized
 *
 *  @b Modifies
 *  @n  None
 *  
 *  Note: As PWRDWN doesn't have any context based information, the function 
 *        just returns CSL_SOK. User is expected to pass NULL.
 *
 *  @b Example
 *  @verbatim
    ...
    if (CSL_SOK != CSL_pwrdwnInit(NULL)) {
       return;
    }
    @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnInit, ".text:csl_section:pwrdwn");
CSL_Status CSL_pwrdwnInit (
    CSL_PwrdwnContext *pContext  
)
{

    /* If the module is already initialized, then error is
     * returned as init done(CSL_EINITDONE). If the user 
     * needs to force init more than once, then set the
     * global Context pointer to NULL and invoke CSL_pwrdwnInit()
     */ 
    return CSL_SOK;
}

