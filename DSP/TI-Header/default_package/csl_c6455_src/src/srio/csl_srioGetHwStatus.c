/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */
/** ===========================================================================
 * @file csl_srioGetHwStatus.c
 *
 * @brief File for functional layer of CSL API CSL_srioGetHwStatus()
 * 
 * @path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioGetHwStatus() function definition and it's associated
 *       functions 
 * ============================================================================
 */
/* ============================================================================
 * Revision History
 * ===============
 * 24-Aug-2005 PSK File Created.
 * ============================================================================
 */
#include <csl_srio.h>
#include <csl_srioAux.h>

/** ===========================================================================
 *   @n@b CSL_srioGetHwStatus
 *
 *   @b Description
 *   @n This function is used to get the value of various parameters of the
 *      SRIO instance. The value returned depends on the query passed.
 *
 *   @b Arguments
 *   @verbatim
            hSrio           Handle to the SRIO instance

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
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *       Data requested by the query is returned through the variable 
 *       "response"
 *
 *   @b Modifies
 *   @n  The input arguement "response" is modified
 *
 *   @b Example
 *   @verbatim
         CSL_Status        status;
         CSL_SrioHandle    hSrio;
         CSL_SrioPidNumber response; 
         ...
         
         Status=CSL_srioGetHwStatus(hSrio, CSL_SRIO_QUERY_PID_NUMBER, 
                                    &response);
         
         ...
     @endverbatim
 * ===========================================================================
 */ 
