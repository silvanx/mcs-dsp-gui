/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */


/** ===========================================================================
 * @file  Vcp2_hard_decisions_example.c
 *
 * @path $(CSLPATH)\example\vcp2\vcp2_hard_decisions\src
 *
 * @desc  Example of usage of CSL of VCP2
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 * @n <b> Description </b>
 *    This is an example for the VCP2 CSL usage for computing hard decision
 *    against the given branch metric values.
 *
 * @n The branch metrics are transferred to the VCP and hard decisions are
 *    read from the VCP using EDMA. 
 * @verbatim
       1. Configure the 2 EDMA channels
       2. Configure the input configuration registers of VCP
       3. Enable EDMA channels
       4. Start VCP
       5. Wait until VCP run is complete
   @endverbatim
 *=============================================================================
 *      
 * @n <b> Procedure to run the example </b>
 * @verbatim
      1. Configure the CCS setup
      2. Please refer CCS manual for setup configuration and loading 
         proper GEL file
      3. Launch CCS window
      4. Open project Vcp2_hard_decisions_example.pjt
      5. Build the project and load the .out file of the project.
           
   @endverbatim
 *       
 *   
 * ============================================================================
 */


/* ============================================================================
 *  Revision History
 *  ===============
 *  20-May-2005   SPrasad     File Created.
 *  25-Jul-2005   Chandra     Updated to a new version of EDMA 3.x
 *  01-Aug-2005   Chandra     Beautified
 *  11-Aug-2005   Chandra     Minor format changes.
 *  14-Sep-2005   Chandra     Changes after review.
 *  19-Dec-2005   SD          Added clearing the EDMA error registers before 
 *                            enabling the channel   
 *  06-Feb-2006   SD          Changes according to spec changes
 *  24-Feb-2006   DS          Added clearing of EDMA channel error registers at
 *                            the end of example
 * ============================================================================
 */
#include <csl_vcp2.h>
#include <csl_vcp2Aux.h>
#include <csl_edma3.h>
#include <soc.h>
#include <stdio.h>
#include <string.h>
#include <Vcp2_example.h>
#include <cslr_dev.h>

#define BITS_IN_A_BYTE 8

/* Constraint length */
#define CONSTRAINT_LEN 5

/* Frame length */
#define FRAME_LENGTH    300

/* EDMA frame size */
#define DMA_BURST_SIZE  128

/* VCP input configuration transfer size */
#define VCPIC_DMA_SIZE  24

/* VCP out register transfer size */
#define VCPOUT_DMA_SIZE  8


/* Forward declarations */
Uint16 vcp2_configEdma (Uint32 inputBM, Uint32 outputHD
);

/* EDMA global declarations */
CSL_Edma3Context context;
CSL_Edma3ChannelObj ChObj, ChObj1;
CSL_Edma3Obj edmaObj;
CSL_Edma3ChannelHandle hChannel, hChannel1;
CSL_Edma3ParamHandle hParam[4];  /* Example uses 4 PaRAMs */
CSL_Edma3ParamSetup myParamSetup;
CSL_Edma3ChannelAttr chParam, chParam1;
CSL_Edma3ChannelErr chErrClear;

/* Globals */
VCP2_ConfigIc vcpConfig;
Uint32 ouputParams[2];
VCP2_ConfigIc vcpConfigRead;

/**
 * ============================================================================
 *   @func   main
 *   @desc
 *      Shows the usage of VCP2 CSL API for computing the hard decisions. 
 *   @n Various parameters of the input data (Branch metrics) provided
 *      are as follows.
 * @verbatim

       Frame length...................................300                                
       rate...........................................1/3
       constraint length..............................5
       Decision mode..................................Hard 
       Traceback Mode.................................Convergent
       Index of the initial max state metric(IMAXI)...0 
       output parameters read flag....................0
       Yamamoto bit enable............................False
       Yamamote threshold.............................N/A
       Traceback state enable.........................False 
       Traceback state index..........................N/A  
       DSP endian.....................................Little 
       Endian Register................................bm_endian
       Output order...................................0       

   @endverbatim
 *   @expected result
 *      Appropriate message will be logged depending on 
 *      the result
 *
 * ============================================================================
 */
