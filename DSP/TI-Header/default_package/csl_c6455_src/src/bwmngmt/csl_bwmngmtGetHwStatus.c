/* ============================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * priovided
 * ============================================================================
 */


/** =========================================================================== 
 * @file csl_bwmngmtGetHwStatus.c
 *
 * @brief File for functional layer of CSL API @a CSL_bwmngmtGetHwStatus()
 *
 * @path $(CSLPATH)\bwmngmt\src
 * 
 * Description
 *   - The @a CSL_bwmngmtGetHwStatus() function definition & it's associated
 *     functions
 *
 * @date 17 Mar, 2006
 * @author PSK 
 * =============================================================================
 */

/* =============================================================================
 * Revision History
 * ===============
 * 17-Mar-2006  PSK  file created
 * =============================================================================
 */
 
#include <csl_bwmngmt.h>

/** ============================================================================
 *  @n@b CSL_bwmngmtGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of the different operations of BWMNGMT. Not Implemented.
 *      For future use.
 *   @b Arguments
 *   @verbatim

         hBwmngmt            Handle to the BWMNGMT instance

         myQuery             The query to this API of BWMNGMT which indicates the
                             status to be returned
         response            Placeholder to return the status

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *                          CSL_SOK            - Always returns
 *
 *
 *   <b> Pre Condition </b>
 *       Both CSL_bwmngmtInit() and CSL_bwmngmtOpen() must 
 *       be called successfully in that order before this function can be called
 *
 *   <b> Post Condition </b>
 *        None
 *   @b  Modifies
 *       None
 *  @b Examples:
 *  @verbatim

       CSL_BwmngmtHandle          hBwmngmt;
       CSL_BwmngmtHwStatusQuery   query;
       void                       response;
        
       // Init Successfully done
       ...
       // Open Successfully done
       ...
               
       ...
       status = CSL_bwmngmtGetHwStatus(hBwmngmt, query, &response);
       ...
       
     @endverbatim
 *
 *  ===========================================================================
 */
#pragma CODE_SECTION (CSL_bwmngmtGetHwStatus, ".text:csl_section:bwmngmt");
CSL_Status CSL_bwmngmtGetHwStatus (
    /* pointer to the object that holds reference to the
     * instance of BWMNGMT requested after the call */
    CSL_BwmngmtHandle         hBwmngmt,
    
    /* pointer to setup structure which contains the
     * information to program BWMNGMT to a useful state */
    CSL_BwmngmtHwStatusQuery   myQuery,

    void                       *response
)
{
    return CSL_SOK;

}


