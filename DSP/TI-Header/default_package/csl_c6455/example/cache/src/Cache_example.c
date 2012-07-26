/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ===========================================================================
 *
 *   @file  Cache_example.c
 *
 *   @path  $(CSLPATH)\example\cache\src
 *
 *   @desc  Example of CACHE
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n Usage of cache CSL API for the following operations
 *       - Invalidate all L2 and L1D cache
 *       - Write back invalidate all L2 and L1D cache
 *       - Write back all L2 and L1D cache 
 *       - Invalidate the L2 and L1D cache
 *       - Write back invalidate L2 and L1D cache
 *       - Write back L2 and L1D cache
 *       - L2 normal mode
 *       - Freeze operation on L2 cache
 * 
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Cache_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
 
/* ============================================================================
 *  Revision History
 *  ===============
 *  26-Jul-2005 ds     File Created.
 *  08-Feb-2006 ds     Changed during testing on EVM. Added EMIFB CE0 as a  
 *                     device memory and supported DDR2 CSL to initialize and   
 *                     setup EMIFB(DDR2) location.
 *                     
 * ============================================================================
 */
#include <stdio.h>
#include <csl_cache.h>
#include <_csl_cache.h>
#include <csl_ddr2.h>
#include <cslr_dev.h>

/* L1 and L2 Caching Memory area */
#define CACHE_MEM    (0xE0000000)

/* Globals variables used for storing the cache data */
Uint32      temp;
Uint32      Data_1;
Uint32      Data_2;
Uint32      Data_3;
Uint32      Data_4;

/* Foraward declarations */
void subExampleEndPrint(void);
void exampleEndPrint (void);
void init_ddr2 (void);
void enableDdr2 (void);

/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.
 *
 * =============================================================================
 */

