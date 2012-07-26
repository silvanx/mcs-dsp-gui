/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/*  ============================================================================
 *   @file  _csl_mcbspClearFrmSyncErr.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API _CSL_mcbspClearFrmSyncErr()
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
 *   @n@b _CSL_mcbspClearFrmSyncErr
 *
 *   @b Description
 *   @n Clear Frame Sync Error for Receiver and Transmitter
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
            
            chanType        Selects receiver/transmitter
     @endverbatim
 *
 *   <b> Return Value </b> 
 *   @n  None
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before _CSL_mcbspClearFrmSyncErr() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *       
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle     hMcbsp;
            ...
            hMcbsp = CSL_mcbspOpen(hMcbsp, CSL_MCBSP_1,NULL, &status );
            _CSL_mcbspClearFrmSyncErr( hMcbsp, CSL_MCBSP_RX);
            ...                    
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_mcbspClearFrmSyncErr, ".text:csl_section:mcbsp");
void  _CSL_mcbspClearFrmSyncErr (
    CSL_McbspHandle     hMcbsp,
    CSL_McbspChType     chanType
)
{
    /* NOTE: The extra step of storing register value in a temporary
     *       variable is done to avoid the Codegen tool bug: SDSsq32003
     */

    /* Clear Receive Frame Sync Error */
    if( chanType == CSL_MCBSP_CHTYPE_RX ) {
        CSL_FINS( hMcbsp->regs->SPCR, MCBSP_SPCR_RSYNCERR, \
                  CSL_MCBSP_SPCR_RSYNCERR_CLEAR );
    }

    /* Clear Transmit Frame Sync Error */
    if( chanType == CSL_MCBSP_CHTYPE_TX ) {
        CSL_FINS( hMcbsp->regs->SPCR, MCBSP_SPCR_XSYNCERR, \
                  CSL_MCBSP_SPCR_XSYNCERR_CLEAR );
    }

    /* Clear Transmit & Receive Frame Sync Errors */
    if( chanType == CSL_MCBSP_CHTYPE_TXRX ) {
            CSL_FINS( hMcbsp->regs->SPCR, MCBSP_SPCR_XSYNCERR, \
                      CSL_MCBSP_SPCR_XSYNCERR_CLEAR );
            CSL_FINS( hMcbsp->regs->SPCR, MCBSP_SPCR_RSYNCERR, \
                      CSL_MCBSP_SPCR_RSYNCERR_CLEAR );

    }
}
