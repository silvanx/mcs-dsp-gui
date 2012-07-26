/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cWrite.c
 *
 *  @brief File for functional layer of CSL API @a CSL_i2cWrite()
 *
 *  @path  $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The @a CSL_i2cWrite() function definition & it's associated functions
 *
 *  Modification 1
 *    - Created on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 *  ============================================================================
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cWrite
 *
 *   @b Description
 *   @n This function writes the specified data into I2C data register.
 *
 *   @b Arguments
 *   @verbatim
            hI2c            Handle to I2C instance
            
            buf             data to be written

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Success (doesnot verify 
                                                           written data)
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_i2cInit() and @a CSL_i2cOpen() must be called successfully
 *       in that order before @a CSL_i2cWrite() can be called.
 *
 *   <b> Post Condition </b>
 *    @n None
 *
 *   @b Modifies
 *   @n  None
 *
 * @b Example:
 * @verbatim

      Uint16     inData;
      CSL_Status status;
      CSL_I2cHandle hI2c;
      ...
      // I2C object defined and HwSetup structure defined and initialized
      ...

      // Init, Open, HwSetup successfully done in that order
      ...

        status = CSL_i2cWrite(hi2c, &inData);
   @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cWrite, ".text:csl_section:i2c");
CSL_Status CSL_i2cWrite (
    CSL_I2cHandle    hI2c,
    void             *buf
)
{
    CSL_Status status = CSL_SOK;
    
    if (hI2c == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (buf == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        hI2c->regs->ICDXR = (hI2c->regs->ICDXR & 0xFF00) |
                            (CSL_FMK(I2C_ICDXR_D,*(Uint8 *)buf));
    }
    return (status);
}

