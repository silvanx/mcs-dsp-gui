/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *   @file  csl_mcbspGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_mcbspGetBaseAddress
 *
 */
/*  ============================================================================
 *  Revision History
 *  ===============
 *  15-Feb-2005 BRN File Created.
 *  09-Aug-2006 NG  Added condition to check the invalid parameter
 *
 *  ============================================================================
 */
#include <soc.h>
#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_mcbspOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            mcbspNum        Specifies the instance of the MCBSP to be opened.

            pMcbspParam     Module specific parameters.

            pBaseAddress  Pointer to baseaddress structure containing base
                          address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK              Successful on getting the base 
 *                                              address of mcbsp
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
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status          status;
        CSL_McbspBaseAddress  baseAddress;

       ...
      status = CSL_mcbspGetBaseAddress(CSL_MCBSP_0, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */

#pragma CODE_SECTION (CSL_mcbspGetBaseAddress, ".text:csl_section:mcbsp");
CSL_Status
    CSL_mcbspGetBaseAddress (
        CSL_InstNum             mcbspNum,
        CSL_McbspParam          *pMcbspParam,
        CSL_McbspBaseAddress    *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (mcbspNum) {
            case CSL_MCBSP_0:
                pBaseAddress->regs = (CSL_McbspRegsOvly)CSL_MCBSP_0_REGS;
                break;

            case CSL_MCBSP_1:
                pBaseAddress->regs = (CSL_McbspRegsOvly)CSL_MCBSP_1_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_McbspRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

