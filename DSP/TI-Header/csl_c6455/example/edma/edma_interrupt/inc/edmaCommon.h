/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *
 *   @file  edmaCommon.h
 *
 *   @path  $(CSLPATH)\example\edma\edma_interrupt\inc
 *
 *   @desc  Header file for EDMA interrupt example
 *
 * =============================================================================
 */
 
#ifndef _EDMACOMMON_H_
#define _EDMACOMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Macro for tcc handler */
#define InvokeHandle(num)       TccHandlerTable[num]()
typedef void (*EdmaTccHandler)(void);

/* Funtion which registers individual event handlers in a table */
void EdmaEventHook(Uint16 ,EdmaTccHandler);

/* Forward declaration */
void eventEdmaHandler();
void eventGlobalEdmaHandler();
Bool Verify_Transfer(Uint16 aCnt, Uint16 bCnt, Uint16 cCnt, Uint16 srcBIdx, \
                    Uint16 dstBIdx, Uint16 srcCIdx, Uint16 dstCIdx, \
                    Uint8 *srcBuff, Uint8 *dstBuff, Bool abSync );

#ifdef __cplusplus
}
#endif

#endif  /* _EDMACOMMON_H_ */
