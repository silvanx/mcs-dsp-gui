/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  Tcp2_shared_mode_example.c
 *
 *   @path  $(CSLPATH)\example\tcp2\tcp2_shared_mode\src
 *
 *   @desc  Example file for the TCP2 CSL
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *
 *  The example demonstrates the usage of the TCP2 CSL API for decoding the 
 *  input data in shared mode.
 *
 * ============================================================================
 * @n <b> Description </b>
 *    This is an example for the usage of the TCP2 CSL API in the shared
 *    mode.
 *
 *   @b Procedure  
 *      1 - Sets up the TCP2 input configuration parameters
 *      2 - Configures the EDMA to transfer the input paramters, 
 *          systematics and parity data, apriori data on successful TCPXEVT
 *      3 - Configures the EDMA for the extrinsics transfer on TCPREVT.
 *      4 - Starts the turbo coprocessor and waits for the completion of the 
 *          processing
 *      5 - After the state indicates the extrinsics are read, the example exits      
 *      6 - This demonstrates the usage only for the first sub frame of 
 *          a frame length = 51200
 *=============================================================================
 *      
 * The steps to run this example are as follows:
 *      1 - Open the Tcp2_shared_mode_example.pjt in the CCS studio 
 *      2 - Build the example
 *      3 - Execute the .out file
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  23-May-2005  sd File Created.
 *  05-Aug-2005  sd Changes for EDMA CSL
 *  17-Dec-2005  sd Added clearing the EDMA error registers before enabling the 
 *                  channel.
 *  05-Feb-2006  sd Changes according to the spec changes 
 *  21-Feb-2006  ds Added clearing the EDMA error registers at end of the 
 *                  example
 *  22-Mar-2006  ds Removed "mode" bit from TCP2_BaseParams structure 
 * =============================================================================
 */

#include <csl_tcp2.h>
#include <csl_tcp2Aux.h>
#include <csl_edma3.h>
#include <stdio.h>
#include <cslr_dev.h>

/* defines */

/* To load the interleaver RAM*/
#define INTERLEAVER_LOAD_FLAG    FALSE 

/* Maximum iterations of the TCP */
#define MAX_TCP_ITERATIONS  8

/* Maximum iterations of the TCP */
#define MIN_TCP_ITERATIONS  1

/* Output paramters read flag */
#define OUT_PARAM_READ_FLAG    FALSE 

/* prolog size  */
#define PROLOG_SIZE     32

/* CRC Polynomial */
#define CRC_POLY        0

/* CRC length */
#define CRC_LEN         0

/* EDMA PARAM size */
#define EDMA_PARAM_SIZE 0x20

/* Frame length of the TCP input data */
Uint32 frameLength = 51200;

/* externs */
extern TCP2_TailData tailData [];
extern TCP2_UserData sysParData [];
extern TCP2_ExtrinsicData aprioriData [];
extern TCP2_ExtrinsicData extrinsicData [];

/* globals */
Uint8 extrinsicBuffer1 [51200];
Uint8 extrinsicBuffer2 [51200];

/* TCP input configuration structure */
TCP2_ConfigIc   configIc [3]; 

/* EDMA CSL configuration structures */
CSL_Edma3Context context;
CSL_Edma3ChannelObj ChObj, ChObj1;
CSL_Edma3Obj edmaObj;
CSL_Edma3ChannelHandle hChannel, hChannel1;
CSL_Edma3ParamHandle hParam[24]; 
CSL_Edma3ParamSetup myParamSetup;
CSL_Edma3ChannelAttr chParam, chParam1;
CSL_Edma3ChannelErr chErrClear;

/* EDMA PARAM indexes */
Uint32 txParamIndex = 0;
Uint32 rxParamIndex = 20;

/* forward declarations */
Uint16 tcp2_configEdma (
    Uint32*  inputRegs,
    Uint8*   aprioriData,
    Uint8*   extrinsicBuffer,
    Uint32   txDataLen,
    Uint32   aprioriTxlen,
    Uint32   rxDataLen,
    Bool     endConfig
);
/*
 * ============================================================================
 *   @func   main ()
 *
 *   @desc
 *      Example to show the usage of the TCP2 CSL API for shared mode 
 *      processing
 *
 *   @b Arguments
 *   @verbatim
        None
     @endverbatim
 *
 *   <b> Return Value </b>  None
 *      
 *   @b Procedure  
 *      1 - Sets up the TCP2 input configuration parameters
 *      2 - Configures the EDMA to transfer the input paramters, 
 *          systematics and parity data, apriori data on successful TCPXEVT
 *      3 - Configures the EDMA for the extrinsics transfer on TCPREVT.
 *      4 - Starts the turbo coprocessor and waits for the completion of the 
 *          processing
 *      5 - After the state indicates the extrinsics are read, the example exits      
 *
 * ============================================================================
 */

