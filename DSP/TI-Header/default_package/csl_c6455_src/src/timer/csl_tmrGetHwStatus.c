/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ===========================================================================
 * @file csl_tmrGetHwStatus.c
 *
 * @brief File for functional layer of CSL API CSL_tmrGetHwStatus() 
 * 
 * @path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrGetHwStatus() function definition & it's associated
 *       functions 
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 * 1-Sept-2004 HMM File Created.
 * 29-Jul-2005 PSK updted changes acooriding to revised timer spec. the number
 *                 convention TIM12, TIM34 are changed to TIMLO and TIMHI.  
 * ============================================================================
 */

#include <csl_tmr.h>
#include <csl_tmrAux.h>

/** ===========================================================================
 *   @n@b CSL_tmrGetHwStatus
 *
 *   @b Description
 *   @n This function is used to get the value of various parameters of the
 *      timer instance. The value returned depends on the query passed.
 *
 *   @b Arguments
 *   @verbatim
            hTmr            Handle to the timer instance

            query           Query to be performed

            response        Pointer to buffer to return the data requested by
                            the query passed
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Successful completion of the
 *                                               query
 *
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *
 *   @li                    CSL_ESYS_INVQUERY  - Query command not supported
 *
 *   @li                    CSL_ESYS_INVPARAMS - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *       Data requested by the query is returned through the variable "response"
 *
 *   @b Modifies
 *   @n  The input arguement "response" is modified
 *
 *   @b Example
 *   @verbatim
        CSL_status    status;
        Uint8         hwRevId;
        ... 
        status = CSL_tmrGetHwStatus(hGptimer, CSL_TMR_QUERY_COUNT_LO,
                                    &hwRevId);
        ...                                    
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_tmrGetHwStatus, ".text:csl_section:tmr");
CSL_Status CSL_tmrGetHwStatus (
    CSL_TmrHandle        hTmr,
    CSL_TmrHwStatusQuery query,
    void                 *response
)
{
    CSL_Status status = CSL_SOK;

    if (hTmr == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (query) {
            case CSL_TMR_QUERY_COUNT_LO:
                CSL_tmrGetTimLoCount(hTmr, (Uint32 *)response);
                break;
    
            case CSL_TMR_QUERY_COUNT_HI:
                CSL_tmrGetTimHiCount(hTmr, (Uint32 *)response);
                break;
    
            case CSL_TMR_QUERY_TSTAT_LO:
                *((CSL_TmrTstat *)response) = CSL_tmrGetTstatLoStatus(hTmr);
                break;
    
            case CSL_TMR_QUERY_TSTAT_HI:
                *((CSL_TmrTstat *)response) = CSL_tmrGetTstatHiStatus(hTmr);
                break;
     
            case CSL_TMR_QUERY_WDFLAG_STATUS:
    		    *((CSL_TmrWdflagBitStatus*)response) = 
                                               CSL_tmrGetWdflagStatus(hTmr); 
    		    break;
    
            default:
                status = CSL_ESYS_INVQUERY;
    		    break;
        }
    }

    return status;
}

