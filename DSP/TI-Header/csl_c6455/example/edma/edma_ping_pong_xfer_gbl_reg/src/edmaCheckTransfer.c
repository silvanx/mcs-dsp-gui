/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004,2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *
 *   @file  edmaCheckTransfer.c
 *
 *   @path  $(CSLPATH)\example\edma\edma_ping_pong_xfer_gbl_reg\src
 *
 *   @desc  This is utility function used by the edma example to verify the 
 *          Data transfer. 
 * ============================================================================
 */

#include <csl_edma3.h>

/* Forward declaration */
Bool Verify_Transfer (Uint16 aCnt, Uint16 bCnt, Uint16 cCnt,Uint16 srcBIdx, 
                      Uint16 dstBIdx, Uint16 srcCIdx, Uint16 dstCIdx, 
                      Uint8  *srcBuff, Uint8 *dstBuff, Bool abSync); 
                      
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
    Uint8       *srcArrayPtr = (Uint8*)srcBuff;
    Uint8       *dstArrayPtr = (Uint8*)dstBuff;
    Uint8       *srcFramePtr = (Uint8*)srcBuff;
    Uint8       *dstFramePtr = (Uint8*)dstBuff;
    
    
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
