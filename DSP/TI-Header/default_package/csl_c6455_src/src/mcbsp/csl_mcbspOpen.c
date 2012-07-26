/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspOpen.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspOpen()
 *
 */

/* =============================================================================
 *  Revision History
 *  ================
 *  15-Feb-2005 NSR      - Updated function and documentation for CSL_mcbspOpen.
 *                       - Removed the include file, csl_resource.h.
 *  15-Nov-2005 ds       - Removed *pMcbspParam = *pMcbspParam  
 *
 * =============================================================================
 */

#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspOpen
 *
 *   @b Description
 *   @n Reserves the specified MCBSP for use. The device can be re-opened 
 *      anytime after it has been normally closed, if so required. 
 *      The MCBSP handle returned by this call is input as an essential argument 
 *      for the rest of the APIs in MCBSP module. 
 *
 *   @b Arguments
 *   @verbatim
            mcbspObj        Mcbsp Module Object pointer
 
            mcbspNum        Instance of Mcbsp 
                            
            pMcbspParam     Parameter for McBSP
 
            status          Status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_McbspHandle
 *   @li                    Valid Mcbsp handle will be returned if status value 
 *                          is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  The MCbsp must be succesfully initialized via CSL_mcbspInit() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  1. The status is returned in the status variable. If status
 *          returned is
 *   @li            CSL_SOK             Valid MCBSP handle is returned
 *   @li            CSL_ESYS_FAIL       The MCBSP instance is invalid
 *   @li            CSL_ESYS_INVPARAMS  The Parameter passed is invalid
 *
 *       2. Mcbsp object structure is populated
 *
 *   @b Modifies
 *   @n  1. The status variable
 *
 *       2. Mcbsp object structure
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle     hMcbsp;
            CSL_McbspObj        mcbspObj;
            CSL_McbspHwSetup    mcbspSetup;
            CSL_Status          status;
            ...
            hMcbsp = CSL_mcbspOpen(&mcbspObj, CSL_MCBSP_0, NULL, &status);
            ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspOpen, ".text:csl_section:mcbsp");
CSL_McbspHandle  CSL_mcbspOpen (
    CSL_McbspObj        *pMcbspObj,
    CSL_InstNum         mcbspNum,
    CSL_McbspParam      *pMcbspParam,
    CSL_Status          *pStatus
)
{
    CSL_Status              status;
    CSL_McbspHandle         hMcbsp = NULL;
    CSL_McbspBaseAddress    baseAddress;

    if (pStatus == NULL) {
        /* do nothing */
    }
    else if (pMcbspObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else{
        status = CSL_mcbspGetBaseAddress(mcbspNum, pMcbspParam, &baseAddress);
    
        if (status == CSL_SOK) {
            pMcbspObj->regs = baseAddress.regs;
            pMcbspObj->perNum = (CSL_InstNum)mcbspNum;
            hMcbsp = (CSL_McbspHandle)pMcbspObj;
        }
        else {
            pMcbspObj->regs = (CSL_McbspRegsOvly)NULL;
            pMcbspObj->perNum = (CSL_InstNum)-1;
            hMcbsp = (CSL_McbspHandle)NULL;
        }
    
        *pStatus = status;
    }

    return hMcbsp;
}


