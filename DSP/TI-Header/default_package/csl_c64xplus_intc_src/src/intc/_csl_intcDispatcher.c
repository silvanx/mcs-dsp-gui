/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/*
 *  @file  _csl_intcDispatcher.c
 *
 *  @brief   File for functional layer of CSL API _CSL_intcDispatcherInit(..)
 *
 *  PATH  $(CSLPATH)\src\intc
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Jun-2004 Ruchika Kharwar File Created
 *  
 * =============================================================================
 */

#include <csl_intc.h>
#include <_csl_intc.h>
#include <csl_intcAux.h>

/*  ============================================================================
 *   @n@b _CSL_intcDispatcher
 *
 *   @b Description
 *   @n Get the Event Source of the Interrupt
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>
 *   @li None
 *
 *
 * @b Example:
 *   @verbatim
            ...
           _CSL_intcCpuIntrTable.isr4  = _CSL_intcDispatcher;
           ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_intcDispatcher, ".text:csl_section:intc");
interrupt void _CSL_intcDispatcher (void)
{
    Uint32  evtId;
    Uint32  intrId = (_CSL_intcCpuIntrTable.currentVectId - \
                    (Uint32)(&_CSL_intcCpuIntrTable) - 4)/4;
        
    /* Get the Event Source of the Interrupt */
    if (intrId < 8) 
        evtId = CSL_FEXTR(((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->INTMUX1, \
                            (intrId-4)*8+6,(intrId-4)*8);
    else {
        if (intrId < 12) 
            evtId = CSL_FEXTR(((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->INTMUX2, \
                                (intrId-8)*8+6,(intrId-8)*8);
        else 
            evtId = CSL_FEXTR(((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->INTMUX3, \
                                (intrId-12)*8+6,(intrId-12)*8);
    }
    
    if (_CSL_intcEventOffsetMap[evtId] != CSL_INTC_MAPPED_NONE) 
        _CSL_intcEventHandlerRecord[_CSL_intcEventOffsetMap[evtId]].handler (
            _CSL_intcEventHandlerRecord[_CSL_intcEventOffsetMap[evtId]].arg 
            );    
}
