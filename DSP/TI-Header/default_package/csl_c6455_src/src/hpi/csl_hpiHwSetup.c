/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiHwSetup.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiHwSetup()
 *
 */
#include <csl_hpi.h>

/** ============================================================================
 *   @n@b CSL_hpiHwSetup
 *
 *   @b Description
 *   @n It configures the hpi registers as per the values passed
 *      in the hardware setup structure.
 *
 *   @b Arguments
 *   @verbatim
            hHpi               Handle to the hpi
 
            hwSetup             Pointer to harware setup structure
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is invalid
 *   @li                    CSL_ESYS_INVPARAMS  - The parameter passed is 
 *                                                invalid
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  HPI registers are configured according to the hardware setup 
 *       parameters.
 *
 *   @b Modifies
 *   @n HPI registers
 *
 *   @b Example
 *   @verbatim
            CSL_status          status;
            CSL_HpiHwSetup     myHwSetup;            
            CSL_HpiHandle      hHpi;

            myHwSetup.HPIC = hwSetup->hpiCtrl;
             .....
            
            status = CSL_hpiHwSetup(hHpi, &hwSetup);
     @endverbatim
 * ===========================================================================
 */

#pragma CODE_SECTION (CSL_hpiHwSetup, ".text:csl_section:hpi"); 
CSL_Status  CSL_hpiHwSetup (
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
        /* Configure the Control Register */
        hpiRegs->HPIC = hwSetup->hpiCtrl;
    }
    return (status);
}

