/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3HwChannelSetup.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API CSL_edma3HwChannelSetup()
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
 *   @n@b CSL_edma3HwChannelSetupParam
 *
 *   @b Description
 *   @n Sets up the channel to parameter entry mapping.This writes the 
 *      DCHMAP[]/QCHMAP appropriately.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            paramNum        Parameter Entry
                            
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Channel setup param successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - The paameters passed is invalid 
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen() must be 
 *       called successfully in that order before this API can be invoked
 *
 *   <b> Post Condition </b>
 *   @n  Channel to parameter entry is configured
 *
 *   @b Modifies
 *   @n Edma registers
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
            CSL_Edma3HwDmaChannelSetup  getdmahwSetup[CSL_EDMA3_NUM_DMACH];
            Uint16                      paramNum;
            CSL_Status                  status;
            
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
        
            // Set the parameter entry number to channel
            paramNum = 100;
            CSL_edma3HwChannelSetupParam(hChannel,paramNum);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3HwChannelSetupParam, ".text:csl_section:edma3");
CSL_Status  CSL_edma3HwChannelSetupParam (
    CSL_Edma3ChannelHandle        hEdma,
    Uint16                        paramNum  
)
{
    CSL_Status    status = CSL_SOK;

    if (hEdma == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (paramNum >= CSL_EDMA3_NUM_PARAMSETS) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* CSL_edma3ChannelSetEvtQue(hCh,setup->que); */
        if (hEdma->chaNum  < CSL_EDMA3_NUM_DMACH) {
#if CSL_EDMA3_CHMAPEXIST        
         CSL_FINS(hEdma->regs->DCHMAP[hEdma->chaNum], EDMA3CC_DCHMAP_PAENTRY, \
                     paramNum);         
#endif      
        } else
        
        CSL_FINS(hEdma->regs->QCHMAP[hEdma->chaNum-CSL_EDMA3_NUM_DMACH], \
                 EDMA3CC_QCHMAP_PAENTRY,paramNum);          
    }

    return (status); 
}

/** ============================================================================
 *   @n@b CSL_edma3HwChannelSetupTriggerWord
 *
 *   @b Description
 *   @n Programs the QDMA channel triggerword.This writes the QCHMAP[]
 *      appropriately.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            triggerWord     Trigger Word
                            
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Channel setup triggerword 
 *                                                successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - The paameters passed is invalid 
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen() must be 
 *       called successfully in that order before this API can be invoked
 *
 *   <b> Post Condition </b>
 *   @n  Sets up the QDMA Channel to trigger Word
 *
 *   @b Modifies
 *   @n Edma registers
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
            chAttr.chaNum = CSL_EDMA3_QCHA_0;
            hChannel = CSL_edma3ChannelOpen(&ChObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
        
            // Sets up the QDMA Channel 0 trigger Word to the 3rd trigger word.
            CSL_edma3HwChannelSetupTriggerWord(hChannel,3);
                    
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_edma3HwChannelSetupTriggerWord, ".text:csl_section:edma3");
CSL_Status  CSL_edma3HwChannelSetupTriggerWord (
    CSL_Edma3ChannelHandle      hEdma,
    Uint8                       triggerWord   
)
{
    CSL_Status    status = CSL_SOK;

    if (hEdma == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (triggerWord > 7) {
        status = CSL_ESYS_INVPARAMS;
    }
    else if (hEdma->chaNum  < CSL_EDMA3_NUM_DMACH) {
        /* CSL_edma3ChannelSetEvtQue(hEdma,setup->que); */    
        status = CSL_ESYS_INVPARAMS;
    } 
    else
        CSL_FINS(hEdma->regs->QCHMAP[hEdma->chaNum-CSL_EDMA3_NUM_DMACH], \
                     EDMA3CC_QCHMAP_TRWORD,triggerWord);    
    
    return (status); 
}

/** ============================================================================
 *   @n@b CSL_edma3HwChannelSetupQue
 *
 *   @b Description
 *   @n Programs the Channel to Queue mapping.This writes the DMAQNUM/QDAMQNUM 
 *      appropriately.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            evtQue          Queue Setup
                            
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Channel setup queue 
 *                                                successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen() must be 
 *       called successfully in that order before this API can be invoked
 *
 *   <b> Post Condition </b>
 *   @n  Sets up the channel to Queue mapping
 *
 *   @b Modifies
 *   @n Edma registers
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
            hChannel = CSL_edma3ChannelOpen(&ChObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
            
            // Set up the channel to que mapping
            CSL_edma3HwChannelSetupQue(hChannel,CSL_EDMA3_QUE_3);
                            
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3HwChannelSetupQue, ".text:csl_section:edma3");
CSL_Status  CSL_edma3HwChannelSetupQue (
    CSL_Edma3ChannelHandle       hEdma,
    CSL_Edma3Que                 evtQue 
) 
{
    Uint32        _cha;
    Uint32        _qNumIndex;
    Uint32        _qchMap;
    CSL_Status    status = CSL_SOK;

    if (hEdma == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else {
        if (hEdma->chaNum >= CSL_EDMA3_NUM_DMACH) {
        /*  Extracting the Channel Number in case of QDMA */
            _cha = hEdma->chaNum - CSL_EDMA3_NUM_DMACH;
        /*  Channel to Event Queue mapping */
            CSL_FINSR(hEdma->regs->QDMAQNUM,_cha * 4 + 2,_cha * 4,evtQue);
        } 
        else {
        /*  Finding out the relevant DMAQNUM register and the correct bit positions 
            to write into */ 
            _qNumIndex = hEdma->chaNum >> 3;
            _qchMap = hEdma->chaNum - (_qNumIndex * 8);
            CSL_FINSR(hEdma->regs->DMAQNUM[_qNumIndex], _qchMap * 4 + 2, \
                      _qchMap * 4, evtQue);
        }
    }

    return (status);
}