void main(void) 
{
    Uint32          cacheExampleFail = 0;
    Uint16          loopCount;
    Uint16          count;
    CACHE_L2Size    localSize[4];
    
    /* Initialize the DDR2 module */
    init_ddr2 ();
    
    /* make sure L1P is turned off */
    CACHE_setL1pSize(CACHE_L1_0KCACHE);
    
    /* make sure that L1D is turned off */
    CACHE_setL1dSize(CACHE_L1_0KCACHE);
    
    /* make sure that L2 is turned off */
    CACHE_setL2Size(CACHE_0KCACHE);
    
    /* Array used for setting L2 cache size */
    localSize[0] = CACHE_32KCACHE;
    localSize[1] = CACHE_64KCACHE;
    localSize[2] = CACHE_128KCACHE;
    localSize[3] = CACHE_256KCACHE;
    
    /* This loop is used to display the L2 cache size while performing different
     * operations on different L2 cache sizes 
     */
    for(loopCount = 0; loopCount <4; loopCount++) {
        switch(loopCount) {
            case 0:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 32K L2 cache.\n");
                subExampleEndPrint();
                break;

            case 1:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 64K L2 cache.\n");
                subExampleEndPrint();
                break;
            case 2:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 128K L2 cache.\n");
                subExampleEndPrint();
                break;

            case 3:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 256K L2 cache.\n");
                subExampleEndPrint();
                break;

            default:
                break;
        }
        
        for(count = 1; count <= 8; count++) {
            /* set a memory location */
            *(Uint32*)CACHE_MEM = 0xABCDABCD;
            
            Data_2 = 0xa5a5a5a5;
            
            /* set Mar bit for CACHE_MEM */
            CACHE_enableCaching(CACHE_EMIFB_CE00);
            
            /* turn on the L2 cache. */
            CACHE_setL2Size( localSize[loopCount]);
            
            /* read (allocate into cache) */
            Data_1 = *(Uint32*)CACHE_MEM;
            
            /* write (dirty the cache line) */
            *(Uint32*)CACHE_MEM = Data_2;
            
            /* Read the data back (make sure it matches Data_2 */
            Data_3 = *(Uint32*)CACHE_MEM;
            
            if(Data_2 != Data_3)
                printf("CACHE: Data read from cache is not same as \
                        data written.\n");
            
            switch(count) {
                /* Case #1 - invAllL2 */
                case 1:
                    /* Invalidate all the L2 cache */
                    CACHE_invAllL2(CACHE_WAIT);
                    
                    for( temp =0 ; temp < 1000; temp++)
                    {}
                    
                    /* read, this data should match data_1 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_1 != Data_4) {
                        printf("CACHE: Invalidate the All L2 cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Invalidate the All L2 cache Passed.\n");
                    }
                    
                    break;
                    
                /* Case #2 - wbInvAllL2 */
                case 2:
                    /* Writeback invalidate all the L2 cache */
                    CACHE_wbInvAllL2(CACHE_WAIT);
                    
                    for( temp =0 ; temp < 1000; temp++)
                    {}
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4) {
                        printf("CACHE: Write back invalidate All");
                        printf("L2 cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back invalidate All");
                        printf("L2 cache Passed.\n");
                    }
                    break;
                    
                /* Case #3 wbAll */
                case 3:
                    /* Writeback all the L2 cache */
                    CACHE_wbAllL2(CACHE_WAIT);
                    
                    for( temp =0 ; temp < 1000; temp++)
                    {}
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4){
                        printf("CACHE: Write back All L2 cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back All L2 cache Passed.\n");
                    }
                    break;
                    
                /* Case #4 - invL2 */
                case 4:
                    /* Invalidate the L2 cache */
                    CACHE_invL2((Uint32*)CACHE_MEM, 4, CACHE_WAIT);
                                        
                    /* read, this data should match data_1 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_1 != Data_4) {
                        printf("CACHE: Invalidate the L2 cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Invalidate the L2 cache Passed.\n");
                    }
                    break;
                    
                /* Case #5 - wbInv */
                case 5:
                    /* Writeback invalidate the L2 cache */
                    CACHE_wbInvL2((Uint32*)CACHE_MEM,1000, CACHE_WAIT);
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4) {
                        printf("CACHE: Write back invalidate");
                        printf(" L2 cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back invalidate");
                        printf("L2 cache Passed.\n");
                    }
                    break;
                    
                /* Case #6 wb */
                case 6:
                    /* Writeback L2 cache */
                    CACHE_wbL2((Uint32*)CACHE_MEM, 4, CACHE_WAIT);
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4) {
                        printf("CACHE: Write back L2 cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back L2 cache Passed.\n");
                    }
                    break;
                    
                /* Case #6 wb */
                case 7:
                    /* Set L2 cache in normal mode */
                    CACHE_setL2Mode(CACHE_L2_NORMAL);
                    
                    /* read, this data should match data_3 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_3 != Data_4) {
                        printf("CACHE: L2 Normal Mode Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: L2 Normal Mode Passed.\n");
                    }
                    break;
                    
                case 8:
                    /* Writeback invalidate the cache */
                    CACHE_wbInvAllL2(CACHE_WAIT);
                    
                    /* freeze the cache */
                    if(CACHE_setL2Mode(CACHE_L2_FREEZE) != CACHE_L2_NORMAL)
                    {}
                    
                    /* read, this would normally allocate space in the cache */
                    temp = *(Uint32*)CACHE_MEM;
                    *(Uint32*)CACHE_MEM = 0xABCDABCD;
                    
                    /* write to external memory */
                    *(Uint32*)CACHE_MEM =0xA5A5A5A5;
                    if(CACHE_setL2Mode(CACHE_L2_NORMAL) != CACHE_L2_FREEZE)
                    {}
                    Data_4 = *(Uint32*)CACHE_MEM;
                    
                    /* if the cache was frozen then the Data_4 should equal */
                    if(Data_4 != 0xA5A5A5A5) {
                        printf("CACHE: Freeze operation on Cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Freeze operation on Cache Passed.\n");
                    }
                    break;
                
                default:
                    break;
            }
            
            /* L2 is turned off */
            CACHE_setL2Size(CACHE_0KCACHE);
            /* disable caching for CE_00 */
            *(Uint32*) 0x01848380 = 0;
        }
    }

    subExampleEndPrint();

    /* Log the result.*/
    if (cacheExampleFail > 0) {
        printf ("\nCACHE: Example on L2 cache FAILED. \
                [Example Failed: %ld]\n", cacheExampleFail);
    }
    else {
        printf ("\nCACHE: Example on L2 cache PASSED\n");
    }
    
    exampleEndPrint();

    cacheExampleFail = 0;

    /*========================================================================*
     *                         L1D                                            *
     *========================================================================*/

    /* Array used for setting L1 cache size */
    localSize[0] = (CACHE_L2Size)CACHE_L1_4KCACHE;
    localSize[1] = (CACHE_L2Size)CACHE_L1_8KCACHE;
    localSize[2] = (CACHE_L2Size)CACHE_L1_16KCACHE;
    localSize[3] = (CACHE_L2Size)CACHE_L1_32KCACHE;
    
    
    /* This loop is used to display the L1 cache size while performing different
     * operations on different L1 cache sizes 
     */
    for(loopCount = 0; loopCount <4; loopCount++) {
        switch(loopCount) {
            case 0:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 4K L1 cache.\n");
                subExampleEndPrint();
                break;

            case 1:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 8K L1 cache.\n");
                subExampleEndPrint();
                break;
            case 2:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 16K L1 cache.\n");
                subExampleEndPrint();
                break;

            case 3:
                printf("\n");
                subExampleEndPrint();
                printf("CACHE: Performing operations on 32K L1 cache.\n");
                subExampleEndPrint();
                break;

            default:
                    break;
        }
        
        for(count = 1; count <= 6; count++) {
            /* set a memory location */
            *(Uint32*)CACHE_MEM = 0xABCDABCD;
            Data_2 = 0xa5a5a5a5;
            
            /* set Mar bit for CACHE_MEM */
            CACHE_enableCaching(CACHE_EMIFB_CE00);
            
            /* turn on the L1D cache. */
            CACHE_setL1dSize( (CACHE_L1Size)localSize[loopCount]);
            
            /* read (allocate into cache) */
            Data_1 = *(Uint32*)CACHE_MEM;
            
            /* write (dirty the cache line) */
            *(Uint32*)CACHE_MEM = Data_2;
            
            /* Read the data back (make sure it matches Data_2) */
            Data_3 = *(Uint32*)CACHE_MEM;
            
            if(Data_2 != Data_3)
                printf("CACHE: Data read from cache is not same as \
                        data written.\n");
            
            switch(count) {
                /* Case #1 - invAllL1D */
                case 1:
                    /* Invalidate all L1D cache */
                    CACHE_invAllL1d(CACHE_WAIT);
                    
                    /* read, this data should match data_1 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_1 != Data_4) {
                        printf("CACHE: Invalidate All L1D cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Invalidate All L1D cache Passed.\n");
                    }
                    break;
                
                /* Case #2 - wbInvAllL1D */
                case 2:
                    /* Writeback invalidate all L1D cache */
                    CACHE_wbInvAllL1d(CACHE_WAIT);
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4) {
                        printf("CACHE: Write back invalidate All");
                        printf("L1D cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back invalidate All");
                        printf(" L1D cache Passed.\n");
                    }
                    break;
                
                /* Case #3 wbAll */
                case 3:
                    /* Writeback all L1D cache */
                    CACHE_wbAllL1d(CACHE_WAIT);
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4) {
                        printf("CACHE: Write back All L1D cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back All L1D cache Passed.\n");
                    }
                    
                    break;
                    
                /* Case #4 - invL1D */
                case 4:
                    /* Invalidate L1D cache */
                    CACHE_invL1d((Uint32*)CACHE_MEM,4, CACHE_WAIT);
                    
                    /* read, this data should match data_1 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_1 != Data_4) {
                        printf("CACHE: Invalidate L1D cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Invalidate L1D cache Passed.\n");
                    }
                    break;
                
                /* Case #5 - wbInv */
                case 5:
                    /* Writeback invalidate L1D cache */
                    CACHE_wbInvL1d((Uint32*)CACHE_MEM,1000, CACHE_WAIT);
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4) {
                        printf("CACHE: Write back invalidate");
                        printf("L1D cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back invalidate");
                        printf("L1D cache Passed\n");
                    }
                    break;
                    
                /* Case #6 wb */
                case 6:
                    /* Writeback L1D cache */
                    CACHE_wbL1d((Uint32*)CACHE_MEM,1000, CACHE_WAIT);
                    
                    /* read, this data should match data_2 */
                    Data_4 = *(Uint32*)CACHE_MEM;
                    if(Data_2 != Data_4) {
                        printf("CACHE: Write back L1D cache Failed.\n");
                        cacheExampleFail++;
                    }
                    else {
                        printf("CACHE: Write back L1D cache Passed.\n");
                    }
                    break;
                
                default:
                    break;
            }
            
            /* L1D is turned off */
            CACHE_setL1dSize(CACHE_L1_0KCACHE);
        
            /* disable caching for CE_00 */
            *(Uint32*) 0x01848380 = 0;
        }
    }
    
    subExampleEndPrint();

    /* Log the result.*/
    if (cacheExampleFail > 0) {
        printf ("\nCACHE: Example on L1 cache FAILED. \
            [Example Failed: %ld]\n", cacheExampleFail);
    }
    else {
        printf ("\nCACHE: Example on L1 cache PASSED\n");
    }
    
    exampleEndPrint();
}

