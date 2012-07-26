/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * =============================================================================
 */
/** ===========================================================================
 * @file csl_srioGetHwSetup.c
 *
 * @brief File for functional layer of CSL API CSL_srioGetHwSetup() 
 * 
 * @path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioGetHwSetup() function definition and it's associated 
 *       functions
 * ============================================================================
 */       
/* ============================================================================
 * Revision History
 * ===============
 * 25-Aug-2005 PSK File Created.
 * 15-Dec-2005 SD  Updated the SERDES configuration.  
 * ============================================================================
 */
#include <csl_srio.h>

/** ============================================================================
 *   @n@b CSL_srioGetHwSetup
 *
 *   @b Description
 *   @n It retrives the hardware setup parameters
 *
 *   @b Arguments
 *   @verbatim
            hSrio           Handle to the SRIO instance

            hwSetup         Pointer to hardware setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hardware setup retrived
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The hardware set up structure will be populated with values from
 *       the registers
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_status          status;
        CSL_SrioHwSetup     hwSetup;
        
        ...
        
        status = CSL_srioGetHwsetup(hSrio, &hwSetup);
        
        ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (CSL_srioGetHwSetup, ".text:csl_section:srio");
CSL_Status CSL_srioGetHwSetup (
    CSL_SrioHandle     hSrio,
    CSL_SrioHwSetup    *hwSetup
)
{
    int i;
    CSL_Status status = CSL_SOK;

    if (hSrio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (hwSetup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* Get the peripheral enable/disable setup */
        hwSetup->perEn = (Bool)CSL_FEXT(hSrio->regs->PCR, SRIO_PCR_PEREN);

        /* Get the sleep/awake mode of memories while shut down */
        hwSetup->periCntlSetup.swMemSleepOverride = 
                    (Bool)CSL_FEXT(hSrio->regs->PER_SET_CNTL, 
                          SRIO_PER_SET_CNTL_SW_MEM_SLEEP_OVERRIDE);

        /* Get the mode of operation, loopback/normal */
        hwSetup->periCntlSetup.loopback = 
            (Bool)CSL_FEXT(hSrio->regs->PER_SET_CNTL, 
            SRIO_PER_SET_CNTL_LOOPBACK);

        /* Get the setup of control ability to write any register during
         * initialization
         */
        hwSetup->periCntlSetup.bootComplete = 
         (Bool)CSL_FEXT(hSrio->regs->PER_SET_CNTL, 
                        SRIO_PER_SET_CNTL_BOOT_COMPLETE);

        /* get the setup of logical layer tx buffers needed to send the 
         * priority 2 packets
         */
        hwSetup->periCntlSetup.txPriority2Wm = (CSL_SrioTxPriorityWm)CSL_FEXT(
                 hSrio->regs->PER_SET_CNTL, SRIO_PER_SET_CNTL_TX_PRI2_WM);

        /* get the setup of logical layer tx buffers needed to send the 
         * priority 1 packets
         */
        hwSetup->periCntlSetup.txPriority1Wm = (CSL_SrioTxPriorityWm)CSL_FEXT(
                 hSrio->regs->PER_SET_CNTL, SRIO_PER_SET_CNTL_TX_PRI1_WM);

        /* get the setup of logical layer tx buffers needed to send the 
         * priority 0 packets
         */
        hwSetup->periCntlSetup.txPriority0Wm = (CSL_SrioTxPriorityWm)CSL_FEXT(
                 hSrio->regs->PER_SET_CNTL, SRIO_PER_SET_CNTL_TX_PRI0_WM);

        /* gwt Internal BUS transaction priority setup */
        hwSetup->periCntlSetup.busTransPriority = 
                 (CSL_SrioBusTransPriority)CSL_FEXT(hSrio->regs->PER_SET_CNTL, 
                  SRIO_PER_SET_CNTL_CBA_TRANS_PRI);

        /* get UDI buffering setup (priority versus port) setup */
        hwSetup->periCntlSetup.bufferMode = (CSL_SrioBufMode)CSL_FEXT(
                        hSrio->regs->PER_SET_CNTL, SRIO_PER_SET_CNTL_1X_MODE);

        /* get Internal clock frequency pre-scalar setup */
        hwSetup->periCntlSetup.prescalar = (CSL_SrioClkDiv)CSL_FEXT(
                hSrio->regs->PER_SET_CNTL, SRIO_PER_SET_CNTL_PRESCALER_SELECT);

        /* get pllc settings */
        hwSetup->periCntlSetup.pllEn = (Uint8)CSL_FEXTR(
                 hSrio->regs->PER_SET_CNTL, 3, 0);

        /* get global enable setup */
        hwSetup->gblEn = (Bool)CSL_FEXT(hSrio->regs->GBL_EN, SRIO_GBL_EN_EN);

        /* get block enable setup */
        for (i = 0; i < CSL_SRIO_BLOCKS_MAX; i++) {
            hwSetup->blkEn[i] = CSL_FEXT(hSrio->regs->BLK_ENABLE[i].BLK_EN, 
                                                            SRIO_BLK_EN_EN);
        }

        /* get the device ids setup */
        hwSetup->deviceId1 = hSrio->regs->DEVICEID_REG1;
        hwSetup->deviceId2 = hSrio->regs->DEVICEID_REG2;

        /* get the hardware packet forwading registers setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hwSetup->pktFwdCntl[i].largeUpBoundDevId = CSL_FEXT(
                        hSrio->regs->HW_PKT_FWD[i].PF_16BIT_CNTL, 
                              SRIO_PF_16BIT_CNTL_16BIT_DEVID_UP_BOUND);

            hwSetup->pktFwdCntl[i].largeLowBoundDevId = CSL_FEXT(
                        hSrio->regs->HW_PKT_FWD[i].PF_16BIT_CNTL, 
                               SRIO_PF_16BIT_CNTL_16BIT_DEVID_LOW_BOUND);

            hwSetup->pktFwdCntl[i].outBoundPort = (CSL_SrioPortNum)CSL_FEXT(
                        hSrio->regs->HW_PKT_FWD[i].PF_8BIT_CNTL, 
                               SRIO_PF_8BIT_CNTL_OUT_BOUND_PORT);

            hwSetup->pktFwdCntl[i].smallUpBoundDevId = CSL_FEXT(
                        hSrio->regs->HW_PKT_FWD[i].PF_8BIT_CNTL, 
                                SRIO_PF_8BIT_CNTL_8BIT_DEVID_UP_BOUND);

            hwSetup->pktFwdCntl[i].smallLowBoundDevId = CSL_FEXT(
                                hSrio->regs->HW_PKT_FWD[i].PF_8BIT_CNTL, 
                                 SRIO_PF_8BIT_CNTL_8BIT_DEVID_LOW_BOUND);
        }

        /* SERDES PLL configuration setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            /* Get the enable pll configuration */
            hwSetup->serDesPllCfg[i].pllEnable = 
                CSL_FEXT (hSrio->regs->SERDES_CFG_CNTL[i], 
                    SRIO_SERDES_CFG_CNTL_ENPLL);

            if (hwSetup->serDesPllCfg[i].pllEnable) {
                /* Get the loop bandwidth configuration */
                hwSetup->serDesPllCfg[i].loopBandwidth = 
                    (CSL_SrioSerDesLoopBandwidth) CSL_FEXT (
                    hSrio->regs->SERDES_CFG_CNTL[i], 
                    SRIO_SERDES_CFG_CNTL_LB);

                /* Get the multiplication factor */
                hwSetup->serDesPllCfg[i].pllMplyFactor = 
                    (CSL_SrioSerDesPllMply) CSL_FEXT (
                    hSrio->regs->SERDES_CFG_CNTL[i], 
                    SRIO_SERDES_CFG_CNTL_MPY);
            }
        }

        /* SERDES RX channel enable setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            /* Get the receiver enabel configuration */
            hwSetup->serDesRxChannelCfg [i].enRx = 
                CSL_FEXT (hSrio->regs->SERDES_CFGRX_CNTL[i],
                SRIO_SERDES_CFGRX_CNTL_ENRX);

            if (hwSetup->serDesRxChannelCfg [i].enRx) {
                /* Get the bus width configuration */
                hwSetup->serDesRxChannelCfg [i].busWidth = 
                    (CSL_SrioSerDesBusWidth) CSL_FEXT (
                    hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_BUSWIDTH);

                /* Get the operating rate configuration */
                hwSetup->serDesRxChannelCfg [i].rate = 
                    (CSL_SrioSerDesRate) CSL_FEXT (
                    hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_RATE);

                /* Get the polarity configuration */
                hwSetup->serDesRxChannelCfg [i].invertedPolarity = 
                    CSL_FEXT (hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_INVPAIR);

                /* Get the termination configuration */
                hwSetup->serDesRxChannelCfg [i].termination = 
                    (CSL_SrioSerDesTermination) CSL_FEXT (
                    hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_TERM);

                /* Get the symbol alignment configuration */
                hwSetup->serDesRxChannelCfg [i].symAlign = 
                    (CSL_SrioSerDesSymAlignment) CSL_FEXT (
                    hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_ALIGN);

                /* Get the loss of signal detection configuration */
                hwSetup->serDesRxChannelCfg [i].los = 
                    (CSL_SrioSerDesLos) CSL_FEXT (
                    hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_LOS);

                /* Get the clock and data recovery algorithm configuration */
                hwSetup->serDesRxChannelCfg [i].clockDataRecovery = 
                    CSL_FEXT (hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_CDR);

                /* Get the adaptive equalizer configuration */
                hwSetup->serDesRxChannelCfg [i].equalizer = 
                    CSL_FEXT (hSrio->regs->SERDES_CFGRX_CNTL[i], 
                    SRIO_SERDES_CFGRX_CNTL_EQ);
            }
        }

        /* SERDES TX channel enable setup */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            /* Get the transmitter enable configuration */
            hwSetup->serDesTxChannelCfg [i].enTx = 
                CSL_FEXT (hSrio->regs->SERDES_CFGTX_CNTL[i],
                SRIO_SERDES_CFGTX_CNTL_ENTX);

            if (hwSetup->serDesTxChannelCfg [i].enTx) {
                /* Get the bus width configuration */
                hwSetup->serDesTxChannelCfg [i].busWidth = 
                    (CSL_SrioSerDesBusWidth) CSL_FEXT (
                    hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_BUSWIDTH);

                /* Get the operating rate configuration */
                hwSetup->serDesTxChannelCfg [i].rate = 
                    (CSL_SrioSerDesRate) CSL_FEXT (
                    hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_RATE);

                /* Get the polarity configuration */
                hwSetup->serDesTxChannelCfg [i].invertedPolarity = 
                    CSL_FEXT (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_INVPAIR);

                /* Get the common mode configuration */
                hwSetup->serDesTxChannelCfg [i].commonMode = 
                    (CSL_SrioSerDesCommonMode) CSL_FEXT (
                    hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_CM);

                /* Get the output swing configuration */
                hwSetup->serDesTxChannelCfg [i].outputSwing = 
                    (CSL_SrioSerDesSwingCfg) CSL_FEXT (
                    hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_SWING);

                /* Get the output de-emphasis configuration */
                hwSetup->serDesTxChannelCfg [i].outputDeEmphasis = 
                    CSL_FEXT (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_DE);

                /* Get the fixed phase configuration */
                hwSetup->serDesTxChannelCfg [i].enableFixedPhase = 
                    CSL_FEXT (hSrio->regs->SERDES_CFGTX_CNTL[i],
                    SRIO_SERDES_CFGTX_CNTL_ENFTP);
            }
        }

        /* get flow control setup */
        for (i = 0; i < CSL_SRIO_FLOW_CONTROL_REG_MAX; i++) {
            hwSetup->flowCntlIdLen[i] = (Bool)CSL_FEXT(
                     hSrio->regs->FLOW_CNTL[i], SRIO_FLOW_CNTL_TT);

            hwSetup->flowCntlId[i] = CSL_FEXT(
                     hSrio->regs->FLOW_CNTL[i], SRIO_FLOW_CNTL_FLOW_CNTL_ID);
        }

        /* get the processing element address bits setup */
        hwSetup->peLlAddrCtrl = (CSL_SrioAddrSelect)hSrio->regs->PE_LL_CTL;

        /* get Base device configuration */
        hwSetup->devIdSetup.smallTrBaseDevId = CSL_FEXT(
                 hSrio->regs->BASE_ID, SRIO_BASE_ID_BASE_DEVICEID);

        hwSetup->devIdSetup.largeTrBaseDevId = CSL_FEXT(
                 hSrio->regs->BASE_ID, SRIO_BASE_ID_LARGE_BASE_DEVICEID);

        hwSetup->devIdSetup.hostBaseDevId = CSL_FEXT(
                            hSrio->regs->HOST_BASE_ID_LOCK, 
                            SRIO_HOST_BASE_ID_LOCK_HOST_BASE_DEVICEID);

        /* get Software defined component Tag for PE (processing element) */
        hwSetup->componentTag = hSrio->regs->COMP_TAG;

        /* Port General configuration */
        hwSetup->portGenSetup.portLinkTimeout = CSL_FEXT(
                 hSrio->regs->SP_LT_CTL, SRIO_SP_LT_CTL_TIMEOUT_VALUE);

        hwSetup->portGenSetup.portRespTimeout = CSL_FEXT(
                 hSrio->regs->SP_RT_CTL, SRIO_SP_RT_CTL_TIMEOUT_VALUE);

        hwSetup->portGenSetup.hostEn = (Bool)CSL_FEXT(
                            hSrio->regs->SP_GEN_CTL, SRIO_SP_GEN_CTL_HOST);

        hwSetup->portGenSetup.masterEn = (Bool)CSL_FEXT(
                    hSrio->regs->SP_GEN_CTL, SRIO_SP_GEN_CTL_MASTER_ENABLE);

        /* get port control configuration */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hwSetup->portCntlSetup[i].portDis = (Bool)CSL_FEXT(
                        hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_PORT_DISABLE);

            hwSetup->portCntlSetup[i].outPortEn = (Bool)CSL_FEXT(
                hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_OUTPUT_PORT_ENABLE);

            hwSetup->portCntlSetup[i].inPortEn = (Bool)CSL_FEXT(
                hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_INPUT_PORT_ENABLE);

            hwSetup->portCntlSetup[i].portWidthOverride = 
                (CSL_SrioPortWidthOverride)CSL_FEXT(hSrio->regs->PORT[i].SP_CTL,
                                            SRIO_SP_CTL_PORT_WIDTH_OVERRIDE);

            hwSetup->portCntlSetup[i].errCheckDis = (Bool)CSL_FEXT(
                hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_ERROR_CHECK_DISABLE);

            hwSetup->portCntlSetup[i].multicastRcvEn = (Bool)CSL_FEXT(
                hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_MULTICAST_PARTICIPANT);

            hwSetup->portCntlSetup[i].stopOnPortFailEn = (Bool)CSL_FEXT(
                hSrio->regs->PORT[i].SP_CTL, 
                SRIO_SP_CTL_STOP_PORT_FLD_ENC_ENABLE);

            hwSetup->portCntlSetup[i].dropPktEn = (Bool)CSL_FEXT(
                hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_DROP_PACKET_ENABLE);

            hwSetup->portCntlSetup[i].portLockoutEn = (Bool)CSL_FEXT(
                hSrio->regs->PORT[i].SP_CTL, SRIO_SP_CTL_PORT_LOCKOUT);	
        }

        /* get logical/transport layer errors setup */
        hwSetup->lgclTransErrEn = hSrio->regs->ERR_EN;

        /* get port error configuration */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hwSetup->portErrSetup[i].portErrRateEn = 
                            hSrio->regs->PORT_ERROR[i].SP_RATE_EN;

            hwSetup->portErrSetup[i].prtErrRtBias = 
             (CSL_SrioErrRtBias)CSL_FEXT(hSrio->regs->PORT_ERROR[i].SP_ERR_RATE, 
                    SRIO_SP_ERR_RATE_ERROR_RATE_BIAS);

            hwSetup->portErrSetup[i].portErrRtRec = (CSL_SrioErrRtNum)CSL_FEXT(
                    hSrio->regs->PORT_ERROR[i].SP_ERR_RATE, 
                    SRIO_SP_ERR_RATE_ERROR_RATE_RECOVERY);

            hwSetup->portErrSetup[i].portErrRtFldThresh = CSL_FEXT(
                    hSrio->regs->PORT_ERROR[i].SP_ERR_THRESH, 
                    SRIO_SP_ERR_THRESH_ERROR_RATE_FAILED_THRESHOLD);

            hwSetup->portErrSetup[i].portErrRtDegrdThresh = CSL_FEXT(
                    hSrio->regs->PORT_ERROR[i].SP_ERR_THRESH, 
                    SRIO_SP_ERR_THRESH_ERROR_RATE_DEGRADED_THRES);
        }

        /* get the discovery timer value */
        hwSetup->discoveryTimer = (CSL_SrioDiscoveryTimer)CSL_FEXT(
                        hSrio->regs->SP_IP_DISCOVERY_TIMER, 
                        SRIO_SP_IP_DISCOVERY_TIMER_DISCOVERY_TIMER);

        /* get the port write timer value */
        hwSetup->pwTimer = (CSL_SrioPwTimer)CSL_FEXT(
                        hSrio->regs->SP_IP_DISCOVERY_TIMER, 
                        SRIO_SP_IP_DISCOVERY_TIMER_PW_TIMER);

        /* get The configuration of SP_IP_MODE register */
        hwSetup->portIpModeSet = hSrio->regs->SP_IP_MODE;

        /* get The configuration of SP_IP_PRESCALE register */
        hwSetup->portIpPrescalar = CSL_FEXT(hSrio->regs->IP_PRESCAL, 
                                            SRIO_IP_PRESCAL_PRESCALE);

        /* ge the setups for silence timer and Port control independent error
         * register
         */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hwSetup->silenceTimer[i] = (CSL_SrioSilenceTimer)CSL_FEXT(
                    hSrio->regs->PORT_OPTION[i].SP_SILENCE_TIMER, \
                                SRIO_SP_SILENCE_TIMER_SILENCE_TIMER);

            hwSetup->portCntlIndpEn[i] = 
                            hSrio->regs->PORT_OPTION[i].SP_CTL_INDEP;
        }
    }
    return (status);
}

