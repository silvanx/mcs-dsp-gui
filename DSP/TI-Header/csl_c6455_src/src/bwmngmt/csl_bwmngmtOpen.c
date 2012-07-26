/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * priovided
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_bwmngmtOpen.c
 *
 *   @path  $(CSLPATH)\src\bwmngmt
 *
 *   @desc  File for functional layer of CSL API CSL_bwmngmtOpen()
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  03-Jun-2004 Chad Courtney File Created
 *  11-Apr-2005 Brn Updated the file for doxygen compatibiliy
 *  16-Nov-2005 ds  Updated the documentation
 *  31-Jan-2006 ds  Supported to use the CSL_bwmngmtGetBaseAddress() API
 * =============================================================================
 */
 
#include <csl_bwmngmt.h>

/** ===========================================================================
 *   @n@b CSL_bwmngmtOpen
 *
 *   @b Description
 *        This function populates the peripheral data object for the instance
 *        and returns a handle to the BWMNGMT instance.
 *        The open call sets up the data structures for the particular instance
 *        of BWMNGMT device. The device can be re-opened anytime after it has
 *        been normally closed, if so required.The handle returned by this call 
 *        is input as an essential argument for rest of the APIs described for 
 *        this module.
 *
 *   @b Arguments
 *   @verbatim
  
        pBwmngmtObj       Pointer to the BWMNGMT instance object

        bwmngmtNum        Instance of the BWMNGMT to be opened.

        pBwmngmtParam     Pointer to module specific parameters

        pStatus           pointer for returning status of the function call

     @endverbatim
 *
 *   <b> Return Value </b> CSL_BwmngmtHandle
 *       Valid BWMNGMT instance handle will be returned if status value is
 *       equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *   @n  The BWMNGMT module must be successfully initialized via 
 *       CSL_bwmngmtInit() before calling this function. 
 *
 *   <b> Post Condition </b>
 *   @n  1. The status is returned in the status variable. If status returned is 
 *          CSL_SOK - Valid BWMNGMT handle is returned. 
 *          CSL_ESYS_FAIL - The BWMNGMT instance is invalid. 
            CSL_ESYS_INVPARAMS - The Obj structure passed is invalid
 *       2. BWMNGMT object structure is populated.
 *
 *
 *   @b  Modifies
 *   @n  1. The status variable 
 *       2. BWMNGMT object structure 
 *
 *   @b Example
 *   @verbatim
         CSL_status            status;
         CSL_BwmngmtObj        bwmngmtObj;
         CSL_BwmngmtHandle     hBwmngmt;
  
         hBwmngmt = CSL_bwmngmtOpen (&bwmngmtObj,
                                    CSL_BWMNGMT,
                                    NULL,
                                    &status
                                    );
   @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_bwmngmtOpen, ".text:csl_section:bwmngmt");
CSL_BwmngmtHandle CSL_bwmngmtOpen (
    CSL_BwmngmtObj    *pBwmngmtObj,
    CSL_InstNum       bwmngmtNum,
    CSL_BwmngmtParam  *pBwmmngmtParam,
    CSL_Status        *pStatus
)
{
    CSL_BwmngmtHandle        hBwmngmt = (CSL_BwmngmtHandle)NULL;
    CSL_BwmngmtBaseAddress   baseAddress;
    
    if (pStatus == NULL) {
        /* do nothing : already the module is initialized to NULL */
    }
    
    else if (pBwmngmtObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }

    else {
        *pStatus = CSL_bwmngmtGetBaseAddress(bwmngmtNum, pBwmmngmtParam, &baseAddress);

        if (*pStatus == CSL_SOK) {
            pBwmngmtObj->regs = baseAddress.regs;
            pBwmngmtObj->bwmngmtNum = (CSL_InstNum)bwmngmtNum;
            hBwmngmt = (CSL_BwmngmtHandle)pBwmngmtObj;
        }
        else {
            pBwmngmtObj->regs = (CSL_BwmngmtRegsOvly)NULL;
            pBwmngmtObj->bwmngmtNum = (CSL_InstNum)-1;
        }
    }
    return (hBwmngmt);   
}
