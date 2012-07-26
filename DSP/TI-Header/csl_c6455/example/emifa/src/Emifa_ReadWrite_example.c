/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *
 *   @file  Emifa_ReadWrite_example.c
 *
 *   @path  $(CSLPATH)\example\emifa\src
 *
 *   @desc  Example of EMIFA
 *
 *  ============================================================================
 *   @n Target Platform: VDB
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example,

 *        1. Sets up for asynchronous and synchronous type
 *        2. Initializes and opens the CSL EMFIA module.
 *        3. Sets up the hardware parameter 
 *        4. Writes the Invalid values into EMIFA CS2 area to over write the 
 *           previous values.
 *        5. Writes valid data into CS2 area.
 *        6. Does the data comparision to ensure the written data is proper or 
 *           not and 
 *        7. Displays the messages based on step 6
 *        8. Steps 4 to 7 is repeated to write the Data into CS4 area
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Emifa_ReadWrite_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  21-May-2005 Ramitha Mathew. created 
 *  20-Jul-2005 RM  Module name changed from EMIF64 to EMIFA
 *  30-Nov-2005 NG  Updated documentation
 *  06-Feb-2006 ds  Async and sync start areas has changed to CE3 loaction
 * =============================================================================
 */
#include <csl_emifa.h>
#include <cslr_dev.h>
#include <stdio.h>

/* Success Flag for data comparision */
#define DATA_MATCH_SUCCESS     1
/* Result - Failed */
#define DATA_MATCH_FAIL        0

/* Data count(number write/readbacks) */
#define DATA_CNT               10

/* Base address of the EMIFA CE3 */
#define EMIFA_CE3_BASE_ADDR    (0xB0000000u)

#define EMIFA_MEMTYPE_ASYNC    0
#define EMIFA_MEMTYPE_SYNC     1

/* Handle for the EMIFA instance */
CSL_EmifaHandle    hEmifa;

/* Locals & Forwards */
void emifaReadWrite(void);

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
    /* Enable EMIFA */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG1, DEV_PERCFG1_EMIFACTL, \
              ENABLE);
    
    emifaReadWrite();  
       
    return; 
}

