/* =============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 * ==========================================================================*/

/** ===========================================================================
 * @file Timer_example.c
 *
 * @path $(CSLPATH)\example\timer\src
 *
 * @desc Example for the usage of General purpose timer CSL APIs
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 * @n <b> Example Description </b>
 * @n The example illustartes the usage of CSL APIs for using timer.
 *    1. This example configures the first instance of timer
 *       as interrupt or event to be sourced normally by the timer. 
 *    2. This enables the timer in one shot mode (for watchdog mode timer is
 *       enabled in continuos mode).
 *    3. The  interrupt handler announces occurance of each interupt 
 *       to the application.
 *    4. The above said procedure is followed for all the modes of the timer
 *       (i.e. 64 bit timer, dual 32 bit timer(chained and unchained)
 *       and watchdog).
 *==============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Timer_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *   
 * =============================================================================
 */ 

/** ============================================================================
 *  Revision History
 *  =============== 
 *  21-Apr-2005 PSK  - File Created.
 *  29-Jul-2005 PSK  - Updted changes acooriding to revised timer spec. The 
 *                     number convention TIM12, TIM34 are changed to TIMLO and 
 *                     TIMHI.  
 *  30-Nov-2005 NG   - Updated documentation
 *  06-Feb-2006 ds   - Updated example according to C6455 user guide.(Removed 
 *                     tmrClksrcHi and tmrIpGateHi hwsetup configuration)
 *  23-Mar-2006 ds   - Fixed Bug PSG00001172
 * ============================================================================= 
 */

#include <csl_tmr.h>
#include <stdio.h>
#include <csl_intc.h>
#include <soc.h>
#include <csl_intcAux.h>
#include <cslr_dev.h>

/* Handle for the TMR instance */
CSL_TmrHandle         hTmr;

/* NOTE: change the Instance of the timer for different timer instances */
Uint8 IntcInstance = CSL_TMR_0;

/* Locals & Forwards */
void tmrIntcPrdLoLoadDemo(void);
void tmrIntcPrdHiLoadDemo(void);
void tmrIntcChainedDemo(void);
void tmrIntcGptDemo(void);
void tmrWdtModeDemo(void);

/*
 *****************************************************************************
 *                    INTC related code                             
 *****************************************************************************
 */
    
/* Intc Declarations */ 
CSL_IntcObj                  tmrIntcObj, tmrIntcObj1;
CSL_IntcHandle               tmrIntcHandle, tmrIntcHandle1;
CSL_IntcContext              context, context1;

CSL_IntcEventHandlerRecord   eventHandler[30];
CSL_IntcEventHandlerRecord   record[1];

/* count for ISR */
volatile int intrCnt = 0;

/*
 * =============================================================================
 *   @func  TimerInterruptHandler
 *  
 *   @arg
 *      event - interrupt event id
 *
 *   @desc
 *      Handler for Timer Interrupt
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void TimerInterruptHandler (
    CSL_IntcEventId *event
)
{
    intrCnt++;
    CSL_intcEventClear(*event);
}

/** ===========================================================================
 *  @n@b   main
 *
 *  @b Description
 *  @n This is the main function for the file.This initializes the CSL for 
 *     INTC, installs interrupt handler for first instance of general purpose 
 *     timer and invokes the routine which demonstrates the usage of CSL APis 
 *     for General purpose timer 
 * ============================================================================
 */
void main (
    void
)
{   
    CSL_IntcGlobalEnableState state;
    
    Bool  timer0En;
    
    /* Unlock the control register */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);
               
    /* Enable the Powersaver clock for TIMER */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_TIMER0CTL, 
               ENABLE);

    do {
        timer0En = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_TIMER0STAT);
    } while ((timer0En) != TRUE);

    printf("Powersaver clock for TIMER is enabled\n");
    
    /* Initialize INTC */
    context.numEvtEntries = 1;
    context.eventhandlerRecord = record;

    CSL_intcInit(&context);
  
    /* Enable NMIS */
    CSL_intcGlobalNmiEnable();

    /* Enable all interrupts */
    CSL_intcGlobalEnable(&state);
        
    tmrIntcPrdLoLoadDemo();
    tmrIntcPrdHiLoadDemo();
    tmrIntcChainedDemo();
    tmrIntcGptDemo();
    tmrWdtModeDemo();

    printf(">>>>>> Example for all the modes of timer are \
                          completed  <<<<<<<< \n");
}

