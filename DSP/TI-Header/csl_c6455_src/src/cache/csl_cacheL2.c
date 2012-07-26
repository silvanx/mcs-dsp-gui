/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *   @file  csl_cacheL2.c
 *
 *   @path  $(CSLPATH)\src\cache
 *
 *   @desc  File for functional layer of L2 Cache
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  23-Mar-2004 Jamon Bowen File Created
 *
 *  21-Jun-2004 Ruchika Kharwar modified
 *
 *  24-Jan-2006 ds Updated CACHE_setL2Size() API to return Old value  
 * ============================================================================= 
 */

#include <csl_cache.h>
#include <_csl_cache.h>

/** ============================================================================
 *   @n@b CACHE_setL2Size
 *
 *   @b Description
 *   @n Sets the L2 size.
 *   @n As per the specification,
 *   @n a. The old size is read from the L2CFG.
 *   @n b. The new size is programmed in L2CFG.
 *   @n c. L2CFG is read back to ensure it is set.
 *
 *   @b Arguments
 *   @verbatim
              newSize      New memory size to be programmed
     @endverbatim
 *
 *   <b> Return Value </b>  CACHE_L2Size
 *   @li                    Old Size set for L2
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Set L2 cache size
 *
 *   @b Modifies
 *   @n L2CFG register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L2Size oldSize ;

        oldSize = CACHE_setL2Size(CACHE_L2_32KCACHE);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_setL2Size, ".text:csl_section:cache");
CACHE_L2Size CACHE_setL2Size (
    CACHE_L2Size    newSize
)
{
    Uint32         curL2cfg;
    CACHE_L2Size   returnVal;
     
    curL2cfg = ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2CFG;
    returnVal = (CACHE_L2Size) CSL_FEXT(curL2cfg, CACHE_L2CFG_MODE);
    
    /* critical section */
    asm(" dint");  
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2CFG = 
                                CSL_FINS(curL2cfg, CACHE_L2CFG_MODE, newSize);
    
    newSize = (CACHE_L2Size)((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2CFG;
    
    /* End critical section */
    asm(" rint");
    
    return returnVal;
}

/** ============================================================================
 *   @n@b CACHE_setL2Mode
 *
 *   @b Description
 *   @n Sets the L2 mode.
 *   @n As per the specification,
 *   @n a. The old mode is read from the L2CFG.
 *   @n b. The new mode is programmed in L2CFG.
 *   @n c. L2CFG is read back to ensure it is set.
 *
 *   @b Arguments
 *   @verbatim
              newMode      New mode to be programmed
     @endverbatim
 *
 *   <b> Return Value </b>  CACHE_L2Mode
 *   @li                    Old Mode set for L2
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Set L2 cache mode
 *
 *   @b Modifies
 *   @n L2CFG register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L2Mode oldMode;

        oldMode = CACHE_setL2Mode(CACHE_L2_NORMAL);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_setL2Mode, ".text:csl_section:cache");
CACHE_L2Mode CACHE_setL2Mode(
    CACHE_L2Mode    newMode
)
{
    Uint32          oldval;
    CACHE_L2Mode    returnVal;
     

    /* critical section */
    asm(" dint");  
    
    oldval = ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2CFG;
    returnVal = (CACHE_L2Mode)(CSL_FEXT(oldval,CACHE_L2CFG_L2CC));
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2CFG = 
                                   CSL_FINS(oldval,CACHE_L2CFG_L2CC, newMode);
    oldval = ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2CFG;
    
    /* End critical section */
    asm(" rint");
    
    return returnVal;
}

