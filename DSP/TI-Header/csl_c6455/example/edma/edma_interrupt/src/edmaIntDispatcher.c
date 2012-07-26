/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *
 *   @file  edmaIntDispatcher.c
 *
 *   @path  $(CSLPATH)\example\edma\edma_interrupt\src
 *
 *   @desc This is utility function used by edma as Interrupt dispather 
 *
 * ============================================================================
 */

#include <csl_edma3.h>
#include <edmaCommon.h>

/* Global Edma Tcc handler table */
#pragma DATA_SECTION(TccHandlerTable,".testMem");
EdmaTccHandler TccHandlerTable[64];

/*
 * =============================================================================
 *   @func  eventEdmaHandler
 *  
 *   @arg
 *      handle        - Edma module handle
 *
 *   @desc
 *      This is the interrupt handler routine for edma interrupt
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void eventEdmaHandler (
    void        *handle
)
{
    CSL_Edma3Handle     hModule = (CSL_Edma3Handle)handle;
    CSL_BitMask32       maskVal;
    CSL_Edma3CmdIntr    regionIntr;
    Uint32              tcc;
    Uint32              intr;
    Uint32              intrh;
    
    /* Read the IPR */
    regionIntr.region = CSL_EDMA3_REGION_1;
    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND, &regionIntr);
    
    while (regionIntr.intr || regionIntr.intrh) {
        intr    = regionIntr.intr;
        intrh = regionIntr.intrh;
        tcc   = 0;
        
        while (intr) {
            maskVal = 1 << tcc;
            if (intr & maskVal) {
                InvokeHandle(tcc);
                intr &= ~maskVal;
            }
            tcc++;      
        }       
        
        tcc = 0;
        while (intrh) {
            maskVal = 1 << tcc;
            if (intrh & maskVal) {
                InvokeHandle((tcc+32));
                intrh &= ~maskVal;
            }       
            tcc++;
        }
        
        CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR,&regionIntr);       
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);         
    }           
}

/*
 * =============================================================================
 *   @func  EdmaEventHook
 *  
 *   @arg
 *      tcc        - Tcc number
 *      fxn        - Pointer to function which points to edma isr
 *
 *   @desc
 *      This is the interrupt handler routine for edma interrupt
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
void EdmaEventHook (
    Uint16            tcc, 
    EdmaTccHandler    fxn
)
{
    TccHandlerTable[tcc] = (fxn);
}

/*
 * =============================================================================
 *   @func  Verify_Transfer
 *  
 *
 *   @desc
 *      This is utility function used by the edma example to verify the 
 *      Data transfer. 
 *
 *   @return
 *      NONE
 *
 * =============================================================================
 */
Bool Verify_Transfer (
    Uint16      aCnt, 
    Uint16      bCnt, 
    Uint16      cCnt, 
    Uint16      srcBIdx, 
    Uint16      dstBIdx, 
    Uint16      srcCIdx, 
    Uint16      dstCIdx,
    Uint8      *srcBuff,
    Uint8      *dstBuff, 
    Bool        abSync
)
{
    Uint32      loopIndex1;
    Uint32      loopIndex2;
    Uint32      loopIndex3;
    Uint8       *srcArrayPtr = srcBuff;
    Uint8       *dstArrayPtr = dstBuff;
    Uint8       *srcFramePtr = srcBuff;
    Uint8       *dstFramePtr = dstBuff;
    
    
    for (loopIndex1 = 0; loopIndex1 < cCnt; loopIndex1++) {
        for (loopIndex2 = 0; loopIndex2 < bCnt; loopIndex2++) {
            for (loopIndex3 = 0; loopIndex3 < aCnt; loopIndex3++)
                if (srcArrayPtr[loopIndex3] != dstArrayPtr[loopIndex3]) 
                    return FALSE;
            srcArrayPtr = srcArrayPtr + srcBIdx;
            dstArrayPtr = dstArrayPtr + dstBIdx;
        }
        
        if (abSync) {
            srcFramePtr = srcFramePtr + srcCIdx;
            srcArrayPtr = srcFramePtr;
            dstFramePtr = dstFramePtr + dstCIdx;
            dstArrayPtr = dstFramePtr;
        }
        else {   
            srcFramePtr = srcArrayPtr + srcCIdx - srcBIdx;
            srcArrayPtr = srcFramePtr;
            dstFramePtr = dstArrayPtr + dstCIdx - dstBIdx;
            dstArrayPtr = dstFramePtr;      
        }       
    }
    
    return TRUE;
}
