/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** =========================================================================== 
 * @file csl_i2cClose.c
 *
 * @brief File for functional layer of CSL API CSL_i2cClose()
 *
 * @path $(CSLPATH)\i2c\src
 * 
 *  Description
 *    - The CSL_i2cClose() function definition & it's associated functions
 *
 *
 *  Modification 1
 *    - Created on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 * ============================================================================ 
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  31-aug-2004 Hs Updated function and documentation for CSL_i2cclose.
 *                 - Removed the include file, csl_resource.h.
 *  11-oct-2004 Hs updated according to code review comments.
 *
 * =============================================================================
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cClose
 *
 *   @b Description
 *   @n This function closes the specified instance of I2C.
 *
 *   @b Arguments
 *   @verbatim
            hI2c            Handle to the I2C

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close Successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  The device should be successfully opened.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n I2C Handle
 *
 *   @b Example
 *   @verbatim
            CSL_I2cHandle   hI2c;
            ...
            status = CSL_i2cClose(hI2c);
            ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_i2cClose, ".text:csl_section:i2c");
CSL_Status CSL_i2cClose (
    CSL_I2cHandle    hI2c
)
{
    CSL_Status status = CSL_SOK;

    if (hI2c != NULL) {
        hI2c->regs = (CSL_I2cRegsOvly)NULL;
        hI2c->perNum = (CSL_InstNum)-1;
    }
    else {
        status = CSL_ESYS_BADHANDLE;
    }
    return (status);
}

