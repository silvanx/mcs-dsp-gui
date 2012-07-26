/* =============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/* ============================================================================
 * @file csl_tmrOpen.c
 *
 * @brief File for functional layer of CSL API CSL_tmrOpen() 
 * 
 * @Path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrOpen() function definition & it's associated
 *       functions 
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 * 1-Sept-2004 HMM File Created.
 * 29-Jul-2005 PSK Updted changes acooriding to revised timer spec. the number
 *                 convention TIM12, TIM34 are changed to TIMLO and TIMHI. 
 *
 * ============================================================================
 */

#include <csl_tmr.h>

/** ===========================================================================
 * @b CSL_trmOpen
 * @b Description
 * @n This function populates the peripheral data object for the TIMER 
 *    instance and returns a handle to the instance.
 *    The open call sets up the data structures for the particular instance
 *    of TIMER device. The device can be re-opened anytime after it has been
 *    normally closed if so required. The handle returned by this call is
 *    input as an essential argument for rest of the APIs described
 *    for this module.
 *
 * @b Arguments
 * @verbatim
          tmrObj          Pointer to timer object.

          tmrNum          Instance of timer CSL to be opened.
                          There are three instance of the timer
                          available. So, the value for this parameter will be
                          based on the instance.
          pTmrParam       Module specific parameters.
          status          Status of the function call
   @endverbatim
 *
 * <b> Return Value </b>  CSL_TmrHandle
 * @n                     Valid timer handle will be returned if
 *                        status value is equal to CSL_SOK.
 *
 * <b> Pre Condition </b>
 * @n  None
 *
 * <b> Post Condition </b>
 * @n   1. The status is returned in the status variable. If status
 *         returned is
 * @li     CSL_SOK             Valid timer handle is returned
 * @li     CSL_ESYS_FAIL       The timer instance is invalid
 * @li     CSL_ESYS_INVPARAMS  The object structure is not properly initialized
 *
 *      2. Timer object structure is populated
 *
 * @b Modifies
 * @n   1. The status variable
 *
 *      2. Timer object structure
 *
 * @b Example
 * @verbatim
            CSL_status              status;
            CSL_TmrObj              tmrObj;
            CSL_TmrHandle           hTmr;
            hTmr = CSL_tmrOpen(&tmrObj, CSL_TMR_1, NULL, &status);
            ...
   @endverbatim
 * ========================================================================== */
#pragma CODE_SECTION(CSL_tmrOpen, ".text:csl_section:tmr");
CSL_TmrHandle CSL_tmrOpen (
    CSL_TmrObj   *pTmrObj, 
    CSL_InstNum  tmrNum, 
    CSL_TmrParam *pTmrParam, 
    CSL_Status   *pStatus
)
{
    CSL_Status st;
    CSL_TmrHandle hTmr = NULL;
    CSL_TmrBaseAddress baseAddress;

    if (pStatus == NULL) {
        /* do nothing */
    }
    else if (pTmrObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        st = CSL_tmrGetBaseAddress(tmrNum, pTmrParam, &baseAddress);
    
        if (st == CSL_SOK) {
            pTmrObj->regs = baseAddress.regs;
            pTmrObj->perNum = (CSL_InstNum)tmrNum;
            hTmr = (CSL_TmrHandle)pTmrObj;
        }
        else {
            pTmrObj->regs = (CSL_TmrRegsOvly)NULL;
            pTmrObj->perNum = (CSL_InstNum)-1;
            hTmr = (CSL_TmrHandle)NULL;
        }
    
        *pStatus = st;
    }

    return hTmr;
}

