/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *   @file  csl_bwmngmtGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_bwmngmtGetBaseAddress
 *
 */
/*  ============================================================================
 *  Revision History
 *  ===============
 *  31-Jan-2006 ds  File Created
 *  09-Aug-2006 NG  Added condition to check the invalid parameter
 *  ============================================================================
 */
#include <soc.h>
#include <csl_bwmngmt.h>

/** ============================================================================
 *   @n@b CSL_bwmngmtGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_bwmngmtOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            bwmngmtNum        Specifies the instance of the bwmngmt to be opened.

            pBwmngmtParam     Module specific parameters.

            pBaseAddress      Pointer to baseaddress structure containing base
                              address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK              Successful on getting the base 
 *                                              address of bwmngmt
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
        CSL_Status              status;
        CSL_BwmngmtBaseAddress  baseAddress;

       ...
      status = CSL_bwmngmtGetBaseAddress(CSL_BWMNGMT, NULL, &baseAddress);

     @endverbatim
 * ===========================================================================
 */

#pragma CODE_SECTION (CSL_bwmngmtGetBaseAddress, ".text:csl_section:bwmngmt");
CSL_Status CSL_bwmngmtGetBaseAddress (
    CSL_InstNum               bwmngmtNum,
    CSL_BwmngmtParam          *pBwmngmtParam,
    CSL_BwmngmtBaseAddress    *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (bwmngmtNum) {
            case CSL_BWMNGMT:
                pBaseAddress->regs = (CSL_BwmngmtRegsOvly)CSL_BWMNGMT_0_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_BwmngmtRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

