/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */


/** ===========================================================================
 * @file  Vcp2_example.h
 *
 * @path  $(CSLPATH)\example\c6455\vcp2\vcp2_hard_decisions\inc
 *
 * @desc  Example header file for VCP.
 *
 * ============================================================================
 */
/* ============================================================================
 *  Revision History
 *  ===============
 *  20-May-2005   SPrasad     File Created.
 *  01-Aug-2005   Chandra     Beautified
 *  11-Aug-2005   Chandra     Minor format chagnes.
 * ============================================================================
 */
 
 
#ifndef _VCP2_EXAMPLE_H_
#define _VCP2_EXAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Space for the banch metrics */
extern Uint32 branch_metric[];

/* Space for the hard decisions */
extern Uint32 hard_decision[];

/* Space for the pre-computed hard decisions */
extern Uint32 hard_decisionRef[];


#ifdef __cplusplus
}
#endif

#endif /*_VCP2_EXAMPLE_H_*/
