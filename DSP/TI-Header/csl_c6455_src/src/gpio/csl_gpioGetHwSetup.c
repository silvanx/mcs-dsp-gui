/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ============================================================================
*/

/** ==========================================================================
 *  @file csl_gpioGetHwSetup.c
 *
 *  @path $(CSLPATH)\src\gpio
 * 
 *  @desc File for functional layer of CSL API CSL_gpioGetHwSetup() 
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 *  10-Jun-2004 PGR File created
 *  11-Oct-2004 Nsr Changed this file according to review commnets.
 *  06-Mar-2006 ds  Updated the documentation
 * ============================================================================
 */
 
#include <csl_gpio.h>

/** ============================================================================
 *   @n@b CSL_gpioGetHwSetup
 *
 *   @b Description
 *   @n Gets the current setup of GPIO. This is a dummy API . 
 *      Its is left for future implementation.
 *
 *   @b Arguments
 *   @verbatim
            hGpio            Handle to the GPIO instance

            setup           Pointer to setup structure to hold the
                            setup information of GPIO.
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
        CSL_GpioHandle       hGpio;
        CSL_GpioHwSetup      setup;
        CSL_Status           status;

        status = CSL_gpioGetHwSetup(hGpio, &setup);
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_gpioGetHwSetup, ".text:csl_section:gpio");
CSL_Status CSL_gpioGetHwSetup ( 
    CSL_GpioHandle  hGpio,
    CSL_GpioHwSetup *setup
)
{
    return CSL_SOK;
}
