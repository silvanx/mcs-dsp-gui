/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                             
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_cfgClose.c
 *
 *   @path  $(CSLPATH)\src\cfg
 *
 *   @desc  File for functional layer of CSL API CSL_cfgClose()
 *
 */

/* ============================================================================
 * Revision History
 * ===============
 *  11-Apr-2005 Brn updated the file for doxygen compatibiliy
 *  31-Jan-2006 ds  Added error checking
 * ============================================================================
 */

#include <csl_cfg.h>

/** ============================================================================
 *   @n@b CSL_cfgClose
 *
 *   @b Description
 *   @n This function closes the specified instance of CFG.
 *
 *   @b Arguments
 *   @verbatim
            hCfg          Handle to the CFG instance
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status 
 *   @li                    CSL_SOK            - close successful
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_cfgInit() and @a CSL_cfgOpen() must be called successfully
 *       in that order before @a CSL_cfgClose() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  The cfg CSL APIs can not be called until the cfg CSL is reopened 
 *       again using CSL_cfgOpen()
 *       
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_cfgHandle  hCfg;
            ...
            CSL_cfgClose(hCfg);
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_cfgClose, ".text:csl_section:cfg");
CSL_Status CSL_cfgClose (
    CSL_CfgHandle   hCfg
)
{
    /* indicate in the CSL global data structure that the peripheral
     * has been unreserved
     */
    
    CSL_Status  status = CSL_SOK;
    
    if (hCfg != NULL) {
        hCfg->regs    = (CSL_CfgRegsOvly) NULL;
        hCfg->cfgNum  = (CSL_InstNum) - 1;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }

    return status;
       
}

