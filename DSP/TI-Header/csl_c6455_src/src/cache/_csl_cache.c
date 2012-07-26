/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */


/* ============================================================================
 *   @file  _csl_cache.c
 *
 *   @path  $(CSLPATH)\src\cache
 *
 *   @desc  File for functional layer of CSL API _CSL_cacheApplyPatch() and 
 *          _CACHE_wait ()
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  23-Mar-2004 Jamon Bowen File Created
 *
 *  21-Jun-2004 Ruchika Kharwar modified.
 *
 * ============================================================================= 
 */

#include <csl_cache.h>
#include <_csl_cache.h>

#pragma DATA_SECTION (_CSL_cachebusyState, ".bss:csl_section:cache");
volatile CACHE_waitState _CSL_cachebusyState = CACHE_WAIT_NONE;

#pragma DATA_SECTION (_CSL_cacheEmifState, ".bss:csl_section:cache");
volatile CACHE_emifState _CSL_cacheEmifState = CACHE_EMIF_NONE;

/* ============================================================================
 *   @n@b _CSL_cacheApplyPatch
 *
 *   @b Description
 *   @n This API used to set the cacheability of the specified EMIF range.
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
        _CSL_cacheApplyPatch ();
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (_CSL_cacheApplyPatch, ".text:csl_section:cache");
void _CSL_cacheApplyPatch(void)
{
    switch (_CSL_cacheEmifState) {
        case CACHE_EMIF_NONE: 
            break;

        case CACHE_EMIF_A: 
            CSL_CACHE_EMIFA_PATCH();
            break;

        case CACHE_EMIF_B: 
            CSL_CACHE_EMIFB_PATCH();
            break;

        case CACHE_EMIF_AB:   
            CSL_CACHE_EMIFA_PATCH();
            CSL_CACHE_EMIFB_PATCH();
            break;
    }
    _CSL_cacheEmifState = CACHE_EMIF_NONE;
}

/* ============================================================================
 *   @n@b _CACHE_wait
 *
 *   @b Description
 *   @n This API call the CACHE_waitInternal() and CACHE_wait() APIs.
 *
 *   @b  Arguments   
 *   @n  wait        - Specifies whether the cache operations should block
 *                     till the desired operation is complete
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
        _CACHE_wait(CACHE_NOWAIT);
        ...
     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (_CACHE_wait, ".text:csl_section:cache");
void _CACHE_wait (
    CACHE_Wait      wait
)
{
    if (wait == CACHE_WAITINTERNAL)
        CACHE_waitInternal();
    else
        CACHE_wait();
}

