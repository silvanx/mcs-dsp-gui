/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *
 *   @file  Edma_interrupt_example.c
 *
 *   @path  $(CSLPATH)\example\edma\edma_interrupt\src
 *
 *   @desc  Example of EDMA
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This is an example of the CSL EDMA usage along with interrupts 
 *      in the context of a shadow region and illustrates a sample EDMA 
 *      interrupt handler implementation. This example, 
 *        1. Initializes the CSL EDMA module
 *        2. Intializes and Sets up the Intc Module for EDMA module
 *        3. Opens and Sets up Edma module to default values 
 *        4. Opens EDMA channel 0 in the region 1
 *        5. Sets up the EDMA PARAM using CSL_edma3ParamSetup() API
 *        6. Enable the Edma interupt and Channel
 *        7. Manually triggers the channel 0
 *        8. Waits for EDMA transfer to complete
 *        9. Does the data comparision to ensure the transffered data is proper  
 *           or not and 
 *        10. Displays the messages based on step 9
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Edma_interrupt_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  08-Jul-2005 Ruchika Kharwar   File Created
 *  16-Dec-2005 ds                Updated documentation 
 *  28-Mar-2006 ds                Added code to disable the region 1 access at 
 *                                the end of example
 * ============================================================================
 */

#include <stdio.h>
#include <csl_edma3.h>
#include <csl_intc.h>
#include <soc.h>
#include <edmaCommon.h>


/* Intc declaration */
CSL_IntcContext                 intcContext; 
CSL_IntcEventHandlerRecord      EventHandler[30];
CSL_IntcObj                     intcObjEdma;
CSL_IntcHandle                  hIntcEdma; 
CSL_IntcGlobalEnableState       state;
CSL_IntcEventHandlerRecord      EventRecord;
CSL_IntcParam                   vectId; 
    
/* Globals */
Uint8               srcBuff[512];
Uint8               dstBuff[512];
volatile Uint32     intFlag = 0; 
Uint32              passStatus = 1;

/* Edma handle */
CSL_Edma3Handle     hModule;   
 
/* Forward declaration */
void tcc1Fxn(void);
void edma_interrupt_example (void); 

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
    /* Invoking a example */
    edma_interrupt_example ();
    
    return;
}

