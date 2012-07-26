/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ===========================================================================
 * @file csl_tmrHwSetupRaw.c
 *
 * @brief File for functional layer of CSL API CSL_tmrHwSetupRaw() 
 * 
 * @path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrHwSetupRaw() function definition & it's associated
 *       functions 
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 *  1-Sept-2004 HMM File Created.
 *  29-Jul-2005 PSK Updated changes acooriding to revised timer spec. The number
 *                  convention TIM12, TIM34 are changed to TIMLO and TIMHI.   
 *  03-Apr-2006 ds  Removed "EMUMGT_CLKSPD" configuration
 * ============================================================================
 */

#include <csl_tmr.h>
#include <csl_tmrAux.h>

/** ============================================================================
 *   @n@b CSL_tmrHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *  	provided through the config data structure.
 *
 *   @b Arguments
 *   @verbatim
            hTmr            Pointer to the object that holds reference to the
                            instance of TIMER requested after the call 

            config          Pointer to the config structure containing the
                            device register values
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration structure
 *                                                pointer is not properly
 *                                                initialized
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified timer instance will be setup according 
 *       to the values passed through the config structure
 *
 *   @b Modifies
 *   @n Hardware registers of the specified timer instance
 *
 *   @b Example
 *   @verbatim
        CSL_TmrHandle           hTmr;
        CSL_TmrConfig           config = CSL_TMR_CONFIG_DEFAULTS;
        CSL_Status              status;
        ...
        status = CSL_tmrHwSetupRaw(hTmr, &config);
        ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION(CSL_tmrHwSetupRaw, ".text:csl_section:tmr");
CSL_Status  CSL_tmrHwSetupRaw (
    CSL_TmrHandle hTmr,
    CSL_TmrConfig *config
)
{
    CSL_Status status = CSL_SOK ;

    if (hTmr == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (config == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* General purpose timer Timer Counter Register Low */
        hTmr->regs->TIMLO = config->TIMLO;
    
        /* General purpose timer Timer Counter Register High */
        hTmr->regs->TIMHI = config->TIMHI;
    
        /* General purpose timer Timer Period Register Low */
        hTmr->regs->PRDLO = config->PRDLO;
    
        /* General purpose timer Timer Period Register High */
        hTmr->regs->PRDHI = config->PRDHI;
    
        /* General purpose timer Timer Control Register */
        hTmr->regs->TCR = config->TCR;
    
        /* General purpose timer Timer Global Control Register */
        hTmr->regs->TGCR = config->TGCR;
    
        /* General purpose timer General purpose Timer Control Register */
        hTmr->regs->WDTCR = config->WDTCR;
    }

    return status;
}

