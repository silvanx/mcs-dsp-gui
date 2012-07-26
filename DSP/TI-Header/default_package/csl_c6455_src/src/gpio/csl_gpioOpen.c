/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ==========================================================================
*/

/** ===========================================================================
 *  @file csl_gpioOpen.c
 *
 *  @path $(CSLPATH)\src\gpio
 * 
 *  @desc The CSL_gpioOpen() function definition & it's associated functions
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 *  10-jun-2004 PGR File created
 *  04-Sep-2004 Nsr Updated function and documentation for CSL_gpioOpen.
 *                - Removed the include file, csl_resource.h.
 *  11-Oct-2004 Nsr renamed the local variable "st" as "status"
 *  06-Mar-2006 ds  Updated the documentation
 * ============================================================================
 */
 
#include <csl_gpio.h>          

/** ============================================================================
 *   @n@b CSL_gpioOpen
 *
 *   @b Description
 *   @n This function populates the peripheral data object for the GPIO instance
 *      and returns a handle to the instance.
 *      The open call sets up the data structures for the particular instance
 *      of GPIO device. The device can be re-opened anytime after it has been
 *      normally closed if so required. The handle returned by this call is
 *      input as an essential argument for rest of the APIs described
 *      for this module.
 *
 *   @b Arguments
 *   @verbatim
              pGpioObj      Pointer to the GPIO instance object

              gpioNum       Instance of the GPIO to be opened

              pGpioParam    Pointer to module specific parameters

              pStatus       pointer for returning status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_GpioHandle
 *   @n                     Valid GPIO instance handle will be returned if 
                            status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  The GPIO must be successfully initialized via CSL_gpioInit() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n   1.    GPIO object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid gpio handle is returned
 *   @li            CSL_ESYS_FAIL       The gpio instance is invalid
 *   @li            CSL_ESYS_INVPARAMS  Invalid parameter
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. GPIO object structure
 *
 *   @b Example
 *   @verbatim
            CSL_Status         status;
            CSL_GpioObj        gpioObj;
            CSL_GpioHandle     hGpio;
            ...

            hGpio = CSL_gpioOpen(&gpioObj, CSL_GPIO, NULL, &status);
            ...
    @endverbatim
 * =============================================================================
 */ 
#pragma CODE_SECTION (CSL_gpioOpen, ".text:csl_section:gpio");
CSL_GpioHandle CSL_gpioOpen (
    CSL_GpioObj   *pGpioObj,
    CSL_InstNum   gpioNum,
    CSL_GpioParam *pGpioParam,
    CSL_Status    *pStatus
)
{
    CSL_GpioHandle hGpio = (CSL_GpioHandle)NULL;
    CSL_GpioBaseAddress baseAddress;

    if (pStatus == NULL) {
        /* do nothing : already the module is initialized to NULL */
    }
    
    else if (pGpioObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }

    else { 
        *pStatus = CSL_gpioGetBaseAddress(gpioNum, pGpioParam, &baseAddress);

        if (*pStatus == CSL_SOK) {
            pGpioObj->regs = baseAddress.regs;
            pGpioObj->gpioNum = (CSL_InstNum)gpioNum;
            pGpioObj->numPins = CSL_GPIO_NUM_PINS;
            hGpio = (CSL_GpioHandle)pGpioObj;
        } 
        else {
            pGpioObj->regs = (CSL_GpioRegsOvly)NULL;
            pGpioObj->gpioNum = (CSL_InstNum)-1;
            
        }
    }
    return (hGpio);
}
