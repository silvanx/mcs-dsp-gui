/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** 
 *  @file    csl_hpiHwSetupRaw.c
 *
 *  @path    $(CSLPATH)\src\hpi
 *
 *  @brief   File for functional layer of CSL API @a CSL_hpiHwSetupRaw()
 *
 */
#include <csl_hpi.h>

/** ============================================================================
 *   @n@b CSL_hpiHwSetupRaw
 *
 *   @b Description
 *   @n This function initializes the device registers with the register-values
 *      provided through the Config Data structure.
 *
 *   @b Arguments
 *   @verbatim
            hHpi        Handle to the HPI instance

            config          Pointer to Config structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li            CSL_SOK               - Configuration successful
 *   @li            CSL_ESYS_BADHANDLE    - Invalid handle
 *   @li            CSL_ESYS_INVPARAMS    - Configuration is not
                                            properly initialized
 *   <b> Pre Condition </b>
 *   @n  CSL_hpiInit() and CSL_hpiOpen() must be called successfully in 
 *       order before calling CSL_hpiGetHwSetupRaw().
 *
 *   <b> Post Condition </b>
 *   @n  The registers of the specified HPI instance will be setup
 *       according to input configuration structure values.
 *
 *   @b Modifies
 *   @n Hardware registers of the specified HPI instance.
 *
 *   @b Example
 *   @verbatim
        CSL_HpiHandle       hHpi;
        CSL_HpiConfig       config = CSL_HPI_CONFIG_DEFAULTS;
        CSL_Status           status;

        status = CSL_hpiHwSetupRaw(hHpi, &config);

     @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_hpiHwSetupRaw, ".text:csl_section:hpi");
CSL_Status CSL_hpiHwSetupRaw (
    CSL_HpiHandle    hHpi,
    CSL_HpiConfig    *config
)
{
    CSL_Status status = CSL_SOK;
    
    if (hHpi == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (config == NULL ) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        hHpi->regs->PWREMU_MGMT = config->PWREMU_MGMT; 
        hHpi->regs->HPIC = config->HPIC;       
        hHpi->regs->HPIAW = config->HPIAW;      
        hHpi->regs->HPIAR = config->HPIAR;      
    }
    return (status);
}

