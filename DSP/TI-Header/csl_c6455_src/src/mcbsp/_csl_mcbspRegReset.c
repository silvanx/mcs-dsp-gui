/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/*  ============================================================================
 *   @file  _csl_mcbspRegReset.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API _CSL_mcbspRegReset()
 *
 */

/*  ============================================================================
 * Revision History
 * ================
 *  July 04, 2005 ds      - Register Naming convention used for 
 *                          Multichannel registers are changed according 
 *                          the changes in cslr_mcbsp.h
 *  ============================================================================
 */

#include <csl_mcbsp.h>
#include <_csl_mcbsp.h>

/*  ============================================================================
 *   @n@b _CSL_mcbspRegReset
 *
 *   @b Description
 *   @n Function to reset all the registers values
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
     @endverbatim
 *
 *   <b> Return Value </b> 
 *   @n  None
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before _CSL_mcbspRegReset() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  Reset all the registers values
 *       
 *   @b Modifies
 *   @n MCBSP registers
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle     hMcbsp;
            hMcbsp = CSL_mcbspOpen(hMcbsp, CSL_MCBSP_1,NULL, &status );
            _CSL_mcbspRegReset(hMcbsp);
            ...                    
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (_CSL_mcbspRegReset, ".text:csl_section:mcbsp");
void  _CSL_mcbspRegReset (
    CSL_McbspHandle     hMcbsp
)
{
    CSL_McbspRegsOvly mcbspRegs = hMcbsp->regs; 
    
    mcbspRegs->DXR =  CSL_MCBSP_DXR_RESETVAL;

    mcbspRegs->SPCR = CSL_MCBSP_SPCR_RESETVAL;
    
    mcbspRegs->RCR = CSL_MCBSP_RCR_RESETVAL;
    
    mcbspRegs->XCR = CSL_MCBSP_XCR_RESETVAL;
    
    mcbspRegs->SRGR = CSL_MCBSP_SRGR_RESETVAL;
    
    mcbspRegs->MCR = CSL_MCBSP_MCR_RESETVAL;
   
    mcbspRegs->PCR = CSL_MCBSP_PCR_RESETVAL; 
    
    mcbspRegs->XCERE0 = CSL_MCBSP_XCERE0_RESETVAL;
    mcbspRegs->XCERE1 = CSL_MCBSP_XCERE1_RESETVAL;
    mcbspRegs->XCERE2 = CSL_MCBSP_XCERE2_RESETVAL;
    mcbspRegs->XCERE3 = CSL_MCBSP_XCERE3_RESETVAL;
    
    mcbspRegs->RCERE0 = CSL_MCBSP_RCERE0_RESETVAL;
    mcbspRegs->RCERE1 = CSL_MCBSP_RCERE1_RESETVAL;
    mcbspRegs->RCERE2 = CSL_MCBSP_RCERE2_RESETVAL;
    mcbspRegs->RCERE3 = CSL_MCBSP_RCERE3_RESETVAL;    
}
