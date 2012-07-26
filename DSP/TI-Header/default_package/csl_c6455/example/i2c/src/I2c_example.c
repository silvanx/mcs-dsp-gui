/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */
/** ============================================================================
 *    @file  I2C_Example.c
 *
 *   @path  $(CSLPATH)\example\i2c\src
 *
 *   @desc  Example of i2c
 *
 * =============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n The example shows the functionality of I2C in Loop back mode
 *          - Enables the I2C power saver clock
 *          - It configures the i2c in Digital Loopback mode.
 *          - Initalizes and Opens I2C instance. 
 *          - Sets up up I2C in Digital Loopback mode, clock
 *          - Takes i2c out of reset
 *          - Sets data count
 *          - Enables and starts I2C
 *          - Waits for the transfer to start
 *          - verifies the data received 
 *          - Stops the transmission and
 *          - Closes the opened instance
 *
 *==============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project I2c_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *   
 * =============================================================================
 */ 

/* =============================================================================
 *  Revision History
 *  ===============
 *  23-Sep-2005 PSK File Created.
 *
 *  07-Nov-2005 NG    - Removed the test bench specific details
 *                    - Removed power saver disable
 *  30-Nov-2005 NG Updated documentation
 *
 * =============================================================================
 */

#include <csl_i2c.h>
#include <csl_i2cAux.h>
#include <soc.h>
#include <cslr_dev.h>
#include <stdio.h>

#define CSL_I2C_MASTER_ADDR                     0x10    
#define CSL_I2C_SLAVE_ADDR                      0x10    

#define DATA_SIZE                               26 

#define CSL_I2C_CLOCK_PRESCALAR                 0x13  
#define CSL_I2C_CLOCK_CLKL                      0x4   
#define CSL_I2C_CLOCK_CLKH                      0x4

#define CSL_I2C_DISABLE_INTR                    0x7F

/* No of command that fails. */
Uint32 i2cFailCnt = 0;

/* Handle for the I2C instance */
CSL_I2cHandle    hI2c;
CSL_I2cObj       i2cObj;

/* Locals & Forwards */
void i2c_txRx_data(void);
  
/* clk set up */
CSL_I2cClkSetup    clksetup = {
                                CSL_I2C_CLOCK_PRESCALAR,
                                CSL_I2C_CLOCK_CLKL,
                                CSL_I2C_CLOCK_CLKH,
};

/*---------Global data ---------*/
Uint8    xmtBuf[DATA_SIZE];
Uint8    rcvBuf[DATA_SIZE];

/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine,which invokes the I2C example scripts
 * =============================================================================
 */
void main (
    void
)
{   
    Bool  i2cEn;
    /* Unlock the control register */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);
               
    /* Enable the I2C */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_I2CCTL, 
               ENABLE);

    do {
        i2cEn = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                  DEV_PERSTAT0_I2CSTAT);
    } while (i2cEn != TRUE);

    printf("Powersaver clock for I2C is enabled\n");
    
    /* Invoking of example Demo Script */
    i2c_txRx_data();
    
    return;
}

