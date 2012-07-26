/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */
/** ===========================================================================
 *   @file  Intc_example3.c
 *
 *   @path  $(CSLPATH)\example\c64xplus\intc\intc_example3\src
 *
 *   @desc  Example of INTC
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example illustrates the opening of an event handle, 
 *      associating a handler with it, enabling it for 124 events starting from 
 *      4 to 128. This example,
 *          1. Initalizes the intc CSL required with proper ISR
 *          2. Opens 4 to 31 events with vector line 4,
 *             32 to 63 events with vector line 5, 64 to 95 events with 
 *             vector line 6 and 96 to 127 events with vector line 7
 *          3. Enables the 4 to 127 events.
 *          4. Manually sets all these events
 *          5. Prints the total number of events occured.
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Intc_example3.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* ============================================================================
 *  Revision History
 *  ===============
 *  24-Mar-2005 BRN File Created
 *  16-Dec-2005 ds  Updated documentation
 *  19-Dec-2005 ds  Added code for clearing of all events
 * ============================================================================
 */
 
#include <stdio.h>
#include <csl_intc.h>
#include <csl_intcAux.h>

/* Intc variables declaration */
CSL_IntcContext                 context; 
CSL_IntcEventHandlerRecord      EventHandler[30];
CSL_IntcGlobalEnableState       state;
CSL_IntcEventHandlerRecord      EventRecord;

/*  Function forwards */
void eventHandler(CSL_IntcEventId* event);
void intc_example (void);

/* Global variable declaration */
Uint32  evtNum = 0;

/*
 * ============================================================================
 *
 *   @func   main
 *
 *   @desc
 *     Application that calls example function
 * ============================================================================
*/
void main (void)
{
    printf ("Running Interrupt Example\n");
    
    intc_example ();

    return;
    
}

/*
 * ============================================================================
 *   @func intc_example
 *   
 *   @arg
 *      NONE
 *
 *   @desc
 *     This checks functionalities of the intc CSL.It implements following steps
 *          1. Initializes the Intc module 
 *          2. Opens the 4 to 31 events with interrupt vector line 4 
 *          3. Enables the 4 to 31 events.
 *          4. Sets manually all these events
 *          5. Opens the 32 to 63 events with interrupt vector line 5
 *          6. Enables the 32 to 63 events.
 *          7. Sets manually all these events
 *          8. Opens the 64 to 95 events with interrupt vector line 6
 *          9. Enables the 64 to 95 events.
 *          10. Sets manually all these events
 *          11. Opens the 96 to 127 events with interrupt vector line 7
 *          12. Enables the 96 to 127 events.
 *          13. Sets manually all these events.
 *          14. Prints the total number of events occured.           
 *   
 *   @return
 *      NONE
 *
 * =============================================================================
 */

