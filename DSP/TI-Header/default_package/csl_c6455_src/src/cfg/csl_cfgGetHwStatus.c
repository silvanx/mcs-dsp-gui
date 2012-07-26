/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */
  
/** ============================================================================
 *   @file  csl_cfgGetHwStatus.c
 *
 *   @path  $(CSLPATH)\src\cfg
 *
 *   @desc  File for functional layer of CSL API CSL_cfgGetHwStatus()
 *
 */

/* ============================================================================
 * Revision History
 *  ===============
 *  14-Apr-2005 Brn File Created
 * ============================================================================
 */

#include <csl_cfg.h>
#include <csl_cfgAux.h>

/** ============================================================================
 *   @n@b CSL_cfgGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of the different operations of CFG.
 *
 *   @b Arguments
 *   @verbatim
            hCfg          Handle to the CFG instance

            query         The query to this API of CFG which indicates the
                          status to be returned.

            response      Placeholder to return the status.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful
 *   @li                    CSL_ESYS_INVQUERY   - Invalid query command
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_cfgInit() and CSL_cfgOpen() must be called successfully in 
 *       that order before CSL_cgfGetHwStatus () can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_CfgHandle          hCfg;
        Uint32                 reponse;
        CSL_Status             status;
        ...
        status = CSL_GetcfgHwStatus(hCfg, CSL_CFG_QUERY_FAULT_ADDR, &response);
        ...
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_cfgGetHwStatus, ".text:csl_section:cfg")
CSL_Status CSL_cfgGetHwStatus (
    CSL_CfgHandle         hCfg,
    CSL_CfgHwStatusQuery  query,
    void                  *response
)
{
    CSL_Status status = CSL_SOK;

    if (hCfg == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }

    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        switch (query) {
            case CSL_CFG_QUERY_FAULT_ADDR:
                CSL_cfgGetFaultAddr(hCfg, (Uint32 *)response);
                break;

            case CSL_CFG_QUERY_FAULT_STATUS:
                CSL_cfgGetFaultStat(hCfg, (CSL_CfgFaultStatus *)response);
                break;

            default:
                status = CSL_ESYS_INVQUERY ;
                break;
        }
    }         
    return status;
}
