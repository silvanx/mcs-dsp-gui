/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *  @file    csl_ddr2GetHwStatus.c
 *
 *  @path    $(CSLPATH)\src\ddr2
 *
 *  @desc    File for functional layer of CSL API @a CSL_ddr2GetHwStatus()
 *           - The @a CSL_ddr2GetHwStatus() function definition & it's 
 *             associated functions.
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Apr-2005 RM  File Created.
 *  
 *  05-Oct-2005 NG  Updation done according to new register layer
 *  
 * =============================================================================
 */
#include <csl_ddr2.h>
#include <csl_ddr2Aux.h>

/** ============================================================================
 * @n@b   CSL_ddr2GetHwStatus
 *
 * @b Description
 * @n This function is used to read the current device configuration, status 
 *  flags and the value present associated registers.  Following table details 
 *  the various status queries supported and the associated data structure to 
 *  record the response.  User should allocate memory for the said data type and
 *  pass its pointer as an unadorned void* argument to the status query call. 
 *  For details about the various status queries supported and the associated 
 *  data structure to record the response, refer to @a CSL_Ddr2HwStatusQuery
 *
 *   @b Arguments
 *   @verbatim      
            hDdr2           Pointer to the peripheral data object of the
                            DDR2 external memory interface instance
 
            query           The query to this API which indicates the status 
                            to be returned 
 
            response        Placeholder to return the status. @a void* casted
 
     @endverbatim
 *
 *  <b> Return Value </b>  CSL_Status
 *  @li                    CSL_SOK            - Hardware status call is 
 *                                              successful
 *  @li                    CSL_ESYS_BADHANDLE - Not a valid Handle  
 *  @li                    CSL_ESYS_INVPARAMS - Not a valid parameter  
 *  @li                    CSL_ESYS_INVQUERY  - Invalid Query
 *
 * <b> Pre Condition </b>
 *  Both @a CSL_ddr2Init() and @a CSL_ddr2Open() must be called successfully
 *  in order before callinbg @a CSL_ddr2GetHwStatus(). For the argument type 
 *  that can be @a void* casted & passed with a particular command refer to 
 *  @a CSL_Ddr2HwStatusQuery
 *
 * <b> Post Condition </b>
 * @n  None
 *
 * @b Modifies
 * @n Third parameter, response vlaue 
 *
 * @b Example:
 * @verbatim
      CSL_Ddr2Handle hDdr2;
      CSL_Status status;
      Uint16  response;
       ...
      status = CSL_ddr2GetHwStatus(hDdr2,
                                   CSL_DDR2_QUERY_REFRESH_RATE,
                                   &response);
   @endverbatim
 *
 *
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_ddr2GetHwStatus,".text:csl_section:ddr2");
CSL_Status  CSL_ddr2GetHwStatus (
    CSL_Ddr2Handle           hDdr2,
    CSL_Ddr2HwStatusQuery    query,
    void                     *response
)
{
    CSL_Status status = CSL_SOK;
     
    if(hDdr2 == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch(query) {
            case CSL_DDR2_QUERY_REV_ID:
                CSL_ddr2GetRevId(hDdr2,(CSL_Ddr2ModIdRev *)response);
                break;        

            case CSL_DDR2_QUERY_REFRESH_RATE:
                *(Uint16 *)response = CSL_ddr2GetRefreshRate(hDdr2);
                break;

            case CSL_DDR2_QUERY_SELF_REFRESH:
                *(CSL_Ddr2SelfRefresh *)response = CSL_ddr2GetSlfRfrsh(hDdr2);
                break;

            case CSL_DDR2_QUERY_ENDIAN:
                CSL_ddr2GetEndian(hDdr2,(Uint8*)response);
                break; 

            case CSL_DDR2_QUERY_IFRDY:
                CSL_ddr2GetIFRDY(hDdr2,(Uint8*)response);
                break;     

            default:
                status = CSL_ESYS_INVQUERY ;
                break;     
        }
    }
    
    return (status);
}

