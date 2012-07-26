/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file  csl_pllcHwSetupRaw.c
 *
 *  @brief File for functional layer of CSL API @a CSL_pllcHwSetupRaw()
 *
 *  Path: \(CSLPATH)\src\pllc
 *
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  10-Feb-2004 kpn  File Created.
 *  25-Aug-2005 Tej File Modified.
 *  17-Jan-2006 sd   Changes according to spec changes
 *  ============================================================================
 */

#include <csl_pllc.h>

/** ============================================================================
 *   @n@b CSL_pllcHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the Config Data structure.
 *
 *   @b Arguments
 *   @verbatim
            hpllc        Handle to the PLLC instance

            config       Pointer to config structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li            CSL_SOK               - Configuration successful
 *   @li            CSL_ESYS_BADHANDLE    - Invalid handle
 *   @li            CSL_ESYS_INVPARAMS    - Configuration is not
                                            properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified PLLC instance will be setup
 *       according to input configuration structure values.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified PLLC instance.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle       hPllc;
        CSL_PllcConfig       config = CSL_PLLC_CONFIG_DEFAULTS;
        CSL_Status           status;
        ...

        status = CSL_pllcHwSetupRaw (hPllc, &config);
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_pllcHwSetupRaw, ".text:csl_section:pllc");
CSL_Status CSL_pllcHwSetupRaw (
    CSL_PllcHandle               hPllc,
    CSL_PllcConfig              *config
)
{
    CSL_Status      status = CSL_SOK;
    volatile Uint32 loopCount;

    if (hPllc == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (config == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        loopCount = 65000;
    
        /* Set PLLCTL, PLLENSRC bit to 0 first to modify PLLEN bit */
        if (hPllc->pllcNum == CSL_PLLC_1) {
    
            CSL_FINS (hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLENSRC,
                      CSL_PLLC_PLLCTL_PLLENSRC_REGBIT);
        
            /* Ensure that PLLCTL is not in the PLL Mode */
            CSL_FINS (hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLEN,
                      CSL_PLLC_PLLCTL_PLLEN_BYPASS);
        
            CSL_FINS (hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLRST,
                      CSL_PLLC_PLLCTL_PLLRST_YES);
        
            /* Ensure that PLLCTL is not in the Power-Down state */
            CSL_FINS (hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLPWRDN,
                      CSL_PLLC_PLLCTL_PLLPWRDN_NO);
        
            /* PLL Multiplier Control register */
            hPllc->regs->PLLM   = config->PLLM;
        
            /* PLL Pre-Divider Control register */
            hPllc->regs->PREDIV   = config->PREDIV;
        
            /* PLL Controller Divider 4 register */
            hPllc->regs->PLLDIV4   = config->PLLDIV4;
        
            /* PLL Controller Divider 5 register */
            hPllc->regs->PLLDIV5   = config->PLLDIV5;
        }
    
    
        /* PLL Controller Divider 1 register if instance is 2 */
        if (hPllc->pllcNum == CSL_PLLC_2) {
            hPllc->regs->PLLDIV1   = config->PLLDIV1;
        }
    
        /* Set GOSET bit to change/set the dividers */
        CSL_FINS (hPllc->regs->PLLCMD, PLLC_PLLCMD_GOSET,
                  CSL_PLLC_PLLCMD_GOSET_SET);
    
        while (CSL_FEXT (hPllc->regs->PLLSTAT, PLLC_PLLSTAT_GOSTAT)) {
            /* Poll for divide-ratio change and clock alignment to complete */
        }
    
        if (hPllc->pllcNum == CSL_PLLC_1) {
    
            CSL_FINS (hPllc->regs->PLLCTL, PLLC_PLLCTL_PLLRST,
                      CSL_PLLC_PLLCTL_PLLRST_NO);
        
            /* Wait for 4 cycles of the slowest of the  CLKIN/OSCIN
             * Introducing some arbitrary delay.
             */
        
            loopCount = 65000;
            while (loopCount--) {
                asm("   NOP");
            }
        
            /* PLL Control register */
            hPllc->regs->PLLCTL   = config->PLLCTL;
        }
    }
    
    return status;
}

