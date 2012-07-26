/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *   @file  csl_cacheWait.c
 *
 *   @path  $(CSLPATH)\src\cache
 *
 *   @desc  File for functional layer of Cache Waite State
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 * - 23-Mar-2004 Jamon Bowen File Created
 *
 *  21-Jun-2004 Ruchika Kharwar modified.
 *
 * ============================================================================= 
 */
 
#include <csl_cache.h>
#include <_csl_cache.h>

/** ============================================================================
 *   @n@b CACHE_wait
 *
 *   @b Description
 *   @n Waits for previously issued block operations to complete. This does a
 *      partial wait. i.e waits for the cache status register to read back as
 *      done. (if required)
 *
 *   @b  Arguments
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
 *   @n None
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_wait();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_wait, ".text:csl_section:cache");
void CACHE_wait (void)
{

    CACHE_waitInternal();
    _CSL_cacheApplyPatch();
    
    return;
}

/** ============================================================================
 *   @n@b CACHE_waitInternal
 *
 *   @b Description
 *   @n Waits for previously issued block operations to complete. This does a
 *      partial wait. i.e waits for the cache status register to read back as
 *      done. (if required)
 *
 *   @b Arguments
 *   @n None
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
 *   @n None
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_waitInternal();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (CACHE_waitInternal, ".text:csl_section:cache");
void CACHE_waitInternal(void)
{
    switch(_CSL_cachebusyState) {
        case CACHE_WAIT_NONE:
            break;
        
        case CACHE_WAIT_L1DINVALL:
            while (CSL_FEXT(((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DINV, \
                            CACHE_L1DINV_CMDANDSTAT) == \
                            CSL_CACHE_L1DINV_CMDANDSTAT_NOTDONE);
            break;
        
        case CACHE_WAIT_L1DINV:
            while (((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DIWC != 0);
            break;
        
        case CACHE_WAIT_L1DWBALL:
            while (CSL_FEXT(((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWB, \
                            CACHE_L1DWB_CMDANDSTAT) == \
                            CSL_CACHE_L1DWB_CMDANDSTAT_NOTDONE);
            break;
        
        case CACHE_WAIT_L1DWB:
            while (((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWWC != 0);
            break;
        
        case CACHE_WAIT_L1DWBINVALL:
            while (CSL_FEXT(((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWBINV, \
                            CACHE_L1DINV_CMDANDSTAT) == \
                            CSL_CACHE_L1DINV_CMDANDSTAT_NOTDONE);
            break;
        
        case CACHE_WAIT_L1DWBINV:
            while (((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1DWIWC != 0);
            break;
        
        case CACHE_WAIT_L1PINVALL:
            while (CSL_FEXT(((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PINV, \
                            CACHE_L1PINV_CMDANDSTAT) == \
                            CSL_CACHE_L1PINV_CMDANDSTAT_NOTDONE);
            break;
    
        case CACHE_WAIT_L1PINV:
            while (((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L1PIWC != 0);
            break;
    
        case CACHE_WAIT_L2INVALL:
            while (CSL_FEXT(((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2INV, \
                            CACHE_L2INV_CMDANDSTAT) == \
                            CSL_CACHE_L2INV_CMDANDSTAT_NOTDONE);
            break;
    
        case CACHE_WAIT_L2INV:
            while (((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2IWC != 0);
            break;
    
        case CACHE_WAIT_L2WBALL:
            while (CSL_FEXT(((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WB, \
                            CACHE_L2WB_CMDANDSTAT) == \
                            CSL_CACHE_L2WB_CMDANDSTAT_NOTDONE);
            break;
    
        case CACHE_WAIT_L2WB:
            while (((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WWC != 0);
            break;
    
        case CACHE_WAIT_L2WBINVALL:
            while (CSL_FEXT(((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WBINV, \
                            CACHE_L2WBINV_CMDANDSTAT) == \
                            CSL_CACHE_L2WBINV_CMDANDSTAT_NOTDONE);
            break;
    
        case CACHE_WAIT_L2WBINV:
            while (((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->L2WIWC != 0);
            break;
    
        default:
            break;
    }
    
    _CSL_cachebusyState = CACHE_WAIT_NONE;
}
