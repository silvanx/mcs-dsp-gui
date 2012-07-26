/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.             
 * ============================================================================
 */ 

/** ============================================================================
 *   @file  csl_cfgHwControl.c
 *
 *   @path  $(CSLPATH)\src\cfg
 *
 *   @desc  File for functional layer of CSL API CSL_cfgHwControl()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 * 14-Apr-2005 Brn File Created
 * =============================================================================
 */

#include <csl_cfg.h>
#include <csl_cfgAux.h>

/** ============================================================================
 *   @n@b CSL_cfgHwControl
 *
 *   @b Description
 *   @n Takes a command of CFG with an optional argument & implements it.
 *
 *   @b Arguments
 *   @verbatim
            hCfg            Handle to the CFG instance

            cmd             The command to this API indicates the action to be
                            taken on CFG.

            arg             An optional argument.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li         CSL_SOK               - Status info return successful.
 *   @li         CSL_ESYS_INVCMD       - Invalid command
 *   @li         CSL_ESYS_BADHANDLE    - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_cfgInit() and CSL_cfgOpen() must be called successfully in 
 *       that order before CSL_cfgHwControl() can be called
 *
 *   <b> Post Condition </b>
 *   @n  CFG registers are configured according to the command and the command 
 *       arguments. The command determines which registers are modified
 *
 *   @b Modifies
 *   @n The registers of CFG.
 *
 *   @b Example
 *   @verbatim
        CSL_CfgHandle         hCfg;
        CSL_Status            status;
        
        ...
        status = CSL_cfgHwControl(hCfg, CSL_CFG_CMD_CLEAR, NULL);
        ...
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_cfgHwControl, ".text:csl_section:cfg");
CSL_Status CSL_cfgHwControl(
    CSL_CfgHandle        hCfg,
    CSL_CfgHwControlCmd  cmd,
    void                 *arg
)
{
    CSL_Status status = CSL_SOK;

    if ((cmd == 0) && (hCfg == NULL))
        status = CSL_ESYS_BADHANDLE;
    
    else {
        switch(cmd){
            case CSL_CFG_CMD_CLEAR:
                CSL_cfgCmdClear(hCfg);
                break;

            default:
                status = CSL_ESYS_INVCMD ;
                break;
        }
    }
    return status;
}
