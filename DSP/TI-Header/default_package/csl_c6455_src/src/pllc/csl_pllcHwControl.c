/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** @file csl_pllcHwControl.c
 *
 *  @brief File for functional layer of CSL API @a CSL_pllcHwControl()
 *
 *  Path: \(CSLPATH)\src\pllc
 */

/*  ============================================================================
 *  Revision History
 *  ===============
 *  25-Aug-2005 Tej File Created.
 *  18-Jan-2006 sd  Changes according to spec changes
 *  ============================================================================
 */

#include <csl_pllc.h>
#include <csl_pllcAux.h>

/** ============================================================================
 *   @n@b CSL_pllcHwControl
 *
 *   @b Description
 *   @n Takes a command of PLLC with an optional argument & implements it.
 *
 *   @b Arguments
 *   @verbatim
            hPllc           Handle to the PLLC instance

            cmd             The command to this API indicates the action to be
                            taken on PLLC.

            arg             An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li            CSL_SOK               - Status info return successful.
 *   @li            CSL_ESYS_BADHANDLE    - Invalid handle
 *   @li            CSL_ESYS_INVCMD       - Invalid command
 *   @li            CSL_ESYS_INVPARAMS    - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  To change PLLM, PREDIV & PLLDIVn, PLLCTL_PLLEN bit must be in BYPASS
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of PLLC.
 *
 *   @b Example
 *   @verbatim
        CSL_PllcHandle         hPllc;
        CSL_PllcHwControlCmd   cmd = CSL_PLLC_CMD_SET_PLLM;
        void                   arg = 0x7;
        ...

        status = CSL_pllcHwControl (hPllc, cmd, &arg);
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CSL_pllcHwControl, ".text:csl_section:pllc");
CSL_Status CSL_pllcHwControl (
    CSL_PllcHandle              hPllc,
    CSL_PllcHwControlCmd        cmd,
    void                       *arg
)
{
    CSL_Status status = CSL_SOK;

    if (hPllc == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (arg == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (cmd) {
            /* cmd to change PLLCTL and PLLCMD register of PLL controller */
            case CSL_PLLC_CMD_PLLCONTROL:
                CSL_pllcCommandCtrl (hPllc, *(CSL_BitMask32*)arg, &status);
                break;
            /* cmd to change PLLM register of PLL controller */
            case CSL_PLLC_CMD_SET_PLLM:
                CSL_pllcMultiplierCtrl (hPllc, *(Uint32*)arg, &status);
                break;
            /* cmd to change PLLDIVn_RATIO of PLLDIVn register */
            case CSL_PLLC_CMD_SET_PLLRATIO:
                CSL_pllcSetPLLDivRatio (hPllc, *(CSL_PllcDivRatio*) arg, &status);
                break;
            /* cmd to change PLLDIVn_DnEN of PLLDIVn register */
            case CSL_PLLC_CMD_PLLDIV_CONTROL:
                CSL_pllcPLLDivCtrl (hPllc, *(CSL_PllcDivideControl*) arg, &status);
                break;
            default:
                status = CSL_ESYS_INVCMD;
                break;
        }
    }

    return status;
}

