/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3HwChannelControl.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API CSL_edma3HwChannelControl()
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
 *   @n@b CSL_edma3HwChannelControl
 *
 *   @b Description
 *   @n Takes a command with an optional argument & implements it. This function
 *      is used to carry out the different operations performed by EDMA.
 *
 *   @b Arguments
 *   @verbatim
            hCh             Channel Handle
 
            cmd             The command to this API which indicates the 
                            action to be taken

            cmdArg          Pointer arguement specific to the command 
                            
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Command execution successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVCMD     - The command passed is invalid 
 *                                                
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen()
 *       must be called successfully in that order before this API can be 
 *       invoked.If a Shadow region is used then care of the DRAE settings
 *       must be taken
 *
 *   <b> Post Condition </b>
 *   @n  Edma registers are configured according to the command and
 *       the command arguements. The command determines which registers are
 *       modified.
 *
 *   @b Modifies
 *   @n Edma registers determined by the command
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3ChannelObj         chObj;
            CSL_Edma3CmdIntr            regionIntr;
            CSL_Edma3CmdDrae            regionAccess;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = \
                                             CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
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
        
            // Interrupt Enable (Bits 0-11)  for the Shadow Region 0. 
            regionIntr.region =  CSL_EDMA3_REGION_0  ;   
            regionIntr.intr  =   0x0FFF ;   
            regionIntr.intrh  =  0x0000 ;
            CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE, &regionIntr);
                
            // Channel 0 Open in context of Shadow region 0
            chAttr.regionNum = CSL_EDMA3_REGION_0;
            chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
            hChannel = CSL_edma3ChannelOpen(&chObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
            
            // Enable Channel(if the channel is meant for external event) 
            // This step is not required if the channel is chained to or manually 
               triggered.
        
            CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE,NULL);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3HwChannelControl, ".text:csl_section:edma3");
CSL_Status  CSL_edma3HwChannelControl (
    CSL_Edma3ChannelHandle          hCh,
    CSL_Edma3HwChannelControlCmd    cmd,
    void                            *cmdArg
)
{ 
    CSL_Status    status = CSL_SOK;
    
    if (hCh == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if ((cmd == CSL_EDMA3_CMD_CHANNEL_CLEARERR) && (cmdArg == NULL)) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(cmd) {
            case CSL_EDMA3_CMD_CHANNEL_ENABLE:
                status = CSL_edma3ChannelEnable(hCh);
                break;
            
            case CSL_EDMA3_CMD_CHANNEL_DISABLE:
                status = CSL_edma3ChannelDisable(hCh);
                break;
            
            case CSL_EDMA3_CMD_CHANNEL_SET:
                status = CSL_edma3ChannelEventSet(hCh);
                break;
            
            case CSL_EDMA3_CMD_CHANNEL_CLEAR:
                status = CSL_edma3ChannelEventClear(hCh);
                break;          
            
            case CSL_EDMA3_CMD_CHANNEL_CLEARERR:
                status = CSL_Edma3ChannelErrorClear(hCh,
                                                 (CSL_Edma3ChannelErr*)cmdArg);
                break;
            
            default:
                status = CSL_ESYS_INVCMD;
                break;
        }
    }

    return (status);
}

