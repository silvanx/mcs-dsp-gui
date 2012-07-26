/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
/** ============================================================================
 *   @file  csl_edma3HwSetup.c
 *
 *   @path  $(CSLPATH)\src\edma
 *
 *   @desc  File for functional layer of CSL API CSL_edma3HwSetup()
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
 *   @n@b CSL_edma3HwSetup
 *
 *   @b Description
 *   @n This function initializes the device registers with the appropriate 
 *      values provided through the HwSetup Data structure. After the Setup is 
 *      completed, the device is ready for operation. For information passed 
 *      through the HwSetup Data structure, refer CSL_Edma3HwSetup.This does 
 *      the setup for all dma/qdma channels viz. the parameter entry mapping, 
 *      the trigger word setting (if QDMA channels) and the event queue mapping 
 *      of the channel.
 *
 *   @b Arguments
 *   @verbatim
            hMod            Edma module Handle
 
            setup           Pointer to the setup structure
                            
      @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Hwsetup successful
 *   @li                    CSL_ESYS_BADHANDLE  - The handle passed is
 *                                                invalid
 *   @li                    CSL_ESYS_INVPARAMS  - The parameter passed is invalid 
 *                                                
 *   <b> Pre Condition </b>
 *   @n  CSL_edma3Init(), CSL_edma3Open() must be called successfully in that
 *       order before this API can be invoked
 *
 *   <b> Post Condition </b>
 *   @n  Edma registers are configured according to the hardware setup 
 *       parameters
 *
 *   @b Modifies
 *   @n Edma registers
 *
 *   @b Example
 *   @verbatim
            CSL_Edma3Handle             hModule;
            CSL_Edma3HwSetup            hwSetup,gethwSetup;
            CSL_Edma3Obj                edmaObj;
            CSL_Edma3QueryInfo          info;
            CSL_Edma3CmdIntr            regionIntr;
            CSL_Edma3CmdDrae            regionAccess;
            CSL_Edma3HwDmaChannelSetup  dmahwSetup[CSL_EDMA3_NUM_DMACH] = 
                                             CSL_EDMA3_DMACHANNELSETUP_DEFAULT;
            CSL_Edma3HwQdmaChannelSetup qdmahwSetup[CSL_EDMA3_NUM_QDMACH] = 
                                             CSL_EDMA3_QDMACHANNELSETUP_DEFAULT;
            CSL_Status                  status;
            Uint32                      i, passStatus = 1;
            
            
            // Module Initialization
            CSL_edma3Init(NULL);
            
            // Module Level Open    
            hModule = CSL_edma3Open(&edmaObj,CSL_EDMA3,NULL,&status);
            
            // Module Setup
            hwSetup.dmaChaSetup  = &dmahwSetup[0];
            hwSetup.qdmaChaSetup = &qdmaSetup[0];
            CSL_edma3HwSetup(hModule,&hwSetup);
                    
     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_edma3HwSetup, ".text:csl_section:edma3");
CSL_Status  CSL_edma3HwSetup(
    CSL_Edma3Handle        hMod,
    CSL_Edma3HwSetup       *setup
)
{
    Uint32        numCha;
    Uint32        tempQnum = 0;
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
                hMod->regs->DCHMAP[numCha] = 
                    CSL_FMK(EDMA3CC_DCHMAP_PAENTRY, \
                              setup->dmaChaSetup[numCha].paramNum);
#endif              
                ii = numCha % 8;
                CSL_FINSR(tempQnum,(ii * 4) + 2,(ii * 4), \
                          setup->dmaChaSetup[numCha].que);
                if (((ii + 1) % 8) == 0) {
                    hMod->regs->DMAQNUM[numCha/8] = tempQnum;
                    tempQnum = 0;
                }
            }
        }
        
        if (setup->qdmaChaSetup != NULL) { 
            for (numCha = 0 ; numCha < CSL_EDMA3_NUM_QDMACH; numCha++) {
                tempChmap = CSL_FMK(EDMA3CC_QCHMAP_PAENTRY, \
                                    setup->qdmaChaSetup[numCha].paramNum)| \
                            CSL_FMK(EDMA3CC_QCHMAP_TRWORD, \
                                    setup->qdmaChaSetup[numCha].triggerWord);
                hMod->regs->QCHMAP[numCha] = tempChmap;
                CSL_FINSR(tempQnum, (numCha * 4) + 2,(numCha * 4), \
                            setup->qdmaChaSetup[numCha].que);
            }
            
            hMod->regs->QDMAQNUM = tempQnum;
        }
    }

    return (status); 
}

