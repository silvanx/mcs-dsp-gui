/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2HwSetupRaw.c
 *
 *  @path:   $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2HwSetupRaw()
 *           - The @a CSL_ddr2HwSetupRaw() function definition & it's associated 
 *             functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Apr-2005 RM  File Created.
 *  
 *  05-Oct-2005 NG  Updation done according to new register layer
 *  
 *  03-Feb-2006 ds  Updated configuration of SDCFG register
 * =============================================================================
 */
#include <csl_ddr2.h>

/** ============================================================================
 *   @n@b CSL_ddr2HwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the config data structure.  
 *
 *   @b Arguments
 *   @verbatim
            hDdr2         Handle to the DDR2 external memory interface instance
            
            config        Pointer to the config structure containing the
                          device register values
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration structure
 *                                                pointer is not properly
 *                                                initialized
 *
 *   <b> Pre Condition </b>
 *   @n  @a CSL_ddr2Init() and @a CSL_ddr2Open () must be called successfully.        
 *       before calling this function.          
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified DDR2 EMIF instance will be 
 *       setup according to the values passed through the config structure
 *
 *   @b Modifies
 *   @n Hardware registers of the DDR2 EMIF
 *    
 *   @b Example
 *   @verbatim
        CSL_Ddr2Handle           hDdr2;
        CSL_Ddr2Config           config = CSL_DDR2_CONFIG_DEFAULTS;
        CSL_Status               status;

        ...       
       
        status = CSL_ddr2HwSetupRaw (hDdr2, &config);
        ..
        
            
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2HwSetupRaw, ".text:csl_section:ddr2");
CSL_Status  CSL_ddr2HwSetupRaw (
    CSL_Ddr2Handle    hDdr2,
    CSL_Ddr2Config    *config
)
{
    CSL_Status status = CSL_SOK;
    Uint32 mask = 0;

    if(hDdr2 == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if(config == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* Disabling the Initialization sequence. */

        /* setting the SDRAM Config Register */
        /* The mask is used to leave the reserved fields at their default 
         * values */

        mask = CSL_DDR2_SDCFG_BOOT_UNLOCK_MASK | CSL_DDR2_SDCFG_DDR_DRIVE_MASK |
                CSL_DDR2_SDCFG_TIMUNLOCK_MASK | CSL_DDR2_SDCFG_NM_MASK | 
                CSL_DDR2_SDCFG_CL_MASK | CSL_DDR2_SDCFG_IBANK_MASK |
                CSL_DDR2_SDCFG_PAGESIZE_MASK;

        hDdr2->regs->SDCFG  = (hDdr2->regs->SDCFG & ~mask) |
                                        (config->SDCFG & mask);

        /* setting SDRAM Timing1 Register */
        hDdr2->regs->SDTIM1 = config->SDTIM1;

        /* setting the SDRAM Timing2 Register */
        hDdr2->regs->SDTIM2 = config->SDTIM2;

        /* Clearing the timing unlock bit to prevent further changes*/
        CSL_FINS(hDdr2->regs->SDCFG,DDR2_SDCFG_TIMUNLOCK,
                                   CSL_DDR2_SDCFG_TIMUNLOCK_CLEAR );

        /* setting the SDRAM Refresh Control Register */
        /* The mask is used to leave the reserved fields at their default 
        * values */
        mask = CSL_DDR2_SDRFC_SR_MASK | CSL_DDR2_SDRFC_REFRESH_RATE_MASK;

        hDdr2->regs->SDRFC = (hDdr2->regs->SDRFC & ~mask) | 
                                                   (config->SDRFC & mask);

        /* setting the VBUSM Burst Priority Register */
        hDdr2->regs->BPRIO = config->BPRIO;   

    }
    return (status);
}

