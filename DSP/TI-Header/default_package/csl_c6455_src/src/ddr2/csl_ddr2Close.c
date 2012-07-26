/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2Close.c
 *
 *  @path    $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2Close()
 *           - The @a CSL_ddr2Close() function definition & it's associated 
 *             functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  11-Apr-2005 RM  File Created.
 *  
 *  05-Oct-2005 NG  Updation done according to new register layer
 *  
 * =============================================================================
 */
#include <csl_ddr2.h>

/** ============================================================================
 *   @n@b csl_ddr2Close.c                                                       
 *                                                                             
 *   @b Description                                                            
 *   @n This function marks that CSL for the external memory interface instance 
 *      is CSL for the external memory interface instance need to be reopened 
 *      before external memory interface CSL API.                                        
 *                                                                             
 *   @b Arguments                                                              
 *   @verbatim                                                                 
            hDdr2         Pointer to the object that holds reference to the
                          instance of DDR2 requested after the call        
     @endverbatim                                                              
 *                                                                             
 *   <b> Return Value </b>  CSL_Status                                         
 *   @li                    CSL_SOK            - external memory interface is 
 *                                               close successfully                  
 *                                                                             
 *   @li                    CSL_ESYS_BADHANDLE - The handle passed is invalid  
 *                                                                             
 *   <b> Pre Condition </b>                                                    
 *   @n  Both @a CSL_ddr2Init() and @a CSL_ddr2Open() must be called 
 *     successfully in that order before @a CSL_ddr2Close() can be called.
 *                                                                             
 *   <b> Post Condition </b>                                                   
 *   @n  1. The external memory interface CSL APIs can not be called until the    
 *          external memory interface CSL is reopened again using CSL_ddr2Open()   
 *                                                                             
 *   @b Modifies                                                               
 *   @n  hDdr2 structure                                                                 
 *                                                                             
 *   @b Example                                                                
 *   @verbatim                                                                 
            CSL_Ddr2Handle   hDdr2;                                              
                                                                               
            ...                                                                
                                                                               
            CSL_ddr2Close (hDdr2);                                               
                                                                               
            ...                                                                
     @endverbatim     
 *
 * =============================================================================
 */               

#pragma CODE_SECTION (CSL_ddr2Close, ".text:csl_section:ddr2");
CSL_Status  CSL_ddr2Close (
    CSL_Ddr2Handle    hDdr2
)
{      
    CSL_Status  status = CSL_SOK;
                                                                               
    if (hDdr2 != NULL) {
        hDdr2->regs    = (CSL_Ddr2RegsOvly)NULL;
        hDdr2->perNum  = (CSL_InstNum)-1;
    }
    else {
        status = CSL_ESYS_BADHANDLE;
    }
    
    return (status);
}

