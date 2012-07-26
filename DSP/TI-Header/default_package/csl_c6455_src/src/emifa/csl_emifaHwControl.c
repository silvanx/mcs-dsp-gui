/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_emifaHwControl.c
 *  
 *  @path    $(CSLPATH)\src\emifa
 *
 *  $desc    File for functional layer of CSL API @a CSL_emifaHwControl()
 *           - The @a CSL_emifaHwControl() function definition & it's associated
 *             functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-May-2005 RM  File Created.
 *  
 *  09-Sep-2005 NG  Updation according to coding guidelines
 *  
 * =============================================================================
 */
#include <csl_emifa.h>
#include <csl_emifaAux.h>

/** ============================================================================
 * @n@b   CSL_emifaHwControl
 *
 * @b Description
 * @n Control operations for the EMIFA.  For a particular control operation, the
 *  pointer to the corresponding data type needs to be passed as argument 
 *  HwControl function Call.  All the arguments (structure elements included) 
 *  passed to  the HwControl function are inputs.  For the list of commands 
 *  supported and argument type that can be @a void* casted & passed with a 
 *  particular command refer to @a CSL_EmifaHwControlCmd.
 *
 * @b Arguments
 * @verbatim      
            hEmifa          Pointer to the object that holds reference to the
                            instance of EMIFA requested after the call
 
            cmd             The command to this API indicates the action to be 
			                taken
            arg             An optional argument @a void* casted
   @endverbatim
 *
 * <b> Return Value </b>  CSL_Status
 * @li                    CSL_SOK            - Hardware control call is 
 *                                             successful
 * @li                    CSL_ESYS_INVCMD    - command is not valid    
 * @li                    CSL_ESYS_BADHANDLE - Handle is not valid    
 *
 * <b> Pre Condition </b>
 *  @n  Both @a CSL_emifaInit() and @a CSL_emifaOpen() must be called 
 *  successfully in order before calling @a CSL_emifaHwControl(). 
 *  For the argument type that can be @a void* casted & passed with a 
 *  particular command refer to @a CSL_EmifaHwControlCmd
 *
 * <b> Post Condition </b>
 * @n  EMIFA registers are configured according to the command passed
 *
 *  @b Modifies
 *  @n EMIFA registers  
 *
 * @b Example:
 * @verbatim
       CSL_EmifaHandle hEmifa;
       CSL_Status status;
       Uint8 * command;
       ...
       status = CSL_emifaHwControl(hEmifa,
                                   CSL_EMIFA_CMD_PRIO_RAISE,
                                   &command);
   @endverbatim
 *
 * =============================================================================
 */
     
#pragma CODE_SECTION (CSL_emifaHwControl, ".text:csl_section:emifa");
CSL_Status  CSL_emifaHwControl (
    CSL_EmifaHandle          hEmifa,
    CSL_EmifaHwControlCmd    cmd,
    void                     *arg
)
{
    CSL_Status status = CSL_SOK;

    if(hEmifa == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if ((cmd == CSL_EMIFA_CMD_PRIO_RAISE) && (arg == NULL)) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(cmd) {
            case CSL_EMIFA_CMD_ASYNC_TIMEOUT_CLEAR:
                CSL_emifaAsyncClear (hEmifa);
                break;
            case CSL_EMIFA_CMD_ASYNC_TIMEOUT_DISABLE:
                CSL_emifaAsyncDisable (hEmifa);    
                break;
            case CSL_EMIFA_CMD_ASYNC_TIMEOUT_ENABLE:
                CSL_emifaAsyncEnable (hEmifa);
                break;         
            case CSL_EMIFA_CMD_PRIO_RAISE:
                CSL_emifaPrioRaise (hEmifa,(*(Uint8*)arg));
                break;        
            default:
                status = CSL_ESYS_INVCMD ;
                break;
        }
    }
    
    return (status);
}

