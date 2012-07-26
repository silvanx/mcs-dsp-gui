/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */
 
/** ===========================================================================
 *
 *   @file  Mcbsp_sinChannel_example.c
 *
 *   @path  $(CSLPATH)\example\mcbsp\mcbsp_single_channel\src
 *
 *   @desc  Example of MCBSP
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n In this example, the MCBSP0 is configured in digital loopback mode,
 *      with 16 bit data transfer, using sample rate generator
 *      to synchronise the frames. Normal mode(Single channel) of transmission 
 *      is selected.
 *      This example,
 *          1. Intializes and opens mcbsp module 
 *          2. Sets up the hardware to default values and single channel 
 *             16 bit data transfe i.e., CSL_mcbspHwSetup() is called for 
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
 *      4. Open project Mcbsp_sinChannel_example.pjt
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
 *  16-Dec-2005   ds  Updated documentation
 *  07-Feb-2006   ds  Added "intEvent" configuration to rcvDataCfg and 
 *                    xmtDataCfg  and Changed to use DEV functional layer
 * 21-Feb-2006    ds  Alocated Memory for readHwsetup structure variable which
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
#define WAIT_FOR_2_CLK  do {                                   \
                            volatile int delayCnt = 2;      \
                            while(delayCnt > 0) --delayCnt; \
                           }while (0)             

/* Global constants- Number of words to transfer */
#define NumOfWords   100

/* Function declarations */
void singleChannelTransmission(void);
CSL_Status hwSetupVerify (CSL_McbspHwSetup *, 
                          CSL_McbspHwSetup *
                          );


/* Handle for the MCBSP instance */
CSL_McbspHandle   hMcbsp;

/* Create data buffers for transfer */
Uint16      xmt[NumOfWords];
Uint16      rcv[NumOfWords];

/* Global data definition */
CSL_McbspGlobalSetup mcbspGbl = {
    CSL_MCBSP_IOMODE_TXDIS_RXDIS ,
    CSL_MCBSP_DLBMODE_ON,
    CSL_MCBSP_CLKSTP_DISABLE
};

