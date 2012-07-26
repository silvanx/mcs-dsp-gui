/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *
 *   @file  Edma_chain_example.c
 *
 *   @path  $(CSLPATH)\example\edma\edma_chain_example\src
 *
 *   @desc  Example of EDMA
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This is an example of the CSL EDMA usage. This example illustrates a  
 *      chain triggering where the completion of the transfer on one channels  
 *      triggers the transfer on another channel. This example, 
 *        1. Initializes the CSL EDMA module
 *        2. Opens and Sets up Edma module to default values 
 *        3. Opens EDMA channel 0 in the region 5
 *        4. Sets up the EDMA PARAM entry for channel 0 using 
 *           CSL_edma3ParamSetup() API
 *        5. Opens EDMA channel 8 in the region 5
 *        6. Sets up the EDMA PARAM entry for channel 8 using 
 *           CSL_edma3ParamSetup() API
 *        7. Enable the channel 0 and 8
 *        8. Manually triggers the channel 0, completion of this transfer 
 *           triggers the transfer on channel 8. 
 *        9. Waits for EDMA transfer to complete
 *        10. Does the data comparision to ensure the transffered data is proper  
 *           or not and 
 *        11. Displays the messages based on step 10
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Edma_chain_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  08-Feb-2006 ds    File Created
 *  28-Mar-2006 ds    Added clearing the EDMA error registers 
 * =============================================================================
 */

#include <stdio.h>
#include <csl_edma3.h>
#include <soc.h>

/* Globals */
Uint8       srcBuff1[512];
Uint8       srcBuff2[512];
Uint8       dstBuff1[512];
Uint8       dstBuff2[512];
Uint32      passStatus = 1;   

/* Forward declaration */
void edma_chain_example (void);

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
    edma_chain_example ();
    
    return;   
}

