/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file csl_i2cGetHwSetup.c
 *
 *  @brief File for functional layer of CSL API CSL_i2cGetHwSetup()
 *
 *  @path $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The CSL_i2cGetHwSetup() function definition & it's associated
 *      functions
 *
 *  Modification 1
 *    - Modified on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cGetHwSetup
 *
 *   @b Description
 *   @n This function gets the current setup of the I2C. The status is
 *      returned through @a CSL_I2cHwSetup. The obtaining of status
 *      is the reverse operation of @a CSL_i2cHwSetup() function.
 *
 *   @b Arguments
 *   @verbatim
            hI2c            Handle to the I2C

            hwSetup         Pointer to the hardware setup structure

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Retrieving the hardware setup
 *                                                parameters is successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_i2cInit() and @a CSL_i2cOpen() must be called successfully
 *       in that order before @a CSL_i2cGetHwSetup() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  The hardware setup structure is populated with the hardware setup
 *       parameters
 *
 *   @b Modifies
 *   @n hwSetup variable
 *
 *   @b Example
 *   @verbatim
            CSL_I2cHandle   hI2c;
            CSL_I2cHwSetup  hwSetup;
            ...
            status = CSL_i2cGetHwSetup(hI2c, &hwSetup);
            ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cGetHwSetup, ".text:csl_section:i2c")
CSL_Status CSL_i2cGetHwSetup (
    CSL_I2cHandle     hI2c,
    CSL_I2cHwSetup    *setup
)
{
    CSL_Status status = CSL_SOK;
    CSL_I2cClkSetup clkSetup;

    if (hI2c == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        setup->mode = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_MST);
        setup->dir = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_TRX);
        setup->addrMode = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_XA);
        setup->ownaddr = CSL_FEXT(hI2c->regs->ICOAR, I2C_ICOAR_OADDR);
        setup->sttbyteen = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_STB);
        setup->ackMode = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_NACKMOD);
        setup ->runMode = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_FREE);
        setup ->repeatMode = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_RM);
        setup->loopBackMode = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_DLB);
        setup->freeDataFormat = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_FDF);
        setup->resetMode = CSL_FEXT(hI2c->regs->ICMDR, I2C_ICMDR_IRS);
        setup->bcm = CSL_FEXT(hI2c->regs->ICEMDR, I2C_ICEMDR_BCM);
        setup->inten = hI2c->regs->ICIMR ;
    
        clkSetup.prescalar = CSL_FEXT(hI2c->regs->ICPSC, I2C_ICPSC_IPSC);
        clkSetup.clklowdiv = CSL_FEXT(hI2c->regs->ICCLKL, I2C_ICCLKL_ICCL);
        clkSetup.clkhighdiv= CSL_FEXT(hI2c->regs->ICCLKH, I2C_ICCLKH_ICCH);
    
        setup->clksetup->prescalar  = clkSetup.prescalar;
        setup->clksetup->clklowdiv  = clkSetup.clklowdiv;
        setup->clksetup->clkhighdiv = clkSetup.clkhighdiv;
    }
    return (status);
}