/*  Receive data setup */
CSL_McbspDataSetup mcbspRxData = {
    CSL_MCBSP_PHASE_SINGLE,
    CSL_MCBSP_WORDLEN_16,
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

/*  Transmit data setup */
CSL_McbspDataSetup mcbspTxData = {
    CSL_MCBSP_PHASE_SINGLE,
    CSL_MCBSP_WORDLEN_16,
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

/*  Clock setup defaults */
CSL_McbspClkSetup mcbspClock = {
    CSL_MCBSP_FSCLKMODE_INTERNAL,    /* XMT Frame-sync */
    CSL_MCBSP_FSCLKMODE_INTERNAL,    /* RCV Frame-sync */
    CSL_MCBSP_TXRXCLKMODE_INTERNAL,  /* XMT clock */
    CSL_MCBSP_TXRXCLKMODE_INTERNAL,  /* RCV clock */
    CSL_MCBSP_FSPOL_ACTIVE_HIGH,     /* XMT Frame-sync active high */
    CSL_MCBSP_FSPOL_ACTIVE_HIGH,     /* RCV Frame-sync active high */
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE, /* XMT clock rising edge */
    CSL_MCBSP_CLKPOL_RX_FALLING_EDGE,/* RCV clock falling edge */
    1,                               /* Frame-sync pulse width = 1 bit */
    0x40,                            /* Frame-sync pulse period  */
    0x1,                             /*clk divide by 2 */
    CSL_MCBSP_SRGCLK_CLKCPU,
    CSL_MCBSP_CLKPOL_TX_RISING_EDGE ,/* CLKS pin signal rising edge */
    CSL_MCBSP_TXFSMODE_DXRCOPY,
    CSL_MCBSP_CLKGSYNCMODE_OFF   /* GSYNC = 0 means no clock synchronisation */
};

/*  Multichannel setup  */
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

/*  Mcbsp hwsetup  */
CSL_McbspHwSetup myHwSetup = {
    &mcbspGbl,
    &mcbspRxData,
    &mcbspTxData,
    &mcbspClock,
    &mcbspMul,
    CSL_MCBSP_EMU_FREERUN,
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

    
    /* Invoke example */
    singleChannelTransmission();    

    return;
}

/*
 * ============================================================================
 * @func  singleChannelTransmission()
 *
 * @desc
 *     This function performs following steps:
 *      -#  Opens one MCBSP port
 *      -#  Resets MCBSP SRGR, XMT, RCV and Frame-sync
 *      -#  Brings MCBSP XMT and RCV out of reset
 *      -#  For every element to be transmitted out of MCBSP, it first waits for
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
void singleChannelTransmission(void)
{
   
    CSL_Status           status = CSL_SOK;
    CSL_McbspContext     pContext;
    CSL_McbspObj         mcbspObj;
    Uint16               loopIndex;
    CSL_BitMask16        ctrlMask;
    CSL_BitMask16        response;
    CSL_McbspHwSetup     readHwSetup;
    Uint16               maxTimeout = 1000;
    Uint16               timeout    = 0;
    Uint16               errCount   = 0; 
    CSL_McbspGlobalSetup globalSetup;
    CSL_McbspDataSetup   rxDataSetup;
    CSL_McbspDataSetup   txDataSetup;
    CSL_McbspClkSetup    clkSetup;

    /* Clear local data structures */   
    memset (&readHwSetup, 0, sizeof(CSL_McbspHwSetup)); 
    memset (&mcbspObj, 0, sizeof(CSL_McbspObj)); 

    /* Allocated memory for variable */
    readHwSetup.global = &globalSetup;
    readHwSetup.rxdataset = &rxDataSetup;
    readHwSetup.txdataset = &txDataSetup;
    readHwSetup.clkset = &clkSetup;

    /* Data Arrays */   
    for (loopIndex = 0; loopIndex < NumOfWords; loopIndex++) {
      xmt[loopIndex] = loopIndex;
      rcv[loopIndex] = 0;
    }

    printf("\n***singleChannelTransmission***\n");

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
    
    /* Disable MCBSP transmit and receive */
    ctrlMask = CSL_MCBSP_CTRL_RX_DISABLE 
               | CSL_MCBSP_CTRL_TX_DISABLE
               | CSL_MCBSP_CTRL_FSYNC_DISABLE 
               | CSL_MCBSP_CTRL_SRG_DISABLE;
    CSL_mcbspHwControl (hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);
    
    /* Setup hardware parameters */
    status= CSL_mcbspHwSetup (hMcbsp , &myHwSetup);
    if (status != CSL_SOK){
        printf ("MCBSP: Hardware setup... Failed.\n");
        exit(1);
    }
    
    /* Get Hw setup Parameters */
    status = CSL_mcbspGetHwSetup (hMcbsp , &readHwSetup); 
    if (status != CSL_SOK){
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

    /* Start sample rate generator and wait for 2 clock cycles */
    ctrlMask = CSL_MCBSP_CTRL_SRG_ENABLE | CSL_MCBSP_CTRL_FSYNC_ENABLE;
    CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask); 
    
    WAIT_FOR_2_CLK;
    
    /* Enable MCBSP transmit and receive and wait for 2 clock cycles */
    ctrlMask = CSL_MCBSP_CTRL_TX_ENABLE | CSL_MCBSP_CTRL_RX_ENABLE;
    CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL, &ctrlMask);
     
    WAIT_FOR_2_CLK;      

    for(loopIndex = 0; loopIndex < NumOfWords; loopIndex++) {
        timeout = 0;

        /* Wait for XRDY signal before writing data to DXR */
        response = 0;
        while ((timeout++ < maxTimeout) && !(response & CSL_MCBSP_XRDY)) {
            CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_DEV_STATUS, &response);
        }
        
        if(timeout >= maxTimeout) {
            printf("MCBSP: Example Failed\n");
            printf("\tReason: Failed to make the transmitter ready\n");
            exit(1);
        }

        /* Write 16 bit data value to DXR */
        CSL_mcbspWrite (hMcbsp, CSL_MCBSP_WORDLEN_16, &xmt[loopIndex]);

        timeout = 0;
        
        /* Read 16 bit value from DRR and check the data */
        response = 0;
        while ((timeout++ < maxTimeout) && !(response & CSL_MCBSP_RRDY)) {
            CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_DEV_STATUS, &response);
        }
        
        /* Read 16 bit value from DRR */
        CSL_mcbspRead (hMcbsp, CSL_MCBSP_WORDLEN_16, &rcv[loopIndex]);
        if(xmt[loopIndex] != rcv[loopIndex])
            errCount++;
    }

    /* Check the data to make sure transfer was successful and print data */
    for(loopIndex = 0; loopIndex <= NumOfWords - 1; loopIndex++) {
        if (xmt[loopIndex] != rcv[loopIndex]) {
            printf("xmt[%d] != rcv[%d]\n", loopIndex, loopIndex);        
        }
        else {
            printf("xmt[%d] == rcv[%d]\n", loopIndex, loopIndex);
        }
    }

    /* Check for error count to display example result */
    if (errCount > 0) {
        printf("MCBSP: Single Channel Transmission Example... Failed.\n");
    
    }
    else {
        printf("MCBSP: Single Channel Transmission Example... Success.\n");            
    }   
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
    
    /* Check the mcbsp emulation mode setup parameters */
    if(!((hwSetup->emumode == hwSetupRead->emumode ) &&
        (hwSetup->extendSetup == hwSetupRead->extendSetup))) {
        
        status = CSL_ESYS_FAIL;
    }

    return status;
}
