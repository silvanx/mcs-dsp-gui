/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ==========================================================================
 */
/** ===========================================================================
 *   @file  Intc_example2.c
 *
 *   @path  $(CSLPATH)\c64plus\example\intc
 *
 *   @desc  Example of INTC
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example demonstrating usage of the combiners in the Interrupt
 *      controller with the help of the the timers. This example,
 *          1. Intializes Intc module
 *          2. Opens a handle for the Timer 0 onto CPU vector 12
 *          3. Plugs timer event handler and enables the event
 *          4. Intializes and opens the timer module
 *          5. Sets up and starts the timer
 *          6. Wait for interrupt genaration, (count to become 20)
 *          7. Disables the timer event
 *          8. Close the Intc module
 *          9. Opens the combined event on CPU vector 12
 *          10. Opens the timer event on the combiner vector 
 *             CSL_INTC_VECTID_COMBINE
 *          11. Enables the combined and timer events
 *          12. Waits for interrupt genaration, (count to become 20)
 *          13. Disables the timer and combined events
 *          14. Enable the timer and combined events
 *          15. Wait for interrupt genaration, (count to become 20)
 *          16. Displays the message
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Intc_example2.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
   
/* ============================================================================
 *  Revision History
 *  ===============
 *  29-Jun-2004  Ruchika Kharwar File Created.
 *
 *  04-Aug-2005  ds  Changed to support timer CSL
 *  11-Nov-2005  ds  Changed to add powersaver clock for timer 
 *  16-Dec-2005  ds  Updated documentation
 *  28-Mar-2006  ds   Added code to clear all the evnts
 * ============================================================================
 */ 

#include <csl_intc.h>
#include <csl_intcAux.h>
#include <csl_tmr.h>
#include <cslr_dev.h>
#include <stdio.h>

/* Intc variables decalarations */
CSL_IntcObj                 intcTimerObj;
CSL_IntcObj                 intcCombObj;
CSL_IntcHandle              hIntcTimer;
CSL_IntcHandle              hIntcComb;
CSL_IntcGlobalEnableState   state;
CSL_IntcEventHandlerRecord  EventRecord;
CSL_IntcParam               vectId;
CSL_IntcContext             context; 
CSL_IntcEventHandlerRecord  Record[1]; 
CSL_IntcEventHandlerRecord  EventHandler[30];

/* Function forwards */
void eventTimerHandler(void *handle);
void intc_example (void);

/* Global variable declarations */
volatile int    intrCnt=0;

/*
 * ============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine, which invokes the example
 * ============================================================================
 */