/*
 * =============================================================================
 *   @func  tmrIntcPrdLoLoadDemo
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This funtion is example for the Period register loading with value.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void tmrIntcPrdLoLoadDemo (
    void
)
{
    CSL_TmrObj TmrObj;
    CSL_Status intStat, status;
    CSL_TmrHwSetup hwSetup = CSL_TMR_HWSETUP_DEFAULTS;
    CSL_IntcEventHandlerRecord EventRecord;
    CSL_IntcParam vectId;
  
    Uint32 LoadValue = 100;
  
    CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_ENABLE;

    /* Clear local data structures */
    memset(&TmrObj, 0, sizeof(CSL_TmrObj));
    printf("Running Gp Timer Interrupt DUAL UNCHAINED Low....\n");
    
    /**************************************************************
    * INTC related code                               *
    **************************************************************/
     
    /* Open INTC */
    vectId = CSL_INTC_VECTID_12;

    tmrIntcHandle = CSL_intcOpen(&tmrIntcObj, CSL_INTC_EVENTID_TINTLO0, &vectId, 
                                 &intStat);
    
    /* Bind ISR to Interrupt */
    EventRecord.handler = (CSL_IntcEventHandler)&TimerInterruptHandler;
    EventRecord.arg = (void *)tmrIntcHandle;
    CSL_intcPlugEventHandler(tmrIntcHandle, &EventRecord);
    
    /* Event Enable */
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);
       
    /**************************************************************/

    /* Initialize timer CSL module */
    CSL_tmrInit(NULL);
    
    hTmr =  CSL_tmrOpen(&TmrObj, IntcInstance, NULL, &status);

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

    /* INTC related code */
    while (1) {
        if (intrCnt == 1)
            break;
    }
      
    /**************************************************************/
    
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTDISABLE, NULL);
    
    printf("INTR: The Total number of Events occured are: 0x%d\n", intrCnt);
  
    intrCnt = 0;
  
    /* Stop the Timer */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMLO, NULL);
    
    printf("Example for TIMLO completed\n");

    /* Close the Tmr instance */
    CSL_tmrClose(hTmr);
    CSL_intcClose(tmrIntcHandle);    
}

