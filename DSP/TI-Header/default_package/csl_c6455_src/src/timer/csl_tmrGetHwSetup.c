/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * =============================================================================
 */

/** ===========================================================================
 * @file csl_tmrGetHwSetup.c
 *
 * @brief File for functional layer of CSL API CSL_tmrGetHwSetup() 
 * 
 * @path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrGetHwSetup() function definition & it's associated functions
 * ============================================================================
 */       

/* ============================================================================
 * Revision History
 * ===============
 *  1-Sept-2004 HMM File Created.
 *
 *  29-Jul-2005 PSK updted changes acooriding to revised timer spec. the number
 *                 convention TIM12, TIM34 are changed to TIMLO and TIMHI.
 *
 *  01-Feb-2006 ds  Updated according to TCI6482/C6455 UserGuide
 * ============================================================================
 */

#include <csl_tmr.h>

/** ============================================================================
 *   @n@b CSL_tmrGetHwSetup
 *
 *   @b Description
 *   @n It retrives the hardware setup parameters
 *
 *   @b Arguments
 *   @verbatim
         hTmr        Handle to the timer instance

         hwSetup     Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup retrived
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - setup structure is not 
 *                                                properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  Module should be initialised and opened
 *
 *   <b> Post Condition </b>
 *   @n  The hardware set up structure will be populated with values from
 *       the registers
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
         CSL_status        status;
         CSL_TmrHwSetup     hwSetup;
         ...  
         hwsetup->tmrTimerPeriodLo = 0x100;
         hwsetup->tmrTimerPeriodLo = 0x100;
         ...
         status = CSL_tmrGetHwsetup(hTmr, &hwSetup);
         ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_tmrGetHwSetup, ".text:csl_section:tmr");
CSL_Status CSL_tmrGetHwSetup (
    CSL_TmrHandle  hTmr,
    CSL_TmrHwSetup *hwSetup
)
{
    CSL_Status     status = CSL_SOK;

    if (hTmr == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* Get the Period register's values */
        hwSetup->tmrTimerPeriodLo = hTmr->regs->PRDLO;
        hwSetup->tmrTimerPeriodHi = hTmr->regs->PRDHI;
    
        /* Get the counter register's  values*/
        hwSetup->tmrTimerCounterLo = hTmr->regs->TIMLO;
        hwSetup->tmrTimerCounterHi = hTmr->regs->TIMHI;
    
        hwSetup->tmrPulseWidthHi =
                (CSL_TmrPulseWidth)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_PWID_HI);
        
        hwSetup->tmrClockPulseHi =
                (CSL_TmrClockPulse)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_CP_HI);
        
        hwSetup->tmrInvOutpHi =
                (CSL_TmrInvOutp)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_INVOUTP_HI);
    
        /* Get the TCR register  configurations */
        hwSetup->tmrIpGateLo =
                (CSL_TmrIpGate)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_TIEN_LO);
        
        hwSetup->tmrClksrcLo =
                (CSL_TmrClksrc)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_CLKSRC_LO);
        
        hwSetup->tmrPulseWidthLo =
                (CSL_TmrPulseWidth)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_PWID_LO);
        
        hwSetup->tmrClockPulseLo =
                (CSL_TmrClockPulse)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_CP_LO);
        
        hwSetup->tmrInvInpLo =
                (CSL_TmrInvInp)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_INVINP_LO);
        
        hwSetup->tmrInvOutpLo =
                (CSL_TmrInvOutp)CSL_FEXT(hTmr->regs->TCR, TMR_TCR_INVOUTP_LO);
    
        /* Get the TGCR register  configurations */
        hwSetup->tmrPreScalarCounterHi = 
            (Uint8)CSL_FEXT(hTmr->regs->TGCR, TMR_TGCR_PSCHI);
        
        /* Get the operation mode */
        hwSetup->tmrTimerMode = 
            (CSL_TmrMode)CSL_FEXT(hTmr->regs->TGCR, TMR_TGCR_TIMMODE);
    }

    return status;
}

