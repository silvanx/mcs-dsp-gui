/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *
 *   @file  Mcbsp_mulChannel_example.c
 *
 *   @path  $(CSLPATH)\example\mcbsp\mcbsp_multi_channel\src
 *
 *   @desc  Example of MCBSP
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n In this example, the MCBSP0 is configured in digital loopback mode,
 *      with 32 bit data transfer, using sample rate generator to synchronise 
 *      the frames.Multi channel mode of transmission is selected.
 *      This example,
 *          1. Intializes and opens mcbsp module 
 *          2. Sets up the hardware to default values and multi channel 
 *             32 bit data transfe i.e., CSL_mcbspHwSetup() is called for 
 *             module configuration.
 *          3. Brings MCBSP XMT and RCV out of reset
 *          4. For every element to be trasmitted out of MCBSP, it first waits 
 *             for XRDY signal to be ON and then writes that element
 *          6. Since MCBSP is configured in loopback, this value also comes at 
 *             the receiver, which comes in RCV data register
 *          7. For every such element to be received, it waits for RRDY signal 
 *             to be ON and then copies that element from RCV data register to 
 *             a buffer
 *          8. Does the data comparision to ensure the written data is proper or 
 *             not and 
 *          9. Displays the messages based on step 8
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Mcbsp_mulChannel_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
  
/* ============================================================================
 *  Revision History
 *  ===============
 *  25-April-2005 Ramitha Mathew. created
 *
 *  14-Nov-2005   ds  Changed the CLKGDV value during testing
 *  16-Dec-2005   ds  Updated documentation
 *  06-Feb-2006   ds  Added "intEvent" configuration to rcvDataCfg and 
 *                    xmtDataCfg
 *  21-Feb-2006   ds  Alocated Memory for readHwsetup structure variable which
 *                    is used in CSL_mcbspGetHwSetup() API call.
 *                    Cleared local data structures 
 *                    Added Code to compare the Hwsetup and read Hwsetup 
 *                    parameters
 * ============================================================================
 */

#include <csl_mcbsp.h>
#include <cslr_dev.h>
#include <soc.h>
#include <stdio.h>

/* Macro that gives 2 CLK delay cycles */
#define WAIT_FOR_2_CLK  do {                            \
                            volatile int delayCnt = 2;   \
                            while(delayCnt > 0) --delayCnt; \
                           }while (0)                         
/* Global constants */
/* Number of words to be transmitted*/
#define NumOfWords       25                


/* Handle for the MCBSP instance */
CSL_McbspHandle   hMcbsp;

/* Create data buffers for transfer */
Uint32      xmt[NumOfWords];
Uint32      rcv[NumOfWords]; 


/* Function forwards */
void mcbsp_multichannel_example (void);
CSL_Status hwSetupVerify (CSL_McbspHwSetup *, 
                          CSL_McbspHwSetup *
                          );
                          
/* Global data definition */
CSL_McbspGlobalSetup gblCfg = {
    CSL_MCBSP_IOMODE_TXDIS_RXDIS,
    CSL_MCBSP_DLBMODE_ON,
    CSL_MCBSP_CLKSTP_DISABLE
};

/*  Receive data setup */                                       
CSL_McbspDataSetup rcvDataCfg = {                            
    CSL_MCBSP_PHASE_SINGLE,                                   
    CSL_MCBSP_WORDLEN_32,                                     
    32,                             /* FRMLEN1 */
    CSL_MCBSP_WORDLEN_8,            /* Default value for phase2*/
    2,                              /* FRMLEN2 */                                                    
    CSL_MCBSP_FRMSYNC_DETECT,                                 
    CSL_MCBSP_COMPAND_OFF_MSB_FIRST,                          
    CSL_MCBSP_DATADELAY_0_BIT, 
    CSL_MCBSP_RJUSTDXENA_RJUST_RZF,
    CSL_MCBSP_INTMODE_ON_READY,          
    CSL_MCBSP_32BIT_REVERS_DISABLE 
};                          
                                  
