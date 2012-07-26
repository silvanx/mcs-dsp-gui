/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/**
 *  @file  csl_intcInit.c
 *
 *  @brief    File for functional layer of CSL API CSL_intcInit()
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
#include <_csl_intc.h>
#include <csl_intcAux.h>

/** ============================================================================
 *   @n@b CSL_intcInit
 *
 *   @b Description
 *   @n This is the initialization function for the INTC. This function is
 *      idempotent in that calling it many times is same as calling it once.
 *      This function initializes the CSL data structures, and doesn't affect
 *      the H/W.
 *
 *   @b Arguments
 *   @verbatim
              pContext     Pointer to module-context structure
             
    @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  This function should be called before using any of the CSL INTC APIs. 
 *       The context should be initialized such that numEvtEntries is equal to 
 *       the number of records capable of being held in the eventhandlerRecord
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
    CSL_IntcContext context; 
    CSL_Status intStat;
    CSL_IntcParam vectId;
    CSL_IntcEventHandlerRecord recordTable[10];
    
    context.numEvtEntries = 10;
    context.eventhandlerRecord = &recordTable;

    // Init Module
   ...
   if (CSL_intcInit(&context) != CSL_SOK) {
       exit;
   }
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcInit, ".text:csl_section:intc");
CSL_Status CSL_intcInit (
    CSL_IntcContext   *pContext
)
{
    Uint16       i;
    
    asm(" dint");
    
    if (pContext != NULL) {
        _CSL_intcEventOffsetMap =  pContext->offsetResv;
        _CSL_intcAllocMask = pContext->eventAllocMask;
        _CSL_intcNumEvents =  pContext->numEvtEntries;
        
        for (i = 0; i < ((CSL_INTC_EVENTID_CNT + 31) / 32); i++)
            _CSL_intcAllocMask[i] = 0;
                 
        for (i = 0; i < CSL_INTC_EVENTID_CNT ; i++)
            _CSL_intcEventOffsetMap[i] = CSL_INTC_MAPPED_NONE;
        if (pContext->eventhandlerRecord != NULL) {
            _CSL_intcEventHandlerRecord  = pContext->eventhandlerRecord;            
            for (i = 0; i < _CSL_intcNumEvents; i++) 
                _CSL_intcEventHandlerRecord[i].handler = CSL_INTC_EVTHANDLER_NONE;
        }       
    } 
    _CSL_intcIvpSet();
    _CSL_intcCpuIntrTable.nmiIsr  = _CSL_intcNmiDummy;
    _CSL_intcCpuIntrTable.isr4  = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr5  = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr6  = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr7  = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr8  = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr9  = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr10 = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr11 = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr12 = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr13 = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr14 = _CSL_intcDispatcher;
    _CSL_intcCpuIntrTable.isr15 = _CSL_intcDispatcher;
    
    asm(" rint");
    
    return CSL_SOK;
}

