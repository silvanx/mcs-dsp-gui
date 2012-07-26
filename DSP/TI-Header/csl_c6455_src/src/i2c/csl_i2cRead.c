/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cRead.c
 *
 *  @brief File for functional layer of CSL API @a CSL_i2cRead()
 *
 *  @path $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The @a CSL_i2cRead() function definition & it's associated functions
 *
 *  Modification 1
 *    - Created on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cRead
 *
 *   @b Description
 *   @n This function reads I2C data.
 *
 *   @b Arguments
 *   @verbatim
            hI2c            Handle to I2C instance
            
            buf             Buffer to store the data read

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Operation Successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *   
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_i2cInit() and @a CSL_i2cOpen() must be called successfully
 *       in that order before @a CSL_i2cRead() can be called.
 *
 *   <b> Post Condition </b>
 *   @n None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 * @verbatim

        Uint16        outData;
        CSL_Status    status;
        CSL_I2cHandle hI2c;
        ...
        // I2C object defined and HwSetup structure defined and initialized
        ...

        // Init, Open, HwSetup successfully done in that order
        ...

        status = CSL_i2cRead (hI2c, &outData);
   @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cRead, ".text:csl_section:i2c");
CSL_Status CSL_i2cRead (
    CSL_I2cHandle hI2c,
    void          *buf
)
{
    CSL_Status status = CSL_SOK;

    if (hI2c == NULL) {
        return CSL_ESYS_BADHANDLE;
    }
    else if (buf == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        *(Uint8 *)buf = CSL_FEXT(hI2c->regs->ICDRR,I2C_ICDRR_D);
    }

    return (status);
}