void intc_example (void)
{   
    
    /* Obj for combined events */
    CSL_IntcObj         intcObj;
    CSL_IntcObj         intcObj2;
    CSL_IntcObj         intcObj4;
    CSL_IntcObj         intcObj6; 
    
    /* Obj for combiner events */
    CSL_IntcObj         intcObj0;
    CSL_IntcObj         intcObj1;
    CSL_IntcObj         intcObj3;
    CSL_IntcObj         intcObj5; 
    
    CSL_IntcHandle      hIntc;
    CSL_IntcHandle      hIntc0;
    CSL_IntcHandle      hIntc1;
    CSL_IntcHandle      hIntc2;
    CSL_IntcHandle      hIntc3;
    CSL_IntcHandle      hIntc4;
    CSL_IntcHandle      hIntc5;
    CSL_IntcHandle      hIntc6; 
    CSL_Status          intStat;
    CSL_IntcParam       vectId;
    CSL_BitMask32       evtEn;
    Uint32              eventId;
    Uint32              evtClr;
    Uint32              idx;
    
    
    /* Since there are only 3 events in the system table of 3 elements are 
     *  enough 
     */
    CSL_IntcEventHandlerRecord Record[128]; 
    context.numEvtEntries = 128; 
    context.eventhandlerRecord = Record;
    
    /* Initializes the CPU vector table, dispatchr */
    intStat = CSL_intcInit(&context);
    if (intStat != CSL_SOK) {
        printf ("INTR: Initialization... Failed.\n");
        printf ("\tReason: CSL_intcInit failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Initialization... Passed.\n");
    }

    /* Enable NMIs */
    intStat = CSL_intcGlobalNmiEnable();
    if (intStat != CSL_SOK) {
        printf ("INTR: Global NMI Enable ... Failed.\n");
        printf ("\tReason: CSL_intcGlobalNmiEnable failed. [status = 0x%x]\n", 
                                                                     intStat);
    }
    else {
        printf ("INTR: Global NMI Enable... Passed.\n");
    }

    /* Enable Global Interrupts */
    intStat = CSL_intcGlobalEnable(&state);
    if (intStat != CSL_SOK) {
        printf ("INTR: Global Enable ... Failed.\n");
        printf ("\tReason: CSL_intcGlobalEnable failed. [status = 0x%x].\n", 
                                                                     intStat);
    }
    else {
        printf ("INTR: Global Enable... Passed.\n");
    }
    
    /* Opening a handle for the Combiner 0 onto CPU vector 4 */
    vectId = CSL_INTC_VECTID_4;
    hIntc0 = CSL_intcOpen (&intcObj0, CSL_INTC_EVENTID_EVT0, &vectId , NULL);
    if ((hIntc0 == NULL) || (intStat != CSL_SOK)) {
            printf ("INTR: Open... Failed.\n");
            printf ("\tReason: Error opening the instance ");
            printf ("[status = 0x%x, hIntc = 0x%x]\n", intStat, hIntc0);
            
    }
    else
        printf ("INTR: Open... Passed.\n");

    /* Opening a handle for the Combiner 1 onto CPU vector 5 */
    vectId = CSL_INTC_VECTID_5;
    hIntc1 = CSL_intcOpen (&intcObj1, CSL_INTC_EVENTID_EVT1, &vectId , NULL);
    if ((hIntc1 == NULL) || (intStat != CSL_SOK)) {
            printf ("INTR: Open... Failed.\n");
            printf ("\tReason: Error opening the instance. [status = 0x%x, \
                                        hIntc = 0x%x].\n", intStat, hIntc1);
            
    }
    else
        printf ("INTR: Open... Passed.\n");

    /* Opening a handle for the Combiner 2 onto CPU vector 6 */
    vectId = CSL_INTC_VECTID_6;
    hIntc3 = CSL_intcOpen (&intcObj3, CSL_INTC_EVENTID_EVT2, &vectId , NULL);
    if ((hIntc3 == NULL) || (intStat != CSL_SOK)) {
            printf ("INTR: Open... Failed.\n");
            printf ("\tReason: Error opening the instance. [status = 0x%x, \
                                    hIntc = 0x%x].\n", intStat, hIntc3);
            
    }
    else
        printf ("INTR: Open... Passed.\n");

    /* Opening a handle for the Combiner 3 onto CPU vector 7 */
    vectId = CSL_INTC_VECTID_7;
    hIntc5 = CSL_intcOpen (&intcObj5, CSL_INTC_EVENTID_EVT3, &vectId , NULL);
    if ((hIntc5 == NULL) || (intStat != CSL_SOK)) {
            printf ("INTR: Open... Failed.\n");
            printf ("\tReason: Error opening the instance. [status = 0x%x, \
                                    hIntc = 0x%x].\n",  intStat, hIntc5);
            
    }
    else
        printf ("INTR: Open... Passed.\n");
    
    /* Clear the all events */
    for (idx = 0; idx < 4; idx++) {
        evtClr = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTFLAG[idx];
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[idx] = evtClr;
    }
            
    /* The event combiner divides the 124 system events in four groups. 
     * The first group includes events 4-31,the second group includes events 
     * 32-63, the third group includes events 64-95, the fourth group includes
     * events 96-127. Events within each group can be combined to provide a new 
     * combined event. These new events are designated interrupt vector line 4,
     * interrupt vector line 5, interrupt vector line 6, interrupt vector line 7
     * respectively.
     */
        
    /* For loop to check 4 to 31 interrupts with interrupt vector line 4 */
    for (eventId = 4; eventId < 32; eventId++) {
        /* Open and setup the handler for each eventId*/
        vectId = CSL_INTC_VECTID_COMBINE;
        hIntc = CSL_intcOpen (&intcObj, (CSL_IntcEventId)eventId, &vectId, 
                                                                        NULL);
        EventRecord.handler = (CSL_IntcEventHandler)&eventHandler;
        EventRecord.arg = hIntc;
        CSL_intcPlugEventHandler(hIntc,&EventRecord); 
        evtEn = (1<<eventId);
        
        /* Note :- Combined events along with the combiner event all can be 
                   enabled in one API */
        intStat = CSL_intcHwControl(hIntc0,CSL_INTC_CMD_EVTENABLE,&evtEn);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to enable event ... Failed.\n");
        }
        else
            printf("INTR: HwControl to enable event ... Passed.\n");
    
        /* Set events manually */
        intStat = CSL_intcHwControl(hIntc,CSL_INTC_CMD_EVTSET,NULL);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to set an event  ... Failed.\n");
        }
        else
            printf("INTC: HwControl to set an event ... Passed.\n");
        
    }
    
    /* For loop to check 32 to 63 interrupts with interrupt vector line 5 */    
    for (eventId = 32; eventId <64; eventId++) {
        
        /* Open and setup the handler for each eventId*/
        vectId = CSL_INTC_VECTID_COMBINE;
        hIntc2 = CSL_intcOpen (&intcObj2, (CSL_IntcEventId)eventId, &vectId, 
                                                                         NULL);
        EventRecord.handler = (CSL_IntcEventHandler)&eventHandler;
        EventRecord.arg = hIntc2;
        CSL_intcPlugEventHandler(hIntc2,&EventRecord); 
        evtEn = (1<<(eventId-32));
        
        /* Note :- Combined events along with the combiner event all can be 
                   enabled in one API */
        intStat = CSL_intcHwControl(hIntc1,CSL_INTC_CMD_EVTENABLE,&evtEn);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to enable event ... Failed.\n");
        }
        else
            printf("INTR: HwControl to enable event ... Passed.\n");

        
    
        /* Set events manually */
        intStat = CSL_intcHwControl(hIntc2,CSL_INTC_CMD_EVTSET,NULL);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to set an event  ... Failed.\n");
        }
        else
            printf("INTR: HwControl to set an event ... Passed.\n");
        
    }

    /* For loop to check 64 to 95 interrupts with interrupt vector line 6 */    
    for (eventId = 64; eventId <96; eventId++) {
        
        /* Open and setup the handler for each eventId*/
        vectId = CSL_INTC_VECTID_COMBINE;
        hIntc4 = CSL_intcOpen (&intcObj4, (CSL_IntcEventId)eventId, &vectId , 
                                                                        NULL);
        EventRecord.handler = (CSL_IntcEventHandler)&eventHandler;
        EventRecord.arg = hIntc4;
        CSL_intcPlugEventHandler(hIntc4,&EventRecord); 
        evtEn = (1<<(eventId-64));
        
        /* Note :- Combined events along with the combiner event all can be 
                   enabled in one API */
        intStat = CSL_intcHwControl(hIntc3,CSL_INTC_CMD_EVTENABLE,&evtEn);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to enable event ... Failed.\n");
        }
        else
            printf("INTR: HwControl to enable event ... Passed.\n");
    
        /* Set events manually */
        intStat = CSL_intcHwControl(hIntc4,CSL_INTC_CMD_EVTSET,NULL);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to set an event  ... Failed.\n");
        }
        else
            printf("INTR: HwControl to set an event ... Passed.\n");
    
    }

    /* For loop to check 96 to 128 interrupts with interrupt vector line 7 */    
    for (eventId = 96; eventId <128; eventId++) {
        
        /* Open and setup the handler for each eventId*/
        vectId = CSL_INTC_VECTID_COMBINE;
        hIntc6 = CSL_intcOpen (&intcObj6, (CSL_IntcEventId)eventId, &vectId , 
                                                                         NULL);
        EventRecord.handler = (CSL_IntcEventHandler)&eventHandler;
        EventRecord.arg = hIntc6;
        CSL_intcPlugEventHandler(hIntc6,&EventRecord); 
        evtEn = (1<<(eventId-96));
        
        /* Note :- Combined events along with the combiner event all can be 
                   enabled in one API */
        intStat = CSL_intcHwControl(hIntc5,CSL_INTC_CMD_EVTENABLE,&evtEn);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to enable event ... Failed.\n");
        }
        else
            printf("INTR: HwControl to enable event ... Passed.\n");
    
        /* Set events manually */
        intStat = CSL_intcHwControl(hIntc6,CSL_INTC_CMD_EVTSET,NULL);
        if(intStat != CSL_SOK) {
            printf("INTR: HwControl to set an event  ... Failed.\n");
        }
        else
            printf("INTR: HwControl to set an event ... Passed.\n");
        
    }

    printf("INTR: The Total number of Events occured are: %d\n", evtNum);
    
    /* Closing all handles */
    
    intStat = CSL_intcClose(hIntc);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
        
    intStat = CSL_intcClose(hIntc0);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
    
    intStat = CSL_intcClose(hIntc1);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
    
    intStat = CSL_intcClose(hIntc2);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
    
    intStat = CSL_intcClose(hIntc3);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
    
    intStat = CSL_intcClose(hIntc4);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
    intStat = CSL_intcClose(hIntc5);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
    
    intStat = CSL_intcClose(hIntc6);
    if (intStat != CSL_SOK) {
        printf ("INTR: Close ... Failed.\n");
        printf ("\tReason: Intc Close failed. [status = 0x%x].\n", intStat);
    }
    else {
        printf ("INTR: Close ... Passed.\n");
    }
        
}  
 
/*
 * =============================================================================
 *   @func   eventHandler
 *
 *   @desc
 *     This is the intc event handler
 *
 *   @arg    event
 *           Pointer to events
 *
 *
 *   @eg
 *      eventHandler ();
 * =============================================================================
 */
void eventHandler (
    CSL_IntcEventId     *event
)
{
    evtNum += 1;
    printf("INTR: EVENT Handler for event:%d\n",*event);
    CSL_intcEventClear (*event);
}

