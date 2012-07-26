/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */

/** ===========================================================================
 *   @file Srio_lsu_example.c
 *
 *   @path  $(CSLPATH)\example\srio\src
 *
 *   @desc This is a simple lookback example of usage of CSL APIs of the 
 *         SRIO module.
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This is an example of the CSL SRIO usage for a LSU port.
 *   @verbatim
       1. Setup SRIO module for loop back transfer on LSU1.
       2. Setup the destination and source data areas.
       3. Configure LSU1 registers.
       4. Start transfer.
       5. Wait for completion of the transfer.
       6. Verify the destination contains the expected data.

     @endverbatim
 *
 *=============================================================================
 *      
 *   @n <b> Procedure </b>
 *   @verbatim
      1. Configure the CCS setup
      2. Please refer CCS manual for setup configuration and loading 
         proper GEL file
      3. Launch CCS window
      4. Open project Srio_lsu_example.pjt
      5. Build the project and load the .out file of the project.

     @endverbatim
 *       
 *   
 * ============================================================================
 */

/* ============================================================================
 * Revision History
 * ===============
 * 02-Sep-2005 Chandra File Created.
 * 19-Dec-2005 SD      Changes for the SERDES configuration 
 * ============================================================================
 */
 
#include <csl_srio.h>
#include <cslr_dev.h>
#include <soc.h>
#include <stdio.h>

/* Macros */

#define SRIO_SET_DEVICE_ID(base_dev_id, large_base_dev_id)              \
            CSL_FMK(SRIO_BASE_ID_BASE_DEVICEID, base_dev_id) |          \
            CSL_FMK(SRIO_BASE_ID_LARGE_BASE_DEVICEID, large_base_dev_id)

#define LARGE_DEV_ID 0xBEEF
#define SMALL_DEV_ID 0xAB

#define SRIO_PKT_TYPE_NWRITE 0x54
#define SELECTED_LSU 0

#define TRANSFER_SIZE 256

/* globals */
static Uint8 src[TRANSFER_SIZE];
static Uint8 dst[TRANSFER_SIZE];
static CSL_SrioHwSetup setup = CSL_SRIO_HWSETUP_DEFAULTS;

/* Function prototypes */
void srio_Create_Setup (
    CSL_SrioHwSetup *pSetup
);


