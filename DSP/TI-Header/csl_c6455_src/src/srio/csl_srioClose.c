/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================ 
 */
/** ===========================================================================
 * @file csl_srioClose.c
 *
 * @brief File for functional layer of CSL API CSL_srioClose() 
 * 
 * @path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioClose() function definition and it's associated functions
 * ============================================================================      
 */
/* ============================================================================
 * Revision History
 * ===============
 * 25-Aug-2005 PSK File Created.
 * ============================================================================
 */
#include <csl_srio.h>

/** ===========================================================================
 *   @n@b csl_srioClose.c
 *
 *   @b Description
 *   @n This function closes the specified instance of SRIO.
 *
 *   @b Arguments
 *   @verbatim
            hSrio         handle to the SRIO
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - SRIO is closed
 *                                               successfully
 *
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *   
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
 *          CSL_SrioHandle hSrio;
 *          CSL_Status     status;
 *          ...
 *          status = CSL_srioClose(hSrio);
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_srioClose, ".text:csl_section:srio");
CSL_Status CSL_srioClose (
    CSL_SrioHandle hSrio
)
{
    CSL_Status status = CSL_SOK;

    if (hSrio != NULL) {
        hSrio->regs = (CSL_SrioRegsOvly)NULL;
        hSrio->perNum = (CSL_InstNum)-1;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }
    return (status);
}

