/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspIoRead.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspIoRead()
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

/** ============================================================================
 *   @n@b CSL_mcbspIoRead
 *
 *   @b Description
 *   @n Reads the data from MCBSP pin which is configured as general purpose 
 *      input.The 16-bit data read from this pin is returned by this API. MCBSP
 *      pin to use in this read operation is identified by the second argument.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            inputSel        MCBSP pin to be used as general purpose input
     @endverbatim
 *
 *   <b> Return Value </b>  Uint16
 *   @li                    Data read from the pin                    
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspIoRead() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *       
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            Uint16              inData;
            Uint16              clkx_data;
            Uint16              clkr_data;
            CSL_Status          status;
            CSL_BitMask16       inMask;
            CSL_McbspHandle     hMcbsp;
            ...
            // MCBSP object defined and HwSetup structure defined and initialized
            ...
            
            // Init, Open, HwSetup successfully done in that order
            ...
            inMask = CSL_MCBSP_IO_CLKX | CSL_MCBSP_IO_CLKR;
            inData = CSL_mcbspIoRead(hMcbsp, inMask);
            if ((inData & CSL_MCBSP_IO_CLKX) != 0) clkx_data = 1;
            else 
                clkx_data = 0;
            if ((inData & CSL_MCBSP_IO_CLKR) != 0) clkr_data = 1;
            else 
                clkr_data = 0;
            ...

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspIoRead, ".text:csl_section:mcbsp");
Uint16  CSL_mcbspIoRead (
    CSL_McbspHandle     hMcbsp,
    CSL_BitMask16       inputSel
)
{
    Uint16      ret_value = 0;

    if(inputSel & CSL_MCBSP_IO_CLKX) {
        if( CSL_FEXT( hMcbsp->regs->PCR, MCBSP_PCR_CLKXP))
            ret_value |= CSL_MCBSP_IO_CLKX;
    }

    if(inputSel & CSL_MCBSP_IO_FSX) {
        if( CSL_FEXT( hMcbsp->regs->PCR, MCBSP_PCR_FSXP))
            ret_value |= CSL_MCBSP_IO_FSX;
    }

    if(inputSel & CSL_MCBSP_IO_CLKR) {
        if( CSL_FEXT( hMcbsp->regs->PCR, MCBSP_PCR_CLKRP))
            ret_value |= CSL_MCBSP_IO_CLKR;
    }

    if(inputSel & CSL_MCBSP_IO_FSR) {
        if( CSL_FEXT( hMcbsp->regs->PCR, MCBSP_PCR_FSRP))
            ret_value |= CSL_MCBSP_IO_FSR;
    }

    if(inputSel & CSL_MCBSP_IO_DR) {
        if( CSL_FEXT( hMcbsp->regs->PCR, MCBSP_PCR_DRSTAT))
            ret_value |= CSL_MCBSP_IO_DR;
    }

    if(inputSel & CSL_MCBSP_IO_CLKS) {
        if( CSL_FEXT( hMcbsp->regs->PCR, MCBSP_PCR_CLKSSTAT))
            ret_value |= CSL_MCBSP_IO_CLKS;
    }

    return( ret_value );
}
