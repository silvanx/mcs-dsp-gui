/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ==========================================================================
 */
/** ===========================================================================
 *   @file  Intc_example5.c
 *
 *   @path  $(CSLPATH)\example\c64xplus\intc\intc_example5\src
 *
 *   @desc  Example of INTC
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example demonstrating usage of the exception handling. Timer 0,1 
 *      are treated as exceptions and they are cleared accordingly
 *      This example,
 *          1. Intializes Intc module and the CPU vector table, dispatcher
 *          2. Enables the external exceptions
 *          3. Hook up the NMI Isr
 *          4. Opens a handle for the Timer 0 and Timer1 Event as an 
 *             exception event
 *          5. Plugs timers event handler
 *          6. Enables timers exception
 *          7. Intializes and opens the timer module 
 *          8. Sets up the timer modules
 *          9. starts the timers
 *          10. Wait for exceptions to occur
 *          11. print the result
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Intc_example5.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
   
/* ============================================================================
 *  Revision History
 *  ===============
 *  2-July-2004  Ruchika Kharwar File Created.
 *
 *  14-Nov-2005  ds changed to support timer CSL
 *
 * ============================================================================
 */ 

#include <csl_intc.h>
#include <csl_intcAux.h>
#include <cslr_dev.h>
#include <csl_tmr.h>
#include <soc.h>
#include <stdio.h>

/* Forward declarations */
void eventTimer0Handler(void *handle);
void eventTimer1Handler(void *handle);
void NMI_handler();
void intc_example (void);

/* Global variables declarations */
volatile Int timer0Cnt = 0;
volatile Int timer1Cnt = 0;
volatile Int passed = 0;
Uint32   excepStatus1;

/* Intc Variable declarations */
CSL_IntcEventHandlerRecord  EventHandler[30];
CSL_IntcContext             context; 
CSL_IntcEventHandlerRecord  Record[3]; 

/* ============================================================================
 *
 *   @func   main
 *
 *   @desc
 *    This is the main routine,which invokes the example
 * ============================================================================
 */
void main (void)
{   
    Bool      timerEn;
    Bool      timerEn1;
    
    printf ("Demonstrating the exception handling \n");
    
    /* Unlock the control register */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);
               
    /* Enable the timer0 */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TIMER0CTL, 
               ENABLE);
    do {
        timerEn = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_TIMER0STAT);
    } while (timerEn != TRUE);
    
    /* Enable the timer1 */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);

    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TIMER1CTL, 
               ENABLE);
    do {
        timerEn1 = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_TIMER1STAT);
    } while (timerEn1 != TRUE);

    printf("Power saver clock for TIMER0 and TIMER1 Enabled\n");
    
    /* Invoke example */
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
 *      Demonstrating usage of the exception handling. Timer 0,1 are treated 
 *      as exceptions and they are cleared accordingly
 *      It implements following steps
 *          1. Intializes Intc module and the CPU vector table, dispatcher
 *          2. Enables the external exceptions
 *          3. Hook up the NMI Isr
 *          4. Opens a handle for the Timer 0 and Timer1 Event as an 
 *             exception event
 *          5. Plugs timers event handler
 *          6. Enables timers exception
 *          7. Intializes and opens the timer module 
 *          8. Sets up the timer modules
 *          9. starts the timers
 *          10. Wait for exceptions to occur
 *          11. print the result
 *          12. Close intc and timer module
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
    CSL_IntcObj                 intcTimerObj0;
    CSL_IntcObj                 intcTimerObj1;
    CSL_IntcHandle              hIntcTimer0;
    CSL_IntcHandle              hIntcTimer1;
    CSL_IntcGlobalEnableState   state;
    CSL_IntcEventHandlerRecord  eventRecord;
    CSL_IntcParam               vectId;
    CSL_TmrHandle               hTmr;
    CSL_TmrHandle               hTmr1;
    CSL_TmrObj                  tmrObj;
    CSL_TmrObj                  tmrObj1;
    CSL_Status                  status;
    CSL_TmrHwSetup              hwSetup = CSL_TMR_HWSETUP_DEFAULTS;
    CSL_TmrHwSetup              hwSetup1 = CSL_TMR_HWSETUP_DEFAULTS;
    CSL_TmrEnamode              TimeCountMode = CSL_TMR_ENAMODE_ENABLE;
    volatile Uint32             delay;
    Uint32                      LoadValue = 100;
    CSL_BitMask32               prevState;
    

    /* Init the Interrupt Controller 
     * Initializes the CPU vector table, dispatcher
     */
    context.numEvtEntries = 3; 
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
    
    /* Enable Global Interrupts */
    status = CSL_intcGlobalEnable(&state);
    if (status != CSL_SOK) {
        printf ("Intc global enable failed\n");
        return;
    }
    
    /* Enable global exceptions */ 
    status = CSL_intcGlobalExcepEnable (); 
    if (status != CSL_SOK) {
        printf ("Intc global exceptions enable failed\n");
        return;
    }
    
    /* Enable external exceptions */ 
    status = CSL_intcGlobalExtExcepEnable ();
    if (status != CSL_SOK) {
        printf ("Intc global external exceptions enable failed\n");
        return;
    }
    
    /* Hook up the NMI Isr */
    status = CSL_intcHookIsr(CSL_INTC_VECTID_NMI,NMI_handler);
    if (status != CSL_SOK) {
        printf ("Intc hook up NMI Isr failed\n");
        return;
    }
    
    /* Opening a handle for the Timer 0 Event as an exception event */
    vectId = CSL_INTC_VECTID_EXCEP;
    hIntcTimer0 = CSL_intcOpen (&intcTimerObj0, CSL_INTC_EVENTID_TINTLO0, 
                                &vectId , NULL);
    if (hIntcTimer0 == NULL) {
        printf("Intc open failed for timer0 event \n");
        return;
    }  
                              
    /* Plug timer0 event handler */
    eventRecord.handler = &eventTimer0Handler;
    eventRecord.arg = hIntcTimer0;
    status = CSL_intcPlugEventHandler(hIntcTimer0,&eventRecord); 
    if (status != CSL_SOK) {
        printf("Intc plug event handler for timer0 event failed\n");
        return;
    }
    
    /* Opening a handle for the Timer 1 Event as an exception event */
    vectId = CSL_INTC_VECTID_EXCEP;
    hIntcTimer1 = CSL_intcOpen (&intcTimerObj1, CSL_INTC_EVENTID_TINTLO1, 
                                &vectId , NULL);
    if (hIntcTimer1 == NULL) {
        printf("Intc open failed for timer1 event\n");
        return;
    }
    
    /* Plug timer1 event handler */
    eventRecord.handler = &eventTimer1Handler;
    eventRecord.arg = hIntcTimer1;
    status = CSL_intcPlugEventHandler(hIntcTimer1,&eventRecord); 
    if (status != CSL_SOK) {
        printf("Intc plug event handler for timer1 event failed\n");
        return;
    }
    
    /* Enabling timers exception */
    status = CSL_intcExcepAllEnable (CSL_INTC_EXCEP_64TO95, 
                                    (1 << (67 - 64))|(1 << (69 - 64)), &prevState);
    if (status != CSL_SOK) {
        printf("Intc enabling timer exceptions failed\n");
        return;
    }
    
    /* Initialize timer CSL module */
    CSL_tmrInit(NULL);
    
    /* Open the timer0 and timer1 */
    hTmr =  CSL_tmrOpen(&tmrObj, CSL_TMR_0, NULL, &status);
    hTmr1 =  CSL_tmrOpen(&tmrObj1, CSL_TMR_1, NULL, &status);

    /* Stop the Timer */
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMLO, NULL);

    /* Stop the Timer */
    status = CSL_tmrHwControl(hTmr1, CSL_TMR_CMD_RESET_TIMLO, NULL);

    /* Set the timer mode to unchained dual mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_DUAL_UNCHAINED;

    /* Set the timer mode to unchained dual mode */
    hwSetup1.tmrTimerMode = CSL_TMR_TIMMODE_DUAL_UNCHAINED;
    
    /* Setup timers */
    CSL_tmrHwSetup(hTmr, &hwSetup); 
    CSL_tmrHwSetup(hTmr1, &hwSetup1); 

    /* Load the period register of timer0 */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_PRDLO, (void *)&LoadValue);
    
    /* Load the period register of timer1 */
    CSL_tmrHwControl(hTmr1, CSL_TMR_CMD_LOAD_PRDLO, (void *)&LoadValue);
    
     /* Start the timer0 with one shot*/
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMLO, (void *)&TimeCountMode);

    /* Start the timer1 with one shot*/
    CSL_tmrHwControl(hTmr1, CSL_TMR_CMD_START_TIMLO, (void *)&TimeCountMode);
    
    /* Waits for exception to generate */
    while (!passed);
    
    /* Wait for some time */
    for (delay = 0; delay < 100; delay++);
    
    printf ("Demonstrating the exception handling Done\n");
        
}