/** ============================================================================
 *   @n@b CACHE_wbL2
 *
 *   @b Description
 *   @n Writes back range specified in L2.
 *   @n As per the specification,
 *   @n a. The start of the range that needs to be written back is programmed
 *         into L2WBAR.
 *   @n b. The byte count is programmed in L2WWC.
 *
 *   @b Arguments
 *   @verbatim
            blockPtr      Start address of range to be written back

            byteCnt       Number of bytes to be written back

            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed or not.
                          Whether the function must exit on completion/or not.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Writeback the L2 cache
 *
 *   @b Modifies
 *   @n L2WWC and L2WBAR registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbL2((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbL2, ".text:csl_section:cache");
void CACHE_wbL2 (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
)
{
     
    CACHE_waitInternal();
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WBAR = (Uint32)blockPtr;
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WWC =((byteCnt+3)>>2);  
    _CSL_cachebusyState = CACHE_WAIT_L2WB;
    _CSL_cacheEmifState = 
        (CACHE_emifState)(CSL_CACHE_EMIF_ISRANGE((Uint32)blockPtr) \
                            + CSL_CACHE_EMIF_ISEMIFBRANGE((Uint32)blockPtr));
    
    /* End critical section */
    asm(" rint");
        
    if(wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_invL2
 *
 *   @b Description
 *   @n Invalidates range specified in L2.
 *   @n As per the specification,
 *   @n a. The start of the range that needs to be written back is programmed
 *         into L2IBAR
 *   @n b. The byte count is programmed in L2IWC.
 *
 *   @b Arguments
 *   @verbatim
            blockPtr      Start address of range to be invalidated

            byteCnt       Number of bytes to be invalidated

            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed or not.
                          Whether the function must exit on completion/or not.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Invalidate the L2 cache
 *
 *   @b Modifies
 *   @n L2IBAR and L2IWC registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_invL2((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_invL2, ".text:csl_section:cache");
void CACHE_invL2 (
    void          *blockPtr,
    Uint32        byteCnt,
    CACHE_Wait    wait
)
{
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2IBAR = (Uint32)blockPtr;
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2IWC = ((byteCnt+3)>>2);       
    _CSL_cachebusyState = CACHE_WAIT_L2INV; 
    
    /* End critical section */
    asm(" rint");
        
    if(wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_wbInvL2
 *
 *   @b Description
 *   @n Writeback invalidated range specified in L2.
 *   @n As per the specification,
 *   @n a. The start of the range that needs to be written back is programmed
 *         into L2WIBAR
 *   @n b. The byte count is programmed in L2WIWC.
 *
 *   @b Arguments
 *   @verbatim
            blockPtr      Start address of range to be written back invalidated

            byteCnt       Number of bytes to be written back invalidated

            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed or not.
                          Whether the function must exit on completion/or not.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Writeback and invalidate the L2 cache
 *
 *   @b Modifies
 *   @n L2WIBAR and L2WIWC registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbInvL2((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbInvL2, ".text:csl_section:cache");
void CACHE_wbInvL2 (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
)
{
     
    CACHE_waitInternal();
       
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WIBAR = (Uint32)blockPtr;
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WIWC = ((byteCnt+3)>>2);
    _CSL_cachebusyState = CACHE_WAIT_L2WBINV;
    _CSL_cacheEmifState = 
        (CACHE_emifState)(CSL_CACHE_EMIF_ISRANGE((Uint32)blockPtr) \
                            + CSL_CACHE_EMIF_ISEMIFBRANGE((Uint32)blockPtr));
    
    /* End critical section */
    asm(" rint");
    
    if(wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_wbAllL2
 *
 *   @b Description
 *   @n Writes back all of L2.
 *   @n As per the specification,
 *   @n a. The L2WB needs to be programmed.
 *
 *   @b Arguments
 *   @verbatim
            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed or not.
                          Whether the function must exit on completion/or not.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Writeback all L2 cache
 *
 *   @b Modifies
 *   @n L2WB register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbAllL2(CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbAllL2, ".text:csl_section:cache");
void CACHE_wbAllL2 (
    CACHE_Wait      wait
)
{
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WB = 1; 
    _CSL_cachebusyState = CACHE_WAIT_L2WBALL;
    _CSL_cacheEmifState = CACHE_EMIF_AB;
    
    /* End critical section */
    asm(" rint");
    
    if(wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_invAllL2
 *
 *   @b Description
 *   @n Invalidates All of L2.
 *   @n As per the specification,
 *   @n a. The L2INV needs to be programmed.
 *
 *   @b Arguments
 *   @verbatim
            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed or not.
                          Whether the function must exit on completion/or not.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Invalidate all L2 cache
 *
 *   @b Modifies
 *   @n L2INV register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_invAllL2(CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_invAllL2, ".text:csl_section:cache");
void CACHE_invAllL2 (
    CACHE_Wait      wait
)
{
    CACHE_waitInternal(); 
      
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2INV = 1; 
    _CSL_cachebusyState = CACHE_WAIT_L2INVALL;
    
    asm(" rint");
    /* End critical section */
    
    if(wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_wbInvAllL2
 *
 *   @b Description
 *   @n Writeback invalidates All of L2.
 *   @n As per the specification,
 *   @n a. The L2WBINV needs to be programmed.
 *
 *   @b Arguments
 *   @verbatim
            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed or not.
                          Whether the function must exit on completion/or not.
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Writeback and invalidate all the L2 cache
 *
 *   @b Modifies
 *   @n L2WBINV register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbInvAllL2(CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbInvAllL2, ".text:csl_section:cache");
void CACHE_wbInvAllL2 (
    CACHE_Wait      wait
)
{
     
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WBINV = 1; 
    _CSL_cachebusyState = CACHE_WAIT_L2WBINVALL;
    _CSL_cacheEmifState = CACHE_EMIF_AB;
    
    /* End critical section */
    asm(" rint");
    
    if(wait)
        _CACHE_wait(wait);
}
