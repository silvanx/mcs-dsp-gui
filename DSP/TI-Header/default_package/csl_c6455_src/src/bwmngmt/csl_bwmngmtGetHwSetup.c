/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * priovided
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_bwmngmtGetHwSetup.c
 *
 *   @path  $(CSLPATH)\src\bwmngmt
 *
 *   @desc  File for functional layer of CSL API CSL_bwmngmtGetHwSetup()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  04-Jun-2004 Chad Courtney File Created
 *
 *  11-Apr-2005 Brn updated the file for doxygen compatibiliy
 *
 *  16-Nov-2005 ds  updated the documentation
 * =============================================================================
 */

#include <csl_bwmngmt.h>

/** ============================================================================
 *  @n@b CSL_bwmngmtGetHwSetup
 *
 *   @b Description
 *   @n Gets the current set up of BWMNGMT
 *
 *  @b Arguments
 *  @verbatim
          hBwmngmt            Handle to the BWMNGMT instance

          setup               Setup structure for BWMNGMT

      @endverbatim
 *
 *  <b> Return Value </b>  CSL_Status
 *                         CSL_SOK            - Close successful
 *                         CSL_ESYS_BADHANDLE - Invalid handle
 *                         CSL_ESYS_INVPARAMS - IF setup is NULL
 *
 *  <b> Pre Condition </b>
 *  @n Both CSL_bwmngmtInit() and CSL_bwmngmtOpen() must be called
 *     successfully in that order before this function can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b  Modifies
 *   @n 
 *   1.  CPU Arbitration Parameters 
 *       -   PRI field set in Control Block Specified by "control" \n
 *       -   MAXWAIT field set in Control Block Specified by "control"  \n
 *
 *   2.  IDMA Arbitration Parameter \n
 *       -   MAXWAIT field set in Control Block Specified by "control"  \n
 *
 *   3.  SLAP Arbitration Parameter \n
 *       -   MAXWAIT field set in Control Block Specified by "control"  \n
 *
 *   4.  MAP Arbitration Parameter \n
 *       -   PRI field set in Control Block Specified by "control"  \n
 *       if not EXT then returns CSL_BWMNGMT_PRI_NULL \n
 *
 *   5.  UC Arbitration Parameter \n
 *       -   MAXWAIT field set in Control Block Specified by "control" \n
 *       if not L1D or L2 then returns CSL_BWMNGMT_MAXWAIT_NULL \n
 *
 *  @b Example:
 *  @verbatim

        CSL_BwmngmtHandle hBwmngmt;
        CSL_BwmngmtHwSetup hwSetup;
        hwSetup.control = CSL_BWMNGMT_BLOCK_L1D;
        // only CSL_BWMNGMT_BLOCK_L1D, CSL_BWMNGMT_BLOCK_L2, or
        // CSL_BWMNGMT_BLOCK_EXT are valid
        ...

        // Init Successfully done
        ...
        // Open Successfully done
        ...
        CSL_bwmngmtGetHwSetup(hBwmngmt, &hwSetup);

    @endverbatim
 *  ===========================================================================
 */
#pragma CODE_SECTION (CSL_bwmngmtGetHwSetup, ".text:csl_section:bwmngmt");
CSL_Status CSL_bwmngmtGetHwSetup (
    CSL_BwmngmtHandle    hBwmngmt,
    CSL_BwmngmtHwSetup   *hwSetup
)
{   
    CSL_Status status = CSL_SOK;
    Uint32 ControlBlock;
    
    if (hBwmngmt == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        ControlBlock =  hwSetup->control;

        if (ControlBlock == CSL_BWMNGMT_BLOCK_L1D) {

            hwSetup->cpuPriority = (CSL_BwmngmtPriority)
                       CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBL1D, 
                                                            BWMNGMT_CPUARBL1D_PRI);

            hwSetup->cpuMaxwait = (CSL_BwmngmtMaxwait)
                       CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBL1D, 
                                                        BWMNGMT_CPUARBL1D_MAXWAIT);

            hwSetup->idmaMaxwait = (CSL_BwmngmtMaxwait)  
                      CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->IDMAARBL1D, 
                                                       BWMNGMT_IDMAARBL1D_MAXWAIT);

            hwSetup->slapMaxwait = (CSL_BwmngmtMaxwait)  
                      CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->SLAPARBL1D, 
                                                       BWMNGMT_SLAPARBL1D_MAXWAIT);

            hwSetup->ucMaxwait = (CSL_BwmngmtMaxwait)  
                        CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->UCARBL1D, 
                                                         BWMNGMT_UCARBL1D_MAXWAIT);
        }
        else if (ControlBlock == CSL_BWMNGMT_BLOCK_L2) {

            hwSetup->cpuPriority = (CSL_BwmngmtPriority) 
                        CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBL2, 
                                                             BWMNGMT_CPUARBL2_PRI);    

            hwSetup->cpuMaxwait = (CSL_BwmngmtMaxwait)  
                        CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBL2, 
                                                         BWMNGMT_CPUARBL2_MAXWAIT);

            hwSetup->idmaMaxwait = (CSL_BwmngmtMaxwait)  
                       CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->IDMAARBL2, 
                                                        BWMNGMT_IDMAARBL2_MAXWAIT);

            hwSetup->slapMaxwait = (CSL_BwmngmtMaxwait)  
                       CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->SLAPARBL2, 
                                                        BWMNGMT_SLAPARBL2_MAXWAIT);

            hwSetup->ucMaxwait = (CSL_BwmngmtMaxwait)  
                         CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->UCARBL2, 
                                                          BWMNGMT_UCARBL2_MAXWAIT);             
        } 
        else if (ControlBlock == CSL_BWMNGMT_BLOCK_EXT) {

            hwSetup->cpuPriority = (CSL_BwmngmtPriority) 
                       CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBEXT, 
                                                            BWMNGMT_CPUARBEXT_PRI);  

            hwSetup->cpuMaxwait = (CSL_BwmngmtMaxwait)  
                       CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBEXT, 
                                                        BWMNGMT_CPUARBEXT_MAXWAIT);

            hwSetup->idmaMaxwait = (CSL_BwmngmtMaxwait)  
                      CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->IDMAARBEXT, 
                                                       BWMNGMT_IDMAARBEXT_MAXWAIT);

            hwSetup->slapMaxwait = (CSL_BwmngmtMaxwait)  
                      CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->SLAPARBEXT, 
                                                       BWMNGMT_SLAPARBEXT_MAXWAIT);

            hwSetup->mapPriority = (CSL_BwmngmtPriority) 
                       CSL_FEXT(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->MAPARBEXT, 
                                                            BWMNGMT_MAPARBEXT_PRI);             
        } 
        else { 
            status = CSL_ESYS_INVPARAMS;
        }

    }
    return status;
}


