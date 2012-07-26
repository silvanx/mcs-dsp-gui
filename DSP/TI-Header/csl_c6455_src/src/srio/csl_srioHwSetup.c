/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */
/** ===========================================================================
 * @file csl_srioHwSetup.c
 *
 * @brief File for functional layer of CSL API CSL_srioHwSetup()
 * 
 * @path $(CSLPATH)\src\srio
 *
 * @desc The CSL_srioHwSetup() function definition and it's associated
 *       functions 
 * ============================================================================
 */
/* ============================================================================
 * Revision History
 * ===============
 * 25-Aug-2005 PSK File Created.
 * 15-Dec-2005 SD  Updated the SERDES configuration.  
 * 09-Aug-2006 NG  Moved the GBL_EN & BLK_ENABLE before setting PER_SET_CNTL.
 * ============================================================================
 */
#include <csl_srio.h>
#include <csl_srioAux.h>

/** ============================================================================
 *   @n@b CSL_srioHwSetup
 *
 *   @b Description
 *   @n It configures the  SRIO instance registers as per the values passed
 *      in the hardware setup structure.
 *
 *   @b Arguments
 *   @verbatim
            hSrio            Handle to the SRIO instance

            setup            Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Hardware structure is not
 *                                                properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The specified instance will be setup according to value passed
 *
 *   @b Modifies
 *   @n Hardware registers for the specified instance
 *
 *   @b Example
 *   @verbatim
         CSL_SrioHandle         hSrio;
         CSL_SrioObj            srioObj;
         CSL_SrioHwSetup        hwSetup;
         CSL_Status             status;
         CSL_SrioControlSetup periSetup;     
         CSL_SrioBlkEn          blockSetup;
         CSL_SrioPktFwdCntl     pktFwdSetup;

         hwSetup.perEn = TRUE;
         periSetup.swMemSleepOverride = FALSE;
         periSetup.loopback = FALSE;
         . . .
         periSetup.prescalar = CSL_SRIO_CLK_PRESCALE_0;
         hwSetup.periCntlSetup = &periSetup;
         hwSetup.blkEn = &blockSetup;
         hwSetup.pktFwdCntl = &pktfwdSetup;
         ...
         
         hSrio = CSL_srioOpen (&srioObj, CSL_SRIO, NULL, &status);
         
         ...
         
         status = CSL_srioHwSetup(hSrio, &hwSetup);     

         ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION(CSL_srioHwSetup, ".text:csl_section:srio");
CSL_Status  CSL_srioHwSetup (
    CSL_SrioHandle  hSrio,
    CSL_SrioHwSetup *hwSetup
)
{
    Uint32 i;
    CSL_Status status = CSL_SOK;

    if (hSrio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* global enable setup */
        CSL_FINS(hSrio->regs->GBL_EN, SRIO_GBL_EN_EN, hwSetup->gblEn);

        /* block enable setup */
        for (i = 0; i < CSL_SRIO_BLOCKS_MAX; i++) {
            CSL_FINS(hSrio->regs->BLK_ENABLE[i].BLK_EN, SRIO_BLK_EN_EN, 
                     hwSetup->blkEn[i]);
        }

        /* sets up the PER_SET_CNTL register */
        hSrio->regs->PER_SET_CNTL = 
                        CSL_FMK(SRIO_PER_SET_CNTL_SW_MEM_SLEEP_OVERRIDE, \
                                hwSetup->periCntlSetup.swMemSleepOverride) |
                        CSL_FMK( SRIO_PER_SET_CNTL_LOOPBACK, \
                                 hwSetup->periCntlSetup.loopback) |
                        CSL_FMK(SRIO_PER_SET_CNTL_BOOT_COMPLETE, \
                                hwSetup->periCntlSetup.bootComplete) |
                        CSL_FMK(SRIO_PER_SET_CNTL_TX_PRI2_WM, \
                                hwSetup->periCntlSetup.txPriority2Wm) |
                        CSL_FMK(SRIO_PER_SET_CNTL_TX_PRI1_WM, \
                                hwSetup->periCntlSetup.txPriority1Wm) |
                        CSL_FMK(SRIO_PER_SET_CNTL_TX_PRI0_WM, \
                                hwSetup->periCntlSetup.txPriority0Wm) |
                        CSL_FMK(SRIO_PER_SET_CNTL_CBA_TRANS_PRI, \
                                hwSetup->periCntlSetup.busTransPriority) |
                        CSL_FMK(SRIO_PER_SET_CNTL_1X_MODE, \
                                hwSetup->periCntlSetup.bufferMode) |
                        CSL_FMK(SRIO_PER_SET_CNTL_PRESCALER_SELECT, \
                                hwSetup->periCntlSetup.prescalar) |
                        CSL_FMKR(3, 0, hwSetup->periCntlSetup.pllEn);

        /* the device ids setup */
        hSrio->regs->DEVICEID_REG1 = hwSetup->deviceId1;
        hSrio->regs->DEVICEID_REG2 = hwSetup->deviceId2;

        /* hardware packet forwading registers setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            CSL_FINS(hSrio->regs->HW_PKT_FWD[i].PF_16BIT_CNTL, 
                     SRIO_PF_16BIT_CNTL_16BIT_DEVID_UP_BOUND, 
                     hwSetup->pktFwdCntl[i].largeUpBoundDevId);

            CSL_FINS(hSrio->regs->HW_PKT_FWD[i].PF_16BIT_CNTL, 
                     SRIO_PF_16BIT_CNTL_16BIT_DEVID_LOW_BOUND,
                     hwSetup->pktFwdCntl[i].largeLowBoundDevId);

            CSL_FINS(hSrio->regs->HW_PKT_FWD[i].PF_8BIT_CNTL, 
                     SRIO_PF_8BIT_CNTL_OUT_BOUND_PORT, 
                     hwSetup->pktFwdCntl[i].outBoundPort);

            CSL_FINS(hSrio->regs->HW_PKT_FWD[i].PF_8BIT_CNTL, 
                     SRIO_PF_8BIT_CNTL_8BIT_DEVID_UP_BOUND,
                     hwSetup->pktFwdCntl[i].smallUpBoundDevId);

            CSL_FINS(hSrio->regs->HW_PKT_FWD[i].PF_8BIT_CNTL, 
                     SRIO_PF_8BIT_CNTL_8BIT_DEVID_LOW_BOUND, 
                     hwSetup->pktFwdCntl[i].smallLowBoundDevId);
        }

        /* SERDES PLL configuration setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            if (hwSetup->serDesPllCfg[i].pllEnable) {
                /* Configure the loop bandwidth */
                CSL_FINS (hSrio->regs->SERDES_CFG_CNTL[i], 
                    SRIO_SERDES_CFG_CNTL_LB, 
                    hwSetup->serDesPllCfg[i].loopBandwidth);

                /* Configure the multiplication factor */
                CSL_FINS (hSrio->regs->SERDES_CFG_CNTL[i], 
                    SRIO_SERDES_CFG_CNTL_MPY, 
                    hwSetup->serDesPllCfg[i].pllMplyFactor);

                /* Enable the internal PLL*/
                CSL_FINST (hSrio->regs->SERDES_CFG_CNTL[i], 
                    SRIO_SERDES_CFG_CNTL_ENPLL, ENABLE);
            }
        }

        /* SERDES RX channel enable setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            if (hwSetup->serDesRxChannelCfg [i].enRx) {
                /* Configure the bus width */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_BUSWIDTH, 
                         hwSetup->serDesRxChannelCfg [i].busWidth);

                /* Configure the operating rate */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_RATE, 
                         hwSetup->serDesRxChannelCfg [i].rate);

                /* Configure the polarity */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_INVPAIR, 
                         hwSetup->serDesRxChannelCfg [i].invertedPolarity);

                /* Configure the termination */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_TERM, 
                         hwSetup->serDesRxChannelCfg [i].termination);

                /* Configure the symbol alignment */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_ALIGN, 
                         hwSetup->serDesRxChannelCfg [i].symAlign);

                /* Configure the loss of signal detection */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_LOS, 
                         hwSetup->serDesRxChannelCfg [i].los);

                /* Configure the clock and data recovery algorithm */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_CDR, 
                         hwSetup->serDesRxChannelCfg [i].clockDataRecovery);

                /* Configure the adaptive equalizer */
                CSL_FINS(hSrio->regs->SERDES_CFGRX_CNTL[i], 
                         SRIO_SERDES_CFGRX_CNTL_EQ, 
                         hwSetup->serDesRxChannelCfg [i].equalizer);

                /* Enable the receiver */
                CSL_FINST(hSrio->regs->SERDES_CFGRX_CNTL[i],
                          SRIO_SERDES_CFGRX_CNTL_ENRX, ENABLE);
            }
        }

        /* SERDES TX channel enable setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            if (hwSetup->serDesTxChannelCfg [i].enTx) {
                /* Configure the bus width */
                CSL_FINS (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_BUSWIDTH,
                    hwSetup->serDesTxChannelCfg [i].busWidth);

                /* Configure the operating rate */
                CSL_FINS (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_RATE,
                    hwSetup->serDesTxChannelCfg [i].rate);

                /* Configure the polarity */
                CSL_FINS (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_INVPAIR,
                    hwSetup->serDesTxChannelCfg [i].invertedPolarity);

                /* Configure the common mode */
                CSL_FINS (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_CM,
                    hwSetup->serDesTxChannelCfg [i].commonMode);

                /* Configure the output swing */
                CSL_FINS (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_SWING,
                    hwSetup->serDesTxChannelCfg [i].outputSwing);

                /* Configure the output de-emphasis */
                CSL_FINS (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_DE,
                    hwSetup->serDesTxChannelCfg [i].outputDeEmphasis);

                /* Enable/disable the fixed phase */
                CSL_FINS (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_ENFTP,
                    hwSetup->serDesTxChannelCfg [i].enableFixedPhase);

                /* Enable the transmitter */
                CSL_FINST (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_ENTX, ENABLE);
            }
        }

        /* flow control setup */
        for (i = 0; i < CSL_SRIO_FLOW_CONTROL_REG_MAX; i++) {
            CSL_FINS(hSrio->regs->FLOW_CNTL[i], SRIO_FLOW_CNTL_TT, 
                                                hwSetup->flowCntlIdLen[i]);
            CSL_FINS(hSrio->regs->FLOW_CNTL[i], SRIO_FLOW_CNTL_FLOW_CNTL_ID, 
                                                hwSetup->flowCntlId[i]);
        }

        /* the processing element address bits setup */
        hSrio->regs->PE_LL_CTL = hwSetup->peLlAddrCtrl;

        /* Base device configuration */
        CSL_FINS(hSrio->regs->BASE_ID, SRIO_BASE_ID_BASE_DEVICEID, 
                                       hwSetup->devIdSetup.smallTrBaseDevId);

        CSL_FINS(hSrio->regs->BASE_ID, SRIO_BASE_ID_LARGE_BASE_DEVICEID, 
                                       hwSetup->devIdSetup.largeTrBaseDevId);

        CSL_FINS(hSrio->regs->HOST_BASE_ID_LOCK, 
                 SRIO_HOST_BASE_ID_LOCK_HOST_BASE_DEVICEID, 
                 hwSetup->devIdSetup.hostBaseDevId);

        /* Software defined component Tag for PE (processing element) setup */
        hSrio->regs->COMP_TAG = hwSetup->componentTag;


        /* Port General configuration */
        CSL_FINS(hSrio->regs->SP_LT_CTL, SRIO_SP_LT_CTL_TIMEOUT_VALUE, 
                 hwSetup->portGenSetup.portLinkTimeout);

        CSL_FINS(hSrio->regs->SP_RT_CTL, SRIO_SP_RT_CTL_TIMEOUT_VALUE, 
                 hwSetup->portGenSetup.portRespTimeout);

        CSL_FINS(hSrio->regs->SP_GEN_CTL, SRIO_SP_GEN_CTL_HOST, 
                 hwSetup->portGenSetup.hostEn);

        CSL_FINS(hSrio->regs->SP_GEN_CTL, SRIO_SP_GEN_CTL_MASTER_ENABLE, 
                 hwSetup->portGenSetup.masterEn);

        /* port control configuration */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_PORT_DISABLE, 
                     hwSetup->portCntlSetup[i].portDis);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, 
                     SRIO_SP_CTL_OUTPUT_PORT_ENABLE, 
                     hwSetup->portCntlSetup[i].outPortEn);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, 
                     SRIO_SP_CTL_INPUT_PORT_ENABLE, 
                     hwSetup->portCntlSetup[i].inPortEn);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, 
                     SRIO_SP_CTL_PORT_WIDTH_OVERRIDE, 
                     hwSetup->portCntlSetup[i].portWidthOverride);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, 
                     SRIO_SP_CTL_ERROR_CHECK_DISABLE,
                     hwSetup->portCntlSetup[i].errCheckDis);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, 
                     SRIO_SP_CTL_MULTICAST_PARTICIPANT, 
                     hwSetup->portCntlSetup[i].multicastRcvEn);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, 
                     SRIO_SP_CTL_STOP_PORT_FLD_ENC_ENABLE,
                     hwSetup->portCntlSetup[i].stopOnPortFailEn);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, 
                     SRIO_SP_CTL_DROP_PACKET_ENABLE,
                     hwSetup->portCntlSetup[i].dropPktEn);

            CSL_FINS(hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_PORT_LOCKOUT, 
                     hwSetup->portCntlSetup[i].portLockoutEn); 
        }

        /* logical/transport layer errors setup */
        hSrio->regs->ERR_EN = hwSetup->lgclTransErrEn;

        /* port error configuration */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->PORT_ERROR[i].SP_RATE_EN = 
                                       hwSetup->portErrSetup[i].portErrRateEn;

            CSL_FINS(hSrio->regs->PORT_ERROR[i].SP_ERR_RATE, 
                     SRIO_SP_ERR_RATE_ERROR_RATE_BIAS,
                     hwSetup->portErrSetup[i].prtErrRtBias);

            CSL_FINS(hSrio->regs->PORT_ERROR[i].SP_ERR_RATE, 
                     SRIO_SP_ERR_RATE_ERROR_RATE_RECOVERY, 
                     hwSetup->portErrSetup[i].portErrRtRec);

            CSL_FINS(hSrio->regs->PORT_ERROR[i].SP_ERR_THRESH, 
                     SRIO_SP_ERR_THRESH_ERROR_RATE_FAILED_THRESHOLD,
                     hwSetup->portErrSetup[i].portErrRtFldThresh);

            CSL_FINS(hSrio->regs->PORT_ERROR[i].SP_ERR_THRESH, 
                     SRIO_SP_ERR_THRESH_ERROR_RATE_DEGRADED_THRES, 
                     hwSetup->portErrSetup[i].portErrRtDegrdThresh);
        }

        /* the discovery timer value setup */
        CSL_FINS(hSrio->regs->SP_IP_DISCOVERY_TIMER, 
                 SRIO_SP_IP_DISCOVERY_TIMER_DISCOVERY_TIMER, 
                 hwSetup->discoveryTimer);

        /* port write timer value setup */
        CSL_FINS(hSrio->regs->SP_IP_DISCOVERY_TIMER, 
                 SRIO_SP_IP_DISCOVERY_TIMER_PW_TIMER, 
                 hwSetup->pwTimer);

        /* configuration of SP_IP_MODE register */
        hSrio->regs->SP_IP_MODE = hwSetup->portIpModeSet;

        /* configuration of SP_IP_PRESCALE register */
        CSL_FINS(hSrio->regs->IP_PRESCAL, SRIO_IP_PRESCAL_PRESCALE, 
                 hwSetup->portIpPrescalar);

        /* setups for silence timer and Port control independent error
         * register
         */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            CSL_FINS(hSrio->regs->PORT_OPTION[i].SP_SILENCE_TIMER, 
                     SRIO_SP_SILENCE_TIMER_SILENCE_TIMER, 
                     hwSetup->silenceTimer[i]);

            hSrio->regs->PORT_OPTION[i].SP_CTL_INDEP = 
                                        hwSetup->portCntlIndpEn[i];
        }

        /* Enable the peripheral */
        CSL_FINS(hSrio->regs->PCR, SRIO_PCR_PEREN, hwSetup->perEn);
    }
    return (status);
}

