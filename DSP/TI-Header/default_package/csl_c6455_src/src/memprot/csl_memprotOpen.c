/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_memprotOpen.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotOpen ()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  16-Nov-2005 ds  updated the documentation
 * =============================================================================
 */
 
#include <csl_memprot.h>
/** ===========================================================================
 *   @n@b CSL_memprotOpen
 *
 *   @b Description
 *   @n This function populates the peripheral data object for the instance
 *      and returns a handle to the instance.
 *      The open call sets up the data structures for the particular instance
 *      of MEMPROT device.The device can be re-opened anytime after it has been
 *      normally closed, if so required. The handle returned by this call is 
 *      input as an essential argument for rest of the APIs described 
 *      for this module.
 *
 *   @b Arguments
 *   @verbatim 
              pMemprotObj     Pointer to the MEMPROT instance object
              
              memprotNum      Instance of the MEMPROT to be opened
              
              pMemprotParam   Pointer to module specific parameters
              
              pStatus         pointer for returning status of the function call
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_MemprotHandle
 *   @n                     Valid MEMPROT instance handle will be returned if 
                            status value is equal to CSL_SOK.
 *
 *   <b> Pre Condition </b>
 *  Memory protection must be successfully initialized via @a CSL_memprotInit()
 *  before calling this function. Memory for the @a CSL_MemprotObj must be
 *  allocated outside this call. This object must be retained while usage of
 *  this module.Depending on the module opened some inherant constraints need
 *  to be kept in mind. When a handle for the Config block is opened the only
 *  operation  possible is a query for the fault Status. No other control
 *  command/ query/ setup must be used.
 *  When a handle for L1D/L1P is opened then too constraints wrt the number of
 *  Memory pages must be kept in mind.
 *
 *   <b> Post Condition </b>
 *   @n   1.    MEMPROT object structure is populated
 *   @n   2.    The status is returned in the status variable. If status
 *              returned is
 *   @li            CSL_SOK             Valid MEMPORT handle is returned
 *   @li            CSL_ESYS_FAIL       The MEMPORT instance is invalid
 *   @li            CSL_ESYS_INVPARAMS  Invalid parameter
 *
 *   @b Modifies
 *   @n    1. The status variable
 *   @n    2. MEMPROT object structure
 *
 *   @b Example
 *  @verbatim

            CSL_MemprotObj mpL2Obj;
            CSL_MemprotHandle hmpL2;
            CSL_Status status;
            // Initializing the module 
            CSL_memprotInit(NULL);
            
            // Opening the Handle for the L2 
            hmpL2 = CSL_memprotOpen(&mpL2Obj,
                                   CSL_MEMPROT_L2,
                                   NULL,
                                   &status);
   @endverbatim
 * ============================================================================
 */  

#pragma CODE_SECTION (CSL_memprotOpen, ".text:csl_section:memprot");
CSL_MemprotHandle CSL_memprotOpen (
    CSL_MemprotObj   *pMemprotObj,   
    CSL_InstNum      memprotNum,     
    CSL_MemprotParam *pMemprotParam, 
    CSL_Status       *pStatus
)
{
    CSL_MemprotHandle       hMemprot = (CSL_MemprotHandle)NULL;
    CSL_MemprotBaseAddress  baseAddress;
    
    if (pStatus == NULL) {
        /* do nothing : already the module is initialized to NULL */        
    }
    
    else if (pMemprotObj == NULL) {
        *pStatus = CSL_ESYS_INVPARAMS;
    }

    else {
        *pStatus = CSL_memprotGetBaseAddress(memprotNum, pMemprotParam, &baseAddress); 

        if (*pStatus == CSL_SOK) {
            pMemprotObj->regs = baseAddress.regs;
            pMemprotObj->modNum = (CSL_InstNum)memprotNum;
            hMemprot = (CSL_MemprotHandle)pMemprotObj;
        } 
        else {
            pMemprotObj->regs = (CSL_MemprotRegsOvly)NULL;
            pMemprotObj->modNum = (CSL_InstNum)-1;
        }
    }
    return (hMemprot);
}

