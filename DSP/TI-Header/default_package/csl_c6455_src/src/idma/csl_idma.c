/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *   @file  csl_idma.c
 *
 *   @path  $(CSLPATH)\src\idma
 *
 *   @desc  File for functional layer of IDMA
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 * - 23-Jun-2004 Chad Courtney File Created
 *
 ******************************************************************************/
 
/*                                                                       
 *  REVISION HISTORY:                                                   
 *  03-25-04...Initial version of Channel 1 routines.......S.Jagadeesh  
 *  05-20-04...Integration of CSL Register Layer...........C.Courtney   
 *  06-10-04...Changed Return Types of all functions except Open to     
 *             Status......................................C.Courtney   
 *  06-14-04...Removed Open/Close APIs and re-implemented Init API      
 *             Also redocumented...........................C.Courtney   
 *                                                                      
 *  DESCRIPTION:                                                        
 *  This file contains various function defeinitions that define a      
 *  IDMA (Internal DMA). Functions for Channel0 contain         
 *  support for transferring from internal memory to memory         
 *  hooked to Config space. Channel 1 functions contain support         
 *  for paging from local memories. These may be from Level 1           
 *  data memory to Level 2 memory or shared L2 memory.                  
 *                                                                      
 *  PRIVATE DATA STRUCTURES:                                            
 *                                                                      
 *  Private data structures are defined in the header file "idma.h"     
 *  and are shown below:                                                
 *                                                                      
 *  typedef struct idma1_handle                                         
 *  {                                                                   
 *      Uint32 status;                                            
 *      Uint32 reserved;                                          
 *      Uint32 *src;                                              
 *      Uint32 *dst;                                              
 *      Uint32 cnt;                                               
 *  }IDMA1_handle;                                                      
 *                                                                      
 *  This handle holds all the descriptors needed to issue a Channel 1   
 *  transfer. In the routines shown below, the cnt register             
 *  fields of this structure is used to hold information regarding      
 *  the priority of IDMA relative to CPU, and whether interrupt is      
 *  desired or not. Once these properties are set in the IDMA1_init()   
 *  function, all transfers performed on Channel 1, use this field      
 *  to submit transfers, unless they are re-configured again by         
 *  seperate calls to setpriority and setInt.                           
 *                                                                      
 *  The following configuration structure holds all the fields needed   
 *  to describe a Channel 0 transfer and has trhe following structure.  
 *                                                                      
 *  typedef struct idma0_config                                         
 *  {                                                                   
 *     Uint32   status;                                           
 *     Uint32   mask;                                             
 *     Uint32   *src;                                             
 *     Uint32   *dst;                                             
 *     Uint32   cnt;                                              
 *  }IDMA0_Config;                                                      
 *                                                                      
 *  The "src" contains the start address in internal memory or          
 *  configspace, the "dst" contains the destination address in          
 *  configspace or internal memory respectively. Transfers from         
 *  configspace to configspace using Channel 1 will raise an            
 *  exception. The mask is a 32-bit field of 1-hot encoding of          
 *  registers to access within the 32-bit register window.  The cnt     
 *  register fields of this structure is used to hold information       
 *  regarding whether interrupt is desired or not. Along with the       
 *  the number of 32-bit fields will be transfered                      
 *                                                                      
 *  FUNCTIONS SUPPORTED:                                                
 *                                                                      
 *  CHANNEL 0:                                                          
 *                                                                      
 *  int IDMA0_init(interrupt): This function set the interrupt for     
 *  transfers on Channel 0, for all further transfers. This returns the 
 *  value of the formatted IDMA0_COUNT.                                 
 *                                                                      
 *  void IDMA0_config( IDMA_Config *config): This function performs     
 *  a Channel 0 transfer using the paremeters contained in the          
 *  configuration structure pointer "config".                           
 *                                                                      
 *  void IDMA0_configArgs                                               
 *  (                                                                   
 *      Uint32 mask,                                                    
 *      Uint32 *src,                                                    
 *      Uint32 *dst,                                                    
 *      Uint32  cnt                                                     
 *   )                                                                  
 *                                                                      
 *  This function issues a Channel 0 transfer from source "src"         
 *  to destination "dst" performing "cnt" 32-word transfers in          
 *  which the individual 32-word transfers are controlled by a          
 *  "1-hot" encoding in a 32-bit field "mask". "src" and "dst"          
 *  must be word aligned, cnt must be <=15.                             
 *                                                                      
 *                                                                      
 *  Uint32 IDMA0_getStatus(): This function returns the ACTV            
 *  and PEND bits.                                                      
 *                                                                      
 *  void IDMA0_wait(): This function waits for all previous           
 *  transfers on Channel 0 to complete by waiting for ACTV == 0         
 *  && PEND==0.                                                         
 *                                                                      
 *  int IDMA0_setInt(interrupt): This function is used to set           
 *  the IDMA to interrupt the DSP on completion.                        
 *                                                                      
 *  CHANNEL 1:                                                          
 *                                                                      
 *  int IDMA1_init(priority, interrupt): This function set the         
 *  priority and interrupt for transfers on Channel 1, for all          
 *  further transfers. This returns the value of the formatted          
 *  IDMA1_COUNT.                                                        
 *                                                                      
 *  int IDMA1_copy(src, dst, byteCnt): This function transfers          
 *  "byteCnt" bytes from source "src" to destination "dst".             
 *                                                                      
 *  int IDMA1_fill(fillValue, dst, byteCnt): This function fills        
 *  destination "dst" with "byteCnt" bytes of the fill, contained       
 *  in fill_value (32-bit field". This requires the "byteCnt" to        
 *  be a multiple of four.                                              
 *                                                                      
 *  Uint32 IDMA1_getStatus(): This function returns the ACTV and        
 *  PEND bits.                                                          
 *                                                                      
 *  int IDMA1_wait(): This function waits to make sure that             
 *  all previous transfers on Channel 1 have completed by               
 *  waiting for ACTV==0 && PEND==0.                                     
 *                                                                      
 *  int IDMA1_setPriority(priority): This function is used to           
 *  set the priority between CPU and IDMA. A value of 0x111             
 *  implies that CPU is higher priority than IDMA. A value              
 *  of 0x0 implies IDMA is higher priority than CPU. These are          
 *  the only values that are allowed.                                   
 *                                                                      
 *  int IDMA1_setInt(interrupt): This function is used to set           
 *  the IDMA to interrupt the DSP on completion.                        
 *                                                                     
 */

