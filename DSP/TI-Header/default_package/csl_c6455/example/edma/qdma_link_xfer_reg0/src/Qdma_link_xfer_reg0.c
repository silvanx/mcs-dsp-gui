/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *
 *   @file  Qdma_link_xfer_reg0.c
 *
 *   @path  $(CSLPATH)\example\edma\qdma_link_xfer_reg0\src
 *
 *   @desc  Example of EDMA
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This is an example of the CSL EDMA usage for the 
 *      QDMA Channel Initialization for linked transfer where channels are 
 *      opened in region 0. This example do the following operations
 *          1. Initializes and Opens the edma module
 *          2. Sets up the Module and gets the module setup values
 *          3. Enables the DMA and QDMA regions
 *          4. Opens qdma channel0 in the region 0. 
 *          5. Gets the param handle for 0 and 1
 *          6. Links the param sets 0 and 1
 *          7. Sets up the param
 *          8. Enables the channel and poll on the IPR bit
 *          9. Clear the pending bit
 *          10. Compares the transfered data
 *          11. Displays the result based on step 10 
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Qdma_link_xfer_reg0.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
 
/* ============================================================================
 *  Revision History
 *  ===============
 *  29-May-2004 Ruchika Kharwar    File Created.
 *  16-Dec-2005 ds                 Minor documentation changes
 *  27-Mar-2006 ds                 Added disable edma chhnel command
 * ============================================================================
 */

#include <stdio.h>
#include <csl_edma3.h>
#include <soc.h>

/* Globals */
Uint8       srcBuff1[256];
Uint8       srcBuff2[256];
Uint8       dstBuff1[256];
Uint8       dstBuff2[256];
Uint32      passStatus = 1;

/* Forward declarations */
void qdma_link_xfer_region0 (void);

/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.
 *
 * =============================================================================
 */
void main(void)
{   
    
    /* Invoke example */
    qdma_link_xfer_region0 ();
    
    return;   
}