#pragma CODE_SECTION (CSL_srioGetHwStatus, ".text:csl_section:srio");
CSL_Status CSL_srioGetHwStatus (
    CSL_SrioHandle        hSrio,
    CSL_SrioHwStatusQuery query,
    void                  *response
)
{
    CSL_Status status = CSL_SOK;

    if (hSrio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (query) {
            /* queries SRIO Peripheral Identification number */
            case CSL_SRIO_QUERY_PID_NUMBER:
                CSL_srioGetPid(hSrio, (CSL_SrioPidNumber *)response);
                break;

            /* Gets global enable status */
            case CSL_SRIO_QUERY_GBL_EN_STAT:
                CSL_srioGetGblEnStat(hSrio, (Uint32 *)response);
                break;

            /* Gets block enable status for all the blocks */
            case CSL_SRIO_QUERY_BLK_EN_STAT:
                 CSL_srioGetBlkEnStat(hSrio, (CSL_SrioBlkEn *)response);
                break;

            /* Get doorbell  interrupts status */
            case CSL_SRIO_QUERY_DOORBELL_INTR_STAT:
                CSL_srioGetDoorbellIntrStat(hSrio, 
                                            (CSL_SrioPortData *)response);
                break;

            /* Get the LSU interrupts status */
            case CSL_SRIO_QUERY_LSU_INTR_STAT:
                CSL_srioGetLsuIntrStat(hSrio, (Uint32 *)response); 
                break;

            /* Gets  Error, Reset, and Special Event interrupts status */
            case CSL_SRIO_QUERY_ERR_RST_INTR_STAT:
                CSL_srioGetErrRstIntrStat(hSrio, (Uint32 *)response); 
                break;

            /* Get status of LSU interrupts decode for DST 0 */
            case CSL_SRIO_QUERY_LSU_INTR_DECODE_STAT:
                CSL_srioGetLsuIntrDecodeStat(hSrio, (Uint32 *)response);
                break;

            /* Get Error, Reset, and Special Event interrupts decode 
             * status for DST 0 
             */
            case CSL_SRIO_QUERY_ERR_INTR_DECODE_STAT:
                CSL_srioGetErrIntrDecodeStat(hSrio, (Uint32 *)response);
                break;

            /* Gets the status of the pending command of LSU 
             * registers for a particular port  
             */
            case CSL_SRIO_QUERY_LSU_COMP_CODE_STAT:
                CSL_srioLsuCompCodeStat(hSrio, 
                                        (CSL_SrioLsuCompStat *)response); 
                break;

            /* Gets status of the command registers of LSU module 
             * for a particular port 
             */
            case CSL_SRIO_QUERY_LSU_BSY_STAT:
                CSL_srioLsuBsyStat(hSrio, (CSL_SrioPortData *)response);
                break;

            /* Gets the type of device (Vendor specific) */
            case CSL_SRIO_QUERY_DEV_ID_INFO:
                CSL_srioGetDevIdInfo(hSrio, (CSL_SrioDevInfo *)response);
                break;

            /* Gets vendor specific assembly information */
            case CSL_SRIO_QUERY_ASSY_ID_INFO:
                CSL_srioGetAssyIdInfo(hSrio, (CSL_SrioAssyInfo *)response);
                break;

            /* Gets processing element features  */
            case CSL_SRIO_QUERY_PE_FEATURE:
                CSL_srioGetPeFeature(hSrio, (Uint32 *)response);
                break;

            /* Get source operations CAR status */
            case CSL_SRIO_QUERY_SRC_OPERN_SUPPORT:
                CSL_srioGetSrcOpernSuppStat(hSrio, (Uint32 *)response);
                break;

            /* Get destination operations CAR status */
            case CSL_SRIO_QUERY_DST_OPERN_SUPPORT:
                CSL_srioGetDstOpernSuppStat(hSrio, (Uint32 *)response);
                break;

            /* Get local configuration space base addresses */
            case CSL_SRIO_QUERY_LCL_CFG_BAR:
                CSL_srioGetLclCfgBar(hSrio, (CSL_SrioLongAddress *)response);
                break;

            /* Get status of SP_LM_RESP register fields */
            case CSL_SRIO_QUERY_SP_LM_RESP_STAT:
                CSL_srioGetSpLmRespStat(hSrio, (CSL_SrioPortData *)response);
                break;

            /* Get status of SP_ACKID_STAT register fields */
            case CSL_SRIO_QUERY_SP_ACKID_STAT:
                CSL_srioGetSpAckIdStat(hSrio, (CSL_SrioPortData *)response);
                break;

            /* Get status of SP_ERR_STAT register fields */
            case CSL_SRIO_QUERY_SP_ERR_STAT:
                CSL_srioGetSpErrStat(hSrio, (CSL_SrioPortData *)response);
                break;

            /* Gets SP_CTL register status fields */
            case CSL_SRIO_QUERY_SP_CTL:
                CSL_srioGetSpCtlStat(hSrio, (CSL_SrioPortData *)response);  
                break;

            /* Get the status of logical/transport layer errors */
            case CSL_SRIO_QUERY_LGCL_TRNS_ERR_STAT:
                CSL_SrioGetLgclTrnsErrStat(hSrio, (Uint32 *)response); 
                break;

            /* Get captured  error info of logical/transport layer */
            case CSL_SRIO_QUERY_LGCL_TRNS_ERR_CAPT:
                CSL_srioGetLgclTransErrCapt(hSrio, 
                                            (CSL_SrioLogTrErrInfo *)response);
                break;

            /* Get status of port error detect CSR fields */
            case CSL_SRIO_QUERY_SP_ERR_DET_STAT:
                CSL_srioGetSpErrDetStat(hSrio, (CSL_SrioPortData *)response); 
                break;

            /* Get the  port  error captured information */
            case CSL_SRIO_QUERY_PORT_ERR_CAPT:
                CSL_srioGetPortErrCapt(hSrio, (CSL_SrioPortErrCapt *)response); 
                break;

            /* Get port control independent register fields status */
            case CSL_SRIO_QUERY_SP_CTL_INDEP:
                CSL_srioGetSpCtlIndepStat(hSrio, (CSL_SrioPortData *)response);
                break;

            /* Get the port write capture information */
            case CSL_SRIO_QUERY_PW_CAPTURE:
                CSL_srioGetPwCapt(hSrio, (CSL_SrioPortWriteCapt *)response);
                break;

            /* Reads the count of the number of transmission 
             * errors that have occurred 
             */
            case CSL_SRIO_QUERY_ERR_RATE_CNTR_READ:
                CSL_srioErrRateCounterRead(hSrio, 
                                           (CSL_SrioPortData *)response);
                break;

            /* Reads the peak value of the error rate counter */
            case CSL_SRIO_QUERY_PEAK_ERR_RATE_READ:
                CSL_srioErrRatePeakRead(hSrio, (CSL_SrioPortData *)response);
                break;

            default:
                status = CSL_ESYS_INVQUERY;
                break;
        }
    }
    return (status);
}