void main (
    void
)
{
    TCP2_BaseParams configBase; /* base params to configure TCP2 */
    TCP2_Params     configParams [2]; /* holds all the input configuration 
                                     parameters for TCP*/
    TCP2_Params     *tempParams;  
    
        
    Uint32          frameLen = frameLength;
    Uint32          cnt;
    Uint32          txDataLen = 0, rxDataLen = 0, aprioriTxLen = 0;
    Uint32          extIndex, aprIndex;
    
    /* Enable the TCP2 in power saver */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, UNLOCK);

    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TCPCTL, ENABLE);

    while (CSL_DEV_PERSTAT0_TCPSTAT_ENABLE != 
            CSL_FEXT (((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, DEV_PERSTAT0_TCPSTAT));

    /* setup the base params */
    configBase.frameLen     = frameLen;
    configBase.inputSign    = TCP2_INPUT_SIGN_POSITIVE;
    configBase.intFlag      = INTERLEAVER_LOAD_FLAG;
    configBase.maxIter      = MAX_TCP_ITERATIONS;
    configBase.maxStarEn    = FALSE;
    configBase.standard     = TCP2_STANDARD_3GPP;
    configBase.crcLen       = 0;  /* Disable CRC */
    configBase.crcPoly      = 0;  /* not used */
    configBase.minIter      = MIN_TCP_ITERATIONS;
    configBase.numCrcPass   = 0; /* default value */
    configBase.outParmFlag  = OUT_PARAM_READ_FLAG;
    configBase.outputOrder  = TCP2_OUT_ORDER_0_31;
    configBase.prologRedEn  = FALSE;
    configBase.prologSize   = PROLOG_SIZE;
    configBase.rate         = TCP2_RATE_1_3;
    configBase.snr          = 0; /* disable SNR threshold checking */
    configBase.map          = TCP2_MAP_MAP1;
    
    /* assign the extrinsic scaling factors */
    for (cnt = 0; cnt < 16; cnt++)
        configBase.extrScaling [cnt] = 0;

    /* setup the TCP configuration registers parmeters */
    TCP2_genParams (&configBase, configParams);

    /* generate the configuration register values */
    
    /* For the first sub frame */
    TCP2_genIc (&configParams [0], tailData, &configIc [0]); 

    /* for the middle sub frame */
    tempParams = &configParams [0];
    tempParams->mode = TCP2_MIDDLE_SF;
    
    TCP2_genIc (tempParams, tailData, &configIc [1]); 
    
    /* For the last sub frame */
    TCP2_genIc (&configParams [1], tailData, &configIc [2]); 

    /* configure the Endian register */
    TCP2_setInterEndian (CSL_TCP2_TCPEND_ENDIAN_INTR_32BITS);
    TCP2_setExtEndian (CSL_TCP2_TCPEND_ENDIAN_EXTR_32BITS);

    /* configure the sleep modes */
    TCP2_setSlpzvdd (CSL_TCP2_TCPEND_SLPZVDD_EN_ENABLE);
    TCP2_setSlpzvss (CSL_TCP2_TCPEND_SLPZVSS_EN_ENABLE);

    /* Configure EDMA to write/read TCP data on app. events */
    /* MAP 1 configuration */
    /* set the index for extrinsics */
    extIndex = 0;
    aprIndex = 0;
    /* for the first sub frame */
    tempParams = &configParams [0];
    
    txDataLen = tempParams->frameLen + tempParams->prologSize;
    if ((txDataLen % 2) !=0)
        txDataLen++;
        
    aprioriTxLen = tempParams->frameLen + tempParams->prologSize;
    if ((aprioriTxLen % 2) !=0)
        aprioriTxLen++;

    rxDataLen = tempParams->frameLen;
    if ((rxDataLen % 2) !=0)
        rxDataLen++;

    tcp2_configEdma ((Uint32*)&configIc [0], &aprioriData [aprIndex], 
        &extrinsicBuffer1 [extIndex], txDataLen, aprioriTxLen, rxDataLen,
        TRUE);

 
    /* Enable Channel */
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);

    /* Enable Channel */
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);


    /* reset and start the TCP */
    TCP2_reset ();
    TCP2_start ();
    
    /* wait for the status to indicate extrinsics to be read */
    while (0x0B != TCP2_statTcpState ());
    printf ("Reading the extrinsics \n");

    /* wait for the status to indicate the extrinsics read complete */    
    while (0x01 == TCP2_statWaitExt ());
    printf ("Reading the extrinsics complete \n");
    
    /* Disable cahnnels and clear the EDMA event registers */
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    
    /* clear the EDMA error registers */
    chErrClear.missed = TRUE;
    chErrClear.secEvt = TRUE;
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEARERR, 
                               &chErrClear);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEARERR, 
                               &chErrClear);

    printf ("Example complete \n");

}