/*  Transmit data setup */                            
CSL_McbspDataSetup xmtDataCfg = {                            
    CSL_MCBSP_PHASE_SINGLE,                                   
    CSL_MCBSP_WORDLEN_32,                                     
    32,                  /* FRMLEN1 */
    CSL_MCBSP_WORDLEN_8, /* Default value */                                         
    2,                   /* FRMLEN2 */                                                        
    CSL_MCBSP_FRMSYNC_DETECT,                                 
    CSL_MCBSP_COMPAND_OFF_MSB_FIRST,                          
    CSL_MCBSP_DATADELAY_0_BIT,                                
    CSL_MCBSP_RJUSTDXENA_DXENA_OFF,
    CSL_MCBSP_INTMODE_ON_READY,                     
    CSL_MCBSP_32BIT_REVERS_DISABLE
};                       
  
/*  Mcbsp clock setup */                                   
CSL_McbspClkSetup clkCfg = {                                          
    CSL_MCBSP_FSCLKMODE_INTERNAL,    /* XMT Frame-sync */             
    CSL_MCBSP_FSCLKMODE_INTERNAL,    /* RCV Frame-sync */             
    CSL_MCBSP_TXRXCLKMODE_INTERNAL,  /* XMT clock */                      
    CSL_MCBSP_TXRXCLKMODE_INTERNAL,  /* RCV clock */                      
    CSL_MCBSP_FSPOL_ACTIVE_HIGH,     /* XMT Frame-sync Active High */               
    CSL_MCBSP_FSPOL_ACTIVE_HIGH,     /* RCV Frame-sync Active High */               
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE, /* XMT clock Rising Edge */                
    CSL_MCBSP_CLKPOL_RX_FALLING_EDGE,/* RCV clock Falling Edge */
    2,                              /* Frame-sync pulse width=2 CLKG periods */
    1024,                    /* Frame-sync pulse period = 1024 CLKG periods */
    1,                      /* CLKGDIV = 1 means divide by input clock by 2 */
    CSL_MCBSP_SRGCLK_CLKCPU,         /* SCLKME = 0, CLKSM = 1 */                          
    CSL_MCBSP_CLKPOL_SRG_RISING_EDGE, /* CLKS pin signal Rising Edge */           
    CSL_MCBSP_TXFSMODE_DXRCOPY,          /* If FSGM = 1, XMT Frame-sync driven by
                                        sample rate generater, FSG signal */                                                           
    CSL_MCBSP_CLKGSYNCMODE_OFF   /* GSYNC = 0 means no clock synchronisation */             
};                                                                                                     

/*  Multichannel setup  */
CSL_McbspMulChSetup mulChCfg = {
    (CSL_McbspPartMode)CSL_MCBSP_PARTMODE_2PARTITION,      
    (CSL_McbspPartMode)CSL_MCBSP_PARTMODE_2PARTITION, 
    (Uint16)1,                     /* Receive multichannel selection enable */
    (Uint16)2,                     /* Transmit multichannel selection enable */
    (CSL_McbspPABlk)CSL_MCBSP_PABLK_0,                    
    (CSL_McbspPBBlk)CSL_MCBSP_PBBLK_1,                     
    (CSL_McbspPABlk)CSL_MCBSP_PABLK_0,                     
    (CSL_McbspPBBlk)CSL_MCBSP_PBBLK_1
           
};                        
                    
/*  Mcbsp hwsetup  */
CSL_McbspHwSetup myHwSetup = {
    &gblCfg,
    &rcvDataCfg,
    &xmtDataCfg,
    &clkCfg,
    &mulChCfg,
    CSL_MCBSP_EMU_STOP,
    NULL
};


/*
 * ============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.
 *
 * ============================================================================
*/
void main (void)
{   
    Bool  mcbsp0En;
    
    /* Unlock the control register */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);
               
    /* Enable the Powersavr for MCBSP 0 */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_MCBSP0CTL, 
               ENABLE);
    do {
        mcbsp0En = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_MCBSP0STAT);
    } while (mcbsp0En != TRUE);
   
    printf("Power saver clock for McBSP0 Enabled\n");
    
    /* Invoke the example */
    mcbsp_multichannel_example(); 

    return;
}