/*
 * ============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine of this program which invokes the different
 *     components to complete a simple LSU transfer.
 * ============================================================================
*/
void main (
    void
)
{

    volatile Uint32 index, dummy_cnt;
    Uint8 lsu_no;

    CSL_SrioContext context;
    CSL_Status status;

    CSL_SrioHandle hSrio;
    CSL_SrioObj   srioObj;
    CSL_InstNum   srioNum = 0;  /* Instance number of the SRIO */
    CSL_SrioParam srioParam;

    CSL_SrioDirectIO_ConfigXfr lsu_conf = {0};
    CSL_SrioPortData response;

    /* Unlock the powersaver control register */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);

    /* Enable the SRIO */
    CSL_FINST (((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_SRIOCTL, 
               ENABLE);
    
    /* Initialization and Open of the SRIO */
    status = CSL_srioInit (&context);
    hSrio = CSL_srioOpen (&srioObj, srioNum, &srioParam, &status);
    if (status != CSL_SOK) {
        printf("SRIO: ... Cannot open SRIO, failed\n");
        return;
    }

    /* Create the setup structure */
    srio_Create_Setup (&setup);

    /* Setup the SRIO with the selected setup in the last step */
    status = CSL_srioHwSetup (hSrio, &setup);
    if (status != CSL_SOK) {
        printf("SRIO: ... Hardwrae setup, failed\n");
        return;
    }

    /* Setup the source and destination */
    for(index=0; index<TRANSFER_SIZE; index++) {
	    src[index] = index + 1;
	    dst[index] = 0;
	}

    /* Create an LSU configuration */
    lsu_conf.srcNodeAddr           = (Uint32)&src[0]; /* Source address */
    lsu_conf.dstNodeAddr.addressHi = 0;
    lsu_conf.dstNodeAddr.addressLo = (Uint32)&dst[0]; /* Destination address */
    lsu_conf.byteCnt               = TRANSFER_SIZE;
    lsu_conf.idSize                = 1;               /* 16 bit device id */
    lsu_conf.priority              = 2;               /* PKT priority is 2 */
    lsu_conf.xambs                 = 0;               /* Not an extended
                                                          address */
    lsu_conf.dstId                 = LARGE_DEV_ID;
    lsu_conf.intrReq               = 0;               /* No interrupts */
    lsu_conf.pktType               = SRIO_PKT_TYPE_NWRITE;
                                                      /* write with no
                                                          response */
    lsu_conf.hopCount              = 0;               /* Valid for
                                                          maintainance pkt */
    lsu_conf.doorbellInfo          = 0;               /* Not a doorbell pkt */
    lsu_conf.outPortId             = 0;               /* Tx on Port 0 */

    /* Configure the LSU1 and start transmission */
    lsu_no = SELECTED_LSU;
    CSL_srioLsuSetup (hSrio, &lsu_conf, lsu_no);

    /* Wait for the completion of transfer */
    response.index = lsu_no;
    do {
        CSL_srioGetHwStatus (hSrio, CSL_SRIO_QUERY_LSU_BSY_STAT, &response);
    }while(response.data == 1);

	/* A delay, above checks seems to be not working
	   may be because, it is a write operation with
	   no response */
	for(index=0; index<0x10000; index++) {
        dummy_cnt = index + 1;
		dummy_cnt++;
	}

    /* Verify whether data is transfered */
    for(index=0; index<TRANSFER_SIZE; index++) {
	    if (src[index] != dst[index]) {
		    break;
        }
    }
    if (index == TRANSFER_SIZE) {
	    printf("SRIO: ... LSU transfered %d bytes of data correctly\n",
	        TRANSFER_SIZE);
    } else {
	    printf("SRIO: ... LSU failed to transfer data\n");
    }
}

/*
 * ============================================================================
 *   @func   srio_Create_Setup
 *
 *   @desc
 *     This routine setsup a structure with the required setup of the SRIO.
 * ============================================================================
*/
void srio_Create_Setup (
    CSL_SrioHwSetup *pSetup
)
{
    Uint32 index;
    
    /* Peripheral enable */
    pSetup->perEn = 1;

    /* While in shutdown, put memories in sleep mode */
    pSetup->periCntlSetup.swMemSleepOverride = 1;
    
    /* Enable loopback operation */
    pSetup->periCntlSetup.loopback = 1;
    
    /* Boot process is over (complete) */
    pSetup->periCntlSetup.bootComplete = 1;
    
    /* Process TX requests of priority 2, when credit is 1 or greater */
    pSetup->periCntlSetup.txPriority2Wm = CSL_SRIO_TX_PRIORITY_WM_0;
    
    /* Process TX requests of priority 1, when credit is 1 or greater */
    pSetup->periCntlSetup.txPriority1Wm = CSL_SRIO_TX_PRIORITY_WM_0;

    /* Process TX requests of priority 0, when credit is 1 or greater */
    pSetup->periCntlSetup.txPriority0Wm = CSL_SRIO_TX_PRIORITY_WM_0;

    /* Set internal bus priority to 1 (next to lowest) */
    pSetup->periCntlSetup.busTransPriority = CSL_SRIO_BUS_TRANS_PRIORITY_1;
    
    /* UDI buffers are port based not proirity based */
    pSetup->periCntlSetup.bufferMode = CSL_SRIO_1X_MODE_PORT;
    
    /* VBUS clock is of 333 MHz  from TPCC document section 2.3 */
    pSetup->periCntlSetup.prescalar = CSL_SRIO_CLK_PRESCALE_6;
    
    /* Enable port 0 PLL */
    pSetup->periCntlSetup.pllEn = CSL_SRIO_PLL1_ENABLE; 

    /* Enable clocks to all domains */
    pSetup->gblEn = 1;

    /* Enable clock in each domain */
    for (index=0; index<9; index++) { /* 9 domains */
        pSetup->blkEn[index] = 1;    /* Enable each of it */
    }

    /* 8-bit id is 0xAB and 16-bit id is 0xBEEF */
    pSetup->deviceId1 = SRIO_SET_DEVICE_ID(SMALL_DEV_ID, LARGE_DEV_ID);

    /* 8-bit id is 0xAB and 16-bit id is 0xBEEF for multi-cast*/
    pSetup->deviceId2 = SRIO_SET_DEVICE_ID(SMALL_DEV_ID, LARGE_DEV_ID);

	/* configure the SERDES registers */

	/* SERDES PLL configuration for channel 0 */
	pSetup->serDesPllCfg[0].pllEnable = TRUE;
	pSetup->serDesPllCfg[0].pllMplyFactor = CSL_SRIO_SERDES_PLL_MPLY_BY_6;

    /* SERDES RX channel 0 enable */
    pSetup->serDesRxChannelCfg[0].enRx = TRUE; 
    pSetup->serDesRxChannelCfg[0].symAlign = CSL_SRIO_SERDES_SYM_ALIGN_COMMA; 
	pSetup->serDesRxChannelCfg[0].los = CSL_SRIO_SERDES_LOS_DET_HIGH_THRESHOLD;
	pSetup->serDesRxChannelCfg[0].clockDataRecovery = 0x01;  /* first order */
	pSetup->serDesRxChannelCfg[0].equalizer = 0x01;

    /* SERDES TX channel 0 enable */
    pSetup->serDesTxChannelCfg[0].enTx = TRUE; 
    pSetup->serDesTxChannelCfg[0].enableFixedPhase = TRUE; 
    
    /* SERDES PLL configuration for channel 1 */
	pSetup->serDesPllCfg[1].pllEnable = TRUE;
	pSetup->serDesPllCfg[1].pllMplyFactor = CSL_SRIO_SERDES_PLL_MPLY_BY_6;

    /* SERDES RX channel 1 enable */
    pSetup->serDesRxChannelCfg[1].enRx = TRUE; 
    pSetup->serDesRxChannelCfg[1].symAlign = CSL_SRIO_SERDES_SYM_ALIGN_COMMA; 
	pSetup->serDesRxChannelCfg[1].los = CSL_SRIO_SERDES_LOS_DET_HIGH_THRESHOLD;
	pSetup->serDesRxChannelCfg[1].clockDataRecovery = 0x01;  /* first order */
	pSetup->serDesRxChannelCfg[1].equalizer = 0x01;

    /* SERDES TX channel 1 enable */
    pSetup->serDesTxChannelCfg[1].enTx = TRUE; 
    pSetup->serDesTxChannelCfg[1].enableFixedPhase = TRUE; 

	/* SERDES PLL configuration for channel 2 */
	pSetup->serDesPllCfg[2].pllEnable = TRUE;
	pSetup->serDesPllCfg[2].pllMplyFactor = CSL_SRIO_SERDES_PLL_MPLY_BY_6;

    /* SERDES RX channel 2 enable */
    pSetup->serDesRxChannelCfg[2].enRx = TRUE; 
    pSetup->serDesRxChannelCfg[2].symAlign = CSL_SRIO_SERDES_SYM_ALIGN_COMMA; 
	pSetup->serDesRxChannelCfg[2].los = CSL_SRIO_SERDES_LOS_DET_HIGH_THRESHOLD;
	pSetup->serDesRxChannelCfg[2].clockDataRecovery = 0x01;   /* first order */
	pSetup->serDesRxChannelCfg[2].equalizer = 0x01;

    /* SERDES TX channel 2 enable */
    pSetup->serDesTxChannelCfg[2].enTx = TRUE; 
    pSetup->serDesTxChannelCfg[2].enableFixedPhase = TRUE; 

	/* SERDES PLL configuration for channel 3 */
	pSetup->serDesPllCfg[3].pllEnable = TRUE;
	pSetup->serDesPllCfg[3].pllMplyFactor = CSL_SRIO_SERDES_PLL_MPLY_BY_6;

    /* SERDES RX channel 3 enable */
    pSetup->serDesRxChannelCfg[3].enRx = TRUE; 
    pSetup->serDesRxChannelCfg[3].symAlign = CSL_SRIO_SERDES_SYM_ALIGN_COMMA; 
	pSetup->serDesRxChannelCfg[3].los = CSL_SRIO_SERDES_LOS_DET_HIGH_THRESHOLD;
	pSetup->serDesRxChannelCfg[3].clockDataRecovery = 0x01; /* first order */
	pSetup->serDesRxChannelCfg[3].equalizer = 0x01;

    /* SERDES TX channel 3 enable */
    pSetup->serDesTxChannelCfg[3].enTx = TRUE; 
    pSetup->serDesTxChannelCfg[3].enableFixedPhase = TRUE; 

    /* Select flow control ID length 16-bit */
    pSetup->flowCntlIdLen[0] = 1; 


    /* Destination ID of flow n, same ids as we are doing loopback */
    pSetup->flowCntlId[0] = LARGE_DEV_ID; 

    /* Sets the number of address bits generated by the PE as a source and 
     * processed by the PE as the target of an operation as 34 bits
     */
    pSetup->peLlAddrCtrl = CSL_SRIO_ADDR_SELECT_34BIT;

    /* Base device configuration */
    pSetup->devIdSetup.smallTrBaseDevId =  SMALL_DEV_ID;
    pSetup->devIdSetup.largeTrBaseDevId =  LARGE_DEV_ID;
    pSetup->devIdSetup.hostBaseDevId =  LARGE_DEV_ID;

    /* Port General configuration */
    pSetup->portGenSetup.portLinkTimeout = 0xFFFFF;  /* 215 ms */
    pSetup->portGenSetup.portRespTimeout = 0xFFFFF;  /* 215 ms */
    pSetup->portGenSetup.hostEn = 0;                 /* It is a slave */
    pSetup->portGenSetup.masterEn = 1;     /* This device can issue requests */

    /* Port control configuration */
    pSetup->portCntlSetup[0].portDis = 0;        /* Do not disable Port 0 */
    pSetup->portCntlSetup[0].outPortEn = 1;      /* Output on Port 0 enabled */
    pSetup->portCntlSetup[0].inPortEn = 1;       /* Input on Port 0 enabled */
    pSetup->portCntlSetup[0].portWidthOverride =
                CSL_SRIO_PORT_WIDTH_NO_OVERRIDE; /* 4 line port */
    pSetup->portCntlSetup[0].errCheckDis = 0;    /* Err check enabled */
    pSetup->portCntlSetup[0].multicastRcvEn = 1; /* MltCast receive enabled */
    pSetup->portCntlSetup[0].stopOnPortFailEn = 1; /* Stop on fail */
    pSetup->portCntlSetup[0].dropPktEn = 1;      /* Drop PKT */
    pSetup->portCntlSetup[0].portLockoutEn = 0;  /* Send any PKT */
    
    /* Enable all logical/transport errors */
    pSetup->lgclTransErrEn = CSL_SRIO_IO_ERR_RESP_ENABLE |
                             CSL_SRIO_ILL_TRANS_DECODE_ENABLE |
                             CSL_SRIO_ILL_TRANS_TARGET_ERR_ENABLE |
                             CSL_SRIO_PKT_RESP_TIMEOUT_ENABLE |
                             CSL_SRIO_UNSOLICITED_RESP_ENABLE |
                             CSL_SRIO_UNSUPPORTED_TRANS_ENABLE;

    /* Enable all Port errors */
    
    pSetup->portErrSetup[0].portErrRateEn =
                            CSL_SRIO_ERR_IMP_SPECIFIC_ENABLE |
                            CSL_SRIO_CORRUPT_CNTL_SYM_ENABLE |
                            CSL_SRIO_CNTL_SYM_UNEXPECTED_ACKID_ENABLE |
                            CSL_SRIO_RCVD_PKT_NOT_ACCPT_ENABLE |
                            CSL_SRIO_PKT_UNEXPECTED_ACKID_ENABLE |
                            CSL_SRIO_RCVD_PKT_WITH_BAD_CRC_ENABLE |
                            CSL_SRIO_RCVD_PKT_OVER_276B_ENABLE |
                            CSL_SRIO_NON_OUTSTANDING_ACKID_ENABLE |
                            CSL_SRIO_PROTOCOL_ERROR_ENABLE |
                            CSL_SRIO_UNSOLICITED_ACK_CNTL_SYM_ENABLE |
                            CSL_SRIO_LINK_TIMEOUT_ENABLE;

    /* Decrement error rate counter every second */ 
    pSetup->portErrSetup[0].prtErrRtBias = CSL_SRIO_ERR_RATE_BIAS_1S;

    /* Allow only 2 errors after error threshold is reached */ 
    pSetup->portErrSetup[0].portErrRtRec = CSL_SRIO_ERR_RATE_COUNT_2;

    /*  Port error setup */ 
    pSetup->portErrSetup[0].portErrRtFldThresh = 10;   /* Err threshold = 10 */
    pSetup->portErrSetup[0].portErrRtDegrdThresh = 10; /* Err degrade
                                                          threshold = 10 */
    
    
    /* This configures the SP_IP_MODE register */
    /*
       IDLE_ERR_DIS    - 0b0;  IDLE Error checking enabled
       TX_FIFO_BYP ASS - 0b0;  The TX_FIFO is operational
       PW_DIS          - 0b0;  Port-Write Error reporting is enabled
       TGT_ID_DIS      - 0b0;  packet accepted if DestID != BaseID
       SELF_RST        - 0b0;  Self reset disabled
       MLTC_EN         - 0b1;  Multicast-Event Interrupt Enable 
       RST_EN          - 0b1;  Reset Interrupt Enable
       PW_EN           - 0b1;  Port-Write-In Interrupt Enable

       Not writing into clear bits, assuming they are cleared on reset
    */
    pSetup->portIpModeSet = 0x0000002A;

    /* Configure the SP_IP_PRESCALE register assuming 333 MHz frequency */
    pSetup->portIpPrescalar = 33; 

    /*  Port-Write Timer. The timer defines a period to repeat sending an error
     *  reporting Port-Write request for software assistance. The timer stopped 
     *  by software writing to the error detect registers 900 ms
     */
    pSetup->pwTimer = CSL_SRIO_PW_TIME_8;

    /* Port control independent error reporting enable. Macros can be ORed
     *  to get the value
     */

    /*
       TX_FLW        - 0;     Receive link flow control
       SOFT_REC      - 0;     Hardware controlled error recovery 
       FORCE_REINIT  - 0;     Reinitialization process NOT forced
       TRANS_MODE    - 01;    transfer mode - Store & Forward Mode 
       DEBUG         - 1;     Debug enable
       SEND_DBG_PKT  - 0;     Do not force a debug packet
       ILL_TRANS_EN  - 1;     Illegal Transfer Error reporting Enable
       MAX_RETRY_EN  - 1;     Max_retry_error report enable
       MAX_RETRY_THR - 0x01;  Maximum Retry Threshold Trigger
       IRQ_EN        - 1;     Interrupt error report Enable
    */ 
    pSetup->portCntlIndpEn[0] = 0x01A20180; 
}


