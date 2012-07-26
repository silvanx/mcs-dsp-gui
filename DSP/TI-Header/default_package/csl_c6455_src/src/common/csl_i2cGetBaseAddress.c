/*  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */
/** ============================================================================
 *   @file  csl_i2cGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_i2cGetBaseAddress
 *
 *  @date 28th May, 2004
 *    @author Santosh Narayanan.
 */
/*  ============================================================================
 *  Revision History
 *  ===============
 *  11-oct-2004 Hs updated according to code review comments.
 *  31-aug-2004 Hs File Created.
 *
 *  ============================================================================
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_i2cOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            i2cNum          Specifies the instance of I2C to be opened.

            pI2cParam       Module specific parameters.

            pBaseAddress    Pointer to baseaddress structure containing base
                            address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK              Successful on getting the base 
 *                                              address of i2c
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
        CSL_I2cBaseAddress  baseAddress;

       ...
      status = CSL_i2cGetBaseAddress(CSL_I2C, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cGetBaseAddress, ".text:csl_section:i2c");
CSL_Status CSL_i2cGetBaseAddress (
        CSL_InstNum            i2cNum,
        CSL_I2cParam           *pI2cParam,
        CSL_I2cBaseAddress     *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    /* Added according to review comment 2. */
    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (i2cNum) {
            case CSL_I2C:
                pBaseAddress->regs = (CSL_I2cRegsOvly)CSL_I2C_0_REGS;
                break;

            default:
                pBaseAddress->regs = NULL;
                status = CSL_ESYS_FAIL;
        }
    }
    return (status);
}