void
main (
)
{
    Uint32 numSymProc, inputBM, outputHD, outputHD_bytes, outputHD_words;
    VCP2_Params vcpParams;
    VCP2_BaseParams vcpBaseParams;
    volatile Uint32 runStat;
	int index;

    /* Enable the VCP2 in power saver */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, UNLOCK);

    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_VCPCTL, ENABLE);

    while (CSL_DEV_PERSTAT0_VCPSTAT_ENABLE != 
            CSL_FEXT (((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, DEV_PERSTAT0_VCPSTAT));
    
    /* VCP configuration */
    
    vcpBaseParams.rate = VCP2_RATE_1_3;
    vcpBaseParams.constLen = CONSTRAINT_LEN;
    vcpBaseParams.frameLen = FRAME_LENGTH;
    vcpBaseParams.yamTh = 0;
    vcpBaseParams.stateNum = 0;
    vcpBaseParams.tbConvrgMode = TRUE;
    vcpBaseParams.decision = VCP2_DECISION_HARD;
    vcpBaseParams.readFlag = 1;
    vcpBaseParams.tailBitEnable = FALSE;
    vcpBaseParams.traceBackIndex = 0;
    vcpBaseParams.outOrder = 0;

    /* VCP configuration */
    VCP2_genParams (&vcpBaseParams, &vcpParams);

    VCP2_genIc (&vcpParams, &vcpConfig);

    /* Number of EDMA frames (transfers) for the branch metrics */
    inputBM = vcpParams.numBmFrames;

    /* Output hard decisions in terms of bytes rounded to upper byte */
    outputHD_bytes =
        VCP2_normalCeil (vcpBaseParams.frameLen + vcpBaseParams.constLen - 1,
        BITS_IN_A_BYTE);

    /* Output hard decisions in terms of words rounded to upper words */
    outputHD_words = VCP2_normalCeil (outputHD_bytes, sizeof (Uint32));

    /* Total number of bytes required to be transfered for the hard decisions */
    outputHD = outputHD_words * sizeof (Uint32);

    /* Configure EDMA */
    if (!(vcp2_configEdma (inputBM, outputHD))) {
        printf ("\nError in configuring EDMA\n");
        return;
    }

    /* clear the EDMA error registers */
    chErrClear.missed = TRUE;
    chErrClear.secEvt = TRUE;
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEARERR, 
                               &chErrClear);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEARERR, 
                               &chErrClear);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);

    /* Enable Channel */
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);
    /* Enable Channel */
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);

    /* write to the endian register */
    VCP2_setPacked32Endian ();

    /* Reset and Start VCP2 */
    VCP2_reset ();
    VCP2_emuDisable ();
    VCP2_start ();

    /* Wait till processing is over */
    do {
        runStat = VCP2_statRun ();
    } while (runStat == 1);
    printf ("VCP2 processing of data over\n");

    printf ("\nRESULT\n");
    printf ("~~~~~~\n");

    /* Get the number of symbols processed */
    numSymProc = VCP2_statSymProc ();
    printf ("Number of symbols processed = %d \n", numSymProc);

    /* Verify the hard decisions output */
	for (index = 0; index < ((vcpParams.frameLen / BITS_IN_A_BYTE)/4); index++) {
		if (hard_decision [index] != hard_decisionRef [index]) {
			break;
		}
	}

	if (index == ((vcpParams.frameLen / BITS_IN_A_BYTE)/4)) {
        printf ("\nHard decisions are computed properly\n");
    }
    else {
        printf ("\nHard decisions are not computed properly %d\n", index);
    }
    
    /* clear the EDMA error registers */
    chErrClear.missed = TRUE;
    chErrClear.secEvt = TRUE;
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEARERR, 
                               &chErrClear);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEARERR, 
                               &chErrClear);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    
    /* Close EDMA channel */
    CSL_edma3ChannelClose (hChannel);
    CSL_edma3ChannelClose (hChannel1);
}

/*
 * ============================================================================
 *   @func   vcp2_configEdma
 *   @desc
 *      Configures EDMA channels 28 and 29. 
 *   @n For channel 29 there are 2 param entries(0 &1) which are linked. 
 *   @n -   Link 0 transfers the VCP2 input configuration register values.
 *   @n -   Link 1 transfers Branch metrics.
 *   @n
 *   @n For channel 28 there 2 param entry (2 & 3).
 *   @n -   Link 2 transfers the Hard decisions.
 *   @n -   Link 3 transfers the VCPOUT values
 *
 *   @expected result
 *      Appropriate message will be logged depending on 
 *      the result
 *
 *   @eg
 *      vcp2_configEdma(inputBm, ouputHD);  
 * ============================================================================
 */
