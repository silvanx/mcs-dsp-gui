/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cGetHwStatus.c
 *
 *  @brief File for functional layer of CSL API CSL_i2cGetHwStatus()
 *
 *  @path  $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The CSL_i2cGetHwStatus() function definition & it's associated
 *      functions
 *
 *  Modification 1
 *    - Modified on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *  @author Santosh Narayanan.
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  06-Feb-2006 ds  Removed CSL_I2C_QUERY_REV, CSL_I2C_QUERY_CLASS and 
 *                  CSL_I2C_QUERY_TYPE queries
 *
 * =============================================================================
 */
#include <csl_i2c.h>
#include <csl_i2cAux.h>

/** ============================================================================
 *   @n@b CSL_i2cGetHwStatus
 *
 *   @b Description
 *   @n This function is used to read the current device configuration, status
 *      flags and the value present associated registers.Following table details
 *      the various status queries supported and the associated data structureto
 *      record the response. User should allocate memory for the said data type 
 *      and pass its pointer as an unadorned void* argument to the status query
 *      call.For details about the various status queries supported and the 
 *      associated data structure to record the response, 
 *      refer to @a CSL_I2cHwStatusQuery
 *
 *   @b Arguments
 *   @verbatim
            hI2c      Handle to the I2C instance

            query     The query to this API of I2C which indicates the
                      status to be returned.

            response  Placeholder to return the status.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVQUERY   - Invalid query command
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_i2cInit() and @a CSL_i2cOpen() must be called successfully
 *       in that order before @a CSL_i2cGetHwStatus() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example
 *   @verbatim
        CSL_I2cHandle        hI2c;
        CSL_I2cHwStatusQuery query;
        void                 reponse;

        status = CSL_i2cGetHwStatus(hI2c, query, &response);

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_i2cGetHwStatus, ".text:csl_section:i2c")
CSL_Status CSL_i2cGetHwStatus (
    CSL_I2cHandle           hI2c,
    CSL_I2cHwStatusQuery    query,
    void                    *response
)
{
    CSL_Status status = CSL_SOK;

    if (hI2c == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else if (response == NULL) {
        status = CSL_ESYS_INVPARAMS;
    }
    else {
        switch (query) {
            case CSL_I2C_QUERY_CLOCK_SETUP:
                CSL_i2cGetClockSetup(hI2c, response);
                break;

            case CSL_I2C_QUERY_BUS_BUSY:
                CSL_i2cGetBusBusy(hI2c, response);
                break;

            case CSL_I2C_QUERY_RX_RDY:
                CSL_i2cGetRxRdy(hI2c, response);
                break;

            case CSL_I2C_QUERY_TX_RDY:
                CSL_i2cGetTxRdy(hI2c, response);
                break;

            case CSL_I2C_QUERY_ACS_RDY:
                CSL_i2cGetAcsRdy(hI2c, response);
                break;

            case CSL_I2C_QUERY_SCD:
                CSL_i2cGetScd(hI2c, response);
                break;

            case CSL_I2C_QUERY_AD0:
                CSL_i2cGetAd0(hI2c, response);
                break;

            case CSL_I2C_QUERY_AAS:
                CSL_i2cGetAas(hI2c, response);
                break;

            case CSL_I2C_QUERY_RSFULL:
                CSL_i2cGetRsFull (hI2c, response);
                break;

            case CSL_I2C_QUERY_XSMT:
                CSL_i2cGetXsmt(hI2c, response);
                break;

            case CSL_I2C_QUERY_AL:
                CSL_i2cGetAl(hI2c, response);
                break;

            case CSL_I2C_QUERY_SDIR:
                CSL_i2cGetSdir(hI2c, response);
                break;

            case CSL_I2C_QUERY_NACKSNT:
                CSL_i2cGetNacksnt(hI2c, response);
                break;

            case CSL_I2C_QUERY_RDONE:
                CSL_i2cGetRdone(hI2c, response);
                break;

            case CSL_I2C_QUERY_BITCOUNT:
                CSL_i2cGetBitcount(hI2c, response);
                break;

            case CSL_I2C_QUERY_INTCODE:
                CSL_i2cGetIntcode(hI2c, response);
                break;

            default:
                status = CSL_ESYS_INVQUERY ;
                break;
        }
    }
    return (status);
}

