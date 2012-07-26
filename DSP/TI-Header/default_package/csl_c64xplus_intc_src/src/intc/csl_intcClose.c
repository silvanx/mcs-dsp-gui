/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/**
 *  @file  csl_intcClose.c
 *
 *  @brief   File for functional layer of CSL API CSL_intcClose()
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
 *   @n@b CSL_intcClose
 *
 *   @b Description
 *   @n This intc Handle can no longer be used to access the event. The event is 
 *      de-allocated and further access to the event resources are possible only
 *      after opening the event object again. 
 *
 *   @b Arguments
 *   @verbatim
            hIntc            Handle identifying the event
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_INTC_BADHANDLE  - The handle passed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_intcInit() and CSL_intcOpen() have to be called in that 
 *       order successfully before calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  The intc CSL APIs can not be called until the intc CSL is reopened 
 *       again using CSL_intcOpen() 
 *
 *   @b Modifies
 *   @n  None
 *            
 *   @b Example
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intStat;
            CSL_IntcParam               vectId;
            CSL_IntcObj                 intcObj20;
            CSL_IntcHandle              hIntc20;
            CSL_IntcEventHandlerRecord  recordTable[10];
            
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK) {
               exit;
            // Opening a handle for the Event 20 at vector id 4
            
            vectId = CSL_INTC_VECTID_4;
            hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId, \
                                    NULL);
            
            // Close handle
            CSL_IntcClose(hIntc20);    
   
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcClose, ".text:csl_section:intc");
CSL_Status  CSL_intcClose (
    CSL_IntcHandle      hIntc
)
{
    
    CSL_Status  closeStatus = CSL_ESYS_BADHANDLE;
    Uint32      evt;
    Uint32      x;
    Uint32      y;
    
    if (hIntc != (CSL_IntcHandle) CSL_INTC_BADHANDLE) {
        evt = (Uint32)(hIntc->eventId);
        y = evt >> 5;
        x = 1 << (evt & 0x1f);
        
        asm(" dint");
        _CSL_intcAllocMask[y] &= ~x; /* clear bit -> unused */
        if (_CSL_intcEventOffsetMap[hIntc->eventId] != CSL_INTC_MAPPED_NONE) {
            _CSL_intcEventHandlerRecord
            [_CSL_intcEventOffsetMap[hIntc->eventId]].handler = 
                                                       CSL_INTC_EVTHANDLER_NONE;
            _CSL_intcEventOffsetMap[hIntc->eventId] = CSL_INTC_MAPPED_NONE;
        }   
        hIntc = (CSL_IntcHandle) CSL_INTC_BADHANDLE;
        asm(" rint");
        
        closeStatus = CSL_SOK;      
    }
    
    return closeStatus;
}
