/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *   @file  csl_hpiGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_hpiGetBaseAddress
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  28-Jan-2005 asr author File Created.
 * =============================================================================
 */
#include <soc.h>
#include <csl_hpi.h>

/** ============================================================================
 *   @n@b CSL_hpiGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_hpiOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            hpiNum      	Specifies the instance of the hpi to be opened

            pHpiParam   	Module specific parameters.

            pBaseAddress    Pointer to base address structure containing base
                            address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK              Successful on getting the base 
 *                                              address of hpi
 *   @li                    CSL_ESYS_FAIL       The instance number is invalid.
 *   @li                    CSL_ESYS_INVPARAMS  Invalid parameter 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status              status;
        CSL_HpiBaseAddress  baseAddress;

        ...

        status = CSL_hpiGetBaseAddress(CSL_HPI, NULL,
                                       &baseAddress);
        ...

    @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_hpiGetBaseAddress, ".text:csl_section:hpi");
CSL_Status CSL_hpiGetBaseAddress (
    CSL_InstNum  		  hpiNum,
    CSL_HpiParam          *pHpiParam,
    CSL_HpiBaseAddress    *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (hpiNum) {
            case CSL_HPI:
                pBaseAddress->regs = (CSL_HpiRegsOvly)CSL_HPI_0_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_HpiRegsOvly)NULL;
                pHpiParam = pHpiParam;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

