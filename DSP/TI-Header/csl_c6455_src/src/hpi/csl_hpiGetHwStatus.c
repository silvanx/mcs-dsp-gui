/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiGetHwStatus.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiGetHwStatus()
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  06-Feb-2006 ds  Removed CSL_HPI_QUERY_PID_REV, CSL_HPI_QUERY_PID_TYPE and
 *                  CSL_HPI_QUERY_PID_CLASS
 *
 * =============================================================================
 */
#include <csl_hpi.h>
#include <csl_hpiAux.h>

/** ============================================================================
 *   @n@b CSL_hpiGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of the different operations of HPI.
 *
 *   @b Arguments
 *   @verbatim
            hHpi         Handle to the HPI instance

            query         The query to this API of HPI which indicates the
                          status to be returned.

            response      Placeholder to return the status.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Query successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVQUERY   - The Query passed is invalid
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *  
 *   <b> Pre Condition </b>
 *   @n  CSL_hpiInit() and CSL_hpiOpen() must be called successfully in order 
 *       before calling CSL_hpiGetHwStatus().
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Third parameter response vlaue
 *
 *   @b Example
 *   @verbatim
        CSL_HpiHandle          hHpi;
        CSL_HpiHwStatusQuery   query;
        void                   reponse;

        status = CSL_hpiGetHwStatus(hHpi, query, &response);

     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_hpiGetHwStatus, ".text:csl_section:hpi");
CSL_Status CSL_hpiGetHwStatus (
    CSL_HpiHandle           hHpi,
    CSL_HpiHwStatusQuery    query,
    void                    *response
)
{
    CSL_Status status = CSL_SOK;

    if (hHpi == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (query) {
           case CSL_HPI_QUERY_HRDY:
               CSL_hpiGetHpicHrdy(hHpi,response);
               break;

           case CSL_HPI_QUERY_FETCH:
               CSL_hpiGetHpicFetch(hHpi,response);
               break;

           case CSL_HPI_QUERY_HPI_RST:
               CSL_hpiGetHpicHpiRst(hHpi,response);
               break;

           case CSL_HPI_QUERY_HWOB_STAT:
               CSL_hpiGetHpicHwobStat(hHpi,response);
               break;

           default:
                status = CSL_ESYS_INVQUERY ;    
        }
    }

    return (status);
}

