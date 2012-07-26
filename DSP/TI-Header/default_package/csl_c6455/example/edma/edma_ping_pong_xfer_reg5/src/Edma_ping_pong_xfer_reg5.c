/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *
 *   @file  Edma_ping_pong_xfer_reg5.c
 *
 *   @path  $(CSLPATH)\example\edma\edma_ping_pong_xfer_reg5\src
 *
 *   @desc  Example of EDMA
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This is an example of the CSL EDMA usage for the  use edma Channel 
 *      Initialization for ping pong buffer where channels are opened 
 *      in the region 5.
 *      This example do the following operations
 *       - Initializes and Opens the edma module
 *       - Sets up the Module and gets the module setup values
 *       - Enables (Bits 0-15) the Shadow Region 0 
 *       - Disables (Bits 12-15) the Shadow Region 0
 *       - Enables interrupt (Bits 0-11)  for the Shadow Region 0
 *       - Disables interrupt (Bits 2-11)  for the Shadow Region 0
 *       - Opens Channel 0 in context of Shadow region 0
 *       - Obtains a handles to parameters set 0, 1 and 2
 *       - Sets up the first param set (Ping buffer)
 *       - Sets up the Ping Entry which is loaded after the Pong entry 
 *         gets exhausted
 *       - Enables Channel and Initialize the data
 *       - Manually triggers the Channel
 *       - Polls on interrupt bit 0 and clears interrupt bit 0
 *       - Maps Channel 0 to Event Queue 1
 *       - Manually triggers the Channel 
 *       - Polls on interrupt pend bit 1 and clears interrupt bit 1
 *       - Compares the transfered data
 *       - Displays the result based on previous step 
 * 
 *  ============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Edma_ping_pong_xfer_reg5.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  29-May-2004 Ruchika Kharwar    File Created.
 *
 *  16-Dec-2005 DS                 Minor documentation changes
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
Uint32       passStatus = 1;   

/* Forward declaration */
void edma_ping_pong_xfer_region5 (void);

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
    edma_ping_pong_xfer_region5 ();
    
    return;   
}

