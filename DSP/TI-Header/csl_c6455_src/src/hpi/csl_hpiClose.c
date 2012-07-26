/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiClose.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiClose()
 *
 */
#include <csl_hpi.h>

/** ============================================================================
 *   @n@b CSL_hpiClose
 *
 *   @b Description
 *   @n This function closes the specified instance of HPI.
 *
 *   @b Arguments
 *   @verbatim
            hHpi            Handle to the HPI

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  The HPI instance should be opened before this close operation.
 *
 *   <b> Post Condition </b>
 *   @n  The HPI CSL APIs can not be called until the HPI CSL is reopened 
 *       again using CSL_hpiOpen().
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_HpiHandle      hHpi;
            CSL_Status         status;

            ...
            
            status = CSL_hpiClose(hHpi);
     @endverbatim
 * ===========================================================================
 */ 

#pragma CODE_SECTION (CSL_hpiClose, ".text:csl_section:hpi");
CSL_Status  CSL_hpiClose (
    CSL_HpiHandle    hHpi
)
{
    CSL_Status status = CSL_SOK;
    
    if (hHpi != NULL) {
        hHpi->regs = (CSL_HpiRegsOvly)NULL;
        hHpi->hpiNum  = (CSL_InstNum)-1;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }
    return status;
}

