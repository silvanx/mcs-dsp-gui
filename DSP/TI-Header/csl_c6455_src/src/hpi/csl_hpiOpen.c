/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiOpen.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiOpen()
 *
 */
#include <csl_hpi.h>

/** ============================================================================
 *   @n@b CSL_hpiOpen
 *
 *   @b Description
 *   @n This function returns the handle to the HPI controller
 *      instance. This handle is passed to all other CSL APIs.
 *
 *   @b Arguments
 *   @verbatim
            hpiObj        Pointer to the object that holds reference to the
                           instance of HPI requested after the call.
 
            hpiNum        Instance of HPI to which a handle is requested. 
                           There is only one instance of the hpi available.
                           So, the value for this parameter will be 
                           CSL_HPI always.
 
            pHpiParam  Module specific parameters.
 
            status         Status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_HpiHandle
 *   @n                     Valid HPI handle will be returned if
 *                          status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK            - Valid HPI handle is returned
 *   @li            CSL_ESYS_FAIL      - The HPI instance is invalid
 *   @li            CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *        2.    HPI object structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. HPI object structure
 *
 *   @b Example
 *   @verbatim
            CSL_status          status;
            CSL_HpiObj         hpiObj;
            CSL_HpiHandle      hHpi;

            ...
                
            hHpi = CSL_hpiOpen(&hpiObj, CSL_HPI, NULL, &status);
            
            ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_hpiOpen, ".text:csl_section:hpi");
CSL_HpiHandle  CSL_hpiOpen (
    CSL_HpiObj      *pHpiObj,   
    CSL_InstNum     hpiNum,     
    CSL_HpiParam    *pHpiParam, 
    CSL_Status      *pStatus
)
{   
    CSL_HpiHandle         hHpi = (CSL_HpiHandle)NULL;
    CSL_HpiBaseAddress    baseAddress;

    if (pStatus == NULL) {
        /* do nothing : module handle is already initialized to NULL */
    }
    else if (pHpiObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        *pStatus = CSL_hpiGetBaseAddress (hpiNum, pHpiParam, &baseAddress);
        if (*pStatus == CSL_SOK) {
            pHpiObj->regs = baseAddress.regs;
            pHpiObj->hpiNum = (CSL_InstNum) hpiNum;
            hHpi = (CSL_HpiHandle) pHpiObj;
        } 
        else {
            pHpiObj->regs = (CSL_HpiRegsOvly)NULL;
            pHpiObj->hpiNum = (CSL_InstNum)-1;
        }
    }
    return (hHpi);
}

