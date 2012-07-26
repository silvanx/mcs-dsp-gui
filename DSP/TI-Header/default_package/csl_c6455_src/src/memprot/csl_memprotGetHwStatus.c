/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */
  
/** ============================================================================
 *   @file  csl_memprotGetHwStatus.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotGetHwStatus ()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 *
 *  16-Nov-2005  ds  Updated the documentation
 * =============================================================================
 */

#include <csl_memprot.h>
#include <csl_memprotAux.h>

/** ===========================================================================
 *   @n@b CSL_memprotGetHwStatus
 *
 *   @b Description
 *   @n This function is used to read the current module configuration, status
 *      flags and the value present associated registers. User should allocate
 *      memory for the said data type and pass its pointer as an unadorned
 *      void*  argument to the status query call. For details about the various
 *      status queries supported and the associated data structure to record
 *      the response refer to @a CSL_MemprotHwStatusQuery
 *
 *   @b Arguments
 *   @verbatim
            hMemprot        Handle to the MEMPROT instance

            query           The query to this API of MEMPROT which indicates
                            the status to be returned.

            response        Placeholder to return the status.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *   @li                    CSL_ESYS_INVQUERY   - Invalid Query
 *
 *   <b> Pre Condition </b>
 *       Both @a CSL_memprotInit() and @a CSL_memprotOpen() must be called
 *       successfully in that order before @a CSL_memprotGetHwStatus() can be
 *       called. For the argument type that can be @a void* casted & passed
 *       with a particular command refer to @a CSL_MemprotHwStatusQuery
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Third parameter "response" value
 *
 *   @b Example
 *   @verbatim
        #define PAGE_ATTR 0xFFF0
        
        Uint16 pageAttrTable[10] = {PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,
                 PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR};
        Uint32 key[2] = {0x11223344,0x55667788};
        CSL_MemprotObj mpL2Obj;
        CSL_MemprotHandle hmpL2;
        CSL_Status status;
        CSL_MemprotHwSetup L2MpSetup,L2MpGetSetup;
        CSL_MemprotLockStatus lockStat;
        CSL_MemprotPageAttr pageAttr;
        CSL_MemprotFaultStatus queryFaultStatus;

        // Initializing the module
        CSL_memprotInit(NULL);

        // Opening the Handle for the L2
        hmpL2 = CSL_memprotOpen(&mpL2Obj,CSL_MEMPROT_L2,NULL,&status);
        L2MpSetup. memPageAttr = pageAttrTable;
        L2MpSetup.numPages = 10;
        L2MpSetup.key = key;

        // Do Setup for the L2 Memory protection/
        CSL_memprotHwSetup  (hmpL2,&L2MpSetup);

        // Query Lock Status
        CSL_memprotGetHwStatus(hmpL2,CSL_MEMPROT_QUERY_LOCKSTAT,&lockStat);

     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_memprotGetHwStatus, ".text:csl_section:memprot") 
CSL_Status CSL_memprotGetHwStatus (
    CSL_MemprotHandle         hMemprot,
    CSL_MemprotHwStatusQuery  query,
    void                      *response
)
{
    CSL_Status status = CSL_SOK;
    
    if (hMemprot == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        switch (query) {
            case CSL_MEMPROT_QUERY_FAULT:
                CSL_memprotGetFaultStatus(hMemprot,
                                      (CSL_MemprotFaultStatus *)response);
                break;

            case CSL_MEMPROT_QUERY_PAGEATTR:
                ((CSL_MemprotPageAttr *)response)->attr = 
                              CSL_memprotGetPageAttr(hMemprot, 
                                    ((CSL_MemprotPageAttr*)response)->page);
                break;

            case CSL_MEMPROT_QUERY_LOCKSTAT:
                *((CSL_MemprotLockStatus *)response) = 
                                            CSL_memprotGetLockStat(hMemprot);
                break;

            default:
                status = CSL_ESYS_INVQUERY ;
        }
    }
    return status;
}
