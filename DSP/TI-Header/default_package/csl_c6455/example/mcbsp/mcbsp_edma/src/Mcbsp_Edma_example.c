/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *
 *   @file  Mcbsp_Edma_example.c
 *
 *   @path  $(CSLPATH)\example\mcbsp\mcbsp_edma\src
 *
 *   @desc  Example of MCBSP
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n In this example, the MCBSP0 is configured in digital loopback mode,
 *      with 32 bit data transfer, using sample rate generator to synchronize 
 *      the frames.Edma mode of transmission is selected.
 *      This example,
 *          1. Initializes and opens mcbsp module. 
 *          2. Sets up the hardware to default values and multi channel 
 *             32 bit data transfer i.e., CSL_mcbspHwSetup() is called for 
 *             module configuration.
            3. Sets up interrupts corresponding to EDMA and MCBSP.
 *          4. Sets up EDMA for synchronizing ate MCBSP.
 *          5. Enables MCBSP to Transmit/Receive Data.
 *          7. Waits for the interrupt and once the transfer is done closes 
 *             the EDMA.  
 *          8. Does the data comparison to ensure the validity of the data.
 *          9. Displays the messages based on step 8.
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Mcbsp_Edma_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
 

/* =============================================================================
 *  Revision History
 *  ===============
 *  9-Aug-2006 RR File Created.
 *
 * =============================================================================
 */

#include <edmaCommon.h>
#include <cslr_dev.h>

/* Define data count */
#define DATATX_COUNT                64

/* Global for mcbsp */
Uint8               srcBuff[DATATX_COUNT];
Uint8               dstBuff[DATATX_COUNT];
volatile Uint32     intFlag = 0;
volatile Uint32     rxintFlag = 0;  

/* Handle for the MCBSP instance used in test */
CSL_McbspHandle   hMcbsp;

/* Macro that gives 2 CLK delay cycles */
#define WAIT_FOR_1_CLK  do {                                   \
                            volatile int delayCnt = 1;      \
                            while(delayCnt > 0) --delayCnt; \
                           }while (0)             

/* Global data definition */
CSL_McbspGlobalSetup mcbspGbl = {
    CSL_MCBSP_IOMODE_TXDIS_RXDIS ,
    CSL_MCBSP_DLBMODE_ON,
    CSL_MCBSP_CLKSTP_DISABLE
};

/** Receive Data Setup defaults */
CSL_McbspDataSetup mcbspRxData = {
    CSL_MCBSP_PHASE_SINGLE,
    CSL_MCBSP_WORDLEN_32,
     1,            //frame length
    (CSL_McbspWordLen)0,
     0,
    CSL_MCBSP_FRMSYNC_IGNORE, //frame sinc ignore
    CSL_MCBSP_COMPAND_OFF_MSB_FIRST,
    CSL_MCBSP_DATADELAY_0_BIT,
    CSL_MCBSP_RJUSTDXENA_RJUST_RZF , 
    CSL_MCBSP_INTMODE_ON_READY,   
    CSL_MCBSP_32BIT_REVERS_DISABLE
};
/** Transmit Data Setup defaults */
CSL_McbspDataSetup mcbspTxData = {
    CSL_MCBSP_PHASE_SINGLE,
    CSL_MCBSP_WORDLEN_32,
     1,
    (CSL_McbspWordLen)0,
     0,
    CSL_MCBSP_FRMSYNC_IGNORE,
    CSL_MCBSP_COMPAND_OFF_MSB_FIRST,
    CSL_MCBSP_DATADELAY_0_BIT,
    CSL_MCBSP_RJUSTDXENA_DXENA_OFF , 
    CSL_MCBSP_INTMODE_ON_READY,   
    CSL_MCBSP_32BIT_REVERS_DISABLE
};

