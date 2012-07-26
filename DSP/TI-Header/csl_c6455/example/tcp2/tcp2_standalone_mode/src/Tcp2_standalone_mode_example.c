/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  Tcp2_standalone_mode_example.c
 *
 *   @path  $(CSLPATH)\example\tcp2\tcp2_standalone_mode\src
 *
 *   @desc  Example file for the TCP2 CSL
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *  The example demonstrates the usage of the TCP2 CSL API for decoding the 
 *  input data in stand alone mode.
 *
 * ============================================================================
 * @n <b> Description </b>
 *    This is an example for the usage of the TCP2 CSL API in the standalone
 *    mode.
 *
 *   @b Procedure  
 *      1 - Sets up the TCP2 input configuration parameters
 *      2 - Configures the EDMA to transfer the input paramters, 
 *          systematics and parity data, interleaver data on successful TCPXEVT
 *      3 - Configures the EDMA for the hard decisions transfer on TCPREVT.
 *      4 - Starts the turbo coprocessor and waits for the completion of the 
 *          processing
 *      5 - After the state indicates the hard decisions are read, they are 
 *          displayed.
 *=============================================================================
 *      
 * The steps to run this example are as follows:
 *      1 - Open the Tcp2_standalone_mode_example.pjt in the CCS studio 
 *      2 - Build the example
 *      3 - Execute the .out file
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  23-May-2005  sd File Created.
 *  05-Aug-2005  sd Changes for EDMA CSL
 *  17-Dec-2005  sd Adding EDMA error registers clearing before enabling 
 *                  the channel
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
#define INTERLEAVER_LOAD_FLAG    TRUE 

/* Maximum iterations of the TCP */
#define MAX_TCP_ITERATIONS  8

/* Maximum iterations of the TCP */
#define MIN_TCP_ITERATIONS  1

/* Output paramters read flag */
#define OUT_PARAM_READ_FLAG    TRUE 

/* prolog size  */
#define PROLOG_SIZE     24

/* externs */
/* systematic and parity data to be input to TCP */
extern Uint32 sysParData [];

/* Interleaver table to be input to TCP */
extern Uint32 interleaverTbl [];

/* tail data for TCP configuration */
extern Int8  tailData [];

/* Hard decisions expected */
extern Uint32 hdRefBuff [];

/* Frame length of the TCP input data */
extern Uint32 frameLength;

/* globals */

/* TCP input configuration structure */
TCP2_ConfigIc   configIc; 

/* EDMA CSL configuration structures */
CSL_Edma3Context context;
CSL_Edma3ChannelObj ChObj, ChObj1;
CSL_Edma3Obj edmaObj;
CSL_Edma3ChannelHandle hChannel, hChannel1;
CSL_Edma3ParamHandle hParam[4];  
CSL_Edma3ParamSetup myParamSetup;
CSL_Edma3ChannelAttr chParam, chParam1;
CSL_Edma3ChannelErr chErrClear;

/* forward declarations */
Uint16 tcp2_configEdma (
    Uint32  *hdDecisionBuffer
);
/*
 * ============================================================================
 *   @func   main ()
 *
 *   @desc
 *      Example to show the usage of the TCP2 CSL API for standalone mode 
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
 *          systematics and parity data, interleaver data on successful TCPXEVT
 *      3 - Configures the EDMA for the hard decision transfer on TCPREVT.
 *      4 - Starts the turbo coprocessor and waits for the completion of the 
 *          processing
 *      5 - After the state indicates the hard decisions are read, they are 
 *          displayed.
 *
 *
 * ============================================================================
 */

