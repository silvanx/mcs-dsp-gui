/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspGetHwSetup.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspGetHwSetup()
 *
 */
 
/*  ============================================================================
 *  Revision History
 *  ================
 *  July 04, 2005 ds     - Removed support for getting DX Mode. 
 *                       - Removed support for getting enhanced sample 
 *                         clock mode
 *  Feb 02 , 2006 ds     - Supported the Transmit & Receive Int Mode
 *  ============================================================================
 */
 
#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspGetHwSetup
 *
 *   @b Description
 *   @n Gets the status of some or all of the setup-parameters of MCBSP.
 *      To get the status of complete MCBSP h/w setup, all the sub-structure
 *      pointers inside the main HwSetup structure, should be non-NULL. 
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            myHwSetup       Pointer to CSL_McbspHwSetup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status 
 *   @li                    CSL_SOK            - Get hwsetup successful
 *   @li                    CSL_ESYS_INVPARAMS - The param passed is invalid
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspGetHwSetup() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *       
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle     hMcbsp;
            CSL_Status          status;
            
            CSL_McbspGlobalSetup gblSetup;
            CSL_McbspClkSetup clkSetup;
            CSL_McbspEmu emuMode;
            CSL_McbspHwSetup readSetup = {
                &gblSetup,
                NULL,    // RX Data-setup structure if not required
                NULL,    // TX Data-setup structure if not required
                &clkSetup,
                NULL,    // Multichannel-setup structure if not required
                emuMode
            };
            ...
            status = CSL_mcbspGetHwSetup(hMcbsp, &readSetup);
   
            ...
    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspGetHwSetup, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspGetHwSetup (
    CSL_McbspHandle              hMcbsp,
    CSL_McbspHwSetup             *myHwSetup
)
{   
    Uint16            tempValue;
    CSL_Status        status    = CSL_SOK;
    CSL_McbspRegsOvly mcbspRegs = hMcbsp->regs;
    
    if (hMcbsp == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (myHwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        if (myHwSetup->global != NULL) {
        CSL_McbspGlobalSetup *gbl = myHwSetup->global;

        gbl->dlbMode = 
            (CSL_McbspDlbMode) CSL_FEXT(mcbspRegs->SPCR,MCBSP_SPCR_DLB);
        
        gbl->clkStopMode = 
            (CSL_McbspClkStp) CSL_FEXT(mcbspRegs->SPCR, MCBSP_SPCR_CLKSTP);
        
        gbl->ioEnableMode = 
            (CSL_McbspIOMode) (CSL_FEXT(mcbspRegs->PCR,MCBSP_PCR_RIOEN)
                             |(CSL_FEXT(mcbspRegs->PCR,MCBSP_PCR_XIOEN) << 1));
        }
    
        if (myHwSetup->rxdataset != NULL) {
            CSL_McbspDataSetup *data = myHwSetup->rxdataset;
            
            data->numPhases = 
                (CSL_McbspPhase) CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RPHASE);
            
            data->wordLength1 = 
                (CSL_McbspWordLen) CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RWDLEN1);
            
            data->wordLength2 = 
                (CSL_McbspWordLen) CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RWDLEN2);
            
            data->frmLength1 = CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RFRLEN1) + 1;
            
            data->frmLength2 = CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RFRLEN2) + 1; 
            
            data->frmSyncIgn = 
                (CSL_McbspFrmSync) CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RFIG);
            
            data->compand = 
                (CSL_McbspCompand) CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RCOMPAND);
                
            data->dataDelay = 
                (CSL_McbspDataDelay) CSL_FEXT(mcbspRegs->RCR, MCBSP_RCR_RDATDLY);
                
            data->rjust_dxenable = 
               (CSL_McbspRjustDxena) CSL_FEXT(mcbspRegs->SPCR, MCBSP_SPCR_RJUST);
            
            data->intEvent = (CSL_McbspIntMode) CSL_FEXT(mcbspRegs->SPCR,
                                                         MCBSP_SPCR_RINTM);
            data->wordReverse = 
                (CSL_McbspBitReversal)CSL_FEXT (mcbspRegs->RCR, MCBSP_RCR_RWDREVRS);
        }
        
        if (myHwSetup->txdataset != NULL) {
            CSL_McbspDataSetup *data = myHwSetup->txdataset;
    
            data->numPhases = 
                (CSL_McbspPhase) CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XPHASE);
                
            data->wordLength1 = 
                (CSL_McbspWordLen) CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XWDLEN1);
                
            data->wordLength2 = 
                (CSL_McbspWordLen) CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XWDLEN2);
                
            data->frmLength1 = CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XFRLEN1) + 1;
            
            data->frmLength2 = CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XFRLEN2) + 1;
            
            data->frmSyncIgn = 
                (CSL_McbspFrmSync) CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XFIG);
                
            data->compand = 
                (CSL_McbspCompand) CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XCOMPAND);
                
            data->dataDelay = 
                (CSL_McbspDataDelay) CSL_FEXT(mcbspRegs->XCR, MCBSP_XCR_XDATDLY);
                
            data->rjust_dxenable = 
               (CSL_McbspRjustDxena) CSL_FEXT(mcbspRegs->SPCR,MCBSP_SPCR_DXENA);
            
            data->intEvent = (CSL_McbspIntMode) CSL_FEXT(mcbspRegs->SPCR, 
                                                         MCBSP_SPCR_XINTM);
            data->wordReverse = 
                (CSL_McbspBitReversal)CSL_FEXT (mcbspRegs->XCR, MCBSP_XCR_XWDREVRS);                                                     
        }
        
        if (myHwSetup->clkset != NULL) {
            CSL_McbspClkSetup *clk = myHwSetup->clkset;
    
            clk->frmSyncRxMode = 
                (CSL_McbspFsClkMode) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_FSRM);
                
            clk->frmSyncTxMode = 
                (CSL_McbspFsClkMode) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_FSXM);
                
            clk->frmSyncRxPolarity = 
                (CSL_McbspFsPol) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_FSRP);
                
            clk->frmSyncTxPolarity = 
                (CSL_McbspFsPol) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_FSXP);
                
            clk->clkRxMode = 
                (CSL_McbspTxRxClkMode) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_CLKRM);
                
            clk->clkTxMode = 
                (CSL_McbspTxRxClkMode) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_CLKXM);
                
            clk->clkRxPolarity = 
                (CSL_McbspClkPol) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_CLKRP);
                
            clk->clkTxPolarity = 
                (CSL_McbspClkPol) CSL_FEXT(mcbspRegs->PCR, MCBSP_PCR_CLKXP);
             
            clk->srgFrmPulseWidth = CSL_FEXT(mcbspRegs->SRGR, MCBSP_SRGR_FWID);
            
            clk->srgFrmPeriod = CSL_FEXT(mcbspRegs->SRGR, MCBSP_SRGR_FPER);
            
            clk->srgClkDivide = CSL_FEXT(mcbspRegs->SRGR, MCBSP_SRGR_CLKGDV);
            
            clk->srgClkSync = 
                (CSL_McbspClkgSyncMode) CSL_FEXT(mcbspRegs->SRGR, MCBSP_SRGR_GSYNC);
                
            clk->srgInputClkMode = 
               (CSL_McbspSrgClk) CSL_FEXT(mcbspRegs->SRGR, MCBSP_SRGR_CLKSM);
                                  
            clk->srgClkPolarity = 
                (CSL_McbspClkPol) CSL_FEXT(mcbspRegs->SRGR, MCBSP_SRGR_CLKSP);
                
            clk->srgTxFrmSyncMode = 
               (CSL_McbspTxFsMode) CSL_FEXT(mcbspRegs->SRGR, MCBSP_SRGR_FSGM);
        }
        
        if (myHwSetup->mulCh != NULL) {
            CSL_McbspMulChSetup *mulch = myHwSetup->mulCh;
    
            mulch->rxMulChSel = CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_RMCM);
            
            mulch->txMulChSel = CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_XMCM);
            
            mulch->rxPartition = 
                (CSL_McbspPartMode) CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_RMCME);
                
            mulch->rxPartABlk = 
                (CSL_McbspPABlk) CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_RPABLK);
                
            mulch->rxPartBBlk = 
                (CSL_McbspPBBlk) CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_RPBBLK);
                
            mulch->txPartition = 
                (CSL_McbspPartMode) CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_XMCME);
                
            mulch->txPartABlk = 
                (CSL_McbspPABlk) CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_XPABLK);
                
            mulch->txPartBBlk = 
                (CSL_McbspPBBlk) CSL_FEXT(mcbspRegs->MCR, MCBSP_MCR_XPBBLK);
        }
                
        tempValue = CSL_FEXT( mcbspRegs->SPCR, MCBSP_SPCR_SOFT) 
                    |(CSL_FEXT( mcbspRegs->SPCR, MCBSP_SPCR_FREE) << 1);
                         
        if (tempValue == 3) 
            tempValue = 2;
                
        myHwSetup->emumode = (CSL_McbspEmu) tempValue;
        
        /* Extra parameters, for future use */ 
        myHwSetup->extendSetup = NULL;
    }

    return(status);
}

