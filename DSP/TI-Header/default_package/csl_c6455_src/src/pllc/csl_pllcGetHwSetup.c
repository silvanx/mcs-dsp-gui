/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_pllcGetHwSetup.c
 *
 *  @brief File for functional layer of CSL API @a CSL_pllcGetHwSetup()
 *
 *  Path: \(CSLPATH)\src\pllc
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  26-Aug-2005 Tej File created.
 *  27-oct-2005 sd  changes for multiplier configuration
 *  18-Jan-2006 sd  Changes according to spec changes
 *  ============================================================================
 */

#include <csl_pllc.h>

/** ============================================================================
 *   @n@b CSL_pllcGetHwSetup
 *
 *   @b Description
 *   @n It retrives the hardware setup parameters of the pllc
 *      specified by the given handle.
 *
 *   @b Arguments
 *   @verbatim
            hPllc        Handle to the pllc

            hwSetup      Pointer to the hardware setup structure
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
 *   @n  None
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
            CSL_PllcHandle   hPllc;
            CSL_PllcHwSetup  hwSetup;
            ...

            status = CSL_pllcGetHwSetup(hPllc, &hwSetup);
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcGetHwSetup, ".text:csl_section:pllc");
CSL_Status CSL_pllcGetHwSetup (
    CSL_PllcHandle               hPllc,
    CSL_PllcHwSetup             *hwSetup
)
{
    CSL_Status       status   = CSL_SOK;
    CSL_PllcRegsOvly pllcRegs = hPllc->regs;

    if (hPllc == NULL ) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        hwSetup->divEnable = 0;
    
        if (hPllc->pllcNum == CSL_PLLC_1) {
    	    hwSetup->pllMode = (CSL_FEXT( pllcRegs->PLLCTL, PLLC_PLLCTL_PLLEN))   ||
    	                       (CSL_FEXT( pllcRegs->PLLCTL, PLLC_PLLCTL_PLLENSRC))||
    	                       (CSL_FEXT( pllcRegs->PLLCTL, PLLC_PLLCTL_PLLRST))  ||
    	                       (CSL_FEXT( pllcRegs->PLLCTL, PLLC_PLLCTL_PLLPWRDN));
    
    	    if (CSL_FEXT (pllcRegs->PREDIV, PLLC_PREDIV_PREDEN)) {
    	        hwSetup->divEnable |= CSL_PLLC_DIVEN_PREDIV;
    	        hwSetup->preDiv = CSL_FEXT (pllcRegs->PREDIV, PLLC_PREDIV_RATIO) + 1;
    	    }
    
    	    hwSetup->pllM = CSL_FEXT (pllcRegs->PLLM, PLLC_PLLM_PLLM) + 1;
    
            if (CSL_FEXT (pllcRegs->PLLDIV4, PLLC_PLLDIV4_D4EN)) {
                hwSetup->divEnable |= CSL_PLLC_DIVEN_PLLDIV4;
                hwSetup->pllDiv4 = CSL_FEXT (pllcRegs->PLLDIV4, PLLC_PLLDIV4_RATIO) + 1;
            }
            if (CSL_FEXT (pllcRegs->PLLDIV5, PLLC_PLLDIV5_D5EN)) {
                hwSetup->divEnable |= CSL_PLLC_DIVEN_PLLDIV5;
                hwSetup->pllDiv5 = CSL_FEXT (pllcRegs->PLLDIV5, PLLC_PLLDIV5_RATIO) + 1;
            }
        }
    
        if (hPllc->pllcNum == CSL_PLLC_2) {
            if (CSL_FEXT (pllcRegs->PLLDIV1, PLLC_PLLDIV1_D1EN)) {
                hwSetup->divEnable |= CSL_PLLC_DIVEN_PLLDIV1;
                hwSetup->pllDiv1 = CSL_FEXT (pllcRegs->PLLDIV1, PLLC_PLLDIV1_RATIO) + 1;
            }
        }
    }

    return status;
}

