/* ============================================================================
 *  Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *  Use of this software is controlled by the terms and conditions found in the
 *  license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/* ============================================================================
 *  @file memprot_example.c
 *
 *  @path $(CSLPATH)\example\memprot\src
 *   
 *  @desc This is an example illustrating usage of the Memory protection
 * 
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example,
 *          1. Intializes and opens memory protection module 
 *          2. Sets up for the L2 Memory protection
 *          3. Get the Lock Status
 *          4. Get the Fault Status, which will clear the previous fault
 *          5. Locks the Unit if not Locked
 *          6. Writes wrong key to UnLock which will generate Fault 
 *          7. The address of MPLKCMD register will be stores the 
 *             fault address in MPFAR register
 *          8. Get the Fault Status, which will clear the previous fault
 *          9. Compares the fault address
 *          10. Displays the messages based on step 9
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Memprot_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  23-sept-2005 PSK  File Created.
 *  16-Dec-2005  ds   Updated documentation
 * =============================================================================
 */

 
#include <stdio.h>
#include <csl_memprot.h>

/* defining the attributes for pages */
#define PAGE_ATTR 0xFFFF

/* Function forwards */
void memprot_example (void); 


/* Global variable declarations */
Uint32 demoFail = 0;
Uint16 pageAttrTable[32] = {
                            PAGE_ATTR, PAGE_ATTR, PAGE_ATTR, PAGE_ATTR,
                            PAGE_ATTR, PAGE_ATTR, PAGE_ATTR, PAGE_ATTR,
                            PAGE_ATTR, PAGE_ATTR, PAGE_ATTR, PAGE_ATTR,
                            PAGE_ATTR, PAGE_ATTR, PAGE_ATTR, PAGE_ATTR,
                            PAGE_ATTR, PAGE_ATTR, PAGE_ATTR, PAGE_ATTR,
                            PAGE_ATTR, PAGE_ATTR, PAGE_ATTR, PAGE_ATTR,
                            PAGE_ATTR, PAGE_ATTR, PAGE_ATTR, PAGE_ATTR,
                            PAGE_ATTR, PAGE_ATTR, 0xFFF0, 0xFFF0
                           };

/* key values */
Uint32 key1[2] = {0xFFFF, 0xFFFF};  
Uint32 key2[2] = {0xABCD, 0xDEFA};                            

/*
 * =============================================================================
 *   @func   main
 *   
 *   @desc
 *     This is the main routine for the file.
 *
 *   @expected result
 *      If the example passes, it displays the message "PASSED"
 *      If the example fails, it displays the messae "FAILED" 
 *
 * =============================================================================
*/
void main(void)
{   
    
    printf("L2 MEMPROT EXAMPLE DEMO\n");
    
    /* Invoke example */
    memprot_example();

    if (demoFail > 0) {
        printf("Example FAILED\n");
    }
    else {
        printf("Example PASSED\n");
    }

    return;
}

