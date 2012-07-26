/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_emifaClose.c
 *
 *  @path    $(CSLPATH)\src\emifa
 *
 *  @desc    File for functional layer of CSL API @a CSL_emifaClose()
 *           - The @a CSL_emifaClose() function definition & it's associated 
 *             functions
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  10-May-2005 RM  File Created.
 *  
 *  09-Sep-2005 NG  Updation according to coding guidelines
 *  
 * =============================================================================
 */
#include <csl_emifa.h>

/** ===========================================================================
 *   @n@b csl_emifaClose.c                                                       
 *                                                                             
 *   @b Description                                                            
 *   @n This function marks that CSL for the external memory interface instance 
 *      needsto be reopened before using any external memory interface CSL APIs.                                        
 *                                                                             
 *   @b Arguments                                                              
 *   @verbatim                                                                 
            hEmifa         Handle to the external memory interface instance         
     @endverbatim                                                              
 *                                                                             
 *   <b> Return Value </b>  CSL_Status                                         
 *   @li                 CSL_SOK            - external memory interface is 
 *                                            closed successfully                  
 *                                                                             
 *   @li                 CSL_ESYS_BADHANDLE - The handle passed is invalid  
 *                                                                             
 *   <b> Pre Condition </b>                                                    
 *   @n  Both @a CSL_emifaInit() and @a CSL_emifaOpen() must be called 
 *       successfully in order before calling @a CSL_emifaClose().
 *                                                                             
 *   <b> Post Condition </b>                                                   
 *   @n  1. The external memory interface CSL APIs cannot be called until the    
 *          external memory interface CSL is reopened again using 
 *          CSL_emifaOpen().
 *                                                                             
 *   @b Modifies                                                               
 *   @n  hEmifa structure                                                                 
 *                                                                             
 *   @b Example                                                                
 *   @verbatim                                                                 
            CSL_EmifaHandle   hEmifa;                                              
                                                                               
            ...                                                                
                                                                               
            CSL_emifaClose(hEmifa);                                               
                                                                               
            ...                                                                
     @endverbatim                                                              
 * =========================================================================== 
 */                                                                                    

#pragma CODE_SECTION (CSL_emifaClose, ".text:csl_section:emifa");                  
CSL_Status  CSL_emifaClose (
   CSL_EmifaHandle    hEmifa
)
{      
    CSL_Status  status = CSL_SOK;

    if (hEmifa != NULL) {
        hEmifa->regs = (CSL_EmifaRegsOvly)NULL;
        hEmifa->perNum = (CSL_InstNum)-1;
    }                                                                          
    else {
        status = CSL_ESYS_BADHANDLE;
    }
    
    return (status); 
}

