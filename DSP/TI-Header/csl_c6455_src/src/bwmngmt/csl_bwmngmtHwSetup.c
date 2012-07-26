/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * priovided
 * ============================================================================
 */

/** ============================================================================
 *   @file  csl_bwmngmtHwSetup.c
 *
 *   @path  $(CSLPATH)\src\bwmngmt
 *
 *   @desc  File for functional layer of CSL API CSL_bwmngmtHwSetup()
 *
 */

/* =============================================================================
 * Revision History
 * ===============
 *  03-Jun-2004 Chad Courtney File Created
 *
 *  11-Apr-2005 Brn updated the file for doxygen compatibiliy
 *
 *  16-Nov-2005 ds  updated the documentation
 * =============================================================================
 */
 
#include <csl_bwmngmt.h>

/** ============================================================================
 *  @n@b CSL_bwmngmtHwSetup
 *
 *   @b Description
 *   @n Configures the BWMNGMT using the values passed in through the
 *      setup structure.
 *
 *   @b Arguments
 *   @verbatim

         hBwmngmt            Handle to the BWMNGMT instance

         setup               Setup structure for BWMNGMT

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *                          CSL_SOK            - Close successful
 *                          CSL_ESYS_BADHANDLE - Invalid handle
 *                          CSL_ESYS_INVPARAMS - If setup is NULL
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_bwmngmtInit() and @a CSL_bwmngmtOpen() must be called
 *       successfully in that order before this function can be called. The
 *       main setup structure consists of fields used for the configuration at
 *       start up. The user must allocate space for it and fill in the main
 *       setup structure fields appropriately before a call to this function
 *       is made. \n
 *
 *   <b> Post Condition </b>
 *   @n  BWMNGMT registers are configured according to the hardware setup 
 *       parameters
 *
 *   @b  Modifies
 *   @n  The following registers and fields are programmed by this API \n
 *   1.  CPU Arbitration Parameters \n
 *       -   PRI field set in L1D, L2 and/or EXT \n
 *       -   MAXWAIT field set in L1D, L2 and/or EXT \n
 *
 *   2.  IDMA Arbitration Parameter \n
 *       -   MAXWAIT field set in L1D, L2 and/or EXT \n
 *
 *   3.  SLAP Arbitration Parameter \n
 *       -   MAXWAIT field set in L1D, L2 and/or EXT \n
 *
 *   4.  MAP Arbitration Parameter \n
 *       -   PRI field set in EXT \n
 *
 *   5.  UC Arbitration Parameter \n
 *       -   MAXWAIT field set in L1D and/or L2 \n
 *
 *  The @b control: bitmask indicates which of the three control blocks
 *  (L1D, L2 and EXT) will be set with the associated PRI and MAXWAIT values 
 *  Note: That if associated control block is not programmable for given 
 *  requestor then it will not ignored but no error will be provide.  This 
 *  allows the user to set control to CSL_BWMNGMT_BLOCK_ALL which is the 
 *  default value. This will set all programmed arbitration values for a given 
 *  requestor to the same value across \n the blocks which is recommended.
 *  If PRI is set to CSL_BWMNGMT_PRI_NULL (-1) then no change will be made 
 *  for the corresponding requestors priority level.
 *  If MAXWAIT is set to CSL_BWMNGMT_MAXWAIT_NULL (-1) then no change will be 
 *  made for the corresponding requestors maxwait setting.

 *  @b Examples:
 *  @verbatim

    Example 1: Sets Priorities and Maxwaits to default values

        CSL_BwmngmtHandle hBwmngmt;
        CSL_BwmngmtHwSetup hwSetup;
        hwSetup = CSL_BWMNGMT_HWSETUP_DEFAULTS;
        ...

        // Init Successfully done
        ...
        // Open Successfully done
        ...
        CSL_bwmngmtHwSetup(hBwmngmt, &hwSetup);


    Example 2: Sets CPU Priority to 1, CPU Maxwait to 8, MAP Priority to 6 for 
    all blocks (L1D, L2 and EXT)

        CSL_BwmngmtHandle hBwmngmt;
        CSL_BwmngmtHwSetup hwSetup;
        hwSetup.cpuPriority = CSL_BWMNGMT_PRI_1;
        hwSetup.cpuMaxwait  = CSL_BWMNGMT_MAXWAIT_8;
        hwSetup.idmaMaxwait = CSL_BWMNGMT_MAXWAIT_NULL;
        hwSetup.slapMaxwait = CSL_BWMNGMT_MAXWAIT_NULL;
        hwSetup.mapPriority = CSL_BWMNGMT_PRI_6;
        hwSetup.ucMaxwait   = CSL_BWMNGMT_MAXWAIT_NULL;
        hwSetup.control     = CSL_BWMNGMT_BLOCK_ALL;
        ...

        // Init Successfully done
        ...
        // Open Successfully done
        ...
        CSL_bwmngmtHwSetup(hBwmngmt, &hwSetup);
     @endverbatim
 *
 *  ===========================================================================
 */
