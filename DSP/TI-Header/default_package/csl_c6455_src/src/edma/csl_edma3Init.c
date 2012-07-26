/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3Init.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API CSL_edma3Init ()
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  29-May-2004 Ruchika Kharwar File Created.
 *
 * =============================================================================
 */

#include <csl_edma3.h>

/** ============================================================================
 *   @n@b CSL_edma3Init
 *
 *   @b Description
 *   @n This is the initialization function for the edma CSL. The function must 
 *      be called before calling any other API from this CSL.This function is 
 *      idem-potent. Currently, the function just return status CSL_SOK, 
 *      without doing anything.
 *
 *   @b Arguments
     @verbatim
            pContext           Pointer to module-context. As edma doesn't have
                               any context based information user is expected 
                               to pass NULL.
    @endverbatim
 *
 *   <b> Return Value </b>      CSL_Status
 *   @li                        CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The CSL for EDMA is initialized 
 *
 *   @b Modifies
 *   @n  None  
 *
 *   @b Example
 *   @verbatim
            ...
            if (CSL_edma3Init(NULL) != CSL_SOK) {
                exit;
            }
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3Init, ".text:csl_section:edma3");
CSL_Status CSL_edma3Init (
        CSL_Edma3Context  *pContext
)
{
    return CSL_SOK;
}

