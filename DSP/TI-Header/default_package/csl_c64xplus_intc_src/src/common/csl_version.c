/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

#include <tistdtypes.h>
#include <csl_version.h>


#pragma DATA_SECTION(CSL_versionStr, ".const:csl_section:version");

const
char  CSL_versionStr[ ] =
    CSL_VERSION_STR ":" CSL_CHIP_STR  ":" __DATE__  ":" __TIME__;



#pragma CODE_SECTION(CSL_versionGetID, ".text:csl_section:version");

Uint32
    CSL_versionGetID (
        void
)
{
    return CSL_VERSION_ID;
}


#pragma CODE_SECTION(CSL_versionGetStr, ".text:csl_section:version");

const char *
    CSL_versionGetStr (
        void
)
{
    return (const char *)CSL_versionStr;
}

