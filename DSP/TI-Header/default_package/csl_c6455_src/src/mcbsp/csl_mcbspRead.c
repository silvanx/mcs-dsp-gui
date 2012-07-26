/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspRead.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspRead()
 *
 */

/* =============================================================================
 * Revision History
 * ================
 *  Jun 29, 2004 Pratheesh Gangadhar - Created
 *  Mar 23, 2006 ds Added check for invalid handle 
 * =============================================================================
 */

#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspRead
 *
 *   @b Description
 *   @n Reads the data from MCBSP. The word length for the read operation is
 *      specefied using @a wordLen argument. According to this word length, 
 *      appropriate amount of data will read in the data object (variable);
 *      the pointer to which is passed as the third argument.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            wordLen         Word length of data to be read in
            
            data            Pointer to data object (variable) that will hold
                            the read data
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Read data successful
 *   @li                    CSL_EMCBSP_INVSIZE  - Invalid Word length
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspRead() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *       
 *   @b Modifies
 *   @n MCBSP registers
 *
 *   @b Example
 *   @verbatim
            Uint16     inData;
            CSL_Status status;
            CSL_McbspHandle hMcbsp;
            ...
            // MCBSP object defined and HwSetup structure defined and initialized
            ...
            
            // Init, Open, HwSetup successfully done in that order
            ...
            // MCBSP SRG, Frame sync, RCV taken out of reset in that order
            ...
            status = CSL_mcbspRead(hMcbsp, CSL_MCBSP_WORDLEN_16, &inData);
            ...

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspRead, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspRead (
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
    }else {
        switch(wordLen) {
            case CSL_MCBSP_WORDLEN_8:
            case CSL_MCBSP_WORDLEN_12:
            case CSL_MCBSP_WORDLEN_16: {
                *((Uint16 *)data) = (Uint16)hMcbsp->regs->DRR;
                break;
            }
            case CSL_MCBSP_WORDLEN_20:
            case CSL_MCBSP_WORDLEN_24:
            case CSL_MCBSP_WORDLEN_32: {
                *((Uint32 *)data) = (Uint32)hMcbsp->regs->DRR;
                break;
            }
            default:
                status = CSL_EMCBSP_INVSIZE;
        }
    }
    return(status);
}
