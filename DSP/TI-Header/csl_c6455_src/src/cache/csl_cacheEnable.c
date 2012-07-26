/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *  ============================================================================
 */

/** ============================================================================
 *   @file  csl_cacheEnable.c
 *
 *   @path  $(CSLPATH)\src\cache
 *
 *   @desc  File for functional layer of CSL API CACHE_enableCaching ()
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  23-Mar-2004 Jamon Bowen File Created
 *
 * ============================================================================= 
 */

#include <csl_cache.h>
#include <_csl_cache.h>

/** ============================================================================
 *   @n@b CACHE_enableCaching
 *
 *   @b Description
 *   @n Enables caching for the specified memory range.
 *
 *   @b Arguments
 *   @verbatim
            mar        EMIF range
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  Caching for the specified memory range is enabled
 *
 *   @b Modifies
 *   @n MAR register
 *
 *   @b Example
 *   @verbatim
        ...
        CACHE_enableCaching (CACHE_EMIFB_CE00);
        ...
     @endverbatim
 *  ============================================================================
 */

#pragma CODE_SECTION (CACHE_enableCaching, ".text:csl_section:cache");
void CACHE_enableCaching (
    CE_MAR          mar
)
{
    ((CSL_CacheRegsOvly)CSL_CACHE_0_REGS)->MAR[mar] = 1;
}
