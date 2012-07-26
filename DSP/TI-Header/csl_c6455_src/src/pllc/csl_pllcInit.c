/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_pllcInit.c
 *
 *  @brief File for functional layer of CSL API @a CSL_pllcInit()
 *
 *  Path: \(CSLPATH)\src\pllc
 *
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  10-Feb-2004 kpn CSL3X Upgradation.
 *  ============================================================================
 */

#include <csl_pllc.h>

/** ============================================================================
 *   @n@b CSL_pllcInit
 *
 *   @b Description
 *   @n This is the initialization function for the pllc CSL. The function
 *      must be called before calling any other API from this CSL. This
 *      function is idem-potent. Currently, the function just return status
 *      CSL_SOK, without doing anything.
 *
 *   @b Arguments
 *   @verbatim
        pContext    Pointer to module-context. As pllc doesn't have
                    any context based information user is expected to pass NULL.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                        CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_pllcInit(NULL);
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcInit, ".text:csl_section:pllc");
CSL_Status CSL_pllcInit (
    CSL_PllcContext       *pContext
)
{
    pContext = pContext;
    return CSL_SOK;
}

