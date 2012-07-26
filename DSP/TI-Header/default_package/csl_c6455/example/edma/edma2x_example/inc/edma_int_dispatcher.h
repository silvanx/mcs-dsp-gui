/*  =====================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *   =====================================================================
 */

/** =====================================================================
 *   @file  edma_int_desp.h
 *
 *   @path $(CSLPATH)\example\edma\inc
 *
 *   @desc  This is part of an example of CSL 2.x usage of EDMA.  A header
 *          file to support the EDMA interrupt handlers.
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

#ifndef _EDMA_INT_DESP_H_
#define _EDMA_INT_DESP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
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
        If pending
        2. Call the corresponding handler
        3. Clear the interrupt

     @endverbatim
 * ======================================================================
 */
void eventEdmaHandler (
    void    *handle
);

/*
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
    Int     tcc, 
    void    fxn ()
);


#ifdef __cplusplus
}
#endif

#endif /*_EDMA_INT_DESP_H_*/
