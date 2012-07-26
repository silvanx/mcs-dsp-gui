/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *  ============================================================================
 */

/**
 *  @file  csl_intcHookIsr.c
 *
 *  @brief    File for functional layer of CSL API CSL_intcHookIsr()
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

/** ============================================================================
 *  @n@b CSL_intcHookIsr
 *
 *  @b Description
 *  @n Hook up an exception handler
 *     This API hooks up the handler to the specified exception.
 *     Note: In this case, it is done by inserting a B(ranch) instruction
 *     to the handler. Because of the restriction in the instruction
 *     the handler must be within 32MB of the exception vector.
 *     Also, the function assumes that the exception vector table is
 *     located at its default ("low") address.
 *
 *  @b Arguments
 *  @verbatim
        vectId       Interrupt Vector identifier
        
        isrAddr      Pointer to the handler
    @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @n                     CSL_SOK - CSL_intcHookIsr Successful 
 *                          
 *   @b Example:
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intStat;
            CSL_IntcParam               vectId;
            CSL_IntcObj                 intcObj20;
            CSL_IntcHandle              hIntc20;
            CSL_IntcDropStatus          drop;
            CSL_IntcEventHandlerRecord  recordTable[10];
            CSL_IntcGlobalEnableState   state;
            Uint32                      intrStat;
            
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK)
               exit;
            // Opening a handle for the Event 20 at vector id 4
            
            vectId = CSL_INTC_VECTID_4;
            hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , 
                                    NULL);
            
            CSL_intcNmiEnable();
            // Enable Global Interrupts 
            intStat = CSL_intcGlobalEnable(&state);
            
            // Hook Isr appropriately
            CSL_intcHookIsr(CSL_INTC_VECTID_4,&isrVect4);
                ...
            }
            interrupt void isrVect4() {
            
            }
    @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_intcHookIsr, ".text:csl_section:intc");
CSL_Status  CSL_intcHookIsr (
    CSL_IntcVectId        evtId,
    void                  *isrAddr
)
{
    Uint32      *dispPtr;
    
    dispPtr = (Uint32*)(&_CSL_intcCpuIntrTable);
    dispPtr[evtId + 1] = (Uint32)(isrAddr);
    
    return(CSL_SOK);
}
