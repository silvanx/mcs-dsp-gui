/*  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *   ==========================================================================
 */


/** ===========================================================================
 * @file  vcp2_example.h
 *
 * @path  $(CSLPATH)\example\c6455\vcp2\vcp2_soft_decisions\inc
 *
 * @desc  Example header file for VCP2.
 *
 * ============================================================================
 */
 
/* ============================================================================
 *  Revision History
 *  ===============
  *  09-10-2005   SD     File created
 * ============================================================================
 */

#ifndef _VCP2_EXAMPLE_H_
#define _VCP2_EXAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Space for the branch metrics */
extern Uint32 branch_metric[];

/* Space for the soft decisions */
extern Uint32 soft_decision[];

/* Space for the pre-computed soft decisions */
extern Uint32 soft_decisionRef[];


#ifdef __cplusplus
}
#endif

#endif /*_VCP2_EXAMPLE_H_*/
