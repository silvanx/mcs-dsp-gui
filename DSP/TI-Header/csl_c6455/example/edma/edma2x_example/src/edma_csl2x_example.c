/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** ===========================================================================
 *   @file  edma_csl2x_example.c
 *
 *   @path $(CSLPATH)\example\edma\src
 *
 *   @desc  This is an example program for EDMA of CSL 2x
 *
 * =============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example Performs EDMA transfers in different modes. 
 *        1. Sets up the INTC module for use by the EDMA
 *        2. Performs a simple memory to memory transfer using EDMA
 *        3. Performs a simple memory to memory transfer using QDMA
 *        4. Performs a memory to memory transfer that involves linking
 *        5. Performs a memory to memory transfer that involves chaining
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Edma_Csl2x_Example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* ============================================================================
 *  Revision History
 *  ================
 *  28-Jul-2005    Chandra    File created.
 *  11-Aug-2005    Chandra    Minor format changes.
 *  16-Dec-2005    DS         Updated documentation 
 * ============================================================================
 */

#include <csl_edma2.h>
#include <stdio.h>
#include <csl_intc.h>
#include <edma_int_dispatcher.h>

/* Macros for buffer sizes */
#define SIMPLE_TRANSFER_SIZE (16)
#define LINK_BUF_SIZE        (16)
#define CHAIN_BUF_SIZE       (16)

/* Macros to manipulate the TCC and TCCM fields */
#define TCC_SHIFT            (16)
#define TCCM_SHIFT           (9)
#define TCC_MASK             (0x0000000F)
#define TCCM_MASK            (0x00000030)

/* LINK and Reload default */
#define NO_RELOAD_AND_LINK   (0xFFFF)

/* OPT word value for different transfers */

/*
   Simple transfer

   Priority  - 2
   Esize     - 3 (1 byte)
   2DS       - 0 (1 dimensional source)
   SUM       - 1 (increment source)
   2DD       - 0 (1 dimensional destination)
   DUM       - 1 (increment destination)
   TCINT     - 1 (transfer complete interrupt ON)
   TCC, TCCM - ?, 0 (transfer completion code is ?)
                    A value for TCC is selected in the function.
   ATCINT    - 0 (alternate transfer completion interrupt OFF)
   ATTC      - 0 (alternate transfer completion code is 0)
   PDTS      - 0 (source peripheral device transfer is OFF)
   PDTD      - 0 (destination peripheral device transfer is OFF)
   LINK      - 0 (linking is OFF)
   FS        - 1 (frame synchronization ON)
*/
#define SIMPLE_TRANSFER_OPTIONS (0x51300001)

/*
   First of the link transfers
   
   Priority  - 2
   Esize     - 3 (1 byte)
   2DS       - 0 (1 dimensional source)
   SUM       - 1 (increment source)
   2DD       - 0 (1 dimensional destination)
   DUM       - 1 (increment destination)
   TCINT     - 0 (transfer complete interrupt ON)
   TCC, TCCM - ?, 0 (transfer completion code is ?)
   ATCINT    - 0 (alternate transfer completion interrupt OFF)
   ATTC      - 0 (alternate transfer completion code is 0)
   PDTS      - 0 (source peripheral device transfer is OFF)
   PDTD      - 0 (destination peripheral device transfer is OFF)
   LINK      - 1 (linking is ON)
   FS        - 1 (frame synchronization ON)
*/
#define LINK_OPTIONS_WITH_LINK (0x45300003)

/*
   Last transfer of the link transfers

   Priority  - 2
   Esize     - 3 (1 byte)
   2DS       - 0 (1 dimensional source)
   SUM       - 1 (increment source)
   2DD       - 0 (1 dimensional destination)
   DUM       - 1 (increment destination)
   TCINT     - 0 (transfer complete interrupt ON)
   TCC, TCCM - ?, 0 (transfer completion code is ?)
   ATCINT    - 0 (alternate transfer completion interrupt OFF)
   ATTC      - 0 (alternate transfer completion code is 0)
   PDTS      - 0 (source peripheral device transfer is OFF)
   PDTD      - 0 (destination peripheral device transfer is OFF)
   LINK      - 0 (linking is OFF)
   FS        - 1 (frame synchronization ON)
*/
#define LINK_OPTIONS_WITH_OUT_LINK (0x45300001)

