/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3Close.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  EDMA3 CSL Implementation on DSP side
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

/** ============================================================================
 *   @n@b CSL_edma3Close.c
 *
 *   @b Description
 *   @n This is a module level close require to invalidate the module handle.
 *      The module handle must not be used after this API call.
 *      
 *   @b Arguments
 *   @verbatim
            hEdma           Handle to the Edma Instance
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK - Edma is closed successfully.
 *                                    
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid
 *
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init() and CSL_edma3Open() have to be called in that 
 *       order successfully before calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  The edma CSL APIs can not be called until the edma CSL is reopened 
 *       again using CSL_edma3Open() 
 *
 *   @b Modifies
 *   @n CSL_edma3Obj structure values 
 *            
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup,gethwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
                                              CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwDmaChannelSetup  getdmahwSetup[CSL_EDMA3_NUM_DMACH];
            CSL_Status status;
        
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj, CSL_EDMA3, NULL, &status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = NULL;
            CSL_edma3HwSetup(hModule, &hwSetup);
         
            // Open Channels, setup transfers etc   
            // Close Module
            CSL_edma3Close(hModule);
            
    @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3Close, ".text:csl_section:edma3");
CSL_Status CSL_edma3Close (
    CSL_Edma3Handle    hEdma
)
{   
    CSL_Status    status = CSL_SOK;
    
    if (hEdma != NULL) {
        hEdma->regs = (CSL_Edma3ccRegsOvly) NULL;
        hEdma->instNum = (CSL_InstNum)-1;
    } 
    else {
        status = CSL_ESYS_BADHANDLE;
    }
    
    return (status);
}

