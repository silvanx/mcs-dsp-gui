/* ==========================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ==========================================================================
*/

/** ========================================================================== 
 *  @file csl_gpioGetHwStatus.c
 *  
 *  @Path $(CSLPATH)\src\gpio
 *  
 *  @desc File for functional layer of CSL API CSL_gpioGetHwStatus() 
 * ============================================================================ 
 */
 
/* ===========================================================================
 * Revision History
 * ===============
 *  11-Jun-2004 PGR file created
 *  04-Sep-2004 Nsr Updated the source csl_gpioGetHwStatus.c for the new CSL 
 *                 format.
 * ============================================================================
 */
 
#include <csl_gpio.h>
#include <csl_gpioAux.h>

/** ============================================================================
 *   @n@b CSL_gpioGetHwStatus
 *
 *   @b Description
 *   @n Gets the status of the different operations of GPIO.
 *
 *   @b Arguments
 *   @verbatim
            hGpio           Handle to the GPIO instance

            query           The query to this API of GPIO which indicates the
                            status to be returned.

            response        Placeholder to return the status.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVQUERY   - Invalid Query
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid Parameters
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_gpioInit() and CSL_gpioOpen() must be called successfully in 
 *       order before this function
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n Third parameter, response value
 *
 *   @b Example
 *   @verbatim
        CSL_GpioHandle        hGpio;
        CSL_GpioHwStatusQuery query = CSL_GPIO_QUERY_BINTEN_STAT;
        Uint32                reponse;

        status = CSL_gpioGetHwStatus(hGpio, query, &response);

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_gpioGetHwStatus, ".text:csl_section:gpio");
CSL_Status CSL_gpioGetHwStatus (
    CSL_GpioHandle        hGpio,
    CSL_GpioHwStatusQuery query, 
    void                  *response
)
{
    CSL_Status status = CSL_SOK;
    
    if (hGpio == NULL) {
        status = CSL_ESYS_BADHANDLE; 
    }

    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }

    else {
        switch (query) {            
            case CSL_GPIO_QUERY_BINTEN_STAT:
                CSL_gpioGetBintenStat(hGpio, response);
                break;    

            default:
                status = CSL_ESYS_INVQUERY;
                break;
        }
    }
    return status;
}
