/* ==========================================================================
 * Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 * Use of this software is controlled by the terms and conditions found
 * in the license agreement under which this software has been supplied
 * provided
 * ==========================================================================
*/

/** ===========================================================================
 * @file csl_gpioHwControl.c
 *
 * @path $(CSLPATH)\src\gpio
 * 
 * @Desc File for functional layer of CSL API CSL_gpioHwControl() 
 * ============================================================================
 */
 
/* ============================================================================
 * Revision History
 * ===============
 *  10-Jun-2004 PGR   File created
 *  04-Sep-2004 Nsr  - Updated the source csl_gpioHwControl.c for the new CSL 
 *                     format.
 *  22-Feb-2005 Nsr  - Added conrol command CSL_GPIO_CMD_GET_BIT according to 
 *                     TI Issue PSG00000310. 
 *  28-Jul-2005 PSK  - Updated changes to support only one BANK
 *  
 *  11-Jan-2006 NG   - Added CSL_GPIO_CMD_SET_OUT_BIT Control Command
 *  06-Mar-2006 ds   - Changed CSL_GPIO_CMD_SET_OUT_BIT cmd to clear and set the
 *                     outbit. Renamed CSL_GPIO_CMD_SET_OUT_BIT to 
 *                     CSL_GPIO_CMD_ENABLE_DISABLE_OUTBIT
 * ============================================================================
 */

#include <csl_gpio.h>
#include <csl_gpioAux.h>

/** ============================================================================
 *   @n@b CSL_gpioHwControl
 *
 *   @b Description
 *   @n Takes a command of GPIO with an optional argument & implements it.
 *
 *   @b Arguments
 *   @verbatim
            hGpio           Handle to the GPIO instance

            cmd             The command to this API indicates the action to be
                            taken on GPIO.

            arg             An optional argument.
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_Status
 *   @li                    CSL_SOK             - Status info return successful.
 *   @li                    CSL_ESYS_BADHANDLE  - Invalid handle
 *   @li                    CSL_ESYS_INVPARAMS  - Invalid parameter
 *   @li                    CSL_ESYS_INVCMD     - Invalid command
 *   @li                    CSL_EGPIO_INVPARAM  - Invalid pin number
 *
 *   <b> Pre Condition </b>
 *   @n  Both CSL_gpioInit() and CSL_gpioOpen() must be called successfully in 
 *       order before this function.
 *
 *   <b> Post Condition </b>
 *   @n  GPIO registers are configured according to the command passed
 *
 *   @b Modifies
 *   @n The hardware registers of GPIO.
 *
 *   @b Example
 *   @verbatim
        CSL_GpioHandle         hGpio;
        CSL_GpioHwControlCmd   cmd = CSL_GPIO_CMD_BANK_INT_ENABLE;
        
        status = CSL_gpioHwControl(hGpio, cmd, NULL);

     @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_gpioHwControl, ".text:csl_section:gpio");
CSL_Status CSL_gpioHwControl ( 
    CSL_GpioHandle       hGpio,
    CSL_GpioHwControlCmd cmd, 
    void                 *arg
)
{
    CSL_Status status = CSL_SOK;
        
    if (hGpio == NULL) {
        status = CSL_ESYS_BADHANDLE;
    }

    else if ( ((cmd >= 0) && (cmd <= CSL_GPIO_CMD_ENABLE_DISABLE_OUTBIT)) \
              && ((cmd != CSL_GPIO_CMD_BANK_INT_ENABLE) && \
              (cmd != CSL_GPIO_CMD_BANK_INT_DISABLE)) && (arg == NULL)) {
        status = CSL_ESYS_INVPARAMS; 
    }
    else {
        switch (cmd) {
            case CSL_GPIO_CMD_BANK_INT_ENABLE:
                status = CSL_gpioBankIntEnable(hGpio);
                break;

            case CSL_GPIO_CMD_BANK_INT_DISABLE:
                status = CSL_gpioBankIntDisable(hGpio);
                break;

            case CSL_GPIO_CMD_CONFIG_BIT:
                status = CSL_gpioConfigBit(hGpio, (CSL_GpioPinConfig *)arg);  
                break;

            case CSL_GPIO_CMD_SET_BIT:
                status = CSL_gpioSetBit(hGpio, *((CSL_GpioPinNum *)arg));    
                break;

            case CSL_GPIO_CMD_CLEAR_BIT:
                status = CSL_gpioClearBit(hGpio, *((CSL_GpioPinNum *)arg));
                break; 

            case CSL_GPIO_CMD_GET_INPUTBIT:
                status = CSL_gpioGetInputBit(hGpio, (CSL_BitMask16 *)arg);  
                break;  

            case CSL_GPIO_CMD_GET_OUTDRVSTATE:
                status = CSL_gpioGetOutDrvState(hGpio, (CSL_BitMask16 *)arg);  
                break;    

            case CSL_GPIO_CMD_GET_BIT:
                status = CSL_gpioGetBit(hGpio, ((CSL_GpioPinData *)arg));    
                break;

            case CSL_GPIO_CMD_ENABLE_DISABLE_OUTBIT:
                status = CSL_gpioEnDisOutBit(hGpio, ((CSL_GpioPinData *)arg));    
                break;

            default:
                status = CSL_ESYS_INVCMD;
                break;
        }
    }
    return status;
}