/*
   Chained Transfer

   Priority  - 2
   Esize     - 3 (1 byte)
   2DS       - 0 (1 dimensional source)
   SUM       - 1 (increment source)
   2DD       - 0 (1 dimensional destination)
   DUM       - 1 (increment destination)
   TCINT     - 0 (transfer complete interrupt ON)
   TCC, TCCM - ?, 0 (transfer completion code is ?)
   ATCINT    - 0 (alternate transfer completion interrupt OFF)
   ATTC      - 0 (alternate transfer completion code is 0)
   PDTS      - 0 (source peripheral device transfer is OFF)
   PDTD      - 0 (destination peripheral device transfer is OFF)
   LINK      - 0 (linking is OFF)
   FS        - 1 (frame synchronization ON)
*/
#define CHAIN_OPTIONS (0x45300001)

/*
   QDMA transfer

   PRI     - 2
   ESIZE   - 0 : 4 byte transfers
   2DS     - 0 : 1-d source
   SUM     - 1 : Increment source address
   2DD     - 0 : 1-d destination
   DUM     - 1 : Increment destination address
   FS      - 1 : Transfer is frame synchronized
   CNT = No. of elements to be transferred = Buffer size / size of tx element
   See section 1.16.1 of 'spru234.pdf'
*/
#define QDMA_OPTIONS (0x41300001)

/* forward declarations */
void transfer_example (void);
static void isr (int tccNum);
static void isr2 (int tccNum);

void eventEdmaHandler (void *handle);
void configure_intc (void);
void link_example (void);
void chain_example (void);
void qdma_example (void);
void configure_intc (void);


/* Global */

/* Flags used in the ISRs */
volatile Uint32 isr_cnt = 0;
volatile Uint32 parent_isr_cnt = 0;

/* Data structures for INTC configuration */
CSL_IntcContext intcContext;
CSL_IntcEventHandlerRecord EventHandler[1];

/* Allocation of buffers to use in the transfers */
static Uint8 src[SIMPLE_TRANSFER_SIZE];
static Uint8 dst[SIMPLE_TRANSFER_SIZE];

static Uint8 link_src1[LINK_BUF_SIZE];
static Uint8 link_src2[LINK_BUF_SIZE];

static Uint8 link_dst1[LINK_BUF_SIZE];
static Uint8 link_dst2[LINK_BUF_SIZE];

static Uint8 chain_src1[CHAIN_BUF_SIZE];
static Uint8 chain_src2[CHAIN_BUF_SIZE];

static Uint8 chain_dst1[CHAIN_BUF_SIZE];
static Uint8 chain_dst2[CHAIN_BUF_SIZE];

/**
 * ============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine of this file that invokes the individual
 *     example routines
 * ============================================================================
*/
void main (void)
{
    /* First configure the interupts */
    configure_intc ();

    /* Simple transfer example */
    transfer_example ();

    /* Transfer example using the QDMA */
    qdma_example ();

    /* Transfer example using link feature */
    link_example ();

    /* Transfer example using chain feature */
    chain_example ();

    /* Clean up */
    EDMA_resetAll ();
    EDMA_intResetAll ();
}


/* ISR to handle TCC interrupt */
static void isr (
    Int tccNum
)
{
    isr_cnt++;
}

/* Another ISR to handle TCC interrupt */
static void isr2 (
    Int tccNum
)
{
    parent_isr_cnt++;
}

/**
 * ============================================================================
 *   @func   transfer_example
 *
 *   @desc
 *     This performs a simple EDMA memory to memory transfer.
 *
 *   @n <b> Procedure </b>
 *   @verbatim
       1. Enables a channel
       2. Configures it
       3. Allocates and configures an EDMA channel interrupt
       4. Sets up the interrupt and ISR
       4. Initiates the transfer
       5. Waits for completion of ISR
       6. Verifies the transfer
       7. Cleans up

     @endverbatim
 * ============================================================================
 */
