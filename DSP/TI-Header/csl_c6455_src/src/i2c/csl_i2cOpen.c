/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cOpen.c
 *
 *  @brief File for functional layer of CSL API @a CSL_i2cOpen()
 *
 *  @path $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The @a CSL_i2cOpen() function definition & it's associated functions

 *  Modification 1
 *    - Created on: 28/05/2004
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  31-aug-2004 Hs Updated function and documentation for CSL_i2cOpen.
 *                 - Removed the include file, csl_resource.h.
 *  11-oct-2004 Hs updated code according to code review comments.
 *	15-nov-2005 Hs Removed the assignment of pI2cParam and 
 				   redundant pStatus check
 *
 * =============================================================================
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cOpen
 *
 *   @b Description
 *   @n This function populates the peripheral data object for the instance
 *        and returns a handle to the instance.
 *        The open call sets up the data structures for the particular instance
 *        of I2C device. The device can be re-opened anytime after it has been
 *        normally closed if so required. The handle returned by this call is
 *        input as an essential argument for rest of the APIs described for
 *        this module.
 *
 *   @b Arguments
 *   @verbatim            
            pI2cObj         Pointer to the I2C instance object
 
            i2cNum          Instance of the I2C to be opened.
 
            pI2cParam       Pointer to module specific parameters
 
            pStatus         pointer for returning status of the function call

     @endverbatim
 *
 *   <b> Return Value </b>  
 *      CSL_I2cHandle
 *        Valid I2C instance handle will be returned if status value is
 *        equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_i2cInit() must be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n  i2c instance will be opened
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b Example:
 *   @verbatim
         CSL_status        status;
         CSL_I2cObj        i2cObj;
         CSL_I2cHandle     hI2c;
         ...
         hI2c = CSL_I2cOpen (&i2cObj,
                             CSL_I2C,
                             NULL,
                             &status
                             );
         ...
     @endverbatim
 *
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cOpen, ".text:csl_section:i2c");
CSL_I2cHandle CSL_i2cOpen (
    CSL_I2cObj      *pI2cObj,
    CSL_InstNum      i2cNum,
    CSL_I2cParam    *pI2cParam,
    CSL_Status      *pStatus
)
{
    CSL_I2cHandle      hI2c = (CSL_I2cHandle)NULL;
    CSL_I2cBaseAddress baseAddress;

    /* Added according to review comment 1. */
    if (pStatus == NULL) {
        /* do nothing : module handle is already initialized to NULL */
    }
    else if (pI2cObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        *pStatus = CSL_i2cGetBaseAddress(i2cNum, pI2cParam, &baseAddress);

        if (*pStatus == CSL_SOK) {
            pI2cObj->regs = baseAddress.regs;
            pI2cObj->perNum = (CSL_InstNum)i2cNum;
            hI2c = (CSL_I2cHandle)pI2cObj;
        }
        else {
            pI2cObj->regs = (CSL_I2cRegsOvly)NULL;
            pI2cObj->perNum = (CSL_InstNum)-1;
        }
    }
    return (hI2c);
}

