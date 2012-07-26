/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_mcbspHwSetupRaw.c
 *
 *   @path  $(CSLPATH)\src\mcbsp
 *
 *   @desc  File for functional layer of CSL API CSL_mcbspHwSetupRaw()
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  15-Feb-2005 NSR File Created.
 *
 *  04-Jul-2005 ds            - Register naming convention used for 
 *                              multichannel registers are changed according 
 *                              the changes in cslr_mcbsp.h
 *  21-Sep-2005 ds            - Removed the DXR and DRR register from config
 *                              data structure
 * =============================================================================
 */

#include <csl_mcbsp.h>

/** ============================================================================
 *   @n@b CSL_mcbspHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the Config Data structure.
 *
 *   @b Arguments
 *   @verbatim
            hMcbsp          Handle to the Mcbsp instance

            config          Pointer to config structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration is not
 *                                                properly initialized
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_mcbspInit() and CSL_mcbspOpen() must be called successfully
 *       in that order before this function can be called.  
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified MCBSP instance will be configured
 *       according to value passed.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified MCBSP instance.
 *
 *   @b Example
 *   @verbatim
        CSL_McbspHandle       hMcbsp;
        CSL_McbspConfig       config;
        CSL_Status            status;
        
        config.SPCR = 0x02008000;
        config.RCR  = 0x010001A0;
        config.XCR  = 0x010001A0;
        config.SRGR = 0x200F010F;
        config.PCR  = 0x00000A00;
        
        // Init Successfully done
        CSL_mcbspInit (NULL);
            
        // Open Successfully done
        hMcbsp = CSL_mcbspOpen (&mcbspObj, CSL_MCBSP_0, NULL, &status);
            
        status = CSL_mcbspHwSetupRaw (hMcbsp, &config);

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_mcbspHwSetupRaw, ".text:csl_section:mcbsp");
CSL_Status  CSL_mcbspHwSetupRaw (
    CSL_McbspHandle     hMcbsp,
    CSL_McbspConfig     *config
)
{
    CSL_Status status = CSL_SOK;

    if (hMcbsp == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (config == NULL ) {
        status = CSL_ESYS_INVPARAMS;
    }
    else{
        hMcbsp->regs->SPCR     = config->SPCR;
        hMcbsp->regs->RCR      = config->RCR ;      
        hMcbsp->regs->XCR      = config->XCR ;      
        hMcbsp->regs->SRGR     = config->SRGR;   
        hMcbsp->regs->MCR      = config->MCR ;  
        hMcbsp->regs->RCERE0   = config->RCERE0;   
        hMcbsp->regs->XCERE0   = config->XCERE0;   
        hMcbsp->regs->PCR      = config->PCR  ;  
        hMcbsp->regs->RCERE1   = config->RCERE1;   
        hMcbsp->regs->XCERE1   = config->XCERE1;   
        hMcbsp->regs->RCERE2   = config->RCERE2;   
        hMcbsp->regs->XCERE2   = config->XCERE2;   
        hMcbsp->regs->RCERE3   = config->RCERE3;   
        hMcbsp->regs->XCERE3   = config->XCERE3;     
    }

    return status;
}