void transfer_example (void)
{
    EDMA_Handle  handle;
    Uint32       chan_no;
    EDMA_Config  conf = { 0 };
    Uint32       index;
    Uint32       tcc;

    /* Setup the source and destination memory areas */
    for (index = 0; index < SIMPLE_TRANSFER_SIZE; index++) {
        src[index] = index;
        dst[index] = 0;
    }

    /* Reset all interrupts of all channels of EDMA */
    EDMA_intResetAll ();
    
    /* Consider the channel 4 of EDMA */
    chan_no = 4;               
    handle = EDMA_open (chan_no, EDMA_OPEN_RESET);

    /* Choose the same TCC as the channel */
    tcc = EDMA_intAlloc (chan_no);      
    if (tcc != chan_no) {
        printf ("Error in allocating TCC\n");
        return;
    }

    /* Setup the config structure */
    conf.opt =
        SIMPLE_TRANSFER_OPTIONS | ((tcc & TCC_MASK) << TCC_SHIFT) | ((tcc &
            TCCM_MASK) << TCCM_SHIFT);
    conf.cnt = SIMPLE_TRANSFER_SIZE;
    conf.idx = 0;               /* 1-d source, 1-d destination, address
                                   increment for both, so
                                   FRMIDX = ELEIDX = don't care */
    conf.rld = NO_RELOAD_AND_LINK;
    conf.dst = (Uint32) & dst[0];
    conf.src = (Uint32) & src[0];

    printf
        ("EDMA: Example ... Config. a memory to memory transfer of %d bytes\n",
        SIMPLE_TRANSFER_SIZE);
    EDMA_config (handle, &conf);

    /* Setup the ISR */
    edmaEventHook (chan_no, isr);

    /* Enable EDMA interrupt for the selected channel */
    EDMA_intEnable (chan_no);

    printf ("EDMA: Example ... Initiating the transfer\n");
    EDMA_setChannel (handle);   /* Set event register, this should result in
                                   interrupt */

    /* Wait for the ISR to run */
    while (1) {
        if (isr_cnt > 0) {
            isr_cnt = 0;
            break;
        }
    }
    printf ("EDMA: Example ... Data transfer is complete\n");

    /* Verify the transferred data */
    for (index = 0; index < SIMPLE_TRANSFER_SIZE; index++) {
        if (src[index] != dst[index]) {
            break;
        }
    }
    if (index == SIMPLE_TRANSFER_SIZE) {
        printf ("EDMA: Example ... Data transferred correctly\n");
    }
    else {
        printf ("EDMA: Example ... Data not transferred correctly\n");
        return;
    }

    /* Clean up */
    EDMA_intReset (tcc);
    EDMA_intFree (tcc);
    EDMA_close (handle);
    printf ("EDMA: Simple Example ... DONE\n");

}

/**
 * ============================================================================
 *   @func   link_example
 *
 *   @desc
 *     This performs a EDMA memory to memory transfer in two stages, by link.
 *
 *   @n <b> Procedure </b>
 *   @verbatim
       1. Setup the data destinations and sources for 2 transfers
       2. Enable a channel
       3. Allocate and configure an interrupt
       4. Configure the PaRAM of the channel
       5. Allocate and configure another PaRAM for link transfer
       6. Link the second PaRAM with the first
       7. Start transfer on the channel
       8. Verify the data transfer
       9. Start the second transfer on the same channel
      10. Verify the data transfer
      11. Clean up

     @endverbatim
 * ============================================================================
 */
