/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                             
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_memprotHwSetup.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotHwSetup ()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 *
 *  16-Nov-2005  ds  Updated the documentation
 * =============================================================================
 */

#include <csl_memprot.h>
#include <csl_memprotAux.h>

/** ============================================================================
 *   @n@b CSL_memprotHwSetup
 *
 *   @b Description
 *   @n This function initializes the module registers with the appropriate
 *      values provided through the HwSetup Data structure.
 *      For information passed through the HwSetup Data structure refer
 *      @a CSL_memprotHwSetup.
 *
 *   @b Arguments
 *   @verbatim
            hMemprot      Handle to the memprot instance

            setup         Pointer to harware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Hardware structure is not
                                                  properly initialized                
 *
 *   <b> Pre Condition </b>
 *  Both @a CSL_memprotInit() and @a CSL_memprotOpen() must be called
 *  successfully in that order before this function can be called. The user
 *  has to allocate space for & fill in the main setup structure appropriately
 *  before calling this function. Ensure numpages is not set to > 32 for handles
 *  for L1D/L1P. Ensure numpages is not > 64 for L2.
 *
 *   <b> Post Condition </b>
 *   @n   1.    MEMPROT object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid MEMPORT handle is returned
 *   @li            CSL_ESYS_INVPARAMS  Invalid parameter
 *   @li            CSL_ESYS_BADHANDLE  Invalid Handle
 *
 *   @b Modifies
 *   @n The hardware registers of MEMPORT.
 *
 *   @b Example
 *   @verbatim
        #define PAGE_ATTR 0xFFF0
        
        CSL_MemprotObj mpL2Obj;
        CSL_MemprotHandle hmpL2;
        CSL_Status status;
        CSL_MemprotHwSetup L2MpSetup;
        Uint16 pageAttrTable[10] = {PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,
                PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR};
        Uint32 key[2] = {0x11223344,0x55667788};
        // Initializing the module
        CSL_memprotInit(NULL);
        
        // Opening the Handle for the L2
        hmpL2 = CSL_memprotOpen(&mpL2Obj, CSL_MEMPROT_L2, NULL, &status);
        L2MpSetup. memPageAttr = pageAttrTable;
        L2MpSetup.numPages = 10;
        L2MpSetup.key = key;
        
        // Do Setup for the L2 Memory protection/
        CSL_memprotHwSetup  (hmpL2, &L2MpSetup);
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_memprotHwSetup, ".text:csl_section:memprot");
CSL_Status CSL_memprotHwSetup (
    /* Handle to the memprot instance */
    CSL_MemprotHandle  hMemprot,
    
    /* Pointer to setup structure which contains the
     * information to program the memory protection module to a useful state.
     */
    CSL_MemprotHwSetup *setup
)
{
    CSL_Status status = CSL_SOK;
    Uint16 i;

    if (hMemprot == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }                
    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* Unlock the module. This call anyways checks if the module
           is already locked/not */
        if (setup->key != NULL) {
            CSL_memprotUnLock(hMemprot,setup->key);
        }                           
        /* Program memory page attribute registers */ 
        for (i = 0;i  < setup->numPages ;i++) {
            hMemprot->regs->MPPA[i] = setup->memPageAttr[i];
        }            
        /* Lock Module */
        if (setup->key != NULL) {
            status = CSL_memprotLock(hMemprot,setup->key);
        }
    }
    return status;
}

