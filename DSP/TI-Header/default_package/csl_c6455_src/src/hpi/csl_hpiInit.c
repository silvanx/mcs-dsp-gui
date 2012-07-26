/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiInit.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiInit()
 *
 */
#include <csl_hpi.h>

/** ============================================================================
 *   @n@b CSL_hpiInit
 *
 *   @b Description
 *   @n This is the initialization function for the hpi CSL.  The function 
 *      must be called before calling any other API from this CSL.  This
 *      function is idem-potent.  Currently, the function just return status
 *      CSL_SOK, without doing anything.
 *
 *   @b Arguments
 *   @verbatim
        pContext    Pointer to module-context.  As HPI doesn't have
                    any context based information user is expected to pass NULL.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None 
 *
 *   @b Modifies
 *   @n  None  
 *
 *   @b Example
 *   @verbatim
            CSL_Status status;  
            ...
            status = CSL_hpiInit(NULL);
            ...
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_hpiInit, ".text:csl_section:hpi");
CSL_Status  CSL_hpiInit (
    CSL_HpiContext    *pContext
)
{
    pContext = pContext;
    
    return CSL_SOK;
}

