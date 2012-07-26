/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_emifaHwSetup.c
 *
 *  @path    $(CSLPATH)\src\emifa
 *
 *  @desc    File for functional layer of CSL API @a CSL_emifaHwSetup()
 *           - The @a CSL_emifaHwSetup() function definition & it's associated
 *             functions
 *
 */ 
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-May-2005 RM  File Created.
 *  
 *  08-Jul-2005 RM  Changes made in accordance to the change in cslr_emifa.h           
 *                               
 *  09-Sep-2005 NG  Updation according to coding guidelines
 *  
 * =============================================================================
 */
#include <csl_emifa.h>

/** ============================================================================
 * @n@b   CSL_emifaHwSetup
 *
 * @b Description
 * @n This function initializes the device registers with the appropriate values
 *  provided through the HwSetup data structure. For information passed through 
 *  the HwSetup data structure refer @a CSL_EmifaHwSetup.
 *  
 * @b Arguments
 * @verbatim      
            hEmifa          Pointer to the object that holds reference to the
                            instance of EMIFA requested after the call
 
            setup           Pointer to setup structure which contains the
                            information to program EMIFA to a useful state 
   @endverbatim
 *
 * <b> Return Value </b>  CSL_Status
 * @li                    CSL_SOK            - configuration successful
 * @li                    CSL_ESYS_FAIL      - The external memory interface 
 *                                              instance is not available.
 * @li                    CSL_ESYS_INVPARAMS - Parameters are not valid    
 * @li                    CSL_ESYS_BADHANDLE - Handle is not valid    
 *
 * <b> Pre Condition </b>
 * @n  Both @a CSL_emifaInit() and @a CSL_emifaOpen() must be called
 *     successfully in order before calling this function. The user has to 
 *     allocate space for & fill in the main setup structure appropriately
 *     before calling this function. 
 *
 * <b> Post Condition </b>
 * @n  EMIFA registers are configured according to the hardware setup parameters
 *
 *   @b Modifies
 *   @n EMIFA registers  
 *
 * @b Example:
 * @verbatim
     CSL_EmifaHandle hEmifa;          
     CSL_EmifaAsync asyncMem = CSL_EMIFA_ASYNCCFG_DEFAULTS;
     CSL_EmifaAsyncWait asyncWait = CSL_EMIFA_ASYNCWAIT_DEFAULTS; 
     CSL_EmifaMemType value;
     CSL_EmifaHwSetup hwSetup ;

     value.ssel = 0;
     value.async = &asyncMem;
     value.sync = NULL;      
     hwSetup.asyncWait = &asyncMem;
     hwSetup.cefg [0] = &value;
     hwSetup.ceCfg [1] = NULL;
     hwSetup.ceCfg [2] = NULL;
     hwSetup.ceCfg [3] = NULL;
     
     //Initialize the Emifa CSL 
     
     //Open Emifa Module

     CSL_emifaHwSetup(hEmifa, &hwSetup);  
     
   @endverbatim
 *
 * ============================================================================
 */