/** Clock Setup defaults */
CSL_McbspClkSetup mcbspClock = {
    CSL_MCBSP_FSCLKMODE_INTERNAL,    /* XMT Frame-sync */
    CSL_MCBSP_FSCLKMODE_INTERNAL,    /* RCV Frame-sync */
    CSL_MCBSP_TXRXCLKMODE_INTERNAL,  /* XMT clock */
    CSL_MCBSP_TXRXCLKMODE_INTERNAL,  /* RCV clock */
    CSL_MCBSP_FSPOL_ACTIVE_HIGH,     /* XMT Frame-sync Active High */
    CSL_MCBSP_FSPOL_ACTIVE_HIGH,     /* RCV Frame-sync Active High */
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE, /* XMT clock Rising Edge */
    CSL_MCBSP_CLKPOL_RX_FALLING_EDGE,/* RCV clock Falling Edge */
    1,                               /* Frame-sync pulse width = 1 bit */
    0x40,                            /* Frame-sync pulse period  */
    0x1,                             /*clk divide by 2 */
    CSL_MCBSP_SRGCLK_CLKCPU,
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE ,/* CLKS pin signal Rising Edge */
    CSL_MCBSP_TXFSMODE_DXRCOPY,
    CSL_MCBSP_CLKGSYNCMODE_OFF  /* GSYNC = 0 means no clock synchronisation */
};

CSL_McbspMulChSetup mcbspMul = {
    CSL_MCBSP_PARTMODE_2PARTITION, /* RX */
    CSL_MCBSP_PARTMODE_2PARTITION, /* TX */
    (Uint16)0,        /*  rxMulChSel */
    (Uint16)0,        /*  txMulChSel */
    CSL_MCBSP_PABLK_0,/* rxPartABlk */
    CSL_MCBSP_PBBLK_1,/* rxPartBBlk */
    CSL_MCBSP_PABLK_0,/* txPartABlk */
    CSL_MCBSP_PBBLK_1 /* txPartABlk */
};

CSL_McbspHwSetup myHwSetup = {
    &mcbspGbl,
    &mcbspRxData,
    &mcbspTxData,
    &mcbspClock,
    &mcbspMul,
    CSL_MCBSP_EMU_FREERUN,
    NULL
};

/* Global Edma Tcc handler table */
CSL_IntcEventHandlerRecord      EventHandler[30];
CSL_IntcContext                 intcContext; 
CSL_IntcGlobalEnableState       state;
CSL_Status                      intStat,status;
CSL_IntcEventHandlerRecord      EventRecord;
CSL_IntcEventHandlerRecord      EventRecord1; 
CSL_IntcEventHandlerRecord      record[2];
CSL_IntcObj                     intcObjEdma,intcObjEdma1;
CSL_IntcHandle                  hIntcEdma,hIntcEdma1; 
CSL_IntcParam                   vectId,vectId1;

CSL_Edma3Handle          hModule;
CSL_Edma3ChannelHandle   hChannel;
CSL_Edma3ChannelHandle   hChannel1;
CSL_Edma3ChannelErr      chErrClear;
    
/* function prototype */
void setupInterrupts(void);
void txmyIsr();
void rxmyIsr();
void mcbsp_edma_example(void);
void mcbsp_edma_setup(void);

/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine,which invokes the test scripts
 * =============================================================================
 */
void main (
    void    
)
{
    Bool  mcbsp0En;
    
    /* Enable Mcbsp0 */
    /* Unlock the PERCFG0 register */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);
               
    /* Enable the powersaver for the MCBSP 0 */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_MCBSP0CTL, 
               ENABLE);
    
    do {
        mcbsp0En = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_MCBSP0STAT);
    } while (mcbsp0En != TRUE);

    printf("Powersaver for MCBSP 0 is enabled\n");

    /* Invoke the example */
    mcbsp_edma_example ();
    
    printf("===============================================================\n");
    
    return;
}

 /*
 * ============================================================================
 * @func  mcbsp_edma_example
 *
 * @desc
 *     This function performs following steps:
 *      -#  Opens one MCBSP port
 *      -#  Resets MCBSP XMT, RCV and Enable SRGR, Frame-sync
 *      -#  Sets up MCBSP with the initialized hwSetup function
 *          and waits for 1 CLK cycles
 *      -#  After all the data is transmitted out of MCBSP, it compares 
 *          the two buffers and prints the result to stdout
 *      -#  In the end it closes the MCBSP instance that was opened
 *
 * ============================================================================
 */