/*
 * =============================================================================
 *   @func  i2c_txRx_data
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *      This function demonstrates the I2C functionality.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void i2c_txRx_data (
    void
)
{	
	CSL_I2cHwSetup  hwSetup;
    CSL_Status 		status = CSL_SOK;
    CSL_I2cObj      i2cObj;
    Uint32          response;
    Uint32        datalen = DATA_SIZE,count = 0;
	Uint32	        DataCount = DATA_SIZE;
	Uint8          success = TRUE;
	Uint32	        BbResponse;
	Uint32 	        cmd_arg,index = 0;
   
    hwSetup.mode           = CSL_I2C_MODE_MASTER;
    hwSetup.dir            = CSL_I2C_DIR_TRANSMIT;
    hwSetup.addrMode       = CSL_I2C_ADDRSZ_SEVEN;
    hwSetup.sttbyteen      = CSL_I2C_STB_DISABLE;
    hwSetup.ownaddr        = CSL_I2C_SLAVE_ADDR;
    hwSetup.ackMode        = CSL_I2C_ACK_ENABLE;
    hwSetup.runMode        = CSL_I2C_FREE_MODE_DISABLE;
    hwSetup.repeatMode     = CSL_I2C_REPEAT_MODE_DISABLE;
    hwSetup.loopBackMode   = CSL_I2C_DLB_ENABLE;
    hwSetup.freeDataFormat = CSL_I2C_FDF_DISABLE;
    hwSetup.resetMode      = CSL_I2C_IRS_ENABLE;
    hwSetup.bcm            = CSL_I2C_BCM_DISABLE;
    hwSetup.inten          = 0x00;   
    hwSetup.clksetup       = &clksetup;

    /* Clear local data structures */
    memset(&i2cObj, 0, sizeof(CSL_I2cObj));
    
    /* initializes the transmit buffer */
    for (index = 0; index < DATA_SIZE; index++) {
        xmtBuf[index] = 0x41 + index;  
    }
    
    printf("Example of I2C\n");
    
    /* Initialize I2C module */
    status = CSL_i2cInit(NULL);

    if (status != CSL_SOK) {
        printf("I2C: Initialization error.\n");
        printf("\tReason: CSL_i2cInit [status = 0x%x].\n", status);
        i2cFailCnt++;
        return;
    }
    
    /* open i2c */
    hI2c = CSL_i2cOpen(&i2cObj, CSL_I2C, NULL, &status);

    if ((status != CSL_SOK) || (hI2c == NULL)) {
        printf("I2C: Error opening the instance. \
               [status = 0x%x, hI2c = 0x%x]\n", status, hI2c);
        i2cFailCnt++;
        return;
    }
    
    /* i2c hwsetup  */
    status = CSL_i2cHwSetup(hI2c, &hwSetup);

    if (status != CSL_SOK) {
        printf("I2C: Error in I2C Hw Setup. [status = 0x%x]\n",status);
        i2cFailCnt++;
        return;
    }
    
    /* i2c out of reset */
    CSL_i2cHwControl(hI2c, CSL_I2C_CMD_OUTOFRESET, NULL);  
    
	/* set data count */ 
	CSL_i2cHwControl(hI2c, CSL_I2C_CMD_SET_DATA_COUNT, &DataCount); 
	
    /* Enable I2C */
    status = CSL_i2cHwControl(hI2c, CSL_I2C_CMD_ENABLE, NULL);
    if (status != CSL_SOK) {
        printf("I2C: Error while enabling I2C. [status = 0x%x]\n", status);
        i2cFailCnt++;
        return;
    }

    /* Start I2C */
    status = CSL_i2cHwControl(hI2c, CSL_I2C_CMD_START, NULL);
    if (status != CSL_SOK) {
        printf("I2C: Error while starting I2C. [status = 0x%x]\n", status);
        return;
    }
    
    /* Wait for the transfer to start */
    do {
        CSL_i2cGetBusBusy(hI2c,&BbResponse);
    } while(BbResponse != 1);
    	
    while (datalen) {
  	    /* If Transmit Data Ready interrupt flag bit is set */
        do {
            CSL_i2cGetHwStatus(hI2c, CSL_I2C_QUERY_TX_RDY, &response);
        } while(response != 1 );
            
        /* Write the data into Data Transmit register*/
		CSL_i2cWrite(hI2c, &xmtBuf[count]);

		/* Clear the flag */
        cmd_arg  = CSL_I2C_CLEAR_XRDY;
	    if (CSL_i2cHwControl(hI2c,CSL_I2C_CMD_CLEAR_STATUS,&cmd_arg) != 
            CSL_SOK) {
		    return;
	    }
              	    	
        /* If Recieve Data Ready , then read the data */
		do {        	
  	        CSL_i2cGetHwStatus(hI2c, CSL_I2C_QUERY_RX_RDY, &response);
        } while (response != 1 /*CSL_I2C_ICSTR_RX_RDY_CHECK*/);
            
        /* Copy the data from Data Recieve register */
        CSL_i2cRead(hI2c, &rcvBuf[count]);

		/* Clear the receive ready flag */
        cmd_arg  = CSL_I2C_CLEAR_RRDY;
        if (CSL_i2cHwControl(hI2c,CSL_I2C_CMD_CLEAR_STATUS,&cmd_arg) !=
            CSL_SOK) {
            return;
        }
				
	    datalen--;
		count++;
    }
         
    /* verify the data recieved */
	for (index = 0; index < DATA_SIZE ; index++) {
		if ( rcvBuf[index] != xmtBuf[index] ) {
			printf("Received data is invalid\n");
	 	    success = FALSE;
    	    break;
    	}
    }
    
    if (success == TRUE) {
        printf("\nData transmit and receive is Successful\n");
    }
    else {
        printf("\nData transmit and receive is NOT Successful\n");
    }
    
		
	/* Stop the transmission */
    if (CSL_i2cHwControl(hI2c, CSL_I2C_CMD_STOP ,NULL) != CSL_SOK) {
        return;
    }

	/* Close the opened instance */
	if (CSL_i2cClose(hI2c) != CSL_SOK) {
        return;
    }
}