#pragma CODE_SECTION (CSL_bwmngmtHwSetup, ".text:csl_section:bwmngmt");
CSL_Status CSL_bwmngmtHwSetup (
    CSL_BwmngmtHandle    hBwmngmt,
    CSL_BwmngmtHwSetup   *setup
)
{
    CSL_Status  status = CSL_SOK;
    Uint32      _tempControl;
    
    if (hBwmngmt == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    
    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        _tempControl =  setup->control;

        if (setup->cpuPriority != CSL_BWMNGMT_PRI_NULL) {

            if (_tempControl & CSL_BWMNGMT_BLOCK_L1D) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBL1D, 
                                        BWMNGMT_CPUARBL1D_PRI, setup->cpuPriority);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_L2) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBL2, 
                                         BWMNGMT_CPUARBL2_PRI, setup->cpuPriority);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_EXT) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBEXT, 
                                        BWMNGMT_CPUARBEXT_PRI, setup->cpuPriority);
            }
        }

        if (setup->cpuMaxwait != CSL_BWMNGMT_MAXWAIT_NULL) {

            if (_tempControl & CSL_BWMNGMT_BLOCK_L1D) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBL1D, 
                                     BWMNGMT_CPUARBL1D_MAXWAIT, setup->cpuMaxwait);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_L2) {

                CSL_FINS(((CSL_BwmngmtRegs*)CSL_BWMNGMT_0_REGS)->CPUARBL2, 
                                      BWMNGMT_CPUARBL2_MAXWAIT, setup->cpuMaxwait);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_EXT) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->CPUARBEXT, 
                                     BWMNGMT_CPUARBEXT_MAXWAIT, setup->cpuMaxwait);
            }
        }

        if (setup->idmaMaxwait != CSL_BWMNGMT_MAXWAIT_NULL) {

            if (_tempControl & CSL_BWMNGMT_BLOCK_L1D) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->IDMAARBL1D, 
                                   BWMNGMT_IDMAARBL1D_MAXWAIT, setup->idmaMaxwait);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_L2) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->IDMAARBL2, 
                                     BWMNGMT_IDMAARBL2_MAXWAIT, setup->idmaMaxwait);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_EXT) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->IDMAARBEXT, 
                                   BWMNGMT_IDMAARBEXT_MAXWAIT, setup->idmaMaxwait);
            }
        }

        if (setup->slapMaxwait != CSL_BWMNGMT_MAXWAIT_NULL) {

            if (_tempControl & CSL_BWMNGMT_BLOCK_L1D) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->SLAPARBL1D, 
                                   BWMNGMT_SLAPARBL1D_MAXWAIT, setup->slapMaxwait);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_L2) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->SLAPARBL2, 
                                    BWMNGMT_SLAPARBL2_MAXWAIT, setup->slapMaxwait);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_EXT) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->SLAPARBEXT, 
                                   BWMNGMT_SLAPARBEXT_MAXWAIT, setup->slapMaxwait);
            }
        }   

        if (setup->mapPriority != CSL_BWMNGMT_PRI_NULL) {

            if (_tempControl & CSL_BWMNGMT_BLOCK_EXT) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->MAPARBEXT, 
                                        BWMNGMT_MAPARBEXT_PRI, setup->mapPriority);
            }
        }

        if (setup->ucMaxwait != CSL_BWMNGMT_MAXWAIT_NULL) {

            if (_tempControl & CSL_BWMNGMT_BLOCK_L1D) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->UCARBL1D, 
                                       BWMNGMT_UCARBL1D_MAXWAIT, setup->ucMaxwait);
            }

            if (_tempControl & CSL_BWMNGMT_BLOCK_L2) {

                CSL_FINS(((CSL_BwmngmtRegs *)CSL_BWMNGMT_0_REGS)->UCARBL2, 
                                        BWMNGMT_UCARBL2_MAXWAIT, setup->ucMaxwait);
            }
        }   
                     
    }     
    return (status);
}