void mcbsp_edma_example (void)
{
    CSL_Status        status = CSL_SOK;
    CSL_McbspContext  pContext;
    CSL_McbspObj      mcbspObj;
    Uint16            i;
    Uint16            success = 1;
    CSL_BitMask16     ctrlMask;
    
    /* Data Arrays */   
    for (i = 0;i < DATATX_COUNT; i++) {
      srcBuff[i] = i;
      dstBuff[i] = 0;
   }

    /* Initialize the MCBSP CSL module */
    status = CSL_mcbspInit(&pContext);
    
    /* Open the CSL module */
    hMcbsp = CSL_mcbspOpen (&mcbspObj, CSL_MCBSP_0, NULL, &status);
       
    /* Setup hardware parameters */
    status= CSL_mcbspHwSetup (hMcbsp , &myHwSetup);

    /* Disable MCBSP transmit and receive */
    ctrlMask =   CSL_MCBSP_CTRL_SRG_ENABLE
               | CSL_MCBSP_CTRL_FSYNC_ENABLE
               | CSL_MCBSP_CTRL_TX_DISABLE
               | CSL_MCBSP_CTRL_RX_DISABLE;
    status = CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);
        
	WAIT_FOR_1_CLK; 
 
    /* setup Edma for Mcbsp */   
    mcbsp_edma_setup ();

	/* All done now, close the port. */
    CSL_mcbspClose(hMcbsp);
    
    /* Check data to make sure transfer was successful */
    for (i = 0; i < DATATX_COUNT; i++) {
        if (srcBuff[i] != dstBuff[i]) {
            success = 0;
            break;
        }
    }
    
    for (i = 0; i < DATATX_COUNT; i++) {
        if (success == 1) 
            printf("RxData = %d\t txData=%d\n", dstBuff[i],srcBuff[i]);
        else {
            printf("RxData = %d\t txData=%d\n", dstBuff[i],srcBuff[i]);
            return;
        }
    }
    
    printf("\n%s",success?"TRANSMISSION SUCCESS\n":"TRANSMISSION: EXAMPLE FAILED\n");         

    return;
}

/**
 *  ============================================================================
 *  @n@b    mcbsp_edma_setup
 *
 * @desc
 *     This function performs follwing steps:
 *      -#  Set up interrupts corresponding to EDMA and MCBSP
 *      -#  Set up EDMA for synchronising with MCBSP
 *      -#  Enable MCBSP to Trax Data.
 *      -#  Wait for the interrupt and once the transfer is done close the EDMA 
 * ============================================================================
 */

