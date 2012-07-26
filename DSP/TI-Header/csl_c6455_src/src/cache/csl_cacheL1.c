/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *   @file  csl_cacheL1.c
 *
 *   @path  $(CSLPATH)\src\cache
 *
 *   @desc  File for functional layer of L1 Cache
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  23-Mar-2004 Jamon Bowen File Created
 *
 *  21-Jun-2004 Ruchika Kharwar modified.
 *
 *  24-Jan-2006 ds Updated CACHE_setL1pSize() API to return Old value  
 * ============================================================================= 
 */

#include <csl_cache.h>
#include <_csl_cache.h>

/** ============================================================================
 *   @n@b CACHE_freezeL1
 *
 *   @b Description
 *   @n Freezes the L1P and L1D.
 *   @n As per the specification,
 *   @n a. The new freeze state is programmed in L1DCC, L1PCC.
 *   @n b. The old state is read from the L1DCC, L1PCC from the POPER field.
 *   @n    This latter read accomplishes 2 things, viz. Ensuring the new state
 *         is programmed as well as reading the old programmed value.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  CACHE_L1_Freeze
 *   @li                    CACHE_L1_FREEZE  - Old Freeze State of L1 Cache
 *   @li                    CACHE_L1P_FREEZE - Old Freeze State of L1P Cache  
 *   @li                    CACHE_L1D_FREEZE - Old Freeze State of L1D Cache
 *   @li                    CACHE_L1_NORMAL  - Normal State of L1 Cache
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Freeze L1 cache
 *
 *   @b Modifies
 *   @n L1DCC and L1PCC registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_freezeL1();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_freezeL1, ".text:csl_section:cache");
CACHE_L1_Freeze CACHE_freezeL1(void)
{
    Uint32      oldL1DFrz;
    Uint32      oldL1PFrz;
     
    /* Critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DCC = \
                        CSL_FMK(CACHE_L1DCC_OPER, CSL_CACHE_L1DCC_OPER_FREEZE);
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PCC = \
                        CSL_FMK(CACHE_L1PCC_OPER, CSL_CACHE_L1PCC_OPER_FREEZE);
    oldL1DFrz = CSL_FEXT(((CSL_CacheRegsOvly) \
                                  CSL_CACHE_0_REGS)->L1DCC, CACHE_L1DCC_POPER);
    oldL1PFrz = CSL_FEXT(((CSL_CacheRegsOvly) \
                                  CSL_CACHE_0_REGS)->L1PCC, CACHE_L1PCC_POPER);
    
    asm(" rint");
    /* End Critical section */

    /*  return cache state if a single freeze is returned then the other */
    if (oldL1DFrz == CSL_CACHE_L1DCC_OPER_FREEZE) {
        if (oldL1PFrz == CSL_CACHE_L1PCC_OPER_FREEZE)
            return CACHE_L1_FREEZE;
        else
            return CACHE_L1D_FREEZE;    
    }
    else {
        if (oldL1PFrz == CSL_CACHE_L1PCC_OPER_FREEZE)
            return CACHE_L1P_FREEZE;
        else
            return CACHE_L1_NORMAL;
    }
}

/** ============================================================================
 *   @n@b CACHE_unfreezeL1
 *
 *   @b Description
 *   @n Unfreezes the L1P and L1D.
 *   @n As per the specification,
 *   @n a. The new unfreeze state is programmed in L1DCC, L1PCC.
 *   @n b. The old state is read from the L1DCC, L1PCC from the POPER field.
 *   @n    This latter read accomplishes 2 things, viz. Ensuring the new state
 *         is programmed as well as reading the old programmed value.
 *
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  CACHE_L1_Freeze
 *   @li                    CACHE_L1_FREEZE  - Old Freeze State of L1 Cache
 *   @li                    CACHE_L1P_FREEZE - Old Freeze State of L1P Cache  
 *   @li                    CACHE_L1D_FREEZE - Old Freeze State of L1D Cache
 *   @li                    CACHE_L1_NORMAL  - Normal State of L1 Cache
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Unfreeze L1 cache
 *
 *   @b Modifies
 *   @n L1DCC and L1PCC registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_unfreezeL1();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_unfreezeL1, ".text:csl_section:cache");
CACHE_L1_Freeze CACHE_unfreezeL1 (void)
{
    Uint32      oldL1DFrz;
    Uint32      oldL1PFrz;
      
    /* Critical Section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DCC = \
                          CSL_FMK(CACHE_L1DCC_OPER, CSL_CACHE_L1DCC_OPER_NORM);
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PCC = \
                          CSL_FMK(CACHE_L1PCC_OPER, CSL_CACHE_L1PCC_OPER_NORM);
    oldL1DFrz = CSL_FEXT(((CSL_CacheRegsOvly) \
                                  CSL_CACHE_0_REGS)->L1DCC, CACHE_L1DCC_POPER);
    oldL1PFrz = CSL_FEXT(((CSL_CacheRegsOvly) \
                                  CSL_CACHE_0_REGS)->L1PCC, CACHE_L1PCC_POPER);
    
    /* End Critical section */
    asm(" rint");
    
    /* return cache state if a single freeze is returned then the other
     * cache is in normal mode
     */
    if (oldL1DFrz == CSL_CACHE_L1DCC_OPER_FREEZE) {
        if (oldL1PFrz == CSL_CACHE_L1PCC_OPER_FREEZE)
            return CACHE_L1_FREEZE;
        else
            return CACHE_L1D_FREEZE;    
    } 
    else {
        if (oldL1PFrz == CSL_CACHE_L1PCC_OPER_FREEZE)
            return CACHE_L1P_FREEZE;
        else
            return CACHE_L1_NORMAL;
    }
}

