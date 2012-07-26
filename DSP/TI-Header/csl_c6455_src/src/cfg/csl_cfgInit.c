/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */  

/** ============================================================================
 *   @file  csl_cfgInit.c
 *
 *   @path  $(CSLPATH)\src\cfg
 *
 *   @desc  File for functional layer of CSL API CSL_cfgInit()
 *
 */ 
 
/* =============================================================================
 * Revision History
 * ===============
 * 14-Apr-2005 Brn File Created
 * =============================================================================
 */
 
#include <csl_cfg.h>

/** ============================================================================
 *   @n@b CSL_cfgInit
 *
 *   @b Description
 *   @n This is the initialization function for the CFG CSL. The function must be
 *      called before calling any other API from this CSL. This function does 
 *      not modify any registers or check status. It returns status CSL_SOK. 
 *      It has been kept for future use
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
        
        CSL_cfgInit(NULL);

     @endverbatim
 *  ===========================================================================
 */
#pragma CODE_SECTION (CSL_cfgInit, ".text:csl_section:cfg");
CSL_Status CSL_cfgInit(
    CSL_CfgContext * pContext
)
{
    return CSL_SOK;
}

