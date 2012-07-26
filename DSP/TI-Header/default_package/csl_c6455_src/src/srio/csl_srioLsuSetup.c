/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 * 
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * =============================================================================
 */
/** ===========================================================================
 * @file csl_srioLsuSetup.c
 *
 * @brief File for functional layer of CSL API CSL_srioLsuSetup() 
 * 
 * @path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioLsuSetup() function definition & it's associated functions
 * ============================================================================
 */       
/* ============================================================================
 * Revision History
 * ===============
 * 25-Aug-2005 PSK File Created.
 * ============================================================================
 */

#include <csl_srio.h>

/** ============================================================================
 *   @n@b CSL_srioLsuSetup
 *
 *   @b Description
 *   @n Function to configure the LSU module for Direct IO transfer
 *
 *   @b Arguments
 *   @verbatim
            hSrio           Handle to the SRIO instance

            lsuConfig       Pointer to the direct IO configuration structure

            index           index to the LSU block number
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Successfully configured the 
                                                  LSU module
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle is passed
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The LSU module registers are configured with the passed parameters 
 *       and the data transfer starts.
 *
 *   @b Modifies
 *   @n LSU module registers
 *
 *   @b Example
 *   @verbatim
         CSL_status					status;
         CSL_SrioDirectIO_ConfigXfr lsuConfig;
         Uint8 					    index;

         index = 1;
         lsuConfig.srcNodeAdd = 0x2ffe550;
         lsuConfig.priority   = 2;
         ...
         Status = CSL_srioLsuSetup(hSrio, &lsuConfig, index);        
         ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_srioLsuSetup, ".text:csl_section:srio");
CSL_Status CSL_srioLsuSetup (
    CSL_SrioHandle             hSrio,
    CSL_SrioDirectIO_ConfigXfr *lsuConfig,
    Uint8                      index
)
{
    CSL_Status status = CSL_SOK;
    
    if (hSrio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (lsuConfig == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* Configures LSU control register 0 */
        hSrio->regs->LSU[index].LSU_REG0 = lsuConfig->dstNodeAddr.addressHi;

        /* Configures LSU control register 1 */
        hSrio->regs->LSU[index].LSU_REG1 = lsuConfig->dstNodeAddr.addressLo;

        /* Configures LSU control register 2 */
        hSrio->regs->LSU[index].LSU_REG2 = lsuConfig->srcNodeAddr;

        /* Configures LSU control register 3 */
        CSL_FINS(hSrio->regs->LSU[index].LSU_REG3, SRIO_LSU_REG3_BYTE_COUNT, 
                                                        lsuConfig->byteCnt);

        /* Configures LSU control register 4 */
        hSrio->regs->LSU[index].LSU_REG4 = 
                CSL_FMK(SRIO_LSU_REG4_OUTPORTID, lsuConfig->outPortId)|
                CSL_FMK(SRIO_LSU_REG4_PRIORITY, lsuConfig->priority)|				
                CSL_FMK(SRIO_LSU_REG4_XAMBS, lsuConfig->xambs)|					
                CSL_FMK(SRIO_LSU_REG4_ID_SIZE, lsuConfig->idSize)|				
                CSL_FMK(SRIO_LSU_REG4_DESTID, lsuConfig->dstId)|
                CSL_FMK(SRIO_LSU_REG4_INTERRUPT_REQ, lsuConfig->intrReq);

        /* Configures LSU control register 5 */
        hSrio->regs->LSU[index].LSU_REG5 = 
                CSL_FMK(SRIO_LSU_REG5_DRBLL_INFO, lsuConfig->doorbellInfo)|		
                CSL_FMK(SRIO_LSU_REG5_HOP_COUNT, lsuConfig->hopCount)|			
                CSL_FMK(SRIO_LSU_REG5_PACKET_TYPE, lsuConfig->pktType);
    }
    return (status);
}

