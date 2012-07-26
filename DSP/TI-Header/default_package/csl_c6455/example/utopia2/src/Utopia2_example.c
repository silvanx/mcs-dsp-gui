/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *   @file  Utopia_example.c
 *
 *   @path  $(CSLPATH)\example\utopia2\utopia_txRx_sphy\src
 *
 *   @desc  This is an example for UTOPIA2 of CSL2x.  
 *        
 * ============================================================================= 
 *   @n Target Platform : VDB
 * =============================================================================
 *   @n <b> Example Description </b>
 *   @verbatim
      This Example, 
       1. Enables the powersaver clock of UTOPIA2.
       2. Configures the UTOPIA2.
       3. Queries for transmit address, receive address and event id of Utopia.
       4. Enables the transmit port and checks for the presence of transmit 
          clock.
       5. Enables the receive port and checks for the presence of receive 
          clock.

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
 *      4. Open project Utopia_txRx_sphy.pjt
 *      5. Build the project and load the .out file of the project.
 *          
 *   @endverbatim
 *
 */
/* =============================================================================
 *  Revision History
 *  ===============
 *  22-Sep-2005 NG Created
 * 
 *  07-Dec-2005 NG Updated documentation
 *
 *  25-Jan-2006 NG Updated Example
 * =============================================================================
 */

/* 
 * <include file> 
 */
#include <stdio.h>

#include <csl_utopia2.h>
#include <cslr_utopia2.h>
#include <cslr_dev.h>

#include <tistdtypes.h>

#include <csl.h>

/*
 * <Macros>
 */
/* Error Interrupt bits */
#define UTOP_ERR_RCF        0x01
#define UTOP_ERR_RCP        0x02
#define UTOP_ERR_XCF        0x11
#define UTOP_ERR_XCP        0x12
 
/* Utopia event Id */
Uint32 g_utopEventId;
Uint32 g_utopXmtAddr;    

Uint32 g_utopEvent;

Uint32 g_clkSts;
Uint32 g_txIntrFlag;

void utopia_example(void);
void utopia_config_disp(void);

/*
 * =============================================================================
 *   @func  utopia_example
 *  
 *   @desc
 *      This function will initialize the UTOPIA module and also write and read
 *      back the value from the UTOPIA register.
 *
 *   @arg
 *      NONE
 *
 *   @return 
 *      NONE
 *
 * =============================================================================
 */

void
utopia_example(
    void
)
{
    Uint32 val;
    UTOPIA2_Config    config;

    config.ucr = 0x00000000;
    /*
     * Transmit Interface Clock Count Value : 0x00FF0000
     * Receive Interface Clock Count Value  : 0x000000FF
     */
    config.cdr = 0x00FF00FF;

    UTOPIA2_config(&config);

    /*
     * Clear all the pending error bit
     * NOTE: Both clearing and disabling of error condition can be achieved by 
     *       calling UTOP_errReset() function.
     */
    printf("Clearing all pending errors...");

    UTOPIA2_errClear(UTOP_ERR_RCF);
    UTOPIA2_errClear(UTOP_ERR_RCP);
    UTOPIA2_errClear(UTOP_ERR_XCF);
    UTOPIA2_errClear(UTOP_ERR_XCP);
    printf("Done\n");

    /* Disable all error condition interrupt */
    UTOPIA2_errDisable(UTOP_ERR_RCF);
    UTOPIA2_errDisable(UTOP_ERR_RCP);
    UTOPIA2_errDisable(UTOP_ERR_XCF);
    UTOPIA2_errDisable(UTOP_ERR_XCP);

    utopia_config_disp();

    /* Transmit Address of Utopia */
    val = UTOPIA2_getXmtAddr();
    printf("Utopia Transmit Address : %x", val);

    /* Receive Address of Utopia */
    val = UTOPIA2_getRcvAddr();
    printf("Utopia Receive Address : %x", val);

    val = UTOPIA2_getEventId();
    printf("Utopia Event Id : %x", val);

    /* *********** TX clock check ****************** */

    /* Enable the transmit port */
    UTOPIA2_enableXmt();

    g_clkSts = UTOPIA2_errTest(UTOP_ERR_XCP);

    /* checks for presence of transmit clock */ 
    if (g_clkSts) {
        printf("UTOPIA: Transmit Clock present\n"); 
    }
    else {
        printf("UTOPIA: Transmit Clock not present \n"); 
        printf("Reason: Utopia Master transmit clock is not enabled\n");
    }

    /* *********** RX clock check ****************** */
    
    /* Initiate the receive port enable */
    UTOPIA2_enableRcv();
    
    g_clkSts = UTOPIA2_errTest(UTOP_ERR_RCP);

    /* checks for presence of receive clock */ 
    if (g_clkSts) {
        printf("UTOPIA: Receive Clock present\n"); 
    }
    else {
        printf("UTOPIA: Receive Clock not present \n"); 
        printf("Reason: Utopia Master receive clock is not enabled\n");
    }
    printf("UTOPIA: Example complete\n"); 
}