/** ============================================================================
 *   @n@b CACHE_setL1pSize
 *
 *   @b Description
 *   @n Sets the L1P size.
 *   @n As per the specification,
 *   @n a. The new size is programmed in L1PCFG.
 *   @n b. L1PCFG is read back to ensure it is set.
 *
 *   @b Arguments
 *   @verbatim
              newSize      New size to be programmed
     @endverbatim     
 *
 *   <b> Return Value </b>  CACHE_L1Size
 *   @li                    Old size of L1 Cache
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Set L1P cache size
 *
 *   @b Modifies
 *   @n L1PCFG register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1Size oldSize ;

        oldSize = CACHE_setL1pSize(CACHE_L1_32KCACHE);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_setL1pSize, ".text:csl_section:cache");
CACHE_L1Size CACHE_setL1pSize (
    CACHE_L1Size    newSize
)
{
    Uint32      curSize;
     
    curSize = ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PCFG;
    
    /* Critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PCFG = newSize;
    newSize = (CACHE_L1Size)((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PCFG;
    
    /* End Critical section */
    asm(" rint");
        
    return (CACHE_L1Size) (curSize);
}

/** ============================================================================
 *   @n@b CACHE_freezeL1p
 *
 *   @b Description
 *   @n Freezes L1P.
 *   @n As per the specification,
 *   @n a. The new freeze state is programmed in L1PCC.
 *   @n b. The old state is read from the L1PCC from the POPER field.
 *   @n    This latter read accomplishes 2 things, viz. Ensuring the new state
 *         is programmed as well as reading the old programmed value.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  CACHE_L1_Freeze
 *   @li                    CACHE_L1P_FREEZE  - Old Freeze State of L1P Cache
 *   @li                    CACHE_L1P_NORMAL  - Normal State of L1P Cache 
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Freeze L1P cache
 *
 *   @b Modifies
 *   @n L1PCC register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_freezeL1p();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_freezeL1p, ".text:csl_section:cache");
CACHE_L1_Freeze CACHE_freezeL1p (void)
{
    Uint32      oldL1PFrz;
     
    /* Critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PCC =  \
                        CSL_FMK(CACHE_L1PCC_OPER, CSL_CACHE_L1PCC_OPER_FREEZE);
    oldL1PFrz = 
        CSL_FEXT(((CSL_CacheRegsOvly) \
                                  CSL_CACHE_0_REGS)->L1PCC, CACHE_L1PCC_POPER);
    /* End Critical Section */
    asm(" rint");
    
    if(oldL1PFrz == CSL_CACHE_L1PCC_OPER_FREEZE)
        return CACHE_L1P_FREEZE;
    else
        return CACHE_L1P_NORMAL;
}

