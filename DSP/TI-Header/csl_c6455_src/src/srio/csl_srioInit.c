/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ========================================================================== 
 */

/** ===========================================================================
 * @file csl_srioInit.c
 *
 * @brief File for functional layer of CSL API CSL_srioInit()
 * 
 * @path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioInit() function definition and it's associated
 *       functions 
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 * 20-Aug-2005 PSK File Created.
 * ============================================================================
 */

#include <csl_srio.h>

/** ============================================================================
 *   @n@b CSL_srioInit
 *
 *   @b Description
 *   @n This is the initialization function for the SRIO CSL.
 *      The function must be called before calling any other API from this CSL.
 *      This function is idem-potent. Currently, the function just return
 *      status CSL_SOK, without doing anything.
 *
 *   @b Arguments
 *   @verbatim
        pContext    Pointer to module-context. As SRIO doesn't
                    have any context based information user is expected to pass
                    NULL.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The CSL for SRIO is initialized
 *
 *   @b Modifies    
 *   @n  None
 *
 *   @b Example
 *   @verbatim
            CSL_Status status;
            ...
            status = CSL_srioInit(NULL);
            ...
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_srioInit, ".text:csl_section:srio");
CSL_Status CSL_srioInit (
    CSL_SrioContext    *pContext
)
{
    return (CSL_SOK);
}

