/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 * @file  Vcp2_soft_decisions_example.c
 *
 * @path $(CSLPATH)\example\vcp2\vcp2_soft_decisions\src
 *
 * @desc  Example of usage of CSL of VCP2 for computing soft decisions
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 * @n <b> Description </b>
 *    This is an example for the VCP2 CSL usage for computing soft decision
 *    against the given branch metric values.
 *
 * @n The branch metrics are transferred to the VCP and soft decisions are
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
      4. Open project Vcp2_soft_decisions_example.pjt
      5. Build the project and load the .out file of the project.
           
   @endverbatim
 *       
 *   
 * ============================================================================
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  08-Oct-2005   SD     File Created.
 *  19-Dec-2005   SD     Added clearing of EDMA channel error registers 
 *  06-Feb-2006   SD     changes for the spec changes
 *  24-Feb-2006   DS     Added clearing of EDMA channel error registers at the
 *                       end of example
 * =============================================================================
 */
#include "csl_vcp2.h"
#include "csl_vcp2Aux.h"
#include "csl_edma3.h"
#include "stdio.h"
#include "string.h"
#include "cslr_dev.h"
#include "vcp2_example.h"

#define BITS_IN_A_BYTE 8

/* Constraint length */
#define CONSTRAINT_LEN 9

/* Frame length */
#define FRAME_LENGTH    186

/* EDMA frame size */
#define DMA_BURST_SIZE  128

/* VCP2 input configuration transfer size */
#define VCPIC_DMA_SIZE  24

/* VCP2 out register transfer size */
#define VCPOUT_DMA_SIZE  8

/* VCP2 yamamoto threshold */
#define YAMAMOTO_THRESHOLD 80

/* VCP2 initial state metric value */
#define INITIAL_STATE       63

/* Forward declarations */
Uint16 vcp2_configEdma(Uint32 inputBM, Uint32 outputHD);

/* EDMA global declarations */
CSL_Edma3Context             context;
CSL_Edma3ChannelObj          ChObj,ChObj1;
CSL_Edma3Obj                 edmaObj;
CSL_Edma3ChannelHandle       hChannel,hChannel1;
CSL_Edma3ParamHandle         hParam[4];
CSL_Edma3ParamSetup          myParamSetup;
CSL_Edma3ChannelAttr        chParam, chParam1;
CSL_Edma3ChannelErr         chErrClear;

/* Globals */                         
VCP2_ConfigIc                vcpConfig; 
Uint32                      ouputParams[2];

/*
 * =============================================================================
 *   @func   main
 *   @desc
 *       Various parameters of the input data (Branch metrics) provided along 
 *      with this example are as follows.
 *      Frame length...................................186                                
 *      rate...........................................1/2
 *      constraint length..............................9
 *      Decision mode..................................Soft 
 *      Traceback Mode.................................Mixed
 *      Index of the initial max state metric(IMAXI)...63 
 *      output parameters read flag....................TRUE
 *      Yamamoto enable................................TRUE
 *      Yamamoto threshold.............................80
 *      Traceback state enable.........................False 
 *      Traceback state index..........................N/A  
 *      DSP endian.....................................Little 
 *      Endian Register................................bm_endian
 *      Output order...................................1       
 *
 *   @expected result
 *      Appropriate message will be logged depending on 
 *      the result
 *
 *   @eg
 *      main();  
 * =============================================================================
 */
