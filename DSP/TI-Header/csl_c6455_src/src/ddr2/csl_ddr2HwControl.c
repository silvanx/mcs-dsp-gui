/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2HwControl.c
 *  
 *  @path    $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2HwControl()
 *           - The @a CSL_ddr2HwControl() function definition & it's associated
 *             functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  11-Apr-2005 RM  File Created.
 *  
 *  05-Oct-2005 NG  Updation done according to new register layer
 *  
 * =============================================================================
 */
#include <csl_ddr2.h>
#include <csl_ddr2Aux.h>

/** ============================================================================
 * @n@b   CSL_ddr2HwControl
 *
 * @b Description
 * @n Control operations for the DDR2.  For a particular control operation, the
 *  pointer to the corresponding data type needs to be passed as argument 
 *  HwControl function Call.  All the arguments (Structure elements included) 
 *  passed to  the HwControl function are inputs. For the list of commands 
 *  supported and argument type that can be @a void* casted & passed with a 
 *  particular command refer to @a CSL_Ddr2HwControlCmd.
 *
 *  @b Arguments
 *  @verbatim      
            hDdr2           Pointer to the peripheral data object of the
                            DDR2 external memory interface instance
 
            cmd             The command to this API indicates the action to be 
			                taken 
 
            arg             An optional argument @a void* casted
 
    @endverbatim
 *
 *  <b> Return Value </b>  CSL_Status
 *  @li                    CSL_SOK            -  Command successful
 *  @li                    CSL_ESYS_BADHANDLE -  The handle passed is invalid
 *  @li                    CSL_ESYS_INVPARAMS -  The argument passed is invalid
 *  @li                    CSL_ESYS_INVCMD    -  The Command passed is invalid      
 *
 *  <b> Pre Condition </b>
 *  Both @a CSL_ddr2Init() and @a CSL_ddr2Open() must be called successfully
 *  in order before calling @a CSL_ddr2HwControl(). For the argument type that 
 *  can be @a void* casted & passed with a particular command refer to 
 *  @a CSL_Ddr2HwControlCmd.
 *
 *  <b> Post Condition </b>
 *  @n  DDR2 registers are configured according to the command passed.
 *
 * @b Modifies
 * @n DDR2 registers
 *
 *  @b Example:
 *  @verbatim
       CSL_Ddr2Handle hDdr2;
       CSL_Status status;
       CSL_Ddr2SelfRefresh command;
       
       command = CSL_DDR2_SELF_REFRESH_DISABLE;
       ...
       status = CSL_ddr2HwControl(hDdr2,
                                  CCSL_DDR2_CMD_SELF_REFRESH,
                                  &command);
    @endverbatim
 *
 *
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2HwControl, ".text:csl_section:ddr2");
CSL_Status  CSL_ddr2HwControl (
    CSL_Ddr2Handle          hDdr2,
    CSL_Ddr2HwControlCmd    cmd,
    void                    *arg
)
{
    CSL_Status status = CSL_SOK;

    if(hDdr2 == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if(((cmd >= 0) && (cmd <= CSL_DDR2_CMD_PRIO_RAISE)) && (arg == NULL)) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(cmd) {
            case CSL_DDR2_CMD_SELF_REFRESH:
                CSL_ddr2Selfrefresh(hDdr2, (*(CSL_Ddr2SelfRefresh*)arg));
                break;

            case CSL_DDR2_CMD_REFRESH_RATE:
                CSL_ddr2RefreshRate(hDdr2,(*(Uint16*)arg));
                break;

            case CSL_DDR2_CMD_PRIO_RAISE:
                CSL_ddr2PrioRaise(hDdr2,(*(Uint8*)arg));
                break;      

            default:
                status = CSL_ESYS_INVCMD ;
                break;
        }
    }
    
    return (status);
}

