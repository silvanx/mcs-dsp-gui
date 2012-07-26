/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/*  ============================================================================
 *   @file  _csl_mcbspChannelControl.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API _CSL_mcbspChannelControl()
 *
 */
 
/*  ============================================================================
 * Revision History
 * ================
 *  July 04, 2005 ds     - Register Naming convention used for 
 *                          Multichannel registers are changed according 
 *                          the changes in cslr_mcbsp.h
 *  ============================================================================
 */
 
#include <csl_mcbsp.h>
#include <_csl_mcbsp.h>

/*  ============================================================================
 *   @n@b _CSL_mcbspChannelControl
 *
 *   @b Description
 *   @n Enable channel in Multi Channel Selection Mode
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to MCBSP Obj used

            channelNo       Channel Number

            block           Block to which the channel belongs

            operation       The operation to be performed
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK            - Successful completion
 *   @li                   CSL_ESYS_FAIL      - Operation could not the done
 *   @li                   CSL_ESYS_BADHANDLE - Invalid Handle 
 *                                            
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before _CSL_mcbspChannelControl() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  Enables the specified channel
 *       
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_McbspHandle     hMcbsp;
            ...
            hMcbsp = CSL_mcbspOpen(hMcbsp, CSL_MCBSP_1,NULL, &status );
            CSL_mcbspChannelControl( hMcbsp, 11, 1, CSL_MCBSP_CHAN_RX_ENABLE);
            ...                    
     @endverbatim
 * =============================================================================
 */
 
#pragma CODE_SECTION (_CSL_mcbspChannelControl, ".text:csl_section:mcbsp");
CSL_Status  _CSL_mcbspChannelControl (
    CSL_McbspHandle         hMcbsp,
    Uint16                  channelNo,
    CSL_McbspBlock          block,
    CSL_McbspChCtrl         operation
)
{

    CSL_McbspRstStat   txEnableChk, rxEnableChk;
    CSL_McbspBlock     blkCheck;
    CSL_Status         status;

    if (hMcbsp == NULL) {
        status = CSL_ESYS_BADHANDLE;
        return status;
    }
    
    status = CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_CUR_RX_BLK, \
                                  &blkCheck);
    if(status != CSL_SOK) {
        return(CSL_ESYS_FAIL);
    }
    
    status = CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_RX_RST_STAT, \
                                  &rxEnableChk);
    if(((status == CSL_SOK) && (rxEnableChk == 1)) && (blkCheck == block)) {
        return(CSL_ESYS_FAIL);
    }
    
    status = CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_CUR_TX_BLK, \
                                  &blkCheck);
    if(status != CSL_SOK) {
        return(CSL_ESYS_FAIL);
    }
    
    status = CSL_mcbspGetHwStatus(hMcbsp, CSL_MCBSP_QUERY_TX_RST_STAT, \
                                  &txEnableChk);
    if(((status == CSL_SOK) && (rxEnableChk == 1)) && (blkCheck == block)) {
        return(CSL_ESYS_FAIL);
    }

    switch(block) {
        /* To Enable or disable One channel in block 0 in Receiver 
         * and Transmitter 
         */
        case CSL_MCBSP_BLOCK_0:
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE0, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE0, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE0, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE0, channelNo, channelNo, 0);
            break;
        /* To Enable or disable One channel in block 1 in Receiver 
         * and Transmitter 
         */
        case CSL_MCBSP_BLOCK_1:
            channelNo += 16;
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE0, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE0, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE0, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE0, channelNo, channelNo, 0);
            break;
        /* To Enable One channel in Partition-C in Receiver and Transmitter */
        case CSL_MCBSP_BLOCK_2:
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE1, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE1, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE1, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE1, channelNo, channelNo, 0);
            break;
       /* To Enable One channel in Partition-D in Receiver and Transmitter */
        case CSL_MCBSP_BLOCK_3:
            channelNo += 16;
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE1, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE1, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE1, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE1, channelNo, channelNo, 0);
            break;
       /* To Enable One channel in Partition-E in Receiver and Transmitter */
        case CSL_MCBSP_BLOCK_4:
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE2, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE2, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE2, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE2, channelNo, channelNo, 0);
            break;
        /* To Enable One channel in Partition-F in Receiver and Transmitter */
        case CSL_MCBSP_BLOCK_5:
            channelNo += 16;
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE2, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE2, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE2, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE2, channelNo, channelNo, 0);
            break;
        /* To Enable One channel in Partition-G in Receiver and Transmitter */
        case CSL_MCBSP_BLOCK_6:
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE3, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE3, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE3, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE3, channelNo, channelNo, 0);
            break;
        /* To Enable One channel in Partition-H in Receiver and Transmitter */
        case CSL_MCBSP_BLOCK_7:
            channelNo += 16;
            if(operation == CSL_MCBSP_CHCTRL_RX_ENABLE)
                CSL_FINSR( hMcbsp->regs->RCERE3, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_RX_DISABLE)
                CSL_FINSR( hMcbsp->regs->RCERE3, channelNo, channelNo, 0);
            if(operation == CSL_MCBSP_CHCTRL_TX_ENABLE)
                CSL_FINSR( hMcbsp->regs->XCERE3, channelNo, channelNo, 1);
            if(operation == CSL_MCBSP_CHCTRL_TX_DISABLE)
                CSL_FINSR( hMcbsp->regs->XCERE3, channelNo, channelNo, 0);
            break;

        default: 
            return(CSL_ESYS_FAIL);
    }

    return(CSL_SOK);

}