/*
 * ============================================================================
 * @func  mcbsp_multichannel_example
 *
 * @desc
 *     This function performs follwing steps:
 *      -#  Opens one MCBSP port
 *      -#  Resets MCBSP SRGR, XMT, RCV and Frame-sync
 *      -#  Sets up MCBSP with the initialised hwSetup function
 *          and waits for 2 CLK cycles
 *      -#  Brings MCBSP SRGR and Frame sync out of reset and waits for 2 CLK 
 *          cycles
 *      -#  Brings MCBSP XMT and RCV out of reset
 *      -#  For every element to be trasmitted out of MCBSP, it first waits for
 *          XRDY signal to be ON and then writes that element
 *      -#  Since MCBSP is configured in loopback, this value also comes at the
 *          receiver, which comes in RCV data register
 *      -#  For every such element to be received, it waits for RRDY signal to
 *          be ON and then copies that element from RCV data register to 
 *          a buffer
 *      -#  After all the data is transmitted out of MCBSP, it compares 
 *          the two buffers and prints the result to stdout
 *      -#  In the end it closes the MCBSP instance that was opened
 *
 * ============================================================================
 */
void mcbsp_multichannel_example (void)
{
    CSL_Status              status = CSL_SOK;
    CSL_McbspContext        pContext;
    CSL_McbspObj            mcbspObj;
    Uint16                  loopIndex;
    CSL_BitMask16           ctrlMask;
    CSL_BitMask16           response; 
    Uint32                  err = 0;
    CSL_McbspHwSetup        readHwSetup;   
    CSL_McbspChanControl    channel;
    CSL_McbspGlobalSetup    globalSetup;
    CSL_McbspDataSetup      rxDataSetup;
    CSL_McbspDataSetup      txDataSetup;
    CSL_McbspClkSetup       clkSetup;
    CSL_McbspMulChSetup     mulChSetup;
    
    /* Clear local data structures */
    memset(&mcbspObj, 0, sizeof(CSL_McbspObj));
    memset(&readHwSetup, 0, sizeof(CSL_McbspHwSetup));
    
    printf("MCBSP Multichannel Example\n");
    
    /* Allocated memory for variable */
    readHwSetup.global    = &globalSetup;
    readHwSetup.rxdataset = &rxDataSetup;
    readHwSetup.txdataset = &txDataSetup;
    readHwSetup.clkset    = &clkSetup;
    readHwSetup.mulCh     = &mulChSetup;

    /* Initilize data buffers. xmt will be 32 bit value      
     * with element number in lower 16 bits and 2 * element 
     * in upper 16 bits.  i.e.  0x00020001, 0x00040002, etc. */
    for(loopIndex = 0; loopIndex <= NumOfWords - 1; loopIndex++) {
        xmt[loopIndex] = (((Uint32) (loopIndex + 1) << 17) + (loopIndex + 1));
        rcv[loopIndex] = 0;
    }
    
    /* Initialize the MCBSP CSL module */
    status = CSL_mcbspInit(&pContext);
    if (status != CSL_SOK) {
        printf("Mcbsp initialization failed\n");
        return;
    }
    
    /* Open the CSL module */
    hMcbsp = CSL_mcbspOpen (&mcbspObj, CSL_MCBSP_0, NULL, &status);
    if ((hMcbsp == NULL) || (status != CSL_SOK)) {
        printf ("MCBSP: Opening instance... Failed.\n");
        printf ("\tReason: Error opening the instance. \
                [status = 0x%x, hMcbsp = 0x%x]\n", status, hMcbsp);
        exit(1);
    }

    /* Put SRG, Frame-sync, XMT and RCV in reset */
    ctrlMask =   CSL_MCBSP_CTRL_SRG_DISABLE
               | CSL_MCBSP_CTRL_FSYNC_DISABLE
               | CSL_MCBSP_CTRL_TX_DISABLE
               | CSL_MCBSP_CTRL_RX_DISABLE;
    status = CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);
    if (status != CSL_SOK) {
        printf("Mcbsp CSL_MCBSP_CMD_RESET_CONTROL command failed\n");
        return;
    }
    
    /* Program MCBSP control registers */
    status = CSL_mcbspHwSetup(hMcbsp, &myHwSetup);
    if (status != CSL_SOK) {
        printf ("MCBSP: Hardware setup... Failed.\n");
        exit(1);
    }
    
    /* Get the mcbsp control register values */
    status = CSL_mcbspGetHwSetup (hMcbsp , &readHwSetup); 
    if (status != CSL_SOK) {
        printf ("MCBSP: Get Hardware setup... Failed.\n");
        exit(1);
    }
    
    /* Compare the hardware setup parameter values passed in the
     * "hwSetup" structure by comparing them with the actual values read from
     * the Mcbsp registers 
     */
    status = hwSetupVerify (&myHwSetup, &readHwSetup);
    if (status != CSL_SOK){
        printf ("MCBSP: Hardware setup and Read Hardware setup parameter "); 
        printf ("comparision ... Failed.\n");
        exit(1);
    }
       
    /* Enabling the channels- 0 & 31 */
    channel.channelNo = 0;
    channel.operation = CSL_MCBSP_CHCTRL_RX_ENABLE;
    CSL_mcbspHwControl (hMcbsp, CSL_MCBSP_CMD_CHANNEL_CONTROL, &channel);
    
    channel.channelNo = 31;
    channel.operation = CSL_MCBSP_CHCTRL_RX_ENABLE;
    CSL_mcbspHwControl (hMcbsp, CSL_MCBSP_CMD_CHANNEL_CONTROL, &channel);

    channel.channelNo = 0;
    channel.operation = CSL_MCBSP_CHCTRL_TX_ENABLE;
    CSL_mcbspHwControl (hMcbsp, CSL_MCBSP_CMD_CHANNEL_CONTROL, &channel);

    channel.channelNo = 31;
    channel.operation = CSL_MCBSP_CHCTRL_TX_ENABLE;
    CSL_mcbspHwControl (hMcbsp, CSL_MCBSP_CMD_CHANNEL_CONTROL, &channel);
       
    /* Start sample rate generator and wait for 2 clock cycles */
    ctrlMask = CSL_MCBSP_CTRL_SRG_ENABLE | CSL_MCBSP_CTRL_FSYNC_ENABLE;
    CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask); 
    
    /* Give small delay to start sample rate generator */
    WAIT_FOR_2_CLK;
    
    /* Enable MCBSP transmit and receive */
    ctrlMask = CSL_MCBSP_CTRL_TX_ENABLE | CSL_MCBSP_CTRL_RX_ENABLE;
    CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);    
    
    /* Give small delay to enable transmit and receive */
    WAIT_FOR_2_CLK;
    
    printf("Waiting for transmission to Complete\n");
    
    /* Begin data transfer loop. We will loop through to transmit 
     * and receive the data.
     */                                   
    for (loopIndex = 0; loopIndex <= NumOfWords - 1; loopIndex++) {
        /* Wait for XRDY signal before writing data to DXR */
        response = 0;
        while (!(response & CSL_MCBSP_XRDY)) {
            CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_DEV_STATUS, &response);
        }  
        
        /* Write 32 bit data value to DXR */    
        CSL_mcbspWrite (hMcbsp, CSL_MCBSP_WORDLEN_32, &xmt[loopIndex]);
        
        /* Wait for RRDY signal to read data from DRR */
        response = 0;
        while (!(response & CSL_MCBSP_RRDY)) {
            CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_DEV_STATUS, &response);
        }
     
        /* Read 32 bit value from DRR */
        CSL_mcbspRead (hMcbsp, CSL_MCBSP_WORDLEN_32, &rcv[loopIndex]); 
    }    
    
    /* Check data to make sure transfer was successful */
    for(loopIndex = 0; loopIndex <= NumOfWords - 1; loopIndex++) {
        if (xmt[loopIndex] != rcv[loopIndex]) {
            printf("xmt[%d] != rcv[%d]\n", loopIndex, loopIndex);
            ++err;      
        }
        else {
            printf("xmt[%d] == rcv[%d]\n",loopIndex, loopIndex);
        }
    }
 
    printf("\n%s",err?"TRANSMISSION: EXAMPLE FAILED\n":"TRANSMISSION SUCCESS\n");
       
    /* We are done with MCBSP, so close it */ 
    CSL_mcbspClose(hMcbsp); 

    return;    
}

