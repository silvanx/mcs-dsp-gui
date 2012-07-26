/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_pllcGetHwStatus.c
 *
 *  @brief   File for functional layer of CSL API @a CSL_pllcGetHwStatus()
 *
 *  Path: \(CSLPATH)\src\pllc
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  25-Aug-2005 Tej File Created.
 *  27-oct-2005 sd  changes for multiplier configuration
 *  18-Jan-2006 sd  Changes according to spec changes
 *  ============================================================================
 */

#include <csl_pllc.h>
#include <csl_pllcAux.h>

/** ============================================================================
 *   @n@b CSL_pllcGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of the different operations of PLLC.
 *
 *   @b Arguments
 *   @verbatim
            hPllc         Handle to the PLLC instance

            query         The query to this API of PLLC which indicates the
                          status to be returned.

            response      Placeholder to return the status.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVQUERY   - Invalid query command
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle          hPllc;
        CSL_PllcHwStatusQuery   query = CSL_PLLC_QUERY_STATUS;
        CSL_BitMask32           reponse;
        ...

        status = CSL_pllcGetHwStatus (hPllc, query, &response);
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcGetHwStatus, ".text:csl_section:pllc");
CSL_Status CSL_pllcGetHwStatus (
    CSL_PllcHandle                hPllc,
    CSL_PllcHwStatusQuery         query,
    void                         *response
)
{
    CSL_Status status = CSL_SOK;

    if (hPllc == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (query) {
            /* Query for GOSTAT bit in PLLSTAT register*/
            case CSL_PLLC_QUERY_STATUS:
                *(CSL_BitMask32*) response = CSL_pllcGetStatus (hPllc);
                break;
            /* Query for SYSnOn bits SYSSTAT register*/
            case CSL_PLLC_QUERY_SYSCLKSTAT:
                *(CSL_BitMask32*) response = CSL_pllcGetSysClkStatus (hPllc);
                break;
            /* Query for status of RSTYPE register*/
            case CSL_PLLC_QUERY_RESETSTAT:
    			if (hPllc->pllcNum == CSL_PLLC_1) 
    	            *(CSL_BitMask32*) response = CSL_pllcGetResetStatus (hPllc);
    			else
    				status = CSL_ESYS_INVPARAMS;
                break;
            default:
               status = CSL_ESYS_INVQUERY;
               break;
        }
    }

    return status;
}

