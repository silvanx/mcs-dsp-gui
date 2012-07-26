/*  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */
/** ============================================================================
 *   @file  csl_ddr2GetBaseAddress.c
 *
 *   @path  $(CSLPATH)\src\common
 *
 *   @desc  CSL Implementation of CSL_ddr2GetBaseAddress
 *
 */
/*  ============================================================================
 *  Revision History
 *  ===============
 *  12-April-2005 Ramitha Mathew File Created.
 *  25-Jan-2006   SD             Modified the code section start address
 *  09-Aug-2006   NG             Added condition to check the invalid parameter
 *  ============================================================================
 */
#include <soc.h>
#include <csl_ddr2.h>

/** ============================================================================
 *   @n@b CSL_ddr2GetBaseAddress
 *
 * @b Description
 * @n The get base address call will give the External memory interface current 
 *    current instance base address
 *
 *   @b Arguments
 *   @verbatim      
            ddr2Num         Specifies the instance of the DDR2 external memory
                            interface for which the base address is requested
 
            pDdr2Param      Module specific parameters.
 
            pBaseAddress    Pointer to the base address structure to return the
                            base address details.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_OK              Successful on getting the base 
 *                                              address of ddr2
 *   @li                    CSL_ESYS_FAIL       The external memory interface 
 *                                              instance is not available.
 *   @li                    CSL_ESYS_INVPARAMS  Invalid parameter 
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_ddr2Init() and CSL_ddr2Open () must be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n  Base address structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *
 *         2. Base address structure.
 *
 *   @b Example
 *   @verbatim
        CSL_Status          status;
        CSL_Ddr2BaseAddress  baseAddress;

       ...
       status = CSL_ddr2GetBaseAddress(CSL_DDR2, NULL, &baseAddress);

    @endverbatim
 *  @return Returns the status of the get base address operation
 *
 * ============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2GetBaseAddress, ".text:csl_section:ddr2");
CSL_Status
    CSL_ddr2GetBaseAddress (
        CSL_InstNum              ddr2Num,
        CSL_Ddr2Param            *pDdr2Param,
        CSL_Ddr2BaseAddress      *pBaseAddress
)
{
    CSL_Status status = CSL_SOK;

    if (pBaseAddress == NULL) {
        status = CSL_ESYS_INVPARAMS;
	}
    else {
        switch (ddr2Num) {
            case CSL_DDR2:
                pBaseAddress->regs = (CSL_Ddr2RegsOvly)CSL_DDR2_0_REGS;
                break;

            default:
                pBaseAddress->regs = (CSL_Ddr2RegsOvly)NULL;
                status = CSL_ESYS_FAIL;
                break;
        }
    }
    return (status);
}

