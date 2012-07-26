/* ==========================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005 
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ==========================================================================
*/

/** ===========================================================================
 *  @file csl_gpioInit.c
 *
 *  @path $(CSLPATH)\src\gpio
 * 
 *  @desc The CSL_gpioInit() function definition & it's associated functions
 * ============================================================================
 */
 
/* ============================================================================
 * Revision History
 * ===============
 *  09-Jun-2004 PGR File created
 *  04-Sep-2004 Nsr Updated the function and documentation for CSL_gpioInit.
 *  11-oct-2004 Nsr updated the code to avoid compiler warning/remark.
 *  06-Mar-2006 ds  Updated the documentation
 * ============================================================================
 */
 

#include <csl_gpio.h>

/** ===========================================================================
 *   @n@b CSL_gpioInit
 *
 *   @b Description
 *   @n This is the initialization function for the GPIO CSL. The function must 
 *      be called before calling any other API from this CSL. This function does 
 *      not modify any registers or check status. It returns status CSL_SOK. It
 *      has been kept for future use.
 *
 *   @b Arguments
 *   @verbatim
 *          pContext      Pointer to module-context. Context information for the 
 *                        instance. Should be NULL
 *   @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The CSL for GPIO is initialized
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
 *      ...
 *      CSL_gpioInit(NULL);
 *   @endverbatim
 *  ===========================================================================
 */ 
#pragma CODE_SECTION (CSL_gpioInit, ".text:csl_section:gpio");
CSL_Status CSL_gpioInit (
    CSL_GpioContext *pContext
)
{
    return CSL_SOK;
}

