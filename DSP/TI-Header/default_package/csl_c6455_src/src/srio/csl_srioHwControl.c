/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found in the
 * license agreement under which this software has been supplied.
 * =============================================================================
 */
/** ===========================================================================
 * @file csl_srioHwControl.c
 *
 * @brief File for functional layer of CSL API CSL_srioHwControl()
 * 
 * @path $(CSLPATH)\srio\src
 *
 * @desc The CSL_srioHwControl() function definition and it's associated
 *       functions 
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
 *   @n@b CSL_srioHwControl
 *
 *   @b Description
 *   @n This function performs various control operations on the SRIO instance,
 *      based on the command passed.
 *
 *   @b Arguments
 *   @verbatim
            hSrio        Handle to the SRIO instance

            cmd          Operation to be performed on the SRIO

            cmdArg       Arguement specific to the command

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK            - Command execution successful.
 *   @li                    CSL_ESYS_BADHANDLE - Invalid handle
 *   @li                    CSL_ESYS_INVCMD    - Invalid command
 *   @li                    CSL_ESYS_INVPARAMS - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Registers of the SRIO instance are configured according to the command
 *       and the command arguments. The command determines which registers are
 *       modified.
 *
 *   @b Modifies
 *   @n Registers determined by the command
 *
 *   @b Example
 *   @verbatim
        CSL_SrioHandle   hSrio;
    	CSL_SrioPortData clearData;
        CSL_Status       status;
        Uint32           mask;
    	Uint8            index;
        ... 
        // for clearing LSU interrupts status [0..3]
    	index = 1;
        mask = CSL_SRIO_LSU_INTR3 | CSL_SRIO_LSU_INTR2 | 
               CSL_SRIO_LSU_INTR1 | CSL_SRIO_LSU_INTR0;
	    clearData.index = index;
    	clearData.data = mask;
        ...
        CSL_srioHwControl(hSrio, CSL_SRIO_CMD_LSU_INTR_CLEAR, &clearData);
        ...
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (CSL_srioHwControl, ".text:csl_section:srio");
CSL_Status  CSL_srioHwControl (
    CSL_SrioHandle       hSrio,
    CSL_SrioHwControlCmd cmd,
    void                 *arg
)
{
    CSL_Status status = CSL_SOK ;

    if (hSrio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    } 
    else if (arg == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (cmd) {
            /* Enables/disables the peripheral */
            case CSL_SRIO_CMD_PER_ENABLE:
                CSL_SrioPerEn(hSrio, *(Bool*)arg);
                break;

            /* Enable/disable the SERDES PLLs */
            case CSL_SRIO_CMD_PLL_CONTROL:
                CSL_SrioPllCntlSet(hSrio, *(Uint8 *)arg);
                break;

            /* Clears doorbell interrupts */
            case CSL_SRIO_CMD_DOORBELL_INTR_CLEAR:
                CSL_SrioDoorbellIntrClear(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Clear load/store module interrupts */
            case CSL_SRIO_CMD_LSU_INTR_CLEAR:
                CSL_SrioLsuIntrClear(hSrio, *(Uint32 *)arg);
                break;

            /* Clears Error, Reset, and Special Event interrupts */
            case CSL_SRIO_CMD_ERR_RST_INTR_CLEAR:
                CSL_SrioErrRstIntrClear(hSrio, *(Uint32 *)arg);
                break;

            /* Sets 32-bit DSP byte source address */
            case CSL_SRIO_CMD_DIRECTIO_SRC_NODE_ADDR_SET:
                CSL_SrioSrcAddrSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Sets the rapid IO destination MSB address */
            case CSL_SRIO_CMD_DIRECTIO_DST_ADDR_MSB_SET:
                CSL_SrioDstAddrMsbSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Sets the rapid IO destination LSB address */
            case CSL_SRIO_CMD_DIRECTIO_DST_ADDR_LSB_SET:
                CSL_SrioDstAddrLsbSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Number of data bytes to Read/Write - up to 4KB */
            case CSL_SRIO_CMD_DIRECTIO_XFR_BYTECNT_SET:
                CSL_SrioLsuXfrByteCntSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* sets the LSU transfer type */
            case CSL_SRIO_CMD_DIRECTIO_LSU_XFR_TYPE_SET:
                CSL_SrioLsuXfrTypeSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Sets RapidIO doorbell info field for type 10 packets */
            case CSL_SRIO_CMD_DOORBELL_XFR_SET:
                CSL_SrioDoorbellXfrTypeSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Sets LSU flow masks */
            case CSL_SRIO_CMD_DIRECTIO_LSU_FLOW_MASK_SET:
                CSL_SrioLsuFlowMaskSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Sets the command to be sent in link-request control symbol */
            case CSL_SRIO_CMD_PORT_COMMAND_SET:
                CSL_SrioPortCmdSet(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Clear port errors status of SP_ERR_STAT register */
            case CSL_SRIO_CMD_SP_ERR_STAT_CLEAR:
                CSL_SrioSpErrStatClear(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Clear status of  Logical/Transport layer errors */
            case CSL_SRIO_CMD_LGCL_TRANS_ERR_STAT_CLEAR:
                CSL_SrioLgclTrnsErrStatClear(hSrio, *(Uint32 *)arg);
                break;

            /* Clears status of port errors interrupts of SP_ERR_DET register */
            case CSL_SRIO_CMD_SP_ERR_DET_STAT_CLEAR:
                CSL_SrioSpErrDetStatClear(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* clears status of the fields of SP_CTL_INDEP_ERR register*/
            case CSL_SRIO_CMD_SP_CTL_INDEP_ERR_STAT_CLEAR:
                CSL_SrioSpCtlIndepErrStatClear(hSrio, (CSL_SrioPortData *)arg);
                break;

            /* Set control symbols used for  packet acknowledgment */
            case CSL_SRIO_CMD_CNTL_SYM_SET:
                CSL_SrioCntlSymSet(hSrio, (CSL_SrioCntlSym *)arg);
                break;

            /* sets  interrupt rate control counter */
            case CSL_SRIO_CMD_INTDST_RATE_CNTL:
                CSL_SrioSetIntdstRateCntl(hSrio, *(Uint32 *)arg);
                break;

            default:
                status = CSL_ESYS_INVCMD;
                break;
        }
    }
    return (status);
}

