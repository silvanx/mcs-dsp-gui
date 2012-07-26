/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_mcbspHwControl.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspHwControl()
 *
 */
 
/* =============================================================================
 * Revision History
 * ================
 *  June 29,2004 Pratheesh Gangadhar - Created
 * 
 *  July 26, 2005 ds        - Removed control cmd CSL_MCBSP_CMD_IO_MODE_CONTROL 
 *
 *  Feb  01, 2006 ds        - Removed CSL_MCBSP_CMD_TX_INT_MODE and
 *                            CSL_MCBSP_CMD_RX_INT_MODE control commands                       
 * =============================================================================
 */
 
#include <csl_mcbsp.h>
#include <_csl_mcbsp.h>
#include <csl_mcbspAux.h>

/** ============================================================================
 *   @n@b CSL_mcbspHwControl
 *
 *   @b Description
 *   @n This function takes an input control command with an optional argument
 *      and accordingly controls the operation/configuration of MCBSP.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          MCBSP handle returned by successful 'open'
 
            cmd             Control command
            
            arg             Optional argument as per the control command
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status 
 *   @li                    CSL_SOK            - Command successful
 *   @li                    CSL_ESYS_INVCMD    - The Command passed is invalid
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *   @li                    CSL_ESYS_INVPARAMS - The parameter is invalid
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before CSL_mcbspHwControl() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  Mcbsp registers are configured according to the command passed 
 *       
 *   @b Modifies
 *   @n MCBSP registers
 *
 *   @b Example
 *   @verbatim
            CSL_Status          status;
            CSL_BitMask16       ctrlMask;
            CSL_McbspHandle     hMcbsp;
            ...
            // MCBSP object defined and HwSetup structure defined and initialized
            ...
            
            // Init successfully done
            ...
            // Open successfully done
            ...
            // HwSetup sucessfully done
            ...
            // MCBSP SRG and Frame sync taken out of reset
            ...
            
            ctrlMask = CSL_MCBSP_CTRL_RX_ENABLE | CSL_MCBSP_CTRL_TX_ENABLE;
            status = CSL_mcbspHwControl(hMcbsp, CSL_MCBSP_CMD_RESET_CONTROL,
                                        &ctrlMask);
            ...

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspHwControl, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspHwControl (
    CSL_McbspHandle         hMcbsp,
    CSL_McbspControlCmd     cmd,
    void                    *arg
)
{
    CSL_Status              status  = CSL_SOK;
    CSL_McbspBlkAssign      *blkAsg;
    CSL_McbspChanControl    *ch;
    CSL_McbspChType         *chan;
    CSL_BitMask16           *ctrl;
    
    if(hMcbsp == NULL) {
        status=CSL_ESYS_BADHANDLE;
    }
    else if(((cmd <= CSL_MCBSP_CMD_RESET_CONTROL) && \
             (cmd != CSL_MCBSP_CMD_RESET))&& \
             (arg == NULL)) {
        status=CSL_ESYS_INVPARAMS;
    }
    else {
        switch(cmd) {
            case CSL_MCBSP_CMD_ASSIGN_BLOCK:
                blkAsg = (CSL_McbspBlkAssign *)arg;
                _CSL_mcbspBlockAssign(hMcbsp, blkAsg->partition, blkAsg->block);
                break;
    
            case CSL_MCBSP_CMD_CHANNEL_CONTROL:
                ch = (CSL_McbspChanControl *)arg;
                _CSL_mcbspChannelControl(hMcbsp, (ch->channelNo & 0xf), \
                                         (CSL_McbspBlock)(ch->channelNo >> 4),\
                                         ch->operation);
                break;
    
            case CSL_MCBSP_CMD_CLEAR_FRAME_SYNC:
                chan = (CSL_McbspChType *)arg;
                _CSL_mcbspClearFrmSyncErr(hMcbsp,*chan);
                break;
    
            case CSL_MCBSP_CMD_RESET:
                _CSL_mcbspRegReset(hMcbsp);
                break;
    
            case CSL_MCBSP_CMD_RESET_CONTROL:
                ctrl = (CSL_BitMask16 *)arg;
                _CSL_mcbspResetCtrl(hMcbsp, *ctrl);
                break;
    
            default: 
                status = CSL_ESYS_INVCMD;
                break;
        }
    }

    return (status);
}

