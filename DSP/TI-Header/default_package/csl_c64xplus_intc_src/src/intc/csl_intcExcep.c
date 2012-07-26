/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/**
 *  @file  csl_intcExcep.c
 *
 *  @brief File for functional layer of CSL Exceptions APIs
 *
 *  PATH  $(CSLPATH)\src\intc
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Jun-2004 Ruchika Kharwar File Created
 *
 *  16-Mar-2005 brn modified for doxygen documentation
 * =============================================================================
 */

#include <csl_intc.h>

/** ============================================================================
 *   @n@b CSL_intcExcepAllEnable
 *
 *   @b Description
 *   @n This enables the events as specified in the bitmask in either 
 *      EXPMASK0/1/2/3.
 *
 *   @b Arguments
 *   @verbatim
            excepMask       Exception Mask

            excVal          Event Value

            prevState       Previous state information 
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK    -  Intc Excep All Enable return successful
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcInit() must be called before use of this API.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intcStat;
            CSL_IntcParam               vectId;
            CSL_IntcEventHandlerRecord  recordTable[10];
            CSL_IntcGlobalEnableState   prevState;
            
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK) {
               exit;
            // Enable exception events 9,10,11.
            intcStat = CSL_intcExcepAllEnable(CSL_INTC_EXCEP_0TO31, 
                                              0x0F00,&prevState);
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcExcepAllEnable, ".text:csl_section:intc");
CSL_Status CSL_intcExcepAllEnable (
        CSL_IntcExcepEn     excepMask,
        CSL_BitMask32       excVal,
        CSL_BitMask32       *prevState
        
)
{
    CSL_Status stat = CSL_SOK;

    if ((prevState) && ((excepMask >= 0) && (excepMask <= 3))) { 
        *prevState = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EXPMASK[excepMask];
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EXPMASK[excepMask] &= ~excVal;
    }
    else {
        stat = CSL_ESYS_INVPARAMS;
    }
    
    return (stat);
}

/** ============================================================================
 *   @n@b CSL_intcExcepAllDisable
 *
 *   @b Description
 *   @n This disables the events as specified in the bitmask in either
 *      EXPMASK0/1/2/3.
 *
 *   @b Arguments
 *   @verbatim
            excepMask       Exception Mask

            excVal          Event Value

            prevState       Pre state information 
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK    -  Intc Excep All Disable return successful
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcInit() must be called before use of this API.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intcStat;
            CSL_IntcParam               vectId;
            CSL_IntcEventHandlerRecord  recordTable[10];
            CSL_IntcGlobalEnableState   prevState;
            
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK) {
               exit;
            // Enable exception events 9,10,11.
            intcStat = CSL_intcExcepAllDisable(CSL_INTC_EXCEP_0TO31, \
                                              0x0F00,&prevState);
    @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_intcExcepAllDisable, ".text:csl_section:intc");
CSL_Status CSL_intcExcepAllDisable (
        CSL_IntcExcepEn             excepMask,
        CSL_BitMask32               excVal,
        CSL_BitMask32               *prevState
)
{
    CSL_Status stat = CSL_SOK;
    
    if ((prevState) && ((excepMask >= 0) && (excepMask <= 3))) {
        *prevState = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EXPMASK[excepMask];
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EXPMASK[excepMask] |= excVal;
    }
    else {
        stat = CSL_ESYS_INVPARAMS;
    }
    
    return (stat);
}

/** ============================================================================
 *   @n@b CSL_intcExcepAllRestore
 *
 *   @b Description
 *   @n This restores the exception enable mask.
 *
 *   @b Arguments
 *   @verbatim
            excepMask       Exception Mask

            restoreVal      BitMask to be restored

     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK    -  Intc Excep All Restore return successful
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcInit() and CSL_intcExcepAllDisable()/CSL_intcExcepAllEnable() 
 *       must be called before use of this API
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intcStat;
            CSL_IntcParam               vectId;
            CSL_bitMask32               exp0Stat;
            CSL_IntcEventHandlerRecord  recordTable[10];
            CSL_IntcGlobalEnableState   prevState;
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK) {
               exit;
            intcStat = CSL_intcExcepAllDisable(CSL_INTC_EXCEP_0TO31,0x0F00, \
                                               &prevState);
            
            // Restore
            intcStat = CSL_intcExcepAllRestore(CSL_INTC_EXCEP_0TO31,prevState);
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcExcepAllRestore, ".text:csl_section:intc");
CSL_Status CSL_intcExcepAllRestore (
        CSL_IntcExcepEn             excepMask,
        CSL_IntcGlobalEnableState   restoreVal
)
{
    CSL_Status stat = CSL_SOK;

    if ((excepMask >= 0) && (excepMask <= 3)) {
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EXPMASK[excepMask] = restoreVal;
    }
    else {
        stat = CSL_ESYS_INVPARAMS;
    }

    return (stat);
}

/** ============================================================================
 *   @n@b CSL_intcExcepAllClear
 *
 *   @b Description
 *   @n This clears the exception flags.
 *
 *   @b Arguments
 *   @verbatim
            excepMask       Exception Mask

            excVal          Holder for the event bitmask to be cleared

     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK    -  Intc Excep All Clear return successful
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcInit() and CSL_intcExcepAllEnable() must be called before
 *       use of this API
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 *   @verbatim
            CSL_IntcContext context; 
            CSL_Status intcStat;
            CSL_IntcParam vectId;
            CSL_IntcEventHandlerRecord recordTable[10];
            CSL_IntcGlobalEnableState prevState;
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK) {
               exit;
            // Clear exception events 9,10,11.
            
            intcStat = CSL_intcExcepAllClear(CSL_INTC_EXCEP_0TO31,0x0F00);
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcExcepAllClear, ".text:csl_section:intc");
CSL_Status CSL_intcExcepAllClear (
        CSL_IntcExcepEn  excepMask,
        CSL_BitMask32    excVal
)
{
    CSL_Status stat = CSL_SOK;

    if ((excepMask >= 0) && (excepMask <= 3)) {
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[excepMask] = excVal;
    }
    else{
        stat = CSL_ESYS_INVPARAMS;
    }

    return (stat);
}

/** ============================================================================
 *   @n@b CSL_intcExcepAllStatus
 *
 *   @b Description
 *   @n This obtains the status of the exception flags
 *
 *   @b Arguments
 *   @verbatim
            excepMask       Exception Mask

            excVal          Holder for the event bitmask to be cleared

     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK    -  intc Excep All Status return successful
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcInit() must be called before use of this API
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intcStat;
            CSL_IntcParam               vectId;
            CSL_bitMask32               exp0Stat;
            CSL_IntcEventHandlerRecord  recordTable[10];
            CSL_IntcGlobalEnableState   prevState;
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK) {
               exit;
            intcStat = CSL_intcExcepAllStatus(CSL_INTC_EXCEP_0TO31,&exp0Stat);  
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcExcepAllStatus, ".text:csl_section:intc");
CSL_Status CSL_intcExcepAllStatus (
        CSL_IntcExcepEn  excepMask,
        CSL_BitMask32    *status     
)
{
    CSL_Status stat = CSL_SOK;

    if ((status) && ((excepMask >= 0) && (excepMask <= 3))) {
        *status = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEXPFLAG[excepMask] ;
    }
    else {
        stat = CSL_ESYS_INVPARAMS;
    }
    
    return (stat); 
}