#include <csl_idma.h>


/* Declare private handles that define Channel 0 and Channel 1         
 * properties.                                                         
 */
#pragma DATA_SECTION (idma1_handle_priv, ".bss:cslsys_section:idma");
#pragma DATA_ALIGN(idma1_handle_priv,    8);

/** Idma1 handle */
IDMA1_handle idma1_handle_priv;

#pragma DATA_SECTION (idma0_configHandle_priv, ".bss:cslsys_section:idma");
#pragma DATA_ALIGN(idma0_configHandle_priv,    8);

/** Idma0 config */
IDMA0_Config  idma0_configHandle_priv;


/** ===========================================================================
 *   @n@b IDMA1_init
 *
 *   @b Description
 *   @n This function obtains a priority and an interrupt flag and remembers
 *      them so that all future transfers on Channel 1 will use these
 *      priorities.  The priority is contained in the argument "priority" and
 *      interrupt flag in "interr".
 *      This function performs IDMA Channel 1 initialization by  setting the
 *      priority level and the enabling/disabling the interrupt event
 *      generation for the channel.
 *
 *   @b Arguments
 *   @verbatim
            priority        Priority 0-7 of handle

            interr          interrupt event generated on/off
     @endverbatim
 *
 *   <b> Return Value </b>  idma1_handle_priv.cnt
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        cnt1;

        // Initialize IDMA Channel 1
        // Set Chan 1 to have Priority 7 and Interrupt Event Gen On
        ...

        cnt1 = IDMA1_init(  IDMA_PRI_7, IDMA_INT_EN);

     @endverbatim
 * ============================================================================
 */ 
