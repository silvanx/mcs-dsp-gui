/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspWrite.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspWrite()
 *
 */

/* =============================================================================
 * Revision History
 * ================
 *  Jun 29,2004 Pratheesh Gangadhar - Created
 *  Mar 23, 2006 ds Added check for invalid handle 
 * =============================================================================
 */
 
#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspWrite
 *
 *   @b Description
 *   @n Transmits the data from MCBSP. The word length for the write operation 
 *      is specified using @a wordLen argument. According to this word length, 
 *      the appropriate amount of data will transmitted from the data object
 *      (variable); the pointer to which is passed as the third argument.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            wordLen         Word length of data to be transmitted
            
            data            Pointer to data object (variable) that holds the
                            data to be sent out
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Write data successful
 *   @li                    CSL_EMCBSP_INVSIZE  - Invalid Word length
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspWrite() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  Data is written to DXR register
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
            // MCBSP SRG, Frame sync, XMT taken out of reset in that order
            ...
            outData = 0x1234;
            status = CSL_mcbspWrite(hMcbsp, CSL_MCBSP_WORDLEN_16,&outData);
            ...

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspWrite, ".text:csl_section:mcbsp");
CSL_Status CSL_mcbspWrite (
    CSL_McbspHandle     hMcbsp,
    CSL_McbspWordLen    wordLen,
    void                *data
)
{
    CSL_Status status = CSL_SOK;
    
    if (hMcbsp == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (data == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }else{
        switch(wordLen) {
            case CSL_MCBSP_WORDLEN_8:
            case CSL_MCBSP_WORDLEN_12:
            case CSL_MCBSP_WORDLEN_16: 
                hMcbsp->regs->DXR = *((Uint16 *)data) ;
                break;
            
            case CSL_MCBSP_WORDLEN_20:
            case CSL_MCBSP_WORDLEN_24:
            case CSL_MCBSP_WORDLEN_32: 
                hMcbsp->regs->DXR = *(Uint32 *)data;
                break;
            
            default:
                status = CSL_EMCBSP_INVSIZE;
        }
    }
    return(status);
}