#pragma CODE_SECTION (CSL_emifaHwSetup, ".text:csl_section:emifa");
CSL_Status CSL_emifaHwSetup(
    CSL_EmifaHandle     hEmifa,
    CSL_EmifaHwSetup    *setup
)
{
    CSL_Status status = CSL_SOK;
    Uint32 mask, mask1, mask2;
    Uint8 loop;
    volatile Uint32 *ceCfgBaseAddr = 0;
    
    /* invalid parameter checking */
    if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else if (hEmifa == NULL) {
        /* bad handle checking */
        status = CSL_ESYS_BADHANDLE;
    }           
    else {
        if (setup->asyncWait != NULL) {
            mask = ~((CSL_EMIFA_AWCC_AP_MASK) |(CSL_EMIFA_AWCC_TA_MASK) |
                     (CSL_EMIFA_AWCC_MAX_EXT_WAIT_MASK));   

            hEmifa->regs->AWCC = (hEmifa->regs->AWCC & mask) |
                    (CSL_FMK(EMIFA_AWCC_AP, setup->asyncWait->asyncRdyPol)) |
                    (CSL_FMK(EMIFA_AWCC_TA, setup->asyncWait->turnArnd)) |
                    (CSL_FMK(EMIFA_AWCC_MAX_EXT_WAIT, 
                             setup->asyncWait->maxExtWait));
        }

        /* Configuring chip selects for synchronous or Asynchronous memory */
        ceCfgBaseAddr = &(hEmifa->regs->CE2CFG);

        mask1 = ~((CSL_EMIFA_CE2CFG_SS_MASK) | 
                  (CSL_EMIFA_CE2CFG_BWEM_MASK) |
                  (CSL_EMIFA_CE2CFG_AE_MASK) |
                  (CSL_EMIFA_CE2CFG_W_SETUP_MASK) |
                  (CSL_EMIFA_CE2CFG_W_STROBE_MASK) |
                  (CSL_EMIFA_CE2CFG_W_HOLD_MASK) |
                  (CSL_EMIFA_CE2CFG_R_SETUP_MASK) |
                  (CSL_EMIFA_CE2CFG_R_STROBE_MASK) |
                  (CSL_EMIFA_CE2CFG_R_HOLD_MASK) |
                  (CSL_EMIFA_CE2CFG_ASIZE_MASK));

        mask2 = ~((CSL_EMIFA_CE2CFG_RD_BE_EN_MASK) |
                  (CSL_EMIFA_CE2CFG_CE_EXT_MASK) |
                  (CSL_EMIFA_CE2CFG_R_ENABLE_MASK) |
                  (CSL_EMIFA_CE2CFG_W_LTNCY_MASK) |
                  (CSL_EMIFA_CE2CFG_R_LTNCY_MASK) |
                  (CSL_EMIFA_CE2CFG_SBSIZE_MASK)); 

        for (loop = 0; loop < NUMCHIPENABLE; loop++) {
            if (setup->ceCfg[loop] != NULL) {
                if ((setup->ceCfg[loop]->ssel == 0) && 
                    (setup->ceCfg[loop]->async != NULL)) {

                    CSL_FINS(*(ceCfgBaseAddr + loop), EMIFA_CE2CFG_SSEL, 
                             CSL_EMIFA_CE2CFG_SSEL_ASYNCMEM);
                    *(ceCfgBaseAddr + loop) = (*(ceCfgBaseAddr + loop) & mask1) |
                            (CSL_FMK(EMIFA_CE2CFG_SS, 
                                setup->ceCfg[loop]->async->selectStrobe)) |
                            (CSL_FMK(EMIFA_CE2CFG_BWEM, 
                                setup->ceCfg[loop]->async->weMode)) |
                            (CSL_FMK(EMIFA_CE2CFG_AE, 
                                setup->ceCfg[loop]->async->asyncRdyEn)) |
                            (CSL_FMK(EMIFA_CE2CFG_W_SETUP, 
                                setup->ceCfg[loop]->async->wSetup)) |
                            (CSL_FMK(EMIFA_CE2CFG_W_STROBE, 
                                setup->ceCfg[loop]->async->wStrobe)) |
                            (CSL_FMK(EMIFA_CE2CFG_W_HOLD, 
                                setup->ceCfg[loop]->async->wHold)) |
                            (CSL_FMK(EMIFA_CE2CFG_R_SETUP, 
                                setup->ceCfg[loop]->async->rSetup)) |
                            (CSL_FMK(EMIFA_CE2CFG_R_STROBE, 
                                setup->ceCfg[loop]->async->rStrobe)) |
                            (CSL_FMK(EMIFA_CE2CFG_R_HOLD, 
                                setup->ceCfg[loop]->async->rHold)) |
                            (CSL_FMK(EMIFA_CE2CFG_ASIZE, 
                                setup->ceCfg[loop]->async->asize));
                }
                else {
                    if ((setup->ceCfg[loop]->ssel == 1) && 
                        (setup->ceCfg[loop]->sync != NULL)) {

                        CSL_FINS(*(ceCfgBaseAddr + loop), EMIFA_CE2CFG_SSEL, 
                                 CSL_EMIFA_CE2CFG_SSEL_SYNCMEM);
                        *(ceCfgBaseAddr + loop) = (*(ceCfgBaseAddr + loop) & mask2)|
                            (CSL_FMK(EMIFA_CE2CFG_RD_BE_EN, 
                                setup->ceCfg[loop]->sync->readByteEn)) |
                            (CSL_FMK(EMIFA_CE2CFG_CE_EXT, 
                                setup->ceCfg[loop]->sync->chipEnExt)) |
                            (CSL_FMK(EMIFA_CE2CFG_R_ENABLE, 
                                setup->ceCfg[loop]->sync->readEn)) |
                            (CSL_FMK(EMIFA_CE2CFG_W_LTNCY, 
                                setup->ceCfg[loop]->sync->w_ltncy)) |
                            (CSL_FMK(EMIFA_CE2CFG_R_LTNCY, 
                                setup->ceCfg[loop]->sync->r_ltncy)) |
                            (CSL_FMK(EMIFA_CE2CFG_SBSIZE, 
                                setup->ceCfg[loop]->sync->sbsize));      
                    }     
                    else {
                        status = CSL_ESYS_FAIL;
                    }
                }
            }
        }
    }
    
    return (status);
}

