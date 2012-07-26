/*  ===========================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */
/** ============================================================================
 *   @file  csl_gpioGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_gpioGetBaseAddress
 *
 */
/*  ===========================================================================
 *  Revision History
 *  ===============
 *  11-Oct-2004 Nsr renamed the local variable "st" as "status" and added the
 *                  - code for validating the input parameters.
 *  04-Sep-2004 Nsr File Created.
 *
 *  ===========================================================================
 */
#include <soc.h>
#include <csl_gpio.h>

/** ===========================================================================
 *   @n@b CSL_gpioGetBaseAddress
 *
 *   @b Description
 *   @n  Function to get the base address of the peripheral instance.
 *       This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_gpioOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *
 *   @b Arguments
 *   @verbatim
            gpioNum        Specifies the instance of the GPIO to be opened.

            pGpioParam     Module specific parameters.

            pBaseAddress  Pointer to baseaddress structure containing base
                          address details.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK              Successful on getting the base 
 *                                              address of gpio
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
        CSL_GpioBaseAddress  baseAddress;

       ...
      status = CSL_gpioGetBaseAddress(CSL_GPIO, NULL, &baseAddress);

    @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_gpioGetBaseAddress, ".text:csl_section:gpio");
CSL_Status
CSL_gpioGetBaseAddress (
    CSL_InstNum            gpioNum,
    CSL_GpioParam          *pGpioParam,
    CSL_GpioBaseAddress    *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (gpioNum) {
            case CSL_GPIO:
                pBaseAddress->regs = (CSL_GpioRegsOvly)CSL_GPIO_0_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_GpioRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
        }
    }
    return (status);
}