/*
 * ============================================================================
 *   @func   init_ddr2
 *
 *   @desc
 *     This function initialize and setup the DDR2 module 
 *
 *  @arg  
 *      None
 *
 *  @return
 *      None
 * ============================================================================
*/
void init_ddr2 (void)
{
    CSL_Ddr2Handle      hDdr2;
    CSL_Ddr2Obj         ddr2Obj;
    CSL_Status          status;
    CSL_Ddr2HwSetup     hwSetup ;     
    
    CSL_Ddr2Timing1     tim1 = {0x23, 0x4,0x4, 0x4, 0x0B, 0x0F, 0x2,0x2};
    CSL_Ddr2Timing2     tim2 = {0x2, 0x25, 0xDC, 0x2, 0x04};
    CSL_Ddr2Settings    set  = CSL_DDR2_SETTING_DEFAULTS;    
    
    /* setup the hardware parameters */
    hwSetup.refreshRate = 0x0000073B;
    hwSetup.timing1Param = &tim1;
    hwSetup.timing2Param = &tim2;
    hwSetup.setParam = &set;    
    
    /* Enable the DDR2 */
    enableDdr2 ();
        
    /* Initialize DDR2 CSL module */
    status = CSL_ddr2Init(NULL);
    if (status != CSL_SOK) {
        printf("DDR2 EMIF: Initialization error.\n");
        printf("\tReason: CSL_ddr2Init [status = 0x%x].\n", status);        
        return;
    }
    
    /* Opening the DDR2 instance */
    hDdr2 =  CSL_ddr2Open(&ddr2Obj, CSL_DDR2, NULL, &status);
    if ((status != CSL_SOK) || (hDdr2 == NULL)) {
        printf("DDR2 EMIF: Error opening the instance. [status = 0x%x, hDdr2 = \
                   0x%x]\n", status, hDdr2);        
        return;
    }
    

    /* Setting up configuration parameter using HwSetup */
    status =  CSL_ddr2HwSetup(hDdr2, &hwSetup);                     
    if (status != CSL_SOK) {
        printf("DDR2 EMIF: Error in HW Setup.\n");        
        printf("Read write operation fails\n");
        return;       
    }
    
}

/*
 * ============================================================================
 *   @func   enableDdr2
 *
 *   @desc
 *     This function enables the powerSaver for DDR2 module
 *
 *  @arg  
 *      None
 *
 *  @return
 *      None
 * ============================================================================
 */
void enableDdr2 (void)
{
    /* Unlock the PERCFG0 register */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);
               
    /* Enable the ddr2 */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG1, DEV_PERCFG1_DDR2CTL, 
               ENABLE);

    printf("Powersaver clock for DDR2 is enabled\n");
}

void subExampleEndPrint (void)
{
    printf ("*************************************************************\n");
}

void exampleEndPrint (void)
{
    printf ("=============================================================\n");
}