/*
 * =============================================================================
 *   @func  tmrIntcPrdHiLoadDemo
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This function is example for the Period register 34 loading with value.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void tmrIntcPrdHiLoadDemo (
    void
)
{
    CSL_TmrObj TmrObj;
    CSL_Status status;
    CSL_TmrHwSetup hwSetup = CSL_TMR_HWSETUP_DEFAULTS;
    CSL_IntcEventHandlerRecord EventRecord;
    CSL_IntcParam vectId;

    Uint32 LoadValue = 100;
    
    CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_ENABLE;

    /* Clear local data structures */
    memset(&TmrObj, 0, sizeof(CSL_TmrObj));
    printf("\n\n\n\n\nRunning Gp Timer Interrupt DUAL UNCHAINED TIMHI....\n");
    
    /**************************************************************
    * INTC related code                           *
    **************************************************************/
     
    /* Open INTC    */
    vectId = CSL_INTC_VECTID_13;
    tmrIntcHandle = CSL_intcOpen(&tmrIntcObj, CSL_INTC_EVENTID_TINTHI0, &vectId, 
                                 NULL);
   
    /* Bind ISR to Interrupt */
    EventRecord.handler = (CSL_IntcEventHandler)&TimerInterruptHandler;
    EventRecord.arg = (void *)tmrIntcHandle;
    CSL_intcPlugEventHandler(tmrIntcHandle, &EventRecord);
  
    /* Event Enable */
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);
       
    /**************************************************************/
  
    /* Initialize timer CSL module */
    CSL_tmrInit(NULL);
    hTmr =  CSL_tmrOpen(&TmrObj, IntcInstance, NULL, &status);
    CSL_tmrHwSetup(hTmr, &hwSetup);

    /* Stop the Timer */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMHI, NULL);
     
    /* set the timer mode to unchained dual mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_DUAL_UNCHAINED;

    CSL_tmrHwSetup(hTmr, &hwSetup);
    
    /* Load the period register */
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_PRDHI, (void *)&LoadValue);

    /* Start the timer with one shot*/
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_TIMHI, (void *)&TimeCountMode);
     
    /* INTC related code */   
    while (1) {
        if (intrCnt == 1)
            break;
    }
      
    /**************************************************************/
    
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTDISABLE, NULL);
    
    printf("INTR: The Total number of Events occured are: 0x%d\n", intrCnt);   
    
    intrCnt = 0;
  
    /* Stop the Timer */
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET_TIMHI, NULL);
    printf("Example for TIM34 completed\n");

    /* Close the Tmr instance */
    CSL_tmrClose(hTmr);
    CSL_intcClose(tmrIntcHandle);   
}

/*
 * =============================================================================
 *   @func  tmrIntcChainedDemo
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is example to verify the setting of timer in dual 32 bit chained
 *      and one shot mode with INTC.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void tmrIntcChainedDemo (
    void
)
{
    CSL_TmrObj TmrObj;
    CSL_Status status;
    CSL_IntcEventHandlerRecord EventRecord;
    CSL_IntcParam vectId;
    
    Uint32 LoadValue = 100;
    Uint32 LoadValue1 = 0;
    Uint8 preScalValue = 0;
    
    CSL_TmrHwSetup hwSetup = CSL_TMR_HWSETUP_DEFAULTS;

    /* set the timer in to one shot mode */
    CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_ENABLE;   

    /* Clear local data structures */
    memset(&TmrObj, 0, sizeof(CSL_TmrObj));
    printf("\n\n\n\n\nRunning Gp Timer Interrupt DUAL CHAINED....\n");
    
    /**************************************************************
    * INTC related code                               *
    **************************************************************/

    /* Open INTC */
    vectId = CSL_INTC_VECTID_12;
    tmrIntcHandle = CSL_intcOpen(&tmrIntcObj, CSL_INTC_EVENTID_TINTLO0, \
                                                  &vectId, NULL);
       
    /* Bind ISR to Interrupt */
    EventRecord.handler = (CSL_IntcEventHandler)&TimerInterruptHandler;
    EventRecord.arg = (void *)tmrIntcHandle;
    CSL_intcPlugEventHandler(tmrIntcHandle, &EventRecord);
    
    /* Event Enable */
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);
     
    /**************************************************************/

    /* Initialize timer CSL module */
    CSL_tmrInit(NULL);

    hTmr =  CSL_tmrOpen(&TmrObj, IntcInstance, NULL, &status);

    CSL_tmrHwSetup(hTmr, &hwSetup);
       
    /* Reset the Timer */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET64, NULL);

    /* set the timer mode to dual chained mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_DUAL_CHAINED;
 
    CSL_tmrHwSetup(hTmr, &hwSetup);     
 
    /* Load the prescale value */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_PSCHI, (void *)&preScalValue);

    /* Load the period register */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_PRDLO, (void *)&LoadValue);
                               
    /* Load the period register */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_PRDHI, (void *)&LoadValue1);
    
    /* Start the timer with one shot*/
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START64, (void *)&TimeCountMode);
    
    /**************************************************************
    * INTC related code                           *
    **************************************************************/
    while (1) {
        if (intrCnt == 1)
            break;
    }
    /**************************************************************/
    
  
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTDISABLE, NULL);
    
    printf("INTR: The Total number of Events occured are: 0x%d\n", intrCnt);
 
    intrCnt = 0;
    
    /* Stop the Timer */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET64, NULL);
    
    printf("Example for timer chained mode completed\n");

    /* Close the Tmr instance */
    CSL_tmrClose(hTmr);
    CSL_intcClose(tmrIntcHandle);   
}

