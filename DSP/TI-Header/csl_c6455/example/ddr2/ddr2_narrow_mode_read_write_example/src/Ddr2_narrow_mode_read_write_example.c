/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *
 *   @file  Ddr2_narrow_mode_read_write_example.c
 *
 *   @path $(CSLPATH)\example\ddr2\Ddr2_narrow_mode_read_write_example\src
 *
 *   @desc  Read write example of DDR2 in Narrow Mode.
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example, 
 *        1. Enables clock to the DDR2 module
 *        2. Initializes and opens the CSL DDR2 module instance.
 *        3. Sets up the hardware to default values and narrow mode i.e.,  
 *           CSL_ddr2HwSetup() is called for module configuration.
 *        4. Writes the invalid values into DDR2 SDRAM area to over write the 
 *           previous values.
 *        5. Writes valid data
 *        6. Does the data comparision to ensure the written data is proper or 
 *           not and 
 *        7. Displays the messages based on step 6
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Ddr2_narrow_mode_read_write_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  21-May-2005 Ramitha Mathew. created
 *
 *  30-Nov-2005 NG Updated documentation
 * =============================================================================
 */
#include <csl_ddr2.h>
#include <cslr_dev.h>
#include <stdio.h>

/* Success Flag for data comparision */
#define DATA_MATCH_SUCCESS    1
/* Fail Flag for data comparision */
#define DATA_MATCH_FAIL       0

/* Data count(number write/readbacks) */
#define DATA_CNT    10

#define EMIFB_CE0_BASE_ADDR            (0xE0000000u)
#define SDRAM_REFRESH_RATE_DEFAULT     (0x0000073Bu)

/* Handle for the DDR2 instance */
CSL_Ddr2Handle    hDdr2;

void ddr2_readWrite(void);

/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.  
 *    
 * =============================================================================
 */
void main (
    void
)
{   
    /* Enable the ddr2 */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG1, DEV_PERCFG1_DDR2CTL, 
              ENABLE);

    printf("Powersaver clock for DDR2 is enabled\n");
    
    /* read_write functionality of DDR2 */
    ddr2_readWrite();   
    return; 
}

/*
 * =============================================================================
 *   @func  ddr2_readWrite
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *     This function demonstrates the functionality of DDR2 EMIF with the setup
 *     It implements following steps
 *          1. It opens the DDR2 module CSL
 *          2. The CSL_ddr2HwSetup is called for module configuration
 *          3. Enable 16 bit DDR2 SDRAM using CSL_ddr2HwSetup
 *          4. It writes into SDRAM area and reads back, to make sure the data
 *             is indeed written. 
 *          5. Closes CSL DDR2 module.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void ddr2_readWrite (
    void
)
{
    volatile Uint32 result, index ;
    Uint16          tempData; 
    CSL_Ddr2Obj     ddr2Obj;
    CSL_Status      status;
    CSL_Ddr2HwSetup hwSetup ;     
    
    CSL_Ddr2Timing1  tim1 = {0x23, 0x4,0x4, 0x4, 0x0B, 0x0F, 0x2,0x2};
    CSL_Ddr2Timing2  tim2 = {0x2, 0x25, 0xDC, 0x2, 0x04};
    CSL_Ddr2Settings set  = CSL_DDR2_SETTING_DEFAULTS;    

    /* Pointer that points to SDRAM start area */
    Uint16 *pDdr2Data = (Uint16 *)EMIFB_CE0_BASE_ADDR ;

    /* Clear local data structures */   
    memset(&ddr2Obj, 0, sizeof(CSL_Ddr2Obj));      
    memset(&hwSetup, 0, sizeof(CSL_Ddr2HwSetup));
    
    /* setup the hardware parameters */
    hwSetup.refreshRate = SDRAM_REFRESH_RATE_DEFAULT;
    hwSetup.timing1Param = &tim1;
    hwSetup.timing2Param = &tim2;
    set.narrowMode       = CSL_DDR2_NARROW_MODE;
    hwSetup.setParam = &set;    
        
    /* Initialize DDR2 CSL module */
    status = CSL_ddr2Init(NULL);
    if (status != CSL_SOK) {
        printf("DDR2 EMIF: Initialization error.\n");
        printf("\tReason: CSL_ddr2Init [status = 0x%x].\n", status);        
        return;
    }
    else {
        printf("DDR2 EMIF: Module Initialized.\n");
    }

    /* Opening the DDR2 instance */
    hDdr2 =  CSL_ddr2Open(&ddr2Obj, CSL_DDR2, NULL, &status);
    if ((status != CSL_SOK) || (hDdr2 == NULL)) {
        printf("DDR2 EMIF: Error opening the instance. [status = 0x%x, hDdr2 = \
                0x%x]\n", status, hDdr2);       
        return;
    }
    else {
        printf("DDR2 EMIF: Module instance opened.\n");
    }

    /* Setting up configuration parameter using HwSetup */
    status =  CSL_ddr2HwSetup(hDdr2, &hwSetup);                     
    if (status != CSL_SOK) {
        printf("DDR2 EMIF: Error in HW Setup.\n"); 
        printf("Read write operation fails\n");
        return;       
    }
    else {
        printf("DDR2 EMIF: Module Hardware setup is successful.\n");
    }
    
    /* Write 'invalid' values into DDR2 SDRAM area. This is to overwrite the 
     * previous valid values
     */
    tempData = 0xdead;
    for (index = 0; index < DATA_CNT; index++) {
        pDdr2Data[index] =  tempData;
    }

    /* Write **valid** values into SDRAM area. */
    tempData = 0x5678;
    for (index = 0; index < DATA_CNT; index++) {
        pDdr2Data[index] = tempData;
    }

    /* Verify that the data was indeed written */
    result = DATA_MATCH_SUCCESS;
    for (index = 0; index < DATA_CNT; index++) {
        if (pDdr2Data[index] != tempData) {
            result = DATA_MATCH_FAIL;                     
            break ;
        }
    }

    /* Print the appropriate message based on result */
    if (result == DATA_MATCH_SUCCESS) {     
        printf("\nWrite to and Read from DDR2 SDRAM is Successful\n"); 
    }
    else {      
        printf("\nWrite to and Read from DDR2 SDRAM is NOT Successful\n"); 
        printf("\tError in data read.[status = 0x%x]\n", status);
    }   
}

