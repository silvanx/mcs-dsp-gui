/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ============================================================================
 */
/** ============================================================================
 *   @file  csl_pwrdwnGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_pwrdwnGetBaseAddress
 *
 *   Note: This function is open for re-implementing if the user wants to modify
 *    the base address of the peripheral object to point to a different location
 *    there by allow CSL initiated write/reads into peripheral MMR's go to an 
 *    alternate location. Please refer documentation for more details. 
 *
 *   @author Ruchika Kharwar.
 */
/* =============================================================================
 *  Revision History
 *  ================
 *  22-sep-2005 PSK updated according to code review comments.
 *  09-Aug-2006 NG  Added condition to check the invalid parameter
 * =============================================================================
 */
#include <soc.h>
#include <csl_pwrdwn.h>

/** ===========================================================================
 *   @n@b CSL_pwrdwnGetBaseAddress
 *
 *   @b Description
 *   @n  This function gets the base address of the given pwrdwn
 *       instance.
 *
 *   @b Arguments
 *   @verbatim
            pwrdwnNum        Peripheral instance numberd

            pPwrdwnParam     Module specific parameters

            pBaseAddress     Pointer to base address structure containing base
                             address details
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             Successful on getting the base 
 *                                              address of pwrdwn
 *   @li                    CSL_ESYS_FAIL       pwrdwn instance is not
 *                                              available.
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
 * @b Example:
   @verbatim

    CSL_PwrdwnHandle       hPwrdwn;
    CSL_PwrdwnBaseAddress  baseAddress;
    CSL_PwrdwnParam        params; 

    CSL_pwrdwnGetBaseAddress(CSL_PWRDWN, &params, &baseAddress) ;

   @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnGetBaseAddress, ".text:csl_section:pwrdwn");
CSL_Status CSL_pwrdwnGetBaseAddress (
    CSL_InstNum              pwrdwnNum,
    CSL_PwrdwnParam          *pPwrdwnParam,
    CSL_PwrdwnBaseAddress    *pBaseAddress 
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (pwrdwnNum) {
            case CSL_PWRDWN:
                pBaseAddress->regs = (CSL_PdcRegsOvly)CSL_PWRDWN_PDC_REGS;
                pBaseAddress->l2pwrdwnRegs = 
                                     (CSL_L2pwrdwnRegsOvly)CSL_PWRDWN_L2_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_PdcRegsOvly)NULL;
                pBaseAddress->l2pwrdwnRegs = (CSL_L2pwrdwnRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
        }
    }
    return (status);
}