Uint16
vcp2_configEdma (
    Uint32 inputBM,
    Uint32 outputHD
)
{
    CSL_Status chStatus, chStatus1;
    Uint32 receive_link_offset, transmit_link_offset;
    
    /* EDMA Initialization */
    CSL_edma3Init (&context);

    CSL_edma3Open (&edmaObj, CSL_EDMA3, NULL, &chStatus);

    /* Channel Configuration for VCPXEVT event */
    /* Channel Open */
    chParam.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chParam.chaNum = CSL_EDMA3_CHA_VCP2XEVT;
    hChannel = CSL_edma3ChannelOpen (&ChObj, CSL_EDMA3, &chParam, &chStatus);
    if ((chStatus != CSL_SOK) || (hChannel == NULL)) {
        printf ("Error in EDMA channel open function\n");
        return 0;
    }

    /* Channel Setup */
    if (CSL_SOK != CSL_edma3HwChannelSetupParam (hChannel,
            0 /* PaRAM entry */ )) {
        printf ("Error in Tx EDMA channel setup\n");
        return 0;
    }
    if (CSL_SOK != CSL_edma3HwChannelSetupQue (hChannel,
       CSL_EDMA3_QUE_0)) {
        printf ("Error in Tx EDMA channel setup\n");
        return 0;
    }

    /* Channel Configuration for VCPREVT event */
    /* Channel Open */
    chParam1.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chParam1.chaNum = CSL_EDMA3_CHA_VCP2REVT;
    hChannel1 =
        CSL_edma3ChannelOpen (&ChObj1, CSL_EDMA3, &chParam1, &chStatus1);
    if ((chStatus1 != CSL_SOK) | (hChannel1 == NULL)) {
        printf ("Error in EDMA channel open function\n");
        return 0;
    }

    /* Channel Setup */
    if (CSL_SOK != CSL_edma3HwChannelSetupParam (hChannel1,
            2 /* PaRAM entry */ )) {
        printf ("Error in Rx EDMA channel setup\n");
        return 0;
    }
    if (CSL_SOK != CSL_edma3HwChannelSetupQue (hChannel1,
        CSL_EDMA3_QUE_0)) {
        printf ("Error in Rx EDMA channel setup\n");
        return 0;
    }

    /* Using PaRAMs 0, 1, 2, 3 */
    /* 0 and 1 are to transmit */
    /* 2 and 3 are to receive */
    hParam[0] = CSL_edma3GetParamHandle (hChannel, 0, &chStatus);
    hParam[1] = CSL_edma3GetParamHandle (hChannel, 1, &chStatus);
    hParam[2] = CSL_edma3GetParamHandle (hChannel1, 2, &chStatus);
    hParam[3] = CSL_edma3GetParamHandle (hChannel1, 3, &chStatus);

    /* Lower 4 nibbles of the PaRAM address forms the link offset */

    /* PaRAMs 0 and 1 are linked */
    transmit_link_offset = (Uint32)hParam[1] & 0x0000FFFF; 

    /* PaRAMs 2 and 3 are linked */
    receive_link_offset = (Uint32)hParam[3] & 0x0000FFFF;

    /*
     *  itcchEn   -    False
     *  tcchEn    -    False
     *  itcintEn  -    False
     *  tcintEn   -    False
     *  tcc       -    0
     *  tccMode   -    Normal completion (interrupt after transfer completion)
     *  fwid      -    SAM, DAM are to increment, so fwid = none
     *  stat      -    0, linking allowed
     *  syncDim   -    A - synchronization
     *  dam       -    Destination address increment
     *  sam       -    Source address increment
     */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
        CSL_EDMA3_TCC_NORMAL, CSL_EDMA3_FIFOWIDTH_NONE, FALSE,
        CSL_EDMA3_SYNC_A, CSL_EDMA3_ADDRMODE_INCR,
        CSL_EDMA3_ADDRMODE_INCR);                               /* Options */
    myParamSetup.srcAddr = (Uint32) & vcpConfig;         /* Source address */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (VCPIC_DMA_SIZE, 1);
                                /* Single transfer of VCPIC_DMA_SIZE bytes */
    myParamSetup.dstAddr = (Uint32) &hVcp2Vbus->VCPIC0;      /* Destination address */
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE (0, 0);
                                                      /* Index do not care */
    myParamSetup.linkBcntrld =
         CSL_EDMA3_LINKBCNTRLD_MAKE (transmit_link_offset, 0);  /* linking */
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE (0, 0);
                                                      /* Index do not care */
    myParamSetup.cCnt = 1;                                  /* CCount is 1 */
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[0], &myParamSetup)) {
        printf ("Error in EDMA paRam setup for VCP IC register transfer\n");
        return 0;
    }

    transmit_link_offset = (Uint32)hParam[2] & 0x0000FFFF; 

    /* Setup link to transmit branch metrics */
    /*
     *  itcchEn   -    False
     *  tcchEn    -    False
     *  itcintEn  -    False
     *  tcintEn   -    False
     *  tcc       -    0
     *  tccMode   -    Normal completion (interrupt after transfer completion)
     *  fwid      -    64-bit
     *  stat      -    0, linking allowed
     *  syncDim   -    A - synchronization
     *  dam       -    Destination is a FIFO
     *  sam       -    Source address increment
     */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
        CSL_EDMA3_TCC_NORMAL, CSL_EDMA3_FIFOWIDTH_64BIT, FALSE,
        CSL_EDMA3_SYNC_A, CSL_EDMA3_ADDRMODE_CONST,
        CSL_EDMA3_ADDRMODE_INCR);                                /* Options */
    myParamSetup.srcAddr = (Uint32) branch_metric;        /* Source address */
                                                /* Source address increment */

    myParamSetup.dstAddr = (Uint32) & (hVcp2Vbus->VCPWBM);
                                                     /* Destination address */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (DMA_BURST_SIZE, inputBM);
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE (DMA_BURST_SIZE, 0);
    myParamSetup.linkBcntrld =
        CSL_EDMA3_LINKBCNTRLD_MAKE (CSL_EDMA3_LINK_NULL, 0);
                                                              /* No linking */

                               /* inputBM transfers of DMA_BURST_SIZE bytes */
    myParamSetup.cCnt = 1;                                   /* CCount is 1 */
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[1], &myParamSetup)) {
        printf ("Error in EDMA paRam setup for branch metrics transfer\n");
        return 0;
    }

    /*
     *  itcchEn   -    False
     *  tcchEn    -    False
     *  itcintEn  -    False
     *  tcintEn   -    False
     *  tcc       -    0
     *  tccMode   -    Normal completion (interrupt after transfer completion)
     *  fwid      -    64-bit
     *  stat      -    0, linking allowed
     *  syncDim   -    A - synchronization
     *  dam       -    Destination to increment
     *  sam       -    Source is a FIFO
     */

    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
        CSL_EDMA3_TCC_NORMAL, CSL_EDMA3_FIFOWIDTH_64BIT, FALSE,
        CSL_EDMA3_SYNC_A, CSL_EDMA3_ADDRMODE_INCR,
        CSL_EDMA3_ADDRMODE_CONST);                               /* Options */
    myParamSetup.srcAddr = (Uint32)&(hVcp2Vbus->VCPRDECS);      /* Source */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (outputHD, 1);
                                           /* outputHD bytes in a transfer */
    myParamSetup.dstAddr = (Uint32) hard_decision;          /* Destination */
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE (0, outputHD);
                                                      
    myParamSetup.linkBcntrld =
         CSL_EDMA3_LINKBCNTRLD_MAKE (receive_link_offset, 0);  /* linking */

    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE (0, 0);
                                                      /* Index do not care */
    myParamSetup.cCnt = 1;                                       /* CCount */
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[2], &myParamSetup)) {
        printf ("Error in EDMA paRam setup for decisions read\n");
        return 0;
    }

    /*
     *  itcchEn   -    False
     *  tcchEn    -    False
     *  itcintEn  -    False
     *  tcintEn   -    False
     *  tcc       -    0
     *  tccMode   -    Normal completion (interrupt after transfer completion)
     *  fwid      -    SAM, DAM are to increment, so fwid = none
     *  stat      -    0, linking allowed
     *  syncDim   -    A - synchronization
     *  dam       -    Destination address increment
     *  sam       -    Source address increment
     */

    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
        CSL_EDMA3_TCC_NORMAL, CSL_EDMA3_FIFOWIDTH_NONE, FALSE,
        CSL_EDMA3_SYNC_A, CSL_EDMA3_ADDRMODE_INCR,
        CSL_EDMA3_ADDRMODE_INCR);                                 /* Options */
    myParamSetup.srcAddr = (Uint32) & (hVcp2Vbus->VCPOUT1);       /* Source */
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (VCPOUT_DMA_SIZE, 1);
                                 /* Transfer of VCPOUT_DMA_SIZE bytes 1 time */
    myParamSetup.dstAddr = (Uint32) & ouputParams[0];         /* Destination */
    myParamSetup.linkBcntrld =
        CSL_EDMA3_LINKBCNTRLD_MAKE (CSL_EDMA3_LINK_NULL, 0);
                                                               /* No linking */
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[3], &myParamSetup)) {
        printf ("Error in EDMA paRam setup for output registers read\n");
        return 0;
    }

    return 1;

}
