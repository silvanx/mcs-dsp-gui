/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_emifaHwSetupRaw.c
 *
 *  @path    $(CSLPATH)\src\emifa
 *
 *  @desc    File for functional layer of CSL API @a CSL_emifaHwSetupRaw()
 *           - The @a CSL_emifaHwSetupRaw() function definition & it's 
 *             associated  functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-May-2005 RM  File Created.
 *  
 *  12-Jul-2005 RM - Changed the module name from EMIF64 to EMIFA            
 *                 - Changes made in accordance to the change in cslr_emifa.h        
 *                                
 *  09-Sep-2005 NG  Updation according to coding guidelines
 *  
 * =============================================================================
 */
#include <csl_emifa.h>

/** ============================================================================
 *   @n@b CSL_emifaHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the Config data structure.This configures registers 
 *      based on a structure of register values, as compared to HwSetup, which 
 *      configures registers based on structure of bit field values.
 *
 *   @b Arguments
 *   @verbatim
            hEmifa        Handle to the EMIFA external memory interface instance
            
            config        Pointer to the config structure containing the
                          device register values
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Configuration successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Configuration structure
 *                                                pointer is not properly
 *                                                initialized
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_ emifaInit () and CSL_emifaOpen() must be called successfully 
 *       in order before calling this function
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified EMIFA instance will be 
 *       setup according to the values passed through the Config structure
 *
 *   @b Modifies
 *   @n Hardware registers of the EMIFA 
 *    
 *   @b Example
 *   @verbatim
        CSL_EmifaHandle        hEmifa;
        CSL_EmifaConfig        config = CSL_EMIFA_CONFIG_DEFAULTS;
        CSL_Status             status;
        
        ..
        status = CSL_emifaHwSetupRaw(hEmifa, &config);       
        ...
            
     @endverbatim
 * ===========================================================================
 */

#pragma CODE_SECTION (CSL_emifaHwSetupRaw, ".text:csl_section:emifa");
CSL_Status  CSL_emifaHwSetupRaw (
    CSL_EmifaHandle    hEmifa,
    CSL_EmifaConfig    *config
)
{
    CSL_Status status = CSL_SOK;

    if(hEmifa == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if(config == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        /* setting the Chip Enable2 Configuration register */
        hEmifa->regs->CE2CFG = config->CE2CFG;   

         /* setting the Chip Enable3 Configuration register */
        hEmifa->regs->CE3CFG = config->CE3CFG;  

         /* setting the Chip Enable4 Configuration register */
        hEmifa->regs->CE4CFG = config->CE4CFG;  

         /* setting the Chip Enable5 Configuration register */
        hEmifa->regs->CE5CFG = config->CE5CFG;  

         /* setting the Asynchronous Wait Cycle Configuration register */
        hEmifa->regs->AWCC = config->AWCC;  

        /* setting the Interrupt Raw Register */
        hEmifa->regs->INTRAW = config->INTRAW;

        /* setting Interrupt Masked Register */
        hEmifa->regs->INTMSK = config->INTMSK;

        /* setting the Interrupt Mask Set Register */
        hEmifa->regs->INTMSKSET = config->INTMSKSET;

        /* setting the Interrupt Mask Clear Register */
        hEmifa->regs->INTMSKCLR = config->INTMSKCLR;

        /* setting the Burst Priority Register */
        hEmifa->regs->BPRIO = config->BPRIO;   
    }
        
    return (status);
}