/*
 * ============================================================================
 *   @func   hwSetupVerify
 *
 *   @desc
 *     This function compare the hardware setup parameter values passed in the
 *     "hwSetup" structure by comparing them with the actual values read from
 *     the Mcbsp registers.
 *
 *   @arg    hwSetup
 *       Pointer to the buffer containing the hardware setup parameters that
 *       are needed to be compare
 *   @arg    hwSetupRead
 *       Pointer to the buffer containing the get hardware setup parameters that
 *       are needed to be compared with setup parameters
 *
 * ============================================================================
*/
CSL_Status hwSetupVerify (
      CSL_McbspHwSetup    *hwSetup,
      CSL_McbspHwSetup    *hwSetupRead
)
{ 
    CSL_Status    status = CSL_SOK;
    
    /* Check the mcbsp global setup parameters */
    if (hwSetupRead->global != NULL) {
        if(!((hwSetup->global->dlbMode == hwSetupRead->global->dlbMode) 
            &&(hwSetup->global->clkStopMode == \
                                             hwSetupRead->global->clkStopMode) 
            &&(hwSetup->global->ioEnableMode == \
                                        hwSetupRead->global->ioEnableMode))) {
            status = CSL_ESYS_FAIL;
        } 
    }  
    
    /* Check the mcbsp receive data setup parameters */
    if (hwSetupRead->rxdataset != NULL) {
        if (!((hwSetup->rxdataset->numPhases == \
                                           hwSetupRead->rxdataset->numPhases)
            &&(hwSetup->rxdataset->wordLength1 == \
                                        hwSetupRead->rxdataset->wordLength1) 
            &&(hwSetup->rxdataset->wordLength2 == \
                                        hwSetupRead->rxdataset->wordLength2)
            &&(hwSetup->rxdataset->frmLength1 == \
                                        hwSetupRead->rxdataset->frmLength1)
            &&(hwSetup->rxdataset->frmSyncIgn  == \
                                        hwSetupRead->rxdataset->frmSyncIgn)
            &&(hwSetup->rxdataset->compand == \
                                        hwSetupRead->rxdataset->compand)
            && (hwSetup->rxdataset->dataDelay == \
                                        hwSetupRead->rxdataset->dataDelay)
            &&(hwSetup->rxdataset->rjust_dxenable == \
                                        hwSetupRead->rxdataset->rjust_dxenable)
            &&(hwSetup->rxdataset->intEvent == \
                                        hwSetupRead->rxdataset->intEvent)
            &&(hwSetup->rxdataset->wordReverse == \
                                       hwSetupRead->rxdataset->wordReverse))) {
               
            status = CSL_ESYS_FAIL;
        }
    }
    
    /* Check the mcbsp transmit data setup parameters */
    if (hwSetupRead->txdataset != NULL) {
        if (!((hwSetup->txdataset->numPhases == \
                                        hwSetupRead->txdataset->numPhases) 
            &&(hwSetup->txdataset->wordLength1 == \
                                        hwSetupRead->txdataset->wordLength1)
            &&(hwSetup->txdataset->wordLength2 == \
                                        hwSetupRead->txdataset->wordLength2)
            &&(hwSetup->txdataset->frmLength1 == \
                                        hwSetupRead->txdataset->frmLength1)
            &&(hwSetup->txdataset->frmSyncIgn == \
                                        hwSetupRead->txdataset->frmSyncIgn)
            &&(hwSetup->txdataset->compand == \
                                        hwSetupRead->txdataset->compand)
            &&(hwSetup->txdataset->dataDelay == \
                                        hwSetupRead->txdataset->dataDelay)
            &&(hwSetup->txdataset->rjust_dxenable == \
                                        hwSetupRead->txdataset->rjust_dxenable)
            &&(hwSetup->txdataset->intEvent == \
                                        hwSetupRead->txdataset->intEvent)
            &&(hwSetup->txdataset->wordReverse == \
                                       hwSetupRead->txdataset->wordReverse))) {
           
            status = CSL_ESYS_FAIL;
        }
    }

    /* Check the mcbsp clock setup parameters */
    if (hwSetupRead->clkset != NULL) {
        if (!((hwSetup->clkset->frmSyncRxMode == \
                                        hwSetupRead->clkset->frmSyncRxMode)
            &&(hwSetup->clkset->frmSyncTxMode == \
                                        hwSetupRead->clkset->frmSyncTxMode)
            &&(hwSetup->clkset->frmSyncRxPolarity == \
                                        hwSetupRead->clkset->frmSyncRxPolarity)
            &&(hwSetup->clkset->frmSyncTxPolarity == \
                                        hwSetupRead->clkset->frmSyncTxPolarity)
            &&(hwSetup->clkset->clkRxMode == \
                                        hwSetupRead->clkset->clkRxMode)
            &&(hwSetup->clkset->clkTxMode == \
                                        hwSetupRead->clkset->clkTxMode)
            &&(hwSetup->clkset->clkRxPolarity == \
                                    hwSetupRead->clkset->clkRxPolarity)
            &&(hwSetup->clkset->clkTxPolarity == \
                                    hwSetupRead->clkset->clkTxPolarity)
            &&(hwSetup->clkset->srgFrmPulseWidth  == \
                                    hwSetupRead->clkset->srgFrmPulseWidth)
            &&(hwSetup->clkset->srgFrmPeriod == \
                                    hwSetupRead->clkset->srgFrmPeriod)
            &&(hwSetup->clkset->srgClkDivide == \
                                    hwSetupRead->clkset->srgClkDivide)
            &&(hwSetup->clkset->srgClkSync == \
                                    hwSetupRead->clkset->srgClkSync)
            &&(hwSetup->clkset->srgInputClkMode == \
                                    hwSetupRead->clkset->srgInputClkMode)
            &&(hwSetup->clkset->srgClkPolarity == \
                                    hwSetupRead->clkset->srgClkPolarity)
            &&(hwSetup->clkset->srgTxFrmSyncMode == \
                                    hwSetupRead->clkset->srgTxFrmSyncMode))) {
            
            status = CSL_ESYS_FAIL;
        }
    }
    
	/* Check the mcbsp multichannel setup parameters */
    if (hwSetupRead->mulCh != NULL) {
        if(!((hwSetup->mulCh->rxMulChSel == hwSetupRead->mulCh->rxMulChSel)
            &&(hwSetup->mulCh->txMulChSel  == hwSetupRead->mulCh->txMulChSel)
            &&(hwSetup->mulCh->rxPartition == hwSetupRead->mulCh->rxPartition)
            &&(hwSetup->mulCh->rxPartABlk  == hwSetupRead->mulCh->rxPartABlk)
            &&(hwSetup->mulCh->rxPartBBlk  == hwSetupRead->mulCh->rxPartBBlk)
            &&(hwSetup->mulCh->txPartition == hwSetupRead->mulCh->txPartition)
            &&(hwSetup->mulCh->txPartABlk  == hwSetupRead->mulCh->txPartABlk)
            &&(hwSetup->mulCh->txPartBBlk  == \
                                           hwSetupRead->mulCh->txPartBBlk))) { 
       
            status = !CSL_SOK;
        }
    }

    /* Check the mcbsp emulation mode setup parameters */
    if(!((hwSetup->emumode == hwSetupRead->emumode ) &&
        (hwSetup->extendSetup == hwSetupRead->extendSetup))) {
        
        status = CSL_ESYS_FAIL;
    }

    return status;
}