/*
 * =============================================================================
 *   @func   tcp2_configEdma
 *   @desc
 *      Configures EDMA channels 30 and 31. 
 *      For channel 31 there are 3 param entries(0, 1 and 2) which are linked. 
 *          Link 0 transfers the TCP2 input configuration register values.
 *          Link 1 transfer the systematics and parity data.
 *          Link 2 transfers the apriori data
 *      For channel 30 there is 1 param entry (3).
 *          Link 3 transfers the extrinsic data.
 *
 *   @expected result
 *      
 *
 *   @eg
 *      tcp2_configEdma();  
 * =============================================================================
 */
Uint16 tcp2_configEdma (
    Uint32 *inputRegs,
    Uint8  *aprioriData,    
    Uint8  *extrinsicBuffer,
    Uint32  txDataLen,
    Uint32  aprioriTxlen,
    Uint32  rxDataLen,
    Bool    endConfig
)
{
    volatile Uint16             count;
    CSL_Status                  chStatus, chStatus1;

    CSL_edma3Init(&context);
    
    CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&chStatus);

    /* Channel Configuration for TCPXEVT event */
    /* Channel Open */
    if (txParamIndex == 0){ /* open it only the first time */
        chParam.regionNum = CSL_EDMA3_REGION_GLOBAL;
        chParam.chaNum = CSL_EDMA3_CHA_TCP2XEVT;
        hChannel = CSL_edma3ChannelOpen(&ChObj, CSL_EDMA3, &chParam, &chStatus);
        if ((chStatus != CSL_SOK) || (hChannel == NULL)) {
            printf("Error in EDMA channel open function\n");
            return 0;
        }

        /* Channel Setup for PaRAM entry 0 */
        if (CSL_SOK != CSL_edma3HwChannelSetupParam(hChannel, txParamIndex )){
            printf("Error is EDMA channel setup for channel #31\n");
            return 0;
        }
    
        if (CSL_SOK != CSL_edma3HwChannelSetupQue(hChannel, CSL_EDMA3_QUE_0)) {
            printf("Error is EDMA channel setup for channel #31\n");
            return 0;
        }
    }
    
    /* Setup EDMA to transmit the input configuration parameters  */
    hParam[txParamIndex] = CSL_edma3GetParamHandle (hChannel, txParamIndex, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(FALSE, FALSE, FALSE, FALSE, 0,
                                                CSL_EDMA3_TCC_NORMAL,
                                                CSL_EDMA3_FIFOWIDTH_NONE,
                                                FALSE,CSL_EDMA3_SYNC_A,
                                                CSL_EDMA3_ADDRMODE_INCR,
                                                CSL_EDMA3_ADDRMODE_INCR); 
                                                          
    myParamSetup.srcAddr = (Uint32)inputRegs;
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(0, 0);     
    myParamSetup.dstAddr = (Uint32)CSL_TCP2_CFG_REGS;
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(
                        ((txParamIndex+1) * EDMA_PARAM_SIZE), 0);  /* offset
                                                     to the next PARAM entry */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(sizeof (TCP2_ConfigIc), 1); 
    myParamSetup.cCnt = 1;
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[txParamIndex], &myParamSetup)) {
        printf("Error in EDMA PARAM setup for entry #0\n");
        return 0;
    }

    /* Setup link to transmit systematics and parity data using param */
    txParamIndex++;
    hParam[txParamIndex] = CSL_edma3GetParamHandle (hChannel, txParamIndex, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(FALSE, FALSE, FALSE, FALSE, 0,
                                                CSL_EDMA3_TCC_NORMAL,
                                                CSL_EDMA3_FIFOWIDTH_NONE,
                                                FALSE,CSL_EDMA3_SYNC_AB,
                                                CSL_EDMA3_ADDRMODE_INCR,
                                                CSL_EDMA3_ADDRMODE_INCR); 
                                                          
    myParamSetup.srcAddr = (Uint32)sysParData;
    myParamSetup.dstAddr = (Uint32)CSL_TCP2_X0_MEM;
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(8, 8);     
    /* length of the systematic and  parity data to be transferred */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(8, (txDataLen/2)); //txDataLen 
    /* linking to the offset to the next PARAM entry */
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(
                        ((txParamIndex+1) * EDMA_PARAM_SIZE), 0);     
    myParamSetup.cCnt = 1;
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0, 0);     
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[txParamIndex], &myParamSetup)) {
        printf("Error in EDMA PARAM setup for entry #1\n");
        return 0;
    }
    txParamIndex++;
    
    /* Setup link to transmit apriori data using param */
    hParam[txParamIndex] = CSL_edma3GetParamHandle (hChannel, txParamIndex, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(FALSE, FALSE, FALSE, FALSE, 0,
                                                CSL_EDMA3_TCC_NORMAL,
                                                CSL_EDMA3_FIFOWIDTH_NONE,
                                                FALSE,CSL_EDMA3_SYNC_A,
                                                CSL_EDMA3_ADDRMODE_INCR,
                                                CSL_EDMA3_ADDRMODE_INCR); 
                                                          
    myParamSetup.srcAddr = (Uint32)aprioriData;
    myParamSetup.dstAddr = (Uint32)CSL_TCP2_W1_MEM;
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(0, 0);     
    /* length of the apriori data to be transferred */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(aprioriTxlen, 1);  
    myParamSetup.cCnt = 1;
    if (!endConfig) {                                       
        myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (
                                        ((txParamIndex+1) * EDMA_PARAM_SIZE), 0);     
    }
    else {
        myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (
                                        CSL_EDMA3_LINK_NULL, 0);     
    }                                        
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[txParamIndex], &myParamSetup)) {
        /* 
         * link this with the next transfer to be configured unless this 
         *                                       is the last iteration 
         */
        printf("Error in EDMA PARAM setup for entry #2\n");
        return 0;
    }
    
    /* increment to the next PARAM index */
    txParamIndex++;
      
    /* Receive Channel Open */
    if (rxParamIndex == 20) { /* open the channel only once */
        chParam1.regionNum = CSL_EDMA3_REGION_GLOBAL;
        chParam1.chaNum = CSL_EDMA3_CHA_TCP2REVT;
        hChannel1 = CSL_edma3ChannelOpen (&ChObj1, CSL_EDMA3, &chParam1, 
                                                            &chStatus1);
        if ((chStatus1 != CSL_SOK) | (hChannel1 == NULL)) {
            printf("Error in EDMA channel open function\n");
            return 0;
        }

        /* Channel Setup */
        if (CSL_SOK != CSL_edma3HwChannelSetupParam(hChannel1, rxParamIndex))
        {
            printf("Error is EDMA channel setup for channel #30\n");
            return 0;
        }
        if (CSL_SOK != CSL_edma3HwChannelSetupQue(hChannel1, CSL_EDMA3_QUE_0))
        {
            printf("Error is EDMA channel setup for channel #30\n");
            return 0;
        }
    }

   /* Channel Setup */

    /* configure param entry 3 to read the extrinsics data */
    hParam[rxParamIndex] = CSL_edma3GetParamHandle (hChannel1, rxParamIndex, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
                                             CSL_EDMA3_TCC_NORMAL,
                                             CSL_EDMA3_FIFOWIDTH_NONE,
                                             FALSE,CSL_EDMA3_SYNC_A,
                                             CSL_EDMA3_ADDRMODE_INCR,
                                             CSL_EDMA3_ADDRMODE_INCR);           
    myParamSetup.srcAddr = (Uint32)CSL_TCP2_W0_MEM;
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (rxDataLen, 1); /* number of bytes of 
                                    apriori data to be read */      
    myParamSetup.dstAddr = (Uint32)extrinsicBuffer;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE (0, 0);     
    /* 
     * link this with the next transfer to be configured unless this 
     *                                       is the last iteration 
     */
    if (!endConfig) {                                       
        myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (
                                        ((rxParamIndex+1) * EDMA_PARAM_SIZE), 0);     
    }
    else {
        myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (
                                        CSL_EDMA3_LINK_NULL, 0);     
    }                                        
                                        
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE (0, 0);     
    myParamSetup.cCnt = 1;
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[rxParamIndex], &myParamSetup)) {
        printf("Error in EDMA paRam setup for entry #3\n");
        return 0;
    }
    
    /* increment to the next PARAM index */
    rxParamIndex++;
    return 1;
}