/*
 * =============================================================================
 *   @func   NMI_handler
 *
 *   @desc
 *     This is the interrupt exception handler
 *
 *   @arg    
 *      None
 *
 *
 *   @eg
 *      NMI_handler ();
 * =============================================================================
 */
#pragma NMI_INTERRUPT(NMI_handler);
void NMI_handler (void)
{
    Uint32        excepStatus1;
    Uint32        rcvExcep64to95;
    Uint32        evtMask;
    Int           evtId;
    CSL_BitMask32 prevState;
    
    /* Get the exception status */
    CSL_intcExcepAllStatus(CSL_INTC_EXCEP_64TO95,&excepStatus1);
    
    while (excepStatus1) {
        rcvExcep64to95 = excepStatus1;
        CSL_intcExcepAllClear(CSL_INTC_EXCEP_64TO95,excepStatus1);
        evtMask = 1;
        evtId = 64;
        do {
            if (rcvExcep64to95 & evtMask) {
                CSL_intcInvokeEventHandle(evtId);
                rcvExcep64to95 &= ~evtMask;
            }
            evtMask = evtMask << 1;
            evtId++;
        } while (rcvExcep64to95);
        CSL_intcExcepAllStatus(CSL_INTC_EXCEP_64TO95,&excepStatus1);
    }
    
    CSL_intcExcepAllDisable(CSL_INTC_EXCEP_64TO95,(1<<3)|(1<< 5), &prevState);     
    
    passed++;
    
}

/*
 * =============================================================================
 *   @func   eventTimer0Handler
 *
 *   @desc
 *     This is the interrupt handler for timer 0
 *
 *   @arg    
 *      None
 *
 *
 *   @eg
 *      eventTimer0Handler ();
 * =============================================================================
 */
void eventTimer0Handler (
    void    *handle
)
{
    timer0Cnt++;
}

/*
 * =============================================================================
 *   @func   eventTimer1Handler
 *
 *   @desc
 *     This is the interrupt handler for timer 1
 *
 *   @arg    
 *      None
 *
 *
 *   @eg
 *      eventTimer1Handler ();
 * =============================================================================
 */
void eventTimer1Handler (
    void    *handle
)
{
    timer1Cnt++;
}