/*
 * =============================================================================
 *   @func  tmrIntcGptDemo
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This is example to verify the setting of timer in GPT mode with INTC.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void tmrIntcGptDemo (
    void
)
{
    CSL_TmrObj TmrObj;
    CSL_IntcEventHandlerRecord EventRecord, EventRecord1;
    CSL_IntcParam vectId;
    CSL_Status status;
    
    CSL_TmrHwSetup hwSetup = CSL_TMR_HWSETUP_DEFAULTS;

    /* set the timer in to one shot mode */
    CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_ENABLE;

    /* set the timer mode to GPT mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_GPT;

    /* load the PRDLO */
    hwSetup.tmrTimerPeriodLo = 0x0f;

    /* load the PRDHI */
    hwSetup.tmrTimerPeriodHi = 0x00;

    /* Clear local data structures */
    memset(&TmrObj, 0, sizeof(CSL_TmrObj));
    printf("\n\n\n\nRunning Gp Timer with INTC....\n");
    
    /**************************************************************
    * INTC related code                               *
    **************************************************************/
  
    /* Open INTC */
    vectId = CSL_INTC_VECTID_12;
    tmrIntcHandle = CSL_intcOpen(&tmrIntcObj, CSL_INTC_EVENTID_TINTLO0,\
                                                &vectId, NULL);
    
    vectId = CSL_INTC_VECTID_13;
    tmrIntcHandle1 = CSL_intcOpen(&tmrIntcObj1, CSL_INTC_EVENTID_TINTHI0,\
                                                &vectId, NULL);
       
    /* Bind ISR to Interrupt */
    EventRecord.handler = (CSL_IntcEventHandler)&TimerInterruptHandler;
    EventRecord.arg = (void *)tmrIntcHandle;
    CSL_intcPlugEventHandler(tmrIntcHandle, &EventRecord);
    
    EventRecord1.handler = (CSL_IntcEventHandler)&TimerInterruptHandler;
    EventRecord1.arg = (void *)tmrIntcHandle1;
    CSL_intcPlugEventHandler(tmrIntcHandle1, &EventRecord1);
    
    /* Event Enable */
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);
    CSL_intcHwControl(tmrIntcHandle1, CSL_INTC_CMD_EVTENABLE, NULL);

    /**************************************************************/

    /* Initialize timer CSL module */
    CSL_tmrInit(NULL);

    hTmr = CSL_tmrOpen(&TmrObj, IntcInstance, NULL, &status); 

    CSL_tmrHwSetup(hTmr, &hwSetup);
        
    /* Reset the Timer */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET64, NULL);
    
    /* Start the timer with one shot*/
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START64, (void *)&TimeCountMode);
    
    /**************************************************************
    * INTC related code                           *
    **************************************************************/
    while (1) {
        if (intrCnt == 1)
            break;
    }
    /**************************************************************/
    
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTDISABLE, NULL);

    CSL_intcHwControl(tmrIntcHandle1, CSL_INTC_CMD_EVTDISABLE, NULL);

    printf("INTR: The Total number of Events occured are: 0x%d\n", intrCnt);
  
    intrCnt = 0;
        
    /* Stop the Timer */
    CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET64, NULL);
    
    printf("Example for 64-bit timer mode completed\n");

    /* Close the Tmr instance */
    CSL_tmrClose(hTmr);
    CSL_intcClose(tmrIntcHandle);   
}

