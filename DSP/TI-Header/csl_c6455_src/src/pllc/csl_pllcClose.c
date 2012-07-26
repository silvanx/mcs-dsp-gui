/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_pllcClose.c
 *
 *  @brief File for functional layer of CSL API @a CSL_pllcClose()
 *
 *  @path \(CSLPATH)\src\pllc
 *
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  10-Feb-2004 kpn CSL3X Upgradation.
 *  ============================================================================
 */

#include <csl_pllc.h>

/** ============================================================================
 *   @n@b CSL_pllcClose
 *
 *   @b Description
 *   @n This function closes the specified instance of PLLC.
 *
 *   @b Arguments
 *   @verbatim
            hPllc            Handle to the pllc
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1. PLLC instance is closed and its usage is
 *           illegal until next open
 *
 *
 *   @b Modifies
 *   @n    1. PLLC object structure
 *
 *   @b Example
 *   @verbatim
            CSL_PllcHandle   hPllc;
            CSL_status       status;
            ...

            status = CSL_pllcClose(hPllc);
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcClose, ".text:csl_section:pllc");
CSL_Status CSL_pllcClose (
    CSL_PllcHandle         hPllc
)
{
    CSL_Status status;

    if (hPllc != NULL) {
        hPllc->regs     = (CSL_PllcRegsOvly)NULL;
        hPllc->pllcNum  = (CSL_InstNum)-1;
        status          = CSL_SOK;
    }
    else {
        status = CSL_ESYS_BADHANDLE;
    }

    return status;
}

