/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *
 *   @file  Edma_sub_frame_xfer.c
 *
 *   @path  $(CSLPATH)\example\edma\edma_sub_frame_xfer\src
 *
 *   @desc  Example of EDMA
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This illustrates Edma Sub frame transfer
 *      This example do the following operations
 *       - Initializes and Opens the edma module
 *       - Sets up the Module
 *       - Enables (Bits 0-15) the Shadow Region 0 
 *       - Opens Channel 0 in context of Shadow region 0
 *       - Obtains a handles to parameters set 0
 *       - Sets up the param set 
 *       - Enables Channel and Initialize the data
 *       - Manually triggers the Channel
 *       - Polls on interrupt bit 0 and clears interrupt bit 0
 *       - Compares the transfered data
 *       - Displays the result based on previous step 
 * 
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Edma_sub_frame_xfer.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  08-Feb-2006 ds    File Created.
 *
 * =============================================================================
 */
 
#include <stdio.h>
#include <csl_edma3.h>
#include <soc.h>

/* Number of bytes to transfer */
#define NOF_BYTES_XFR   512

/* Globals */
Uint8       srcBuff1[NOF_BYTES_XFR];
Uint8       dstBuff1[NOF_BYTES_XFR];
Uint32      passStatus = 1;   

/* Forward declaration */
void edma_sub_frame_xfer (void);

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
    edma_sub_frame_xfer ();
    
    return;   
}

/*
 * =============================================================================
 *   @func  edma_sub_frame_xfer
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the example routine which perform edma sub frame transfer
 *      It implements following steps
 *       - Initializes and Opens the edma module
 *       - Sets up the Module
 *       - Enables (Bits 0-15) the Shadow Region 0 
 *       - Opens Channel 0 in context of Shadow region 0
 *       - Obtains a handles to parameters set 0
 *       - Sets up the param set 
 *       - Enables Channel and Initialize the data
 *       - Manually triggers the Channel
 *       - Polls on interrupt bit 0 and clears interrupt bit 0
 *       - Compares the transfered data
 *       - Displays the result based on previous step 
 *          
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void edma_sub_frame_xfer (void)
{
    CSL_Edma3Handle             hModule;
    CSL_Edma3HwSetup            hwSetup;
    CSL_Edma3Obj                edmaObj;
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
    
    /* Setup the first param set */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (CSL_EDMA3_ITCCH_DIS, \
                                              CSL_EDMA3_TCCH_DIS, \
                                              CSL_EDMA3_ITCINT_DIS, \
                                              CSL_EDMA3_TCINT_EN,\
                                              0, CSL_EDMA3_TCC_NORMAL,\
                                              CSL_EDMA3_FIFOWIDTH_NONE, \
                                              CSL_EDMA3_STATIC_EN, \
                                              CSL_EDMA3_SYNC_AB, \
                                              CSL_EDMA3_ADDRMODE_INCR, \
                                              CSL_EDMA3_ADDRMODE_INCR
                                             );           
    myParamSetup.srcAddr = (Uint32)srcBuff1;         
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(20,12);       
    myParamSetup.dstAddr = (Uint32)dstBuff1;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(40,20);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(CSL_EDMA3_LINK_NULL,0);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0, 1);     
    myParamSetup.cCnt = 1;
    status = CSL_edma3ParamSetup(hParamBasic, &myParamSetup);
    if (status != CSL_SOK) {
        printf("Edma parameter entry setup is failed\n");
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
    for (loopIndex = 0; loopIndex < 41; loopIndex++) {
        srcBuff1[loopIndex] = loopIndex;
        dstBuff1[loopIndex] = 0;
        
    }
    
     for (loopIndex = 41; loopIndex < NOF_BYTES_XFR; loopIndex++) {
        srcBuff1[loopIndex] = loopIndex + 12;
        dstBuff1[loopIndex] = 0;
        
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
    
    /* Check transfer */
    if(Verify_Transfer(20, 12, 1, 40, 20, 0, 0, srcBuff1, dstBuff1,TRUE) 
                                                                    == FALSE) {
       passStatus = 0; 
    }
              
    if (passStatus == 1)    
        printf ("<<EXAMPLE PASSED>>: Edma Sub Frame Transfer Passed\n");
    else {
        printf ("<<EXAMPLE FAILED>>: Edma Sub Frame Buffer Transfer Failed\n");
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