/** ============================================================================
 *   @n@b CACHE_unfreezeL1p
 *
 *   @b Description
 *   @n Unfreezes L1P.
 *   @n As per the specification,
 *   @n a. The normal state is programmed in L1PCC
 *   @n b. The old state is read from the L1PCC from the POPER field.
 *   @n    This latter read accomplishes 2 things, viz. Ensuring the new state
 *         is programmed as well as reading the old programmed value.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  CACHE_L1_Freeze
 *   @li                    CACHE_L1P_FREEZE  - Old Freeze State of L1P Cache
 *   @li                    CACHE_L1P_NORMAL  - Normal State of L1P Cache 
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Unreeze L1P cache
 *
 *   @b Modifies
 *   @n L1PCC register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_unfreezeL1p();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_unfreezeL1p, ".text:csl_section:cache");
CACHE_L1_Freeze CACHE_unfreezeL1p (void)
{
    Uint32      temp;
     
    /* Critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PCC = 
                          CSL_FMK(CACHE_L1PCC_OPER, CSL_CACHE_L1PCC_OPER_NORM);
    temp = CSL_FEXT(((CSL_CacheRegsOvly) \
                                  CSL_CACHE_0_REGS)->L1PCC, CACHE_L1PCC_POPER);
    
    /* End Critical Section */
    asm(" rint");
        
    if(temp == CSL_CACHE_L1PCC_OPER_NORM)
        return CACHE_L1P_NORMAL;
    else
        return CACHE_L1P_FREEZE;
}

/** ============================================================================
 *   @n@b CACHE_invL1p
 *
 *   @b Description
 *   @n Invalidates range specified in L1P.
 *   @n As per the specification,
 *   @n a. The start of the range that needs to be invalidated is written
 *         into L1PIBAR
 *   @n b. The byte count is programmed in L1PIWC.
 *
 *   @b Arguments
 *   @verbatim
            blockPtr      Start address of range to be invalidated

            byteCnt       Number of bytes to be invalidated

            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed.
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
 *   @n  Invalidate L1P cache
 *
 *   @b Modifies
 *   @n L1PIBAR and L1PIWC registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_invL1p ((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_invL1p, ".text:csl_section:cache");
void CACHE_invL1p (
    void            *blockPtr,
    Uint32          byteCnt,
    CACHE_Wait      wait
)
{
     
    CACHE_waitInternal();
    
    /* treat BAR/WC as crit section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PIBAR = (Uint32)blockPtr;
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PIWC = ((byteCnt+3)>>2);
    _CSL_cachebusyState = CACHE_WAIT_L1PINV; 
    
    /* End Critical section */
    asm(" rint");
        
    if (wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_invAllL1p
 *
 *   @b Description
 *   @n Invalidates all of L1P.
 *   @n As per the specification,
 *   @n a. The L1PINV is programmed.
 *
 *   @b Arguments
 *   @verbatim
            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed.
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
 *   @n  Invalidate all L1P cache
 *
 *   @b Modifies
 *   @n L1PINV register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_invAllL1p (CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_invAllL1p, ".text:csl_section:cache");
void CACHE_invAllL1p (
    CACHE_Wait      wait
)
{
    CACHE_waitInternal();
     
    /* Critical Section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PINV = 1;
    _CSL_cachebusyState = CACHE_WAIT_L1PINVALL;
    
    /* End Critical Section */
    asm(" rint");
        
    if (wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_setL1dSize
 *
 *   @b Description
 *   @n Sets the L1D size.
 *   @n As per the specification,
 *   @n a. The new size is programmed in L1DCFG
 *   @n b. L1DCFG is read back to ensure it is set.
 *
 *   @b Arguments
 *   @verbatim
              newSize      New size to be programmed
     @endverbatim
 *
 *   <b> Return Value </b>  CACHE_L1Size
 *   @li                    Old Size set for L1D 
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n Set L1D cache size
 *
 *   @b Modifies
 *   @n L1DCFG register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1Size oldSize ;

        oldSize = CACHE_setL1dSize(CACHE_L1_32KCACHE);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_setL1dSize, ".text:csl_section:cache");
CACHE_L1Size CACHE_setL1dSize (
    CACHE_L1Size    newSize
)
{
    Uint32      curSize;
     
    curSize = ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DCFG;
    
    /* Critical Section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DCFG = newSize;
    newSize = (CACHE_L1Size)((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DCFG;
    
    /* End critical section */
    asm(" rint");
    
    return (CACHE_L1Size) (curSize);
}

/** ============================================================================
 *   @n@b CACHE_freezeL1d
 *
 *   @b Description
 *   @n Freezes L1D.
 *   @n As per the specification,
 *   @n a. The new freeze state is programmed in L1DCC.
 *   @n b. The old state is read from the L1DCC from the POPER field.
 *   @n    This latter read accomplishes 2 things, viz. Ensuring the new state
 *         is programmed as well as reading the old programmed value.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  CACHE_L1_Freeze
 *   @li                    CACHE_L1D_FREEZE  - Old Freeze State of L1D Cache
 *   @li                    CACHE_L1D_NORMAL  - Normal State of L1D Cache 
 *
 *   <b> Pre Condition </b>
 *   @n  The CACHE must be succesfully enabled via CACHE_enableCaching() before 
 *       calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  Freeze L1D cache
 *
 *   @b Modifies
 *   @n L1DCC register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_freezeL1d();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_freezeL1d, ".text:csl_section:cache");
CACHE_L1_Freeze CACHE_freezeL1d (void)
{

    Uint32 temp;
     
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DCC = 
                        CSL_FMK(CACHE_L1DCC_OPER, CSL_CACHE_L1DCC_OPER_FREEZE);
    temp = CSL_FEXT(((CSL_CacheRegsOvly) \
                                  CSL_CACHE_0_REGS)->L1DCC, CACHE_L1DCC_POPER);
    
    /* End critical section */
    asm(" rint");
        
    if(temp == CSL_CACHE_L1DCC_OPER_FREEZE)
        return CACHE_L1D_FREEZE;
    else
        return CACHE_L1D_NORMAL;
}

/** ============================================================================
 *   @n@b CACHE_unfreezeL1d
 *
 *   @b Description
 *   @n Unfreezes L1D.
 *   @n As per the specification,
 *   @n a. The normal state is programmed in L1DCC
 *   @n b. The old state is read from the L1DCC from the POPER field.
 *   @n    This latter read accomplishes 2 things, viz. Ensuring the new state
 *         is programmed as well as reading the old programmed value.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b>  CACHE_L1_Freeze
 *   @li                    CACHE_L1D_FREEZE  - Old Freeze State of L1D Cache
 *   @li                    CACHE_L1D_NORMAL  - Normal State of L1D Cache 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Unfreeze L1D cache
 *
 *   @b Modifies
 *   @n L1DCC register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_L1_Freeze oldFreezeState ;

        oldFreezeState = CACHE_unfreezeL1d();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_unfreezeL1d, ".text:csl_section:cache");
CACHE_L1_Freeze CACHE_unfreezeL1d (void)
{
    Uint32      temp;
    
     
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DCC = 
                        CSL_FMK(CACHE_L1DCC_OPER, CSL_CACHE_L1DCC_OPER_NORM);
    temp = CSL_FEXT(((CSL_CacheRegsOvly) \
                                CSL_CACHE_0_REGS)->L1DCC, CACHE_L1DCC_POPER);
    
    /* End critical section */
    asm(" rint");
    
    if(temp == CSL_CACHE_L1DCC_OPER_NORM)
        return CACHE_L1D_NORMAL;
    else
        return CACHE_L1D_FREEZE;
}

