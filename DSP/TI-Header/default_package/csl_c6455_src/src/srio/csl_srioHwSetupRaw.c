/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * ============================================================================
 */
/** ===========================================================================
 * @file csl_srioHwSetupRaw.c
 *
 * @brief File for functional layer of CSL API CSL_srioHwSetupRaw()
 * 
 * @path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioHwSetupRaw() function definition and it's associated
 *       functions 
 * ============================================================================
 */
/* ============================================================================
 * Revision History
 * ===============
 * 24-Aug-2005 PSK File Created.
 * ============================================================================
 */
#include <csl_srio.h>
#include <csl_srioAux.h>

/** ============================================================================
 *   @n@b CSL_srioHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *  	provided through the config data structure. 
 *
 *   @b Arguments
 *   @verbatim
            hSrio           Handle to the SRIO instance

            config          Pointer to the config structure containing the
                            device register values
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration structure
 *                                                pointer is not properly
 *                                                 initialized
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified SRIO instance will be setup
 *       according to the values passed through the config structure
 *
 *   @b Modifies
 *   @n Hardware registers of the specified SRIO
 *
 *   @b Example
 *   @verbatim
        CSL_SrioHandle hSrio;
        CSL_SrioConfig config = CSL_SRIO_CONFIG_DEFAULTS;
        CSL_Status     status;
        ...
        
        status = CSL_srioHwSetupRaw(hSrio, &config);

        ...
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION(CSL_srioHwSetupRaw, ".text:csl_section:srio");
CSL_Status  CSL_srioHwSetupRaw (
    CSL_SrioHandle    hSrio,
    CSL_SrioConfig    *config 
)
{
    CSL_Status status = CSL_SOK;
    int i;
    
    if (hSrio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (config == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* Configures Peripheral settings control register */
        hSrio->regs->PER_SET_CNTL = config->PER_SET_CNTL;

        /* Configures Peripheral global enable register */
        hSrio->regs->GBL_EN = config->GBL_EN;

        /* Configures Block enable registers */
        for (i = 0; i < CSL_SRIO_BLOCKS_MAX; i++) {
            hSrio->regs->BLK_ENABLE[i].BLK_EN = config->BLK_EN[i];
        }

        /* Configures Device ID register 1 */
        hSrio->regs->DEVICEID_REG1 = config->DEVICEID_REG1;

        /* Configures Device ID register 2 */
        hSrio->regs->DEVICEID_REG2 = config->DEVICEID_REG2;

        /* Configures Packet forwarding registers for 16-bit and 8bbit 
         * device IDs 
         */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->HW_PKT_FWD[i].PF_16BIT_CNTL = 
                            config->HW_PKT_FWD[i].PF_16BIT_CNTL;
            hSrio->regs->HW_PKT_FWD[i].PF_8BIT_CNTL = 
                            config->HW_PKT_FWD[i].PF_8BIT_CNTL;
        }

        /* Configures SerDes RX channels configuration control registers*/
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->SERDES_CFGRX_CNTL[i] = config->SERDES_CFGRX_CNTL[i];
        }

        /* Configures SerDes TX channels configuration control registers*/
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->SERDES_CFGTX_CNTL[i] = config->SERDES_CFGTX_CNTL[i];
        }

        /* Configures SerDes macros configuration control registers */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->SERDES_CFG_CNTL[i] = config->SERDES_CFG_CNTL[i];
        }

        /* Configures Doorbell interrupt clear registers */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->DOORBELL_INTR[i].DOORBELL_ICCR = 
                config->DOORBELL_ICCR[i]; 
        }

        /* Configures LSU interrupt clear registers */
        hSrio->regs->LSU_ICCR = config->LSU_ICCR;

        /* Configures Error, Reset, and Special event interrupt clear 
         * registers 
         */
        hSrio->regs->ERR_RST_EVNT_ICCR = config->ERR_RST_EVNT_ICCR;

        /* Configures INTDST interrupt rate control register for DST 0 */
        hSrio->regs->INTDST_RATE_CNTL[0] = config->INTDST_RATE_CNTL;

        /* Configures LSU registers */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->LSU[i].LSU_REG0 = config->LSU[i].LSU_REG0;
            hSrio->regs->LSU[i].LSU_REG1 = config->LSU[i].LSU_REG1;
            hSrio->regs->LSU[i].LSU_REG2 = config->LSU[i].LSU_REG2;
            hSrio->regs->LSU[i].LSU_REG3 = config->LSU[i].LSU_REG3;
            hSrio->regs->LSU[i].LSU_REG4 = config->LSU[i].LSU_REG4;
            hSrio->regs->LSU[i].LSU_FLOW_MASKS = config->LSU[i].LSU_FLOW_MASKS;
        } 

        /* Configures Flow control table entry registers */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->FLOW_CNTL[i]  = config->FLOW_CNTL[i];
        }

        /* Configures Processing element logical layer control CSR register */
        hSrio->regs->PE_LL_CTL = config->PE_LL_CTL;

        /* Configures Base device ID CSR register */
        hSrio->regs->BASE_ID = config->BASE_ID;

        /* Configures Host base device ID lock CSR */
        hSrio->regs->HOST_BASE_ID_LOCK = config->HOST_BASE_ID_LOCK;

        /* Configures Component tag CSR */
        hSrio->regs->COMP_TAG = config->COMP_TAG;

        /* Configures Port link time-out control CSR */
        hSrio->regs->SP_LT_CTL = config->SP_LT_CTL;

        /* Configures Port link response time-out control CSR */
        hSrio->regs->SP_RT_CTL = config->SP_RT_CTL;

        /* Configures Port general control CSR */
        hSrio->regs->SP_GEN_CTL = config->SP_GEN_CTL;

        /* Configures Port registers */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->PORT[i].SP_LM_REQ = config->PORT[i].SP_LM_REQ;
            hSrio->regs->PORT[i].SP_ACKID_STAT = config->PORT[i].SP_ACKID_STAT;
            hSrio->regs->PORT[i].SP_ERR_STAT = config->PORT[i].SP_ERR_STAT;
            hSrio->regs->PORT[i].SP_CTL = config->PORT[i].SP_CTL;
        }

        /* Configures Logical/Transport layer error detect CSR */
        hSrio->regs->ERR_DET = config->ERR_DET;

        /* Configures Logical/Transport layer error enable CSR */
        hSrio->regs->ERR_EN = config->ERR_EN;

        /* Configures Port-write target device ID CSR */
        hSrio->regs->PW_TGT_ID = config->PW_TGT_ID;

        /* Configures Port error CSR */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->PORT_ERROR[i].SP_ERR_DET = 
                config->PORT_ERROR[i].SP_ERR_DET;
            hSrio->regs->PORT_ERROR[i].SP_RATE_EN = 
                config->PORT_ERROR[i].SP_RATE_EN;
            hSrio->regs->PORT_ERROR[i].SP_ERR_RATE = 
                config->PORT_ERROR[i].SP_ERR_RATE;
            hSrio->regs->PORT_ERROR[i].SP_ERR_THRESH = 
                config->PORT_ERROR[i].SP_ERR_THRESH;
        }

        /* Configures Port IP discovery timer in 4x mode */
        hSrio->regs->SP_IP_DISCOVERY_TIMER = config->SP_IP_DISCOVERY_TIMER;

        /* Configures Port IP mode CSR */
        hSrio->regs->SP_IP_MODE = config->SP_IP_MODE;

        /* Configures Serial port IP prescalar */
        hSrio->regs->IP_PRESCAL = config->IP_PRESCALAR;

        /* Configures Port options CSR */
        for (i = 0; i < CSL_SRIO_PORTS_MAX; i++) {
            hSrio->regs->PORT_OPTION[i].SP_RST_OPT = 
                config->PORT_OPTION[i].SP_RST_OPT;
            hSrio->regs->PORT_OPTION[i].SP_CTL_INDEP = 
                config->PORT_OPTION[i].SP_CTL_INDEP;
            hSrio->regs->PORT_OPTION[i].SP_SILENCE_TIMER = 
                config->PORT_OPTION[i].SP_SILENCE_TIMER;
            hSrio->regs->PORT_OPTION[i].SP_MULT_EVNT_CS = 
                config->PORT_OPTION[i].SP_MULT_EVNT_CS;
            hSrio->regs->PORT_OPTION[i].SP_CS_TX = 
                config->PORT_OPTION[i].SP_CS_TX;
        }

        /* Configures Peripheral control register */
        hSrio->regs->PCR = config->PCR;
    }
    return (status);
}

