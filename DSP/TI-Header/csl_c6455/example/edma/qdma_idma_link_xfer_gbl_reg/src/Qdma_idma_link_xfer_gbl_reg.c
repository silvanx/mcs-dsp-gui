/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *
 *   @file  Qdma_link_xfer_gbl_reg.c
 *
 *   @path  $(CSLPATH)\example\edma\qdma_idma_link_xfer_gbl_reg\src
 *
 *   @desc  Example of EDMA
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This is an example of the CSL EDMA usage for the QDMA Channel 
 *      Initialization for a linked transfer. 
 *      This example do the following operations
 *          1. Initializes and Opens the edma module
 *          2. Sets up the Module and gets the module setup values
 *          3. Opens qdma channel0 in the global region. 
 *          4. Maps channel to parameter entry 67
 *          5. Gets param handle for 64, 65, 66
 *          6. Links the param sets
 *              - Parameter set 67 is linked 66
 *              - Parameter set 66 is linked 65 
 *              - Parameter set 65 is linked 64
 *          7. Initializes the parameter entries using IDMA and
 *          8. IDMA trigger the transfer
 *          9. Polls for IPR bit and clears the bit
 *          10. Compares the transfered data
 *          11. Displays the result based on step 10
 *      Note:- Parameter Set 64 is marked as static
 * 
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Qdma_idma_link_xfer_gbl_reg.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
 
/* ============================================================================
 *  Revision History
 *  ===============
 *  08-July-2005 Ruchika Kharwar  File Created.
 *  16-Dec-2005 ds                Updated documentation 
 *  27-Mar-2006  ds               Added disable edma chhnel command
 * ============================================================================
 */

#include <stdio.h>
#include <csl_edma3.h>
#include <soc.h>
#include <csl_idma.h>

/* Globals */
Uint8       srcBuff0[64];
Uint8       srcBuff1[64];
Uint8       srcBuff2[64];
Uint8       srcBuff3[64];
Uint8       dstBuff0[64];
Uint8       dstBuff1[64];
Uint8       dstBuff2[64];
Uint8       dstBuff3[64];
Uint32       passStatus = 1;

#pragma DATA_ALIGN(myParamSetup, 32);
CSL_Edma3ParamSetup myParamSetup[4];

/* Forward declarations */
void qdma_link_xfer_gbl_region (void);

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
    qdma_link_xfer_gbl_region ();
    
    return;   
}

/*
 * =============================================================================
 *   @func  qdma_link_xfer_gbl_region
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the example routine which perform qdma link transfer where 
 *      channel is open in global region
 *      It implements following steps
 *          1. Initializes and Opens the edma module
 *          2. Sets up the Module and gets the module setup values
 *          3. Opens qdma channel0 in the global region. 
 *          4. Maps channel to parameter entry 67
 *          5. Gets param handle for 64, 65, 66
 *          6. Links the param sets
 *              - Parameter set 67 is linked 66
 *              - Parameter set 66 is linked 65 
 *              - Parameter set 65 is linked 64
 *          7. Initializes the parameter entries using IDMA and
 *          8. IDMA trigger the transfer
 *          9. Polls for IPR bit and clears the bit
 *          10. Compares the transfered data
 *          11. Closes edma module and channel
 *          
 *   @return
 *      NONE
 *
 * =============================================================================
 */

