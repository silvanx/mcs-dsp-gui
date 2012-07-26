/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */
 
/**
 *  @file  csl_intcPlugEventHandler.c
 *
 *  @brief  File for functional layer of CSL API @a CSL_intcPlugEventHandler()
 *
 *  PATH  $(CSLPATH)\src\intc
 *  
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
 *  @n@b CSL_intcPlugEventHandler
 *
 *  @b Description
 *  @n Associate an event-handler with an event
 *     CSL_intcPlugEventHandler(..) ties an event-handler to an event; so
 *     that the occurence of the event, would result in the event-handler
 *     being invoked.
 *
 *  @b Arguments
 *  @verbatim
        hIntc                Intc handle identifies the interrupt-event
        
        eventHandlerRecord   Provides the details of the event-handler
    @endverbatim
 *
 *  <b> Return Value </b>   CSL_Status
 *  @li                     CSL_SOK  - Succussful completion of PlugEventHandler 
 *  @li                     CSL_ESYS_FAIL - Non completion of PlugEventHandler
 *
 * @b Example:
 *  @verbatim
    CSL_IntcObj intcObj20;
    
    CSL_IntcGlobalEnableState state;
    
    CSL_IntcContext context; 
    CSL_Status intStat;
    CSL_IntcParam vectId;
    
    context.numEvtEntries = 0;
    context.eventhandlerRecord = NULL;
    // Init Module
    CSL_intcInit(&context);
    
    // NMI Enable   
    CSL_intcGlobalNmiEnable();
    
    // Enable Global Interrupts 
    intStat = CSL_intcGlobalEnable(&state);
    
    // Opening a handle for the Event 20 at vector id 4
    
    vectId = CSL_INTC_VECTID_4;
    hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , NULL);
    
    EventRecord.handler = &event20Handler;
    EventRecord.arg = hIntc20;
    CSL_intcPlugEventHandler(hIntc20,&EventRecord); 
    // Close handle
    CSL_IntcClose(hIntc20);
    }
   
    void event20Handler( CSL_IntcHandle hIntc)
    {
  
    }
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcPlugEventHandler, ".text:csl_section:intc");
CSL_Status CSL_intcPlugEventHandler (
    CSL_IntcHandle                 hIntc,
    CSL_IntcEventHandlerRecord     *eventHandlerRecord
)
{
    volatile Uint16  i;
    CSL_Status status = CSL_ESYS_FAIL;

    asm(" dint");

    /* Search for free entry and plug in handler */
    
    for (i = 0; i < _CSL_intcNumEvents; i++) {
        if (_CSL_intcEventHandlerRecord[i].handler == CSL_INTC_EVTHANDLER_NONE){
            /* Plug in Handler */
            _CSL_intcEventHandlerRecord[i].handler =
                eventHandlerRecord->handler;
            _CSL_intcEventHandlerRecord[i].arg =
                eventHandlerRecord->arg;    
            /* Establish mapping */
            _CSL_intcEventOffsetMap[hIntc->eventId] = i;
            status = CSL_SOK;
            break;          
        }
    
    }
    asm(" rint");
    
    return status;
}
