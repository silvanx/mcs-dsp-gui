/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *   @file  csl_pllcGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_pllcGetBaseAddress
 *
 */
/*  ============================================================================
 *  Revision History
 *  ===============
 *  29 Aug 2005 Tej Valecha File Created.
 *  ============================================================================
 */
#include <soc.h>
#include <csl_pllc.h>

/** ============================================================================
 *   @n@b CSL_pllcGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_pllcOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            pllcNum         Specifies the instance of the pllc to be opened.

            pPllcParam      Module specific parameters.

            pBaseAddress    Pointer to base address structure containing base
                            address details.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK             - Successful on getting the base 
 *                                               address of pllc
 *   @li                    CSL_ESYS_FAIL      - The instance number is invalid.
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
         CSL_Status              status;
         CSL_PllcBaseAddress     baseAddress;

         ...

         status = CSL_pllcGetBaseAddress(CSL_PLLC_1, NULL, &baseAddress);
         ...
    @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcGetBaseAddress, ".text:csl_section:pllc");
CSL_Status CSL_pllcGetBaseAddress (
    CSL_InstNum            pllcNum,
    CSL_PllcParam          *pPllcParam,
    CSL_PllcBaseAddress    *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (pllcNum) {
            case CSL_PLLC_1:
                pBaseAddress->regs = (CSL_PllcRegsOvly) CSL_PLLC_1_REGS;
                break;

            case CSL_PLLC_2:
                pBaseAddress->regs = (CSL_PllcRegsOvly) CSL_PLLC_2_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_PllcRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

