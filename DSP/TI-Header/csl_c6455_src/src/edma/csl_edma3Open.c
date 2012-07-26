/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3Open.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API CSL_edma3Open ()
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
 *   @n@b CSL_edma3Open
 *
 *   @b Description
 *   @n This function returns the handle to the edma instance. This handle is 
 *      passed to all other CSL APIs.
 *
 *   @b Arguments
 *   @verbatim
            pEdmaObj         EDMA Module Object pointer
 
            edmaNum          Instance of EDMA 
                            
            pAttr            EDMA Attribute pointer
 
            pStatus          Status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Edma3Handle
 *   @li                    Valid Edma handle will be returned if status value 
 *                          is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  The EDMA must be succesfully initialized via CSL_edma3Init() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  1. The status is returned in the status variable. If status
 *          returned is
 *   @li            CSL_SOK             Valid EDMA handle is returned
 *   @li            CSL_ESYS_FAIL       The EDMA instance is invalid
 *   @li            CSL_ESYS_INVPARAMS  The Parameter passed is invalid
 *
 *       2. Edma object structure is populated
 *
 *   @b Modifies
 *   @n  1. The status variable
 *
 *       2. Edma object structure
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle     hModule;
            CSL_Edma3Obj        edmaObj;
            CSL_Status          status;
            
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
    @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3Open, ".text:csl_section:edma3");
CSL_Edma3Handle  CSL_edma3Open (
    CSL_Edma3Obj             *pEdmaObj,
    CSL_InstNum              edmaNum,
    CSL_Edma3ModuleAttr      *pAttr,
    CSL_Status               *pStatus
)
{
    CSL_Edma3ModuleBaseAddress    baseAddress;
    CSL_Edma3Handle               hEdma = (CSL_Edma3Handle)NULL;
    
    if (pStatus == NULL) {
        /* Do nothing : Module handle already initialised to NULL */
    }
    else if (pEdmaObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        *pStatus = CSL_edma3ccGetModuleBaseAddr(edmaNum, pAttr, &baseAddress);
        if (*pStatus == CSL_SOK) {
            pEdmaObj->regs = baseAddress.regs;
            pEdmaObj->instNum = (CSL_InstNum)edmaNum;
            hEdma = (CSL_Edma3Handle)pEdmaObj;
        } 
        else {
            pEdmaObj->regs = (CSL_Edma3ccRegsOvly)NULL;
            pEdmaObj->instNum = (CSL_InstNum) -1;
        }
    }

    return (hEdma);
}