/*
 * =============================================================================
 *   @func  emifaReadWrite
 *  
 *   @arg
 *      NONE
 *
 *   @desc
 *     This function demonstrates the functionality of EMIFA with the setup
 *     It implements following steps
 *          1. Opens the EMIFA module CSL
 *          2. The CSL_emifaHwSetup is called for module configuration
 *          3. It writes into CE4 area configured for synchronous memory and 
 *             CE2 area configured for asynchronous memory reads back, to make
 *             sure the data is indeed written. 
 *          4. EMIFA module CSL is closed.
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void emifaReadWrite (
    void
)
{
    Uint32                result, index, tempData;
    CSL_EmifaObj          emifaObj;
    CSL_Status            status;
    CSL_EmifaHwSetup      hwSetup ;   

    CSL_EmifaMemType      asyncVal, syncVal;
    CSL_EmifaAsyncWait    asyncWait = CSL_EMIFA_ASYNCWAIT_DEFAULTS; 
    CSL_EmifaAsync        asyncMem = CSL_EMIFA_ASYNCCFG_DEFAULTS;
    CSL_EmifaSync         syncMem = CSL_EMIFA_SYNCCFG_DEFAULTS;

    /* Pointer that points to Async(CE3) start area */
    Uint32 *pAsyncData = (Uint32 *)EMIFA_CE3_BASE_ADDR;

    /* Pointer that points to Sync(CE3) start area */
    Uint32 *pSyncData = (Uint32 *)EMIFA_CE3_BASE_ADDR;
    
    /* Clear local data structures */   
    memset(&emifaObj, 0, sizeof(CSL_EmifaObj));      
    memset(&hwSetup, 0, sizeof(CSL_EmifaHwSetup));

    /* setting for asynchronous type */
    asyncVal.ssel = EMIFA_MEMTYPE_ASYNC;
    asyncVal.async = &asyncMem;
    asyncVal.sync = NULL;

    /* setting for synchronous type */
    syncVal.ssel = EMIFA_MEMTYPE_SYNC;
    syncVal.async = NULL;
    syncVal.sync = &syncMem;
    
    /* setup the hardware parameters */
    hwSetup.asyncWait = &asyncWait;
    hwSetup.ceCfg[0] = &asyncVal;   
    hwSetup.ceCfg[1] = NULL;
    hwSetup.ceCfg[2] = &syncVal;
    hwSetup.ceCfg[3] = NULL;      
        
    printf("\tInfo: Read-Write operations of EMIFA \n");  

    /* Initialize EMIFA CSL module */
    status = CSL_emifaInit(NULL);
    if (status != CSL_SOK) {
        printf("EMIFA: Initialization error.\n");
        printf("\tReason: CSL_emifaInit [status = 0x%x].\n", status);       
        return;
    }
    else {
        printf("EMIFA: Module Initialized.\n");
    }

    /* Opening the EMIFA instance */
    hEmifa =  CSL_emifaOpen(&emifaObj, CSL_EMIFA, NULL, &status);
    if ((status != CSL_SOK) || (hEmifa == NULL)) {
        printf("EMIFA: Error opening the instance. [status = 0x%x, hEmifa \
                = 0x%x]\n", status, hEmifa);        
        return;
    }
    else {
        printf("EMIFA: Module instance opened.\n");
    }
    
    /* Setting up configuration parameter using HwSetup */
    status =  CSL_emifaHwSetup(hEmifa, &hwSetup);                     
    if (status != CSL_SOK) {
        printf("EMIFA: Error in HW Setup.\n");          
        printf("Read write operation fails\n");
        return;       
    }
    else {
        printf("EMIFA: Module Hardware setup is successful.\n");
    }
    
    printf("\tInfo: Async read write \n"); 
    /* Write 'invalid' values into EMIFA CS2 area. This is to overwrite the 
     * previous valid values. 
     */
    tempData = 0xdeadbeef;
    for (index = 0; index < DATA_CNT; index++) {
        pAsyncData[index] = tempData;
    }

    /* Write **valid** values into CS2 area. */
    tempData = 0x55550000;
    for (index = 0; index < DATA_CNT; index++) {
        pAsyncData[index] = tempData + index;
    }

    /* Verify that the data was indeed written */
    result = DATA_MATCH_SUCCESS;
    for (index = 0; index < DATA_CNT; index++) {
        if (pAsyncData[index] != (tempData + index)) {
            result = DATA_MATCH_FAIL;                     
            break ;
        }
    }

    /* Print the appropriate messages */
    if (result == DATA_MATCH_SUCCESS) {
        printf("\nAsynchronous Read Write is Successful\n"); 
    }
    else {
        printf("\nAsynchronous Read Write is NOT Successful\n"); 
    }       

    printf("\tInfo: Sync read write  \n"); 
    /* Write 'invalid' values into EMIFA CS4 area. This is to overwrite the 
     * previous valid values. 
     */
 
    tempData = 0xdeadbeef;
    for (index = 0; index < DATA_CNT; index++) {
        pSyncData[index] = tempData;
    }

    /* Write **valid** values into CS4 area. */
    tempData = 0x56780000;
    for (index = 0; index < DATA_CNT; index++) {
        pSyncData[index] = tempData + index ;
    }

    /* Verify that the data was indeed written */
    result = DATA_MATCH_SUCCESS;
    for (index = 0; index < DATA_CNT; index++) {
        if (pSyncData[index] != (tempData + index)) {
            result = DATA_MATCH_FAIL;                  
            break ;
        }
    }

    /* Print the appropriate messages */
    if (result == DATA_MATCH_SUCCESS) {
        printf("\nSync Read Write is Successful\n"); 
    }
    else {
        printf("\nSync Read Write is NOT Successful\n"); 
        printf("\tReason:Error in data read.[status = 0x%x]\n", status);
    }      
    return;
}

