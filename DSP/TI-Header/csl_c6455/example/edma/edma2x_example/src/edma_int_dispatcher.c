/*  =====================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *   =====================================================================
 */

/** =====================================================================
 *   @file  edma_int_desp.c
 *
 *   @path $(CSLPATH)\example\edma\src
 *
 *   @desc  This file has routines to handle the EDMA interrupts.
 *
 * ======================================================================
 */

/* ======================================================================
 *  Revision History
 *  ================
 *  01-Aug-2005    Chandra    File created.
 *  11-Aug-2005    Chandra    Minor format changes.
 * ======================================================================
 */
#include <csl_edma2.h>
#include <edma_int_dispatcher.h>

/* Global Edma Tcc handler table */
#pragma DATA_SECTION(TccHandlerTable,".exampleMem");
static void (*TccHandlerTable[EDMA_CHA_CNT]) () = { 0 };

/**
 * ======================================================================
 *   @func   eventEdmaHandler
 *
 *   @desc
 *     This calls all the handlers of the TCC interrupts.
 *
 *   @n <b> Procedure </b>
 *   @verbatim
       For each TCC
        1. Check if the interrupt is pending for that TCC
           if pending
        2. Call the corresponding handler
        3. Clear the interrupt

     @endverbatim
 * ======================================================================
 */
void eventEdmaHandler (
    void *handle
)
{
    Uint32 tcc, status;
    for (tcc = 0; tcc < EDMA_CHA_CNT; tcc++) {
        status = EDMA_intTest (tcc);
        if (status) {
            TccHandlerTable[tcc] (tcc);
            EDMA_intClear (tcc);
        }
    }
}

/**
 * ======================================================================
 *   @func   edmaEventHook
 *
 *   @desc
 *     Hooks an interrupt for a given TCC number.
 *
 *   @n <b> Procedure </b>
 *   @verbatim
        1. Copies the address of given ISR into the given entry of
           the TCC handler table.

     @endverbatim
 * ======================================================================
 */
void edmaEventHook (
    Int tcc,
    void fxn ()
)
{
    TccHandlerTable[tcc] = fxn;
}





