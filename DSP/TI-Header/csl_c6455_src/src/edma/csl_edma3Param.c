/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3Param.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  CSL for  Edma Parameter Entries
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  29-May-2004 Ruchika Kharwar File Created.
 *  23-Mar-2006 ds Added invalid handle check for CSL_edma3ParamWriteWord() API.
 * =============================================================================
 */
 
#include <csl_edma3.h>

/** ============================================================================
 *   @n@b CSL_edma3GetParamHandle
 *
 *   @b Description
 *   @n Acquires the Param entry as specified by the argument.
 *
 *   @b Arguments
 *   @verbatim
            hEdma           Channel Handle
 
            paramNum        Parameter entry number
            
            status          Status of the function call
                            
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Edma3ParamHandle
 *   @n                     Valid param handle will be returned if status value
 *                          is equal to CSL_SOK.
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() and CSL_edma3ChannelOpen() must be 
 *       called successfully in that order before this API can be invoked
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
            CSL_Edma3CmdIntr            regionIntr;
            CSL_Edma3CmdDrae            regionAccess;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
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
            CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);
            
            // Channel 0 Open in context of Shadow region 0
            chAttr.regionNum = CSL_EDMA3_REGION_0;
            chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
            hChannel = CSL_edma3ChannelOpen(&chObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
            
            // Obtain a handle to parameter entry 0
            hParamBasic = CSL_edma3GetParamHandle(hChannel,0,NULL);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3GetParamHandle, ".text:csl_section:edma3");
CSL_Edma3ParamHandle  CSL_edma3GetParamHandle (
    CSL_Edma3ChannelHandle    hEdma,
    Int16                     paramNum,
    CSL_Status                *status       
)
{   
    CSL_Edma3ParamHandle handle = (CSL_Edma3ParamHandle)NULL;

    if (status == NULL) {
        /* Do nothing */
    }
    else if (hEdma == NULL) {
        *status = CSL_ESYS_BADHANDLE;
    }
    else if (paramNum < 0 || paramNum > 255) {
        *status = CSL_ESYS_INVPARAMS;
    }
    else {
        handle = (&hEdma->regs->PARAMSET[paramNum]);
        *status = CSL_SOK;
    }

    return (handle);
}

