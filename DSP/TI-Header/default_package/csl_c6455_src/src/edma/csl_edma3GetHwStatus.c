/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3GetHwStatus.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API @a CSL_edma3GetHwStatus()
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  29-May-2004 Ruchika Kharwar File Created.
 *
 * =============================================================================
 */

#include <csl_edma3.h>
#include <csl_edma3Aux.h>

/** ============================================================================
 *   @n@b CSL_edma3GetHwStatus
 *
 *   @b Description
 *   @n Gets the status of the different operations or the current setup of EDMA 
 *      module.
 *
 *   @b Arguments
 *   @verbatim
            hMod            Edma module handle
 
            myQuery         Query to be performed
            
            response        Pointer to buffer to return the data requested by
                            the query passed
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Get the status of edma 
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVQUERY   - The query passed is invalid 
 *   @li                    CSL_ESYS_INVPARAMS  - The parameter passed is 
 *                                                invalid
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() must be called successfully 
 *       in that order before this API can be invoked.argument type that can be
 *       void* casted & passed with a particular command refer to 
 *       CSL_Edma3HwStatusQuery
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The input arguement "response" is modified
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup,gethwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3QueryInfo          info;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = \
                                            CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwDmaChannelSetup  getdmahwSetup[CSL_EDMA3_NUM_DMACH];
            
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = NULL;
            CSL_edma3HwSetup(hModule,&hwSetup);
            
            // Query Module Info 
            CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INFO,&info);  
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3GetHwStatus, ".text:csl_section:edma3");
CSL_Status  CSL_edma3GetHwStatus (
    CSL_Edma3Handle                hMod,
    CSL_Edma3HwStatusQuery         myQuery,
    void                           *response
)
{
    CSL_Status status = CSL_SOK;
    
    if (hMod == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(myQuery) {
#if CSL_EDMA3_MEMPROTECT        
            case CSL_EDMA3_QUERY_MEMFAULT:  
                status = CSL_edma3GetMemoryFaultError(hMod, \
                                             (CSL_Edma3MemFaultStat*)response);
                break;  
            case CSL_EDMA3_QUERY_MEMPROTECT:    
                ((CSL_Edma3CmdRegion*)response)->regionVal = \
                    CSL_edma3GetMemoryProtectionAttrib(hMod, \
                                      ((CSL_Edma3CmdRegion*)response)->region);
                break;              
#endif              
            case CSL_EDMA3_QUERY_CTRLERROR: 
                status = CSL_edma3GetControllerError(hMod, \
                                              (CSL_Edma3CtrlErrStat*)response);
                break;          
            case CSL_EDMA3_QUERY_INTRPEND:  
                status = CSL_edma3GetIntrPendStatus(hMod, \
                                       ((CSL_Edma3CmdIntr*)response)->region, \
                                       &((CSL_Edma3CmdIntr*)response)->intr, \
                                       &((CSL_Edma3CmdIntr*)response)->intrh );
                break;          
            
            case CSL_EDMA3_QUERY_EVENTMISSED:   
                status = \
                CSL_edma3GetEventMissed(hMod,&((CSL_BitMask32*)response)[0],\
                                        &((CSL_BitMask32*)response)[1], \
                                        &((CSL_BitMask32*)response)[2]);
                break;   
            case CSL_EDMA3_QUERY_QUESTATUS: 
                status = \
                CSL_edma3GetQueStatus(hMod,((CSL_Edma3QueStat*)response)->que,\
                                     ((CSL_Edma3QueStat*)response));
                break;  
            case CSL_EDMA3_QUERY_ACTIVITY:
                status = \
                CSL_edma3GetActivityStatus(hMod,\
                                           ((CSL_Edma3ActivityStat*)response));
                break;
            case  CSL_EDMA3_QUERY_INFO:
                status = CSL_edma3GetInfo(hMod,((CSL_Edma3QueryInfo*)response));
                break;
            default:
                status = CSL_ESYS_INVQUERY;
                break; 
        }  
    }

    return (status);
}

