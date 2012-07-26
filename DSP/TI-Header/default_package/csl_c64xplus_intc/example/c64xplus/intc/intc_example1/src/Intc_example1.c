/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  Intc_example.c
 *
 *   @path  $(CSLPATH)\example\c64xplus\intc\intc_example1\src
 *
 *   @desc  Example of INTC
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n The example shows how to use INTC CSL with EDMA module.
 *      This is an example of the CSL Interrupt Controller usage.
 *      A event object is opened and is simply hooked up to a CPU vector. 
 *      An event hnadler is associaed with it. This example, 
 *      1. Initalizes the intc CSL required with proper ISR
 *      2. Intializes and opens  EDMA 
 *      3. Associates EDMA event handler with the INTC routine 
 *         CSL_intcPlugEventHandler ()
 *      4. Enables the edma interrupt
 *      5. Waits for edma interrupt generate.
 *      6. Compares the transferred data
 *      7. Displays the messages based on step 6
 *
 *=============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Intc_example1.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  30-Jun-2004 Ruchika Kharwar File Created
 *  22-Jul-2005 ds     changed to support edma3 csl
 *  16-Dec-2005 ds     Updated documentation
 *  28-Mar-2006 ds     Added code to clear all the evnts
 * =============================================================================
 */

#include <stdio.h>
#include <csl_edma3.h>
#include <csl_intc.h>
#include <soc.h>

/* Pragma to edma tcc handler table */
#pragma DATA_SECTION(TccHandlerTable,".testMem");

/* Global variable to Edma Tcc handler table */
typedef void (* EdmaTccHandler)(void);
EdmaTccHandler TccHandlerTable[64];

/* Macro for tcc handler table */
#define InvokeHandle(num)       TccHandlerTable[num]()

/* Funtion forwards, for which registers individual event handlers in a table */
void EdmaEventHook(Uint16 , EdmaTccHandler);
void eventEdmaHandler(void *);

/* Function forwards */
void tcc1Fxn();
void intc_example (void);

/* Intc variable declarartion */
CSL_IntcContext             intcContext; 
CSL_IntcEventHandlerRecord  EventHandler[30];
CSL_IntcObj                 intcObjEdma;
CSL_IntcHandle              hIntcEdma; 
CSL_IntcGlobalEnableState   state;
CSL_IntcEventHandlerRecord  EventRecord;
CSL_IntcParam               vectId;

/* Global variable declarations */ 
Uint8             srcBuff[512];
Uint8             dstBuff[512];
volatile Uint32   intFlag = 0;  
CSL_Edma3Handle   hModule;  


/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine,which invokes the example
 * =============================================================================
 */    
void main()
{   
    printf ("Running Interrupt Example\n");
    
    intc_example ();

    return;
}

/*
 * =============================================================================
 *   @func  intc_example
 *  
 *   @arg   None
 *
 *   @desc
 *      This is an example of the CSL Interrupt Controller usage.
 *      A event object is opened and is simply hooked up to a CPU vector. 
 *      An event hnadler is associaed with it. 
 *          1. Initalizes the intc CSL required with proper ISR
 *          2. Intializes and opens  EDMA 
 *          3. Associates EDMA event handler with the INTC routine 
 *             CSL_intcPlugEventHandler ()
 *          4. Enables the edma interrupt
 *          5. Waits for edma interrupt generate.
 *          6. Compares the transferred data
 *          7. Closes the edma module and edma channel.
 *          8. Closes the Intc module
 *
 *   @return
 *      None
 *   
 *   @eg
 *      intc_example ();
 * =============================================================================
 */