void link_example (void)
{
    EDMA_Handle     handle;
    EDMA_Handle     link_handle;
    Uint32          chan_no;
    Uint32          tcc;
    EDMA_Config     conf = { 0 };
    Int             index;

    /* Setup the data area */
    for (index = 0; index < LINK_BUF_SIZE; index++) {
        link_src1[index] = index;
        link_dst1[index] = 0;
        link_src2[index] = LINK_BUF_SIZE - index;
        link_dst2[index] = 0;
    }

    /* Reset all interrupts of all channels of EDMA */
    EDMA_intResetAll ();

    /* Open a channel and allocate a PaRAM for linking */
    chan_no = 3;                /* Use channel 3 of EDMA */
    handle = EDMA_open (chan_no, EDMA_OPEN_RESET);

    /* Allocate and enable interrupt of same number as channel */
    tcc = EDMA_intAlloc (chan_no);
    if (tcc != chan_no) {
        printf ("Error in allocating TCC\n");
        return;
    }
    EDMA_intEnable (chan_no);

    printf
        ("EDMA: Link Example ... Config. a 2 stage mem. to mem. transfer\n");
    printf ("EDMA: Link Example ... Each transfer of %d bytes\n",
        LINK_BUF_SIZE);

    printf ("EDMA: Link Example ... Configuring stage 1\n");
    conf.opt =
        LINK_OPTIONS_WITH_LINK | ((tcc & TCC_MASK) << TCC_SHIFT) | ((tcc &
            TCCM_MASK) << TCCM_SHIFT);
    conf.cnt = (LINK_BUF_SIZE);
    conf.idx = 0;               /* 1-d source, 1-d destination, address
                                   increment for both, so
                                   FRMIDX = ELEIDX = don't care */

    conf.rld = NO_RELOAD_AND_LINK;  /* Linking is done latter in the example */
    conf.dst = (Uint32) & link_dst1[0];
    conf.src = (Uint32) & link_src1[0];
    EDMA_config (handle, &conf);

    printf
        ("EDMA: Link Example ... Alloc. a PaRAM for stage 2 configuration\n");
    link_handle = EDMA_allocTable (EDMA_ALLOC_ANY);

    printf ("EDMA: Link Example ... Configuring stage 2\n");
    conf.opt =
        LINK_OPTIONS_WITH_OUT_LINK | ((tcc & TCC_MASK) << TCC_SHIFT) | ((tcc &
            TCCM_MASK) << TCCM_SHIFT);   /* Same as stage 1 without linking */

    conf.cnt = (LINK_BUF_SIZE);
    conf.idx = 0;               /* 1-d source, 1-d destination, address
                                   increment for both, so
                                   FRMIDX = ELEIDX = don't care */
    conf.rld = NO_RELOAD_AND_LINK;
    conf.dst = (Uint32) & link_dst2[0];
    conf.src = (Uint32) & link_src2[0];
    EDMA_config (link_handle, &conf);

    printf ("EDMA: Link Example ... Linking the two transfers\n");
    EDMA_link (handle, link_handle);

    printf ("EDMA: Link Example ... Initiating the transfer 1\n");

    /* Setup the ISR for the transfer */
    edmaEventHook (chan_no, isr);
    EDMA_setChannel (handle);   /* Set event register, this should result in
                                   interrupt */

    /* Wait for the first transfer */
    while (1) {
        if (isr_cnt > 0) {
            isr_cnt = 0;
            break;
        }
    }
    printf
        ("EDMA: Link Example ... Data transfer of first stage is complete\n");

    /* Verify the first data transfer */
    for (index = 0; index < LINK_BUF_SIZE; index++) {
        if (link_dst1[index] != link_src1[index]) {
            break;
        }
    }
    if (index == LINK_BUF_SIZE) {
        printf
            ("EDMA: Link Example ... 1st stage data transferred correctly\n");
    }
    else {
        printf
         ("EDMA: Link Example ... 1st stage data not transferred correctly\n");
        return;
    }

    printf ("EDMA: Link Example ... Initiating the transfer 2\n");
    EDMA_setChannel (handle);   /* Set event register, this should result in
                                   interrupt */

    /* Wait for the 2nd transfer completion */
    while (1) {
        if (isr_cnt > 0) {
            isr_cnt = 0;
            break;
        }
    }

    printf
        ("EDMA: Link Example ... Data transfer of second stage is complete\n");

    /* Verify the 2nd data transfer */
    for (index = 0; index < LINK_BUF_SIZE; index++) {
        if (link_dst2[index] != link_src2[index]) {
            break;
        }
    }
    if (index == LINK_BUF_SIZE) {
        printf
            ("EDMA: Link Example ... 2nd stage data transferred correctly\n");
    }
    else {
        printf
         ("EDMA: Link Example ... 2nd stage data not transferred correctly\n");
        return;
    }

    /* Clean up */
    EDMA_intReset (chan_no);
    printf ("EDMA: Link Example ... DONE\n");
    EDMA_close (handle);
    EDMA_freeTable (link_handle);
    EDMA_intFree (tcc);
}

/**
 * ============================================================================
 *   @func   chain_example
 *
 *   @desc
 *     This performs a EDMA memory to memory transfer in two stages, by
 *     chaining.
 *
 *   @n <b> Procedure </b>
 *   @verbatim
       1. Setup the data destinations and sources for 2 transfers
       2. Enable 2 channels
       3. Allocate and configure interrupts, such that first channel transfer
          is chained to the second channel
       4. Configure the PaRAMs of the channels
       5. Setup chaining
       6. Start transfer on the first channel
       7. Wait for the completion of both the tranfers
       8. Verify the data transfers
       9. Clean up

     @endverbatim
 * ============================================================================
 */

