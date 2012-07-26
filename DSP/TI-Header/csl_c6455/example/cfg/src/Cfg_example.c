/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/* ============================================================================
 *   @file  Cfg_example.c
 *
 *   @path  $(CSLPATH)\example\cfg\src
 *
 *   @desc  Example for cfg module
 *
 *  ============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @n This example, 
 *        1. Initializes and opens the CSL INTC for CFG module.
 *        2. Initializes and opens the CSL CFG module instance.
 *        3. Clears the fault if already there
 *        4. Generates the fault interrupt by writing 1000 to the reserved s
 *           pace of internal configuration space (0x01BE0000)
 *        5. Does the fault address comparision to ensure the fault occured 
 *           in the proper address (0x01BE0000) or not
 *        6. Clears the error conditions
 *        7. Displays the messages based on step 4
 *         
 *
 *  ============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Cfg_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */

/* =============================================================================
 *  Revision History
 *  ===============
 *  28-July-2005 PSK File Created
 *  
 *  16-Dec-2005  ds  Updated documentation 
 * =============================================================================
 */

#include <csl_cfg.h>
#include <stdio.h>
#include <csl_intc.h>
#include <csl_intcAux.h>


/* Intc variable declarartions */
CSL_IntcContext             intcContext; 
CSL_IntcEventHandlerRecord  EventHandler[30];
CSL_IntcObj                 intcObjEdma;
CSL_IntcHandle              hIntcEdma; 
CSL_IntcGlobalEnableState   state;
CSL_IntcEventHandlerRecord  EventRecord;
CSL_IntcParam               vectId;

/* The data variable pointing to protected area */
Int *protData = (Int *)0x01BE0000;

/* Forward declaration */
void myIsr();
void cfg_example (void);

/* Global variables declarations */
volatile Uint32 intFlag = 0;  
Uint32      cfgExampleFail = 0;

/* Handle for the CFG instance */
CSL_CfgHandle    hCfg;

/*
 * ============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.
 *
 * ============================================================================
 */
void main(void)
{   
    /* Invoke example */
    cfg_example();

    if (cfgExampleFail) {
        printf("CFG Example FAILED\n");
    }
    else {
        printf("CFG Example PASSED\n");
    }

    return;
}

/*
 * ============================================================================
 *   @func   cfg_example
 *
 *   @desc
 *      This function invokes example that prove functionalites of fault
 *      occurence when something to be written to the reserved memory.
 *      The CSL API to retrive the fault address parameters. this is for
 *      config memory protection
 *      
 *   @arg
 *      None
 *      
 *   @expected result
 *      If the example passes, it displays the message "PASSED"
 *      If the example fails, it displays the message "FAILED" 
 *
 *   @eg
 *      cfg_example();
 * ============================================================================
*/
void cfg_example (void)
{
    CSL_CfgHandle               hCfg;
    CSL_Status                  status;
    CSL_CfgObj                  cfgObj;
    CSL_IntcParam               vectId;                             
    CSL_IntcObj                 intcObj;
    CSL_IntcHandle              hIntc; 
    CSL_IntcGlobalEnableState   state;
    CSL_IntcEventHandlerRecord  EventRecord;
    Uint32                      faultAdd;
    
    
    printf("CFG EXAMPLE DEMO\n");
    
    /* Intc Module Initialization */
    intcContext.eventhandlerRecord = EventHandler;
    intcContext.numEvtEntries = 10;
    CSL_intcInit(&intcContext);
    
    /* Enable NMIs */
    CSL_intcGlobalNmiEnable();

    /* Enable Global Interrupts */
    CSL_intcGlobalEnable(&state);
    
    /* Opening a handle for the event */
    vectId = CSL_INTC_VECTID_4;
    hIntc = CSL_intcOpen (&intcObj, CSL_INTC_EVENTID_IDMA_CMPA, &vectId, NULL);
    
    /* binding to the ISR */
    EventRecord.handler = (CSL_IntcEventHandler)&myIsr;
    EventRecord.arg = hIntc;
    CSL_intcPlugEventHandler(hIntc, &EventRecord);

    /* Enabling event */
    CSL_intcHwControl(hIntc,CSL_INTC_CMD_EVTENABLE,NULL);
    
        
    /* Initialize the CFG CSL module */
    status = CSL_cfgInit(NULL);
    if (status != CSL_SOK) {
        printf ("CFG: Initialization... Failed.\n");
        printf ("\tReason: CSL_cfgInit failed. [status = 0x%x].\n", status);
        cfgExampleFail++;
        return;
    }
    
    /* Cfg Level Open */
    hCfg = CSL_cfgOpen (&cfgObj, (CSL_InstNum)CSL_MEMPROT_CONFIG, NULL,&status);
    if ((hCfg == NULL) || (status != CSL_SOK)) {
        printf ("CFG: Cfg Opening instance... Failed.\n");
        printf ("\tReason: Error opening the instance. \
                [status = 0x%x, hCfg = 0x%x]\n", status, hCfg);
        cfgExampleFail++;
        return;
    }
        
        
    /* clear the fault if already there */
    status = CSL_cfgHwControl(hCfg, CSL_CFG_CMD_CLEAR, NULL);
    if (status != CSL_SOK) {
        printf ("CFG: The func to clear ... Failed.\n");
        cfgExampleFail++;
        return;
    }
    
    /* writing some value to the reserved space in internal configuration space
     * to generate the fault */
    *protData = 1000;
    
    printf("The Data at location [0x%X]=>0x%X\n", protData, *protData);

    /*wait for the interrupt */
     while (1) {
        if (intFlag == 1)
           break;
     }

     printf("Interrupt occured \n");

    /* Query to get the fault address */
    status = CSL_cfgGetHwStatus(hCfg, CSL_CFG_QUERY_FAULT_ADDR, &faultAdd);
    if (status != CSL_SOK) {
        printf ("\nCFG: CSL_CFG_QUERY_FAULT_ADDR query command... Failed.\n");
        cfgExampleFail++;
        return;
    }
    
    /* Verify the fault occured address */
    if ((Int *) faultAdd == protData) 
        printf ("CFG: Fault address = 0x%x \n", faultAdd);
    else {
        printf ("CFG: Fault occured in diffrent address = 0x%x \n", faultAdd);
        cfgExampleFail++;
        return;
    }
        
    /* Clears the error conditions stored in MPFAR and MPFSR */
    status = CSL_cfgHwControl(hCfg, CSL_CFG_CMD_CLEAR, NULL);
    if (status != CSL_SOK) {
        printf ("CFG: The func to clear ... Failed.\n");
        cfgExampleFail++;
        return;
    }
    
    /*Close the CFG instance */
    CSL_cfgClose(hCfg);

    return;  
}


/*
 * ============================================================================
 *   @func   myIsr
 *
 *   @desc
 *     This is the interrupt service routine function to handle the 
 *     CFG interrupt
 *
 * ============================================================================
 */
void myIsr (
    CSL_IntcEventId *event
)
{
    intFlag = intFlag + 1;
    CSL_intcEventClear(*event);
}
