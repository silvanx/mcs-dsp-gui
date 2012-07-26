/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ===========================================================================
 * @file csl_tmrHwSetup.c
 *
 * @brief File for functional layer of CSL API CSL_tmrHwSetup() 
 * 
 * @path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrHwSetup() function definition & it's associated
 *       functions 
 * ============================================================================
 */
 
/* ============================================================================
 * Revision History
 * ===============
 *  1-Sept-2004 HMM File Created.
 *  29-Jul-2005 PSK Updted changes acooriding to revised timer spec. The number
 *                  convention TIM12, TIM34 are changed to TIMLO and TIMHI.
 *  01-Feb-2006 ds  Updated According to TCI6482/C6455 UserGuide
 * ============================================================================
 */

#include <csl_tmr.h>
#include <csl_tmrAux.h>

/** ============================================================================
 *   @n@b CSL_tmrHwSetup
 *
 *   @b Description
 *   @n It configures the  timer instance registers as per the values passed
 *      in the hardware setup structure.
 *
 *   @b Arguments
 *   @verbatim
            htmr            Handle to the timer instance

            setup           Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Hardware structure is not
 *                                                properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The specified instance will be setup according to value passed
 *
 *   @b Modifies
 *   @n Hardware registers for the specified instance
 *
 *   @b Example
 *   @verbatim
        CSL_status          status;
        CSL_tmrHwSetup      hwSetup;
        ...
        status = CSL_tmrHwSetup(htmr, &hwSetup);
        ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION(CSL_tmrHwSetup, ".text:csl_section:tmr");
CSL_Status  CSL_tmrHwSetup (
    CSL_TmrHandle  hTmr,
    CSL_TmrHwSetup *hwSetup
)
{
    CSL_Status status = CSL_SOK ;

    if (hTmr == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
    	/* Load the Period register's */
    	hTmr->regs->PRDLO = hwSetup->tmrTimerPeriodLo;
    	hTmr->regs->PRDHI = hwSetup->tmrTimerPeriodHi;
    
    	/* Load the counter register's */
    	hTmr->regs->TIMLO = hwSetup->tmrTimerCounterLo;
    	hTmr->regs->TIMHI = hwSetup->tmrTimerCounterHi;
    
    	/* Setup the TCR register  configurations */
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_PWID_HI, hwSetup->tmrPulseWidthHi);
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_CP_HI, hwSetup->tmrClockPulseHi);
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_INVOUTP_HI, hwSetup->tmrInvOutpHi);
    
    	/* Setup the TCR register  configurations */
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_TIEN_LO, hwSetup->tmrIpGateLo);
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_CLKSRC_LO, hwSetup->tmrClksrcLo);
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_PWID_LO, hwSetup->tmrPulseWidthLo);
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_CP_LO, hwSetup->tmrClockPulseLo);
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_INVINP_LO, hwSetup->tmrInvInpLo);
    	CSL_FINS(hTmr->regs->TCR, TMR_TCR_INVOUTP_LO, hwSetup->tmrInvOutpLo);
    
    	/* Setup the TGCR register  configurations */
    	CSL_FINS(hTmr->regs->TGCR, TMR_TGCR_PSCHI, hwSetup->tmrPreScalarCounterHi);
    
    	/* set the operation mode */
    	CSL_FINS(hTmr->regs->TGCR, TMR_TGCR_TIMMODE, hwSetup->tmrTimerMode);
    }

    return status;
}

