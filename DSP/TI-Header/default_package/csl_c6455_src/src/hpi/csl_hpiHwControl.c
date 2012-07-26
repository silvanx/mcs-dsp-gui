/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiHwControl.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiHwControl()
 *
 */
/* ============================================================================
 * Revision History
 * ===============
 *  06-Mar-2006 sd  Removed the invalid parameter check
 * ============================================================================
 */
#include <csl_hpi.h>
#include <csl_hpiAux.h>

/** ============================================================================
 *   @n@b CSL_hpiHwControl
 *
 *   @b Description
 *   @n This function takes an input control command with an optional argument 
 *      and accordingly controls the operation/configuration of HPI.
 *
 *   @b Arguments
 *   @verbatim
            hHpi           Handle to the HPI instance

            cmd             The command to this API indicates the action to be
                            taken on HPI.

            arg             An optional argument.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li         CSL_SOK               - Command successful.
 *   @li         CSL_ESYS_BADHANDLE    - The handle passed is invalid
 *   @li         CSL_ESYS_INVCMD       - Invalid command
 *   @li         CSL_ESYS_INVPARAMS    - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_hpiInit() and CSL_hpiOpen() must be called successfully in order 
 *       before calling CSL_hpiHwControl().
 *
 *   <b> Post Condition </b>
 *   @n  HPI registers are configured according to the command passed.
 *
 *   @b Modifies
 *   @n The hardware registers of HPI.
 *
 *   @b Example
 *   @verbatim
        CSL_HpiHandle         hHpi;
        CSL_Status            status;
        CSL_HpiHwControlCmd   cmd = CSL_HPI_CMD_SET_DSP_INT;
        
        status = CSL_hpiHwControl(hHpi, cmd, NULL);

     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_hpiHwControl, ".text:csl_section:hpi");
CSL_Status CSL_hpiHwControl (
    CSL_HpiHandle          hHpi,
    CSL_HpiHwControlCmd    cmd,
    void                   *arg
)
{
    CSL_Status status = CSL_SOK;
    
    if (hHpi == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else {
        switch (cmd) {
            /* Set the Host-to-DSP Interrupt */        
            case CSL_HPI_CMD_SET_DSP_INT:
                CSL_hpiSetDspInt(hHpi);
                break;
            
            /* Reset the Host-to-DSP Interrupt */        
            case CSL_HPI_CMD_RESET_DSP_INT:
                CSL_hpiResetDspInt(hHpi);
                break;
            
            /* Set the HPIC Host Interrupt */        
            case CSL_HPI_CMD_SET_HINT:
                CSL_hpiSetHint(hHpi);
                break;

            /* Rest the HPIC Host Interrupt */        
            case CSL_HPI_CMD_RESET_HINT:
                CSL_hpiResetHint(hHpi);
                break;

            default:
                status = CSL_ESYS_INVCMD;
        }
    }
    return (status);
}

