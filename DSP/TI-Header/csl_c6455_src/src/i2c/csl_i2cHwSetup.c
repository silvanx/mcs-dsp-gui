/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cHwSetup.c
 *
 *  @brief File for functional layer of CSL API @a CSL_i2cHwSetup()
 *
 *  @path $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The @a CSL_i2cHwSetup() function definition & it's associated
 *      functions
 *
 *  Modification 1
 *    - Modified on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 *  ============================================================================
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cHwSetup
 *
 *   @b Description
 *   @n This function initializes the device registers with the appropriate 
 *      values provided through the HwSetup Data structure. This function needs
 *      to be called only if the HwSetup Structure was not previously passed 
 *      through the Open call. After the Setup is completed, the device is ready
 *      for  operation.For information passed through the HwSetup Data structure
 *      refer @a CSL_i2cHwSetup.
 *   @b Arguments
 *   @verbatim
            hI2c            Handle to the I2C

            setup           Pointer to setup structure which contains the
                            information to program I2C to a useful state

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup Successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_i2cInit() and @a CSL_i2cOpen() must be called successfully
 *       in that order before this function can be called. The user has to 
 *       allocate space for & fill in the main setup structure appropriately 
 *       before calling this function.
 *
 *   <b> Post Condition </b>
 *   @n The registers of the specified I2C instance will be setup
 *      according to value passed.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified I2C instance.
 *
 *   @b Example
 * @verbatim
     CSL_i2cHandle hI2c;
     CSL_i2cHwSetup hwSetup = CSL_I2C_HWSETUP_DEFAULTS;
     ...
     CSL_i2cHwSetup(hI2c, &hwSetup);
     ...
  @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cHwSetup, ".text:csl_section:i2c");
CSL_Status CSL_i2cHwSetup (
    CSL_I2cHandle     hI2c,
    CSL_I2cHwSetup    *setup
)
{
    CSL_Status status = CSL_SOK;

    if (hI2c == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /*  Set the mode(Master/Slave), direction(Transmitter/Receiver),
         *  addressing mode(7-bit or 10-bit, free run mode, free data 
         *  format and start byte mode.
         */
        hI2c->regs->ICMDR = ((hI2c->regs->ICMDR & 0x3807) |
                             (CSL_FMK(I2C_ICMDR_MST,setup->mode) |
                              CSL_FMK(I2C_ICMDR_NACKMOD, setup->ackMode) |
                              CSL_FMK(I2C_ICMDR_TRX, setup->dir) |
                              CSL_FMK(I2C_ICMDR_XA, setup->addrMode) |
                              CSL_FMK(I2C_ICMDR_FREE, setup->runMode) |
                              CSL_FMK(I2C_ICMDR_STB, setup->sttbyteen) |
                              CSL_FMK(I2C_ICMDR_FDF, setup->freeDataFormat) |
                              CSL_FMK(I2C_ICMDR_RM, setup->repeatMode) |
                              CSL_FMK(I2C_ICMDR_DLB, setup->loopBackMode) |
                              CSL_FMK(I2C_ICMDR_IRS, setup->resetMode)));

        /* set Backward Compatibility Mode  */
        hI2c->regs->ICEMDR = (hI2c->regs->ICEMDR & 0x1) |
                             (CSL_FMK(I2C_ICEMDR_BCM, setup->bcm));

        /* Set the own address of the given instance        */
        CSL_FINS(hI2c->regs->ICOAR, I2C_ICOAR_OADDR, setup->ownaddr);

        /* The interrupt status is set into the interrupt enable register  */
        hI2c->regs->ICIMR = setup->inten ;

        /* Set up the prescalar value       */
        CSL_FINS(hI2c->regs->ICPSC, I2C_ICPSC_IPSC, setup->clksetup->prescalar);

        /* Set the clock low value         */
        CSL_FINS(hI2c->regs->ICCLKL, I2C_ICCLKL_ICCL, 
                 setup->clksetup->clklowdiv);

        /* Set the clock high value      */
        CSL_FINS(hI2c->regs->ICCLKH, I2C_ICCLKH_ICCH, 
                 setup->clksetup->clkhighdiv);
    }
    return (status);
}

