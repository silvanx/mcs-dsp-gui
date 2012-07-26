/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/*  ============================================================================
 *   @file  _csl_mcbspBlockAssign.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API _CSL_mcbspBlockAssign()
 *
 */

/* =============================================================================
 * Revision History
 * ================
 *  June 29,2004 Pratheesh Gangadhar - Created
 * 
 * =============================================================================
 */
 
#include <csl_mcbsp.h>
#include <_csl_mcbsp.h>

/*  ============================================================================
 *   @n@b _CSL_mcbspBlockAssign
 *
 *   @b Description
 *   @n The funtion is used to assign block to a particular partition
 *      This is an Internal function and is used by the CSL_mcbspHwControl
 *      function
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to MCBSP Obj used

            partition       Partition to which the block is to be assigned

            block           Identifies the block
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK            - Successful completion
 *   @li                   CSL_ESYS_FAIL      - Operation could not the done
 *   @li                   CSL_ESYS_BADHANDLE - Invalid Handle 
 *                                            
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before _CSL_mcbspBlockAssign() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  Assign block to a specified partition
 *       
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle     hMcbsp;
            ...
            CSL_mcbspBlockAssign(hMcbsp, CSL_MCBSP_PARTITION_ATX, \
                                 CSL_MCBSP_BLOCK0);
            ...                    
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_mcbspBlockAssign, ".text:csl_section:mcbsp");
CSL_Status  _CSL_mcbspBlockAssign (
    CSL_McbspHandle         hMcbsp,
    CSL_McbspPartition      partition,
    CSL_McbspBlock          block
)
{
    CSL_Status  status = CSL_SOK;

    if (partition & 0x01) {
        if ((CSL_FEXT(hMcbsp->regs->MCR, MCBSP_MCR_RMCME) == 0) 
            && (CSL_FEXT(hMcbsp->regs->MCR, MCBSP_MCR_RMCM) == 1)) {
            if ((block & 0x01) && partition == 3) {
               /* Odd blocks can be assinged to only partition B */
               CSL_FINS( hMcbsp->regs->MCR, MCBSP_MCR_RPBBLK, block );
            }
            else {
                if ((!(block & 0x01)) && partition == 1) {
                   /* Even blocks can be assinged to only partition A */
                   CSL_FINS( hMcbsp->regs->MCR, MCBSP_MCR_RPABLK, block );
                }
                else 
                    status = CSL_EMCBSP_INVPARAMS;
           }
        }
        else 
            status = CSL_EMCBSP_INVMODE;
    }
    else {
        if ((CSL_FEXT(hMcbsp->regs->MCR, MCBSP_MCR_XMCME) == 0) 
            && (CSL_FEXT(hMcbsp->regs->MCR, MCBSP_MCR_XMCM) != 0)) {
            if ((block & 0x01) && partition == 2) {
                /* Odd blocks can be assinged to only partition B */
                CSL_FINS( hMcbsp->regs->MCR, MCBSP_MCR_XPBBLK, block );
            }
            else {
                if ((!(block & 0x01)) && partition == 0) {
                    /* Even blocks can be assinged to only partition A */
                    CSL_FINS( hMcbsp->regs->MCR, MCBSP_MCR_XPABLK, block );
                 }
                 else 
                     status = CSL_EMCBSP_INVPARAMS;
            }
        }
        else 
            status = CSL_EMCBSP_INVMODE;
    }

    return (status);

}


