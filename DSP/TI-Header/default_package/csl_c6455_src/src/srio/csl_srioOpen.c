/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 *  ===========================================================================
 */
/** ============================================================================
 * @file csl_srioOpen.c
 *
 * @brief File for functional layer of CSL API CSL_srioOpen()
 * 
 * @Path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioOpen() function definition and it's associated functions. 
 * ============================================================================
 */
/* ============================================================================
 * Revision History
 * ===============
 * 29-Aug-2005 PSK File Created.
 * ============================================================================
 */
#include <csl_srio.h>

/** ============================================================================
 *   @n@b CSL_srioOpen
 *
 *   @b Description
 *   @n This function populates the peripheral data object for the SRIO instance
 *      and returns a handle to the instance. This handle is passed to all other
 *      CSL APIs.
 *
 *   @b Arguments
 *   @verbatim
            pSrioObj          Pointer to SRIO object.

            srioNum          Instance of SRIO CSL to be opened.
                             There is one instance of the SRIO
                             available. So, the value for this parameter will be
                             CSL_SRIO always.
 
            pSrioParam       Module specific parameters.

            pStatus          Status of the function call
     @endverbatim
 * 
 *   <b> Return Value </b>  CSL_SrioHandle
 *   @n                         Valid SRIO handle will be returned if
 *                              status value is equal to CSL_SOK, otherwise NULL
 *                              is returned.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK            - Valid SRIO handle is returned
 *   @li            CSL_ESYS_FAIL      - The SRIO instance is invalid
 *   @li            CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *        2.    SRIO object structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. SRIO object structure
 *
 *   @b Example
 *   @verbatim
            CSL_status     status;
            CSL_SrioObj    srioObj;
            CSL_SrioHandle hSrio;
            ...   
            hSrio = CSL_srioOpen(&srioObj, CSL_SRIO, NULL, &status);
            ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_srioOpen, ".text:csl_section:srio");
CSL_SrioHandle CSL_srioOpen (
    CSL_SrioObj      *pSrioObj, 
    CSL_InstNum      srioNum, 
    CSL_SrioParam    *pSrioParam, 
    CSL_Status       *pStatus
)
{
    CSL_SrioHandle         hSrio = (CSL_SrioHandle)NULL;
    CSL_SrioBaseAddress    baseAddress;

    if (pStatus == NULL) {
        /* do nothing : module handle is already initialized to NULL */
    }
    else if (pSrioObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        *pStatus = CSL_srioGetBaseAddress(srioNum, pSrioParam, &baseAddress);

        if (*pStatus == CSL_SOK) {
            pSrioObj->regs = baseAddress.regs;
            pSrioObj->perNum = (CSL_InstNum)srioNum;
            hSrio = (CSL_SrioHandle)pSrioObj;
        }
        else {
            pSrioObj->regs = (CSL_SrioRegsOvly)NULL;
            pSrioObj->perNum = (CSL_InstNum)-1;
        }
    }
    return (hSrio);
}

