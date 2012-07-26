/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */
 
/** ===========================================================================
 *   @file  Intc_example4.c
 *
 *   @path  $(CSLPATH)\example\c64xplus\intc\intc_example4\src
 *
 *   @desc  Example of INTC
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n Demonstraing the usage and occurence of the dropped event.
 *          1. Initalizes the intc CSL required with proper ISR
 *          2. Opens the INTERR/DROP and timer events
 *          3. Enables the timer event drop 
 *          4. Intializes and setup timer module
 *          5. Poll for the event to be set 
 *          6. Closes the Intc module
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Intc_example4.pjt
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
 *  04-Aug-2005  ds Changed to support timer CSL
 *  11-Nov-2005  ds Changed to add powersaver for timer
 *  16-Dec-2005  ds Updated documentation 
 * ============================================================================
 */ 

#include <stdio.h>
#include <csl_intc.h>
#include <csl_intcAux.h>
#include <csl_tmr.h>
#include <cslr_dev.h>

/* Intc variables declarations */
CSL_IntcEventHandlerRecord  EventHandler[30];
CSL_IntcGlobalEnableState   state;
CSL_IntcEventHandlerRecord  EventRecord;    
CSL_IntcEventHandlerRecord  Record[2];  /* Suficient Entries */
CSL_IntcDropStatus          drop;
CSL_IntcContext             context; 
CSL_IntcHandle              hIntcTimer;
CSL_IntcHandle              hDrop;

/* Function forwards */
interrupt void eventTimerHandler();
void eventDropHandler(void *handle);
void intc_example (void);

/* Global variables declarations */
volatile Uint32  intrCnt = 0;
volatile Uint32  passed  = 0;
volatile Uint32  intrDrop = 0;

/* ============================================================================
 *
 *   @func   main
 *
 *   @desc
 *    This is the main routine,which invokes the example
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
 *      This is the usage and occurence of the dropped event.
 *      It implements following steps
 *          1. Initalizes the intc CSL required with proper ISR
 *          2. Opens the INTERR/DROP and timer events
 *          3. Enables the timer event drop 
 *          4. Intializes and setup timer module
 *          5. Poll for the event to be set 
 *          6. Closes the Intc module
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
    CSL_IntcObj         intcTimerObj;
    CSL_IntcObj         intcDropObj;   
    CSL_IntcParam       vectId;
    volatile Uint32     dropStat;
    volatile Uint32     timerStat;
    CSL_TmrHandle       hTmr;
    CSL_TmrObj          TmrObj;
    CSL_Status          status;
    CSL_TmrHwSetup      hwSetup = CSL_TMR_HWSETUP_DEFAULTS;
    CSL_TmrEnamode      TimeCountMode = CSL_TMR_ENAMODE_CONT;
    Uint32              LoadValue = 100;
    
    printf ("Demonstraing the usage and occurence of the dropped event\n");
    
    /* Initialize Intc */
    context.numEvtEntries = 2; 
    context.eventhandlerRecord = Record;
    CSL_intcInit(&context);
    
    /*  Enable NMIs */
    CSL_intcGlobalNmiEnable();
    
    /* Enable Global Interrupts */
    CSL_intcGlobalEnable(&state);
    
    /* Open the INTERR/DROP EVENT Object */
    vectId = CSL_INTC_VECTID_4;
    hDrop  = CSL_intcOpen (&intcDropObj, CSL_INTC_EVENTID_INTERR, &vectId , 
                                                                        NULL);
    
    EventRecord.handler = &eventDropHandler;
    EventRecord.arg = hDrop;
    CSL_intcPlugEventHandler(hDrop,&EventRecord);   
    CSL_intcQueryDropStatus(&drop);

    /* Opening a handle for the Timer 0 Event onto CPU vector 13 */
    vectId = CSL_INTC_VECTID_13;
    hIntcTimer = CSL_intcOpen (&intcTimerObj, CSL_INTC_EVENTID_TINTLO0, &vectId,
                                                                         NULL);
  
    /* Enabling timer event */
    CSL_intcHwControl(hIntcTimer,CSL_INTC_CMD_EVTDROPENABLE,NULL);
    CSL_intcHwControl(hDrop,CSL_INTC_CMD_EVTENABLE,NULL);

    /* Initialize timer CSL module */
    CSL_tmrInit(NULL);
    
    hTmr =  CSL_tmrOpen(&TmrObj, CSL_TMR_0, NULL, &status);

    CSL_tmrHwSetup(hTmr, &hwSetup);

    /* Stop the Timer */
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMLO, NULL);
    
    /* set the timer mode to unchained dual mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_DUAL_UNCHAINED;

    CSL_tmrHwSetup(hTmr, &hwSetup); 

    /* Load the period register */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_PRDLO, (void *)&LoadValue);

    /* Start the timer with one shot*/
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMLO, (void *)&TimeCountMode);

    /* Poll mode, query for the event to be set */
    do {
        CSL_intcGetHwStatus(hIntcTimer,CSL_INTC_QUERY_PENDSTATUS, \
                                                            (void*)&timerStat);
        if (timerStat)  
            intrCnt++;
        if (intrDrop)
            break;  
    } while (1);
    
    printf ("Example Passed for usage and occurence of the dropped event\n");
}   

/*
 * =============================================================================
 *   @func   eventDropHandler
 *
 *   @desc
 *     This is the interrupt event drop handler
 *
 *   @arg    handle
 *           Pointer to timer handle
 *
 *
 *   @eg
 *      eventDropHandler ();
 * =============================================================================
 */
void eventDropHandler(void *handle)
{
    intrDrop++;
    
    CSL_intcQueryDropStatus(&drop); 
    
    /* Want only one drop */
    CSL_intcHwControl(hIntcTimer,CSL_INTC_CMD_EVTDROPDISABLE,NULL);
    
}
