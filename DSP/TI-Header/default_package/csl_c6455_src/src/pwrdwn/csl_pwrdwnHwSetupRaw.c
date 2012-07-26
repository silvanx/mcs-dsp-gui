/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnHwSetupRaw.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnHwSetupRaw ()
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 * =============================================================================
 */
 
#include <csl_pwrdwn.h>

/** ===========================================================================
 *   @n@b CSL_pwrdwnHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the config data structure.
 *
 *   @b Arguments
 *   @verbatim
            hPwrdwn         Pointer to the object that holds reference to the
                            instance of PWRDWN requested after the call 

            config          Pointer to the config structure containing the
                            device register values
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration structure
 *                                                pointer is not properly
 *                                                 initialized
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_pwrdwnInit(), CSL_pwrdwnOpen() must be opened prior to this call
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified PWRDWN instance will be setup
 *       according to the values passed through the config structure
 *
 *   @b Modifies
 *   @n Hardware registers of the specified PWRDWN instance
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
    
        // Setup the arguments for the Config structure
        ...
    
        // Setup
        CSL_pwrdwnHwSetupRaw(hPwr,&pwrConfig);
    
        // Close handle
        CSL_pwrdwnClose(hPwr);
    @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnHwSetupRaw, ".text:csl_section:pwrdwn");
CSL_Status  CSL_pwrdwnHwSetupRaw (
    CSL_PwrdwnHandle    hPwrdwn,
    CSL_PwrdwnConfig    *config
)
{
    CSL_Status status = CSL_SOK;

    if (hPwrdwn == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }              
    else if (config == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }              
    else {
        hPwrdwn->pdcRegs->PDCCMD = config->PDCCMD;

        hPwrdwn->l2pwrdwnRegs->L2PDWAKE[0] = config->L2PDWAKE0;
        hPwrdwn->l2pwrdwnRegs->L2PDWAKE[1] = config->L2PDWAKE1;

        hPwrdwn->l2pwrdwnRegs->L2PDSLEEP[0] = config->L2PDSLEEP0;
        hPwrdwn->l2pwrdwnRegs->L2PDSLEEP[1] = config->L2PDSLEEP1;
    }   
    return status;
}

