/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3GetHwChannelStatus.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API CSL_edma3GetHwChannelStatus()
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
 *   @n@b CSL_edma3GetHwChannelStatus
 *
 *   @b Description
 *   @n Gets the status of the different operations or the current setup of EDMA  
 *      module.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            myQuery         Query to be performed
            
            response        Pointer to buffer to return the data requested by
                            the query passed
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Get the edma channel status
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVQUERY   - The query passed is invalid 
 *                                                
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen()
 *       must be called successfully in that order before this API can be 
 *       invoked.If a Shadow region is used then care of the DRAE settings
 *       must be taken
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
            CSL_Edma3HwSetup            hwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3ChannelObj         chObj;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = \
                                            CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Status                  status;
            Bool                        errStat;
           
        
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = NULL;
            CSL_edma3HwSetup(hModule,&hwSetup);
         
            // Channel 0 Open in context of Shadow region 0
            chAttr.regionNum = CSL_EDMA3_REGION_0;
            chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
            hChannel = CSL_edma3ChannelOpen(&chObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
        
            
            // Enable Channel(  .. ) 
           CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE,NULL);
        
            // Obtain Channel Error Status
            CSL_edma3GetHwChannelStatus(hChannel,CSL_EDMA3_QUERY_CHANNEL_ERR, \
                                        errStat);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3GetHwChannelStatus, ".text:csl_section:edma3");
CSL_Status  CSL_edma3GetHwChannelStatus (
    CSL_Edma3ChannelHandle             hEdma,
    CSL_Edma3HwChannelStatusQuery      myQuery,
    void                               *response
)
{
    CSL_Status status = CSL_SOK;
    
    if (hEdma == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(myQuery) {
            case CSL_EDMA3_QUERY_CHANNEL_STATUS:    
                status = CSL_Edma3GetChannelStatus(hEdma,(Bool*)response);
                break;
                
            case CSL_EDMA3_QUERY_CHANNEL_ERR:     
                status = CSL_Edma3GetChannelErrStatus(hEdma, \
                                               (CSL_Edma3ChannelErr*)response);
                break;
                
            default:
                status = CSL_ESYS_INVQUERY;
                break;
        }
    }

    return (status);
}

