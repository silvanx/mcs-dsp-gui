/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspIoWrite.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspIoWrite()
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
 *   @n@b CSL_mcbspIoWrite
 *
 *   @b Description
 *   @n Sends the data using MCBSP pin which is configured as general purpose 
 *      output.The 16-bit data transmitted is specified by 'outputData' argument.
 *      MCBSP pin to use in this write operation is identified by the second
 *      argument.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            outputSel       MCBSP pin to be used as general purpose output
            
            outputData      1 bit output data to be transmitted
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None                    
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspIoWrite() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *       
 *   @b Modifies
 *   @n MCBSP registers
 *
 *   @b Example
 *   @verbatim
            Uint16              outData;
            CSL_Status          status;
            CSL_McbspHandle     hMcbsp;
            ...
            // MCBSP object defined and HwSetup structure defined and initialized
            ...
     
            // Init, Open, HwSetup successfully done in that order
            ...
            outData = 1;
            CSL_mcbspIoWrite(hMcbsp, CSL_MCBSP_IO_CLKX, outData);
            ...

     @endverbatim
 * =============================================================================
 */
 
#pragma CODE_SECTION (CSL_mcbspIoWrite, ".text:csl_section:mcbsp");
void  CSL_mcbspIoWrite (
    CSL_McbspHandle     hMcbsp,
    CSL_BitMask16       outputSel,
    Uint16              outputData
)
{

    Uint16          bit_val;
    Uint16          _pcrval;

    _pcrval = hMcbsp->regs->PCR;

    if(outputSel & CSL_MCBSP_IO_CLKX) {
        bit_val = !(!(outputData & CSL_MCBSP_IO_CLKX));
        CSL_FINS( _pcrval, MCBSP_PCR_CLKXP, bit_val);
    }

    if(outputSel & CSL_MCBSP_IO_FSX) {
        bit_val = !(!(outputData & CSL_MCBSP_IO_FSX));
        CSL_FINS( _pcrval, MCBSP_PCR_FSXP, bit_val);
    }

    if(outputSel & CSL_MCBSP_IO_DX) {
        bit_val = !(!(outputData & CSL_MCBSP_IO_DX));
        CSL_FINS( _pcrval, MCBSP_PCR_DXSTAT, bit_val);
    }


    if(outputSel & CSL_MCBSP_IO_CLKR) {
        bit_val = !(!(outputData & CSL_MCBSP_IO_CLKR));
        CSL_FINS( _pcrval, MCBSP_PCR_CLKRP, bit_val);
    }

    if(outputSel & CSL_MCBSP_IO_FSR) {
        bit_val = !(!(outputData & CSL_MCBSP_IO_FSR));
        CSL_FINS( _pcrval, MCBSP_PCR_FSRP, bit_val );
    }
    
    hMcbsp->regs->PCR = _pcrval;
}

