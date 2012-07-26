/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/**
 *  @file  csl_intcOpen.c
 *
 *  @brief    File for functional layer of CSL API CSL_intcOpen()
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
 *   @n@b CSL_intcOpen
 *
 *   @b Description
 *   @n The API would reserve an interrupt-event for use. It returns
 *      a valid handle to the event only if the event is not currently
 *      allocated. The user could release the event after use by calling
 *      CSL_intcClose(..)
 *
 *   @b Arguments
 *   @verbatim
              pIntcObj     Pointer to the CSL-object allocated by the user

              eventId      The event-id of the interrupt

              param        Pointer to the Intc specific parameter
              
              pStatus      Pointer for returning status of the function call
                           
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_IntcHandle
 *   @n                     Valid INTC handle identifying the event
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   1.    INTC object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid intc handle is returned
 *   @li            CSL_ESYS_FAIL       The open command failed
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. INTC object structure
 *
 * @b Example:
 * @verbatim

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
    
    // Close handle
    CSL_IntcClose(hIntc20);
   @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcOpen, ".text:csl_section:intc");
CSL_IntcHandle  CSL_intcOpen (
    CSL_IntcObj          *intcObj,
    CSL_IntcEventId      eventId,
    CSL_IntcParam        *param,
    CSL_Status           *status
)
{
    CSL_IntcHandle  hIntc = (CSL_IntcHandle)CSL_INTC_BADHANDLE;
    CSL_Status      openStatus;
    Uint32          evtId;      
    Uint32          _yCo;
    Uint32          _xCo;
    
    evtId = (Uint32)(eventId);
    _yCo = evtId >> 5;          /* _yCo co-ordinate */
    _xCo = 1 << (evtId & 0x1f); /* _xCo co-ordinate */
    
    asm(" dint");
    if (!(_CSL_intcAllocMask[_yCo] & _xCo)) {
        _CSL_intcAllocMask[_yCo] |= _xCo; /* set bit -> used */
        hIntc = intcObj;
    }
    asm(" rint");
    
    if (hIntc != (CSL_IntcHandle)CSL_INTC_BADHANDLE) {
        intcObj->eventId    = eventId;
        intcObj->vectId     = *((CSL_IntcVectId*)param);
        openStatus          = CSL_SOK;
        
        /* Do the Mapping for the Event -> CPU Interrupt */
        if (*((CSL_IntcVectId*)param) < ((Uint32)(CSL_INTC_VECTID_COMBINE))) {
            CSL_intcMapEventVector(eventId,*param); 
            if (eventId < 4) {
                switch (eventId) {
                    case 0:
                        CSL_intcHookIsr(*((CSL_IntcVectId*)param), \
                                        _CSL_intcEvent0Dispatcher);
                        break;
                    case 1:
                        CSL_intcHookIsr(*((CSL_IntcVectId*)param), \
                                       _CSL_intcEvent1Dispatcher);
                        break;
                    case 2:
                        CSL_intcHookIsr(*((CSL_IntcVectId*)param), \
                                       _CSL_intcEvent2Dispatcher);
                        break;
                    case 3:
                        CSL_intcHookIsr(*((CSL_IntcVectId*)param), \
                                       _CSL_intcEvent3Dispatcher);
                        break;                  
                }           
            }
            
        }        
    } 
    else 
        openStatus = CSL_ESYS_FAIL;

    if (status) {
        *status = openStatus;
    }
    
    return hIntc;
}