/*
 * =============================================================================
 *   @func  tmrWdtModeDemo
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This demonstrates the Setting of timer to watchdog mode with INTC.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void tmrWdtModeDemo (
    void
)
{
    CSL_TmrObj TmrObj;
    CSL_Status status;
    CSL_IntcParam vectId;
    CSL_IntcEventHandlerRecord EventRecord;
    Uint16 loadVal;
    CSL_TmrHwSetup hwSetup = CSL_TMR_HWSETUP_DEFAULTS;
    
    /* set the timer in to countinuos mode and it is must for watchdog mode */
    CSL_TmrEnamode TimeCountMode = CSL_TMR_ENAMODE_CONT;

    CSL_IntcEventId eventId = CSL_INTC_EVENTID_TINTLO0;

    

    /* set the timer mode to WATCHDOG mode */
    hwSetup.tmrTimerMode = CSL_TMR_TIMMODE_WDT;
    hwSetup.tmrPulseWidthLo = CSL_TMR_PWID_THREECLKS;
    hwSetup.tmrClksrcLo = CSL_TMR_CLKSRC_INTERNAL;
    hwSetup.tmrClockPulseLo = CSL_TMR_CP_PULSE;
    hwSetup.tmrClockPulseHi = CSL_TMR_CP_PULSE; 
    hwSetup.tmrIpGateLo = CSL_TMR_CLOCK_INP_NOGATE;
    
    
    /* load the PRDLO */
    hwSetup.tmrTimerPeriodLo = 0x100;

    /* load the PRDHI */
    hwSetup.tmrTimerPeriodHi = 0x0;

    /* Clear local data structures */
    memset(&TmrObj, 0, sizeof(CSL_TmrObj));
    printf("\n\n\n\n Running the GP timer in watchdog mode with INTC......\n");

    /**************************************************************
    * INTC related code                           *
    **************************************************************/
    
    /* Open INTC */
    vectId = CSL_INTC_VECTID_12;
    
    if (IntcInstance == 1)
        eventId = eventId + 2;

    tmrIntcHandle = CSL_intcOpen(&tmrIntcObj, eventId, &vectId, NULL);
       
    /* Bind ISR to Interrupt */
    EventRecord.handler = (CSL_IntcEventHandler)&TimerInterruptHandler;
    EventRecord.arg = (void *)tmrIntcHandle;
    CSL_intcPlugEventHandler(tmrIntcHandle, &EventRecord);
    
    /* Event Enable */
    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);
     
    /**************************************************************/

    /* Initialize timer CSL module */
    status = CSL_tmrInit(NULL);

    hTmr =  CSL_tmrOpen(&TmrObj, IntcInstance, NULL, &status);

    CSL_tmrHwSetup(hTmr, &hwSetup);

    /* Reset the Timer */
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_RESET64, NULL);

    /* Start the timer in continuous mode*/
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_START_WDT, \
                               (void *)&TimeCountMode);
                               
    /* Watchdog timer service key1 */
    loadVal = CSL_TMR_WDTCR_WDKEY_CMD1;
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_WDKEY, \
                               (Uint16 *) &loadVal);
    
    /* Watchdog timer service key2 */
    loadVal = CSL_TMR_WDTCR_WDKEY_CMD2;
    status = CSL_tmrHwControl(hTmr, CSL_TMR_CMD_LOAD_WDKEY, \
                               (Uint16 *)&loadVal);

    /**************************************************************
    * INTC related code                                           *
    **************************************************************/
    while (1) {
        if (intrCnt == 1)
            break;
    }
      
    /**************************************************************/

    CSL_intcHwControl(tmrIntcHandle, CSL_INTC_CMD_EVTDISABLE, NULL);
    
    printf("INTR: The Total number of Events occured are: 0x%d\n", intrCnt);
  
    intrCnt = 0;
    printf("Example for Watch dog mode completed\n");

    /* Close the Tmr instance */
    status = CSL_tmrClose(hTmr);
    CSL_intcClose(tmrIntcHandle);
}

