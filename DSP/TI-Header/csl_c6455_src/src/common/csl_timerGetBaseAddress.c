/*  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *   @file  csl_tmrGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_tmrGetBaseAddress
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  1-Sept-2004 HMM File Created.
 * =============================================================================
 */
#include <soc.h>
#include <csl_tmr.h>

/** ============================================================================
 *   @n@b CSL_tmrGetBaseAddress
 *
 *   @b Description
 *   @n  This function gets the base address of the given gptimer
 *       instance.
 *
 *   @b Arguments
 *   @verbatim
            tmrNum        Specifies the instance of the gptimer to be opened

            pTmrParam     Gptimer module specific parameters

            pBaseAddress  Pointer to base address structure containing base
                          address details
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li					CSL_OK             Successful on getting the base 
 *                                             address of timer
 *   @li					CSL_ESYS_FAIL      gptimer instance is not
 *                                             available.
 *   @li                    CSL_ESYS_INVPARAMS Invalid Parameters
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 *
 *   @b Example
 *   @verbatim
        CSL_Status            status;
        CSL_TmrBaseAddress    baseAddress;

        ...
        status = CSL_tmrGetBaseAddress(CSL_TMR_1, NULL, &baseAddress);
        ...

    @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_tmrGetBaseAddress, ".text:csl_section:tmr");
CSL_Status CSL_tmrGetBaseAddress (
    CSL_InstNum 	      tmrNum,
    CSL_TmrParam          *pTmrParam,
    CSL_TmrBaseAddress    *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (tmrNum) {
            case CSL_TMR_0:
                pBaseAddress->regs = (CSL_TmrRegsOvly)CSL_TMR_0_REGS;
                break;

            case CSL_TMR_1:
                pBaseAddress->regs = (CSL_TmrRegsOvly)CSL_TMR_1_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_TmrRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

