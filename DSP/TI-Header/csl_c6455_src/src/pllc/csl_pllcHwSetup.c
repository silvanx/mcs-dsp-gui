/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_pllcHwSetup.c
 *
 *  @brief File for functional layer of CSL API @a CSL_pllcHwSetup()
 *
 *  Path: \(CSLPATH)\src\pllc
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  25-Aug-2005 Tej File Created.
 *  27-oct-2005 sd  changes for multiplier configuration
 *  18-Jan-2006 sd  Changes according to spec changes
 *  ============================================================================
 */

#include <csl_pllc.h>

/** ============================================================================
 *   @n@b CSL_pllcHwSetup
 *
 *   @b Description
 *   @n It configures the pllc registers as per the values passed
 *      in the hardware setup structure.
 *
 *   @b Arguments
 *   @verbatim
            hPllc            Handle to the pllc

            hwSetup          Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Hardware structure is not
                                                  properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  PLLC registers are configured according
 *       to the hardware setup parameters
 *
 *   @b Modifies
 *   @n PLLC registers
 *
 *   @b Example
 *   @verbatim
            CSL_PllcHandle   hPllc;
            CSL_PllcObj      pllcObj;
            CSL_PllcHwSetup  hwSetup;
            CSL_status       status;
            ...

            hPllc = CSL_pllcOpen(&pllcObj, CSL_PLLC_1, NULL, &status);
            ...

            status = CSL_pllcHwSetup(hPllc, &hwSetup);
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcHwSetup, ".text:csl_section:pllc");
CSL_Status CSL_pllcHwSetup (
    CSL_PllcHandle            hPllc,
    CSL_PllcHwSetup          *hwSetup
)
{
    CSL_PllcRegsOvly pllcRegs = hPllc->regs;
    CSL_Status       status = CSL_SOK;
    volatile unsigned int loopCount;

    if (hPllc == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        if (hPllc->pllcNum == CSL_PLLC_1) {
    
            /* 
             * The registers PLLCTL, PREDIV, PLLM, PLLDIV4, PLLDIV5 are valid only for 
             * PLLC instance 1
             */
    
            /* Set PLLCTL, PLLENSRC bit to 0 first to modify PLLEN bit */
            CSL_FINS (pllcRegs->PLLCTL, PLLC_PLLCTL_PLLENSRC,
                      CSL_PLLC_PLLCTL_PLLENSRC_REGBIT);
        
            /* Ensure that PLLCTL is not in the PLL Mode */
            CSL_FINS (pllcRegs->PLLCTL, PLLC_PLLCTL_PLLEN,
                      CSL_PLLC_PLLCTL_PLLEN_BYPASS);
        
            CSL_FINS (pllcRegs->PLLCTL, PLLC_PLLCTL_PLLRST,
                      CSL_PLLC_PLLCTL_PLLRST_YES);
        
            /* Ensure that PLL is not in the Power-Down state */
            CSL_FINS (pllcRegs->PLLCTL, PLLC_PLLCTL_PLLPWRDN,
                      CSL_PLLC_PLLCTL_PLLPWRDN_NO);
        
            if (hwSetup->divEnable & CSL_PLLC_DIVEN_PREDIV) {
                CSL_FINS (pllcRegs->PREDIV, PLLC_PREDIV_PREDEN,
                          CSL_PLLC_PREDIV_PREDEN_ENABLE);
                CSL_FINS (pllcRegs->PREDIV, PLLC_PREDIV_RATIO, hwSetup->preDiv - 1);
            }
            else {
                CSL_FINS (pllcRegs->PREDIV, PLLC_PREDIV_PREDEN,
                          CSL_PLLC_PREDIV_PREDEN_DISABLE);
            }
        
            CSL_FINS (pllcRegs->PLLM, PLLC_PLLM_PLLM, hwSetup->pllM - 1);
            
            if (hwSetup->divEnable & CSL_PLLC_DIVEN_PLLDIV4) {
                CSL_FINS (pllcRegs->PLLDIV4, PLLC_PLLDIV4_D4EN,
                          CSL_PLLC_PLLDIV4_D4EN_ENABLE);
                CSL_FINS (pllcRegs->PLLDIV4, PLLC_PLLDIV4_RATIO, hwSetup->pllDiv4 - 1);
            }
            else {
                CSL_FINS (pllcRegs->PLLDIV4, PLLC_PLLDIV4_D4EN,
                          CSL_PLLC_PLLDIV4_D4EN_DISABLE);
            }
            if (hwSetup->divEnable & CSL_PLLC_DIVEN_PLLDIV5) {
                CSL_FINS (pllcRegs->PLLDIV5, PLLC_PLLDIV5_D5EN,
                          CSL_PLLC_PLLDIV5_D5EN_ENABLE);
                CSL_FINS (pllcRegs->PLLDIV5, PLLC_PLLDIV5_RATIO, hwSetup->pllDiv5 - 1);
            }
            else {
                CSL_FINS (pllcRegs->PLLDIV5, PLLC_PLLDIV5_D5EN,
                          CSL_PLLC_PLLDIV5_D5EN_DISABLE);
            }
        }
        
        /* If Instance no. is CSL_PLLC_2 then only change PLLDIV1 */
        if (hPllc->pllcNum == CSL_PLLC_2) {
            if (hwSetup->divEnable & CSL_PLLC_DIVEN_PLLDIV1) {
                CSL_FINS (pllcRegs->PLLDIV1, PLLC_PLLDIV1_D1EN,
                          CSL_PLLC_PLLDIV1_D1EN_ENABLE);
                CSL_FINS (pllcRegs->PLLDIV1, PLLC_PLLDIV1_RATIO, hwSetup->pllDiv1 - 1);
            }
            else {
                CSL_FINS (pllcRegs->PLLDIV1, PLLC_PLLDIV1_D1EN,
                      CSL_PLLC_PLLDIV1_D1EN_DISABLE);
            }
        }
    
        /* Set GOSET bit to change/set the dividers */
        CSL_FINS (pllcRegs->PLLCMD, PLLC_PLLCMD_GOSET, CSL_PLLC_PLLCMD_GOSET_SET);
    
        while (CSL_FEXT (pllcRegs->PLLSTAT, PLLC_PLLSTAT_GOSTAT)) {
            /* Poll for divide-ratio change and clock alignment to complete */
        }
    
        
        if (hPllc->pllcNum == CSL_PLLC_1) {
        
            CSL_FINS (pllcRegs->PLLCTL, PLLC_PLLCTL_PLLRST, CSL_PLLC_PLLCTL_PLLRST_NO);
        
            /* Wait for 4 cycles of the slowest of the  CLKIN/OSCIN
             * Introducing some arbitrary delay.
             */
        
            loopCount = CSL_PLLC_DELAY_2000;
            while (loopCount--) {
                asm("   NOP");
            }
        
            CSL_FINS (pllcRegs->PLLCTL, PLLC_PLLCTL_PLLEN, hwSetup->pllMode);
        }
    }

    return status;
}
