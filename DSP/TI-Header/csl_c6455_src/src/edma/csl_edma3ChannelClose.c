/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3ChannelClose.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  EDMA3 CSL Implementation on DSP side
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

/** ============================================================================
 *   @n@b csl_edma3ChannelClose.c
 *
 *   @b Description
 *   @n This function marks the channel cannot be accessed anymore using 
 *      the handle. CSL for the EDMA channel need to be reopened before using 
 *      any edma channel.
 *      
 *   @b Arguments
 *   @verbatim
            hEdma           Handle to the requested channel 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Edma channel is closed successfully.
 *                                    
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open(), CSL_edma3ChannelOpen()
 *       must be invoked successfully in that order before this API can 
 *       be invoked.
 *
 *   <b> Post Condition </b>
 *   @n  The edma channel related CSL APIs can not be called until the edma 
 *       channel is reopened again using CSL_edma3ChannelOpen() 
 *
 *   @b Modifies
 *   @n CSL_Edma3ChannelObj structure values
 *            
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle         hModule;
            CSL_Edma3HwSetup        hwSetup;
            CSL_Edma3Obj            edmaObj;
            CSL_Edma3ChannelObj     chObj;
            CSL_Edma3QueryInfo      info;
            CSL_Edma3CmdDrae        regionAccess;
            CSL_Edma3ChannelHandle  hChannel;
            CSL_Edma3ChannelAttr    chAttr;
            CSL_Edma3HwDmaChannelSetup dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
                                             CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwDmaChannelSetup getdmahwSetup[CSL_EDMA3_NUM_DMACH];
        
            CSL_Status              status;
            
           
        
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = NULL;
            CSL_edma3HwSetup(hModule,&hwSetup);
         
             
            // DRAE Enable(Bits 0-15) for the Shadow Region 0.
            regionAccess.region = CSL_EDMA3_REGION_0 ;
            regionAccess.drae =   0xFFFF ;   
            regionAccess.draeh =  0x0000 ;
            CSL_edma3HwControl(hModule, CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                                                               &regionAccess); 
                
            // Channel 0 Open in context of Shadow region 0
            chAttr.regionNum = CSL_EDMA3_REGION_0;
            chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
            hChannel = CSL_edma3ChannelOpen(&chObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
        
            // Setup a Parameter Entry
            ...
                        
            // Manually trigger the Channel     
            CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
            
            // Close Channel
            CSL_edma3ChannelClose(hChannel);
            
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_edma3ChannelClose, ".text:csl_section:edma3");
CSL_Status  CSL_edma3ChannelClose (
    CSL_Edma3ChannelHandle    hEdma
)
{
    CSL_Status    status = CSL_SOK;
    
    if(hEdma != NULL) {
        hEdma->regs    = (CSL_Edma3ccRegsOvly) NULL;
        hEdma->edmaNum = (CSL_InstNum) - 1;
        hEdma->region  = -2;  /* -2 specifies the invalid region number */
        hEdma->chaNum  = -1;  /* -1 specifies the invalid channel */
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }
            
    return (status);
}