/** ============================================================================
 *   @n@b CSL_edma3ParamSetup
 *
 *   @b Description
 *   @n Configures the EDMA parameter Entry using the values passed in through
 *      the Param setup structure.
 *
 *   @b Arguments
 *   @verbatim
            hParamHndl      Handle to the param entry
 
            setup           Pointer to param setup structure
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Command execution successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - The parameter passed is invalid 
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() and  CSL_edma3ChannelOpen() must be 
 *       called successfully in that order before this API can be invoked
 *
 *   <b> Post Condition </b>
 *   @n  Configures the EDMA parameter Entry
 *
 *   @b Modifies
 *   @n Parameter entry
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
            CSL_Edma3ParamSetup         myParamSetup;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
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
            CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);
        
            // Channel 0 Open in context of Shadow region 0
            chAttr.regionNum = CSL_EDMA3_REGION_0;
            chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
            hChannel = CSL_edma3ChannelOpen(&chObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
        
            // Obtain a handle to parameter entry 0
            hParamBasic = CSL_edma3GetParamHandle(hChannel,0,NULL);
        
            // Setup the first param Entry (Ping buffer) 
            myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                                     CSL_EDMA3_TCCH_DIS, \
                                                     CSL_EDMA3_ITCINT_DIS, \
                                                     CSL_EDMA3_TCINT_EN,\
                                                     0,CSL_EDMA3_TCC_NORMAL,\
                                                     CSL_EDMA3_FIFOWIDTH_NONE, \
                                                     CSL_EDMA3_STATIC_DIS, \
                                                     CSL_EDMA3_SYNC_A, \
                                                     CSL_EDMA3_ADDRMODE_INCR, \
                                                     CSL_EDMA3_ADDRMODE_INCR);           
            myParamSetup.srcAddr = (Uint32)srcBuff1;         
            myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(256,1);       
            myParamSetup.dstAddr = (Uint32)dstBuff1;        
            myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
            myParamSetup.linkBcntrld = 
                             CSL_EDMA3_LINKBCNTRLD_MAKE(CSL_EDMA3_LINK_NULL,0);     
            myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
            myParamSetup.cCnt = 1;
            CSL_edma3ParamSetup(hParamBasic,&myParamSetup);     
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3ParamSetup, ".text:csl_section:edma3");
CSL_Status  CSL_edma3ParamSetup (
    CSL_Edma3ParamHandle       hParamHndl,
    CSL_Edma3ParamSetup        *setup
)
{
    Uint32        *paramHndl = (Uint32*)hParamHndl;
    Uint32        i;
    CSL_Status    status = CSL_SOK;
    
    if (hParamHndl == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        for (i = 0; i < 8 ; i++)
            paramHndl[i] = ((Uint32*)setup)[i];  
    }

    return (status);
}

/** ============================================================================
 *   @n@b CSL_edma3ParamWriteWord
 *
 *   @b Description
 *   @n This is for the ease of QDMA channels. Once the QDMA channel transfer is 
 *      triggered, subsequent triggers may be done with only writing the modified
 *      words in the parameter entry along with the trigger word. This API is 
 *      expected to achieve this purpose. Most usage scenarios, the user 
 *      should not be writing more than the trigger word entry.
 *
 *   @b Arguments
 *   @verbatim
            hParamHndl      Handle to the param entry
 
            wordOffset      word offset in the 8 word paramater entry
            
            word            word to be written
            
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Param Write Word successful
 *   @li                    CSL_ESYS_BADHANDLE - Invlaid handle
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() and  CSL_edma3ChannelOpen() and 
 *       must be CSL_edma3GetParamHandle(), CSL_edma3ParamSetup()
 *       called successfully in that order before this API can be invoked.
 *       The main setup structure consists of pointers to sub-structures.The  
 *       user has to allocate space for & fill in the parameter setup structure.
 *
 *   <b> Post Condition </b>
 *   @n  Configure trigger word
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
            CSL_Edma3CmdIntr            regionIntr;
            CSL_Edma3CmdQrae            regionAccess;
            CSL_Edma3ChannelHandle      hChannel;
            CSL_Edma3ParamSetup         myParamSetup;
            CSL_Edma3ParamHandle        hParamBasic;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
                                             CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwQdmaChannelSetup qdmahwSetup[CSL_EDMA3_NUM_QDMACH] = 
                                             CSL_EDMA3_QDMACHANNELSETUP_DEFAULT;
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = &qdmahwSetup[0];;
            CSL_edma3HwSetup(hModule,&hwSetup);
            
            // DRAE Enable(Bits 0-15) for the Shadow Region 0.
            regionAccess.region = CSL_EDMA3_REGION_0 ;
            regionAccess.qrae =   0x000F ;   
            CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_QDMAREGION_ENABLE, \
                               &regionAccess); 
            
            // Interrupt Enable (Bits 0-11)  for the Shadow Region 0. 
            regionIntr.region =  CSL_EDMA3_REGION_0  ;   
            regionIntr.intr  =   0x0FFF ;   
            regionIntr.intrh  =  0x0000 ;
            CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE, &regionIntr);
            
            // Channel 0 Open in context of Shadow region 0
            chAttr.regionNum = CSL_EDMA3_REGION_0;
            chAttr.chaNum = CSL_EDMA3_QCHA_0;
            hChannel = CSL_edma3ChannelOpen(&ChObj,
                                    CSL_EDMA3,
                                    &chAttr,                            
                                    &status);   
            
            // Obtain a handle to parameter entry 0
            hParamBasic = CSL_edma3GetParamHandle(hChannel,0,NULL);
            
            
            // Setup the first param Entry (Ping buffer) 
            myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                                     CSL_EDMA3_TCCH_DIS, \
                                                     CSL_EDMA3_ITCINT_DIS, \
                                                     CSL_EDMA3_TCINT_EN,\
                                                     0,CSL_EDMA3_TCC_NORMAL,\
                                                     CSL_EDMA3_FIFOWIDTH_NONE, \
                                                     CSL_EDMA3_STATIC_EN, \
                                                     CSL_EDMA3_SYNC_A, \
                                                     CSL_EDMA3_ADDRMODE_INCR, \
                                                     CSL_EDMA3_ADDRMODE_INCR);           
            myParamSetup.srcAddr = (Uint32)srcBuff1;         
            myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(256,1);       
            myParamSetup.dstAddr = (Uint32)dstBuff1;        
            myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
            myParamSetup.linkBcntrld = 
                            CSL_EDMA3_LINKBCNTRLD_MAKE(CSL_EDMA3_LINK_NULL,0);     
            myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
            myParamSetup.cCnt = 1;
            CSL_edma3ParamSetup(hParamBasic,&myParamSetup); 
            
            // Enable Channel
            CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE,NULL);
            
            // Write trigger word
            CSL_edma3ParamWriteWord(hParamBasic,7,myParamSetup.cCnt);    
                    
     @endverbatim
 * =============================================================================
 */
 
#pragma CODE_SECTION (CSL_edma3ParamWriteWord, ".text:csl_section:edma3");
CSL_Status  CSL_edma3ParamWriteWord(
    CSL_Edma3ParamHandle       hParamHndl,
    Uint16                     wordOffset,
    Uint32                     word 
)
{
    Uint32        *hParam = (Uint32*)(hParamHndl);
    CSL_Status    status = CSL_SOK;
    
    if (hParamHndl == NULL)
        status = CSL_ESYS_BADHANDLE;
    else    
        hParam[wordOffset] = word;  
    
    return (status);
}

