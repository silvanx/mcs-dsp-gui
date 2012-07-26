/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2Open.c
 *  
 *  @path:   $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2Open()
 *           - The @a CSL_ddr2Open() function definition & it's associated 
 *             functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  10-Apr-2005 RM  File Created.
 *  
 *  05-Oct-2005 NG  Updation done according to new register layer
 *  
 * =============================================================================
 */
#include <csl_ddr2.h>

/** ============================================================================
 *   @n@b   CSL_ddr2Open
 *
 *   @b Description
 *   @n This function returns the handle to the DDR2 instance. This
 *      handle is passed to all other CSL APIs.
 *
 *   @b Arguments
 *   @verbatim

            pDdr2Obj        Pointer to the object that holds reference to the
                            instance of DDR2 requested after the call
            
            ddr2Num         Instance of DDR2 to which a handle is requested
 
            pDdr2Param      Pointer to module specific parameters
 
            pStatus         pointer for returning status of the function call

     @endverbatim
 *
 *   <b> Return Value </b>  
 *      CSL_Ddr2Handle - Valid DDR2 instance handle will be returned if status
 *    @li                value is equal to CSL_SOK.
 * 
 *   <b> Pre Condition </b>
 *   @n  @a The DDR2 must be successfully initialized via CSL_ ddr2Init() 
 *          before calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  1. The status is returned in the status variable. If status returned is 
 *          CSL_SOK - Valid DDR2 handle is returned. 
 *          CSL_ESYS_FAIL - The DDR2 instance is invalid. 
            CSL_ESYS_INVPARAMS - The Obj structure passed is invalid
 *       2. DDR2 object structure is populated.
 * 
 *   @n  None
 *
 *   @b  Modifies
 *   @n  None
 *
 *   @b Example:
 *   @verbatim
         CSL_Status         status;
         CSL_Ddr2Obj        ddr2Obj;
         CSL_Ddr2Handle     hDdr2;
 
         hDdr2 = CSL_Ddr2Open(&ddr2Obj,
                              CSL_DDR2,
                              NULL,
                              &status
                             );
     @endverbatim
 *
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2Open, ".text:csl_section:ddr2");
CSL_Ddr2Handle CSL_ddr2Open (
    CSL_Ddr2Obj      *pDdr2Obj,
    CSL_InstNum      ddr2Num,
    CSL_Ddr2Param    *pDdr2Param,
    CSL_Status       *pStatus
)
{    
    CSL_Ddr2Handle         hDdr2 = (CSL_Ddr2Handle)NULL;
    CSL_Ddr2BaseAddress    baseAddress;
    
    if (pStatus == NULL) {
        /* Do nothing : Module handle already initialised to NULL */
    }
    else if (pDdr2Obj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        *pStatus = CSL_ddr2GetBaseAddress(ddr2Num, pDdr2Param, &baseAddress);
        if (*pStatus == CSL_SOK) {
            pDdr2Obj->regs = baseAddress.regs;
            pDdr2Obj->perNum = (CSL_InstNum)ddr2Num;
            hDdr2 = (CSL_Ddr2Handle)pDdr2Obj;
        } 
        else {
            pDdr2Obj->regs = (CSL_Ddr2RegsOvly)NULL;
            pDdr2Obj->perNum = (CSL_InstNum)-1;
        }
    }
    
    return (hDdr2);
}