#pragma CODE_SECTION (IDMA1_init, ".text:cslsys_section:idma");
Int IDMA1_init (
    IDMA_priSet priority, 
    IDMA_intEn  interr
)
{
    Uint32  Priority;
    Uint32  Interrupt;
    Uint32  cs;
    
    /* Limit incoming priotity to a three bit field. Move the        
     * priority "pri" and the interrupt "interr" into the right      
     * locations in the count register, namely 31-28. Remeber        
     * this 32-bit field in the local handle                         
     *  "idma1_handle_priv.cnt                                       
     */
     
    cs =    _disable_interrupts();
    Priority    = ((Uint32)priority << CSL_IDMA_IDMA1_CNT_PRI_SHIFT) 
                                        & CSL_IDMA_IDMA1_CNT_PRI_MASK;
    Interrupt       = ((Uint32)interr << CSL_IDMA_IDMA1_CNT_INT_SHIFT) 
                                        & CSL_IDMA_IDMA1_CNT_INT_MASK;
    idma1_handle_priv.cnt = (Priority | Interrupt);

    /* Return the 32-bit field that has been prepared for the user */
         
    _restore_interrupts(cs);
    
    return(idma1_handle_priv.cnt);
            
}

/** ===========================================================================
 *   @n@b IDMA1_copy
 *
 *   @b Description
 *   @n IDMA1_copy() transfers "byteCnt" bytes from a source "src"
 *      to a destination "dst". It is assumed that both the source and
 *      destination addresses are in internal memory. Transfers from
 *      addresses that are not in the internal memory will raise an
 *      exception. No checking is performed by this function to check
 *      the correctness of any of the passed in arguments.
 *
 *      Used to transfer "byteCnt" bytes from source "src" to destination "dst"
 *
 *   @b Arguments
 *   @verbatim
            src        Pointer to the source address

            dst        Pointer to the destination address

            byteCnt    Number of bytes to be transferred.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of IDMA.
 *
 *   @b Example
 *   @verbatim
        Uint32        src;
        Uint32        dst;

        ...

        // Copy src to dst1 - 80 bytes - 20 words
        IDMA1_copy(src, dst1, 80);
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA1_copy, ".text:cslsys_section:idma");
Int IDMA1_copy (
    Uint32      *src,     
    Uint32      *dst,   
    Uint32      byteCnt
)
{
    volatile Uint32  pend;
    Uint32           cs;
    
    cs =    _disable_interrupts();
    
    #ifdef PEND_SUPPORT
        /* Make sure that there are no pending transfers before using 
         * this channel. This is done by reading bit "1" of the status 
         * register.                                                    
         */
        while (pend = CSL_FEXT(((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_STAT, 
                                                        IDMA_IDMA1_STAT_PEND)); 
    #endif
    
    /*  Poke in "src", "dst" and "count" with the correct          
     *  priority and interrupt flags on.                           
     */

    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_SRC     = (Uint32) src;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_DST     = (Uint32) dst;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_CNT     = ((byteCnt & 0xFFFC) 
                                                      | idma1_handle_priv.cnt);
    
    _restore_interrupts(cs);
    
    return(0);
}

/** ===========================================================================
 *   @n@b IDMA1_fill
 *
 *   @b Description
 *   @n IDMA1_fill() Takes a fill value in "fill_value" and fills
 *      "byteCnt" bytes of the "fill_value" to destination "dst".
 *
 *   @b Arguments
 *   @verbatim
            dst        Pointer to the destination address

            byteCnt    Number of bytes to be transferred.
            
            fill_value Data to be filled
            
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of IDMA.
 *
 *   @b Example
 *   @verbatim
        Uint32        dst1[100];

        ...

        IDMA1_fill(dst1, 0x800, 0xAAAABABA);
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA1_fill, ".text:cslsys_section:idma");
Int IDMA1_fill (
    Uint32      *dst,
    Uint32      byteCnt,
    Uint32      fill_value
)
{
    Uint32       cs;     
    
    /* Make sure that there are no pending tyransfers before using 
     * this channel. This is done by reading bit "1" of the status 
     * register.                                                   
     */
    cs = _disable_interrupts();
    
    #ifdef PEND_SUPPORT
        while (CSL_FEXT(((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_STAT, 
                                                        IDMA_IDMA1_STAT_PEND)); 
    #endif
    
    /*
     * Poke in "fill_value" into source and destination in the      
     * "dst". Poke in the count into the "COUNT" field.             
     */
    
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_SRC     = fill_value;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_DST     = (Uint32) dst;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_CNT     = ( (byteCnt& 0xFFFC) |  
            idma1_handle_priv.cnt |  CSL_IDMA_IDMA1_CNT_FILL_MASK );
   
    _restore_interrupts(cs);
    
    return(0);
}

/** ===========================================================================
 *   @n@b IDMA1_getStatus
 *
 *   @b Description
 *   @n IDMA1_getStatus() gets the active and pending status of IMDA    
 *      Channel 1 and returns ACTV in the least significant bit and PEND
 *      in the 2nd least significant bit                   
 *
 *      Gets the active and pending status of IDMA channel 1
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  IDMA channel 1 status.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        stat;
        
        ...
        
        stat = IDMA1_getStatus();
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA1_getStatus, ".text:cslsys_section:idma");
Uint32  IDMA1_getStatus(void)
{       
    return (((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_STAT & 
        (CSL_IDMA_IDMA1_STAT_PEND_MASK | CSL_IDMA_IDMA1_STAT_ACTV_MASK));
}

/** ===========================================================================
 *   @n@b IDMA1_wait
 *
 *   @b Description
 *   @n IDMA1_wait() waits until all previous transfers for IDMA Channel
 *      1 have been completed by making sure that both active and pend  
 *      bits are zero. These are the two least significant bits of the  
 *      status register for the channel.                                
 *
 *      Waits until previous transfers have completed for IDMA channel 1
 *      before returning.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        stat;
        
        ...
        
        stat = IDMA1_getStatus();
        IDMA1_wait();
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA1_wait, ".text:cslsys_section:idma");
void  IDMA1_wait (void)
{   
    Uint32  cs;
    
    cs = _disable_interrupts();
    
    while (((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA1_STAT & 
            (CSL_IDMA_IDMA1_STAT_PEND_MASK | CSL_IDMA_IDMA1_STAT_ACTV_MASK));
    
    _restore_interrupts(cs);
} 

/** ===========================================================================
 *   @n@b IDMA1_setPriority
 *
 *   @b Description
 *   @n IDMA1_setPriority()  set a "3-bit" priority field which has 
 *      a valid range of 0-7 for priorities 0-7. It returns the a    
 *      "32-bit" count register field back to the user. This 32-bit  
 *      register field will be used in IDMA1_copy() and IDMA1_fill() 
 *      to program the Priority and Interrupt options for IDMA Chan 1
 *
 *      Set the priority level for IDMA channel 1 transfers
 *
 *   @b Arguments
 *   @verbatim
            priority        Priority 0-7 of handle
            
     @endverbatim
 *
 *   <b> Return Value </b>  idma1_handle_priv.cnt
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        tempCnt;

        ...

        // Set and test Priority level for IDMA1
        tempCnt = IDMA1_setPriority(IDMA_PRI_2);
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA1_setPriority, ".text:cslsys_section:idma");
Int IDMA1_setPriority (
    IDMA_priSet     priority
)
{
    Uint32   Priority;
    Uint32   cs;
    
    cs = _disable_interrupts();
    Priority  = ((Uint32)priority << CSL_IDMA_IDMA1_CNT_PRI_SHIFT)
                         & CSL_IDMA_IDMA1_CNT_PRI_MASK;
    idma1_handle_priv.cnt = 
            (idma1_handle_priv.cnt & CSL_IDMA_IDMA1_CNT_INT_MASK) | Priority;
            
    _restore_interrupts(cs);
    
    return (idma1_handle_priv.cnt);
}

/** ===========================================================================
 *   @n@b IDMA1_setInt
 *
 *   @b Description
 *   @n IDMA1_setInt() set a the interrupt enable field which       
 *      is used to enable/disable interrupts for IDMA Channel 1.      
 *      It returns the a "32-bit" count register field back to the    
 *      user. This 32-bit register field will be used in IDMA1_copy() 
 *      and IDMA1_fill() to program the Priority and Interrupt options
 *      for IDMA Channel 1                                            
 *
 *      Enables/Disables interrupt event generation for IDMA channel 1 
 *      transfers
 *
 *   @b Arguments
 *   @verbatim
            interr        interrupt event generated on/off
            
     @endverbatim
 *
 *   <b> Return Value </b>  idma1_handle_priv.cnt
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        tempCnt;

        ...

        // Set and test Interrupt event gen for IDMA1 
        tempCnt = IDMA1_setInt(IDMA_INT_DIS);
     @endverbatim
 * ============================================================================
 */ 
#pragma CODE_SECTION (IDMA1_setInt, ".text:cslsys_section:idma");
Int IDMA1_setInt (
    IDMA_intEn      interr
)
{
    Uint32      Interrupt;
    Uint32      cs;
    
    cs = _disable_interrupts();
    Interrupt  = ((Uint32)interr << CSL_IDMA_IDMA1_CNT_INT_SHIFT) 
                                                & CSL_IDMA_IDMA1_CNT_INT_MASK;
    idma1_handle_priv.cnt   = 
            (idma1_handle_priv.cnt & CSL_IDMA_IDMA1_CNT_PRI_MASK) | Interrupt;
    _restore_interrupts(cs);
    
    return (idma1_handle_priv.cnt);
}

/** ===========================================================================
 *   @n@b IDMA0_init
 *
 *   @b Description
 *   @n This function obtains a interrupt enable setting and    
 *      remembers them so that all future transfers on Channel 0
 *      generate interrupts or not.                             
 *      Initializes the Interrupt Event Generation for IDMA Channel 0
 *
 *   @b Arguments
 *   @verbatim
            interr        interrupt event generated on/off
            
     @endverbatim
 *
 *   <b> Return Value </b>  idma0_configHandle_priv.cnt
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        cnt0;

        ...

        // Initialize IDMA Channel 0           
        // Set Chan 0 to have Interrupt Event Gen On 
        cnt0 = IDMA0_init(IDMA_INT_EN);
        
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA0_init, ".text:cslsys_section:idma");
Int IDMA0_init (
    IDMA_intEn  interr
)
{
    Uint32      Interrupt;
    Uint32      cs; 
    
    /* Move the interrupt enable bit "interr" into the right         
     * locations in the count register, namely bit 28. Remember       
     * this 32-bit field in the local handle                         
     *  "idma0_configHandle_priv.cnt                                 
     */
     
    cs = _disable_interrupts();
    
    Interrupt = ((Uint32)interr << CSL_IDMA_IDMA0_CNT_INT_SHIFT) 
                                                & CSL_IDMA_IDMA0_CNT_INT_MASK;
    idma0_configHandle_priv.cnt = Interrupt;

    /* Return the 32-bit field that has been prepared for the user.  */
    
    _restore_interrupts(cs);
    
    return(idma0_configHandle_priv.cnt);
            
}

/** ===========================================================================
 *   @n@b IDMA0_config
 *
 *   @b Description
 *   @n IDMA0_config() - Configures IMDA Channel 0 to perform a transfer
 *      between Internal Memory and Configuration Space based on the    
 *      data in the config structure.  "mask" provides a 1-hot encoding
 *      for the 32-word tranfer that determines which of the 32-words   
 *      are to be transfered. In the config structure "src" provides  
 *      the source location of the transfer and "dst provides the       
 *      destination location of the transfer and both must be word      
 *      aligned. The "cnt" provides the number of 32-word transfers. 
 *      Initializes the configuration for IDMA Channel 0  including 1-hot 
 *      encoding mask, source location, destination location  and count.  
 *      This is done using the structure IDMA0_Config.            
 *
 *   @b Arguments
 *   @verbatim
            config        Pointer to the Configuration structure
            
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of IDMA.
 *
 *   @b Example
 *   @verbatim
        IDMA0_Config   config
        ...
        
        IDMA0_config(&config);
        IDMA0_wait();
        
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA0_config, ".text:cslsys_section:idma");
void IDMA0_config (
    IDMA0_Config  *config
)
{
    volatile Uint32 pend;
    Uint32          cs;    
    
    /* Make sure that there are no pending tyransfers before using 
     * this channel. This is done by reading bit "1" of the status  
     * register.                                                    
     */
    cs = _disable_interrupts();      
    
    while (pend = (CSL_FEXT(((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_STAT, 
                                IDMA_IDMA0_STAT_PEND) 
                    | CSL_FEXT(((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_STAT, 
                                IDMA_IDMA0_STAT_ACTV))   ); 
    
    /*
     *  Copy src, dst, mask and count to the appropriate registers 
     *  from the structure that is passed in.                      
     */
    
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_SRC  = (Uint32) config->src;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_DST  = (Uint32) config->dst;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_MASK = config->mask;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_CNT  = config->cnt 
                                                | idma0_configHandle_priv.cnt;
    _restore_interrupts(cs);

}

/** ===========================================================================
 *   @n@b IDMA0_configArgs
 *
 *   @b Description
 *   @n IDMA0_configArgs() - Configures IMDA Channel 0 to perform a     
 *      transfer between Internal Memory and Configuration Space based  
 *      on the inputs to the function.  "mask" provides a 1-hot encoding
 *      for the 32-word tranfer that determines which of the 32-words   
 *      are to be transfered.  "src" provides the source location of the
 *      transfer and "dst provides the destination location of the      
 *      transfer and both must be word aligned. While "cnt" provides the
 *      number of 32-word transfers to perform and must not be greater  
 *      than 15.                                                        
 *        Initializes the configuration for IDMA Channel 0 including 1-hot 
 *      encoding mask, source location, destination location and count.
 *
 *   @b Arguments
 *   @verbatim
            mask        encoding value for the 32-word tranfer 
            
            src         Pointer to the source location of the transfer
            
            dst         Pointer to the destination location of the transfer
            
            cnt         number of 32-word transfers 
            
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n The hardware registers of IDMA.
 *
 *   @b Example
 *   @verbatim
        Uint32  src,dst;
        Uint32  mask;
        ...
        
        IDMA0_configArgs(mask, src, dst, 1);
        IDMA0_wait();
        
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA0_configArgs, ".text:cslsys_section:idma");
void IDMA0_configArgs (
    Uint32      mask, 
    Uint32      *src, 
    Uint32      *dst, 
    Uint32      count
)
{
    volatile Uint32 pend;
    Uint32          cs;
    
    cs = _disable_interrupts();    
    
    #ifdef PEND_SUPPORT
    
    while (pend = (CSL_FEXT(((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_STAT, 
                            IDMA_IDMA0_STAT_PEND) 
                   | CSL_FEXT(((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_STAT, 
                                IDMA_IDMA0_STAT_ACTV))); 
    
    #endif
     
    /*  Copy src, dst, mask and count to the appropriate registers 
     *  from the structure that is passed in.                       
     */
    
    
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_SRC     = (Uint32) src;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_DST     = (Uint32) dst;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_MASK    = mask;
    ((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_CNT     = count |
                                                 idma0_configHandle_priv.cnt;
    _restore_interrupts(cs);

}

/** ===========================================================================
 *   @n@b IDMA0_getStatus
 *
 *   @b Description
 *   @n IDMA0_getStatus() gets the active and pending status of IMDA    
 *      Channel 0 and returns ACTV in the least significant bit and PEND
 *      in the 2nd least significant bit                                
 *
 *      Gets the active and pending status of IDMA channel 0
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>  IDMA channel 0 status.
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        stat;
        
        ...
        
        stat = IDMA0_getStatus();
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA0_getStatus, ".text:cslsys_section:idma");
Uint32  IDMA0_getStatus(void)
{

    /* Read the status and return it as a 3-bit field.   */
    return (((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_STAT & 
        (CSL_IDMA_IDMA0_STAT_PEND_MASK | CSL_IDMA_IDMA0_STAT_ACTV_MASK));
}

/** ===========================================================================
 *   @n@b IDMA0_wait
 *
 *   @b Description
 *   @n IDMA0_wait() waits until all previous transfers for IDMA Channel
 *      0 have been completed by making sure that both active and pend  
 *      bits are zero. These are the two least significant bits of the  
 *      status register for the channel.                                
 *
 *      Waits until previous transfers have completed for IDMA channel 0
 *      before returning.
 *
 *   @b Arguments
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        stat;
        
        ...
        
        stat = IDMA0_getStatus();
        IDMA0_wait();
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA0_wait, ".text:cslsys_section:idma");
void IDMA0_wait(void)
{
    
    Uint32  cs;
    
    /* Make sure that there are no pending tyransfers before using 
     * this channel. This is done by reading bit "1" of the status  
     * register.                                                    
     */
    cs =    _disable_interrupts();          
    while (((CSL_IdmaRegs*)CSL_IDMA_0_REGS)->IDMA0_STAT & 
        (CSL_IDMA_IDMA0_STAT_PEND_MASK | CSL_IDMA_IDMA0_STAT_ACTV_MASK));
    _restore_interrupts(cs);    
}

/** ===========================================================================
 *   @n@b IDMA0_setInt
 *
 *   @b Description
 *   @n IDMA0_setInt()  set a the interrupt enable field which       
 *      is used to enable/disable interrupts for IDMA Channel 0.      
 *      It returns the a "32-bit" count register field back to the    
 *      user. This 32-bit register field will be used in              
 *      IDMA0_config() and IDMA0_configArgs() to program the Interrupt
 *      option for IDMA Channel 0                                     
 *
 *      Enables/Disables interrupt event generation for IDMA channel 0 
 *      transfers
 *
 *   @b Arguments
 *   @verbatim
            interr        interrupt event generated on/off
            
     @endverbatim
 *
 *   <b> Return Value </b>  idma0_handle_priv.cnt
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n  None
 *
 *   @b Example
 *   @verbatim
        Uint32        tempCnt;

        ...

        // Set and test Interrupt event gen for IDMA0 
        tempCnt = IDMA0_setInt(IDMA_INT_DIS);
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (IDMA0_setInt, ".text:cslsys_section:idma");
Int IDMA0_setInt (
    IDMA_intEn interr
)
{
    Uint32      Interrupt;    
    Uint32      cs;
    
    cs = _disable_interrupts();  
    
    /* Verify handle is for channel 0    */
    Interrupt = ((Uint32)interr << CSL_IDMA_IDMA0_CNT_INT_SHIFT) 
                                        & CSL_IDMA_IDMA0_CNT_INT_MASK;
    idma0_configHandle_priv.cnt = Interrupt;
    
    _restore_interrupts(cs);    
    
    return (idma0_configHandle_priv.cnt);
}
