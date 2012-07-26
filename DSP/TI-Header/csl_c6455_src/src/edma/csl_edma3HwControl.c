/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3HwControl.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API CSL_edma3HwControl()
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  29-May-2004 Ruchika Kharwar File Created.
 *
 * =============================================================================
 */
 
#include <csl_edma3.h>
#include <csl_edma3Aux.h> 

/** ============================================================================
 *   @n@b CSL_edma3HwControl
 *
 *   @b Description
 *   @n Takes a command with an optional argument & implements it. This function
 *      is used to carry out the different operations performed by EDMA.
 *
 *   @b Arguments
 *   @verbatim
            hMod            Edma module Handle
 
            cmd             The command to this API which indicates the 
                            action to be taken

            cmdArg          Pointer arguement specific to the command 
                            
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Command execution successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVCMD     - The command passed is invalid 
 *                                                
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() must be called successfully 
 *       in that order before this API can be invoked
 *
 *   <b> Post Condition </b>
 *   @n  Edma registers are configured according to the command and
 *       the command arguments. The command determines which registers are
 *       modified.
 *
 *   @b Modifies
 *   @n Edma registers determined by the command
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup,gethwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3QueryInfo          info;
            CSL_Edma3CmdIntr            regionIntr;
            CSL_Edma3CmdDrae            regionAccess;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = \
                                             CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwDmaChannelSetup  getdmahwSetup[CSL_EDMA3_NUM_DMACH];
            CSL_Status                  status;
            Uint32                      i,passStatus = 1;
           
        
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = NULL;
            CSL_edma3HwSetup(hModule,&hwSetup);
        
            // Query Module Info 
            CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INFO,&info);
            
            // DRAE Enable(Bits 0-15) for the Shadow Region 0.
            regionAccess.region = CSL_EDMA3_REGION_0 ;
            regionAccess.drae =   0xFFFF ;   
            regionAccess.draeh =  0x0000 ;
            CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_DMAREGION_ENABLE, \
                              &regionAccess); 
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3HwControl, ".text:csl_section:edma3");
CSL_Status  CSL_edma3HwControl (
    CSL_Edma3Handle           hMod,
    CSL_Edma3HwControlCmd     cmd,
    void                     *cmdArg
)
{ 
    CSL_Status    status = CSL_SOK; 
    
    if (hMod == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (((cmd >= 0) && (cmd <= CSL_EDMA3_CMD_EVENTMISSED_CLEAR)) && 
              ((cmd != CSL_EDMA3_CMD_MEMFAULT_CLEAR) && 
               (cmd != CSL_EDMA3_CMD_ERROR_EVAL)) && (cmdArg == NULL)) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(cmd) {
#if CSL_EDMA3_MEMPROTECT    
            case CSL_EDMA3_CMD_MEMPROTECT_SET:
                status = CSL_edma3SetMemoryProtectionAttrib(hMod, \
                                     ((CSL_Edma3CmdRegion*)cmdArg)->region,\
                                     ((CSL_Edma3CmdRegion*)cmdArg)->regionVal);
                break;
            case CSL_EDMA3_CMD_MEMFAULT_CLEAR:
                status = CSL_edma3MemFaultClear(hMod);
                break;
#endif                      
            case CSL_EDMA3_CMD_DMAREGION_ENABLE:
                status = CSL_edma3DmaRegionAccessEnable(hMod, \
                                     ((CSL_Edma3CmdDrae*)cmdArg)->region, \
                                     ((CSL_Edma3CmdDrae*)cmdArg)->drae, \
                                     ((CSL_Edma3CmdDrae*)cmdArg)->draeh);
                break;
                
            case CSL_EDMA3_CMD_DMAREGION_DISABLE:
                status = CSL_edma3DmaRegionAccessDisable(hMod, \
                                     ((CSL_Edma3CmdDrae*)cmdArg)->region, \
                                     ((CSL_Edma3CmdDrae*)cmdArg)->drae, \
                                     ((CSL_Edma3CmdDrae*)cmdArg)->draeh);
                break;
                
            case CSL_EDMA3_CMD_QDMAREGION_ENABLE:
                status = CSL_edma3QdmaRegionAccessEnable(hMod, \
                                     ((CSL_Edma3CmdQrae*)cmdArg)->region,\
                                     ((CSL_Edma3CmdQrae*)cmdArg)->qrae);
                break;
                
            case CSL_EDMA3_CMD_QDMAREGION_DISABLE:
                status = CSL_edma3QdmaRegionAccessDisable(hMod, \
                                     ((CSL_Edma3CmdQrae*)cmdArg)->region, \
                                     ((CSL_Edma3CmdQrae*)cmdArg)->qrae);
                break;  
                
            case CSL_EDMA3_CMD_QUEPRIORITY_SET:
                status = CSL_edma3EventQueuePrioritySet(hMod, \
                                     ((CSL_Edma3CmdQuePri*)cmdArg)->que, \
                                     ((CSL_Edma3CmdQuePri*)cmdArg)->pri);
                break;
                
            case CSL_EDMA3_CMD_QUETHRESHOLD_SET:
                status = CSL_edma3EventQueueThresholdSet(hMod,\
                                     ((CSL_Edma3CmdQueThr*)cmdArg)->que, \
                                     ((CSL_Edma3CmdQueThr*)cmdArg)->threshold);
                break;          
                
            case CSL_EDMA3_CMD_ERROR_EVAL:
                status = CSL_edma3ErrorEval(hMod);
                break;          
                
            case CSL_EDMA3_CMD_INTRPEND_CLEAR:
                status = CSL_edma3InterruptClear(hMod, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->region, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->intr,\
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->intrh);
                break;          
                
            case CSL_EDMA3_CMD_INTR_ENABLE:
                status = CSL_edma3InterruptEnable(hMod, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->region, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->intr, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->intrh);
                break;          
                
            case CSL_EDMA3_CMD_INTR_DISABLE:
                status = CSL_edma3InterruptDisable(hMod, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->region, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->intr, \
                                     ((CSL_Edma3CmdIntr*)(cmdArg))->intrh);
                break;
                
            case CSL_EDMA3_CMD_INTR_EVAL:
                status = CSL_edma3InterruptEval(hMod,*((Int*)(cmdArg)));            
                break;  
                        
            case CSL_EDMA3_CMD_CTRLERROR_CLEAR:
                status = CSL_edma3ControllerErrorClear(hMod, \
                ((CSL_Edma3CtrlErrStat*)(cmdArg)));
                break;
                
            case CSL_EDMA3_CMD_EVENTMISSED_CLEAR:
                status = \
                CSL_edma3EventsMissedClear(hMod,((CSL_BitMask32*)cmdArg)[0], \
                ((CSL_BitMask32*)cmdArg)[1],((CSL_BitMask32*)cmdArg)[2]);
                break;
                
            default:
                 status = CSL_ESYS_INVCMD;
                 break;
        }
    }

    return (status);
}

