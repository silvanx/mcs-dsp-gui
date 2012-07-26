/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_emifaOpen.c
 *  
 *  @path    $(CSLPATH)\src\emifa
 *
 *  @desc    File for functional layer of CSL API @a CSL_emifaOpen()
 *           - The @a CSL_emifaOpen() function definition & it's associated 
 *             functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  10-May-2005 RM  File Created.
 *  
 *  09-Sep-2005 NG  Updation according to coding guidelines
 *  
 * =============================================================================
 */
#include <csl_emifa.h>

/** ============================================================================
 *   @n@b   CSL_emifaOpen
 *
 *   @b Description
 *   @n This function populates the peripheral data object for the EMIFA 
 *      instance and returns a handle to the instance.
 *      The open call sets up the data structures for the particular instance
 *      of EMIFA device. The device can be re-opened anytime after it has been
 *      normally closed if so required. The handle returned by this call is
 *      input as an essential argument for rest of the APIs described
 *      for this module.
 *
 *   @b Arguments
 *   @verbatim

            pEmifaObj        Pointer to the EMIFA instance object
 
            emifaNum         Instance of the EMIFA to be opened.
 
            pEmifaParam      Pointer to module specific parameters
 
            pStatus          Pointer for returning status of the function call

     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @li                 CSL_EmifaHandle - Valid EMIFA instance handle will be 
 *                                         returned if status value is equal to 
 *                                         CSL_SOK.
 * 
 *   <b> Pre Condition </b>
 *   @n  @a CSL_emifaInit() must be called successfully.
 *
 *   <b> Post Condition </b>
 *   @n  EMIFA object structure is populated
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. EMIFA object structure
  *
 *   @b Example:
 *   @verbatim
         CSL_Status           status;
         CSL_EmifaObj         emifaObj;
         CSL_EmifaHandle      hEmifa;
 
         hI2c = CSL_emifaOpen (&emifaObj,
                               CSL_EMIFA,
                               NULL,
                               &status
                              );
     @endverbatim
 *
 * ===========================================================================
 */

#pragma CODE_SECTION (CSL_emifaOpen, ".text:csl_section:emifa");
CSL_EmifaHandle CSL_emifaOpen (
    CSL_EmifaObj      *pEmifaObj,
    CSL_InstNum       emifaNum,
    CSL_EmifaParam    *pEmifaParam,
    CSL_Status        *pStatus
)
{    
    CSL_EmifaHandle       hEmifa = (CSL_EmifaHandle)NULL;
    CSL_EmifaBaseAddress  baseAddress;  
  
    if (pStatus == NULL) {
        /* Do nothing: Module handle already initialised to NULL */ 
    }
    else if (pEmifaObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }
    else {
        *pStatus = CSL_emifaGetBaseAddress(emifaNum, pEmifaParam, &baseAddress);
        if (*pStatus == CSL_SOK) {
            pEmifaObj->regs = baseAddress.regs;
            pEmifaObj->perNum = (CSL_InstNum)emifaNum;
            hEmifa = (CSL_EmifaHandle)pEmifaObj;
        } 
        else {
            pEmifaObj->regs = (CSL_EmifaRegsOvly)NULL;
            pEmifaObj->perNum = (CSL_InstNum)-1;
        }
    }

    return (hEmifa);
}