void chain_example (void)
{
    EDMA_Handle     handle; 
    EDMA_Handle     chain_handle;
    Uint32          chan_no; 
    Uint32          chain_chan_no;
    Uint32          tcc1;
    Uint32          tcc2;
    EDMA_Config     conf = { 0 };
    Uint32          index;

    /* Setup the data area */
    for (index = 0; index < CHAIN_BUF_SIZE; index++) {
        chain_src1[index] = index;
        chain_dst1[index] = 0;
        chain_src2[index] = CHAIN_BUF_SIZE - index;
        chain_dst2[index] = 0;
    }

    /* Reset all interrupts of all channels of EDMA */
    EDMA_intResetAll ();

    chan_no = 4;        /* Consider channel 4 as primary channel */
    chain_chan_no = 5;  /* Consider channel 5 as second channel in the chain */

    /* TCC field of the first channel = second channel number, allocate it */
    tcc1 = EDMA_intAlloc (chain_chan_no);
    if (tcc1 != chain_chan_no) {
        return;
    }

    /* Enable interrupt and open channel for the first transfer */
    EDMA_intEnable (chain_chan_no);
    handle = EDMA_open (chan_no, EDMA_OPEN_RESET);

    printf
        ("EDMA: Chain Example ... Config. a 2 stage mem to mem transfer\n");
    printf ("EDMA: Chain Example ... Each transfer of %d bytes\n",
        CHAIN_BUF_SIZE);

    printf ("EDMA: Chain Example ... Configuring stage 1\n");
    conf.opt = CHAIN_OPTIONS;   /* EDMA_chian will set the TCC */
    conf.cnt = (CHAIN_BUF_SIZE);        /* Frame Count is 0 */
    conf.idx = 0;               /* 1-d source, 1-d destination, address
                                   increment for both, so
                                   FRMIDX = ELEIDX = don't care */
    conf.rld = NO_RELOAD_AND_LINK;
    conf.dst = (Uint32) & chain_dst1[0];
    conf.src = (Uint32) & chain_src1[0];
    EDMA_config (handle, &conf);

    /* Open the channel for the second transfer */
    chain_handle = EDMA_open (chain_chan_no, EDMA_OPEN_RESET);

    tcc2 = EDMA_intAlloc (6);   /* Allocate EDMA interrupt 6 for the 2nd
                                   transfer completion */
    if (tcc2 != 6) {
        return;
    }
    printf ("EDMA: Chain Example ... Configuring stage 2\n");
    conf.opt =
        CHAIN_OPTIONS | ((tcc2 & TCC_MASK) << TCC_SHIFT) | ((tcc2 &
            TCCM_MASK) << TCCM_SHIFT);   /* TCC is 6 */

    conf.cnt = (CHAIN_BUF_SIZE);        /* Frame Count is 0 */

    conf.idx = 0;               /* 1-d source, 1-d destination, address
                                   increment for both, so
                                   FRMIDX = ELEIDX = don't care */
    conf.rld = NO_RELOAD_AND_LINK;
    conf.dst = (Uint32) & chain_dst2[0];
    conf.src = (Uint32) & chain_src2[0];
    EDMA_config (chain_handle, &conf);

    printf ("EDMA: Chain Example ... Chaining the two transfers\n");
    EDMA_chain (handle, chain_handle, EDMA_TCC_SET, EDMA_ATCC_CLEAR);

    printf ("EDMA: Chain Example ... Initiating the transfer\n");
    EDMA_intEnable (tcc2);

    /* Setup the ISRs for both the transfers */
    edmaEventHook (chain_chan_no, isr2);
    edmaEventHook (tcc2, isr);

    /* Inititate transfer */
    EDMA_setChannel (handle);   /* Set event register, this should
                                   result in interrupt */

    /* Wait for the first stage of the chain */
    while (1) {
        if (parent_isr_cnt > 0) {
            parent_isr_cnt = 0;
            break;
        }
    }

    /* Wait for the second stage of the chain */
    while (1) {
        if (isr_cnt > 0) {
            isr_cnt = 0;
            break;
        }
    }
    printf ("EDMA: Chain Example ... Data transfer is complete\n");

    /* Verify the first stage data transfer */
    for (index = 0; index < CHAIN_BUF_SIZE; index++) {
        if (chain_dst1[index] != chain_src1[index]) {
            break;
        }
    }
    if (index == CHAIN_BUF_SIZE) {
        printf
            ("EDMA: Chain Example ... 1st stage data transferred correctly\n");
    }
    else {
        printf
        ("EDMA: Chain Example ... 1st stage data not transferred correctly\n");
        return;
    }

    /* Verify the second stage data transfer */
    for (index = 0; index < CHAIN_BUF_SIZE; index++) {
        if (chain_dst2[index] != chain_src2[index]) {
            break;
        }
    }
    if (index == CHAIN_BUF_SIZE) {
        printf
            ("EDMA: Chain Example ... 2nd stage data transferred correctly\n");
    }
    else {
        printf
         ("EDMA: Chain Example ... 2nd stage data not transferred correctly\n");
        return;
    }
    printf ("EDMA: Chain Example ... DONE\n");

    /* Clean up */
    EDMA_close (handle);
    EDMA_close (chain_handle);
    EDMA_intReset (tcc2);
    EDMA_intReset (chain_chan_no);
    EDMA_intFree (tcc2);
    EDMA_intFree (chain_chan_no);
}