/** ============================================================================
 *   @n@b CACHE_wbL1d
 *
 *   @b Description
 *   @n Writes back range specified in L1D.
 *   @n As per the specification,
 *   @n a. The start of the range that needs to be written back is programmed
 *         into L1DWBAR.
 *   @n b. The byte count is programmed in L1DWWC.
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
 *   @n  Writeback L1D cache
 *
 *   @b Modifies
 *   @n L1DWWC and L1DWBAR registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbL1d((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbL1d, ".text:csl_section:cache");
void CACHE_wbL1d (
    void            *blockPtr,
    Uint32          byteCnt,
    CACHE_Wait      wait
)
{
    CACHE_waitInternal();
    
    /* Critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWBAR = (Uint32)blockPtr;
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWWC =((byteCnt+3)>>2);
    _CSL_cachebusyState = CACHE_WAIT_L1DWB;
    _CSL_cacheEmifState = (CACHE_emifState) \
                        (CSL_CACHE_EMIF_ISRANGE((Uint32)blockPtr) 
                             + CSL_CACHE_EMIF_ISEMIFBRANGE((Uint32)blockPtr));
    
    /* End critical section  */
    asm(" rint");
    
    if (wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_invL1d
 *
 *   @b Description
 *   @n Invalidates range specified in L1D.
 *   @n As per the specification,
 *   @n a. The start of the range that needs to be invalidated is written
 *         into L1DIBAR.
 *   @n b. The byte count is programmed in L1DIWC.
 *
 *   @b Arguments
 *   @verbatim
            blockPtr      Start address of range to be invalidated

            byteCnt       Number of bytes to be invalidated

            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed.
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
 *   @n  Invalidate the L1D cache
 *
 *   @b Modifies
 *   @n L1DIWC and L1DIBAR registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_invL1d ((Uint32*)(0x1000), 200, CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_invL1d, ".text:csl_section:cache");
void CACHE_invL1d (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
)
{
     
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DIBAR = (Uint32)blockPtr;
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DIWC = ((byteCnt+3)>>2);
    _CSL_cachebusyState = CACHE_WAIT_L1DINV;
    
    /* End critical section */
    asm(" rint");
    
    if (wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_wbInvL1d
 *
 *   @b Description
 *   @n Writeback invalidates range specified in L1D.
 *   @n As per the specification,
 *   @n a. The start of the range that needs to be writeback invalidated is
 *         programmed into L1DWIBAR.
 *   @n b. The byte count is programmed in L1DWIWC.
 *
 *   @b Arguments
 *   @verbatim
            blockPtr      Start address of range to be written back invalidated

            byteCnt       Number of bytes to be written back invalidated

            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed.
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
 *   @n  Witebacvk and invalidate the L1D cache
 *
 *   @b Modifies
 *   @n L1DWIWC and L1DWIBAR registers
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbInvL1d ((Uint32*)(0x1000),200,CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbInvL1d, ".text:csl_section:cache");
void CACHE_wbInvL1d (
    void         *blockPtr,
    Uint32       byteCnt,
    CACHE_Wait   wait
)
{
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWIBAR = (Uint32)blockPtr;
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWIWC = ((byteCnt+3)>>2);
    _CSL_cachebusyState = CACHE_WAIT_L1DWBINV;
    _CSL_cacheEmifState = (CACHE_emifState) \
                        (CSL_CACHE_EMIF_ISRANGE((Uint32)blockPtr) \
                            + CSL_CACHE_EMIF_ISEMIFBRANGE((Uint32)blockPtr));
                            
    /* End critical section */
    asm(" rint");
        
    if (wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_wbAllL1d
 *
 *   @b Description
 *   @n Writeback All of L1D.
 *   @n As per the specification,
 *   @n a. The L1DWB is programmed.
 *
 *   @b Arguments
 *   @verbatim
            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed.
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
 *   @n  Writeback all the L1D cache
 *
 *   @b Modifies
 *   @n L1DWB register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbAllL1d (CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbAllL1d, ".text:csl_section:cache");
void CACHE_wbAllL1d (
    CACHE_Wait     wait
)
{
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWB = 1;
    _CSL_cachebusyState = CACHE_WAIT_L1DWBALL;  
    _CSL_cacheEmifState = CACHE_EMIF_AB;
    
    /*  End critical section */
    asm(" rint");
    
    if (wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_invAllL1d
 *
 *   @b Description
 *   @n Invalidates All of L1D.
 *   @n As per the specification,
 *   @n a. The L1DINV is programmed.
 *
 *   @b Arguments
 *   @verbatim
            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed.
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
 *   @n  Invalidate the all L1D cache
 *
 *   @b Modifies
 *   @n L1DINV register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_invAllL1d (CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_invAllL1d, ".text:csl_section:cache");
void CACHE_invAllL1d (
    CACHE_Wait    wait
)
{
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint"); 
      
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DINV = 1;
    _CSL_cachebusyState = CACHE_WAIT_L1DINVALL;
    
    /* End critical section */
    asm(" rint");
    
    if (wait)
        _CACHE_wait(wait);
}

/** ============================================================================
 *   @n@b CACHE_wbInvAllL1d
 *
 *   @b Description
 *   @n Writeback invalidates All of L1D.
 *   @n As per the specification,
 *   @n a. The L1DWBINV is programmed.
 *
 *   @b Arguments
 *   @verbatim
            wait          Whether the call is blocking (and the extent of wait)
                          till the issued operation is completed.
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
 *   @n  Writeback and invalidate all L1D cache
 *
 *   @b Modifies
 *   @n L1DWBINV register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wbInvAllL1d (CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wbInvAllL1d, ".text:csl_section:cache");
void CACHE_wbInvAllL1d (
    CACHE_Wait      wait
)
{
     
    CACHE_waitInternal();
    
    /* critical section */
    asm(" dint");
    
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWBINV = 1;
    _CSL_cachebusyState = CACHE_WAIT_L1DWBINVALL;
    _CSL_cacheEmifState = CACHE_EMIF_AB;
    
    /* End of critical section */
    asm(" rint");
    
    if (wait)
        _CACHE_wait(wait);
}