/*
 * =============================================================================
 *   @func  edma_interrupt_example
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the example routine which perform edma interrupt.
 *      It implements following steps
 *          1. Intializes and Opens the Edma and Intc module.
 *          2. Sets up the interrupt for the edma Regoin1.
 *          3. Sets up the edma module using the API csl_edma3Hwsetup () 
 *          4. Enables the edma region1 using CSL_EDMA3_CMD_DMAREGION_ENABLE. 
 *          5. Opens the channel 0 and get the param handle. 
 *          6. Sets up the edma param entry 
 *          7. Enables the edma interrupt using CSL_EDMA3_CMD_INTR_ENABLE. 
 *          8. Enables the channel using CSL_EDMA3_CMD_CHANNEL_ENABLE 
 *          9. Manually trigger the channel using CSL_EDMA3_CMD_CHANNEL_SET. 
 *          10. Waits for transfer to complete.
 *          11. Compares the data in the destination buffer is proper or not.
 *          12. Closes the edma module and channel.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void edma_interrupt_example (void)
{
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
    Uint32                      loopIndex;    

    /* Initialize data buffers */
    for (loopIndex = 0; loopIndex < 512; loopIndex++) {
        srcBuff[loopIndex] = loopIndex;
        dstBuff[loopIndex] = 0;
    }      
    
    /* Module initialization */
    status = CSL_edma3Init(&context);
    if (status != CSL_SOK) {
        printf ("Edma module initialization failed\n");   
        return;
    }
    
    /* Intc module initialization */
    intcContext.eventhandlerRecord = EventHandler;
    intcContext.numEvtEntries = 10;
    CSL_intcInit(&intcContext);
    
    /* Enable NMIs */
    CSL_intcGlobalNmiEnable();
    
    /* Enable global interrupts */
    CSL_intcGlobalEnable(&state);
    
    /* Opening a intc handle for edma event */
    vectId = CSL_INTC_VECTID_4;
    hIntcEdma = CSL_intcOpen (&intcObjEdma, CSL_INTC_EVENTID_EDMA3CC_INT1, \
                              &vectId , NULL);
    
    /* Edma module open */
    hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
    if ( (hModule == NULL) || (status != CSL_SOK)) {
        printf ("Edma module open failed\n");    
        return;
    }
        
    /* Edma module setup */
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
    
    /* Setup the DRAE masks
     * DRAE enable(Bits 0-15) for the shadow region 1.
     */
    regionAccess.region = CSL_EDMA3_REGION_1 ;
    regionAccess.drae =   0xFFFF ;   
    regionAccess.draeh =  0x0000 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                                &regionAccess); 
    if (status != CSL_SOK) {
        printf("Edma region enable command failed\n");
        return;    
    }
        
    /* Channel open */
    chAttr.regionNum = CSL_EDMA3_REGION_1;
    chAttr.chaNum = CSL_EDMA3_CHA_DSP_EVT;
    hChannel = CSL_edma3ChannelOpen(&chObj, CSL_EDMA3, &chAttr, &status);   
    if ( (hChannel == NULL) || (status != CSL_SOK)) {
        printf ("Edma channel open failed\n");    
        return;
    }
        
    /* Get the parameter handle */
    hParamBasic = CSL_edma3GetParamHandle(hChannel,0,&status);
    if (hParamBasic == NULL) {
        printf("Edma get param handle failed\n");
        return;
    }
    
    /* Edma parameter entry Setup */
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
    myParamSetup.aCntbCnt = CSL_EDMA3_CNT_MAKE(512,1);       
    myParamSetup.dstAddr = (Uint32)dstBuff;        
    myParamSetup.srcDstBidx = CSL_EDMA3_BIDX_MAKE(0,0);     
    myParamSetup.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (CSL_EDMA3_LINK_NULL, 
                                                           1); 
    myParamSetup.srcDstCidx = CSL_EDMA3_CIDX_MAKE(0,0);     
    myParamSetup.cCnt = 1;          
    status = CSL_edma3ParamSetup(hParamBasic,&myParamSetup);
    if (status != CSL_SOK) {
        printf ("Edma param setup failed\n");
        return;
    }
    
    /* Association of an EDMA event handler with the INTC routine */
    EventRecord.handler = &eventEdmaHandler;
    EventRecord.arg = (void*)(hModule);
    CSL_intcPlugEventHandler(hIntcEdma,&EventRecord);

    /* Enabling event edma  */
    CSL_intcHwControl(hIntcEdma,CSL_INTC_CMD_EVTENABLE,NULL);
    
    /* Hook up the EDMA event with an completion code function handler */
    EdmaEventHook(1, tcc1Fxn);  

    /* Enable interrupts */
    regionIntr.region = CSL_EDMA3_REGION_1 ;
    regionIntr.intr = 0x2 ;
    regionIntr.intrh = 0x0 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_ENABLE,&regionIntr);    
    if (status != CSL_SOK) {
        printf ("Edma interrupt enable command failed\n");
        return;
    }
     
    /* Manually trigger the channel */
    status = CSL_edma3HwChannelControl(hChannel,CSL_EDMA3_CMD_CHANNEL_SET,NULL);
    if (status != CSL_SOK) {
        printf ("Edma channel set command failed\n");
        return;
    }
       
    /* Wait for completion */
    while (!intFlag);   
    
    /* Disable the region 1 access */
    regionAccess.region = CSL_EDMA3_REGION_1 ;
    regionAccess.drae =   0xFFFF ;   
    regionAccess.draeh =  0x0000 ;
    status = CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_DISABLE, \
                                &regionAccess);

    /* Verify destination buffer to be equal to the source buffer */
    if(Verify_Transfer(512, 1, 1, 0, 0, 0, 0, srcBuff, dstBuff,TRUE) == FALSE)
        passStatus = 0;  
    
    if (passStatus == 1)    
        printf ("<<EXAMPLE PASSED>>: Edma Interrupt Example Passed\n");
    
    printf ("=============================================================\n");
    
    /* Channel close */    
    status = CSL_edma3ChannelClose(hChannel);
    if (status != CSL_SOK) {
        printf ("Edma channle close failed\n");
        return;
    }
    
    /* Edma module close */    
    status = CSL_edma3Close(hModule);    
    if (status != CSL_SOK) {
        printf ("Edma module close failed\n");
        return;
    }
    
    return;  
}

/*
 * =============================================================================
 *   @func  tcc1Fxn
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is the interrupt service routine for edma interrupt
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void tcc1Fxn(void) 
{

    intFlag = 1;
}