/**
 * ============================================================================
 *   @func   qdma_example
 *
 *   @desc
 *     This performs a QDMA memory to memory transfer.
 *
 *   @n <b> Procedure </b>
 *   @verbatim
       1. Setup the data destination and source
       2. Allocate and configure interrupt
       3. Configure the QDMA
       4. Wait for the completion of the transfer
       5. Verify the data transfer
       6. Clean up

     @endverbatim
 * ============================================================================
 */
void qdma_example (void)
{
    EDMA_Config conf = { 0 };
    Int         index;
    Int         tcc;

    printf
       ("EDMA: QDMA Example ... config. to transfer a 1 dimensional array \n");
    for (index = 0; index < SIMPLE_TRANSFER_SIZE; index++) {
        src[index] = index;
        dst[index] = 0;
    }

    /* Allocate the interrupt */
    tcc = EDMA_intAlloc (EDMA_ALLOC_ANY);
    conf.opt =
        QDMA_OPTIONS | ((tcc & TCC_MASK) << TCC_SHIFT) | ((tcc & TCCM_MASK) <<
            TCCM_SHIFT);
    conf.src = (Uint32) (&src[0]);
    conf.cnt = ((SIMPLE_TRANSFER_SIZE) / sizeof (Uint32));  /* Element Count */
    conf.dst = (Uint32) (&dst[0]);

    /* Setup the ISR */
    edmaEventHook (tcc, isr);
    EDMA_intEnable (tcc);

    printf ("EDMA: QDMA Example ... Configuring and starting the transfer\n");
    EDMA_qdmaConfig (&conf);

    /* Wait for until transfer is over */
    while (1) {
        if (isr_cnt > 0) {
            isr_cnt = 0;
            break;
        }
    }

    /* Verify the transferred data */
    for (index = 0; index < SIMPLE_TRANSFER_SIZE; index++) {
        if (src[index] != dst[index]) {
            break;
        }
    }

    if (index == SIMPLE_TRANSFER_SIZE) {
      printf
        ("EDMA: QDMA Example ... transferred 1 dimensional array of %d bytes\n",
            SIMPLE_TRANSFER_SIZE);
    }
    else {
        printf ("EDMA: qdmaConfig ... Failed, while transfering an array\n");
        return;
    }
    EDMA_intFree (tcc);
    EDMA_intReset (tcc);
    printf ("EDMA: QDMA Example ... DONE\n");
}

/* Configuration of INTC module */
void configure_intc (void)
{
    CSL_IntcObj                 intcObjEdma;
    CSL_IntcGlobalEnableState   state;
    CSL_IntcEventHandlerRecord  EventRecord;
    CSL_IntcHandle              hIntcEdma;
    CSL_Status                  intStat;
    CSL_IntcParam               vectId;

    /* Intc Module Initialization */
    intcContext.eventhandlerRecord = EventHandler;
    intcContext.numEvtEntries = 1;
    CSL_intcInit (&intcContext);

    /* Enable NMIs  */
    CSL_intcGlobalNmiEnable ();

    /* Enable Global Interrupts */
    intStat = CSL_intcGlobalEnable (&state);
    if (intStat != CSL_SOK) {
        printf ("Initiallization of INTC failed\n");
    }

    /* Opening a handle for the Event edma */
    vectId = CSL_INTC_VECTID_12;
    hIntcEdma = CSL_intcOpen (&intcObjEdma, CSL_INTC_EVENTID_EDMA3CC_GINT, \
                              &vectId, NULL);
    EventRecord.handler = &eventEdmaHandler;
    EventRecord.arg = 0;
    CSL_intcPlugEventHandler (hIntcEdma, &EventRecord);

    /* Enabling event edma */
    CSL_intcHwControl (hIntcEdma, CSL_INTC_CMD_EVTENABLE, NULL);
}











