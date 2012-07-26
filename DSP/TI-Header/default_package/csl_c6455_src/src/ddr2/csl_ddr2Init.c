/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2Init.c
 *  
 *  @path    $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2Init()
 *           - The @a CSL_ddr2Init() function definition & it's associated 
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
 *   @n@b   CSL_ddr2Init
 *
 *  @b Description
 *  @n This function is idempotent i.e. calling it many times is same as calling
 *     it once.  This function presently does nothing.
 *
 * <b> Usage Constraints: </b>
 *  This function should be called before using any of the CSL APIs
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
 * @verbatim
   ...
   
   CSL_ddr2Init( NULL );
   ...    
   }
   @endverbatim
 *
 *
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2Init, ".text:csl_section:ddr2");
CSL_Status  CSL_ddr2Init (
   CSL_Ddr2Context    *pContext
)
{
    return CSL_SOK;
}

