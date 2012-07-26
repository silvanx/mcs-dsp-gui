/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/**
 *  @file  csl_intcHwControl.c
 *
 *  @brief File for functional layer of CSL API CSL_intcHwControl()
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
 *   @n@b CSL_intcHwControl
 *
 *   @b Description
 *   @n Perform a control-operation. This API is used to invoke any of the
 *      supported control-operations supported by the module.
 *
 *   @b Arguments
 *   @verbatim
            hIntc           Handle identifying the event

            command         The command to this API indicates the action to be
                            taken on INTC.
    
            commandArg      An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - HwControl successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVCMD     - Invalid command
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcOpen() must be invoked before this call.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of INTC.
 *
 *   @b Example
 *   @verbatim
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
    
    CSL_intcHwControl(hIntc20,CSL_INTC_CMD_EVTENABLE,NULL);
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcHwControl, ".text:csl_section:intc");
CSL_Status  CSL_intcHwControl(
    CSL_IntcHandle            hIntc,
    CSL_IntcHwControlCmd      controlCommand,
    void*                     commandArg
)

{
    CSL_Status status = CSL_SOK;
    
    if (hIntc == NULL)
        status = CSL_ESYS_BADHANDLE;
        
    switch(controlCommand) {
        case CSL_INTC_CMD_EVTENABLE: 
            if (hIntc->vectId < CSL_INTC_VECTID_EXCEP) {
                if (hIntc->vectId < CSL_INTC_VECTID_COMBINE) {
                    if (hIntc->eventId < 4) {
                        if (commandArg)
                            CSL_intcCombinedEventEnable(hIntc->eventId,\
                                                  *(CSL_BitMask32*)commandArg);
                    }
                    CSL_intcInterruptEnable(hIntc->vectId);             
                    CSL_intcEventDisable(hIntc->eventId);                   
                }       
                else 
                    CSL_intcEventEnable(hIntc->eventId);                    
            } 
            else          
                CSL_intcExcepEnable(hIntc->eventId);
            break;
        
        case CSL_INTC_CMD_EVTDISABLE:
            if (hIntc->vectId < CSL_INTC_VECTID_EXCEP) {
                if (hIntc->vectId < CSL_INTC_VECTID_COMBINE) {
                    if (hIntc->eventId < 4) {
                        if (commandArg)
                            CSL_intcCombinedEventDisable(hIntc->eventId, \
                                                  *(CSL_BitMask32*)commandArg);
                    }
                    CSL_intcInterruptDisable(hIntc->vectId);                
                }       
                else 
                    CSL_intcEventDisable(hIntc->eventId);
            }
            else          
                CSL_intcExcepDisable(hIntc->eventId);
            break;
            
        case CSL_INTC_CMD_EVTSET:
            CSL_intcEventSet(hIntc->eventId);               
            break;
                
        case CSL_INTC_CMD_EVTCLEAR:  
            if (hIntc->vectId < CSL_INTC_VECTID_EXCEP) {
                if (hIntc->eventId < 4) {
                    if (commandArg)
                        CSL_intcCombinedEventClear(hIntc->eventId, \
                                                  *(CSL_BitMask32*)commandArg);
                } 
                else                    
                    CSL_intcEventClear(hIntc->eventId);
            } 
            else          
                CSL_intcExcepClear(hIntc->eventId);

            break;
        
        case CSL_INTC_CMD_EVTDROPENABLE:  
            if (hIntc->vectId < CSL_INTC_VECTID_COMBINE)
                CSL_intcInterruptDropEnable(1 << hIntc->vectId); 
            else 
                status = CSL_ESYS_INVCMD;
            break;
        
        case CSL_INTC_CMD_EVTDROPDISABLE:   
            if (hIntc->vectId < CSL_INTC_VECTID_COMBINE)
                CSL_intcInterruptDropDisable(1 << hIntc->vectId); 
            else 
                status = CSL_ESYS_INVCMD;   
            break;
        case CSL_INTC_CMD_EVTINVOKEFUNCTION:    
            CSL_intcInvokeEventHandle (hIntc->eventId);
            break;
        default:
            status = CSL_ESYS_INVCMD;
            break;

    }
    return status;
}
