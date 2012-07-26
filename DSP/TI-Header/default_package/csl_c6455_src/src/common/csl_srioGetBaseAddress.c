/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */
/** ============================================================================
 *   @file  csl_srioGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_srioGetBaseAddress
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  25-Aug-2005 PSK File Created.
 * =============================================================================
 */
#include <soc.h>
#include <csl_srio.h>

/** ============================================================================
 *   @n@b CSL_SrioGetBaseAddress
 *
 *   @b Description
 *   @n  This function gets the base address of the given SRIOinstance.
         This function is used for getting the base address of the peripheral
 *       instance. This function will be called inside the CSL_srioOpen()
 *       function call. This function is open for re-implementing if the user
 *       wants to modify the base address of the peripheral object to point to
 *       a different location and there by allow CSL initiated write/reads into
 *       peripheral. MMR's go to an alternate location.
 *   
 *   @b Arguments
 *   @verbatim
            srioNum        Specifies the instance of the SRIO to be opened

            pSrioParam     SRIO module specific parameters

            pBaseAddress   Pointer to base address structure containing base
                           address details
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li					CSL_OK             Successful on getting the base 
 *                                             address of srio
 *   @li					CSL_ESYS_FAIL      SRIO instance is not
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
        CSL_Status          status;
        CSL_SrioBaseAddress baseAddress;

        ...
        
        status = CSL_SrioGetBaseAddress(CSL_SRIO, NULL, &baseAddress);

        ...
    @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_srioGetBaseAddress, ".text:csl_section:srio");
CSL_Status CSL_srioGetBaseAddress (
    CSL_InstNum 	       srioNum,
    CSL_SrioParam          *pSrioParam,
    CSL_SrioBaseAddress    *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (srioNum) {
            case CSL_SRIO:
                pBaseAddress->regs = (CSL_SrioRegsOvly)CSL_SRIO_0_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_SrioRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