void main (
    void
)
{
    TCP2_BaseParams configBase; /* base params to configure TCP2 */
    TCP2_Params     configParams; /* holds all the input configuration 
                                     parameters for TCP*/
           

        
    Uint32          frameLen = frameLength;
    Uint32          cnt;
    Uint32          numHd; /* number of hard decisions */
    Uint32          *hdDecisionBuffer; /* to hold the hard decisions */

    
    /* Enable the TCP2 in power saver */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, UNLOCK);

    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TCPCTL, ENABLE);

    while (CSL_DEV_PERSTAT0_TCPSTAT_ENABLE != 
            CSL_FEXT (((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, DEV_PERSTAT0_TCPSTAT));

    /* calculate the number of hard decision 32 bit words expected */
    numHd = frameLen / 32; /* for 32 bits */
    
    /** account for the hard decision data if the frame len is not 
      * 32 bit aligned
      */
    if (0 != (frameLen % 32))
        numHd++;
        
    /* Allocate memory for the hard decisions */
    hdDecisionBuffer = (Uint32*) malloc ( sizeof (Uint32) * numHd);
    
    /* setup the base params */
    configBase.frameLen     = frameLen;
    configBase.inputSign    = TCP2_INPUT_SIGN_POSITIVE;
    configBase.intFlag      = INTERLEAVER_LOAD_FLAG;
    configBase.maxIter      = MAX_TCP_ITERATIONS;
    configBase.maxStarEn    = TRUE;
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
    
    /* assign the extrinsic scaling factors */
    for (cnt = 0; cnt < 16; cnt++)
        configBase.extrScaling [cnt] = 32;

    /* setup the TCP configuration registers parmeters */
    TCP2_genParams (&configBase, &configParams);

    /* generate the configuration register values */
    TCP2_genIc (&configParams, tailData, &configIc); 

    /* configure the Endian register */
    TCP2_setInterEndian (CSL_TCP2_TCPEND_ENDIAN_INTR_32BITS);
    TCP2_setExtEndian (CSL_TCP2_TCPEND_ENDIAN_EXTR_32BITS);

    /* configure the sleep modes */
    TCP2_setSlpzvdd (CSL_TCP2_TCPEND_SLPZVDD_EN_ENABLE);
    TCP2_setSlpzvss (CSL_TCP2_TCPEND_SLPZVSS_EN_ENABLE);

    /* Configure EDMA to write/read TCP data on app. events */
    tcp2_configEdma (hdDecisionBuffer);
    
    /* Disable cahnnels and clear the EDMA event registers */
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    

    /* Enable Channel */
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);

    /* reset and start the TCP */
    TCP2_reset ();
    TCP2_start ();
    
    /* wait for the status to indicate hard decisions are read */
    while (0xA != TCP2_statTcpState ());

    /* compare the hard decisions and check if they are as expected */
    for (cnt = 0; cnt < numHd; cnt++) {
        printf ("Hard decisions : 0x%x \n", hdDecisionBuffer [cnt]);
    } /* end of for */

    /*  free the allocated memory */
    free (hdDecisionBuffer);
    
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
 *          Link 2 transfers the interleaver data
 *      For channel 30 there is 1 param entry (3).
 *          Link 3 transfers the Hard decisions.
 *
 *
 *   @eg
 *      tcp2_configEdma();  
 * =============================================================================
 */
Uint16 tcp2_configEdma (
    Uint32  *hdDecisionBuffer
)
{
    volatile Uint16             count;
    CSL_Status                  chStatus, chStatus1;

    CSL_edma3Init(&context);
    
    CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&chStatus);

    /* Channel Configuration for TCPXEVT event */
    /* Channel Open */
    chParam.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chParam.chaNum = CSL_EDMA3_CHA_TCP2XEVT;
    hChannel = CSL_edma3ChannelOpen(&ChObj, CSL_EDMA3, &chParam, &chStatus);
    if ((chStatus != CSL_SOK) || (hChannel == NULL)) {
        printf("Error in EDMA channel open function\n");
        return 0;
    }

    /* Channel Setup for PARAM entry 0 */
    if (CSL_SOK != CSL_edma3HwChannelSetupParam(hChannel, 0 )){
        printf("Error is EDMA channel setup for channel #31\n");
        return 0;
    }
    
    if (CSL_SOK != CSL_edma3HwChannelSetupQue(hChannel, CSL_EDMA3_QUE_0)) {
        printf("Error is EDMA channel setup for channel #31\n");
        return 0;
    }

    /* Setup EDMA to transmit the input configuration parameters  */
    hParam[0] = CSL_edma3GetParamHandle (hChannel, 0, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(FALSE, FALSE, FALSE, FALSE, 0,
                                                CSL_EDMA3_TCC_NORMAL,
                                                CSL_EDMA3_FIFOWIDTH_NONE,
                                                FALSE,CSL_EDMA3_SYNC_A,
                                                CSL_EDMA3_ADDRMODE_INCR,
                                                CSL_EDMA3_ADDRMODE_INCR); 
                                                          
    myParamSetup.srcAddr = (Uint32)&configIc;
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(1, 1);     
    myParamSetup.dstAddr = (Uint32)CSL_TCP2_CFG_REGS;
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(0x20, 0);  /* offset
                                                     to the next PARAM entry */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(sizeof (configIc), 1); 
    myParamSetup.cCnt = 1;
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[0], &myParamSetup)) {
        printf("Error in EDMA PARAM setup for entry #0\n");
        return 0;
    }

    /* Setup link to transmit systematics and parity data using param 1*/
    hParam[1] = CSL_edma3GetParamHandle (hChannel, 1, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(FALSE, FALSE, FALSE, FALSE, 0,
                                                CSL_EDMA3_TCC_NORMAL,
                                                CSL_EDMA3_FIFOWIDTH_NONE,
                                                FALSE,CSL_EDMA3_SYNC_A,
                                                CSL_EDMA3_ADDRMODE_INCR,
                                                CSL_EDMA3_ADDRMODE_INCR); 
                                                          
    myParamSetup.srcAddr = (Uint32)sysParData;
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(1, 1);     
    myParamSetup.dstAddr = (Uint32)CSL_TCP2_X0_MEM;
    /* linking to the offset to the next PARAM entry */
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(0x40, 0);     
    /* length of the systematic and  parity data to be transferred */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(frameLength * 4, 1);  

    myParamSetup.cCnt = 1;
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[1], &myParamSetup)) {
        printf("Error in EDMA paRam setup for entry #1\n");
        return 0;
    }
      
    /* Setup link to transmit interleaver data */
    hParam[2] = CSL_edma3GetParamHandle (hChannel, 2, &chStatus); /* param entry 2 */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(FALSE, FALSE, FALSE, FALSE, 0,
                                                CSL_EDMA3_TCC_NORMAL,
                                                CSL_EDMA3_FIFOWIDTH_NONE,
                                                FALSE,CSL_EDMA3_SYNC_A,
                                                CSL_EDMA3_ADDRMODE_INCR,
                                                CSL_EDMA3_ADDRMODE_INCR); 
                                                          
    myParamSetup.srcAddr = (Uint32)interleaverTbl;
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(1, 1);     
    myParamSetup.dstAddr = (Uint32)CSL_TCP2_I0_MEM;
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (
                                        CSL_EDMA3_LINK_NULL, 0);
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(88, 1); 
                        /* number of bytes of interleaver data */ 
                        
    myParamSetup.cCnt = 1;
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[2], &myParamSetup)) {
        printf("Error in EDMA PARAM setup for entry #2\n");
        return 0;
    }
      
    /* Receive Channel Open */
    chParam1.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chParam1.chaNum = CSL_EDMA3_CHA_TCP2REVT;
    hChannel1 = CSL_edma3ChannelOpen (&ChObj1, CSL_EDMA3, &chParam1, 
                                                        &chStatus1);
    if ((chStatus1 != CSL_SOK) | (hChannel1 == NULL)) {
        printf("Error in EDMA channel open function\n");
        return 0;
    }

    /* Channel Setup */
    if (CSL_SOK != CSL_edma3HwChannelSetupParam(hChannel1, 3 /* PaRAM entry 3*/))
    {
        printf("Error is EDMA channel setup for channel #30\n");
        return 0;
    }
    if (CSL_SOK != CSL_edma3HwChannelSetupQue(hChannel1, CSL_EDMA3_QUE_0))
    {
        printf("Error is EDMA channel setup for channel #30\n");
        return 0;
    }

   /* Channel Setup */

    /* configure param entry 3 to read the hard decisions */
    hParam[3] = CSL_edma3GetParamHandle (hChannel1, 3, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
                                             CSL_EDMA3_TCC_NORMAL,
                                             CSL_EDMA3_FIFOWIDTH_NONE,
                                             FALSE,CSL_EDMA3_SYNC_A,
                                             CSL_EDMA3_ADDRMODE_INCR,
                                             CSL_EDMA3_ADDRMODE_INCR);           
    myParamSetup.srcAddr = (Uint32)CSL_TCP2_O0_MEM;
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (8, 1); /* number of bytes of 
                                    hard decision data to be read */      
    myParamSetup.dstAddr = (Uint32)hdDecisionBuffer;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE (1, 1);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (
                                        CSL_EDMA3_LINK_NULL, 0);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE (1, 1);     
    myParamSetup.cCnt = 1;
    
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[3], &myParamSetup)) {
        printf("Error in EDMA PARAM setup for entry #3\n");
        return 0;
    }

    return 1;
}