void intc_example (void)
{
    CSL_Edma3HwSetup        hwSetup;
    CSL_Edma3Obj            edmaObj;
    CSL_Edma3ParamHandle    hParamBasic;
    CSL_Edma3ChannelObj     chObj;
    CSL_Edma3CmdIntr        regionIntr;
    CSL_Edma3CmdDrae        regionAccess;
    CSL_Edma3ChannelHandle  hChannel;
    CSL_Edma3ParamSetup     myParamSetup;
    CSL_Edma3Context        context;
    CSL_Edma3ChannelAttr    chAttr;
    CSL_Status              status;
    Uint32                  loopIndex;
    Uint32                  passStatus = 1;
    Uint32                  evtClr;
    CSL_Edma3HwDmaChannelSetup dmahwSetup[CSL_EDMA3_NUM_DMACH] = \
                                            CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
    /* Initialize Data Buffers */
    for (loopIndex = 0; loopIndex < 512;loopIndex++) {
        srcBuff[loopIndex] = loopIndex;
        dstBuff[loopIndex] = 0;
    }      
    
    /* Edma CSL initialization */
    CSL_edma3Init(&context);
    

    /* Intc module initialization */
    intcContext.eventhandlerRecord = EventHandler;
    intcContext.numEvtEntries      = 10;
    status = CSL_intcInit(&intcContext);
    if (status != CSL_SOK) {
        printf("Intc initialization failed\n");
        return;
    }
    
    /* Enable NMIs */
    status = CSL_intcGlobalNmiEnable();
    if (status != CSL_SOK) {
        printf("Intc global NMI enable failed\n");
        return;
    }
    
    /* Enable global interrupts */
    status = CSL_intcGlobalEnable(&state);
    if (status != CSL_SOK) {
        printf ("Intc global enable failed\n");
        return;
    }
    
    /* Opening intc module */
    vectId = CSL_INTC_VECTID_4;
    hIntcEdma = CSL_intcOpen (&intcObjEdma, CSL_INTC_EVENTID_EDMA3CC_INT1, \
                              &vectId , NULL);
    if (hIntcEdma == NULL) {
        printf("Intc open failed\n");
        return;
    }
     
    /* Opening a edma module */
    hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status); 
    

    /* Edma module setup */
    hwSetup.dmaChaSetup  = &dmahwSetup[0];
    hwSetup.qdmaChaSetup = NULL;
    CSL_edma3HwSetup(hModule,&hwSetup);
        
    /* Setup the DRAE Masks
     * DRAE Enable(Bits 0-15) for the Shadow Region 1. 
     */
    regionAccess.region = CSL_EDMA3_REGION_1 ;
    regionAccess.drae =   0xFFFF ;   
    regionAccess.draeh =  0x0000 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                                 &regionAccess); 
    
    /* Edma channel open */
    chAttr.regionNum = CSL_EDMA3_REGION_1;
    chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
    hChannel = CSL_edma3ChannelOpen(&chObj,CSL_EDMA3,&chAttr,&status);  
    
        
    /* Parameter Set Setup */
    hParamBasic = CSL_edma3GetParamHandle(hChannel,0,&status);
    myParamSetup.option = CSL_EDMA3_OPT_MAKE(CSL_EDMA3_ITCCH_DIS, \
                                             CSL_EDMA3_TCCH_DIS, \
                                             CSL_EDMA3_ITCINT_DIS, \
                                             CSL_EDMA3_TCINT_EN,\
                                             1,CSL_EDMA3_TCC_NORMAL,\
                                             CSL_EDMA3_FIFOWIDTH_NONE, \
                                             CSL_EDMA3_STATIC_DIS, \
                                             CSL_EDMA3_SYNC_A, \
                                             CSL_EDMA3_ADDRMODE_INCR, \
                                             CSL_EDMA3_ADDRMODE_INCR);  
    myParamSetup.srcAddr = (Uint32)srcBuff;         
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(256,1);       
    myParamSetup.dstAddr = (Uint32)dstBuff;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(0,0);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE(CSL_EDMA3_LINK_NULL,1);     
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);     
    myParamSetup.cCnt = 1;          
    
    CSL_edma3ParamSetup(hParamBasic,&myParamSetup);
    
    /* Association of an EDMA event handler with the INTC routine */
    EventRecord.handler = &eventEdmaHandler;
    EventRecord.arg = (void*)(hModule);
    status = CSL_intcPlugEventHandler(hIntcEdma,&EventRecord);
    if (status != CSL_SOK) {
        printf("Intc plug event handler failed\n");
        return;
    }
    
    /* Enabling event edma  */
    status = CSL_intcHwControl(hIntcEdma,CSL_INTC_CMD_EVTENABLE,NULL);
    if (status != CSL_SOK) {
        printf("Intc CSL_INTC_CMD_EVTENABLE command failed\n");
        return;
    }
    
    /* Hook up the EDMA Event with an completion code function handler */
    EdmaEventHook(1, tcc1Fxn);  

    /* Enable Interrupts */
    regionIntr.region = CSL_EDMA3_REGION_1 ;
    regionIntr.intr = 0x2 ;
    regionIntr.intrh = 0x0 ;
    CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);
       

    /* Enable Channel :- though not required for a manual trigger */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_ENABLE, \
                                       NULL);    
    
    /* Manually trigger the channel */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
       
    /* Wait for generation of interrut */
    while (!intFlag);   
   
    /* Verify destination buffer to be equal to the source buffer */
    for (loopIndex = 0; loopIndex < 256; loopIndex++)
        if (srcBuff[loopIndex] != dstBuff[loopIndex])
            passStatus = 0;  
    
    if (passStatus != 0) {
        printf ("<<Example Passed>>: Interrupt example passed\n");
    }   
    else {
        printf ("<<Example Failed>>: Interrupt example failed\n");
        return;
    }
    
    /* Clear the all events */
    for (loopIndex = 0; loopIndex < 4; loopIndex++) {
        evtClr = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTFLAG[loopIndex];
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[loopIndex] = evtClr;
    }
    
    /* Close handles */
    CSL_edma3ChannelClose(hChannel);
    CSL_edma3Close(hModule);    
    CSL_intcClose (hIntcEdma);

    return; 
}

