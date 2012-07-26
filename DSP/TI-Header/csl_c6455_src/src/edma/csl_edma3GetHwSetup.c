/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3GetHwSetup.c
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
#include <csl_edma3Aux.h>

/** ============================================================================
 *   @n@b CSL_edma3GetHwSetup
 *
 *   @b Description
 *   @n It gets setup of the all dma/qdma channels
 *
 *   @b Arguments
 *   @verbatim
            hMod            Edma Handle
 
            setup           pointer to the setup structure
 
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Get Module Setup
 *   @li                    CSL_ESYS_BADHANDLE  - The handle is passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameter entry
 *                                                
 *   <b> Pre Condition </b>
 *   @n  Functions CSL_edma3Init(), CSL_edma3Open() must be called successfully
 *       in that order before CSL_edma3GetHwSetup() can be called. 
 *
 *   <b> Post Condition </b>
 *   @n  The hardware setup structure is populated with the hardware setup
 *       parameters
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup,gethwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3ChannelObj         ChObj;
            CSL_Edma3ChannelAttr        chAttr;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
                                              CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwDmaChannelSetup  getdmahwSetup[CSL_EDMA3_NUM_DMACH];
            CSL_Status                  status;
            Uint32                      i, passStatus = 1;
           
        
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = NULL;
            CSL_edma3HwSetup(hModule,&hwSetup);
         
             
            // Get Module Setup
            gethwSetup.dmaChaSetup  = &getdmahwSetup[0];
            gethwSetup.qdmaChaSetup = NULL;
            CSL_edma3GetHwSetup(hModule,&gethwSetup);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3GetHwSetup, ".text:csl_section:edma3");
CSL_Status  CSL_edma3GetHwSetup (
    CSL_Edma3Handle        hMod,
    CSL_Edma3HwSetup      *setup
)
{
    Uint32        numCha;
    Uint32        tempQnum  = 0;
    Uint32        tempChmap = 0;
    Uint32        ii;
    CSL_Status    status = CSL_SOK;  
    
    if (hMod == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (setup == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        if (setup->dmaChaSetup != NULL) {
            for (numCha = 0 ; numCha < CSL_EDMA3_NUM_DMACH; numCha++) {
#ifdef CSL_EDMA3_CHMAPEXIST
                setup->dmaChaSetup[numCha].paramNum = \
                    CSL_FEXT(hMod->regs->DCHMAP[numCha], EDMA3CC_DCHMAP_PAENTRY);
#endif      
                if (((ii) % 8) == 0)
                    tempQnum = hMod->regs->DMAQNUM[numCha/8];
                ii = numCha % 8;
                setup->dmaChaSetup[numCha].que = \
                      (CSL_Edma3Que) CSL_FEXTR(tempQnum, (ii * 4) + 2, (ii * 4));
            }
        }
        
        if (setup->qdmaChaSetup != NULL) { 
            tempQnum = hMod->regs->QDMAQNUM;
            for (numCha = 0 ; numCha < CSL_EDMA3_NUM_QDMACH; numCha++) {
                tempChmap = hMod->regs->QCHMAP[numCha];
                setup->qdmaChaSetup[numCha].paramNum = \
                        CSL_FEXT(tempChmap,EDMA3CC_QCHMAP_PAENTRY);
                setup->qdmaChaSetup[numCha].triggerWord = \
                      CSL_FEXT(tempChmap,EDMA3CC_QCHMAP_TRWORD);
                setup->qdmaChaSetup[numCha].que = \
                     (CSL_Edma3Que)CSL_FEXTR(tempQnum, (numCha * 4) + 2, numCha* 4);
            }
        }
    }

    return (status); 
}