/*
 * =============================================================================
 *   @func  utopia_config_disp
 *  
 *   @desc
 *           Displays the configurations of UTOPIA2
 *
 *   @arg
 *      NONE
 *
 *   @return 
 *      NONE
 *
 * =============================================================================
 */
void
utopia_config_disp (
    void
)
{
    UTOPIA2_Config myConfig;
    printf("UTOPIA Configurations:\n");

    UTOPIA2_getConfig(&myConfig);

    printf("\tUCR Register\n");
    if (myConfig.ucr & 0x10000000) {
        printf("\t\tEndian         : Big\n");
    }
    else {
        printf("\t\tEndian         : Little\n");
    }

    printf("\t\tSlave Id       : %d\n",((myConfig.ucr & 0x1F000000) >> 24));
    printf("\t\tTransmit Cell  : %s\n",(((myConfig.ucr & 0x003C0000)==0)? \
                            "Standard Cell":"User Defined Cell") );
    printf("\t\tTranmit Port   : %s\n",  \
        ((myConfig.ucr & 0x00010000)?"Enabled":"Disabled"));

    printf("\t\tSlave Mode     : Single\n", \
        (myConfig.ucr & 0x00004000)?"Multi":"Single");

    /*
     * Receive User defined cell
     * NOTE: 1. UTOPIA receives standard ATM cell size of 53B
     */
    printf("\t\tReceive Cell  : %s\n",(((myConfig.ucr & 0x0000003C)==0)? \
                            "Standard Cell":"User Defined Cell") );
    printf("\t\tReceive Port   : %s\n", \
        ((myConfig.ucr & 0x00000001)?"Enabled":"Disabled"));

    /* Clock Detect Register (CDR) related stuffs 
     * NOTE: 
     *     1.The other way of setting this CDR is 
     *       UTOP_CDR_RMK(UTOP_CDR_XCCNT_DEFAULT | UTOP_CDR_RCCNT_DEFAULT)
     *
     *       Transmit/Receive Interface Clock Count Value
     *
     *     2.UTOP_CDR_XCCNT_OF(x) & UTOP_CDR_RCCNT_OF(x) is used to choose
     *       the value.
     */
    printf("\tCDR Register\n");

    printf("\t\tReceive Clock Detection  : CLOCK %s\n", \
                (((myConfig.cdr & 0x00FF0000) == 0)?"DISABLED":"ENABLED"));
 
    printf("\t\tTransmit Clock Detection : CLOCK %s\n", \
                (((myConfig.cdr & 0x000000FF) == 0)?"DISABLED":"ENABLED"));
}


/*
 * =============================================================================
 *   @func   main
 *
 *   @desc
 *     This is the main routine for the file.  
 *    
 * =============================================================================
 */
void
main (
    void
)
{

    Bool  utopia2En;
    /* Unlock the control register */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERLOCK, DEV_PERLOCK_LOCKVAL, 
              UNLOCK);
               
    /* Enable the UTOPIA2 */
    CSL_FINST(((CSL_DevRegs*)CSL_DEV_REGS)->PERCFG0, DEV_PERCFG0_UTOPIACTL, 
              ENABLE);

    do {
        utopia2En = (Bool) CSL_FEXT(((CSL_DevRegs*)CSL_DEV_REGS)->PERSTAT1, 
                                   DEV_PERSTAT1_UTOPIASTAT);
    } while(utopia2En != TRUE);

    g_clkSts = 0;
    g_txIntrFlag = 1;
    utopia_example();

}

