/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/*
 *  @file  _csl_intcCombEventDispatcher.c
 *
 *  @brief  File for functional layer of CSL API _CSL_intcEvent0Dispatcher()
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
 *   @n@b _CSL_intcEvent0Dispatcher
 *
 *   @b Description
 *   @n Get the event source of the combiner interrupt0
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
           CSL_IntcParam   *param;
           ...
           CSL_intcHookIsr(*((CSL_IntcVectId*)param),_CSL_intcEvent0Dispatcher);
           ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_intcEvent0Dispatcher, ".text:csl_section:intc");
interrupt void _CSL_intcEvent0Dispatcher (void)
{
    volatile CSL_BitMask32  evtRcv;
    Uint32                  evtId;
    Uint32                  evtMask ;
    
    evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[0];
    
    while (evtRcv) {
        /* Clear the events */
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[0] = evtRcv ;
        evtMask = 1 << 4;
        evtId = 4;
        evtRcv &= ~(0xF);
        do {
            if (evtRcv & evtMask) {
                if (_CSL_intcEventOffsetMap[evtId] != CSL_INTC_MAPPED_NONE) 
                    _CSL_intcEventHandlerRecord
                    [_CSL_intcEventOffsetMap[evtId]].handler (
                        _CSL_intcEventHandlerRecord 
                        [_CSL_intcEventOffsetMap[evtId]].arg
                   );
                evtRcv &= ~evtMask;
            }
                
            evtMask = evtMask << 1;         
            evtId++;
        } while (evtRcv);   
        
        /* Read the MEVTFLAG[0] register */
        evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[0];
    }
}

/*  ============================================================================
 *   @n@b _CSL_intcEvent1Dispatcher
 *
 *   @b Description
 *   @n Get the event source of the combiner interrupt1
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
           CSL_IntcParam   *param;
           ...
           CSL_intcHookIsr(*((CSL_IntcVectId*)param),_CSL_intcEvent1Dispatcher);
           ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_intcEvent1Dispatcher, ".text:csl_section:intc");
interrupt void _CSL_intcEvent1Dispatcher (void)
{
    volatile CSL_BitMask32  evtRcv;
    Uint32                  evtId;
    Uint32                  evtMask ;
    
    /* Read the MEVTFLAG[1] register */
    evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[1];
    while (evtRcv) {
        /* Clear the events */
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[1] = evtRcv ;
        evtId = 32;
        evtMask = 1;
        do {
            if (evtRcv & evtMask) {
                if (_CSL_intcEventOffsetMap[evtId] != CSL_INTC_MAPPED_NONE) 
                    _CSL_intcEventHandlerRecord 
                        [_CSL_intcEventOffsetMap[evtId]].handler (
                        _CSL_intcEventHandlerRecord 
                            [_CSL_intcEventOffsetMap[evtId]].arg
                    );
                evtRcv &= ~evtMask;
            }    
            evtMask = evtMask << 1;         
            evtId++;
        } while (evtRcv);   
        
        /* Read the MEVTFLAG[1] register */
        evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[1];
    }
}

/*  ============================================================================
 *   @n@b _CSL_intcEvent2Dispatcher
 *
 *   @b Description
 *   @n Get the event source of the combiner interrupt2
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
           CSL_IntcParam   *param;
           ...
           CSL_intcHookIsr(*((CSL_IntcVectId*)param),_CSL_intcEvent2Dispatcher);
           ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_intcEvent2Dispatcher, ".text:csl_section:intc");
interrupt void _CSL_intcEvent2Dispatcher (void)
{
    volatile CSL_BitMask32  evtRcv;
    Uint32                  evtId;
    Uint32                  evtMask ;
    
    /* Read the MEVTFLAG[2] register */
    evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[2];
    while (evtRcv) {
        /* Clear the events */
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[2] = evtRcv ;
        evtId = 64;
        evtMask = 1;
        do {
            if (evtRcv & evtMask) {
                if (_CSL_intcEventOffsetMap[evtId] != CSL_INTC_MAPPED_NONE) 
                    _CSL_intcEventHandlerRecord 
                        [_CSL_intcEventOffsetMap[evtId]].handler (
                        _CSL_intcEventHandlerRecord 
                            [_CSL_intcEventOffsetMap[evtId]].arg
                    );
                evtRcv &= ~evtMask;
            }    
            evtMask = evtMask << 1;         
            evtId++;
        } while (evtRcv);   
        
        /* Read the MEVTFLAG[2] register */
        evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[2];
    }
}

/*  ============================================================================
 *   @n@b _CSL_intcEvent3Dispatcher
 *
 *   @b Description
 *   @n Get the event source of the combiner interrupt3
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
           CSL_IntcParam   *param;
           ...
           CSL_intcHookIsr(*((CSL_IntcVectId*)param),_CSL_intcEvent3Dispatcher);
           ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_intcEvent3Dispatcher, ".text:csl_section:intc");
interrupt void _CSL_intcEvent3Dispatcher (void)
{
    volatile CSL_BitMask32  evtRcv;
    Uint32                  evtId;
    Uint32                  evtMask ;
    
    /* Read the MEVTFLAG[3] register */
    evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[3];
    while (evtRcv) {
        /* Clear the events */
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->EVTCLR[3] = evtRcv ;
        evtId = 96;
        evtMask = 1;
        do {
            if (evtRcv & evtMask) {
                if (_CSL_intcEventOffsetMap[evtId] != CSL_INTC_MAPPED_NONE) 
                    _CSL_intcEventHandlerRecord 
                        [_CSL_intcEventOffsetMap[evtId]].handler (
                        _CSL_intcEventHandlerRecord 
                            [_CSL_intcEventOffsetMap[evtId]].arg
                    );
                evtRcv &= ~evtMask;
            }    
            evtMask = evtMask << 1;   
            evtId++;    
        } while (evtRcv);   
        
       /* Read the MEVTFLAG[3] register */
        evtRcv = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->MEVTFLAG[3];
    }
}
