/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_memprotInit.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotInit ()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 *
 *  16-Nov-2005 ds   Updated the documentation
 * =============================================================================
 */
 
#include <csl_memprot.h>

/** ===========================================================================
 *   @n@b CSL_memprotInit
 *
 *   @b Description
 *   @n This is the initialization function for the MEMPROT. This function is
 *      idempotent in that calling it many times is same as calling it once.
 *      This function initializes the CSL data structures, and doesn't affect
 *      the H/W. The function must be called before calling any other API from 
 *      this CSL.
 *
 *   @b Arguments
     @verbatim
            pContext   Context information for the instance. Should be NULL
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *       This function should be called before using any of the CSL APIs
 *       in the Memory Protection module.
 *       
 *       Note: As Memory Protection doesn't have any context based information, 
 *       the function  just returns CSL_SOK. User is expected to pass NULL.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
      ...
         CSL_memprotInit();
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_memprotInit, ".text:csl_section:memprot"); 
CSL_Status CSL_memprotInit (
    CSL_MemprotContext *pContext  
)
{

    /* If the module is already initialized, then error is
     * returned as init done(CSL_EINITDONE). If the user 
     * needs to force init more than once, then set the
     * global Context pointer to NULL and invoke CSL_memprotInit()
     */ 
     
    return CSL_SOK;
}

