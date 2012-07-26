/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found
 *   in the license agreement under which this software has been supplied.
 *   ==========================================================================
 */

/** @file  csl_edma.c
 *
 *  @path $(CSLPATH)\src\edma
 *
 *  @brief File for functional layer of CSL API 
 *
 */

/*****************************************************************************\
* FILENAME...... csl_edma.c
* DATE CREATED.. 06/11/1999
* LAST MODIFIED. 16-SEP-2005 Changes according to the review comments
* LAST MODIFIED. 04-AUG-2005 Beautified and added a EDMA instance structure
*                25/05/2005 Modified to support the spec EDMA 3.0.2 and to use
*                           the CSL 3.x internally
*                08/13/2004 Modified tccAllocTable type from static to global. 
*                06/17/2003 Added support for 6712C
*                05/28/2003 Added support for 6711C
*                12/05/2000

\*****************************************************************************/
#define _EDMA_MOD_
#include <csl_edma2.h>

extern far Uint32 _lmbd (Uint32 src1, Uint32 src2
);

/*****************************************************************************\
*                         L O C A L   S E C T I O N
\*****************************************************************************/


/*****************************************************************************\
* static macro declarations
\*****************************************************************************/
#define _EDMA_OPT_PRI_MASK       0xE0000000
#define _EDMA_OPT_PRI_SHIFT      29

#define _EDMA_OPT_ESIZE_MASK     0x18000000
#define _EDMA_OPT_ESIZE_SHIFT    27

#define _EDMA_OPT_2DS_MASK       0x04000000
#define _EDMA_OPT_2DS_SHIFT      26

#define _EDMA_OPT_SUM_MASK       0x03000000
#define _EDMA_OPT_SUM_SHIFT      24

#define _EDMA_OPT_2DD_MASK       0x00800000
#define _EDMA_OPT_2DD_SHIFT      23

#define _EDMA_OPT_DUM_MASK       0x00600000
#define _EDMA_OPT_DUM_SHIFT      21

#define _EDMA_OPT_TCINT_MASK     0x00100000
#define _EDMA_OPT_TCINT_SHIFT    20

#define _EDMA_OPT_TCC_MASK       0x000F0000
#define _EDMA_OPT_TCC_SHIFT      16

#define _EDMA_OPT_TCCM_MASK      0x00006000
#define _EDMA_OPT_TCCM_SHIFT     13

#define _EDMA_OPT_ATCINT_MASK    0x00001000
#define _EDMA_OPT_ATCINT_SHIFT   12

#define _EDMA_OPT_ATCC_MASK      0x000007E0
#define _EDMA_OPT_ATCC_SHIFT     5

#define _EDMA_OPT_PDTS_MASK      0x00000008
#define _EDMA_OPT_PDTS_SHIFT     3

#define _EDMA_OPT_PDTD_MASK      0x00000004
#define _EDMA_OPT_PDTD_SHIFT     2

#define _EDMA_OPT_LINK_MASK      0x00000002
#define _EDMA_OPT_LINK_SHIFT     1

#define _EDMA_OPT_FS_MASK        0x00000001
#define _EDMA_OPT_FS_SHIFT       0


#define _EDMA_RLD_LINK_MASK      0x0000FFFF
#define _EDMA_RLD_LINK_SHIFT     0

#define _EDMA_RLD_ELERLD_MASK    0xFFFF0000
#define _EDMA_RLD_ELERD_SHIFT    16

#define _EDMA_CNT_FRMCNT_MASK    0xFFFF0000
#define _EDMA_CNT_FRMCNT_SHIFT   16

#define _EDMA_CNT_ELECNT_MASK    0x0000FFFF
#define _EDMA_CNT_ELECNT_SHIFT   0

#define _EDMA_IDX_FRMIDX_MASK    0xFFFF0000
#define _EDMA_IDX_FRMIDX_SHIFT   16

#define _EDMA_IDX_ELEIDX_MASK    0x0000FFFF
#define _EDMA_IDX_ELEIDX_SHIFT   0

/*****************************************************************************\
* static typedef declarations
\*****************************************************************************/


/*****************************************************************************\
* static function declarations
\*****************************************************************************/


/*****************************************************************************\
* static variable definitions
\*****************************************************************************/
static Uint32 allocMaskCL = 0x00000000;
static Uint32 allocMaskCH = 0x00000000;

static Uint32 allocMaskT[(Uint32) ((EDMA_TABLE_CNT -
            1) / (sizeof (Uint32) * 8)) + 1] = { 0, 0, 0, 0, 0, 0 };


/*****************************************************************************\
* static function definitions
\*****************************************************************************/

/*****************************************************************************\
*                        G L O B A L   S E C T I O N
\*****************************************************************************/


/*****************************************************************************\
* global variable definitions
\*****************************************************************************/
Uint8 tccAllocTable[EDMA_CHA_CNT] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* Objects needed to maintain the 3x data */
EDMA_Wrapper_Data EDMA_Wrapper_Data_Objs[EDMA_CHA_CNT];

/* A global structure to maintain the EDMA object instance */
CSL_Edma3Obj edmaObj = {
    (CSL_Edma3ccRegsOvly)CSL_EDMA3CC_0_REGS,
    CSL_EDMA3
};

