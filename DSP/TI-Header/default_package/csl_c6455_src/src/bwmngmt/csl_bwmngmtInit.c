/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * priovided
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_bwmngmtInit.c
 *
 *   @path  $(CSLPATH)\src\bwmngmt
 *
 *   @desc  File for functional layer of CSL API CSL_bwmngmtInit()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  03-Jun-2004 Chad Courtney File Created
 *
 *  11-Apr-2005 Brn updated the file for doxygen compatibiliy
 *
 *  16-Nov-2005 ds  updated the documentation
 * =============================================================================
 */
 

#include <csl_bwmngmt.h>

/** ============================================================================
 *   @n@b CSL_bwmngmtInit
 *
 *   @b Description
 *   @n This is the initialization function for the BWMNGMT. This function must
 *      be called before calling any other API from this CSL.This function is
 *      idem-potent. Currently, the function just returns status CSL_SOK, 
 *      without doing anything.
 *
 *   @b Arguments
     @verbatim
            pContext   Context information for the instance. Should be NULL
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Always returns
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
          ...
          CSL_bwmngmtInit();
     @endverbatim
 *  ===========================================================================
 */
#pragma CODE_SECTION (CSL_bwmngmtInit, ".text:csl_section:bwmngmt");
CSL_Status CSL_bwmngmtInit (
    CSL_BwmngmtContext *pContext
)
{
    return CSL_SOK;
}