/*
 * =============================================================================
 *   @func  edma_ping_pong_xfer_region5
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the example routine which perform edma ping pong buffer transfer
 *      where channel is open in region 5.
 *      It implements following steps
 *         1. Initializes and Opens the edma module
 *         2. Sets up the Module and gets the module setup values
 *         3. Enables (Bits 0-15) the Shadow Region 0 
 *         4. Disables (Bits 12-15) the Shadow Region 0
 *         5. Enables interrupt (Bits 0-11)  for the Shadow Region 0
 *         6. Disables interrupt (Bits 2-11)  for the Shadow Region 0
 *         7. Opens Channel 0 in context of Shadow region 0
 *         8. Obtains a handles to parameters set 0, 1 and 2
 *         9. Sets up the first param set (Ping buffer)
 *         10. Sets up the Ping Entry which is loaded after the Pong entry 
 *             gets exhausted
 *         11. Enables Channel and Initialize the data
 *         12. Manually triggers the Channel
 *         13. Polls on interrupt bit 0 and clears interrupt bit 0
 *         14. Maps Channel 0 to Event Queue 1
 *         15. Manually triggers the Channel 
 *         16. Polls on interrupt pend bit 1 and clears interrupt bit 1
 *         17. Compares the transfered data
 *         18. Close the Edma module and channel
 *          
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void edma_ping_pong_xfer_region5 (void)
{
    CSL_Edma3Handle             hModule;
    CSL_Edma3HwSetup            hwSetup;
    CSL_Edma3Obj                edmaObj;
    CSL_Edma3ParamHandle        hParamPing;
    CSL_Edma3ParamHandle        hParamPong;
    CSL_Edma3ParamHandle        hParamBasic;
    CSL_Edma3ChannelObj         chObj;
    CSL_Edma3CmdIntr            regionIntr;
    CSL_Edma3CmdDrae            regionAccess;
    CSL_Edma3ChannelHandle      hChannel;
    CSL_Edma3ParamSetup         myParamSetup;
    CSL_Edma3Context            context;
    CSL_Edma3ChannelAttr        chAttr;
    CSL_Status                  status;
    CSL_Edma3HwDmaChannelSetup  dmahwSetup;
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
    regionAccess.draeh =  0x0000 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                               &regionAccess); 
    if (status != CSL_SOK) {
        printf ("Edma region enable command failed\n");
        return;
    }

    /* DRAE disable(Bits 12-15) for the shadow region 5 */
    regionAccess.region = CSL_EDMA3_REGION_5 ;
    regionAccess.drae =   0xF000 ;   
    regionAccess.draeh =  0x0000 ;    
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_DISABLE, \
                               &regionAccess); 
    if (status != CSL_SOK) {
        printf ("Edma region disable command failed\n");
        return;
    }
    
    if (hModule->regs->DRA[CSL_EDMA3_REGION_5].DRAE != 0x0FFF)
        passStatus = 0;
    
    /* Interrupt enable (Bits 0-11)  for the shadow region 5 */
    regionIntr.region =  CSL_EDMA3_REGION_5  ;   
    regionIntr.intr  =   0x0FFF ;   
    regionIntr.intrh  =  0x0000 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE, &regionIntr);
    if (status != CSL_SOK) {
        printf ("Edma interrupts enable command failed\n");
        return;
    }
    
    /* Interrupt disable (Bits 2-11)  for the shadow region 5 */
    regionIntr.region =  CSL_EDMA3_REGION_5  ;   
    regionIntr.intr  =   0x0FFC ;   
    regionIntr.intrh  =  0x0000 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_DISABLE,&regionIntr);
    if (status != CSL_SOK) {
        printf ("Edma interrupts disable command failed\n");
        return;
    }
    
    /* Check intr enable register bit */
    if (hModule->regs->SHADOW[CSL_EDMA3_REGION_5].IER != 0x0003)
        passStatus = 0;
        
    /* Channel 0 open in context of shadow region 5 */
    chAttr.regionNum = CSL_EDMA3_REGION_5;
    chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
    hChannel = CSL_edma3ChannelOpen(&chObj, CSL_EDMA3, &chAttr, &status);   
    if ((hChannel == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");
        return;
    }
    
    /* Obtain a handle to parameter set 0 */
    hParamBasic = CSL_edma3GetParamHandle(hChannel,0,&status);
    if (hParamBasic == NULL) {
        printf ("Edma get param handle for param entry 0 failed\n");    
        return;
    }
    
    /* Obtain a handle to parameter set 2 */
    hParamPing = CSL_edma3GetParamHandle(hChannel,2,&status);
    if (hParamPing == NULL) {
        printf ("Edma get param handle for param entry 2 failed\n");    
        return;
    }
    
    /* Obtain a handle to parameter set 1 */
    hParamPong = CSL_edma3GetParamHandle(hChannel,1,&status);
    if (hParamPong == NULL) {
        printf ("Edma get param handle for param entry 1 failed\n");        
        return;
    }
    
    /* Setup the first param set (Ping buffer) */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE( CSL_EDMA3_ITCCH_DIS, \
                                              CSL_EDMA3_TCCH_DIS, \
                                              CSL_EDMA3_ITCINT_DIS, \
                                              CSL_EDMA3_TCINT_EN,\
                                              0, CSL_EDMA3_TCC_NORMAL,\
                                              CSL_EDMA3_FIFOWIDTH_NONE, \
                                              CSL_EDMA3_STATIC_DIS, \
                                              CSL_EDMA3_SYNC_A, \
                                              CSL_EDMA3_ADDRMODE_INCR, \
                                              CSL_EDMA3_ADDRMODE_INCR
                                             );           
    myParamSetup.srcAddr = (Uint32)srcBuff1;         
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(512,1);       
    myParamSetup.dstAddr = (Uint32)dstBuff1;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParamPong,0);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup.cCnt = 1;
    status = CSL_edma3ParamSetup(hParamBasic, &myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma parameter entry setup is failed\n");
        return;
    }
    
    /* Setup the Ping Entry which loaded after the Pong entry gets exhausted */
    status = CSL_edma3ParamSetup(hParamPing,&myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma ping parameter entry setup is failed\n");
        return;
    }
    
    /* Setup the Pong Entry which loaded after the Ping entry gets exhausted */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE( CSL_EDMA3_ITCCH_DIS, \
                                              CSL_EDMA3_TCCH_DIS, \
                                              CSL_EDMA3_ITCINT_DIS, \
                                              CSL_EDMA3_TCINT_EN, \
                                              1,CSL_EDMA3_TCC_NORMAL, \
                                              CSL_EDMA3_FIFOWIDTH_NONE, \
                                              TRUE,CSL_EDMA3_SYNC_A, \
                                              CSL_EDMA3_ADDRMODE_INCR, \
                                              CSL_EDMA3_ADDRMODE_INCR
                                             );           
    myParamSetup.srcAddr = (Uint32)srcBuff2;
    myParamSetup.dstAddr = (Uint32)dstBuff2;    
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParamPing,0);     
    status = CSL_edma3ParamSetup(hParamPong,&myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma pong parameter entry setup is failed\n");
        return;
    }
    
    /* Enable channel */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE, \
                                       NULL);
    if (status != CSL_SOK) {
        printf("Edma channel enable command is failed\n");
        return;
    }
    
    /* Initialize data */
    for (loopIndex = 0; loopIndex < 512; loopIndex++) {
        srcBuff1[loopIndex] = loopIndex;
        srcBuff2[loopIndex] = loopIndex;
        dstBuff1[loopIndex] = 0;
        dstBuff2[loopIndex] = 0;        
    }
    
    /* Manually trigger the channel */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
    if (status != CSL_SOK) {
        printf("Edma channel set command is failed\n");
        return;
    }
    
    regionIntr.region = CSL_EDMA3_REGION_5;
    regionIntr.intr = 0;
    regionIntr.intrh = 0;
    
    do {
        /* Poll on interrupt bit 0 */
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    } while (!(regionIntr.intr & 0x1));

    /* Clear interrupt bit 0 */
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR, \
                               &regionIntr);   
    if (status != CSL_SOK) {
        printf("Edma clear interrupt bit 0 command is failed\n");
        return;
    }
    
    /* Mapping channel 0 to event queue 1 */
    status = CSL_edma3HwChannelSetupQue(hChannel,CSL_EDMA3_QUE_1);
    if (status != CSL_SOK) {
        printf("Edma channel setup queue is failed\n");
        return;
    }

    /* Manually trigger the channel */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
    if (status != CSL_SOK) {
        printf("Edma channel set command is failed\n");
        return;
    }
    
    regionIntr.region = CSL_EDMA3_REGION_5;
    regionIntr.intr = 0;
    regionIntr.intrh = 0;
    
    /* Poll on interrupt pend bit 1 */
    do {   
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    } while (!(regionIntr.intr & 0x2));

    /* Clear interrupt bit 1 */
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR, \
                               &regionIntr);   
    if (status != CSL_SOK) {
        printf("Edma clear interrupt bit 1 command is failed\n");
        return;
    }
    
    /* Check transfer */
    if(Verify_Transfer(512, 1, 1, 0, 0, 0, 0, srcBuff1, dstBuff1,TRUE) == FALSE)
        passStatus = 0; 
    if(Verify_Transfer(512, 1, 1, 0, 0, 0, 0, srcBuff2, dstBuff2,TRUE) == FALSE)
        passStatus = 0;
           
    if (passStatus == 1)    
        printf ("<<EXAMPLE PASSED>>: Edma Ping Pong Buffer Transfer Passed\n");
    else {
        printf ("<<EXAMPLE FAILED>>: Edma Ping Pong Buffer Transfer Failed\n");
        return;
    }    
    
    
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

