/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3GetHwChannelSetup.c
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
#include <csl_edma3Aux.h>

/** ============================================================================
 *   @n@b CSL_edma3GetHwChannelSetupParam
 *
 *   @b Description
 *   @n Obtains the Channel to Parameter Set mapping.This reads the 
 *      DCHMAP/QCHMAP appropriately.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            paramNum        Pointer to parameter entry
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Retrieving the parameter entry 
 *                                                number to which a channel is 
 *                                                mapped
 *   @li                    CSL_ESYS_BADHANDLE  - The handle is passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter entry
 *                                                
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen()
 *       must be called successfully in that order before 
 *       CSL_edma3GetHwChannelSetupParam() can be invoked. 
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3ChannelObj         chObj;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
                                              CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
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
            hChannel = CSL_edma3ChannelOpen(&ChObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
        
            // Get the parameter entry number to which a channel is mapped to 
            CSL_edma3GetHwChannelSetupParam(hChannel,&paramNum);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3GetHwChannelSetupParam, ".text:csl_section:edma3");
CSL_Status  CSL_edma3GetHwChannelSetupParam (
    CSL_Edma3ChannelHandle    hEdma,
    Uint16                    *paramNum
)
{
    CSL_Status    status = CSL_SOK;

    if (hEdma == NULL) {
        status = CSL_ESYS_BADHANDLE;        
    }
    else if (paramNum == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        if (hEdma->chaNum  < CSL_EDMA3_NUM_DMACH) {
#if CSL_EDMA3_CHMAPEXIST        
            *paramNum = CSL_FEXT(hEdma->regs->DCHMAP[hEdma->chaNum], \
                                 EDMA3CC_DCHMAP_PAENTRY);           
#endif      
        } 
        else
            *paramNum = 
              CSL_FEXT(hEdma->regs->QCHMAP[hEdma->chaNum-CSL_EDMA3_NUM_DMACH],\
                         EDMA3CC_QCHMAP_PAENTRY);           
    }

    return (status); 
}

/** ============================================================================
 *   @n@b CSL_edma3GetHwChannelSetupTriggerWord
 *
 *   @b Description
 *   @n Reads the QDMA channel triggerword.This reads the QCHMAP to obtain the
 *      trigger word appropriately.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            triggerWord     Pointer to Trigger word
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Retrieving the parameter entry 
 *                                                number to which a channel is 
 *                                                mapped
 *   @li                    CSL_ESYS_BADHANDLE  - The handle is passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter entry
 *                                                
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen()
 *       must be called successfully in that order before 
 *       CSL_edma3GetHwChannelSetupTriggerWord() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3ChannelObj         chObj;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = \
                                            CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            Uint8                       triggerWord;
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
        
            // Get the trigger word programmed for a channel
            CSL_edma3GetHwChannelSetupTriggerWord(hChannel,&triggerWord);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3GetHwChannelSetupTriggerWord, ".text:csl_section:edma3");
CSL_Status  CSL_edma3GetHwChannelSetupTriggerWord (
    CSL_Edma3ChannelHandle    hEdma,
    Uint8                     *triggerWord  
)
{
    CSL_Status    status = CSL_SOK;

    if (hEdma == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else {
        if (hEdma->chaNum  < CSL_EDMA3_NUM_DMACH) {
            status = CSL_ESYS_INVPARAMS;
        } 
        else
            *triggerWord = \
                CSL_FEXT(hEdma->regs->QCHMAP[hEdma->chaNum-CSL_EDMA3_NUM_DMACH], \
                      EDMA3CC_QCHMAP_TRWORD); 
    }
    
    return (status); 
}


/** ============================================================================
 *   @n@b CSL_edma3GetHwChannelSetupQue
 *
 *   @b Description
 *   @n Obtains the Channel to Queue map for the channel.This reads the 
 *      DMAQNUM/QDAMQNUM appropriately.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            evtQue          Pointer to Queue setup
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Retrieving the que to which a 
 *                                                channel is mapped
 *   @li                    CSL_ESYS_BADHANDLE  - The handle is passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter entry
 *                                                
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen()
 *       must be called successfully in that order before 
 *       CSL_edma3GetHwChannelSetupQue() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
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
            CSL_Edma3Que                evtQue;
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
        
            // Get the que to which a channel is mapped
            CSL_edma3GetHwChannelSetupQue(hChannel,&evtQue);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3GetHwChannelSetupQue, ".text:csl_section:edma3");
CSL_Status  CSL_edma3GetHwChannelSetupQue (
    CSL_Edma3ChannelHandle        hEdma,
    CSL_Edma3Que                  *evtQue   
) 
{
    Uint32          _cha;
    Uint32          _qNumIndex;
    Uint32          _qchMap;
    CSL_Status      status = CSL_SOK;
    
    if (hEdma == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }    
    else if (evtQue == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        if (hEdma->chaNum >= CSL_EDMA3_NUM_DMACH) {
            /* Extracting the Channel Number in case of QDMA */
            _cha = hEdma->chaNum - CSL_EDMA3_NUM_DMACH;
           /*  Channel to Event Queue mapping */
            *evtQue = (CSL_Edma3Que)CSL_FEXTR(hEdma->regs->QDMAQNUM, _cha * 4 + 2, \
                                              _cha * 4);
        } 
        else {
            /*  Finding out the relevant DMAQNUM register and the correct bit 
             *  positions to write into 
             */ 
            _qNumIndex = hEdma->chaNum >> 3;
            _qchMap = hEdma->chaNum - (_qNumIndex * 8);
            *evtQue = (CSL_Edma3Que)CSL_FEXTR(hEdma->regs->DMAQNUM[_qNumIndex], \
                                              _qchMap * 4 + 2, _qchMap * 4);
        }
    }

    return (status);
}

