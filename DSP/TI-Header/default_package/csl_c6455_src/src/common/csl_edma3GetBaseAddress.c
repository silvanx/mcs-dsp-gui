/*  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */
/** ============================================================================
 *   @file  csl_edma3GetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_edma3ccGetModuleBaseAddr
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  01-Jun-2004 Ruchika Kharwar File Created.
 *  09-Aug-2006 NG              Added condition to check the invalid parameter
 *
 * =============================================================================
 */
#include <soc.h>
#include <csl_edma3.h>

/** ============================================================================
 *   @n@b CSL_edma3ccGetModuleBaseAddr
 *
 *   @b Description
 *   @n  This function is used for getting the base-address of the peripheral
 *       instance. This function will be called inside the @ CSL_edma3Open()/
 *       CSL_edma3ChannelOpen() function call. 
 *
 *       Note: This function is open for re-implementing if the user wants to 
 *       modify the base address of the peripheral object to point to a 
 *       different location and there by allow CSL initiated write/reads into 
 *       peripheral MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim      
            edmaNum         Specifies the instance of the edma to be opened.
 
            pParam          Module specific parameters.
 
            pBaseAddress    Pointer to baseaddress structure containing base 
                            address details.
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             Successful on getting the base 
 *                                              address of edma3 
 *   @li                    CSL_ESYS_FAIL       The instance number is invalid.
 *   @li                    CSL_ESYS_INVPARAMS  Invalid parameter 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base Address structure is populated
 *
 *   @b Modifies
 *   @li    The status variable
 *   @li    Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status                   status;
        CSL_Edma3ModuleBaseAddress   baseAddress;

        ...
        status = CSL_edma3ccGetModuleBaseAddr(CSL_EDMA3, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_edma3ccGetModuleBaseAddr, ".text:csl_section:edma");

CSL_Status CSL_edma3ccGetModuleBaseAddr (
    CSL_InstNum                   edmaNum,
    CSL_Edma3ModuleAttr           *pParam,
    CSL_Edma3ModuleBaseAddress    *pBaseAddress 
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (edmaNum) {
            case CSL_EDMA3:
                pBaseAddress->regs = (CSL_Edma3ccRegsOvly)CSL_EDMA3CC_0_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_Edma3ccRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
        }
    }
    return (status);
}

