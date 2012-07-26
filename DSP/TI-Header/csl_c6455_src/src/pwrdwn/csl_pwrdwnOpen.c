/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnOpen.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnOpen ()
 *
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 * =============================================================================
 */

#include <csl_pwrdwn.h>

/** ============================================================================
 *  @b CSL_ pwrdwnOpen
 *  
 *  @b Description
 *  @n This function populates the peripheral data object for the PWRDWN 
 *    instance and returns a handle to the instance.
 *    The open call sets up the data structures for the particular instance
 *    of PWRDWN device. The device can be re-opened anytime after it has been
 *    normally closed if so required. The handle returned by this call is
 *    input as an essential argument for rest of the APIs described
 *    for this module.
 *
 *  @b Arguments
 *  @verbatim
          pwrdwnObj      Pointer to PWRDWN object.

          pwrdwnNum      Instance of pwrdwn CSL to be opened.
                         There are three instance of the PWRDWN
                         available. So, the value for this parameter will be
                         based on the instance.
          pPwrdwnParam   Module specific parameters.
          status         Status of the function call
    @endverbatim
 *
 *  <b> Return Value </b>  CSL_pwrdwnHandle
 *  @n                     Valid pwrdwn handle will be returned if
 *                        status value is equal to CSL_SOK.
 *
 *  <b> Pre Condition </b>
 *  @n  CSL_pwrdwnInit(), CSL_pwrdwnOpen()must be opened prior to this call
 *
 *  <b> Post Condition </b>
 *  @n   1. The status is returned in the status variable. If status
 *          returned is
 *  @li     CSL_SOK             Valid pwrdwn handle is returned
 *  @li     CSL_ESYS_FAIL       The pwrdwn instance is invalid
 *  @li     CSL_ESYS_INVPARAMS  Invalid Parameters
 *  
 *       2. pwrdwn object structure is populated
 *  
 *  @b Modifies
 *  @n   1. The status variable
 *  
 *       2. pwrdwn object structure
 *       
 *  @b Example
    @verbatim
        CSL_PwrdwnObj pwrObj;
        CSL_PwrdwnConfig pwrConfig;
        CSL_PwrdwnHandle hPwr;
        // Init Module
        ...
        if (CSL_pwrdwnInit(NULL) != CSL_SOK)
            exit;
        // Opening a handle for the Module   
        hPwr = CSL_pwrdwnOpen (&pwrObj, CSL_PWRDWN, NULL, NULL);
     
         // Setup the arguments fof the Config structure
         ...
    @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnOpen, ".text:csl_section:pwrdwn");
CSL_PwrdwnHandle CSL_pwrdwnOpen (
    CSL_PwrdwnObj       *pPwrdwnObj,   
    CSL_InstNum         pwrdwnNum,     
    CSL_PwrdwnParam     *pPwrdwnParam, 
    CSL_Status          *pStatus
)
{
    CSL_PwrdwnBaseAddress baseAddress;
    CSL_PwrdwnHandle hPwrdwn = (CSL_PwrdwnHandle)NULL;

    
    if (pStatus == NULL) {
        /* do nothing : already the module is initialized to NULL */
    }
    
    else if (pPwrdwnObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }

    else {
        *pStatus = CSL_pwrdwnGetBaseAddress(pwrdwnNum, pPwrdwnParam, &baseAddress);

        if (*pStatus == CSL_SOK) {
            pPwrdwnObj->pdcRegs = baseAddress.regs;
            pPwrdwnObj->l2pwrdwnRegs = baseAddress.l2pwrdwnRegs;
            pPwrdwnObj->instNum = (CSL_InstNum)pwrdwnNum;
            hPwrdwn = (CSL_PwrdwnHandle)pPwrdwnObj;
        }
        else {
            pPwrdwnObj->pdcRegs = (CSL_PdcRegsOvly)NULL;
            pPwrdwnObj->l2pwrdwnRegs = NULL;
            pPwrdwnObj->instNum = (CSL_InstNum)-1;
        }      
    }
    return (hPwrdwn);
}