/*
 * =============================================================================
 *   @func   memprot_example
 *
 *   @desc
 *      This function invokes example that prove functionalites of fault
 *      occurence when something to be written to the reserved memory.
 *      The CSL API is used to retrieve the fault address parameters. this  
 *      example gives the idea for the MEMPROT CSL usage
 *      It implements following steps
 *          1. It opens the MEMPROT module CSL
 *          2. The CSL_memprotHwSetup is called for module configuration
 *          3. Locks the Unit if not Locked
 *          4. Writes wrong key to UnLock which will generate Fault
 *          5. Get the Fault Status, which will clear the previous fault
 *          6. Compares the fault address
 *          7. Closes CSL MEMPROT module.
 *      
 *   @arg
 *      None
 *  
 *   @eg
 *      memport_csl_example();
 * =============================================================================
*/
void memprot_example (void) 
{
    CSL_MemprotObj         mpL2Obj;
    CSL_MemprotHandle      hmpL2;
    CSL_Status             status;
    CSL_MemprotHwSetup     L2MpSetup;
    CSL_MemprotLockStatus  lockStat;
    CSL_MemprotFaultStatus queryFaultStatus; 

    /* Initializing the module */
    status = CSL_memprotInit(NULL);
    if (status != CSL_SOK) {
        printf ("MEMPROT: Initialization... Failed.\n");
        printf ("\tReason: CSL_memprotInit failed. [status = 0x%x].\n", status);
        demoFail++;
        return;
    }
    
    /* Opening the Handle for the L2 */
    hmpL2 = CSL_memprotOpen(&mpL2Obj, CSL_MEMPROT_L2, NULL, &status);
    if (status != CSL_SOK || hmpL2 == NULL) {
        printf ("MEMPROT: Opening instance... Failed.\n");
        printf ("\tReason: Error opening the instance. \
                [status = 0x%x, hmpL2 = 0x%x]\n", status, hmpL2);
        demoFail++;
        return;
    }
    
    /* setup parameters */
    L2MpSetup. memPageAttr = pageAttrTable;
    L2MpSetup.numPages = 32;
    L2MpSetup.key = NULL;
    
    /* Do Setup for the L2 Memory protection */
    status = CSL_memprotHwSetup (hmpL2,&L2MpSetup);
    if (status != CSL_SOK){
            printf ("MEMPROT: Hardware setup validation... Failed.\n");
            printf ("\tReason: CSL_memprotHwSetup failed. \
                    [status = 0x%x].\n", status);
            demoFail++;
            return;
        }
    
    /* Query Lock Status */
    status = CSL_memprotGetHwStatus(hmpL2,CSL_MEMPROT_QUERY_LOCKSTAT,&lockStat);
    if (status != CSL_SOK) {
        printf ("MEMPROT: CSL_MEMPROT_QUERY_LOCKSTAT query command Failed.\n");
        demoFail++;
        return;
    }
    
    /* Query Fault Status. By doing this previous fault will be cleared(i.e once 
     *  the fault is read, the fault registers are cleared automatically) 
     */
    status = CSL_memprotGetHwStatus(hmpL2, CSL_MEMPROT_QUERY_FAULT, 
                                    &queryFaultStatus);
    if (status != CSL_SOK) {
        printf ("MEMPROT: CSL_MEMPROT_QUERY_FAULT query command... Failed.\n");
        demoFail++;
        return;
    }
   
    /* lock the Unit if not Locked */
    if ((lockStat & 0x1) == CSL_MEMPROT_LOCKSTAT_UNLOCK) {
        status = CSL_memprotHwControl(hmpL2, CSL_MEMPROT_CMD_LOCK, key1);
        if (status != CSL_SOK) {
            printf ("MEMPROT: Control command CSL_MEMPROT_CMD_LOCK Failed.\n");
            demoFail++;
            return;
         }
    }
    
    /* Try UnLocking with the wrong key. Fault occurs and the address of MPLKCMD
     * register will be stored as the fault address in MPFAR register */
    status = CSL_memprotHwControl(hmpL2, CSL_MEMPROT_CMD_UNLOCK, key2); 
    if (status != CSL_SOK) {
            printf ("MEMPROT: Control command CSL_MEMPROT_CMD_UNLOCK Failed.\n");
            demoFail++;
            return;
         }
    
    /* Query Fault Status */
    status = CSL_memprotGetHwStatus(hmpL2, CSL_MEMPROT_QUERY_FAULT, 
                                    &queryFaultStatus);
    if (status != CSL_SOK) {
        printf ("MEMPROT: CSL_MEMPROT_QUERY_FAULT query command... Failed.\n");
        demoFail++;
        return;
    }

    /* check for the fault address */
    if (queryFaultStatus.addr == (Uint32)&(hmpL2->regs->MPLKCMD)) {
        printf("L2 MEMPROT Functionality Example passed\n");
    }
    else {
        printf("L2 MEMPROT Functionality Example Failed\n");
        demoFail++;
        return;
    }
    
    return; 
}   
