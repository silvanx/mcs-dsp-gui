/* ===========================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in 
 * the license agreement under which this software has been supplied.
 * ==========================================================================
 */

/** ===========================================================================
 *  @file csl_gpioHwSetupRaw.c
 *
 *  @path $(CSLPATH)\src\gpio
 * 
 *  @desc File for functional layer of CSL API CSL_gpioHwSetupRaw() 
 * ============================================================================
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  07-Sep-2004 Nsr File Created.
 *  28-Jul-2005 PSK updated changes to support only one BANK
 *  06-Mar-2006 ds  Updated the documentation
 * ============================================================================
 */

#include <csl_gpio.h>

/** ===========================================================================
 *   @n@b CSL_gpioHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the Config Data structure. This configures registers 
 *      based on a structure of register values, as compared to HwSetup, which 
 *      configures registers based on structure of bit field values.
 *
 *   @b Arguments
 *   @verbatim
            hGpio        Handle to the Gpio instance

            config       Pointer to config structure
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameters                                                
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_gpioInit() and CSL_gpioOpen() must be called successfully in 
 *       order before this function.
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified GPIO instance will be setup
 *       according to value passed.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified GPIO instance.
 *
 *   @b Example
 *   @verbatim
        CSL_GpioHandle       hGpio;
        CSL_GpioConfig       config = CSL_GPIO_CONFIG_DEFAULTS;
        CSL_Status          status;

        status = CSL_gpioHwSetupRaw (hGpio, &config);

     @endverbatim
 * ===========================================================================
 */ 
#pragma CODE_SECTION (CSL_gpioHwSetupRaw, ".text:csl_section:gpio");
CSL_Status CSL_gpioHwSetupRaw (
    CSL_GpioHandle hGpio,    
    CSL_GpioConfig *config
)
{
    CSL_Status status = CSL_SOK;

    if (hGpio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }

    else if (config == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        hGpio->regs->BINTEN = config->BINTEN;   
        hGpio->regs->DIR = config->DIR;   
        hGpio->regs->OUT_DATA = config->OUT_DATA;   
        hGpio->regs->SET_DATA = config->SET_DATA;   
        hGpio->regs->CLR_DATA = config->CLR_DATA;   
        hGpio->regs->SET_RIS_TRIG = config->SET_RIS_TRIG;   
        hGpio->regs->CLR_RIS_TRIG = config->CLR_RIS_TRIG;   
        hGpio->regs->SET_FAL_TRIG = config->SET_FAL_TRIG;   
        hGpio->regs->CLR_FAL_TRIG = config->CLR_FAL_TRIG; 
    }
    return (status);
}