/*
 * =============================================================================
 *   @func  qdma_link_xfer_region0
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the example routine which perform qdma link transfer where 
 *      channel is open in region0
 *          1. Initializes and Opens the edma module
 *          2. Sets up the Module and gets the module setup values
 *          3. Enables the DMA and QDMA regions
 *          4. Opens qdma channel0 in the region 0. 
 *          5. Gets the param handle for 0 and 1
 *          6. Links the param sets 0 and 1
 *          7. Sets up the param
 *          8. Enables the channel and poll on the IPR bit
 *          9. Clear the pending bit
 *          10. Compares the transfered data
 *          11. Closes Edma module
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void qdma_link_xfer_region0 (void)
{
    CSL_Edma3Handle             hModule;
    CSL_Edma3HwSetup            hwSetup;
    CSL_Edma3Obj                edmaObj;
    CSL_Edma3ParamHandle        hParamPong,hParamBasic;
    CSL_Edma3ChannelObj         chObj;
    CSL_Edma3CmdIntr            regionIntr;
    CSL_Edma3CmdDrae            regionAccess;
    CSL_Edma3ChannelHandle      hChannel;
    CSL_Edma3ParamSetup         myParamSetup;
    CSL_Edma3Context            context;
    CSL_Edma3ChannelAttr        chAttr;
    CSL_Edma3CmdQrae            qraeSetup;
    CSL_Status                  status;
    CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = \
                                            CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
    CSL_Edma3HwQdmaChannelSetup qdmahwSetup[CSL_EDMA3_NUM_QDMACH] = \
                                            CSL_EDMA3_QDMACHANNELSETUP_DEFAULT;
    Uint32                      loopIndex;
    
   /* Initialize data  */
    for (loopIndex = 0; loopIndex < 256; loopIndex++) {
        srcBuff1[loopIndex] = loopIndex;
        srcBuff2[loopIndex] = loopIndex;
        dstBuff1[loopIndex] = 0;
        dstBuff2[loopIndex] = 0;        
    }  

    /* Module initialization */
    status = CSL_edma3Init(&context);
    if (status != CSL_SOK) {
        printf ("Edma module initialization failed\n");   
        return;
    }
    
    /* Module level open */
    hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
    if ((hModule == NULL) || (status != CSL_SOK)) {
        printf ("Edma module open failed\n");    
        return;
    }
    
    /* Module Setup */
    hwSetup.dmaChaSetup  = &dmahwSetup[0];
    hwSetup.qdmaChaSetup = &qdmahwSetup[0];
    status = CSL_edma3HwSetup(hModule, &hwSetup);
    if (status != CSL_SOK) {
         printf ("Hardware setup failed\n");
         CSL_edma3Close (hModule);
         return;
    } 
     
    /* DRAE enable(Bits 0-15) for the shadow region 0. */
    regionAccess.region = CSL_EDMA3_REGION_0 ;
    regionAccess.drae =   0xFFFF ;   
    regionAccess.draeh =  0x0000 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                                &regionAccess); 
    if (status != CSL_SOK) {
         printf ("Edma region enable command failed\n");
         return;
    } 
    if (hModule->regs->DRA[CSL_EDMA3_REGION_0].DRAE != 0xFFFF)
        passStatus = 0;

    qraeSetup.region  = CSL_EDMA3_REGION_0;
    qraeSetup.qrae     = 0xF;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_QDMAREGION_ENABLE, \
                                &qraeSetup); 
    if (status != CSL_SOK) {
         printf ("Qdma region enable command failed\n");
         return;
    } 
    if (hModule->regs->QRAE[CSL_EDMA3_REGION_0] != 0x000F)
        passStatus = 0;

    regionAccess.region = CSL_EDMA3_REGION_0;
    regionAccess.drae = 0xFFFF;
    regionAccess.draeh = 0x0;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                                &regionAccess);               
    if (status != CSL_SOK) {
         printf ("Edma region enable command failed\n");
         return;
    }
    /* Channel Open */
    chAttr.regionNum = CSL_EDMA3_REGION_0;
    chAttr.chaNum    = CSL_EDMA3_QCHA_0;
    hChannel = CSL_edma3ChannelOpen(&chObj, CSL_EDMA3, &chAttr, &status);   
    if ((hChannel == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");    
        return;
    }
        
    /* Parameter entry 0 */
    hParamBasic = CSL_edma3GetParamHandle(hChannel,qdmahwSetup[0].paramNum, \
                                          &status);
    if (hParamBasic == NULL) {
        printf ("Edma get handle for param entry 0 failed\n");    
        return;
    }
    
    /* Pong Entry 1 */
    hParamPong = CSL_edma3GetParamHandle(hChannel,qdmahwSetup[0].paramNum+1, \
                                         &status);
    if (hParamPong == NULL) {
        printf ("Edma get handle for param entry 1 failed\n");    
        return;
    }
    
    /* Setup param entry */                                     
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                             CSL_EDMA3_TCCH_DIS, \
                                             CSL_EDMA3_ITCINT_DIS, \
                                             CSL_EDMA3_TCINT_DIS,\
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
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParamPong,0);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup.cCnt = 1;
    CSL_edma3ParamSetup(hParamBasic,&myParamSetup);
    
    /* Setting up the next entry */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                             CSL_EDMA3_TCCH_DIS, \
                                             CSL_EDMA3_ITCINT_DIS, \
                                             CSL_EDMA3_TCINT_EN,\
                                             1,CSL_EDMA3_TCC_NORMAL,\
                                             CSL_EDMA3_FIFOWIDTH_NONE, \
                                             CSL_EDMA3_STATIC_EN, \
                                             CSL_EDMA3_SYNC_A, \
                                             CSL_EDMA3_ADDRMODE_INCR, \
                                             CSL_EDMA3_ADDRMODE_INCR);
    myParamSetup.srcAddr = (Uint32)srcBuff2;
    myParamSetup.dstAddr = (Uint32)dstBuff2;    

    /* Setup for the Pong buffer */
    status = CSL_edma3ParamSetup(hParamPong,&myParamSetup);
    if (status != CSL_SOK) {
         printf ("Edma param setup failed\n");
         return;
    }
    
    /* Enable Channel */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE, \
                                       NULL);
    if (status != CSL_SOK) {
         printf ("Edma channel enable command failed\n");
         return;
    }
    
    status = CSL_edma3ParamWriteWord(hParamBasic,7,1);
    if (status != CSL_SOK) {
         printf ("Edma param write word failed\n");
         return;
    }
    
    /* Poll IPR bit */ 
    regionIntr.region = CSL_EDMA3_REGION_0;
    do {
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    } while (!(regionIntr.intr & 0x2));
    
    /* Clear pending interrupt */
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR, \
                               &regionIntr);   
    if (status != CSL_SOK) {
         printf ("Edma clear interrupt pend command failed\n");
         return;
    }
    
    
    /* Check transfer by comparing the source and destination buffers */
    if(Verify_Transfer( 256, 1, 1, 0, 0, 0, 0, srcBuff1, dstBuff1,TRUE) == \
                       FALSE)
        passStatus = 0; 
    if(Verify_Transfer( 256, 1, 1, 0, 0, 0, 0, srcBuff2, dstBuff2,TRUE) == \
                       FALSE)
        passStatus = 0; 
    
    if (passStatus == 1)    
        printf ("<<EXAMPLE PASSED>>: Qdma Link Transfer Passed\n");
    else {
        printf ("<<EXAMPLE FAILED>>: Qdma Link Transfer Failed\n");
        return;
    }
    
    /* Disable the channel */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_DISABLE, \
                                      NULL);

    /* Close channel */
    status = CSL_edma3ChannelClose(hChannel);
    if (status != CSL_SOK) {
        printf("Edma channel close failed\n");
        return;
    }
    
    /* Close edma module */
    status = CSL_edma3Close(hModule);
    if (status != CSL_SOK) {
        printf("Edma module close failed\n");
        return;
    }
    
    printf ("=============================================================\n");
    
    return;
}

