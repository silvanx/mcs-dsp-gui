/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *
 *   @file  Hpi_example.c
 *
 *   @path  $(CSLPATH)\example\hpi\src
 *
 *   @desc  In this example, demonstrates the CSL HPI functionalities. 
 *
 * =============================================================================
 *   @n Target Platform: EVM
 *  ============================================================================
 *   @n <b> Example Description </b>
 *   @verbatim
      This Example, 
       1. Enables the powersaver clock of HPI.
       2. Initializes and Opens the HPI CSL module.
       3. Takes HPI out of reset.
       4. Sets Host Interrupt
       5. Queries for peripheral revision Id, class, type.
       6. Queries for host ready.

     @endverbatim
 *
 * =============================================================================
 *      
 *   <b> Procedure to run the example </b>
 *   @verbatim
 *      1. Configure the CCS setup to work with the emulator being used
 *      2. Please refer CCS manual for setup configuration and loading 
 *         proper GEL file
 *      3. Launch CCS window
 *      4. Open project Hpi_example.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *   
 * =============================================================================
 */ 
/* =============================================================================
 *  Revision History
 *  ===============
 *  21-Sep-2005 NG Created
 * 
 *  30-Nov-2005 NG Updated documentation
 *
 *  25-Jan-2006 NG Updated Example
 * =============================================================================
 */
#include <stdio.h>
#include <csl.h>
#include <csl_hpi.h>
#include <cslr_dev.h>


/* HPI Handle Initialize to NULL */
CSL_HpiHandle    hHpi = (CSL_HpiHandle) NULL;
/* CSL status */
CSL_Status    status;
Uint32        response;

/* forward declaration */
void hpi_error_exit(void);
CSL_Status hpi_example(void);

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
)
{
    Bool  hpi2En;
    /* Unlock the control register */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
               UNLOCK);
               
    /* Enable the HPI */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_HPICTL, 
               ENABLE);

    do {
        hpi2En = (Bool)CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT0, 
                                   DEV_PERSTAT0_HPISTAT);
    } while(hpi2En != TRUE);

    status = hpi_example();

    if (status == CSL_SOK) {
        printf ("HPI CSL example complete\n");
    }
    else {
        printf ("HPI CSL example is not complete\n");
    }
}

/*
 * ============================================================================
 *   @func   hpi_example
 *
 *   @desc
 *     This function will initialize the HPI module and also write and read
 *      back the value from the HPI register.
 *
 *  @arg  
 *      NONE
 *
 *  @return
 *      NONE
 * ============================================================================
*/

CSL_Status hpi_example (
    void
)
{
    CSL_HpiObj        hpiObj;
    CSL_HpiHwSetup    hwSetup;
    Uint32            arg;

    /* hardware setup for HPI */
    hwSetup.hpiCtrl = (CSL_HpiCtrl)0x4;
    hwSetup.hpiAddr.hpiaReadAddr = 0x0;
    hwSetup.hpiAddr.hpiaWrtAddr = 0x0;

    /* Initialiaze device config registers related to HPI */
    status = CSL_hpiInit(NULL);
    if (status != CSL_SOK) {
        printf("\nNot Initialized");
        hpi_error_exit();
        return status;
    }

    /* Open the hpi CSL module */
    hHpi = CSL_hpiOpen(&hpiObj, CSL_HPI, NULL, &status);
    if ((hHpi == NULL) || (status != CSL_SOK)) {
        printf("HPI: Error opening the instance. [status = 0x%x, hHpi \
                = 0x%x]\n", status, hHpi);      
        hpi_error_exit();
        return status;
    }

    status = CSL_hpiHwSetup(hHpi, &hwSetup);
    if (status != CSL_SOK) {
        printf("HPI: Hardware setup is NOT successfull\n");
        hpi_error_exit();
        return status;        
    }
    else {
        printf("HPI: Hardware setup is successfull\n");
    }

    /* Set Host Interrupt */
    arg = 1;
    status  = CSL_hpiHwControl(hHpi, CSL_HPI_CMD_SET_HINT, &arg);
    if (status != CSL_SOK) {
        printf("HPI: Not able to set Host Interrupt.\n");
        hpi_error_exit();
        return status;        
    }
    else {
        printf("HPI: Host Interrupt set \n");
    }

    /* Query for Host Ready */    
    status = CSL_hpiGetHwStatus(hHpi, CSL_HPI_QUERY_HRDY, &response);
    if (status != CSL_SOK) {
        printf("HPI: Host Not ready. \n");
        return status;
    }
    else {
        printf("HPI: Host is Ready. \n");
        printf("HPI: Response is 0x%x.\n", response);
    } 
    

    hpi_error_exit();
    return status;
}

/******************************************************************************
* @func hpi_error_exit
*
* @desc Error in executing the example. As error is occurred closing the HPI
*       handle and returning.
*
* @arg  
*   NONE
*
* @return
*   NONE
******************************************************************************/
void hpi_error_exit (
    void
)
{
    status = CSL_hpiClose(hHpi);
    if (status != CSL_SOK) {
        printf("HPI:Unable to close the instance\n");
    }
        return;
}

