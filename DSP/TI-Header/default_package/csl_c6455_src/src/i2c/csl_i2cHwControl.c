/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *  @file csl_i2cHwControl.c
 *
 *  @brief File for functional layer of CSL API CSL_i2cHwControl()
 *
 *  @path  $(CSLPATH)\i2c\src
 *
 *  Description
 *    - The CSL_i2cHwControl() function definition & it's associated
 *      functions
 *
 *  Modification 1
 *    - Modified on: 28/5/2004
 *    - Reason: created the sources
 *
 *  @date 28th May, 2004
 *    @author Santosh Narayanan.
 */
/** ============================================================================
 *  Revision History
 *  ===============
 *  31-aug-2004 Hs Updated the CSL_i2cHwControl to call respective functions.
 *  11-oct-2004 Hs updated code according to code review comments.
 * =============================================================================
 */
#include <csl_i2c.h>
#include <csl_i2cAux.h>

/** ============================================================================
 *   @n@b CSL_i2cHwControl
 *
 *   @b Description
 *   @n Control operations for the I2C.  For a particular control operation, 
 *      the pointer to the corresponding data type need to be passed as argument 
 *      to HwControl function Call.All the arguments(Structure element included) 
 *      passed to the HwControl function are inputs. For the list of commands 
 *      supported and argument type that can be @a void* casted & passed with a 
 *      particular command refer to @a CSL_I2cHwControlCmd.
 *   @b Arguments
 *   @verbatim
            hI2c        Handle to the I2C instance

            cmd         The command to this API indicates the action to be
                        taken on I2C.

            arg         An optional argument.

     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li         CSL_SOK               - Status info return successful.
 *   @li         CSL_ESYS_BADHANDLE    - Invalid handle
 *   @li         CSL_ESYS_INVCMD       - Invalid command
 *   @li         CSL_ESYS_INVPARAMS    - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  Both @a CSL_i2cInit() and @a CSL_i2cOpen() must be called successfully
 *       in that order before @a CSL_i2cHwControl() can be called.
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of I2C.
 *
 *   @b Example
 *   @verbatim
        CSL_I2cHandle         hI2c;
        CSL_I2cHwControlCmd   cmd = CSL_I2C_CMD_RESET;
        void                  arg;
        CSL_Status            status;
        ...
        status = CSL_i2cHwControl (hI2c, cmd, &arg);
        ...
     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_i2cHwControl, ".text:csl_section:i2c");
CSL_Status  CSL_i2cHwControl(
    CSL_I2cHandle          hI2c,
    CSL_I2cHwControlCmd    cmd,
    void                   *arg
)
{
    CSL_Status status = CSL_SOK;

    if (hI2c == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }
    else {
        switch (cmd) {
            case CSL_I2C_CMD_ENABLE:
                CSL_i2cEnable(hI2c);
                break;

            case CSL_I2C_CMD_RESET:
                CSL_i2cReset(hI2c);
                break;

            case CSL_I2C_CMD_OUTOFRESET:
                CSL_i2cOutOfReset(hI2c);
                break;

            case CSL_I2C_CMD_CLEAR_STATUS:
                CSL_i2cClearStatus(hI2c);
                break;

            case CSL_I2C_CMD_SET_SLAVE_ADDR:
                if (arg == NULL) {
                    status = CSL_ESYS_INVPARAMS;
                }
                else {
                    CSL_i2cSetSlaveAddr(hI2c, arg);
                }
                break;

            case CSL_I2C_CMD_SET_DATA_COUNT:
                if (arg == NULL) {
                    status = CSL_ESYS_INVPARAMS;
                }
                else {
                    CSL_i2cSetDataCount(hI2c, arg);
                }
                break;

            case CSL_I2C_CMD_START:
                CSL_i2cStart(hI2c);
                break;

            case CSL_I2C_CMD_STOP:
                CSL_i2cStop(hI2c);
                break;

            case CSL_I2C_CMD_DIR_TRANSMIT:
                CSL_i2cDirTransmit(hI2c);
                break;

            case CSL_I2C_CMD_DIR_RECEIVE:
                CSL_i2cDirReceive(hI2c);
                break;

            case CSL_I2C_CMD_RM_ENABLE:
                CSL_i2cRmEnable(hI2c);
                break;

            case CSL_I2C_CMD_RM_DISABLE:
                CSL_i2cRmDisable(hI2c);
                break;

            case CSL_I2C_CMD_DLB_ENABLE:
                CSL_i2cDlbEnable(hI2c);
                break;

            case CSL_I2C_CMD_DLB_DISABLE:
                CSL_i2cDlbDisable(hI2c);
                break;

            default:
                status = CSL_ESYS_INVCMD;
                break;
        }
    }
    return (status);
}

