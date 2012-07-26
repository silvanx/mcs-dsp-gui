/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/*  ============================================================================
 *   @file  _csl_mcbspResetCtrl.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API _CSL_mcbspResetCtrl()
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
 *   @n@b _CSL_mcbspResetCtrl
 *
 *   @b Description
 *   @n Enable/Disable Frame Sync Logic/Sample Rate Generator and Receiver and
 *      Transmitter Operation
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            selectMask      Selects enable/disable of receiverCfg/transmitter.
                            Bitwise OR of MCBSP_CTRL_XXXX
     @endverbatim
 *
 *   <b> Return Value </b> 
 *   @n  None
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before _CSL_mcbspResetCtrl() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  Sets/Resets Frame Sync Logic/Sample Rate Generator and Receiver and
 *       Transmitter Operation
 *       
 *   @b Modifies
 *   @n MCBSP registers
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle hMcbsp;
            ...
            hMcbsp = CSL_mcbspOpen(hMcbsp, CSL_MCBSP_1,NULL, &status );
            ...
            _CSL_mcbspResetCtrl( hMcbsp, CSL_MCBSP_CTRL_SRG_ENABLE
                                |CSL_MCBSP_CTRL_FSYNC_DISABLE
                                |CSL_MCBSP_CTRL_RX_ENABLE
                                |CSL_MCBSP_CTRL_TX_ENABLE );
            ...                    
     @endverbatim
 * =============================================================================
 */
 
#pragma CODE_SECTION (_CSL_mcbspResetCtrl, ".text:csl_section:mcbsp");
void  _CSL_mcbspResetCtrl (
    CSL_McbspHandle     hMcbsp,
    CSL_BitMask16       selectMask
)
{
    CSL_McbspRegsOvly mcbspRegs = hMcbsp->regs;

    if(selectMask & CSL_MCBSP_CTRL_FSYNC_ENABLE)
        CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_FRST, 1);
    
    if(selectMask & CSL_MCBSP_CTRL_SRG_ENABLE)
        CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_GRST, 1);
    
    if(selectMask & CSL_MCBSP_CTRL_FSYNC_DISABLE)
        CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_FRST, 0);
    
    if(selectMask & CSL_MCBSP_CTRL_SRG_DISABLE)
        CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_GRST, 0);
    
    if(selectMask & CSL_MCBSP_CTRL_RX_ENABLE)
        CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_RRST, 1);
    
    if(selectMask & CSL_MCBSP_CTRL_TX_ENABLE)
        CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_XRST, 1);
    
    if(selectMask & CSL_MCBSP_CTRL_RX_DISABLE)
        CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_RRST, 0);
    
    if(selectMask & CSL_MCBSP_CTRL_TX_DISABLE)
        CSL_FINS(mcbspRegs->SPCR, MCBSP_SPCR_XRST, 0);

}

