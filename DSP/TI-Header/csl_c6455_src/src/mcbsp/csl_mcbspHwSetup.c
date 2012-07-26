/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspHwSetup.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspHwSetup()
 *
 */

/*  ============================================================================
 *  Revision History
 *  ================
 *  July 04, 2005 ds       - Removed support for DX Mode. Hence removed
 *                           dxState from CSL_McbspHwSetup 
 *                         - Removed support for enhanced sample clock mode
 *  Feb 02 , 2006 ds       - Supported the Transmit & Receive Int Mode
 *  ============================================================================ 
 */

#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspHwSetup
 *
 *   @b Description
 *   @n Configures the MCBSP using the values passed in the setup structure.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            setup           Pointer to setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status 
 *   @li                    CSL_SOK            - Hwsetup successful
 *   @li                    CSL_ESYS_INVPARAMS - The param passed is invalid
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspHwSetup() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  Mcbsp registers are configured according to the hardware setup 
 *       parameters
 *       
 *   @b Modifies
 *   @n MCBSP registers
 *
 *   @b Example
 *   @verbatim
            CSL_mcbspHandle     hMcbsp;
            CSL_McbspObj        mcbspObj;
            CSL_McbspHwSetup    hwSetup = CSL_MCBSP_HWSETUP_DEFAULTS;
            CSL_Status          status;
            
            // Init Successfully done
            CSL_mcbspInit (NULL);
            
            // Open Successfully done
            hMcbsp = CSL_mcbspOpen (&mcbspObj, CSL_MCBSP_0, NULL, &status);
            
            CSL_mcbspHwSetup(hMcbsp, &hwSetup);
            ...

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspHwSetup, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspHwSetup (
    CSL_McbspHandle     hMcbsp,
    CSL_McbspHwSetup    *setup
)
{
    CSL_Status        status    = CSL_SOK;
    CSL_McbspRegsOvly mcbspRegs =  hMcbsp->regs; 
    
    if(setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else if (hMcbsp == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else {
        /* Set Emulation Mode Configuration */
        CSL_FINS(mcbspRegs->SPCR, MCBSP_SPCR_SOFT, setup->emumode );
        CSL_FINS(mcbspRegs->SPCR, MCBSP_SPCR_FREE, setup->emumode >> 1); 
    
        /*Clock and Frame Sync Configuration*/
        if(setup->clkset != NULL ) {
            CSL_McbspClkSetup clkCfg = *(setup->clkset);
    
            mcbspRegs->PCR = CSL_FMK( MCBSP_PCR_FSRM, clkCfg.frmSyncRxMode)
                             | CSL_FMK( MCBSP_PCR_FSXM, clkCfg.frmSyncTxMode)
                             | CSL_FMK( MCBSP_PCR_FSRP, clkCfg.frmSyncRxPolarity)
                             | CSL_FMK( MCBSP_PCR_FSXP, clkCfg.frmSyncTxPolarity)
                             | CSL_FMK( MCBSP_PCR_CLKRM, clkCfg.clkRxMode )
                             | CSL_FMK( MCBSP_PCR_CLKXM, clkCfg.clkTxMode )
                             | CSL_FMK( MCBSP_PCR_CLKRP, clkCfg.clkRxPolarity )
                             | CSL_FMK( MCBSP_PCR_CLKXP, clkCfg.clkTxPolarity);
                    
            mcbspRegs->SRGR = CSL_FMK( MCBSP_SRGR_FWID, clkCfg.srgFrmPulseWidth)
                          | CSL_FMK( MCBSP_SRGR_CLKGDV, clkCfg.srgClkDivide)
                          | CSL_FMK( MCBSP_SRGR_FPER, clkCfg.srgFrmPeriod)
                          | CSL_FMK( MCBSP_SRGR_GSYNC, clkCfg.srgClkSync)
                          | CSL_FMK( MCBSP_SRGR_CLKSM, clkCfg.srgInputClkMode)
                          | CSL_FMK( MCBSP_SRGR_CLKSP, clkCfg.srgClkPolarity )
                          | CSL_FMK( MCBSP_SRGR_FSGM, clkCfg.srgTxFrmSyncMode);
             
        }
    
        /*McBSP Global Configuration*/
        if(setup->global!= NULL) {
            CSL_McbspGlobalSetup globalCfg = *(setup->global);
            CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_DLB, globalCfg.dlbMode );
            CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_CLKSTP, globalCfg.clkStopMode);
            CSL_FINS( mcbspRegs->PCR, MCBSP_PCR_RIOEN, globalCfg.ioEnableMode & 0x1);
            CSL_FINS( mcbspRegs->PCR, MCBSP_PCR_XIOEN, globalCfg.ioEnableMode >> 1 );
    
        }
    
        /*Transmitter Configuration*/
        if(setup->txdataset != NULL) {
            CSL_McbspDataSetup transmitterCfg = *(setup->txdataset);
            CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_XRST, 0 );
           
            mcbspRegs->XCR = CSL_FMK( MCBSP_XCR_XWDLEN1, transmitterCfg.wordLength1)
                     | CSL_FMK( MCBSP_XCR_XWDREVRS,transmitterCfg.wordReverse)
                     | CSL_FMK( MCBSP_XCR_XPHASE, transmitterCfg.numPhases )                         
                     | CSL_FMK( MCBSP_XCR_XWDLEN2, transmitterCfg.wordLength2)
                     | CSL_FMK( MCBSP_XCR_XFRLEN2,(transmitterCfg.frmLength2 - 1))
                     | CSL_FMK( MCBSP_XCR_XFIG, transmitterCfg.frmSyncIgn )
                     | CSL_FMK( MCBSP_XCR_XCOMPAND, transmitterCfg.compand )
                     | CSL_FMK( MCBSP_XCR_XDATDLY, transmitterCfg.dataDelay );
                    
            CSL_FINS(mcbspRegs->XCR, MCBSP_XCR_XFRLEN1, \
                     (transmitterCfg.frmLength1 - 1));         
            CSL_FINS(mcbspRegs->SPCR, MCBSP_SPCR_DXENA, \
                      transmitterCfg.rjust_dxenable);
            CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_XINTM, transmitterCfg.intEvent );
            
        }
    
        /*Receiver Configuration*/
        if(setup->rxdataset != NULL) {
            CSL_McbspDataSetup receiverCfg = *(setup->rxdataset);
            CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_RRST, 0 );
            mcbspRegs->RCR = CSL_FMK( MCBSP_RCR_RWDLEN1, receiverCfg.wordLength1 )
                         | CSL_FMK( MCBSP_RCR_RWDREVRS, receiverCfg.wordReverse)
                         | CSL_FMK( MCBSP_RCR_RPHASE, receiverCfg.numPhases )
                         | CSL_FMK( MCBSP_RCR_RWDLEN2, receiverCfg.wordLength2 )
                         | CSL_FMK( MCBSP_RCR_RFRLEN2, (receiverCfg.frmLength2 - 1))
                         | CSL_FMK( MCBSP_RCR_RFIG, receiverCfg.frmSyncIgn )
                         | CSL_FMK( MCBSP_RCR_RCOMPAND, receiverCfg.compand )
                         | CSL_FMK( MCBSP_RCR_RDATDLY, receiverCfg.dataDelay );
    
            CSL_FINS(mcbspRegs->RCR, MCBSP_RCR_RFRLEN1, \
                     (receiverCfg.frmLength1 - 1) );         
            CSL_FINS(mcbspRegs->SPCR, MCBSP_SPCR_RJUST, \
                     receiverCfg.rjust_dxenable );
            CSL_FINS( mcbspRegs->SPCR, MCBSP_SPCR_RINTM, receiverCfg.intEvent);        
        }
    
        /* Multi Channel Configuration */
        if(setup->mulCh != NULL) {
            CSL_McbspMulChSetup multiChCfg = *(setup->mulCh);
            mcbspRegs->MCR = CSL_FMK( MCBSP_MCR_RMCM, multiChCfg.rxMulChSel)
                             | CSL_FMK( MCBSP_MCR_RMCME, multiChCfg.rxPartition)
                             | CSL_FMK( MCBSP_MCR_RPABLK, multiChCfg.rxPartABlk)
                             | CSL_FMK( MCBSP_MCR_RPBBLK, multiChCfg.rxPartBBlk)                  
                             | CSL_FMK( MCBSP_MCR_XMCM, multiChCfg.txMulChSel) 
                             | CSL_FMK( MCBSP_MCR_XMCME, multiChCfg.txPartition)
                             | CSL_FMK( MCBSP_MCR_XPABLK, multiChCfg.txPartABlk)
                             | CSL_FMK( MCBSP_MCR_XPBBLK, multiChCfg.txPartBBlk);       
        }  
    }

    return(status);
}