void qdma_link_xfer_gbl_region (void)
{
    CSL_Edma3Handle             hModule;
    CSL_Edma3HwSetup            hwSetup;
    CSL_Edma3Obj                edmaObj;
    CSL_Edma3ParamHandle        hParam64;
    CSL_Edma3ParamHandle        hParam65;
    CSL_Edma3ParamHandle        hParam66;
    CSL_Edma3ChannelObj         ChObj;
    CSL_Edma3CmdIntr            regionIntr;
    CSL_Edma3ChannelHandle      hChannel;
    CSL_Edma3Context            context;
    CSL_Edma3ChannelAttr        chAttr;
    CSL_Status                  status;
    CSL_Edma3HwQdmaChannelSetup qdmahwSetup[CSL_EDMA3_NUM_QDMACH] = \
                                            CSL_EDMA3_QDMACHANNELSETUP_DEFAULT;
    Uint32                      loopIndex;
    
    /* Initialize data  */
    for (loopIndex = 0; loopIndex < 64; loopIndex++) {
        srcBuff0[loopIndex] = loopIndex;
        srcBuff1[loopIndex] = loopIndex;
        srcBuff2[loopIndex] = loopIndex;
        srcBuff3[loopIndex] = loopIndex;
        dstBuff0[loopIndex] = 0;
        dstBuff1[loopIndex] = 0;
        dstBuff2[loopIndex] = 0;
        dstBuff3[loopIndex] = 0;        
    }  

    /* Module Initialization */
    status = CSL_edma3Init(&context);
    if (status != CSL_SOK) {
        printf ("Edma module initialization failed\n");   
        return;
    }
    
    /* Module Level Open */
    hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
    if ( (hModule == NULL) || (status != CSL_SOK)) {
        printf ("Edma module open failed\n");    
        return;
    }
    
    /* Module setup */
    hwSetup.dmaChaSetup  = NULL;
    hwSetup.qdmaChaSetup = &qdmahwSetup[0];
    status = CSL_edma3HwSetup(hModule, &hwSetup);
    if (status != CSL_SOK) {
         printf ("Hardware setup failed\n");
         CSL_edma3Close (hModule);
         return;
    } 
     
    /* Channel open  */
    chAttr.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chAttr.chaNum    = CSL_EDMA3_QCHA_0;
    hChannel = CSL_edma3ChannelOpen(&ChObj, CSL_EDMA3, &chAttr, &status);   
    if ((hChannel == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");    
        return;
    }
        
    /* Change channel to parameter entry mapping */
    status = CSL_edma3HwChannelSetupParam(hChannel, 67);
    if (status != CSL_SOK) {
        printf ("Edma channel to parameter entry mapping is failed\n");    
        return;
    }
    
    /* Obtain a handle to parameter set 66 */
    hParam66 = CSL_edma3GetParamHandle(hChannel,66,&status);
    if (hParam66 == NULL) {
        printf ("Edma get param handle for param entry 66 failed\n");        
        return;
    }
    
    /* Obtain a handle to parameter set 65 */
    hParam65 = CSL_edma3GetParamHandle(hChannel,65,&status);
    if (hParam65 == NULL) {
        printf ("Edma get param handle for param entry 65 failed\n");        
        return;
    }
    
    /* Obtain a handle to parameter set 64 */
    hParam64 = CSL_edma3GetParamHandle(hChannel,64,&status);
    if (hParam64 == NULL) {
        printf ("Edma get param handle for param entry 64 failed\n");        
        return;
    }
    
    /* Parameter setup for 64, 65, 66 param entries */
    myParamSetup[0].option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                                CSL_EDMA3_TCCH_DIS, \
                                                CSL_EDMA3_ITCINT_DIS, \
                                                CSL_EDMA3_TCINT_EN,\
                                                3,CSL_EDMA3_TCC_NORMAL,\
                                                CSL_EDMA3_FIFOWIDTH_NONE, \
                                                CSL_EDMA3_STATIC_EN, \
                                                CSL_EDMA3_SYNC_A, \
                                                CSL_EDMA3_ADDRMODE_INCR, \
                                                CSL_EDMA3_ADDRMODE_INCR);
    myParamSetup[0].srcAddr = (Uint32)srcBuff3;         
    myParamSetup[0].aCntbCnt = CSL_EDMA3_CNT_MAKE(64,1);       
    myParamSetup[0].dstAddr = (Uint32)dstBuff3;        
    myParamSetup[0] .srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
    myParamSetup[0].linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(
                                                          CSL_EDMA3_LINK_NULL, \
                                                          0);     
    myParamSetup[0].srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup[0].cCnt = 1;
    
    myParamSetup[1].option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                                CSL_EDMA3_TCCH_DIS, \
                                                CSL_EDMA3_ITCINT_DIS, \
                                                CSL_EDMA3_TCINT_DIS,\
                                                2,CSL_EDMA3_TCC_NORMAL,\
                                                CSL_EDMA3_FIFOWIDTH_NONE, \
                                                CSL_EDMA3_STATIC_DIS, \
                                                CSL_EDMA3_SYNC_A, \
                                                CSL_EDMA3_ADDRMODE_INCR, \
                                                CSL_EDMA3_ADDRMODE_INCR);
    myParamSetup[1].srcAddr = (Uint32)srcBuff2;         
    myParamSetup[1].aCntbCnt = CSL_EDMA3_CNT_MAKE(64,1);       
    myParamSetup[1].dstAddr = (Uint32)dstBuff2;        
    myParamSetup[1] .srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
    myParamSetup[1].linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParam64,0);     
    myParamSetup[1].srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup[1].cCnt = 1;

    myParamSetup[2].option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                                CSL_EDMA3_TCCH_DIS, \
                                                CSL_EDMA3_ITCINT_DIS, \
                                                CSL_EDMA3_TCINT_DIS,\
                                                1,CSL_EDMA3_TCC_NORMAL,\
                                                CSL_EDMA3_FIFOWIDTH_NONE, \
                                                CSL_EDMA3_STATIC_DIS, \
                                                CSL_EDMA3_SYNC_A, \
                                                CSL_EDMA3_ADDRMODE_INCR, \
                                                CSL_EDMA3_ADDRMODE_INCR);
    myParamSetup[2].srcAddr = (Uint32)srcBuff1;         
    myParamSetup[2].aCntbCnt = CSL_EDMA3_CNT_MAKE(64,1);       
    myParamSetup[2].dstAddr = (Uint32)dstBuff1;        
    myParamSetup[2] .srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
    myParamSetup[2].linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParam65,0);     
    myParamSetup[2].srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup[2].cCnt = 1;

    myParamSetup[3].option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                                CSL_EDMA3_TCCH_DIS, \
                                                CSL_EDMA3_ITCINT_DIS, \
                                                CSL_EDMA3_TCINT_DIS,\
                                                0,CSL_EDMA3_TCC_NORMAL,\
                                                CSL_EDMA3_FIFOWIDTH_NONE, \
                                                CSL_EDMA3_STATIC_DIS, \
                                                CSL_EDMA3_SYNC_A, \
                                                CSL_EDMA3_ADDRMODE_INCR, \
                                                CSL_EDMA3_ADDRMODE_INCR);
    myParamSetup[3].srcAddr = (Uint32)srcBuff0;         
    myParamSetup[3].aCntbCnt = CSL_EDMA3_CNT_MAKE(64,1);       
    myParamSetup[3].dstAddr = (Uint32)dstBuff0;        
    myParamSetup[3].srcDstBidx = CSL_EDMA3_BIDX_MAKE(1,1);     
    myParamSetup[3].linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(hParam66,0);     
    myParamSetup[3].srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,1);     
    myParamSetup[3].cCnt = 1;

    /* Enable channel  */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE, \
                                      NULL);
    if (status != CSL_SOK) {
        printf("Edma channel enable command failed\n");
        return;
    }
    
    /* Initialize the parameter entries using IDMA. Parameter entries are writtn 
     * linearly start with parameter entry 64. As soon as the last word in 
     * entry 67 is written the transfer gets triggered.
     */
    IDMA0_init(IDMA_INT_EN);
    IDMA0_configArgs(0x00000000, (Uint32*)myParamSetup,(Uint32*)hParam64, 0);
    IDMA0_wait(); 
    regionIntr.region = CSL_EDMA3_REGION_GLOBAL;
    
    /* Poll on IPR bit */
    do {
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    } while (!(regionIntr.intr & 0x8));
    
    /* Clear interrupt */
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR, \
                               &regionIntr);   
    if (status != CSL_SOK) {
        printf("Edma interrrupt clear command failed\n");
        return;
    }
    
    /* Check transfer by comparing the source and destination buffers */
    if(Verify_Transfer( 64, 1, 1, 0, 0, 0, 0, srcBuff0, dstBuff0,TRUE) == FALSE)
        passStatus = 0; 
        
    if(Verify_Transfer( 64, 1, 1, 0, 0, 0, 0, srcBuff1, dstBuff1,TRUE) == FALSE)
        passStatus = 0;
                 
    if(Verify_Transfer( 64, 1, 1, 0, 0, 0, 0, srcBuff2, dstBuff2,TRUE) == FALSE)
        passStatus = 0;         
        
    if(Verify_Transfer( 64, 1, 1, 0, 0, 0, 0, srcBuff3, dstBuff3,TRUE) == FALSE)
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

