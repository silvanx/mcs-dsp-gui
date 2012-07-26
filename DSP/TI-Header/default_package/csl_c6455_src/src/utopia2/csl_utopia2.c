/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *  @file    csl_utopia2.c
 *
 *  @path    $(CSLPATH)\src\utopia2
 *
 *  @desc    This file contains the functions which are required to reset the 
 *           UTOPIA2.
 */
#include "csl_utopia2.h"

/******************************************************************************\
*                         L O C A L   S E C T I O N
\******************************************************************************/

/* static macro declarations */

/* static typedef declarations */

/* static function declarations */

/* static variable definitions */

/* static function definitions */

/******************************************************************************\
*                        G L O B A L   S E C T I O N
\******************************************************************************/

/* global variable definitions */
CSL_Utopia2Regs *utopia2Regs = (CSL_Utopia2Regs *) CSL_UTOPIA2_0_REGS;

/* global function definitions */

/** ============================================================================
 *   @n@b UTOPIA2_reset
 *
 *   @b Description
 *   @n This function resets UTOPIA2 Control Register and sets the Clock Detect
 *      Register.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n UTOPIA2 registers 
 *
 *   @b Example
 *   @verbatim
        ...
        UTOPIA2_reset()
        ...

     @endverbatim
 * =============================================================================
 */
void 
UTOPIA2_reset (
    void
)
{
    Uint32 cs;
    
    cs = _disable_interrupts();
    
    utopia2Regs->UCR = UTOPIA2_UCR_DEFAULT;
    utopia2Regs->CDR = UTOPIA2_CDR_DEFAULT;
    _restore_interrupts(cs);
}

/* End of csl_utopia2.c */

