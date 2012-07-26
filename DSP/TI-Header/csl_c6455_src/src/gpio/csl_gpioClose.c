/* ==========================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ==========================================================================
*/

/** ===========================================================================
 *  @file csl_gpioClose.c
 *
 *  @path $(CSLPATH)\src\gpio
 * 
 *  @desc File for functional layer of CSL API CSL_gpioClose()
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 *  10-Jun_2004 PGR file created
 *  07-Sep-2004 Nsr Updated function and documentation for CSL_gpioclose.
 *                  - Removed the include file, csl_resource.h.
 *  11-Oct-2004 Nsr renamed the local variable "st" as "status"
 *  28-Jul-2005 PSK Updated CSL source to support only ONE BANK.
 *                 bank "index" is removed.
 *  06-Mar-2006 ds  Updated the documentation
 * ============================================================================
 */

#include <csl_gpio.h>        

/** ============================================================================
 *   @n@b CSL_gpioClose
 *
 *   @b Description
 *   @n This function closes the specified instance of GPIO.
 *
 *   @b Arguments
 *   @verbatim
            hGpio            Handle to the GPIO instance
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_gpioInit() and CSL_gpioOpen() must be called successfully in 
 *       order before calling CSL_gpioClose(). 
 *
 *   <b> Post Condition </b>
 *   @n  The GPIO CSL APIs can not be called until the GPIO CSL is reopened 
 *       again using CSL_gpioOpen().
 *
 *   @b Modifies
 *   @n Obj structure values
 *
 *   @b Example
 *   @verbatim
            CSL_GpioHandle       hGpio;
            CSL_Status          status;

            ...

            status = CSL_gpioClose(hGpio);
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_gpioClose, ".text:csl_section:gpio");
CSL_Status CSL_gpioClose (
    CSL_GpioHandle hGpio
)
{
    /* Indicate in the CSL global hGpio structure that the peripheral
     * has been unreserved   */
    CSL_Status  status = CSL_SOK;
    
    if (hGpio != NULL) {
        hGpio->regs = (CSL_GpioRegsOvly)NULL;
        hGpio->gpioNum = (CSL_InstNum)-1;
    }
    else {
        status = CSL_ESYS_BADHANDLE;
    }
    return status;
}
