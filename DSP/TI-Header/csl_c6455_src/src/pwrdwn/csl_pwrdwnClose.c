/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnClose.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnClose ()
 *
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004 Ruchika Kharwar File Created
 *  01-Feb-2006 ds  Added error checking
 * =============================================================================
 */
 
#include <csl_pwrdwn.h>

/** =========================================================================== 
 * @n@b CSL_pwrdwnClose
 *
 *  @b Description
 *  @n This function closes the specified instance of pwrdwn.
 *
 *  @b Arguments
 *  @verbatim
           hPwrdwn            Handle to the PWRDWN instance
    @endverbatim
 *
 *  <b> Return Value </b>  CSL_Status
 *  @li                    CSL_SOK             - Close successful
 *  @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   
 *  <b> Pre Condition </b>
 *  @n  CSL_pwrdwnInit(), CSL_pwrdwnOpen() must be opened prior to this call.
 *
 *  <b> Post Condition </b>
 *  @n  1. The PWRDWN CSL APIs can not be called until the PWRDWN
 *         CSL is reopened again using CSL_pwrdwnOpen()
 *
 *  @b Modifies
 *  @n  None
 *
 *  @b Example:
 *  @verbatim 
       CSL_PwrdwnObj pwrObj;
       CSL_PwrdwnConfig pwrConfig;
       CSL_PwrdwnHandle hPwr;
       // Init Module
       ...
       if (CSL_pwrdwnInit(NULL) != CSL_SOK)
       exit;
       // Opening a handle for the Module   
       hPwr = CSL_pwrdwnOpen(&pwrObj, CSL_PWRDWN, NULL, NULL);
    
       // Setup the arguments fof the Config structure
       ...
       // Close
       CSL_pwrdwnClose(hPwr);  
  @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnClose, ".text:csl_section:pwrdwn");
CSL_Status CSL_pwrdwnClose (
    CSL_PwrdwnHandle hPwrdwn
)
{   CSL_Status     status = CSL_SOK;
    
    /* Indicate in the CSL global data structure that the peripheral
     * has been unreserved   */
    if (hPwrdwn != NULL) {
        hPwrdwn->l2pwrdwnRegs = (CSL_L2pwrdwnRegsOvly) NULL;
        hPwrdwn->pdcRegs      = (CSL_PdcRegsOvly) NULL;
        hPwrdwn->instNum      = (CSL_InstNum) - 1;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }             
    return status;
}