void mcbsp_edma_setup (
    void
)
{   
    
    CSL_Edma3ParamHandle     hParamBasic;
    CSL_Edma3ParamHandle     hParamBasic1;
    CSL_Edma3ParamSetup      myParamSetup;
    CSL_Edma3ParamSetup      myParamSetup1;
    CSL_Edma3ChannelObj      ChObj,ChObj1;
    CSL_Edma3ChannelAttr     chParam;
    CSL_Edma3Context         edmaContext;
    CSL_Edma3Obj             edmaObj;    
    CSL_Edma3QueryInfo       info;
    CSL_Edma3CmdIntr         regionIntr; 
    CSL_Edma3CmdDrae         regionAccess;
    Uint32                   i, j; 
    CSL_BitMask16            ctrlMask;
  
    for (i = 0, j = 1; i < DATATX_COUNT;i++,j++) {
        srcBuff[i] = j;
        dstBuff[i] = 0;
    }   
 
    /* Intc Module Initialization */
    intcContext.eventhandlerRecord = EventHandler;
    intcContext.numEvtEntries = 10;

    CSL_intcInit(&intcContext);
    
    /* Enable NMIs */
    CSL_intcGlobalNmiEnable();

    /* Enable Global Interrupts */
    intStat = CSL_intcGlobalEnable(&state);
    
    /* Opening a handle for the Event edma */
    vectId = CSL_INTC_VECTID_4;
    hIntcEdma = CSL_intcOpen (&intcObjEdma, CSL_INTC_EVENTID_EDMA3CC_INT0, 
                             &vectId , NULL);

   /* Edma Module Initialization */
    CSL_edma3Init(&edmaContext); 
    
    /* Edma Module Level Open */   
    hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);

    /* Query Module Info */
    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INFO, &info); 

    /********************************Setup for Tx******************************/

    /* Setup the DRAE Masks */
    regionAccess.region = CSL_EDMA3_REGION_0;
    regionAccess.drae   = 0xFFFF;      
    regionAccess.draeh  = 0;         
    
    CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE,&regionAccess);
       
    /* Open transmit channel */
    chParam.regionNum = CSL_EDMA3_REGION_0;
    chParam.chaNum = CSL_EDMA3_CHA_XEVT0;
    hChannel = CSL_edma3ChannelOpen(&ChObj,
                        CSL_EDMA3,
                        &chParam,                            
                        &status); 

    /* Channel setup */    
    hParamBasic = CSL_edma3GetParamHandle(hChannel,CSL_EDMA3_CHA_XEVT0, &status);
    
    /* param setup */
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                             CSL_EDMA3_TCCH_DIS, \
                                             CSL_EDMA3_ITCINT_DIS, \
                                             CSL_EDMA3_TCINT_EN,\
                                             CSL_EDMA3_CHA_XEVT0, \
                                             CSL_EDMA3_TCC_NORMAL, \
                                             CSL_EDMA3_FIFOWIDTH_32BIT, \
                                             CSL_EDMA3_STATIC_DIS, \
                                             CSL_EDMA3_SYNC_A,\
                                             CSL_EDMA3_ADDRMODE_INCR,\
                                             CSL_EDMA3_ADDRMODE_INCR \
                                            );           
    myParamSetup.srcAddr = (Uint32)srcBuff;
    myParamSetup.dstAddr = (Uint32)CSL_MCBSP_0_TX_EDMA_REGS;
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(4,16);       
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(4,0);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(CSL_EDMA3_LINK_NULL,1);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);     
    myParamSetup.cCnt = 1;          
      
    CSL_edma3HwChannelSetupParam (hChannel, CSL_EDMA3_CHA_XEVT0);
    CSL_edma3HwChannelSetupQue(hChannel, CSL_EDMA3_QUE_1); 

    
    
    CSL_edma3ParamSetup(hParamBasic,&myParamSetup); 
    CSL_edma3HwChannelControl(hChannel, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);    
    
    /********************************Setup for Rx******************************/
    
    /* Open Receive channel */
    chParam.regionNum = CSL_EDMA3_REGION_0;
    chParam.chaNum = CSL_EDMA3_CHA_REVT0;
    hChannel1 = CSL_edma3ChannelOpen(&ChObj1,
                        CSL_EDMA3,
                        &chParam,                            
                        &status);
     
    /* Channel Setup */
    hParamBasic1 = CSL_edma3GetParamHandle(hChannel1,CSL_EDMA3_CHA_REVT0,&status);
    
    /* Param Setup */
    myParamSetup1.option = CSL_EDMA3_OPT_MAKE(FALSE,FALSE,FALSE,TRUE,\
                                              CSL_EDMA3_CHA_REVT0, \
                                              CSL_EDMA3_TCC_NORMAL,\
                                              CSL_EDMA3_FIFOWIDTH_32BIT, \
                                              CSL_EDMA3_STATIC_DIS, \
                                              CSL_EDMA3_SYNC_A, \
                                              CSL_EDMA3_ADDRMODE_INCR, \
                                              CSL_EDMA3_ADDRMODE_INCR \
                                             );           
    myParamSetup1.srcAddr = (Uint32)CSL_MCBSP_0_RX_EDMA_REGS;
    myParamSetup1.dstAddr = (Uint32)dstBuff;
    myParamSetup1.aCntbCnt = CSL_EDMA3_CNT_MAKE(4,16);       
    myParamSetup1.srcDstBidx = CSL_EDMA3_BIDX_MAKE(0,4);     
    myParamSetup1.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(
                                                         CSL_EDMA3_LINK_NULL,1);     
    myParamSetup1.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);     
    myParamSetup1.cCnt = 1;          
        
    CSL_edma3HwChannelSetupParam (hChannel1, CSL_EDMA3_CHA_REVT0);
    CSL_edma3HwChannelSetupQue(hChannel1, CSL_EDMA3_QUE_1);
    CSL_edma3ParamSetup(hParamBasic1, &myParamSetup1); 
       
    EventRecord.handler = &eventEdmaHandler;
    EventRecord.arg = (void*)(hModule);
    CSL_intcPlugEventHandler(hIntcEdma,&EventRecord);

    /* Enabling event edma  */
    CSL_intcHwControl(hIntcEdma,CSL_INTC_CMD_EVTENABLE,NULL);

     /* Hook up the EDMA Event with an ISR */
    EdmaEventHook(CSL_EDMA3_CHA_XEVT0, txmyIsr); 
    EdmaEventHook(CSL_EDMA3_CHA_REVT0, rxmyIsr);  
    
   /* Enable the interrupts */
    regionIntr.region = CSL_EDMA3_REGION_0;
    regionIntr.intr   = 0x3000;      
    regionIntr.intrh  = 0;
    CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);    

    /* Enable the receive channel */
    CSL_edma3HwChannelControl(hChannel1, CSL_EDMA3_CMD_CHANNEL_ENABLE, NULL);    
        
    /* Enable MCBSP transmit and receive */
    ctrlMask = CSL_MCBSP_CTRL_TX_ENABLE | CSL_MCBSP_CTRL_RX_ENABLE;
    CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);
    
    WAIT_FOR_1_CLK;
        
    /* wait for Transmit complete Interrupt */
    while (!intFlag);
    
    /* wait for Transmit complete Interrupt */
    while (!rxintFlag);
    
      /* Disable cahnnels and clear the EDMA event registers */
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
     
    /* clear the error registers */
    chErrClear.missed = TRUE;
    chErrClear.secEvt = TRUE;
    CSL_edma3HwChannelControl (hChannel, CSL_EDMA3_CMD_CHANNEL_CLEARERR, &chErrClear);
    CSL_edma3HwChannelControl (hChannel1, CSL_EDMA3_CMD_CHANNEL_CLEARERR, &chErrClear);
    
    CSL_edma3ChannelClose(hChannel);
    CSL_edma3ChannelClose(hChannel1);
    CSL_edma3Close(hModule);
    CSL_intcClose (hIntcEdma);
}

/*
 * ============================================================================
 *   @func   txmyIsr
 *
 *   @desc
 *     This function is the interrupt service routine for transmit data
 *
 *  @arg  
 *      None
 *
 *  @return
 *      None
 * ============================================================================
*/

void txmyIsr()
{

    intFlag = 1;
}

/*
 * ============================================================================
 *   @func   rxmyIsr
 *
 *   @desc
 *     This function is the interrupt service routine for receive data
 *
 *  @arg  
 *      None
 *
 *  @return
 *      None
 * ============================================================================
*/

void rxmyIsr()
{

    rxintFlag = 1;
}