void main()
{
    volatile Uint16         frameLen, constLen;
    Uint32                  numSymProc;
    Uint32                  inputBM;
    Uint32                  outputHD;
    Uint32                  outputHD_bytes;
    Uint32                  outputHD_words;
    VCP2_Params             vcpParams;
    VCP2_BaseParams         vcpBaseParams;
    VCP2_Errors             errors;
	Uint32 					index;

    VCP2_Poly        poly = {0x6c, 0xe4, 0,0}; /* polynomials used */

    /* Enable the VCP2 in power saver */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
                                                                    UNLOCK);

    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_VCPCTL, 
                                                                    ENABLE);

    while (CSL_DEV_PERSTAT0_VCPSTAT_ENABLE != 
            CSL_FEXT (((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                                    DEV_PERSTAT0_VCPSTAT));

    /* VCP configuration */
    vcpBaseParams.rate      = VCP2_RATE_1_2;
    vcpBaseParams.constLen  = CONSTRAINT_LEN;
    vcpBaseParams.frameLen  = FRAME_LENGTH;
    vcpBaseParams.yamTh     = YAMAMOTO_THRESHOLD;
    vcpBaseParams.stateNum  = INITIAL_STATE;
    vcpBaseParams.tbConvrgMode = FALSE;
    vcpBaseParams.decision  = VCP2_DECISION_SOFT;
    vcpBaseParams.readFlag  = TRUE;
    vcpBaseParams.tailBitEnable = FALSE;
    vcpBaseParams.traceBackIndex = 0;
    vcpBaseParams.outOrder  = 1;

    /* VCP configuration */
    VCP2_genParams (&vcpBaseParams, &vcpParams);

    /* Number of EDMA frames (transfers) for branch metrics */
    inputBM = vcpParams.numBmFrames;

    /* Output hard decisions in terms of bytes rounded to upper byte */
    outputHD_bytes = vcpBaseParams.frameLen + vcpBaseParams.constLen - 1;

    /* Output hard decisions in terms of words rounded to upper words */
    outputHD_words = VCP2_normalCeil (outputHD_bytes, sizeof (Uint32));

    /* Total number of bytes required to be transfered */
    outputHD = outputHD_words * sizeof (Uint32);
    
    /* Configure EDMA */
    if (!(vcp2_configEdma (inputBM, outputHD)))
    {
        printf("\nError in configuring EDMA\n");
        return;
    }
    else
        printf("\nConfiguring EDMA......... Success\n");

    /* update the polynomials */        
    VCP2_addPoly (&poly, &vcpParams);
    
    frameLen = vcpParams.frameLen;
    constLen = vcpParams.constLen;
    VCP2_genIc (&vcpParams, &vcpConfig);

    /* clear the error registers */
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
    CSL_edma3HwChannelControl(hChannel1, CSL_EDMA3_CMD_CHANNEL_ENABLE , NULL);
    /* Enable Channel */ 
    CSL_edma3HwChannelControl(hChannel, CSL_EDMA3_CMD_CHANNEL_ENABLE , NULL);

    /* Start VCP2 */ 
    VCP2_reset ();
    VCP2_emuDisable ();   
    VCP2_start ();
    printf("VCP2 is started...\n");
    
    /* Wait till processing is over */
    while (VCP2_statRun());
    printf("VCP2 processing of data over\n");

    printf("\nRESULTS\n");
    printf("~~~~~~~\n");
    
    printf("FMINS = %d\n", ((ouputParams[0] & 0x0FFF0000)>>16));
    printf("FMAXS = %d\n", (ouputParams[0] & 0x00000FFF));
    printf("FMAXI = %d\n", (ouputParams[1] & 0x0000000F));
    
    /* Get the number of symbols processed */
    numSymProc = VCP2_statSymProc();
    printf("Number of symbols processed = %d \n", numSymProc);

    /* Verify the soft decisions output */
	for (index = 0; index < ((vcpParams.frameLen)/4); index++) {
		if (soft_decision [index] != soft_decisionRef [index]) {
			break;
		}
	}

	if (index == ((vcpParams.frameLen)/4)) {
        printf ("\nSoft decisions are computed properly\n");
    }
    else {
        printf ("\nSoft decisions are not computed properly %d\n", index);
	    VCP2_getErrors(&errors);
        if(errors.tbnaErr == FALSE &&
           errors.ftlErr == FALSE &&
           errors.fctlErr == FALSE &&
           errors.maxminErr == FALSE &&
           errors.symxErr == FALSE &&
           errors.symrErr == FALSE) {
           printf("No errors found set\n");
        }
    }
    
    /* clear the error registers */
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
    
    /* Close EDMA channels */
    CSL_edma3ChannelClose (hChannel);
    CSL_edma3ChannelClose (hChannel1);
}

/*
 * =============================================================================
 *   @func   vcp2_configEdma
 *   @desc
 *      Configures EDMA channels 28 and 29. 
 *      For channel 29 there are 2 param entries(0 &1) which are linked. 
 *          Link 0 transfers the VCP2 input configuration register values.
 *          Link 1 transfer Branch metrics.
 *      For channel 28 there 2 param entry (2 & 3).
 *          Link 2 transfers the soft decisions.
 *          Link 3 transfers the VCPOUT values          
 *
 *   @expected result
 *      Appropriate message will be logged depending on 
 *      the result
 *
 *   @eg
 *      vcp2_configEdma();  
 * =============================================================================
 */
Uint16 vcp2_configEdma(Uint32 inputBM, Uint32 outputHD)
{
    volatile Uint16             count;
    CSL_Status                  chStatus, chStatus1;

    CSL_edma3Init(&context);
    
    CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&chStatus);

    /* Channel Configuration for VCP2XEVT event */
    /* Channel Open */
    chParam.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chParam.chaNum = CSL_EDMA3_CHA_VCP2XEVT;
    hChannel = CSL_edma3ChannelOpen(&ChObj, CSL_EDMA3, &chParam, &chStatus);
    if ((chStatus != CSL_SOK) || (hChannel == NULL)) {
        printf("Error in EDMA channel open function\n");
        return 0;
    }

    /* Channel Setup */
    if (CSL_SOK != CSL_edma3HwChannelSetupParam(hChannel, 0 /* PaRAM entry */)){
        printf("Error in EDMA channel setup for channel #29\n");
        return 0;
    }

    if (CSL_SOK != CSL_edma3HwChannelSetupQue(hChannel, CSL_EDMA3_QUE_0)) {
        printf("Error in EDMA channel setup for channel #29\n");
        return 0;
    }

    /* Setup link to transmit Input configuration */
    hParam[0] = CSL_edma3GetParamHandle (hChannel, 0, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE,FALSE,FALSE,FALSE,0,
                                            CSL_EDMA3_TCC_NORMAL,
                                            CSL_EDMA3_FIFOWIDTH_NONE,
                                            FALSE,CSL_EDMA3_SYNC_A,
                                            CSL_EDMA3_ADDRMODE_INCR,
                                            CSL_EDMA3_ADDRMODE_INCR);           
    myParamSetup.srcAddr = (Uint32)&vcpConfig;
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(VCPIC_DMA_SIZE, 1);       
    myParamSetup.dstAddr = (Uint32)hVcp2Vbus;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(0, 0);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(0x20, 0); 
                            /* offset to the next param entry */    
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0, 0);     
    myParamSetup.cCnt = 1;
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[0], &myParamSetup)) {
        printf("Error in EDMA paRam setup for entry #0\n");
        return 0;
    }

    /* Setup link to transmit branch metrics */
    hParam[1] = CSL_edma3GetParamHandle(hChannel,1,&chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(FALSE, FALSE, FALSE, FALSE, 0,
                                            CSL_EDMA3_TCC_NORMAL,
                                            CSL_EDMA3_FIFOWIDTH_64BIT,
                                            FALSE,CSL_EDMA3_SYNC_A,
                                            CSL_EDMA3_ADDRMODE_CONST,
                                            CSL_EDMA3_ADDRMODE_INCR);           
    myParamSetup.srcAddr = (Uint32)branch_metric;
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(DMA_BURST_SIZE, 0);     
    myParamSetup.dstAddr = (Uint32)&(hVcp2Vbus->VCPWBM);
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(
                                                CSL_EDMA3_LINK_NULL, 0);
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(DMA_BURST_SIZE, inputBM);
    myParamSetup.cCnt = 1;
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[1], &myParamSetup)) {
        printf("Error in EDMA paRam setup for entry #1\n");
        return 0;
    }

    /* Channel Configuration for VCP2REVT event */
    /* Channel Open */
    chParam1.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chParam1.chaNum = CSL_EDMA3_CHA_VCP2REVT;
    hChannel1 = CSL_edma3ChannelOpen (&ChObj1, CSL_EDMA3, &chParam1, 
                                                            &chStatus1);
    if ((chStatus1 != CSL_SOK) | (hChannel1 == NULL)) {
        printf("Error in EDMA channel open function\n");
        return 0;
    }

    /* Channel Setup */
    if (CSL_SOK != CSL_edma3HwChannelSetupParam(hChannel1, 2 )) {
        printf("Error in EDMA channel setup for channel #29\n");
        return 0;
    }

    if (CSL_SOK != CSL_edma3HwChannelSetupQue(hChannel1, CSL_EDMA3_QUE_0)) {
        printf("Error in EDMA channel setup for channel #29\n");
        return 0;
    }

    hParam[2] = CSL_edma3GetParamHandle (hChannel1, 2, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
                                             CSL_EDMA3_TCC_NORMAL,
                                             CSL_EDMA3_FIFOWIDTH_64BIT,
                                             FALSE,CSL_EDMA3_SYNC_A,
                                             CSL_EDMA3_ADDRMODE_INCR,
                                             CSL_EDMA3_ADDRMODE_CONST);           
    myParamSetup.srcAddr = (Uint32)&(hVcp2Vbus->VCPRDECS);
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (outputHD, 1);       
    myParamSetup.dstAddr = (Uint32)soft_decision;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE (0, outputHD);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (0x60, 0);  
                                        /* offset to the next param entry */    
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE (0, 0);     
    myParamSetup.cCnt = 1;
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[2], &myParamSetup)) {
        printf("Error in EDMA paRam setup for entry #2\n");
        return 0;
    }

    hParam[3] = CSL_edma3GetParamHandle (hChannel1, 3, &chStatus);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE (FALSE, FALSE, FALSE, FALSE, 0,
                                             CSL_EDMA3_TCC_NORMAL,
                                             CSL_EDMA3_FIFOWIDTH_NONE,
                                             FALSE,CSL_EDMA3_SYNC_A,
                                             CSL_EDMA3_ADDRMODE_INCR,
                                             CSL_EDMA3_ADDRMODE_INCR);
    myParamSetup.srcAddr = (Uint32)&(hVcp2Vbus->VCPOUT0);
    myParamSetup.dstAddr = (Uint32)&ouputParams[0];
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE (VCPOUT_DMA_SIZE, 1);
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (
                                            CSL_EDMA3_LINK_NULL, 0);
    if (CSL_SOK != CSL_edma3ParamSetup (hParam[3], &myParamSetup)) {
        printf("Error in EDMA paRam setup for entry #3\n");
        return 0;
    }

    return 1;

}

