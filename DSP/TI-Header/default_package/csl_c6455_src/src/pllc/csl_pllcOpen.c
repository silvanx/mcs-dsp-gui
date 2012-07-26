/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_pllcOpen.c
 *
 *  @brief File for functional layer of CSL API @a CSL_pllcOpen()
 *
 *  Path: \(CSLPATH)\src\pllc
 *
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  10-Feb-2004 kpn CSL3X Upgradation.
 *  25-Aug-2005 Tej Modified for c64xx support.
 *  ============================================================================
 */

#include <csl_pllc.h>

/** ============================================================================
 *   @n@b CSL_pllcOpen
 *
 *   @b Description
 *   @n This function returns the handle to the PLLC
 *      instance. This handle is passed to all other CSL APIs.
 *
 *   @b Arguments
 *   @verbatim
            pPllcObj    Pointer to pllc object.

            pllcNum     Instance of pllc CSL to be opened.

            pPllcParam  Module specific parameters.

            status      Status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_PllcHandle
 *   @n                     Valid pllc handle will be returned if
 *                          status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK            - Valid pllc handle is returned
 *   @li            CSL_ESYS_FAIL      - The pllc instance is invalid
 *   @li            CSL_ESYS_INVPARAMS - Invalid parameter
 *   @n   2.    PLLC object structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. PLLC object structure
 *
 *   @b Example
 *   @verbatim
            CSL_status           status;
            CSL_PllcObj          pllcObj;
            CSL_PllcHandle       hPllc;
            ...

            hPllc = CSL_pllcOpen(&pllcObj, CSL_PLLC_1, NULL, &status);
            ...

    @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcOpen, ".text:csl_section:pllc");
CSL_PllcHandle CSL_pllcOpen (
    CSL_PllcObj               *pPllcObj,
    CSL_InstNum                pllcNum,
    CSL_PllcParam             *pPllcParam,
    CSL_Status                *pStatus
)
{
    CSL_Status                status;
    CSL_PllcHandle            hPllc = NULL;
    CSL_PllcBaseAddress       baseAddress;

    if (pStatus == NULL) {
        /* do nothing */
    }
    else if (pPllcObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        status = CSL_pllcGetBaseAddress (pllcNum, pPllcParam, &baseAddress);
    
        if (status == CSL_SOK) {
            pPllcObj->regs     = baseAddress.regs;
            pPllcObj->pllcNum  = (CSL_InstNum) pllcNum;
            hPllc              = (CSL_PllcHandle) pPllcObj;
        }
        else {
            pPllcObj->regs     = (CSL_PllcRegsOvly)NULL;
            pPllcObj->pllcNum  = (CSL_InstNum)-1;
        }
    
        *pStatus = status;
    }

    return hPllc;
}

