/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *   @file  csl_edma3ChannelOpen.c
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
 *  08-Feb-2006 ds  Added error checking  
 * =============================================================================
 */
#include <csl_edma3.h>

/** ============================================================================
 *   @n@b CSL_edma3ChannelOpen
 *
 *   @b Description
 *   @n The API returns a handle for the specified EDMA Channel for use. The 
 *      channel can be re-opened anytime after it has been normally closed if so
 *      required. The handle returned by this call is input as an essential 
 *      argument for many of the APIs described for this module.
 *
 *   @b Arguments
 *   @verbatim
            pEdmaObj         pointer to the object that holds reference to the
                             channel instance of the Specified DMA 
 
            edmaNum          Instance of EDMA whose channel is requested
                             
            pChAttr          Instance of Channel requested
 
            status           Status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Edma3ChannelHandle
 *   @n                     The requested channel instance of the EDMA
 *                          if the call is successful,else a NULL is returned
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() must be invoked successfully in that 
 *       order before this API can be invoked
 *
 *   <b> Post Condition </b>
 *   @n  1. The status is returned in the status variable. If status
 *          returned is
 *   @li            CSL_SOK             Valid channel handle is returned
 *   @li            CSL_ESYS_FAIL       The Edma instance or channel is invalid
 *   @li            CSL_ESYS_INVPARAMS  The Parameter passed is invalid
 *
 *       2. Edma channel object structure is populated
 *
 *   @b Modifies
 *   @n  1. The status variable
 *
 *       2. Edma channel object structure
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3ChannelObj         chObj;
            CSL_Edma3QueryInfo          info;
            CSL_Edma3CmdDrae            regionAccess;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
                                              CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwDmaChannelSetup  getdmahwSetup[CSL_EDMA3_NUM_DMACH];
            CSL_Status                  status;
            
            
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
            CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
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

#pragma CODE_SECTION (CSL_edma3ChannelOpen, ".text:csl_section:edma3");
CSL_Edma3ChannelHandle  CSL_edma3ChannelOpen (
    CSL_Edma3ChannelObj     *pEdmaObj,
    CSL_InstNum             edmaNum,
    CSL_Edma3ChannelAttr    *pChAttr,
    CSL_Status              *pStatus
)
{
    CSL_Edma3ChannelHandle        hEdma = (CSL_Edma3ChannelHandle)NULL;
    CSL_Edma3ModuleBaseAddress    baseAddress;
    
    if (pStatus == NULL) {
        /* Do nothing : Module handle already initialised to NULL */
    }
    else if (pEdmaObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        if (pChAttr != NULL) {
            *pStatus = CSL_edma3ccGetModuleBaseAddr(edmaNum, NULL, &baseAddress);
            if (*pStatus == CSL_SOK) {
                pEdmaObj->regs = baseAddress.regs;
                pEdmaObj->edmaNum = edmaNum;
                pEdmaObj->chaNum = pChAttr->chaNum;
                pEdmaObj->region = pChAttr->regionNum;
                hEdma = (CSL_Edma3ChannelHandle)pEdmaObj;
            }
            else {
                pEdmaObj->regs = (CSL_Edma3ccRegsOvly)NULL;
                pEdmaObj->edmaNum = (CSL_InstNum) -1;
                pEdmaObj->chaNum = -1;
                pEdmaObj->region = -2;
            } 
        }
        else {
            *pStatus = CSL_ESYS_INVPARAMS;
        }        
    }

    return (hEdma);
}

