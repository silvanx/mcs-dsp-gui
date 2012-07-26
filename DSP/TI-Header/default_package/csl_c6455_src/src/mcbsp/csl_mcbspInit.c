/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspInit.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspInit()
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
 *   @n@b CSL_mcbspInit
 *
 *   @b Description
 *   @n This function is idempotent i.e. calling it many times is same as
 *      calling it once. This function is only for book-keeping purpose
 *      and it doesn't touch the hardware (read/write registers) in any manner.
 *
 *   @b Arguments
     @verbatim
            pContext           Pointer to module-context. As mcbsp doesn't have
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
 *   @b Modifies
 *   @n  None  
 *
 *   @b Example
 *   @verbatim
            ...
            CSL_mcbspInit();
            ...
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspInit, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspInit (
    CSL_McbspContext    *pContext
)
{
    return CSL_SOK;
}