/*
 * =============================================================================
 *   @func   tcc1Fxn
 *   @desc
 *     This is the Interrupt service routine  
 *
 *   @arg    None
 *
 *   @eg
 *      tcc1Fxn ();
 *
 *
 * =============================================================================
*/
void tcc1Fxn(void)
{

    intFlag = 1;
}

/*
 * =============================================================================
 *   @func  EdmaEventHook
 *  
 *   @arg
 *      tcc        - Tcc number
 *      fxn        - Pointer to function which points to edma isr
 *
 *   @desc
 *      This is the interrupt handler routine for edma interrupt
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void EdmaEventHook (
    Uint16              tcc, 
    EdmaTccHandler      fxn
)
{
    TccHandlerTable[tcc] = (fxn);
}

/*
 * =============================================================================
 *   @func   eventEdmaHandler
 *
 *   @desc
 *     This is the event handler for edma 
 *
 *   @arg    handle
 *           Pointer to edma handle
 *
 *
 *   @eg
 *      eventEdmaHandler ();
 * =============================================================================
 */
void eventEdmaHandler (
    void        *handle
)
{
    CSL_BitMask32       mask;
    CSL_BitMask32       maskVal;
    CSL_Edma3CmdIntr    regionIntr;
    Uint32              tcc;
    Uint32              intr;
    Uint32              intrh;
    Int                 region;
    CSL_Edma3Handle     hModule = (CSL_Edma3Handle)handle;

    regionIntr.region = CSL_EDMA3_REGION_GLOBAL;
    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    
    intr  = regionIntr.intr;
    intrh = regionIntr.intrh;
    mask  = 1;
    tcc   = 0;
    while (intr) {
        maskVal = mask << tcc;
        if (regionIntr.intr & maskVal) {
            InvokeHandle(tcc);
            intr &= ~maskVal;
        }       
        tcc++;
    }       
    mask = 1;
    tcc = 0;
    while (intrh) {
        maskVal = mask << tcc;
        if (intrh & maskVal) {
            InvokeHandle((tcc+32));
            intrh &= ~maskVal;
        }       
        tcc++;
    }
    
    CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR,&regionIntr);       
    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);         
    
    if ((regionIntr.intr !=0)||(regionIntr.intrh !=0)) {
        region = CSL_EDMA3_REGION_GLOBAL;
        CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_EVAL,&region);        
    }

}

