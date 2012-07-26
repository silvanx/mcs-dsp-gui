/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *
 *   @file  gpioExample.c
 *
 *   @path  $(CSLPATH)\example\gpio\src
 *
 *   @desc  example for GPIO.
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @verbatim
      This Example, 
       1. Initializes INTC, enables NMIs, enables event
       2. Initializes and opens GPIO CSL module
       3. Configures pin 5 to generate an interrupt on rising edge and 
          configures the pin as an output.
       4. Enables the bank interrupt.
       5. Sets data high.
       6. Waits for interrupt to be generated
       7. Sets the data low and closes the GPIO instance.
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project gpioExample.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  23-Sep-2005 PSK File Created
 *
 *  07-Nov-2005 NG  Updated documentation
 *
 * =============================================================================
 */

#include <csl_gpio.h>
#include <csl_intc.h>
#include <stdio.h>
#include <string.h>
#include <csl_intcAux.h>
#include <cslr_dev.h>


/* Locals & Forwards */
void gpioInternalLoopbackDemo(void);


/* Globals */
CSL_GpioHandle hGpio;

volatile Uint8 intrCnt;

int demoFail = 0;

/* Interrupt module Declarations */ 
CSL_IntcObj     gpioIntcObj;
CSL_IntcHandle  gpioIntcHandle;
CSL_IntcContext context;

CSL_IntcEventHandlerRecord isr_gpio;
CSL_IntcEventHandlerRecord record[1];

/*
 * =============================================================================
 *   @func  HandleGPIO_INT
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This function is Handler for Interrupt.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void HandleGPIO_INT (
    void *arg
)
{
    intrCnt++;
    return;
}

/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine, which invokes the example script. 
 *    
 * =============================================================================
 */
void main (
    void
)
{

    Bool  gpioEn;
   
    /* Unlock the control register */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
              UNLOCK);
               
    /* Enable the GPIO */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_GPIOCTL, 
              ENABLE);

    do {
        gpioEn = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_GPIOSTAT);
    } while (gpioEn != TRUE);

    printf("Powersaver clock for GPIO is enabled\n");
    
    
    /* Invoking example script */
    gpioInternalLoopbackDemo();

    if (demoFail) {
        printf("\nGPIO: EXAMPLE fails. \n");
    }
    else {
        printf("\nGPIO: EXAMPLE completed\n");
    }

    return;
}


/*
 * =============================================================================
 *   @func  gpioInternalLoopbackDemo
 *   
 *   @arg
 *      NONE
 *
 *   @desc
 *       Gives demo for the internal loopback mechanism for the interrupt path;      
 *       the value sent on a output pin can trigger a Rising or Falling edge
 *       interrupt.                                    
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void gpioInternalLoopbackDemo (
    void
)
{
    CSL_Status              	intStat;
    CSL_GpioPinConfig          	config;
    CSL_GpioPinNum          	pinNum;
    CSL_Status              	status;
    CSL_GpioContext         	pContext;
    CSL_GpioObj             	gpioObj;
    CSL_GpioHwSetup             hwSetup;
    CSL_IntcGlobalEnableState   state;
    CSL_IntcParam 				vectId;
 
    
    /* Initialize INTC */
    context.numEvtEntries = 1;
    context.eventhandlerRecord = record;

    intStat = CSL_intcInit(&context);
    if (intStat != CSL_SOK) {
        printf("INTR: Initialization error.\n");
        demoFail++;
        return;
    }
    
	/* Enable NMIs */
	intStat = CSL_intcGlobalNmiEnable();
	if (intStat != CSL_SOK) {
        printf("INTR: Error while enabling NMI.\n");
        demoFail++;
        return;
    }

    /* Enable all interrupts */
    intStat = CSL_intcGlobalEnable(&state);
    if (intStat != CSL_SOK) {
        printf("INTR: Error while enabling interrupt.\n");
        demoFail++;
        return;
    }
  
    /* Open interrupt module */
    vectId = CSL_INTC_VECTID_12;

	gpioIntcHandle = CSL_intcOpen(&gpioIntcObj, CSL_INTC_EVENTID_GPINT5,
                                                      &vectId, &intStat);
    if ((gpioIntcHandle == NULL) || (intStat != CSL_SOK)) {
        printf("INTR: Error opening the instance.\n");
        demoFail++;
        return;
    }
        
    /* Bind ISR to Interrupt */
    isr_gpio.handler = (CSL_IntcEventHandler)&HandleGPIO_INT;
    isr_gpio.arg = gpioIntcHandle;
    CSL_intcPlugEventHandler(gpioIntcHandle, &isr_gpio);
    
    /* Event Enable */
    CSL_intcHwControl(gpioIntcHandle, CSL_INTC_CMD_EVTENABLE, NULL);
    if (intStat != CSL_SOK) {
        printf("INTR: Error in enabling event.\n");
        demoFail++;
        return;
    }
          
    /* Initialize the GPIO CSL module */
    status = CSL_gpioInit(&pContext);
    if (status != CSL_SOK) {
        printf("GPIO: Initialization error.\n");
        demoFail++;
        return;
    }

    /* Open the CSL module */
    hGpio = CSL_gpioOpen(&gpioObj, CSL_GPIO, NULL, &status);
    if ((hGpio == NULL) || (status != CSL_SOK)) {
        printf("GPIO: Error opening the instance.\n");
        demoFail++;
        return;
    }
        
    intrCnt = 0;
    
    /* Setup hardware parameters */
    hwSetup.extendSetup = NULL;
    
    /* Setup the General Purpose IO */
    status = CSL_gpioHwSetup(hGpio, &hwSetup);
    

    /* Configure pin 5 to generate an interrupt on Rising Edge, and
     * configure it as an output, then set the data High (Low->High).
     * Set Trigger: 
     */
    config.pinNum = CSL_GPIO_PIN5;
    config.trigger = CSL_GPIO_TRIG_RISING_EDGE;
    config.direction = CSL_GPIO_DIR_OUTPUT;
    
    /* Enable the bank interrupt */
    status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_BANK_INT_ENABLE, NULL);
    if (status != CSL_SOK) {
        printf("GPIO: Command to enable bank interrupt... Failed.\n");
        demoFail++;
    }
    
    /* configure the gpio pin 5 */
    status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_CONFIG_BIT, &config);
    if (status != CSL_SOK) {
        printf("GPIO: GPIO pin configuration error.\n");
        demoFail++;
        return;
    }
        
    /* Set Data High: */
    pinNum = CSL_GPIO_PIN5;
    status = CSL_gpioHwControl (hGpio, CSL_GPIO_CMD_SET_BIT, &pinNum);
    if (status != CSL_SOK) {
        printf("GPIO: Command to set bit... Failed.\n");
        demoFail++;
        return;
    }
    
    /* Wait for interrupt to be generated. */
    while (1) {
        if (intrCnt == 1)
            break;
    }

    printf("\n GPIO: Interrupt Occurred.\n");

    /* Set Data Low again: */
    pinNum = CSL_GPIO_PIN5;
    status = CSL_gpioHwControl(hGpio, CSL_GPIO_CMD_CLEAR_BIT, &pinNum);
    if (status != CSL_SOK) {
        printf("GPIO: Command to clear bit... Failed.\n");
        demoFail++;
        return;
    }

	status = CSL_gpioClose(hGpio);
    if (status != CSL_SOK) {
        printf("GPIO: Unable to Close the instance.[status = 0x%x].\n", status);
		demoFail++;
        return;
    }
}

