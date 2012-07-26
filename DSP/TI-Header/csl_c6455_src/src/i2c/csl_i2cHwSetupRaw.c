/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cHwSetupRaw.c
 *
 *  @brief File for functional layer of CSL API @a CSL_i2cHwSetupRaw()
 *
 *  @path $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The @a CSL_i2cHwSetupRaw() function definition & it's associated
 *      functions
 *
 *  Modification 1
 *    - Modified on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *    @author Santosh Narayanan.
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  01-Sep-2004 Hs File Created.
 *  11-oct-2004 Hs updated code according to code review comments.
 * =============================================================================
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the Config Data structure.
 *
 *   @b Arguments
 *   @verbatim
            hI2c            Handle to the I2C

            config          Pointer to config structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration is not
 *                                                properly initialized
 *
 *   @n Both @a CSL_i2cInit() and @a CSL_i2cOpen() must be called successfully
 *      in that order before @a CSL_i2cHwSetupRaw() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified I2C instance will be setup
 *       according to value passed.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified I2C instance.
 *
 *   @b Example
 *   @verbatim
        CSL_I2cHandle       hI2c;
        CSL_I2cConfig       config = CSL_I2C_CONFIG_DEFAULTS;
        CSL_Status          status;
        ...
        status = CSL_i2cHwSetupRaw(hI2c, &config);
        ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cHwSetupRaw, ".text:csl_section:i2c");
CSL_Status CSL_i2cHwSetupRaw (
    CSL_I2cHandle    hI2c,
    CSL_I2cConfig    *config
)
{
    CSL_Status status = CSL_SOK;

    if (hI2c == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (config == NULL ) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        hI2c->regs->ICOAR = config->ICOAR;
        hI2c->regs->ICIMR = config->ICIMR;
        hI2c->regs->ICSTR = config->ICSTR;
        hI2c->regs->ICCLKL = config->ICCLKL;
        hI2c->regs->ICCLKH = config->ICCLKH;
        hI2c->regs->ICCNT = config->ICCNT;
        hI2c->regs->ICSAR = config->ICSAR;
        hI2c->regs->ICDXR = config->ICDXR;
        hI2c->regs->ICMDR = config->ICMDR;
        hI2c->regs->ICIVR = config->ICIVR;
        hI2c->regs->ICEMDR = config->ICEMDR;
        hI2c->regs->ICPSC = config->ICPSC;
    }

    return (status);
}

