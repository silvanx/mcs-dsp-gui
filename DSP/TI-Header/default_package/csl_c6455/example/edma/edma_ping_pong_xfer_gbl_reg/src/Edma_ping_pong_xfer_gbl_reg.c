/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *
 *   @file  Edma_ping_pong_xfer_gbl_reg.c
 *
 *   @path  $(CSLPATH)\example\edma\edma_ping_pong_xfer_gbl_reg\src
 *
 *   @desc  Example of EDMA
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This is an example of the CSL EDMA usage for the channel Initialization 
 *      for ping pong buffer transfer where channels are opened in the 
 *      global region. This example, 
 *        1. Initializes and opens the CSL EDMA module
 *        2. Sets up Edma module to default values 
 *        3. Opens EDMA channel 0 in the region 1
 *        4. Sets up the channel queue 3
 *        5. Gets the param handle for PARAM 0, 1, 2 
 *        6. Sets up the EDMA PARAM for ping and pong buffers
 *        7. Enables Interrupt (Bit 0-2) for the global region interrupts
 *        8. Manually triggers the channel 0
 *        9. Polls 0n IPR bit 0 and 2
 *        10. Clears the pending bit
 *        11. Does the data comparision to ensure the transffered data is proper 
 *            or not
 *        12. Displays the result based on step 11
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Edma_ping_pong_xfer_gbl_reg.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
 
/* ============================================================================
 *  Revision History
 *  ===============
 *  29-May-2004 Ruchika Kharwar    File Created.
 *
 *  16-Dec-2005 ds                Updated documentation 
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
Uint32       passStatus = 1;

/* Forward declaration */
void edma_ping_pong_xfer_gbl_region (void);

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
    edma_ping_pong_xfer_gbl_region ();
    
    return;
} 

/*
 * =============================================================================
 *   @func  edma_ping_pong_xfer_gbl_region
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the example routine which perform edma ping pong buffer transfer
 *      where channel is open in the global region.
 *      It implements following steps
 *          1. Intializes and Opens the Edma and Intc module.
 *          2. Sets up the interrupt for the edma global region.
 *          3. Sets up the edma module using the API csl_edma3Hwsetup () 
 *          4. Enables the edma global region
 *          5. Opens the channel nd get the param handle for PARAM 0, 1, 2
 *          6. Sets up the edma param entry for ping and pong buffers 
 *          7. Enables the edma interrupt using CSL_EDMA3_CMD_INTR_ENABLE. 
 *          7. Enables Interrupt (Bit 0-2) for the global region interrupts
 *          8. Manually triggers the channel 0
 *          9. Polls 0n IPR bit 0 
 *          10. Clear the pending bit
 *          11. Manually triggers the channel 0
 *          12. Polls 0n IPR bit 2 
 *          13. Clears the pending bit
 *          14. Compares the data in the destination buffer is proper or not.
 *          15. Closes the edma module and channel.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */

void edma_ping_pong_xfer_gbl_region (void)
{    
    CSL_Edma3Handle                 hModule;
    CSL_Edma3HwSetup                hwSetup;
    CSL_Edma3Obj                    edmaObj;
    CSL_Edma3ParamHandle            hParamPing;
    CSL_Edma3ParamHandle            hParamPong;
    CSL_Edma3ParamHandle            hParamBasic;
    CSL_Edma3ChannelObj             chObj;
    CSL_Edma3CmdIntr                regionIntr;
    CSL_Edma3ChannelHandle          hChannel;
    CSL_Edma3ParamSetup             myParamSetup;
    CSL_Edma3Context                context;
    CSL_Edma3ChannelAttr            chAttr;
    CSL_Status                      status;
    CSL_Edma3HwDmaChannelSetup      dmahwSetup;
    Uint32                          loopIndex;
        
   
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
           
    /* Channel open */
    chAttr.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
    hChannel = CSL_edma3ChannelOpen(&chObj, CSL_EDMA3, &chAttr, &status);
    if ((hChannel == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");    
        return;
    }
    
    /* Change Channel Default queue setup from 0 to 3  */
    status = CSL_edma3HwChannelSetupQue(hChannel,CSL_EDMA3_QUE_3);
    if (status != CSL_SOK) {
        printf ("Edma channel setup que failed\n");    
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
 
    /* Setup the parameter entry parameters (Ping buffer) */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                             CSL_EDMA3_TCCH_DIS, \
                                             CSL_EDMA3_ITCINT_DIS, \
                                             CSL_EDMA3_TCINT_EN, \
                                             0,CSL_EDMA3_TCC_NORMAL,\
                                             CSL_EDMA3_FIFOWIDTH_NONE, \
                                             CSL_EDMA3_STATIC_DIS, \
                                             CSL_EDMA3_SYNC_A, \
                                             CSL_EDMA3_ADDRMODE_INCR, \
                                             CSL_EDMA3_ADDRMODE_INCR );
    myParamSetup.srcAddr = (Uint32)srcBuff1;         
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(256,1);       
    myParamSetup.dstAddr = (Uint32)dstBuff1;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParamPong,0);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup.cCnt = 1;
    status = CSL_edma3ParamSetup(hParamBasic,&myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma parameter entry setup is failed\n");
        return;
    }

    /* Ping setup */
    status = CSL_edma3ParamSetup(hParamPing,&myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma ping parameter entry setup is failed\n");
        return;
    }
    
    /* Pong setup */    
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParamPing,0);     
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                             CSL_EDMA3_TCCH_DIS, \
                                             CSL_EDMA3_ITCINT_DIS, \
                                             CSL_EDMA3_TCINT_EN,\
                                             1,CSL_EDMA3_TCC_NORMAL,\
                                             CSL_EDMA3_FIFOWIDTH_NONE, \
                                             CSL_EDMA3_STATIC_EN, \
                                             CSL_EDMA3_SYNC_A, \
                                             CSL_EDMA3_ADDRMODE_INCR, \
                                             CSL_EDMA3_ADDRMODE_INCR );
    myParamSetup.srcAddr = (Uint32)srcBuff2;
    myParamSetup.dstAddr = (Uint32)dstBuff2;    
    status = CSL_edma3ParamSetup(hParamPong,&myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma ping parameter entry setup is failed\n");
        return;
    }
    
    /* Interrupt enable (Bits 0-1)  for the global region interrupts */
    regionIntr.region =  CSL_EDMA3_REGION_GLOBAL  ;   
    regionIntr.intr  =   0x3 ;   
    regionIntr.intrh  =  0x0000 ;
    CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);

    /* Trigger channel */
    CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL); 
    regionIntr.region =  CSL_EDMA3_REGION_GLOBAL  ;   
    regionIntr.intr  =   0 ;   
    regionIntr.intrh  =  0 ;

    /* Poll on IPR bit 0 */
    do {
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    } while (!(regionIntr.intr & 0x1));
    
    /* Clear the pending bit */
    CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR,&regionIntr);   
    
    /* Trigger Channel */
    CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
    
    /* Poll on IPR bit 2 */
    do {
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    } while (!(regionIntr.intr & 0x2));
    
    /* Check transfer by comparing the source and destination buffers */
    if(Verify_Transfer( 256, 1, 1, 0, 0, 0, 0, srcBuff1, dstBuff1, \
                                                               TRUE) == FALSE)
        passStatus = 0; 
    
    if(Verify_Transfer( 256, 1, 1, 0, 0, 0, 0, srcBuff2, dstBuff2, \
                                                               TRUE) == FALSE)
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