/*****************************************************************************\
* global function definitions
\*****************************************************************************/
/** 
 * ============================================================================
 *   @n@b EDMA_reset
 *
 *   @b Description
 *   @n Resets the given DMA channel.
 *
 *   @b Arguments
 *   @verbatim
       hEdma      Handle to the channel to be reset

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  Channel must have been opened, previously.
 *
 *   <b> Post Condition </b>
 *   @li 1. The corresponding PaRAM entry is cleared to 0.
 *   @li 2. The channel is disabled and event register bit is cleared.
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle handle;
     Uint32 chan_no = 1;
     handle = EDMA_open(chan_no, EDMA_OPEN_RESET);
      ...
     EDMA_reset(handle);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_reset (
    EDMA_Handle    hEdma
)
{
    Uint32 gie;
    CSL_Edma3ParamSetup config = { 0 };
    gie = _disable_interrupts ();

    if (hEdma != EDMA_HINV) {
        if (_EDMA_CHANNEL_NUMBER (hEdma) < EDMA_CHA_CNT) {
            /* Clear event enable bit  */
            CSL_edma3HwChannelControl (_EDMA_CHANNEL_HANDLE_2X_TO_3X (hEdma),
                CSL_EDMA3_CMD_CHANNEL_DISABLE, NULL);

            /* Clear event bit  */
            CSL_edma3HwChannelControl (_EDMA_CHANNEL_HANDLE_2X_TO_3X (hEdma),
                CSL_EDMA3_CMD_CHANNEL_CLEAR, NULL);
            CSL_edma3ParamSetup (
                _EDMA_CHANNEL_HANDLE_2X_TO_3X_PARAM_HANDLE (hEdma),
                &config);
        }
    }
    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_resetAll
 *
 *   @b Description
 *   @n Resets all EDMA channels.
 *
 *   @b Arguments </b>
 *   @n  None
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @li 1. The PaRAM words corresponding to all of the DMA channels is are
 *          cleared to 0.
 *   @li 2. All channels are disabled and their interrupts reset.
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *   @b Example
 *   @verbatim
      ...
     EDMA_resetAll();
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_resetAll (
    void
)
{

    Uint32 gie;
    Uint32 index;

    gie = _disable_interrupts ();

    /* start by disabling and clearing EDMA channels */
    /* Clear Event enable */
    _EDMA_MODULE_HANDLE->EECR = 0xFFFFFFFF;
    _EDMA_MODULE_HANDLE->EECRH = 0xFFFFFFFF;

    /* Clear Event */
    _EDMA_MODULE_HANDLE->ECR = 0xFFFFFFFF;
    _EDMA_MODULE_HANDLE->ECRH = 0xFFFFFFFF;

    /* Clear interrupt enable bits */
    _EDMA_MODULE_HANDLE->IECR = 0xFFFFFFFF;
    _EDMA_MODULE_HANDLE->IECRH = 0xFFFFFFFF;

    /* Clear pending interrupts */
    _EDMA_MODULE_HANDLE->ICR = 0xFFFFFFFF;
    _EDMA_MODULE_HANDLE->ICRH = 0xFFFFFFFF;

    EDMA_clearPram (0x00000000);
    for (index = 0; index < (sizeof (allocMaskT) / sizeof (Uint32)); ++index) {
        allocMaskT[index] = 0;
    }
    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_open
 *
 *   @b Description
 *   @n Opens a DMA channel for use by the application.
 *
 *   @b Arguments </b>
 *   @verbatim
     1. Channel number or EDMA_CHA_ANY (to open any channel)
     2. Flags - EDMA_OPEN_RESET or EDMA_OPEN_ENABLE or 0
        EDMA_OPEN_RESET  - resets the channel
        EDMA_OPEN_ENABLE - enables the transfers


     @endverbatim
 *   <b> Return Value </b>
 *   @li  A valid handle on success
 *   @li  EDMA_HINV on failure
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @li 1. The channel is enabled or reset (PaRAM entry is cleared, channel
 *          disabled and interrupts cleared) depending on the flags passed. 
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *   @b Example
 *   @verbatim
     Uint32 chan_no = 4;
     EDMA_handle handle;
      ...
     handle = EDMA_open(chan_no, 0);
      ...
     @endverbatim
 * ============================================================================
 */
EDMA_Handle EDMA_open (
    int       channel,
    Uint32    flags
)
{
    Uint32 gie;
    EDMA_Handle hEdma = EDMA_HINV;
    Uint32 cha;
    Int32 t_cha = -1;
    CSL_Status status;

    CSL_Edma3ChannelAttr chParam;
    CSL_Status edmaStatus;

    gie = _disable_interrupts ();

    if (channel == EDMA_CHA_ANY) {
        for (cha = 0; cha < EDMA_CHA_CNT; cha++) {
            if (cha < 32) {  /* There are 64 channels; One register can hold
                                bits corresponding to 32 channels */
                if (!(allocMaskCL & (1 << cha))) {
                    t_cha = cha;
                    break;
                }
            }
            else {
                if (!(allocMaskCH & (1 << (cha - 32)))) {
                    t_cha = cha;
                    break;
                }
            }
        }
    }
    else {
        if (channel < 32) {  /* There are 64 channels; One register can hold
                                bits corresponding to 32 channels */
            if (!(allocMaskCL & (1 << channel))) {
                t_cha = channel;
            }
        }
        else if (t_cha < 64) {
            if (!(allocMaskCH & (1 << (channel - 32)))) {
                t_cha = channel;
            }
        }
    }

    if (t_cha == -1) {
        return hEdma;
    }

    /*
     * Channel is opened which is allocated to Global Region 1
     * instance of the EDMA
     */
    chParam.regionNum = CSL_EDMA3_REGION_GLOBAL;
    chParam.chaNum = t_cha;
    EDMA_Wrapper_Data_Objs[t_cha].hChannel =
        CSL_edma3ChannelOpen (&EDMA_Wrapper_Data_Objs[t_cha].ChObj, CSL_EDMA3,
        &chParam, &edmaStatus);

    if (edmaStatus != CSL_ESYS_FAIL) {
        EDMA_Wrapper_Data_Objs[t_cha].param =
            CSL_edma3GetParamHandle (EDMA_Wrapper_Data_Objs[t_cha].hChannel,
            t_cha, &status);
        if (status != CSL_SOK) {
            edmaStatus =
                CSL_edma3ChannelClose (EDMA_Wrapper_Data_Objs[t_cha].hChannel);
            return hEdma;
        }
    }
    else {
        return hEdma;
    }

    if (t_cha < 32) {  /* There are 64 channels; One register can hold
                          bits corresponding to 32 channels */
        allocMaskCL |= (1 << t_cha);
    }
    else if (t_cha < 64) {
        allocMaskCH |= (1 << (t_cha - 32));
    }

    hEdma =
        _EDMA_MK_HANDLE ((Uint32) EDMA_Wrapper_Data_Objs[t_cha].param, t_cha,
        _EDMA_TYPE_C);

    _restore_interrupts (gie);

    if (flags & EDMA_OPEN_RESET) {
        EDMA_reset (hEdma);
    }

    if (flags & EDMA_OPEN_ENABLE) {
        EDMA_enableChannel (hEdma);
    }
    return hEdma;
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_close
 *
 *   @b Description
 *   @n Closes a previously opened DMA channel, after its use
 *      by the application.
 *
 *   @b Arguments
 *   @verbatim
       hEdma      Handle to the channel to be closed

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li None
 *
 *   <b> Pre Condition </b>
 *   @n  The channel to be closed must have been opened previously.
 *
 *   <b> Post Condition </b>
 *   @li 1. The channel is closed and reset.
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle handle;
     Uint32 chan_no = 1;
     handle = EDMA_open(chan_no, EDMA_OPEN_RESET);
      ...
     EDMA_close(handle);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_close (
    EDMA_Handle    hEdma
)
{

    Uint32 cha = _EDMA_CHANNEL_NUMBER (hEdma);
    Uint32 gie;
    gie = _disable_interrupts ();
    if (cha < 32) {  /* There are 64 channels; One register can hold
                        bits corresponding to 32 channels */
        allocMaskCL &= ~(1 << cha);
    }
    else if (cha < 64) {
        allocMaskCH &= ~(1 << (cha - 32));
    }
    EDMA_reset (hEdma);
    _restore_interrupts (gie);
    CSL_edma3ChannelClose (_EDMA_CHANNEL_HANDLE_2X_TO_3X (hEdma));
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_allocTable
 *
 *   @b Description
 *   @n Allocates a PaRAM table entry for use by the application.
 *
 *   @b Arguments
 *   @verbatim
       tableNum         - PaRAM table entry number (0 to EDMA_TABLE_CNT)
        or
       EDMA_ALLOC_ANY   - to allocate any available entry of PaRAM table
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li  A valid handle on success
 *   @li  EDMA_HINV on failure
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @li A PaRAM table entry is allocated from the free pool.
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle handle;
     Uint32 tabNum = 1;
      ...
     handle = EDMA_allocTable(tabNum);
      ...
     @endverbatim
 * ============================================================================
 */
EDMA_Handle EDMA_allocTable (
    int    tableNum
)
{

    Uint32 addr;
    EDMA_Handle hEdma = EDMA_HINV;
    Uint32 tbl, major, minor;
    Uint32 gie;

    gie = _disable_interrupts ();

    if (tableNum == EDMA_ALLOC_ANY) {
        for (tbl = 0; tbl < EDMA_TABLE_CNT; tbl++) {
            major = ((tbl) & (~0x1F)) >> 5;
            minor = (tbl) & (0x1F);
            if (!(allocMaskT[major] & (1 << minor))) {
                allocMaskT[major] |= (1 << minor);
                addr = (tbl * _EDMA_ENTRY_SIZE) + _EDMA_LINK_START;
                hEdma =
                    _EDMA_MK_HANDLE (addr,
                    tbl + (_EDMA_LINK_START / _EDMA_ENTRY_SIZE), _EDMA_TYPE_T);
                break;
            }
        }
        if (tbl >= EDMA_TABLE_CNT) {
            hEdma = EDMA_HINV;
        }
    }
    else {
        if ((tableNum < EDMA_TABLE_CNT)) {
            major = ((tableNum) & (~0x1F)) >> 5;
            minor = (tableNum) & (0x1F);
            if (!(allocMaskT[major] & (1 << minor))) {
                allocMaskT[major] |= (1 << minor);
                addr = (tableNum * _EDMA_ENTRY_SIZE) + _EDMA_LINK_START;
                hEdma =
                    _EDMA_MK_HANDLE (addr,
                    tableNum + (_EDMA_LINK_START / _EDMA_ENTRY_SIZE),
                    _EDMA_TYPE_T);
            }
            else {
                hEdma = EDMA_HINV;
            }
        }
    }

    _restore_interrupts (gie);

    return hEdma;
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_freeTable
 *
 *   @b Description
 *   @n Frees a previously allocated PaRAM table entry.
 *
 *   @b Arguments
 *   @verbatim
       hEdma      Handle to the PaRAM entry to be freed

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The channel to be closed must have been allocated previously.
 *
 *   <b> Post Condition </b>
 *   @li One more entry in the free PaRAM table.
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle handle;
     Uint32 tabNum = 1;
      ...
     handle = EDMA_allocTable(tabNum);
      ...
     EDMA_freeTable(handle);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_freeTable (
    EDMA_Handle    hEdma
)
{

    Uint32 tbl, major, minor, tmp;
    Uint32 gie;

    gie = _disable_interrupts ();
    if (hEdma & _EDMA_TYPE_T) {
        tbl = _EDMA_CHANNEL_NUMBER (hEdma);
        tmp = (_EDMA_LINK_START / _EDMA_ENTRY_SIZE) & 0x000000FF;
        tbl -= tmp;
        major = ((tbl) & (~0x1F)) >> 5;
        minor = (tbl) & (0x1F);
        allocMaskT[major] &= ~(1 << minor);
    }
    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_allocTableEx
 *
 *   @b Description
 *   @n Allocates a number of PaRAM table entries from the free pool.
 *
 *   @b Arguments
 *   @verbatim
       cnt        number of channels to be allocaed
       array      pointer to the first element of array of EDMA_handles
                  to return handles for the allocated entries

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li  The number of allocated entries, if success
 *   @li  0, if failure
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @li 1. The number of entries in free PaRAM table are less by 'cnt'
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle hArray[4];
     Uint32 cnt = 4, retCnt;
     retCnt = EDMA_allocTableEx(cnt, &hArray[0]);
      ...

     @endverbatim
 * ============================================================================
 */
Uint32 EDMA_allocTableEx (
    int    cnt,
    EDMA_Handle    * array
)
{

    Uint32 index, numAllocated = 0;
    EDMA_Handle hEdma;
    Uint32 gie;

    gie = _disable_interrupts ();
    for (index = 0; index < cnt; index++) {
        hEdma = EDMA_allocTable (EDMA_ALLOC_ANY);
        if (hEdma != EDMA_HINV) {
            numAllocated++;
            array[index] = hEdma;
        }
        else {
            EDMA_freeTableEx (numAllocated, array);
            numAllocated = 0;
        }
    }
    _restore_interrupts (gie);
    return numAllocated;
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_freeTableEx
 *
 *   @b Description
 *   @n Frees previously allocated PaRAM table entries.
 *
 *   @b Arguments
 *   @verbatim
       cnt        number of channels to be freed
       array      pointer to the first element of array of EDMA_handles
                  that are to be freed

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  Freed entries must have been allocated previously
 *
 *   <b> Post Condition </b>
 *   @li 1. The number of entries in free PaRAM table are more by 'cnt' 
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle hArray[4];
     Uint32 cnt = 4, retCnt;
     retCnt = EDMA_allocTableEx(cnt, &hArray[0]);
      ...
     EDMA_freeTableEx(cnt, &hArray[0]);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_freeTableEx (
    int            cnt,
    EDMA_Handle    * array
)
{

    Uint32 index;
    Uint32 gie;

    gie = _disable_interrupts ();
    for (index = 0; index < cnt; index++) {
        EDMA_freeTable (array[index]);
        array[index] = EDMA_HINV;
    }
    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_clearPram
 *
 *   @b Description
 *   @n The PaRAM words corresponding to all of the DMA channels  are set to
 *      ‘val’.
 *
 *   @b Arguments
 *   @verbatim
       val      Value to be written into the PaRAM words

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @li All words of the PaRAM corresponding to the DMA
 *       channels, are set to the given value, 'val'.  Reserved fields of PaRAM
 *       do not reflect the written bit values.  They are read as 0.
 *
 *   @b Modifies
 *      None.
 *
 *
 *   @b Example
 *   @verbatim
     Uint32 val = 0;
      ...
     EDMA_clearPram(val);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_clearPram (
    Uint32    val
)
{
    Uint32 gie;

    Uint32 index;
    CSL_Edma3ParamSetup config;
    config.option = val;
    config.srcAddr = val;
    config.aCntbCnt = val;
    config.dstAddr = val;
    config.srcDstBidx = val;
    config.linkBcntrld = val;
    config.srcDstCidx = val;
    config.cCnt = val;

    gie = _disable_interrupts ();

    for (index = 0; index < EDMA_CHA_CNT; index++) {
        CSL_edma3ParamSetup ((CSL_Edma3ParamHandle) (&(_EDMA_MODULE_HANDLE->
                    PARAMSET[index])), &config);
    }

    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_intAlloc
 *
 *   @b Description
 *   @n Allocates a DMA channel interrupt.  This interrupt is used in channel
 *      configuration to configure the interrupt to be generated after a
 *      transfer.
 *
 *   @b Arguments
 *   @verbatim
       tcc      interrupt number
       or
       -1       to allocate any avaliable interrupt

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @li interrupt number allocated, if success
 *   @li -1, to indicate failure
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @li One interrupt less in the free pool of interrupts.
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     Uint32 tcc = 1, retTcc;
      ...
     retTcc = EDMA_intAlloc(tcc);
      ...

     @endverbatim
 * ============================================================================
 */
int EDMA_intAlloc (
    int    tcc
)
{
    Uint32 gie;
    Int32 tccReturn = -1;

    gie = _disable_interrupts ();
    if (tcc == -1) {
        for (tcc = 0; tcc < EDMA_CHA_CNT; tcc++) {
            if (tccAllocTable[tcc] == 0) {
                tccAllocTable[tcc] = 1;
                tccReturn = tcc;
                break;
            }
        }
    }
    else {
        if ((tcc < EDMA_CHA_CNT) && (tccAllocTable[tcc] == 0)) {
            tccAllocTable[tcc] = 1;
            tccReturn = tcc;
        }
    }
    _restore_interrupts (gie);

    return tccReturn;
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_intFree
 *
 *   @b Description
 *   @n Frees a previously allocated interrupt.
 *
 *   @b Arguments
 *   @verbatim
       tcc      interrupt number to be freed

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  To be freed interrupt must have been allocated, previously.
 *
 *   <b> Post Condition </b>
 *   @li One interrupt more in the free pool.
 *
 *   @b Modifies
 *   @n The system data structures are modified.
 *
 *
 *   @b Example
 *   @verbatim
     Uint32 tcc = 1, retTcc;
      ...
     retTcc = EDMA_intAlloc(tcc);
      ...
     EDMA_intFree(retTcc);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_intFree (
    int tcc
)
{
    Uint32 gie;

    gie = _disable_interrupts ();
    tccAllocTable[tcc] = 0;
    _restore_interrupts (gie);
}

/** 
 * ============================================================================
 *   @n@b EDMA_config
 *
 *   @b Description
 *   @n Configures an EDMA transfer.
 *
 *   @verbatim
     1. Following transfers specified in the document 'spru234.pdf' are
        NOT possible.  When these are configured in the EDMA_Config structure,
        the routine returns without cofiguring the PaRAM.

        The NOT possible transfers are:
        A-44, A-47, A-48, A-49, A-50, A-62, A-65, A-66, A-67,
        A-68, A-80, A-83 A-84, A-85 and A-86.

        All these "NOT POSSIBLE" are possible saying that Acnt = elmSize,
        BCnt = elmCnt, Cnt =arCnt+1, appropriate indexes and these chain to
        themselves. But TCC = channel Number should be free and this
        programmation should not contrast with user programmation of Interrupt
        enables/chain enables/tcc programmation.

     2. For the following transfers specfied in the document 'spru234.pdf',
        the source address must be alligned to 256-bits, otherwise the config
        API returns without configuring.
        A-42, A-43, A-60, A-61 and A-78

     3. For the following transfers specified in the document 'spru234.pdf',
        the destination address must be alligned to 256-bits, otherwise the
        config API returns without configuring.
        A-42, A-45, A-60, A-63, A-66, A78 and A-81
     @endverbatim

 *   @b Arguments
 *   @verbatim
       hEdma      Handle to the channel or PaRAM to be configured
       conf       Address of the cofiguration structure
     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @verbatim
     1. Channel must have been opened or a PaRAM entry allocated, previously.
     2. A TCC must have been allocated, if TCINT bit is set.
     @endverbatim

 *   <b> Post Condition </b>
 *   @li The corresponding PaRAM entry is cofigured, if the configuration is
 *       valid
 *
 *   @b Modifies
 *   @n The PaRAM is modified if the configuration is valid.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle handle;
     Uint32 chan_no = 1, tcc;
     EDMA_Config conf;
     char dst[512];
     char src[512];
     handle = EDMA_open(chan_no, EDMA_OPEN_RESET);
     tcc = EDMA_intAlloc(4);
      ...
     conf.opt = 0x51340001;
     conf.cnt = 0x00000200;  // Transfer 512 bytes
     conf.idx = 0;
     conf.rld = 0x0000FFFF;
     conf.dst = (Uint32)&dst[0];
     conf.src = (Uint32)&src[0];

     EDMA_config(handle, &conf);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_config (
    EDMA_Handle    hEdma,
    EDMA_Config    * config
)
{
    Uint32 gie;
    Uint32 esize, elmCnt, sync, DS2_DD2, sum, dum, srcBidx, srcCidx;
    Uint32 dstBidx, dstCidx, frmCnt, frmIdx, eleIdx, fifo_width;
    Uint32 tmp, chan_no;
    volatile Uint32 *base;

    /* OPT fields */
    Uint32 itcchEn = 0, tcchEn = 0, itcintEn = 0, tcintEn = 0, tcc =
        0, tccMode = 0;
    Uint32 fwid = 0, stat = 0, syncDim = 0, dam = 0, sam = 0;

    /* ACNT, BCNT, CCNT */
    Uint32 aCnt = 0, bCnt = 0, cCnt = 0;

    /* BCNTRLD, LINK */
    Uint32 link = 0, bCntRld = 0;
    CSL_Edma3ParamSetup config3 = { 0 };
    Uint32 invalid_options = 0, src_addr_align_256_bits =
        0, dst_addr_align_256_bits = 0;

    /*  If QDMA configuration, then handle is 0x20000000 or 0x10000000 */
    if (hEdma == (0x20000000) || hEdma == (0x10000000)) {
        EDMA_qdmaConfig (config);
        return;
    }
    gie = _disable_interrupts ();

    /* if LINK bit is set then setup the link address */
    if (config->opt & _EDMA_OPT_LINK_MASK) {
        link = config->rld & _EDMA_RLD_LINK_MASK;
    }
    else {
        link = 0xFFFF;          /* No linking */
    }


    config3.option = 0;

    /* TCC = TCC */
    tcc =
        (((config->opt & _EDMA_OPT_TCC_MASK) >> _EDMA_OPT_TCC_SHIFT) |
         ((config->opt & _EDMA_OPT_TCCM_MASK) >> (_EDMA_OPT_TCCM_SHIFT - 4)));

    /*
     * Set ATCINTEN, ATCCEN ONLY if the user's TCC == ATCC, else never set it
     * Assuming ATCINTEN is ITCINTEN and ATCCEN is ITCCHEN
     */

    if ((((config->opt & _EDMA_OPT_TCC_MASK) >> _EDMA_OPT_TCC_SHIFT) |
         ((config->opt & _EDMA_OPT_TCCM_MASK) >> (_EDMA_OPT_TCCM_SHIFT - 4)))
         ==
        ((config->opt & _EDMA_OPT_ATCC_MASK) >> _EDMA_OPT_ATCC_SHIFT)) {
        if ((config->opt & _EDMA_OPT_ATCINT_MASK) != 0) {
            itcintEn = 1;
        }
    }

    /* Base address of the PaRAM entry */
    base = (volatile Uint32 *) ((hEdma & 0x0000FFFF) + _EDMA_BASE_PRAM);

    if (base[0] & CSL_EDMA3CC_OPT_TCCHEN_MASK) {
        /*
         * Do not disturb this bit if it was set in EDMA_enableChaining
         */
        tcchEn = 1;
    }

    /* Set TCCHEN, TCINTEN as per older param entries */
    if (config->opt & CSL_EDMA3CC_OPT_TCINTEN_MASK) {
                                             /* if TCINT of old param is set */
        tcintEn = 1;
    }

    /* Set Normal Completion - Nothing to do 0 is already set */

    /* Check source address for 256 bit alignment */
    if ((config->src % 32) == 0) {
        src_addr_align_256_bits = 1;
    }

    /* Check destination address for 256 bit alignment */
    if ((config->dst % 32) == 0) {
        dst_addr_align_256_bits = 1;
    }

    /*Set up A-count */
    tmp = (config->opt & _EDMA_OPT_ESIZE_MASK) >> _EDMA_OPT_ESIZE_SHIFT;

    if (tmp == 0) {             /* 4 bytes */
        fifo_width = 2;         /* 32 bits */
        esize = 4;
    }
    else if (tmp == 1) {        /* 2 bytes */
        esize = 2;
        fifo_width = 1;         /* 16 bits */
    }
    else {
        esize = 1;
        fifo_width = 0;         /* 8 bits */
    }


    /* Set up B-count */
    elmCnt = config->cnt & _EDMA_CNT_ELECNT_MASK;

    frmCnt = (config->cnt & _EDMA_CNT_FRMCNT_MASK) >> _EDMA_CNT_FRMCNT_SHIFT;
    frmIdx = (config->idx & _EDMA_IDX_FRMIDX_MASK) >> _EDMA_IDX_FRMIDX_SHIFT;
    eleIdx = (config->idx & _EDMA_IDX_ELEIDX_MASK);
    sync = config->opt & _EDMA_OPT_FS_MASK;

    DS2_DD2 =
        ((config->opt & _EDMA_OPT_2DS_MASK) >> (_EDMA_OPT_2DS_SHIFT -
            1)) | ((config->opt & _EDMA_OPT_2DD_MASK) >> _EDMA_OPT_2DD_SHIFT);
    sum = (config->opt & _EDMA_OPT_SUM_MASK) >> _EDMA_OPT_SUM_SHIFT;
    dum = (config->opt & _EDMA_OPT_DUM_MASK) >> _EDMA_OPT_DUM_SHIFT;

    if ((sync == 0) || (DS2_DD2 == 0)) {
        /* A count and B count */
        aCnt = esize;
        bCnt = elmCnt;
        /* C count */
        cCnt = frmCnt + 1;
    }
    else {
        /* A count and B count */
        aCnt = (esize * elmCnt);
        bCnt = frmCnt + 1;
        /* C count */
        cCnt = 1;
    }

    if ((DS2_DD2) == 0 && (sync == 0)) {
        /* A sync */
        bCntRld = elmCnt;
    }
    else {
        syncDim = 1;            /* AB sync */
    }

    fwid = fifo_width;
    srcBidx = 0;                /* Source B Index */
    srcCidx = 0;                /* Source C Index */
    srcBidx = 0;                /* Source B Index */
    srcCidx = 0;                /* Source C Index */

    if (sync == 0) {
        switch (DS2_DD2) {
            case 0:                /* 1 dimentional to 1 dimentional */
                if (sum == 0) {     /* Fixed source address */
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 1) {     /* Increment source address */
                    srcBidx = esize;        /* Source B Index */
                    srcCidx = esize;        /* Source C Index */
                }
                if (sum == 2) {     /* Decrement source address */
                    srcBidx = -esize;       /* Source B Index */
                    srcCidx = -esize;       /* Source C Index */
                }
                if (sum == 3) {     /* First bytes of elements are
                                       sperated by eleidx */
                    srcBidx = eleIdx;       /* Source B Index */
                    srcCidx = frmIdx;       /* Source C Index */
                }
                if (dum == 0) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 1) {
                    dstBidx = esize;        /* Destination B Index */
                    dstCidx = esize;        /* Destination C Index */
                }
                if (dum == 2) {
                    dstBidx = -esize;       /* Destination B Index */
                    dstCidx = -esize;       /* Destination C Index */
                }
                if (dum == 3) {
                    dstBidx = eleIdx;       /* Destination B Index */
                    dstCidx = frmIdx;       /* Destination C Index */
                }
                break;

            case 1:                /* 1 dimentional to 2 dimentional */
                if (sum == 0) {
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 1) {     /* AB sync mode */
                    srcBidx = esize;        /* Source B Index */
                    srcCidx = esize * elmCnt;       /* Source C Index */
                }
                if (sum == 2) {
                    srcBidx = -esize;       /* Source B Index */
                    srcCidx = -esize * elmCnt;      /* Source C Index */
                }
                if (sum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                if (dum == 0) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 1) {
                    dstBidx = esize;        /* Destination B Index */
                    dstCidx = frmIdx;       /* Destination C Index */
                }
                if (dum == 2) {
                    dstBidx = -esize;       /* Destination B Index */
                    dstCidx = frmIdx;       /* Destination C Index */
                }
                if (dum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                break;
            case 2:
                if (sum == 0) {
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 1) {
                    srcBidx = esize;        /* Source B Index */
                    srcCidx = frmIdx;       /* Source C Index */
                }
                if (sum == 2) {
                    srcBidx = -esize;       /* Source B Index */
                    srcCidx = frmIdx;       /* Source C Index */
                }
                if (sum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                if (dum == 0) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 1) {     /* AB sync mode */
                    dstBidx = esize;        /* Destination B Index */
                    dstCidx = esize * elmCnt;       /* Destination C Index */
                }
                if (dum == 2) {
                    dstBidx = -esize;       /* Destination B Index */
                    dstCidx = -esize * elmCnt;      /* Destination C Index */
                }
                if (dum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                break;
            case 3:
                if (sum == 0) {
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 1) {
                    srcBidx = esize;        /* Source B Index */
                    srcCidx = frmIdx;       /* Source C Index */
                }
                if (sum == 2) {
                    srcBidx = -esize;       /* Source B Index */
                    srcCidx = frmIdx;       /* Source C Index */
                }
                if (sum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                if (dum == 0) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 1) {
                    dstBidx = esize;        /* Destination B Index */
                    dstCidx = frmIdx;       /* Destination C Index */
                }
                if (dum == 2) {
                    dstBidx = -esize;       /* Destination B Index */
                    dstCidx = frmIdx;       /* Destination C Index */
                }
                if (dum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                break;
        }
    }
    else {
        switch (DS2_DD2) {
            case 0:                /* 1 dimentional to 1 dimentional */
                if (sum == 0) {     /* Fixed source address */
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 1) {     /* Increment source address */
                    srcBidx = esize;        /* Source B Index */
                    srcCidx = esize * elmCnt;       /* Source C Index */
                }
                if (sum == 2) {     /* Decrement source address */
                    srcBidx = -esize;       /* Source B Index */
                    srcCidx = -esize * elmCnt;      /* Source C Index */
                }
                if (sum == 3) {
                    srcBidx = eleIdx;       /* Source B Index */
                    srcCidx = frmIdx;       /* Source C Index */
                }
                if (dum == 0) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 1) {
                    dstBidx = esize;        /* Destination B Index */
                    dstCidx = esize * elmCnt;       /* Destination C Index */
                }
                if (dum == 2) {
                    dstBidx = -esize;       /* Destination B Index */
                    dstCidx = -esize * elmCnt;      /* Destination C Index */
                }
                if (dum == 3) {
                    dstBidx = eleIdx;       /* Destination B Index */
                    dstCidx = frmIdx;       /* Destination C Index */
                }
                break;

            case 1:                /* 1 dimentional to 2 dimentional */
                if (sum == 0) {
                    if (src_addr_align_256_bits == 1) {
                        srcBidx = 0;        /* Source B Index */
                        srcCidx = 0;        /* Source C Index */
                        sam = 1;
                    }
                    else {
                        invalid_options = 1;
                    }
                }
                if (sum == 1) {     /* AB sync mode */
                    srcBidx = esize * elmCnt;       /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 2) {
                    invalid_options = 1;
                }
                if (sum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }

                if (dum == 0) {
                    if (dst_addr_align_256_bits == 1) {
                        dstBidx = 0;        /* Destination B Index */
                        dstCidx = 0;        /* Destination C Index */
                        dam = 1;
                    }
                    else {
                        invalid_options = 1;
                    }
                }
                if (dum == 1) {
                                    /* Source B Index */
                    dstBidx = (esize * elmCnt) + frmIdx;
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 2) {
                    invalid_options = 1;
                }
                if (dum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                break;
            case 2:
                if (sum == 0) {
                    if (src_addr_align_256_bits == 1) {
                        srcBidx = 0;        /* Source B Index */
                        srcCidx = 0;        /* Source C Index */
                        sam = 1;
                    }
                    else {
                        invalid_options = 1;
                    }
                }
                if (sum == 1) {
                                    /* Source B Index */
                    srcBidx = (esize * elmCnt) + frmIdx;
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 2) {
                    invalid_options = 1;
                }
                if (sum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }

                if (dum == 0) {
                    if (dst_addr_align_256_bits == 1) {
                        dstBidx = 0;        /* Destination B Index */
                        dstCidx = 0;        /* Destination C Index */
                        dam = 1;
                    }
                    else {
                        invalid_options = 1;
                    }
                }
                if (dum == 1) {     /* AB sync mode */
                    dstBidx = esize * elmCnt;       /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 2) {
                    invalid_options = 1;
                }
                if (dum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                break;

            case 3:                /* 2 dimentional to 2 dimentional */
                if (sum == 0) {
                    if (src_addr_align_256_bits == 1) {
                        srcBidx = 0;        /* Source B Index */
                        srcCidx = 0;        /* Source C Index */
                        sam = 1;
                    }
                    else {
                        invalid_options = 1;
                    }
                }
                if (sum == 1) {
                                    /* Source B Index */
                    srcBidx = (esize * elmCnt) + frmIdx;
                    srcCidx = 0;    /* Source C Index */
                }
                if (sum == 2) {
                    invalid_options = 1;
                }
                if (sum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                if (dum == 0) {
                    if (dst_addr_align_256_bits == 1) {
                        dstBidx = 0;        /* Destination B Index */
                        dstCidx = 0;        /* Destination C Index */
                        dam = 1;
                    }
                    else {
                        invalid_options = 1;
                    }
                }
                if (dum == 1) {
                                    /* Destination B Index */
                    dstBidx = (esize * elmCnt) + frmIdx;
                    dstCidx = 0;    /* Destination C Index */
                }
                if (dum == 2) {
                    invalid_options = 1;
                }
                if (dum == 3) {     /* Invalid Option */
                    invalid_options = 1;
                }
                break;
        }
    }

    /* Set up each word of the config3 structure */
    config3.option =
        CSL_EDMA3_OPT_MAKE (itcchEn, tcchEn, itcintEn, tcintEn, tcc, tccMode,
        fwid, stat, syncDim, dam, sam);
    config3.aCntbCnt = CSL_EDMA3_CNT_MAKE (aCnt, bCnt);
    config3.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (link, bCntRld);
    config3.srcDstBidx = CSL_EDMA3_BIDX_MAKE (srcBidx, dstBidx);
    config3.srcDstCidx = CSL_EDMA3_CIDX_MAKE (srcCidx, dstCidx);
    config3.cCnt = cCnt;
    config3.srcAddr = config->src;
    config3.dstAddr = config->dst;

    if (!invalid_options) {
     /* Do the following only if configuring a channel, not for a link PaRAM */
        chan_no = _EDMA_CHANNEL_NUMBER (hEdma);
        if (chan_no < EDMA_CHA_CNT) {
            tmp = (((config->opt) & _EDMA_OPT_PRI_MASK) >>
            _EDMA_OPT_PRI_SHIFT);
            /* Queue number */
            CSL_edma3HwChannelSetupQue (_EDMA_CHANNEL_HANDLE_2X_TO_3X (hEdma),
                (CSL_Edma3Que) tmp);
            CSL_edma3HwChannelSetupParam (
                _EDMA_CHANNEL_HANDLE_2X_TO_3X (hEdma),
                chan_no);
            /* chan_no has PaRAM  */
        }

        /* Write to the PaRAM */
        CSL_edma3ParamSetup ((CSL_Edma3ParamHandle) base, &config3);
    }
    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_configArgs
 *
 *   @b Description
 *   @n Configures an EDMA transfer.
 *
 *   @verbatim
     1. Following transfers specified in the document 'spru234.pdf' are
        NOT possible.  When these are configured in the EDMA_Config structure,
        the routine returns without cofiguring the PaRAM.

        The NOT possible transfers are:
        A-44, A-47, A-48, A-49, A-50, A-62, A-65, A-66, A-67,
        A-68, A-80, A-83 A-84, A-85 and A-86.

        All these "NOT POSSIBLE" are possible saying that Acnt = elmSize,
        BCnt = elmCnt, Cnt =arCnt+1, appropriate indexes and these chain to
        themselves. But TCC = channel Number should be free and this
        programmation should not contrast with user programmation of Interrupt
        enables/chain enables/tcc programmation.

     2. For the following transfers specfied in the document 'spru234.pdf',
        the source address must be alligned to 256-bits, otherwise the config
        API returns without configuring.
        A-42, A-43, A-60, A-61 and A-78

     3. For the following transfers specified in the document 'spru234.pdf',
        the destination address must be alligned to 256-bits, otherwise the
        config API returns without configuring.
        A-42, A-45, A-60, A-63, A-66, A78 and A-81
     @endverbatim

 *   @b Arguments
 *   @verbatim
       hEdma      Handle to the channel or PaRAM to be configured
       opt        Options word of the configuration
       src        From address used in the transfer
       cnt        Specify the number of arrays and number of elements
                  in each array
       dst        To address used in the transfer
       idx        Specify offsets used to calculate the addresses
       rld        Specify the link address and the reload value

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @verbatim
     1. Channel must have been opened or a PaRAM entry allocated, previously.
     2. A TCC must have been allocated, if TCINT bit is set.
     @endverbatim

 *
 *   <b> Post Condition </b>
 *   @li The corresponding PaRAM entry is cofigured, if the configuration is
 *       valid
 *
 *   @b Modifies
 *   @n The PaRAM is modified if the configuration is valid.
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle handle;
     Uint32 chan_no = 1, tcc;
     Uint32 opt, cnt, idx, rld, src, dst;
     char dst[512];
     char src[512];
     handle = EDMA_open(chan_no, EDMA_OPEN_RESET);
     tcc = EDMA_intAlloc(4);
      ...
     opt = 0x51340001;
     cnt = 0x00000200;  // Transfer 512 bytes
     idx = 0;
     rld = 0x0000FFFF;
     dst = (Uint32)&dst[0];
     src = (Uint32)&src[0];

     EDMA_configArgs(handle, opt, src, cnt, dst, idx, rld);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_configArgs (
    EDMA_Handle    hEdma,
    Uint32         opt,
    Uint32         src,
    Uint32         cnt,
    Uint32         dst,
    Uint32         idx,
    Uint32         rld
)
{
    EDMA_Config config;
    config.opt = opt;
    config.src = src;
    config.cnt = cnt;
    config.dst = dst;
    config.idx = idx;
    config.rld = rld;

    EDMA_config (hEdma, &config);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_getConfig
 *
 *   @b Description
 *   @n Returns the configuration of an EDMA transfer, with the following
 *          limitations.
 *   @verbatim
     Fields - 2DS, SUM, 2DD, DUM, PDTS, PDTD, FS, FRMIDX, ELEIDX and ELERLD 
              are not returned (not modified in the argument structure
              passed to the API).
     Fields - ATCINT, ATCC, LINK valid if the programed values are valid
     Other fields contain valid configuration.
     @endverbatim
 *   @b Arguments
 *   @verbatim
       handle       Handle of the channel
       config       Pointer to the configuration structure of type
                    'EDMA_Config'

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n   None
 *
 *   @b Modifies
 *   @n None
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_handle handle;
     Uint32 chan_no = 1;
     EDMA_Config conf;
     handle = EDMA_open(chan_no, EDMA_OPEN_RESET);
      ...
     EDMA_getConfig(handle, &conf);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_getConfig (
    EDMA_Handle    hEdma,
    EDMA_Config    * config
)
{
    Uint32 gie;
    Uint32 cCnt, link, abCnt, opt, src, dst, elmSize, tcc;
    CSL_Edma3Que pri;
    Uint32 *param_addr, chan_no;

    gie = _disable_interrupts ();

    /* Set PRI bits as per the Queue set up */
    chan_no = _EDMA_CHANNEL_NUMBER (hEdma);
    if (chan_no < EDMA_CHA_CNT) {
        CSL_edma3GetHwChannelSetupQue (_EDMA_CHANNEL_HANDLE_2X_TO_3X (hEdma),
            &pri);
        config->opt &= ~_EDMA_OPT_PRI_MASK;
        config->opt |= (pri << _EDMA_OPT_PRI_SHIFT);
    }

    param_addr = (Uint32 *) EDMA_getTableAddress (hEdma);

    opt = param_addr[0];
    src = param_addr[1];
    abCnt = param_addr[2];
    dst = param_addr[3];
    link = param_addr[5];
    cCnt = param_addr[7] & CSL_EDMA3CC_CCNT_CCNT_MASK;

    /* Try for counts */
    if (cCnt == 1) {
        /* We can find only FRMCNT only */
        config->cnt &= ~_EDMA_CNT_FRMCNT_MASK;
        config->cnt |=
            (((abCnt & CSL_EDMA3CC_A_B_CNT_BCNT_MASK) >>
                CSL_EDMA3CC_A_B_CNT_BCNT_SHIFT) - 1) << _EDMA_CNT_FRMCNT_SHIFT;

        /* Use FIFO width to find elmSize */
        config->opt &= ~_EDMA_OPT_ESIZE_MASK;
        if ((opt & CSL_EDMA3CC_OPT_FWID_MASK) == 0) {
            elmSize = 1;        /* 8 bits */
            config->opt |= 0x10000000;
        }
        else if ((opt & CSL_EDMA3CC_OPT_FWID_MASK) == (0x00000100)) {
            elmSize = 2;        /* 16 bits */
            config->opt |= 0x08000000;
        }
        else {
            elmSize = 4;        /* 32 bits */
        }
        config->cnt &= ~_EDMA_CNT_ELECNT_MASK;
        config->cnt |=
            ((abCnt & CSL_EDMA3CC_A_B_CNT_ACNT_MASK) /
            elmSize) & _EDMA_CNT_ELECNT_MASK;
    }
    else {
        config->cnt =
            ((cCnt -
                1) << _EDMA_CNT_FRMCNT_SHIFT) | (abCnt >>
            _EDMA_CNT_ELECNT_SHIFT);
        config->opt &= ~_EDMA_OPT_ESIZE_MASK;    /* ESIZE bits of the opt */
        elmSize = abCnt & CSL_EDMA3CC_A_B_CNT_ACNT_MASK;
        if (elmSize == 4) {
        }
        else if (elmSize == 2) {
            config->opt |= 0x08000000;
        }
        else {
            config->opt |= 0x10000000;
        }
    }

    if ((opt & _EDMA_OPT_TCINT_MASK) == _EDMA_OPT_TCINT_MASK) { /* TCINT bit */
        config->opt |= _EDMA_OPT_TCINT_MASK;
    }
    else {
        config->opt &= ~_EDMA_OPT_TCINT_MASK;
    }

    /* Set TCC */
    tcc = (opt & CSL_EDMA3CC_OPT_TCC_MASK);     /* Extract TCC */
    config->opt &= ~(_EDMA_OPT_TCC_MASK | _EDMA_OPT_TCCM_MASK);
    /* Clear TCC in the destination */

    config->opt |= (((tcc & 0xF000) << 4) | ((tcc & 0x00030000) >> 3));
    /* Rearange the source TCC into the format of destination */

    /* Set ATCCINT and ATCC if ITCINTEN is set */
    if ((opt & CSL_EDMA3CC_OPT_ITCINTEN_MASK) ==
        CSL_EDMA3CC_OPT_ITCINTEN_MASK) {
        config->opt |= _EDMA_OPT_ATCINT_MASK;
        config->opt &= ~_EDMA_OPT_ATCC_MASK;
        config->opt |= (tcc >> 7);
        /* Adjust the source TCC to destination ATCC */
    }
    else {
        config->opt &= ~_EDMA_OPT_ATCINT_MASK;
    }

    /* Set LINK bit and word */
    if ((link & 0xFFFF) != 0xFFFF) {
        config->opt |= _EDMA_OPT_LINK_MASK;
    }
    else {
        config->opt &= ~_EDMA_OPT_LINK_MASK;
    }
    config->rld &= ~_EDMA_RLD_LINK_MASK;
    config->rld |= (link & _EDMA_RLD_LINK_MASK);

    config->src = src;
    config->dst = dst;
    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_qdmaConfig
 *
 *   @b Description
 *   @n Configures a QDMA transfer, returns after initiating the transfer.
 *
 *   @verbatim
     1. Following transfers specified in the document 'spru234.pdf' are
        NOT possible.  When these are configured in the EDMA_Config structure,
        the routine returns without a data transfer.

        The NOT possible transfers are:
        A-44, A-47, A-48, A-49, A-50, A-62, A-65, A-66, A-67,
        A-68, A-80, A-83 A-84, A-85 and A-86.

     2. For the following transfers specfied in the document 'spru234.pdf',
        the source address must be alligned to 256-bits, otherwise the config
        API returns without a data transfer.
        A-42, A-43, A-60, A-61 and A-78

     3. For the following transfers specified in the document 'spru234.pdf',
        the destination address must be alligned to 256-bits, otherwise the
        config API returns without a data transfer.
        A-42, A-45, A-60, A-63, A-66, A78 and A-81

     4. No need to enable the QDMA channel seperately, this API takes care of
        enabling the QDMA channel.

     5. All transfers with QDMA are frame synchronized transfers.

     @endverbatim

 *   @b Arguments
 *   @verbatim
       hEdma      Handle to the channel or PaRAM to be configured

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @verbatim
     1. A TCC must have been allocated, if TCINT bit is set.
     @endverbatim
 *
 *   <b> Post Condition </b>
 *   @li The corresponding PaRAM entry is cofigured, if the configuration is
 *       valid
 *
 *   @b Modifies
 *   @n The PaRAM is modified if the configuration is valid.
 *
 *
 *   @b Example
 *   @verbatim

     EDMA_Config conf;
     Uint32 tcc;
     char dst[512];
     char src[512];
     handle = EDMA_open(chan_no, EDMA_OPEN_RESET);
     tcc = EDMA_intAlloc(4);
      ...
     conf.opt = 0x51340001;
     conf.cnt = 0x00000200;  // Transfer 512 bytes
     conf.idx = 0;
     conf.dst = (Uint32)&dst[0];
     conf.src = (Uint32)&src[0];

     EDMA_qdmaConfig(&conf);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_qdmaConfig (
    EDMA_Config    * config
)
{

    Uint32 tmp, esize, elmCnt, DS2_DD2, sum, dum, srcBidx, srcCidx;
    Uint32 dstBidx, dstCidx, frmCnt, frmIdx, eleIdx, fifo_width;
    volatile Uint32 *base;

    /* OPT fields */
    Uint32 itcchEn = 0, tcchEn = 0, itcintEn = 0, tcintEn = 0, tcc =
        0, tccMode = 0;
    Uint32 fwid = 0, stat = 0, syncDim = 0, dam = 0, sam = 0;

    /* ACNT, BCNT, CCNT */
    Uint32 aCnt = 0, bCnt = 0, cCnt = 0;

    /* BCNTRLD, LINK */
    Uint32 link = 0, bCntRld = 0;

    CSL_Edma3ParamSetup config3 = { 0 };
    Uint32 invalid_options = 0, src_addr_align_256_bits =
        0, dst_addr_align_256_bits = 0;
    Uint32 gie;

    /* Wait until previous transfer has been submitted */
    while (0 != (_EDMA_MODULE_HANDLE->QER & CSL_EDMA3CC_QER_E0_MASK)) {
        ;
    }
    gie = _disable_interrupts ();
    config3.option = 0;
    config3.linkBcntrld = 0;

    /* No LINKing */
    link = 0xFFFF;
    stat = 1;                   /* Setting the static Entry bit, no linking */

    /* TCC = TCC */
    tcc =
        (((config->opt & _EDMA_OPT_TCC_MASK) >> _EDMA_OPT_TCC_SHIFT) |
         ((config->opt & _EDMA_OPT_TCCM_MASK) >> (_EDMA_OPT_TCCM_SHIFT - 4)));

    if (config->opt & _EDMA_OPT_TCINT_MASK) {
        tcintEn = 1;
    }

    /* Check source address for 256 bit alignment */
    if ((config->src % 32) == 0) {
        src_addr_align_256_bits = 1;
    }

    /* Check destination address for 256 bit alignment */
    if ((config->dst % 32) == 0) {
        dst_addr_align_256_bits = 1;
    }


    /* Set up A-count */
    tmp = (config->opt & _EDMA_OPT_ESIZE_MASK) >> _EDMA_OPT_ESIZE_SHIFT;

    if (tmp == 0) {             /* 4 bytes */
        fifo_width = 2;         /* 32 bits */
        esize = 4;
    }
    else if (tmp == 1) {        /* 2 bytes */
        esize = 2;
        fifo_width = 1;         /* 16 bits */
    }
    else {
        esize = 1;
        fifo_width = 0;         /* 8 bits */
    }

    /* Set up B-count */
    elmCnt = config->cnt & _EDMA_CNT_ELECNT_MASK;
    frmCnt = (config->cnt & _EDMA_CNT_FRMCNT_MASK) >> _EDMA_CNT_FRMCNT_SHIFT;
    frmIdx = (config->idx & _EDMA_IDX_FRMIDX_MASK) >> _EDMA_IDX_FRMIDX_SHIFT;
    eleIdx = (config->idx & _EDMA_IDX_ELEIDX_MASK);

    /* Extract 2DS and 2DD */
    DS2_DD2 =
        ((config->opt & _EDMA_OPT_2DS_MASK) >> (_EDMA_OPT_2DS_SHIFT -
            1)) | ((config->opt & _EDMA_OPT_2DD_MASK) >> _EDMA_OPT_2DD_SHIFT);

    /* Extract SUM and DUM */
    sum = (config->opt & _EDMA_OPT_SUM_MASK) >> _EDMA_OPT_SUM_SHIFT;
    dum = (config->opt & _EDMA_OPT_DUM_MASK) >> _EDMA_OPT_DUM_SHIFT;

    if (DS2_DD2 == 0) {
        /* A count and B count */
        aCnt = esize;
        bCnt = elmCnt;
    }
    else {
        /* A count and B count */
        aCnt = esize * elmCnt;
        bCnt = frmCnt + 1;
    }

    /* C count */
    cCnt = 1;                   /* Only one array to be transfered with QDMA
                                   if DS2_DD2 = 0 */

    syncDim = 1;                /* AB sync */

    fwid = fifo_width;
    srcBidx = 0;                /* Source B Index */
    srcCidx = 0;                /* Source C Index */
    srcBidx = 0;                /* Source B Index */
    srcCidx = 0;                /* Source C Index */

    switch (DS2_DD2) {
        case 0:                    /* 1 dimentional to 1 dimentional */
            if (sum == 0) {         /* Fixed source address */
                srcBidx = 0;        /* Source B Index */
                srcCidx = 0;        /* Source C Index */
            }
            if (sum == 1) {         /* Increment source address */
                srcBidx = esize;    /* Source B Index */
                srcCidx = esize * elmCnt;   /* Source C Index */
            }
            if (sum == 2) {         /* Decrement source address */
                srcBidx = -esize;   /* Source B Index */
                srcCidx = -esize * elmCnt;  /* Source C Index */
            }
            if (sum == 3) {
                srcBidx = eleIdx;   /* Source B Index */
                srcCidx = frmIdx;   /* Source C Index */
            }
            if (dum == 0) {
                dstBidx = 0;        /* Destination B Index */
                dstCidx = 0;        /* Destination C Index */
            }
            if (dum == 1) {
                dstBidx = esize;    /* Destination B Index */
                dstCidx = esize * elmCnt;   /* Destination C Index */
            }
            if (dum == 2) {
                dstBidx = -esize;   /* Destination B Index */
                dstCidx = -esize * elmCnt;  /* Destination C Index */
            }
            if (dum == 3) {
                dstBidx = eleIdx;   /* Destination B Index */
                dstCidx = frmIdx;   /* Destination C Index */
            }
            break;

        case 1:                    /* 1 dimentional to 2 dimentional */
            if (sum == 0) {
                if (src_addr_align_256_bits == 1) {
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                    sam = 1;
                }
                else {
                    invalid_options = 1;
                }
            }
            if (sum == 1) {         /* AB sync mode */
                srcBidx = esize * elmCnt;   /* Source B Index */
                srcCidx = 0;        /* Source C Index */
            }
            if (sum == 2) {
                invalid_options = 1;
            }
            if (sum == 3) {         /* Invalid Option */
                invalid_options = 1;
            }

            if (dum == 0) {
                if (dst_addr_align_256_bits == 1) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                    dam = 1;
                }
                else {
                    invalid_options = 1;
                }
            }
            if (dum == 1) {
                                    /* Destination B Index */
                dstBidx = (esize * elmCnt) + frmIdx;
                dstCidx = 0;        /* Destination C Index */
            }
            if (dum == 2) {
                invalid_options = 1;
            }
            if (dum == 3) {         /* Invalid Option */
                invalid_options = 1;
            }
            break;
        case 2:
            if (sum == 0) {
                if (src_addr_align_256_bits == 1) {
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                    sam = 1;
                }
                else {
                    invalid_options = 1;
                }
            }
            if (sum == 1) {
                srcBidx = (esize * elmCnt) + frmIdx;     /* Source B Index */
                srcCidx = 0;        /* Source C Index */
            }
            if (sum == 2) {
                invalid_options = 1;
            }
            if (sum == 3) {         /* Invalid Option */
                invalid_options = 1;
            }

            if (dum == 0) {
                if (dst_addr_align_256_bits == 1) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                    dam = 1;
                }
                else {
                    invalid_options = 1;
                }
            }
            if (dum == 1) {         /* AB sync mode */
                dstBidx = esize * elmCnt;   /* Destination B Index */
                dstCidx = 0;        /* Destination C Index */
            }
            if (dum == 2) {
                invalid_options = 1;
            }
            if (dum == 3) {         /* Invalid Option */
                invalid_options = 1;
            }
            break;

        case 3:                    /* 2 dimentional to 2 dimentional */
            if (sum == 0) {
                if (src_addr_align_256_bits == 1) {
                    srcBidx = 0;    /* Source B Index */
                    srcCidx = 0;    /* Source C Index */
                    sam = 1;
                }
                else {
                    invalid_options = 1;
                }
            }
            if (sum == 1) {
                srcBidx = (esize * elmCnt) + frmIdx;      /* Source B Index */
                srcCidx = 0;        /* Source C Index */
            }
            if (sum == 2) {
                invalid_options = 1;
            }
            if (sum == 3) {         /* Invalid Option */
                invalid_options = 1;
            }
            if (dum == 0) {
                if (dst_addr_align_256_bits == 1) {
                    dstBidx = 0;    /* Destination B Index */
                    dstCidx = 0;    /* Destination C Index */
                    dam = 1;
                }
                else {
                    invalid_options = 1;
               }
            }
            if (dum == 1) {
                dstBidx = (esize * elmCnt) + frmIdx;  /* Destination B Index */
                dstCidx = 0;        /* Destination C Index */
            }
            if (dum == 2) {
                invalid_options = 1;
            }
            if (dum == 3) {         /* Invalid Option */
                invalid_options = 1;
            }
            break;
    }

    /* Setup each word of the Config3 structure */
    config3.option =
        CSL_EDMA3_OPT_MAKE (itcchEn, tcchEn, itcintEn, tcintEn, tcc, tccMode,
        fwid, stat, syncDim, dam, sam);
    config3.aCntbCnt = CSL_EDMA3_CNT_MAKE (aCnt, bCnt);
    config3.linkBcntrld = CSL_EDMA3_LINKBCNTRLD_MAKE (link, bCntRld);
    config3.srcDstBidx = CSL_EDMA3_BIDX_MAKE (srcBidx, dstBidx);
    config3.srcDstCidx = CSL_EDMA3_CIDX_MAKE (srcCidx, dstCidx);

    config3.srcAddr = config->src;
    config3.dstAddr = config->dst;
    config3.cCnt = cCnt;

    /* Get the base address of the PaRAM */
    base = (volatile Uint32 *) (_EDMA_QDMA_PARAM);
    if (!invalid_options) {
        _EDMA_MODULE_HANDLE->QDMAQNUM =
            (config->opt & _EDMA_OPT_PRI_MASK) >> _EDMA_OPT_PRI_SHIFT;
        /* Setup PRI field of input */
        _EDMA_MODULE_HANDLE->QCHMAP[0] =
            (((Uint32) (_EDMA_QDMA_PARAM) -
                (_EDMA_PRAM_START)) /
            (_EDMA_ENTRY_SIZE)) << CSL_EDMA3CC_QCHMAP_PAENTRY_SHIFT;
        _EDMA_MODULE_HANDLE->QEESR = CSL_EDMA3CC_QEESR_E0_SET;
        base[1] = config->src;
        base[2] = config3.aCntbCnt;
        base[3] = config->dst;
        base[4] = config3.srcDstBidx;
        base[5] = config3.linkBcntrld;
        base[6] = config3.srcDstCidx;
        base[7] = config3.cCnt;
        base[0] = config3.option;
    }

    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/
/** 
 * ============================================================================
 *   @n@b EDMA_qdmaConfigArgs
 *
 *   @b Description
 *   @n Configures a QDMA transfer, returns after initiating the transfer.
 *
 *   @verbatim
     1. Following transfers specified in the document 'spru234.pdf' are
        NOT possible.  When these are configured in the EDMA_Config structure,
        the routine returns without a data transfer.

        The NOT possible transfers are:
        A-44, A-47, A-48, A-49, A-50, A-62, A-65, A-66, A-67,
        A-68, A-80, A-83 A-84, A-85 and A-86.

     2. For the following transfers specfied in the document 'spru234.pdf',
        the source address must be alligned to 256-bits, otherwise the config
        API returns without a data transfer.
        A-42, A-43, A-60, A-61 and A-78

     3. For the following transfers specified in the document 'spru234.pdf',
        the destination address must be alligned to 256-bits, otherwise the
        config API returns without a data transfer.
        A-42, A-45, A-60, A-63, A-66, A78 and A-81

     4. No need to enable the QDMA channel seperately, this API takes care of
        enabling the QDMA channel.

     5. All transfers with QDMA are frame synchronized transfers.

     @endverbatim

 *   @b Arguments
 *   @verbatim
       opt        Options word of the configuration
       src        From address used in the transfer
       cnt        Specify the number of arrays and number of elements
                  in each array
       dst        To address used in the transfer
       idx        Specify offsets used to calculate the addresses

     @endverbatim
 *
 *   <b> Return Value </b>
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @verbatim
     1. A TCC must have been allocated, if TCINT bit is set.
     @endverbatim
 *
 *   <b> Post Condition </b>
 *   @li The corresponding PaRAM entry is cofigured, if the configuration is
 *       valid
 *
 *   @b Modifies
 *   @n The PaRAM is modified if the configuration is valid.
 *
 *
 *   @b Example
 *   @verbatim

     Uint32 opt, cnt, idx, src, dst, tcc;
     char dst[512];
     char src[512];

      ...
     tcc = EDMA_intAlloc(4);
     opt = 0x51340001;
     cnt = 0x00000200;  // Transfer 512 bytes
     idx = 0;
     rld = 0x0000FFFF;
     dst = (Uint32)&dst[0];
     src = (Uint32)&src[0];

     EDMA_qdmaConfigArgs(opt, src, cnt, dst, idx);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_qdmaConfigArgs (
    Uint32    opt,
    Uint32    src,
    Uint32    cnt,
    Uint32    dst,
    Uint32    idx
)
{

    EDMA_Config config;
    config.opt = opt;
    config.src = src;
    config.cnt = cnt;
    config.dst = dst;
    config.idx = idx;
    EDMA_qdmaConfig (&config);
}

/*---------------------------------------------------------------------------*/

/** 
 * ============================================================================
 *   @n@b EDMA_qdmaGetConfig
 *
 *   @b Description
 *   @n Returns the configuration of an QEDMA transfer, with the following
 *      limitations.
 *   @verbatim
     Fields - ESIZE, 2DS, SUM, 2DD, DUM, PDTS, PDTD, FRMCNT, ELECNT, 
              FRMIDX and ELEIDX are not returned (not modified in the
              argument structure passed to the API).
     Fields - FS returned as 1, reserved fields are DO NOT CARE.
              Other fields contain valid configuration.
     
     @endverbatim
 *   @b Arguments
 *   @verbatim
       config       A pointer to EDMA_Config structure to return the
                    configuration

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
 *   @n None
 *
 *
 *   @b Example
 *   @verbatim
     EDMA_Config conf;
     handle = EDMA_open(chan_no, EDMA_OPEN_RESET);
      ...
     EDMA_qdmaGetConfig(&conf);
      ...
     @endverbatim
 * ============================================================================
 */
void EDMA_qdmaGetConfig (
    EDMA_Config    * config
)
{

    Uint32 opt, src, dst, tcc;
    Uint32 *param_addr, gie;

    gie = _disable_interrupts ();
    param_addr = (Uint32 *) _EDMA_QDMA_PARAM;

    opt = param_addr[0];
    src = param_addr[1];
    dst = param_addr[3];

    /* PRI bits */
    config->opt |= (_EDMA_MODULE_HANDLE->QDMAQNUM) << _EDMA_OPT_PRI_SHIFT;

    if ((opt & _EDMA_OPT_TCINT_MASK) == _EDMA_OPT_TCINT_MASK) { /* TCINT bit */
        config->opt |= _EDMA_OPT_TCINT_MASK;
    }
    else {
        config->opt &= ~_EDMA_OPT_TCINT_MASK;
    }

    /*
     * It is not possible to return the ESIZE, FRMCNT and ELECNT
     * because cCnt is always 1 for QDMA.  The cCnt value is
     * the basis for finding CNT value of 2.x for EDMA.
     */
    /* Set TCC */
    tcc = (opt & CSL_EDMA3CC_OPT_TCC_MASK);     /* Extract TCC */
    config->opt &= ~(_EDMA_OPT_TCC_MASK | _EDMA_OPT_TCCM_MASK);
    /* Clear TCC in the destination */

    config->opt |= (((tcc & 0xF000) << 4) | ((tcc & 0x00030000) >> 3));
    /* Rearange the source TCC into the format of destination */

    /* No link bit in the Set LINK bit and word */
    config->opt &= ~_EDMA_OPT_LINK_MASK;

    /* FS is allways set */
    config->opt |= _EDMA_OPT_FS_MASK;

    config->src = src;
    config->dst = dst;
    _restore_interrupts (gie);
}

/*---------------------------------------------------------------------------*/

/*****************************************************************************\
* End of csl_edma.c
\*****************************************************************************/
