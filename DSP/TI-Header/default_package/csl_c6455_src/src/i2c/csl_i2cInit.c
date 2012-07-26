/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cInit.c
 *
 *  @brief File for functional layer of CSL API @a CSL_i2cInit()
 *
 *  @path $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The @a CSL_i2cInit() function definition & it's associated functions
 *
 *  Modification 1
 *    - Modified on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  31-aug-2004 Hs Updated the function and documentation for CSL_i2cInit.
 *  11-oct-2004 Hs updated code according to code review comments.
 * =============================================================================
 */
#include <csl_i2c.h>

/** ============================================================================
 *   @n@b CSL_i2cInit
 *
 *   @b Description
 *   @n This is the initialization function for the I2C. This function is
 *      idempotent in that calling it many times is same as calling it once.
 *      This function initializes the CSL data structures, and doesn't affect
 *      the H/W.
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
       CSL_Status status;
       ...
       status = CSL_i2cInit();
       ...
     @endverbatim
 *  ===========================================================================
 */
#pragma CODE_SECTION (CSL_i2cInit, ".text:csl_section:i2c");
CSL_Status  CSL_i2cInit (
    CSL_I2cContext    *pContext
)
{
    /* Added according to review comment 1. */
    pContext = pContext; /* To remove compiler warning/remarks */
    return CSL_SOK;
}