void main(void)
{   
    Bool    timer0En;
    
    printf ("Running Interrupt Example\n");
    
    /* Unlock the control register */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);

    /* Enable the Powersaver clock for TIMER 0 */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TIMER0CTL, 
               ENABLE);

    do {
        timer0En = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_TIMER0STAT);
    } while (timer0En != TRUE);

    printf("Powersaver clock for TIMER 0 is enabled\n");
    
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
 *      This is the example for combiners in the interrupt comtroller.
 *      It implements following steps
 *          1. Initalizes the intc CSL required with proper ISR
 *          2. Intializes Timer.
 *          3. Enables the timer event
 *          4. Waits for timer interrupt generate.
 *          5. Disables the timer event
 *          6. Closes the Intc module
 *          7. Opens the combined event on CPU vector 12
 *          8. Opens the timer event on the combiner vector 
 *             CSL_INTC_VECTID_COMBINE
 *          9. Enables the combined and timer events
 *          10. Waits for interrupt genaration, (count to become 20)
 *          11. Disables the timer and combined events
 *          12. Enables the timer and combined events
 *          13. Waits for interrupt genaration, (count to become 20)
 *          14. Closes the timer module
 *          15. Closes the Intc module
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
    CSL_TmrHandle       hTmr;
    CSL_TmrObj          TmrObj;
    CSL_Status          status, intStat;
    CSL_TmrHwSetup      hwSetup = CSL_TMR_HWSETUP_DEFAULTS;
    CSL_TmrEnamode      TimeCountMode = CSL_TMR_ENAMODE_CONT;
    volatile Uint32     delay;
    Uint32              LoadValue = 100;
    Uint32              evtClr;
    Uint32              idx;
    CSL_BitMask32       evtEn;

    printf ("Demonstrating usage of the combiners in the Intc\n");
     
    /* Init the interrupt controller initializes the CPU vector table,
     * dispatcher
     */
    context.numEvtEntries = 1; 
    context.eventhandlerRecord = Record;
    status = CSL_intcInit(&context);
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
    intStat = CSL_intcGlobalEnable(&state);
    if (intStat != CSL_SOK) {
        printf ("Intc global enable failed\n");
        return;
    }

    /* Opening a handle for the Timer 0 onto CPU vector 12 */
    vectId = CSL_INTC_VECTID_12;
    hIntcTimer = CSL_intcOpen (&intcTimerObj, CSL_INTC_EVENTID_TINTLO0, \
                               &vectId , NULL);
    if (hIntcTimer == NULL) {
        printf("Intc open failed\n");
        return;
    }
     
    /* Plug Event handler */
    EventRecord.handler = &eventTimerHandler;
    EventRecord.arg = hIntcTimer;
    status = CSL_intcPlugEventHandler(hIntcTimer,&EventRecord);
    if (status != CSL_SOK) {
        printf("Intc plug event handler failed\n");
        return;
    }
    
    /* Checking the CSL_INTC_CMD_EVTENABLE, by enabling timer event */   
    status = CSL_intcHwControl(hIntcTimer, CSL_INTC_CMD_EVTENABLE,NULL);
    if (status != CSL_SOK) {
        printf("Intc CSL_INTC_CMD_EVTENABLE command failed\n");
        return;
    }

    /* Initialize and Setup timer CSL module */
    CSL_tmrInit(NULL);
    hTmr =  CSL_tmrOpen(&TmrObj, CSL_TMR_0, NULL, &status);
    
    /* Setup timer */
    CSL_tmrHwSetup(hTmr, &hwSetup);

    /* Stop the timer */
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMLO, NULL);
    
    /* set the timer mode to unchained dual mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_DUAL_UNCHAINED;
    
    /* Setup timer */
    CSL_tmrHwSetup(hTmr, &hwSetup); 

    /* Load the period register */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_PRDLO, (void *)&LoadValue);

    /* Start the timer with auto reload */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMLO, (void *)&TimeCountMode);
    
    /* Wait for interrupt genaration, (count to become 20) */ 
    while (intrCnt < 20);
    intrCnt = 0;

    /* Checking the CSL_INTC_CMD_EVTDISABLE, by disabling timer event */
    status = CSL_intcHwControl(hIntcTimer,CSL_INTC_CMD_EVTDISABLE,NULL);
    if (status != CSL_SOK) {
        printf("Intc CSL_INTC_CMD_EVTDISABLE command failed\n");
        return;
    }
    
    /* Wait for long time, to check timer stop */
    for (delay =0 ; delay < 10000; delay++);
    
    /* Check for timer counter value */
    if (intrCnt != 0)
        while(1);       /* Failed */
    
    /* Close Intc CSL */
    CSL_intcClose(hIntcTimer);

    /* Do the same stuff with an event that is on a combined with others.
     * Opening a handle for the Combiner 0 onto CPU vector 12 
     */
    
    /* Open the combined event on CPU vector 12 */
    vectId = CSL_INTC_VECTID_12;
    hIntcComb = CSL_intcOpen(&intcCombObj,CSL_INTC_EVENTID_EVT2, &vectId,NULL);
    if (hIntcComb == NULL) {
        printf("Intc combined event open failed \n");
        return;
    }
    vectId = CSL_INTC_VECTID_COMBINE;
    hIntcTimer = CSL_intcOpen (&intcTimerObj, CSL_INTC_EVENTID_TINTLO0, \
                               &vectId , NULL);
    if (hIntcTimer == NULL) {
        printf("Intc open failed\n");
        return;
    }
    
    /* Plug event handler */    
    EventRecord.handler = &eventTimerHandler;
    EventRecord.arg = hIntcTimer;
    status = CSL_intcPlugEventHandler(hIntcTimer, &EventRecord);  
    if (status != CSL_SOK) {
        printf("Intc plug event handler failed\n");
        return;
    }

    /* Enabling the combined event */
    evtEn = CSL_INTC_EVENTID_TINTLO0;
    status = CSL_intcHwControl(hIntcComb,CSL_INTC_CMD_EVTENABLE, &evtEn);
    if (status != CSL_SOK) {
        printf("Enabling the combined event failed\n");
        return;
    }
    
    /* Enabling timer event */
    status = CSL_intcHwControl(hIntcTimer,CSL_INTC_CMD_EVTENABLE,NULL);
    if (status != CSL_SOK) {
        printf("Enabling timer event failed\n");
        return;
    }
    
    /* Wait for interrupt genaration, (count to become 20) */ 
    while (intrCnt < 20);
    intrCnt = 0;
    
    /* Checking the CSL_INTC_CMD_EVTDISABLE by disabling timer event */
    status = CSL_intcHwControl(hIntcTimer,CSL_INTC_CMD_EVTDISABLE,NULL);
    if (status != CSL_SOK) {
        printf("Disabling the combined event failed\n");
        return;
    }

    /* Wait for a long time */
    for (delay =0 ; delay < 10000; delay++);
    
    /* Check for timer counter value */
    if (intrCnt != 0)
        while(1);       /* Failed */
    
    /* Now doing the same test with the Combined Event disabled/enabled */        
    intrCnt = 0;
    CSL_intcHwControl(hIntcComb,CSL_INTC_CMD_EVTDISABLE,NULL);
    
    /* Enabling timer event */
    CSL_intcHwControl(hIntcTimer,CSL_INTC_CMD_EVTENABLE,NULL);
    
    /* Wait for a long time, to check timer stop */
    for (delay =0 ; delay < 10000; delay++);

    /* Check for timer counter value */
    if (intrCnt != 0)
        while(1); /* Failed */
        
    /* Enable the combined event */    
    CSL_intcHwControl(hIntcComb,CSL_INTC_CMD_EVTENABLE,NULL);   
    
    /* Wait for interrupt genaration, (count to become 20) */ 
    while (intrCnt < 20);
    
    printf ("Intc Example Done \n");
    
    /* Clear the all events */
    for (idx = 0; idx < 4; idx++) {
        evtClr = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTFLAG[idx];
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[idx] = evtClr;
    }

    /* Close Intc */
    CSL_tmrClose (hTmr);
    CSL_intcClose(hIntcTimer);
    CSL_intcClose(hIntcComb);   
}
   
/*
 * =============================================================================
 *   @func   eventTimerHandler
 *
 *   @desc
 *     This is the interrupt event handler for timer 
 *
 *   @arg    handle
 *           Pointer to timer handle
 *
 *
 *   @eg
 *      eventTimerHandler ();
 * =============================================================================
 */
void eventTimerHandler (
    void       *handle
)
{
    intrCnt++;
    
    if (intrCnt == 20)
        CSL_intcHwControl(hIntcTimer,CSL_INTC_CMD_EVTDISABLE,NULL);

}
