/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 


/** ============================================================================
 *   @file  csl_memprotGetHwSetup.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotGetHwSetup ()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 *  16-Nov-2005  ds              Updated the documentation
 * =============================================================================
 */
 
#include <csl_memprot.h>

/** ============================================================================
 *   @n@b CSL_memprotGetHwSetup
 *
 *   @b Description
 *   @n This function gets the current setup of the Memory Protection registers.
 *      The status is returned through @a CSL_MemprotHwSetup. The obtaining of
 *      status is the reverse operation of @a CSL_MemprotHwSetup() function.
 *      Only the Memory Page attributes are read and filled into the HwSetup
 *      structure
 *
 *   @b Arguments
 *   @verbatim

            hMemprot        Handle to the MEMPROT instance

            setup           Pointer to setup structure which contains the
                            setup information of MEMPROT.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Setup info load successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Usage Constraints: </b>
 *  Both @a CSL_memprotInit(), @a CSL_memprotOpen() and @a CSL_memprotHwSetup()
 *  must be called successfully in that order before @a CSL_memprotGetHwSetup()
 *  can be called. Ensure numpages is initialized depending on the number of
 *  desired attributes in the setup.Make sure to set numpages <= 32 for handles
 *  for L1D/L1P. Ensure numpages <= 64 for L2.
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified MEMPROT instance will be setup.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified MEMPROT instance.
 *
 *   @b Example
 *   @verbatim
        #define PAGE_ATTR 0xFFF0
        
        CSL_MemprotObj mpL2Obj;
        CSL_MemprotHandle hmpL2;
        CSL_Status status;
        CSL_MemprotHwSetup L2MpSetup,L2MpGetSetup;
        Uint16 pageAttrTable[10] = {PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,
                 PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR};
        Uint32 key[2] = {0x11223344,0x55667788};

        // Initializing the module
        CSL_memprotInit(NULL);

        // Opening the Handle for the L2
        hmpL2 = CSL_memprotOpen(&mpL2Obj,CSL_MEMPROT_L2,NULL,&status);
        L2MpSetup. memPageAttr = pageAttrTable;
        L2MpSetup.numPages = 10;
        L2MpSetup.key = key;

        // Do Setup for the L2 Memory protection/
        CSL_memprotHwSetup  (hmpL2,&L2MpSetup);
        CSL_memprotGetHwSetup(hmpL2,&L2MpGetSetup);

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_memprotGetHwSetup, ".text:csl_section:memprot")
CSL_Status CSL_memprotGetHwSetup (
    CSL_MemprotHandle   hMemprot,
    CSL_MemprotHwSetup  *setup
)
{
    CSL_Status  status = CSL_SOK;
    Uint16  i;
    
    if (hMemprot == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    
    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        for (i = 0; i < setup->numPages; i++) {
            setup->memPageAttr[i] = hMemprot->regs->MPPA[i];
        }    
    }        
    return (status);
}

