/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * ============================================================================
*/
/** ============================================================================
 *   @file  csl_memprotGetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_memprotGetBaseAddress
 *
 *   Note: This function is open for re-implementing if the user wants to modify
 *    the base address of the peripheral object to point to a different location
 *    there by allow CSL initiated write/reads into peripheral MMR's go to an 
 *    alternate location. Please refer documentation for more details. 
 *      
 *   @author Ruchika Kharwar.
 */
/* =============================================================================
 *  Revision History
 *  ================  
 *  22-sep-2005 PSK updated according to code review comments.
 *  09-Aug-2006 NG  Added condition to check the invalid parameter
 * =============================================================================
 */
#include <soc.h>
#include <csl_memprot.h>

/** ===========================================================================
 *   @n@b CSL_memprotGetBaseAddress
 *
 *   @b Description
 *   @n  This function gets the base address of the given memprot
 *       instance.
 *
 *   @b Arguments
 *   @verbatim
            memprotNum        Module instance number 

            pMemprotParam     Module specific parameters

            pBaseAddress      Pointer to base address structure containing base
                              address details
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li					CSL_OK             Successful on getting the base 
 *                                             address of memprot
 *   @li					CSL_ESYS_FAIL      memprot instance is not
 *                                             available.
 *   @li                    CSL_ESYS_INVPARAMS Invalid Parameters
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Base address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure is modified.
 * 
 * @b Example:
 * @verbatim

      CSL_Status status;
      CSL_MemprotBaseAddress   baseAddress;

       ...
      status = CSL_memprotGetBaseAddress(CSL_MEMPROT_L2, NULL, &baseAddress);
   @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_memprotGetBaseAddress, ".text:csl_section:memprot");
CSL_Status CSL_memprotGetBaseAddress (
    CSL_InstNum               memprotNum,
    CSL_MemprotParam          *pMemprotParam,
    CSL_MemprotBaseAddress    *pBaseAddress 
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (memprotNum) {
            case CSL_MEMPROT_L2:
                pBaseAddress->regs = (CSL_MemprotRegsOvly)CSL_MEMPROT_L2_REGS;
                break;

            case CSL_MEMPROT_L1D:
                pBaseAddress->regs = (CSL_MemprotRegsOvly)CSL_MEMPROT_L1D_REGS;
                break;

            case CSL_MEMPROT_L1P:
                pBaseAddress->regs = (CSL_MemprotRegsOvly)CSL_MEMPROT_L1P_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_MemprotRegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

