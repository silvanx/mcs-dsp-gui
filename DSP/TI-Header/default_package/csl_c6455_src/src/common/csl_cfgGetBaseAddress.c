/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *   @file  csl_cfgGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_cfgGetBaseAddress
 *
 */
/*  ============================================================================
 *  Revision History
 *  ===============
 *  31-Jan-2006 ds  File Created.
 *  09-Aug-2006 NG  Added condition to check the invalid parameter
 *
 *  ============================================================================
 */
#include <soc.h>
#include <csl_cfg.h>

/** ============================================================================
 *   @n@b CSL_cfgGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_cfgOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            cfgNum        Specifies the instance of the CFG to be opened.

            pCfgParam     Module specific parameters.

            pBaseAddress  Pointer to baseaddress structure containing base
                          address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK              Successful on getting the base 
 *                                              address of CFG
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
        CSL_CfgBaseAddress  baseAddress;

       ...
      status = CSL_cfgGetBaseAddress(CSL_MEMPROT_CONFIG, NULL, &baseAddress);

     @endverbatim
 * ===========================================================================
 */

#pragma CODE_SECTION (CSL_cfgGetBaseAddress, ".text:csl_section:cfg");
CSL_Status CSL_cfgGetBaseAddress (
    CSL_InstNum             cfgNum,
    CSL_CfgParam            *pCfgParam,
    CSL_CfgBaseAddress      *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (cfgNum) {
            case CSL_MEMPROT_CONFIG:
                pBaseAddress->regs = (CSL_CfgRegsOvly)CSL_MEMPROT_CONFIG_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_CfgRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

