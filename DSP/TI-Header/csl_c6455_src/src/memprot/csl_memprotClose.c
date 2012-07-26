/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_memprotClose.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotClose ()
 *
 */

/* =============================================================================
 *  Revision History
 * ===============
 *  01-Feb-2006 ds  Added error checking
 * =============================================================================
 */

#include <csl_memprot.h>

/** ===========================================================================
 *   @n@b CSL_memprotClose
 *
 *   @b Description
 *   @n This function closes the specified instance of MEMPROT.
 *
 *   @b Arguments
 *   @verbatim
            hMem            Handle to the MEMPROT instance
     @endverbatim
 *    
 *   <b> Usage Constraints: </b>
 *   CSL_memprotInit(), CSL_memprotOpen() must be opened prior to this call.
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Close successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   @b Example
 *   @verbatim
            CSL_MemprotHandle   hMem;
            CSL_status          status;

            ...   
            status = CSL_memprotClose(hMem);
     @endverbatim
 * ============================================================================
 */ 
#pragma CODE_SECTION (CSL_memprotClose, ".text:csl_section:memprot");
CSL_Status CSL_memprotClose (
    CSL_MemprotHandle   hMemprot
)
{
    /* Indicate in the CSL global data structure that the peripheral
     * has been unreserved   
     */
    CSL_Status  status = CSL_SOK;
    
    if (hMemprot != NULL) {
        hMemprot->regs        = (CSL_MemprotRegsOvly) NULL;
        hMemprot->modNum      = (CSL_InstNum) - 1;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }  
    return status;
}
