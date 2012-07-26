/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2HwSetup.c
 *
 *  @path:   $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2HwSetup()
 *           - The @a CSL_ddr2HwSetup() function definition & it's associated
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
 *  03-Feb-2006 ds  Updated according to TCI6482/C6455 user guide
 *                  (Added ddrDrive Configuration)
 * =============================================================================
 */
#include <csl_ddr2.h>

/** ============================================================================
 * @n@b   CSL_ddr2HwSetup
 *
 * @b Description
 * @n This function initializes the device registers with the appropriate values
 *  provided through the HwSetup data structure. 
 *
 *  @b Arguments
 *  @verbatim      
            hDdr2           Pointer to the peripheral data object of the
                            DDR2 external memory interface instance
 
            setup           Pointer to setup structure which contains the
                            information to program DDR2 to a useful state
 
    @endverbatim
 *
 *  <b> Return Value </b>  CSL_Status
 *  @li                    CSL_SOK              Hwsetup successful
 *  @li                    CSL_ESYS_BADHANDLE   The handle passed is invalid
 *  @li                    CSL_ESYS_INVPARAMS   The param passed is invalid
 *
 *  <b> Pre Condition </b>
 *  Both @a CSL_ddr2Init() and @a CSL_ddr2Open() must be called
 *  successfully in that order before this function can be called.  The user
 *  has to allocate space for & fill in the main setup structure appropriately
 *  before calling this function
 *
 *  <b> Post Condition </b>
 *  @n  DDR2 registers are configured according to the hardware setup parameters
 *
 *  @b Modifies
 *  @n DDR2 registers
 *
 *  @b Example:
 *  @verbatim
     CSL_Ddr2Handle hDdr2;     
     CSL_Ddr2Timing1 tim1 = CSL_DDR2_TIMING1_DEFAULTS;
     CSL_Ddr2Timing2 tim2 = CSL_DDR2_TIMING2_DEFAULTS;
     CSL_Ddr2Settings set = CSL_DDR2_SETTING_DEFAULTS;
     CSL_Ddr2HwSetup hwSetup ;
     
     hwSetup.refreshRate = (Uint16)0x753;
     hwSetup.timing1Param = &tim1;
     hwSetup.timing2Param = &tim2;
     hwSetup.setParam = &set;
     
     CSL_ddr2HwSetup(hDdr2, &hwSetup);
    @endverbatim
 *
 *
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2HwSetup, ".text:csl_section:ddr2");
CSL_Status  CSL_ddr2HwSetup (
    CSL_Ddr2Handle     hDdr2,
    CSL_Ddr2HwSetup    *setup
)
{

    CSL_Status status = CSL_SOK;
    Uint32 mask;
    
    /* invalid parameter checking */
    if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else if (hDdr2 == NULL) {
    /* bad handle checking*/
        status = CSL_ESYS_BADHANDLE;
    }    
    else {
        /* Refresh rate*/     
        CSL_FINS(hDdr2->regs->SDRFC, DDR2_SDRFC_REFRESH_RATE, setup->refreshRate);  

        /* Writing the ddr2 sdram Settings in SDRAM Config register */  
        if (setup->setParam != NULL) {
            mask = ~( 
                      (CSL_DDR2_SDCFG_TIMUNLOCK_MASK) |
                      (CSL_DDR2_SDCFG_CL_MASK) | 
                      (CSL_DDR2_SDCFG_IBANK_MASK) |
                      (CSL_DDR2_SDCFG_PAGESIZE_MASK)|
                      (CSL_DDR2_SDCFG_NM_MASK));   

            hDdr2->regs->SDCFG = (hDdr2->regs->SDCFG & mask ) |
                                  (CSL_FMK(DDR2_SDCFG_TIMUNLOCK, 
                                           CSL_DDR2_SDCFG_TIMUNLOCK_SET)) |
                                  (CSL_FMK(DDR2_SDCFG_CL, 
                                           setup->setParam->casLatncy)) |
                                  (CSL_FMK(DDR2_SDCFG_IBANK, 
                                           setup->setParam->ibank)) |
                                  (CSL_FMK(DDR2_SDCFG_NM, 
                                           setup->setParam->narrowMode)) |
                                  (CSL_FMK(DDR2_SDCFG_PAGESIZE, 
                                           setup->setParam->pageSize));  

            CSL_FINS(hDdr2->regs->SDCFG, DDR2_SDCFG_BOOT_UNLOCK, \
                                              CSL_DDR2_SDCFG_BOOT_UNLOCK_UNLOCKED);
            CSL_FINS(hDdr2->regs->SDCFG, DDR2_SDCFG_DDR_DRIVE, \
                                                        setup->setParam->ddrDrive);
            CSL_FINS(hDdr2->regs->SDCFG, DDR2_SDCFG_BOOT_UNLOCK, \
                                              CSL_DDR2_SDCFG_BOOT_UNLOCK_LOCKED);
        }

        /* Setup the SDRAM Timing1 Register */
        /* All fields which are writable with timing_unlock set are edited since the
         *  unlock bit is set above
         */
        if(setup->timing1Param != NULL) {
            if(setup->setParam == NULL) {
                CSL_FINS(hDdr2->regs->SDCFG, DDR2_SDCFG_TIMUNLOCK, 
                        CSL_DDR2_SDCFG_TIMUNLOCK_SET);
            }
            mask = ~( (CSL_DDR2_SDTIM1_T_RFC_MASK) |
                      (CSL_DDR2_SDTIM1_T_RP_MASK) |
                      (CSL_DDR2_SDTIM1_T_RCD_MASK) |
                      (CSL_DDR2_SDTIM1_T_WR_MASK) |
                      (CSL_DDR2_SDTIM1_T_RAS_MASK) | 
                      (CSL_DDR2_SDTIM1_T_RC_MASK) |
                      (CSL_DDR2_SDTIM1_T_RRD_MASK) | 
                      (CSL_DDR2_SDTIM1_T_WTR_MASK));   


            hDdr2->regs->SDTIM1 = (hDdr2->regs->SDTIM1 & mask) |
                        (CSL_FMK(DDR2_SDTIM1_T_RFC, setup->timing1Param->trfc)) |
                        (CSL_FMK(DDR2_SDTIM1_T_RP, setup->timing1Param->trp)) |
                        (CSL_FMK(DDR2_SDTIM1_T_RCD, setup->timing1Param->trcd)) |
                        (CSL_FMK(DDR2_SDTIM1_T_WR, setup->timing1Param->twr)) |
                        (CSL_FMK(DDR2_SDTIM1_T_RAS, setup->timing1Param->tras)) |
                        (CSL_FMK(DDR2_SDTIM1_T_RC, setup->timing1Param->trc)) |
                        (CSL_FMK(DDR2_SDTIM1_T_RRD, setup->timing1Param->trrd)) |
                        (CSL_FMK(DDR2_SDTIM1_T_WTR, setup->timing1Param->twtr));
        }

        /* Setup the SDRAM Timing2 Register */
        /* All fields which are writable with timing_unlock set are edited since the
         *  unlock bit is set above
         */
        if (setup->timing2Param != NULL) {
            if((setup->setParam == NULL) && (setup->timing1Param == NULL)) {
                 CSL_FINS(hDdr2->regs->SDCFG, DDR2_SDCFG_TIMUNLOCK, 
                         CSL_DDR2_SDCFG_TIMUNLOCK_SET);
            }
            mask = ~( (CSL_DDR2_SDTIM2_T_ODT_MASK)|
                      (CSL_DDR2_SDTIM2_T_SXNR_MASK) |
                      (CSL_DDR2_SDTIM2_T_SXRD_MASK) |
                      (CSL_DDR2_SDTIM2_T_RTP_MASK) |
                      (CSL_DDR2_SDTIM2_T_CKE_MASK));   

            hDdr2->regs->SDTIM2 = (hDdr2->regs->SDTIM2 & mask) |
                                   (CSL_FMK(DDR2_SDTIM2_T_ODT, 
                                            setup->timing2Param->todt)) |
                                   (CSL_FMK(DDR2_SDTIM2_T_SXNR, 
                                            setup->timing2Param->tsxnr)) |
                                   (CSL_FMK(DDR2_SDTIM2_T_SXRD, 
                                            setup->timing2Param->tsxrd)) |
                                   (CSL_FMK(DDR2_SDTIM2_T_RTP, 
                                            setup->timing2Param->trtp)) |
                                   (CSL_FMK(DDR2_SDTIM2_T_CKE, 
                                            setup->timing2Param->tcke));
        }

        /* Locking the timing_unlock to prevent further changes */
        CSL_FINS(hDdr2->regs->SDCFG, DDR2_SDCFG_TIMUNLOCK, 
                CSL_DDR2_SDCFG_TIMUNLOCK_CLEAR);        
    }

    return (status);
}

