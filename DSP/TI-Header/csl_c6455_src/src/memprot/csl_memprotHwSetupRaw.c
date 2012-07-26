/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_memprotHwSetupRaw.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotHwSetupRaw ()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 *
 * =============================================================================
 */
 
#include <csl_memprot.h>

/** @brief Configures the Memory protection using the register-values passed in
 *  through the config structure. For this module this API is a dummy.
 */
#pragma CODE_SECTION (CSL_memprotHwSetupRaw, ".text:csl_section:memprot");
CSL_Status CSL_memprotHwSetupRaw (
    /* Pointer to the object that holds reference to the
     * instance of memory protection unit.
     */
    CSL_MemprotHandle hMemprot,
    
    /* Pointer to setup structure which contains the
     * information to program the memory protection unit to a useful state
     */
    CSL_MemprotConfig *config
)
{
    return CSL_SOK;
}

