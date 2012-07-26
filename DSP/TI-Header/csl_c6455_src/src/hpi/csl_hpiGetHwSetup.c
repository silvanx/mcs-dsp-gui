/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiGetHwSetup.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiGetHwSetup()
 *
 */
#include <csl_hpi.h>

/** ============================================================================
 *   @n@b CSL_hpiGetHwSetup
 *
 *   @b Description
 *   @n It retrives the hardware setup parameters of the hpi
 *      specified by the given handle.
 *
 *   @b Arguments
 *   @verbatim
            hHpi        Handle to the hpi
 
            hwSetup         Pointer to the harware setup structure
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Retrieving the hardware setup
 *                                                parameters is successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle is passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_hpiInit() and CSL_hpiOpen() must be called successfully in order
 *       before calling CSL_hpiGetHwSetup().
 *
 *   <b> Post Condition </b>
 *   @n  The hardware setup structure is populated with the hardware setup
 *       parameters
 *
 *   @b Modifies
 *   @n hwSetup variable
 *
 *   @b Example
 *   @verbatim
            CSL_HpiHandle   hHpi;
            CSL_HpiHwSetup  hwSetup;

            ...
            
            status = CSL_hpiGetHwSetup(hHpi, &hwSetup);
            
            ...
            
     @endverbatim
 * ===========================================================================
 */

#pragma CODE_SECTION (CSL_hpiGetHwSetup, ".text:csl_section:hpi");
CSL_Status  CSL_hpiGetHwSetup (
    CSL_HpiHandle     hHpi,
    CSL_HpiHwSetup    *hwSetup
)
{
    CSL_Status status = CSL_SOK;
    CSL_HpiRegsOvly hpiRegs = hHpi->regs;
        
    if (hHpi == NULL) { 
        status = CSL_ESYS_BADHANDLE;
    }
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        hwSetup->hpiCtrl = (CSL_HpiCtrl)hpiRegs->HPIC;
        hwSetup->hpiAddr.hpiaWrtAddr = hpiRegs->HPIAW;
        hwSetup->hpiAddr.hpiaReadAddr = hpiRegs->HPIAR;                        
    }
    return (status);
}

