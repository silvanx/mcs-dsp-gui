/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspGetHwStatus.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspGetHwStatus()
 *
 */

/* =============================================================================
 * Revision History
 * ================
 *  June 29,2004  Pratheesh Gangadhar - Created
 *  Oct  27, 2005 ds  - Removed CSL_MCBSP_QUERY_PID query
 *  Feb 02, 2006  ds  - Removed CSL_MCBSP_QUERY_TX_INT_MODE and 
 *                      CSL_MCBSP_QUERY_TX_INT_MODE queries
 * =============================================================================
 */ 
#include <csl_mcbsp.h>
#include <_csl_mcbsp.h>
#include <csl_mcbspAux.h>

/** ============================================================================
 *   @n@b CSL_mcbspGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of different operations or some setup-parameters of 
 *      MCBSP.The status is returned through the third parameter.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            myQuery         Query command
            
            response        Response from the query. Pointer to appropriate
                            object corresponding to the query command needs 
                            to be passed here
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status 
 *   @li                    CSL_SOK            - Query successful
 *   @li                    CSL_ESYS_INVQUERY  - The Query passed is invalid
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *   @li                    CSL_ESYS_INVPARAMS - Invalid Parameter
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspGetHwStatus() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *       
 *   @b Modifies
 *   @n Third parameter response vlaue
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle     hMcbsp;
            CSL_Status          status;
            Uint16              response;
            ...
            status = CSL_mcbspGetHwStatus(hMcbsp,
                                         CSL_MCBSP_QUERY_DEV_STATUS,
                                         &response);
            
            if (response & CSL_MCBSP_RRDY)
            {
                // Receiver is ready to with new data
                ...
            }
            ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspGetHwStatus, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspGetHwStatus (
    CSL_McbspHandle                hMcbsp,
    CSL_McbspHwStatusQuery         myQuery,
    void                           *response
)
{
    CSL_Status status = CSL_SOK;

    if (hMcbsp == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if(response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(myQuery) {
            case CSL_MCBSP_QUERY_CUR_RX_BLK:
                  CSL_mcbspGetCurRxBlk (hMcbsp, response);
                  break;
    
            case CSL_MCBSP_QUERY_CUR_TX_BLK:
                  CSL_mcbspGetCurTxBlk (hMcbsp, (CSL_BitMask16 *)response);
                  break;
    
            case CSL_MCBSP_QUERY_DEV_STATUS:
                  CSL_mcbspGetDevStatus (hMcbsp, (CSL_BitMask16 *)response);
                  break;
    
            case CSL_MCBSP_QUERY_TX_RST_STAT:
                  CSL_mcbspGetTxRstStat (hMcbsp, response);
                  break;
    
            case CSL_MCBSP_QUERY_RX_RST_STAT:
                 CSL_mcbspGetRxRstStat (hMcbsp, response);
                 break;
            
            default:
                status = CSL_ESYS_INVQUERY;
                break;
        }
    }
    
    return(status);
}

