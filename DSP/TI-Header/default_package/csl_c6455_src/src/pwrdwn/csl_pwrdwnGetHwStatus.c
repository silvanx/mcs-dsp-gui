/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_pwrdwnGetHwStatus.c
 *
 *   @path  $(CSLPATH)\src\pwrdwn
 *
 *   @desc  File for functional layer of CSL API CSL_pwrdwnGetHwStatus ()
 *
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 * =============================================================================
 */
 
#include <csl_pwrdwn.h>
#include <csl_pwrdwnAux.h>

/** ===========================================================================
 *   @n@b CSL_pwrdwnGetHwStatus
 *
 *   @b Description
 *   @n This function is used to get the value of various parameters of the
 *      PWRDWN instance. The value returned depends on the query passed.
 *
 *   @b Arguments
 *   @verbatim
            hPwr            Handle to the PWRDWN instance

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
 *   @li                    CSL_ESYS_INVPARAMS - Invalid Parameters.
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_pwrdwnInit(), CSL_pwrdwnOpen() must be opened prior to this call
 *
 *   <b> Post Condition </b>
 *       Data requested by the query is returned through the variable "response"
 *
 *   @b Modifies
 *   @n The input arguement "response" is modified
 *
 *   @b Example:
     @verbatim
            CSL_PwrdwnObj pwrObj;
            CSL_PwrdwnHwSetup pwrSetup;
            CSL_PwrdwnHandle hPwr;
            CSL_PwrdwnPortData pageSleep;

            pageSleep.portNum = 0x0;

            // Init Module
            ...
            if (CSL_pwrdwnInit(NULL) != CSL_SOK)
                exit;
            // Opening a handle for the Module  
            hPwr = CSL_pwrdwnOpen (&pwrObj, CSL_PWRDWN, NULL, NULL);
    
            // Setup the arguments for the Setup structure
            ...
    
            // Setup
            CSL_pwrdwnHwSetup(hPwr,&pwrSetup);
    
            // Hw Status Query
            CSL_pwrdwnGetHwStatus(hPwr,CSL_PWRDWN_QUERY_PAGE0_STATUS, 
                                  &pageSleep);
    
            // Close handle
            CSL_pwrdwnClose(hPwr);
   @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_pwrdwnGetHwStatus, ".text:csl_section:pwrdwn");
CSL_Status CSL_pwrdwnGetHwStatus (
    CSL_PwrdwnHandle        hPwrdwn,
    CSL_PwrdwnHwStatusQuery query,
    void                    *response
)
{

    CSL_Status status = CSL_SOK;
    
    if (hPwrdwn == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        switch (query) {
            case CSL_PWRDWN_QUERY_PAGE0_STATUS:
                CSL_pwrdwnGetPage0SleepStatus(hPwrdwn, \
                                              (CSL_PwrdwnPortData *)response);
                break;

            case CSL_PWRDWN_QUERY_PAGE1_STATUS:
                CSL_pwrdwnGetPage1SleepStatus(hPwrdwn, \
                                              (CSL_PwrdwnPortData *)response);
                break;

            default:
                status = CSL_ESYS_INVQUERY ;
                break;
        }
    }
    return status;
}
