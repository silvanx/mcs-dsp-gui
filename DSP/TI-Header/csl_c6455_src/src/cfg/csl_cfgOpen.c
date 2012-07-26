/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_cfgOpen.c
 *
 *   @path  $(CSLPATH)\src\cfg
 *
 *   @desc  File for functional layer of CSL API CSL_cfgOpen()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  11-Apr-2005 Brn Updated the file for doxygen compatibiliy
 *
 *  16-Nov-2005 ds Updated the documentation
 *
 *  31-Jan-2006 ds Supported to use the CSL_cfgGetBaseAddress() API
 * =============================================================================
 */

#include <csl_cfg.h>

/** ===========================================================================
 *   @n@b CSL_cfgOpen
 *
 *   @b Description
 *   @n  This function populates the peripheral data object for the instance
 *       and returns a handle to the instance.
 *       The open call sets up the data structures for the particular instance
 *       of CFG device. The device can be re-opened anytime after it has
 *       been normally closed, if so required. The handle returned by this call 
 *       is input as an essential argument for rest of the APIs described for
 *       this module. 
 *
 *   @b Arguments
 *   @verbatim
        pCfgObj         Pointer to the CFG instance object

        cfgNum          Instance of the CFG to be opened.

        pCfgParam       Pointer to module specific parameters

        pStatus         pointer for returning status of the function call
     @endverbatim
 *
 *   <b> Return Value </b> CSL_CfgHandle
 *   @n  Valid CFG instance handle will be returned if status value is
 *       equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_cfgInit() has to be called before this function get called
 *
 *   <b> Post Condition </b>
 *   @n  CSL_cfgInit has to be called before calling this function.
 *       Post Condition 
 *       1. The status is returned in the status variable. If status returned is 
 *              - CSL_SOK       - Valid CFG handle is returned. 
 *              - CSL_ESYS_FAIL - The CFG instance is invalid. 
 *              - CSL_ESYS_INVPARAMS - The Obj structure passed is invalid
 *       2. CFG object structure is populated.
 *
 *
 *   @b Modifies
 *   @n  1. The status variable 
 *       2. CFG object structure 
 *
 *   @b Example
 *   @verbatim
          CSL_status        status;
          CSL_CfgObj        cfgObj;
          CSL_CfgHandle     hCfg;
          ...
          hCfg = CSL_cfgOpen (&cfgObj, CSL_MEMPROT_CONFIG, NULL, &status);
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_cfgOpen, ".text:csl_section:cfg");
CSL_CfgHandle CSL_cfgOpen (
    CSL_CfgObj      *pCfgObj,
    CSL_InstNum      cfgNum,
    CSL_CfgParam    *pCfgParam,
    CSL_Status      *pStatus
)
{
    CSL_CfgHandle         hCfg = (CSL_CfgHandle)NULL;
    CSL_CfgBaseAddress    baseAddress;
    
    if (pStatus == NULL) {
        /* do nothing : already the module is initialized to NULL */    
    }
    
    else if (pCfgObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    
    else {
        *pStatus = CSL_cfgGetBaseAddress(cfgNum, pCfgParam, &baseAddress);

        if (*pStatus == CSL_SOK) {
            pCfgObj->regs = baseAddress.regs;
            pCfgObj->cfgNum = (CSL_InstNum)cfgNum;
            hCfg = (CSL_CfgHandle)pCfgObj;
        }
        else {
            pCfgObj->regs = (CSL_CfgRegsOvly)NULL;
            pCfgObj->cfgNum = (CSL_InstNum)-1;
        }
    }
    return (hCfg);
}
