/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * =============================================================================
 */

/** ===========================================================================
 * @file csl_tmrHwControl.c
 *
 * @brief File for functional layer of CSL API CSL_tmrHwControl() 
 * 
 * @path $(CSLPATH)\src\timer
 *
 * @desc The CSL_tmrHwControl() function definition & it's associated
 *       functions 
 *
 */

/* ============================================================================
 * Revision History
 * ===============
 * 1-Sept-2004 HMM File Created.
 * 29-Jul-2005 PSK updted changes acooriding to revised timer spec. The number
 *                 convention TIM12, TIM34 are changed to TIMLO and TIMHI.   
 * ============================================================================
 */

#include <csl_tmr.h>
#include <csl_tmrAux.h>

/** ============================================================================
 *   @n@b CSL_tmrHwControl
 *
 *   @b Description
 *   @n This function performs various control operations on the timer instance,
 *      based on the command passed.
 *
 *   @b Arguments
 *   @verbatim
            hTmr         Handle to the timer instance

            cmd          Operation to be performed on the timer

            cmdArg       Arguement specific to the command

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Command execution successful.
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVCMD    - Invalid command
 *   @li                    CSL_ESYS_INVPARAMS - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Registers of the timer instance are configured according to the command
 *       and the command arguments. The command determines which registers are
 *       modified.
 *
 *   @b Modifies
 *   @n Registers determined by the command
 *
 *   @b Example
 *   @verbatim
        CSL_Status status;
        ...  
        status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMLO, NULL);
        ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_tmrHwControl, ".text:csl_section:tmr");
CSL_Status  CSL_tmrHwControl (
    CSL_TmrHandle       hTmr,
    CSL_TmrHwControlCmd cmd,
    void                *arg
)
{
    CSL_Status status = CSL_SOK ;

    if (hTmr == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (\
         (cmd <= CSL_TMR_CMD_LOAD_WDKEY) && (cmd != CSL_TMR_CMD_STOP_TIMLO) &&\
         (cmd != CSL_TMR_CMD_STOP_TIMHI) && (cmd != CSL_TMR_CMD_RESET_TIMLO)&&\
         (cmd != CSL_TMR_CMD_RESET_TIMHI)&& (cmd != CSL_TMR_CMD_STOP64) &&\
         (cmd != CSL_TMR_CMD_RESET64)    && (arg == NULL)\
         ) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (cmd) {
            /* Load PRDLO */
            case CSL_TMR_CMD_LOAD_PRDLO:
                CSL_TmrLoadPrdLo(hTmr, (Uint32 *)arg);
                break;
    
            /* Load PRDHI */
            case CSL_TMR_CMD_LOAD_PRDHI:
                CSL_TmrLoadPrdHi(hTmr, (Uint32 *)arg);
                break;
    
            /* Load PSCHI */
            case CSL_TMR_CMD_LOAD_PSCHI:
                CSL_TmrLoadPrescalarHi(hTmr, (Uint8 *)arg);
                break;
    
            /* start the timer Low */
            case CSL_TMR_CMD_START_TIMLO:
                CSL_TmrStartLo(hTmr, *((CSL_TmrEnamode *)arg));
                break;
    
            /* start the timer Low */
            case CSL_TMR_CMD_START_TIMHI:
                CSL_TmrStartHi(hTmr, *((CSL_TmrEnamode *)arg));
                break;
    
            /* Stop the Timer Low */
            case CSL_TMR_CMD_STOP_TIMLO:
                CSL_TmrStopLo(hTmr);
                break;
    
            /* Stop the TimerHi */
            case CSL_TMR_CMD_STOP_TIMHI:
                CSL_TmrStopHi(hTmr);
                break;
    
            /* Reset the Timer Low */
            case CSL_TMR_CMD_RESET_TIMLO:
                CSL_TmrResetLo(hTmr);
                break;
    
            /* Reset the TimerHi */
            case CSL_TMR_CMD_RESET_TIMHI:
                CSL_TmrResetHi(hTmr);
                break;
    
         	/* Start the timer in GPtimer64 OR Chained mode */
          	case CSL_TMR_CMD_START64:
          	    CSL_TmrStart64(hTmr, *((CSL_TmrEnamode *)arg));
                break;
    
        	/*Stop the timer of GPtimer64 OR Chained */
        	case CSL_TMR_CMD_STOP64:
        	    CSL_TmrStop64(hTmr);
        	    break;
    
        	/*Reset the timer of GPtimer64 OR Chained */
        	case CSL_TMR_CMD_RESET64:
        	    CSL_TmrReset64(hTmr);
        	    break;
    
    	    /*Starts the timer in watchdog mode */ 
            case CSL_TMR_CMD_START_WDT:
    		    CSL_TmrStartWdt(hTmr, *(CSL_TmrEnamode *)arg);
                break;
    
    	    /*loads the watchdog key */
    	    case CSL_TMR_CMD_LOAD_WDKEY:
    		    CSL_TmrLoadWdkey(hTmr, *((Uint16 *)arg));
                break;
    
            default:
                status = CSL_ESYS_INVCMD;
    	        break;
        }
    }

    return status;
}

