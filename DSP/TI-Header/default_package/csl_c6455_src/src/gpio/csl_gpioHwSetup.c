/* ==========================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ==========================================================================
*/

/** ===========================================================================
 *  @file csl_gpioHwSetup.c
 *  
 *  @path $(CSLPATH)\src\gpio
 *  
 *  @Desc File for functional layer of CSL API CSL_gpioHwSetup()
 * ============================================================================
 */
 
/* ============================================================================ 
 * Revision History
 * =================
 *  10-Jun-2004 PGR file created
 *  06-Mar-2006 ds  Updated the documentation
 * ============================================================================
 */

#include <csl_gpio.h>

/** ============================================================================
 *   @n@b CSL_gpioHwSetup
 *
 *   @b Description
 *   @n It configures the gpio registers as per the values passed
 *      in the hardware setup structure.This is a dummy API . 
 *      Its is left for future implementation.
 *
 *   @b Arguments
 *   @verbatim
            hGpio            Handle to the GPIO instance

            hwSetup          Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  Always return CSL_SOK
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_gpioInit() and CSL_gpioOpen() must be called successfully in 
 *       order before this function. 
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_GpioHandle    hGpio;
        CSL_GpioObj       gpioObj;
        CSL_GpioHwSetup   hwSetup;
        CSL_Status        status;

        hwSetup.extendSetup = NULL;
        ...

        hGpio = CSL_gpioOpen(&gpioObj, CSL_GPIO, NULL, &status);

        status = CSL_gpioHwSetup(hGpio, &hwSetup);
 *   @endverbatim
 * =============================================================================
 */ 
#pragma CODE_SECTION (CSL_gpioHwSetup, ".text:csl_section:gpio");
CSL_Status CSL_gpioHwSetup (
    CSL_GpioHandle  hGpio, 
    CSL_GpioHwSetup *setup
)
{
    return CSL_SOK;
}
