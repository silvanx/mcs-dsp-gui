/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_emifaGetHwSetup.c
 *
 *  @path    $(CSLPATH)\src\emifa
 *
 *  $desc    File for functional layer of CSL API @a CSL_emifaGetHwSetup()
 *           - The @a CSL_emifaGetHwSetup() function definition & it's 
 *             associated functions
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

/** ============================================================================
 * @n@b   CSL_emifaGetHwSetup
 *
 * @b Description
 * @n This function gets the current setup of the EMIFA. The status is
 *    returned through @a CSL_EmifaHwSetup. The obtaining of status
 *    is the reverse operation of @a CSL_emifaHwSetup() function.
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
 * @li                    CSL_SOK             - Hardware status call is 
 *                                               successful
 * @li                    CSL_ESYS_FAIL      - The external memory interface 
 *                                              instance is not available.
 * @li                    CSL_ESYS_INVPARAMS - Parameters are not valid    
 * @li                    CSL_ESYS_BADHANDLE - Handle is not valid    
 *
 * <b> Pre Condition </b>
 * @n  Both @a CSL_emifaInit() and @a CSL_emifaOpen() must be called 
 *     successfully in order before calling @a CSL_emifaGetHwSetup().
 *
 * <b> Post Condition </b>
 * @n  None
 *
 * @b Modifies
 * @n Second parameter setup
 *
 * @b Example:
 * @verbatim
      CSL_EmifaHandle hEmifa;
      CSL_Status status;
      CSL_EmifaHwSetup hwSetup;      
      CSL_EmifaAsync asyncMem;
      CSL_EmifaMemType value;
      CSL_EmifaAsyncWait asyncWait;

      value.ssel = 0;
      value.async = &asyncMem;
      value.sync = NULL;      
      hwSetup.asyncWait = &asyncWait;
      hwSetup.ceCfg [0] = &value;
      hwSetup.ceCfg [1] = NULL;
      hwSetup.ceCfg [2] = NULL;
      hwSetup.ceCfg [3] = NULL;   
      
      //Initialize the Emifa CSL 
     
      //Open Emifa Module

      status = CSL_emifaGetHwSetup(hEmifa, &hwSetup);

   @endverbatim
 *
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_emifaGetHwSetup, ".text:csl_section:emifa")
CSL_Status  CSL_emifaGetHwSetup (
    CSL_EmifaHandle     hEmifa,
    CSL_EmifaHwSetup    *setup
)
{
    Uint8 loop;
    volatile Uint32* ceCfgBaseAddr=0;
    CSL_Status status = CSL_SOK;
    
    /* invalid parameter checking */
    if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else if (hEmifa == NULL) {
        /* bad handle checking */
        status = CSL_ESYS_BADHANDLE;
    }    
    else {
        /* Get Async config */
        if (setup->asyncWait != NULL) {
            setup->asyncWait->asyncRdyPol = 
                 (CSL_EmifaArdyPol)CSL_FEXT(hEmifa->regs->AWCC, EMIFA_AWCC_AP);
            setup->asyncWait->turnArnd = 
                 (Uint8)CSL_FEXT(hEmifa->regs->AWCC, EMIFA_AWCC_TA);    
            setup->asyncWait->maxExtWait = 
                 (Uint8)CSL_FEXT(hEmifa->regs->AWCC, EMIFA_AWCC_MAX_EXT_WAIT);
        }

        ceCfgBaseAddr = &(hEmifa->regs->CE2CFG);

        for (loop=0; loop < NUMCHIPENABLE; loop++) {
            if (setup->ceCfg[loop] != NULL)
            {
                if ((setup->ceCfg[loop]->ssel == 0) && 
                    (setup->ceCfg[loop]->async != NULL) &&
                    (!((Uint8)CSL_FEXT(*(ceCfgBaseAddr + loop), 
                                          EMIFA_CE2CFG_SSEL))))
                {      
                    setup->ceCfg[loop]->async->selectStrobe = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_SS);
                    setup->ceCfg[loop]->async->weMode = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_BWEM);    
                    setup->ceCfg[loop]->async->asyncRdyEn = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_AE);
                    setup->ceCfg[loop]->async->wSetup = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_W_SETUP);
                    setup->ceCfg[loop]->async->wStrobe = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_W_STROBE);    
                    setup->ceCfg[loop]->async->wHold = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_W_HOLD);
                    setup->ceCfg[loop]->async->rSetup = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_R_SETUP);
                    setup->ceCfg[loop]->async->rStrobe = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_R_STROBE);    
                    setup->ceCfg[loop]->async->rHold = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_R_HOLD);
                    setup->ceCfg[loop]->async->asize = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_ASIZE);      
                }

                if ((setup->ceCfg[loop]->ssel == 1) && 
                    (setup->ceCfg[loop]->sync != NULL) &&
                    ((Uint8)CSL_FEXT(*(ceCfgBaseAddr + loop), EMIFA_CE2CFG_SSEL)))
                {
                    setup->ceCfg[loop]->sync->readByteEn = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_RD_BE_EN);
                    setup->ceCfg[loop]->sync->chipEnExt = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_CE_EXT);    
                    setup->ceCfg[loop]->sync->readEn = (Uint8)CSL_FEXT(
                        *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_R_ENABLE);
                    setup->ceCfg[loop]->sync->w_ltncy = (Uint8)CSL_FEXT(
                            *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_W_LTNCY);
                    setup->ceCfg[loop]->sync->r_ltncy = (Uint8)CSL_FEXT(
                            *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_R_LTNCY);  
                    setup->ceCfg[loop]->sync->sbsize = (Uint8)CSL_FEXT(
                            *(ceCfgBaseAddr + loop), EMIFA_CE2CFG_SBSIZE);                
                }      
                else {
                    status = CSL_ESYS_FAIL;
                }  
            }
        }
    }
    
    return (status);
}

