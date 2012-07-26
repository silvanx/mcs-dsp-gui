/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2GetHwSetup.c
 *
 *  @path    $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2GetHwSetup()
 *           - The @a CSL_ddr2GetHwSetup() function definition & it's associated
 *             functions
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Apr-2005 RM  File Created.
 *  
 *  05-Oct-2005 NG  Updation done according to new register layer
 *  
 *  03-Feb-2006 ds  Updated according to TCI6482/C6455 user guide
 * =============================================================================
 */
#include <csl_ddr2.h>

/** ============================================================================
 * @n@b   CSL_ddr2GetHwSetup
 *
 * @b Description
 * @n This function gets the current setup of the DDR2.  The status is
 *    returned through @a CSL_Ddr2HwSetup.  The obtaining of status
 *    is the reverse operation of @a CSL_ddr2HwSetup() function.
 * 
 * @b Arguments                                                              
 * @verbatim                                                                 
            hDdr2        Handle to the external memory interface instance
			setup        Pointer to setup structure which contains the
                         information to program DDR2 to a useful state
   @endverbatim                                                              
 *                                                                             
 * <b> Return Value </b>  CSL_Status
 * @li                    CSL_SOK            - Hardware setup successful
 * @li                    CSL_ESYS_INVPARAMS - The param passed is invalid    
 * @li                    CSL_ESYS_BADHANDLE - Handle is not valid    
 *
 * <b> Pre Condition </b>
 *     Both @a CSL_ddr2Init() and @a CSL_ddr2Open() must be called successfully
 *     in order before calling @a CSL_ddr2GetHwSetup().
 *
 * <b> Post Condition </b>
 * @n  None  
 *
 * @b Modifies
 * @n Second parameter setup value
 *
 * @b Example:
 * @verbatim
      CSL_Ddr2Handle hDdr2;
      CSL_Status status;      
      CSL_Ddr2Timing1 tim1;
      CSL_Ddr2Timing2 tim2;
      CSL_Ddr2Settings set;
      CSL_Ddr2HwSetup hwSetup ;
     
     
     hwSetup.timing1Param = &tim1;
     hwSetup.timing2Param = &tim2;
     hwSetup.setParam = &set;
       ...
      status = CSL_ddr2GetHwSetup(hDdr2, &hwSetup);
   @endverbatim
 *
 *
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2GetHwSetup, ".text:csl_section:ddr2")
CSL_Status  CSL_ddr2GetHwSetup(
    CSL_Ddr2Handle     hDdr2,
    CSL_Ddr2HwSetup    *setup
)
{
    CSL_Status status = CSL_SOK;
    
    /* invalid parameter checking */
    if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else if (hDdr2 == NULL) {
    /* bad handle checking */
        status = CSL_ESYS_BADHANDLE;
    }    
    else {
        /* Get the SDRAM Refresh Rate Configuration */
        setup->refreshRate = (Uint16)CSL_FEXT(hDdr2->regs->SDRFC, 
                                     DDR2_SDRFC_REFRESH_RATE);


        /* Get the SDRAM Configuration */
        if (setup->setParam != NULL) {
            setup->setParam->casLatncy = (CSL_Ddr2CasLatency)CSL_FEXT(
                                             hDdr2->regs->SDCFG, DDR2_SDCFG_CL);
            setup->setParam->ibank = (CSL_Ddr2IntBank)CSL_FEXT(hDdr2->regs->SDCFG,
                                         DDR2_SDCFG_IBANK);   
            setup->setParam->pageSize = (CSL_Ddr2PageSize)CSL_FEXT(
                                            hDdr2->regs->SDCFG,
                                            DDR2_SDCFG_PAGESIZE);
            setup->setParam->narrowMode = (CSL_Ddr2Mode)CSL_FEXT(
                                    hDdr2->regs->SDCFG, DDR2_SDCFG_NM);
            setup->setParam->ddrDrive = (CSL_Ddr2Drive) 
                               CSL_FEXT(hDdr2->regs->SDCFG, DDR2_SDCFG_DDR_DRIVE);     
        }

        /* Get the SDRAM Timing1 Configuration */
        if(setup->timing1Param != NULL) {
            setup->timing1Param->trfc = CSL_FEXT(hDdr2->regs->SDTIM1, 
                                            DDR2_SDTIM1_T_RFC);
            setup->timing1Param->trp = CSL_FEXT(hDdr2->regs->SDTIM1, 
                                           DDR2_SDTIM1_T_RP);
            setup->timing1Param->trcd = CSL_FEXT(hDdr2->regs->SDTIM1, 
                                            DDR2_SDTIM1_T_RCD);
            setup->timing1Param->twr = CSL_FEXT(hDdr2->regs->SDTIM1, 
                                           DDR2_SDTIM1_T_WR);
            setup->timing1Param->tras = CSL_FEXT(hDdr2->regs->SDTIM1,
                                            DDR2_SDTIM1_T_RAS);
            setup->timing1Param->trc = CSL_FEXT(hDdr2->regs->SDTIM1,
                                           DDR2_SDTIM1_T_RC);
            setup->timing1Param->trrd = CSL_FEXT(hDdr2->regs->SDTIM1, 
                                           DDR2_SDTIM1_T_RRD);
            setup->timing1Param->twtr = CSL_FEXT(hDdr2->regs->SDTIM1,
                                            DDR2_SDTIM1_T_WTR);
        }

        /* Get the SDRAM Timing2 Configuration */
        if (setup->timing2Param != NULL) {    
            setup->timing2Param->todt = CSL_FEXT(hDdr2->regs->SDTIM2, 
                                             DDR2_SDTIM2_T_ODT);
            setup->timing2Param->tsxnr = CSL_FEXT(hDdr2->regs->SDTIM2,
                                             DDR2_SDTIM2_T_SXNR);
            setup->timing2Param->tsxrd = CSL_FEXT(hDdr2->regs->SDTIM2,
                                             DDR2_SDTIM2_T_SXRD);
            setup->timing2Param->trtp = CSL_FEXT(hDdr2->regs->SDTIM2,
                                            DDR2_SDTIM2_T_RTP);
            setup->timing2Param->tcke = CSL_FEXT(hDdr2->regs->SDTIM2,
                                            DDR2_SDTIM2_T_CKE);
        }
    }
    
    return (status);
}

