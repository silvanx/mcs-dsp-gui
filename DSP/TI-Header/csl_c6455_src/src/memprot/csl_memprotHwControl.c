/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_memprotHwControl.c
 *
 *   @path  $(CSLPATH)\src\memprot
 *
 *   @desc  File for functional layer of CSL API CSL_memprotHwControl ()
 *
 */
 
/* =============================================================================
 * Revision History
 * ===============
 *  16-Jul-2004  Ruchika Kharwar File Created
 *
 *  16-Nov-2005 ds   Updated the documentation
 * =============================================================================
 */
 
#include <csl_memprot.h>
#include <csl_memprotAux.h>

/** ===========================================================================
 *   @n@b CSL_memprotHwControl
 *
 *   @b Description
 *   @n Control operations for the Memory protection registers.
 *      For a particular control operation, the pointer to the corresponding
 *      data type needs to be passed as argument HwControl function Call.
 *      All the arguments (Structure elements included) passed to  the
 *      HwControl function are inputs. For the list of commands supported and
 *      argument type that can be @a void* casted & passed with a particular
 *      command refer to @a CSL_MemprotHwControlCmd.
 *
 *   @b Arguments
 *   @verbatim
            hMemprot        Handle to the MEMPROT instance

            cmd             The command to this API indicates the action to be
                            taken on MEMPROT.

            arg             An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVCMD     - Invalid command
 *   @li                    CSL_ESYS_FAIL       - Invalid instance number
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_memprotInit() and @a CSL_memprotOpen() must be called
 *       successfully in that order before @a CSL_memprotHwControl() can be
 *       called. For the argument type that can be @a void* casted & passed
 *       with a particular command refer to @a CSL_MemprotHwControlCmd
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of MEMPROT.
 *
 *   @b Example
 *   @verbatim
        #define PAGE_ATTR 0xFFF0
         
        Uint16 pageAttrTable[10] = {PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,
                 PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR,PAGE_ATTR};
        Uint32 key[2] = {0x11223344,0x55667788};

        CSL_MemprotObj mpL2Obj;
        CSL_MemprotHandle hmpL2;
        CSL_Status status;
        CSL_MemprotHwSetup L2MpSetup,L2MpGetSetup;
        CSL_MemprotLockStatus lockStat;
        CSL_MemprotPageAttr pageAttr;
        CSL_MemprotFaultStatus queryFaultStatus;

        // Initializing the module
        CSL_memprotInit(NULL);

        // Opening the Handle for the L2
        hmpL2 = CSL_memprotOpen(&mpL2Obj,CSL_MEMPROT_L2,NULL,&status);
        L2MpSetup. memPageAttr = pageAttrTable;
        L2MpSetup.numPages = 10;
        L2MpSetup.key = key;

        // Do Setup for the L2 Memory protection/
        CSL_memprotHwSetup  (hmpL2,&L2MpSetup);

        // Query Lock Status
        CSL_memprotGetHwStatus(hmpL2,CSL_MEMPROT_QUERY_LOCKSTAT,&lockStat);
        // Unlock the Unit if Locked
        if ((lockStat == CSL_MEMPROT_LOCKSTAT_LOCK)
                || (lockStat == CSL_MEMPROT_LOCKSTAT_UNLOCK)) {
            CSL_memprotHwControl(hmpL2,CSL_MEMPROT_CMD_UNLOCK,key);
        }

     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_memprotHwControl, ".text:csl_section:memprot");
CSL_Status CSL_memprotHwControl (
    CSL_MemprotHandle        hMemprot,
    CSL_MemprotHwControlCmd  cmd,
    void                     *arg
)
{
    CSL_Status status = CSL_SOK;
    
    if (hMemprot == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    
    else if ((arg == NULL) && ((cmd >= 0) && \
                    (cmd <= CSL_MEMPROT_CMD_PAGEATTR))){
        status = CSL_ESYS_INVPARAMS;
    }
    
    else {
        switch (cmd) {
            case CSL_MEMPROT_CMD_LOCK:
                status = CSL_memprotLock(hMemprot, (Uint32 *)(arg));
                break;

            case CSL_MEMPROT_CMD_UNLOCK:
                status = CSL_memprotUnLock(hMemprot, (Uint32 *)(arg));
                break;

            case CSL_MEMPROT_CMD_PAGEATTR:
                CSL_memprotSetPageAttr(hMemprot,
                                   ((CSL_MemprotPageAttr *)arg)->page,
                                   ((CSL_MemprotPageAttr *)arg)->attr);
                break;

            default:
                status = CSL_ESYS_INVCMD;
                break;
        }
    }   
    return status;
}