/*
 * =============================================================================
 *   @func  edma_chain_example
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the example routine which perform edma interrupt.
 *      It implements following steps
 *          1. Intializes and Opens the Edma 
 *          2. Sets up the edma module using the API csl_edma3Hwsetup () 
 *          4. Enables the edma region5 using CSL_EDMA3_CMD_DMAREGION_ENABLE. 
 *          5. Opens the channel 0 and get the param handle. 
 *          6. Sets up the edma param entry for channel 0
 *          7. Opens the channel 8 and get the param handle. 
 *          8. Sets up the edma param entry  for channel 8
 *          9. Enables the channels using CSL_EDMA3_CMD_CHANNEL_ENABLE 
 *          10. Manually trigger the channel 0 using CSL_EDMA3_CMD_CHANNEL_SET. 
 *          10. Waits for transfer to complete.
 *          11. Compares the data in the destination buffer is proper or not.
 *          12. Closes the edma module and channel.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void edma_chain_example (void)
{
    CSL_Edma3Handle             hModule;
    CSL_Edma3HwSetup            hwSetup;
    CSL_Edma3Obj                edmaObj;
    CSL_Edma3ParamHandle        hParamBasic;
    CSL_Edma3ParamHandle        hParamBasic1;
    CSL_Edma3ChannelObj         chObj;
    CSL_Edma3ChannelObj         chObj1;
    CSL_Edma3CmdIntr            regionIntr;
    CSL_Edma3CmdDrae            regionAccess;
    CSL_Edma3ChannelHandle      hChannel;
    CSL_Edma3ChannelHandle      hChannel1;
    CSL_Edma3ParamSetup         myParamSetup;
    CSL_Edma3ParamSetup         myParamSetup1;
    CSL_Edma3Context            context;
    CSL_Edma3ChannelAttr        chAttr;
    CSL_Edma3ChannelAttr        chAttr1;
    CSL_Status                  status;
    CSL_Edma3HwDmaChannelSetup  dmahwSetup;
    CSL_Edma3ChannelErr         chErrClear;
    volatile Uint32             loopIndex;

    
    printf ("Running Edma Example\n");
    
    /* Module Initialization */
    status = CSL_edma3Init(&context);
    if (status != CSL_SOK) {
        printf ("Edma module initialization failed\n");   
        return;
    }
    
    /* Module level open */
    hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
    if ( (hModule == NULL) || (status != CSL_SOK)) {
        printf ("Edma module open failed\n");    
        return;
    }
    
    /* Module setup */
    dmahwSetup.paramNum = 0;
    dmahwSetup.que      = CSL_EDMA3_QUE_0;
    hwSetup.dmaChaSetup = &dmahwSetup;
    hwSetup.qdmaChaSetup = NULL;
    status = CSL_edma3HwSetup(hModule,&hwSetup);
    if (status != CSL_SOK) {
         printf ("Hardware setup failed\n");
         CSL_edma3Close (hModule);
         return;
    } 
      
    /* DRAE enable(Bits 0-15) for the shadow region 5 */
    regionAccess.region = CSL_EDMA3_REGION_5 ;
    regionAccess.drae =   0xFFFF ;   
    regionAccess.draeh =  0x0 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                               &regionAccess); 
    if (status != CSL_SOK) {
        printf ("Edma region enable command failed\n");
        return;
    }

    /* Channel 0 open in context of shadow region 5 */
    chAttr.regionNum = CSL_EDMA3_REGION_5;
    chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
    hChannel = CSL_edma3ChannelOpen(&chObj, CSL_EDMA3, &chAttr, &status);   
    if ((hChannel == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");
        return;
    }
    
    /* Obtain a handle to parameter set 0 */
    hParamBasic = CSL_edma3GetParamHandle(hChannel, 0, &status);
    if (hParamBasic == NULL) {
        printf ("Edma get param handle for param entry 0 failed\n");    
        return;
    }
    
    /* Setup the param set */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE( CSL_EDMA3_ITCCH_DIS, \
                                              CSL_EDMA3_TCCH_EN, \
                                              CSL_EDMA3_ITCINT_DIS, \
                                              CSL_EDMA3_TCINT_EN,\
                                              8, 
                                              CSL_EDMA3_TCC_NORMAL,\
                                              CSL_EDMA3_FIFOWIDTH_NONE, \
                                              CSL_EDMA3_STATIC_DIS, \
                                              CSL_EDMA3_SYNC_AB, \
                                              CSL_EDMA3_ADDRMODE_INCR, \
                                              CSL_EDMA3_ADDRMODE_INCR
                                             );           
    myParamSetup.srcAddr = (Uint32)srcBuff1;         
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(512,2);       
    myParamSetup.dstAddr = (Uint32)dstBuff1;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(512,512);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(CSL_EDMA3_LINK_NULL,0);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup.cCnt = 1;

    status = CSL_edma3ParamSetup(hParamBasic, &myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma parameter entry setup is failed\n");
        return;
    }
    
     /* Channel 8 open in context of shadow region 5 */
    chAttr1.regionNum = CSL_EDMA3_REGION_5;
    chAttr1.chaNum = CSL_EDMA3_CHA_8;
    hChannel1 = CSL_edma3ChannelOpen(&chObj1, CSL_EDMA3, &chAttr1, &status);   
    if ((hChannel1 == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");
        return;
    }
    
    /* Obtain a handle to parameter set 8 */
    hParamBasic1 = CSL_edma3GetParamHandle(hChannel1, 8, &status);

    /* Setup the param set */
    myParamSetup1.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                              CSL_EDMA3_TCCH_EN, \
                                              CSL_EDMA3_ITCINT_DIS, \
                                              CSL_EDMA3_TCINT_EN, \
                                              1, \
                                              CSL_EDMA3_TCC_NORMAL, \
                                              CSL_EDMA3_FIFOWIDTH_NONE, \
                                              TRUE,CSL_EDMA3_SYNC_AB, \
                                              CSL_EDMA3_ADDRMODE_INCR, \
                                              CSL_EDMA3_ADDRMODE_INCR
                                             );           
    myParamSetup1.srcAddr = (Uint32)srcBuff2;
    myParamSetup1.aCntbCnt = CSL_EDMA3_CNT_MAKE(512,2);       
    myParamSetup1.dstAddr = (Uint32)dstBuff2;        
    myParamSetup1.srcDstBidx = CSL_EDMA3_BIDX_MAKE(512,512);     
    myParamSetup1.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(CSL_EDMA3_LINK_NULL,0);     
    myParamSetup1.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup1.cCnt = 1;

    status = CSL_edma3ParamSetup(hParamBasic1,&myParamSetup1);
    if (status != CSL_SOK) {
        printf("Edma parameter entry setup is failed\n");
        return;
    }
    
    /* Enable channel 0 */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);
    if (status != CSL_SOK) {
        printf("Edma channel enable command for channel 0 is failed\n");
        return;
    }
                                      
    /* Enable channel 8 */
    status = CSL_edma3HwChannelControl(hChannel1,CSL_EDMA3_CMD_CHANNEL_ENABLE, \
                                        NULL);
    if (status != CSL_SOK) {
        printf("Edma channel enable command for channel 8 is failed\n");
        return;
    }
    
    /* Initialize data */
    for (loopIndex = 0; loopIndex < 512; loopIndex++) {
        srcBuff1[loopIndex] = loopIndex;
        srcBuff2[loopIndex] = loopIndex;
        dstBuff1[loopIndex] = 0;
        dstBuff2[loopIndex] = 0;        
    }
    
    /* Trigger Channel 0 */
    CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL); 

    regionIntr.region = CSL_EDMA3_REGION_5;
    do {
        /* Poll on interrupt bit 8 */
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    } while (!(regionIntr.intr & 0x100));
    
    
    /* Clear interrupt bit 8 */
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR, \
                              &regionIntr);   
    if (status != CSL_SOK) {
        printf("Edma clear interrupt bit 0 command is failed\n");
        return;
    }
    
    /* Check transfer */
    if(Verify_Transfer(512, 1, 1, 0, 0, 0, 0, srcBuff1, dstBuff1,TRUE) == FALSE)
        passStatus = 0; 
    if(Verify_Transfer(512, 1, 1, 0, 0, 0, 0, srcBuff2, dstBuff2,TRUE) == FALSE)
        passStatus = 0;
           
    if (passStatus == 1)    
        printf ("<<EXAMPLE PASSED>>: Edma Chain Transfer Passed\n");
    else {
        printf ("<<EXAMPLE FAILED>>: Edma Chain Transfer Failed\n");
        return;
    }    
    
     /* Disable the region 5 */
    regionAccess.region = CSL_EDMA3_REGION_5 ;
    regionAccess.drae =   0xFFFF ;   
    regionAccess.draeh =  0x0 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                               &regionAccess); 

    /* clear the EDMA error registers */
    chErrClear.missed = TRUE;
    chErrClear.secEvt = TRUE;
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEARERR, 
                               &chErrClear);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);

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

