/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */
/** ============================================================================
 *   @file  cslr_edma3tc.h
 *
 *   @path  $(CSLPATH)\inc
 *
 *   @desc  This file contains the Register Descriptions for EDMA3TC
 */
#ifndef _CSLR_EDMA3TC_H_
#define _CSLR_EDMA3TC_H_

#include <cslr.h>
#include <tistdtypes.h>

/**************************************************************************\
* Register Overlay Structure for DFIREG 
\**************************************************************************/
typedef struct  {
    volatile Uint32 DFOPT;
    volatile Uint32 DFSRC;
    volatile Uint32 DFCNT;
    volatile Uint32 DFDST;
    volatile Uint32 DFBIDX;
    volatile Uint32 DFMPPRXY;
    volatile Uint8 RSVD0[40];
} CSL_Edma3tcDfiregRegs;

/**************************************************************************\
* Register Overlay Structure
\**************************************************************************/
typedef struct  {
    volatile Uint32 PID;
    volatile Uint32 TCCFG;
    volatile Uint8 RSVD0[248];
    volatile Uint32 TCSTAT;
    volatile Uint8 RSVD1[28];
    volatile Uint32 ERRSTAT;
    volatile Uint32 ERREN;
    volatile Uint32 ERRCLR;
    volatile Uint32 ERRDET;
    volatile Uint32 ERRCMD;
    volatile Uint8 RSVD2[12];
    volatile Uint32 RDRATE;
    volatile Uint8 RSVD3[252];
    volatile Uint32 SAOPT;
    volatile Uint32 SASRC;
    volatile Uint32 SACNT;
    volatile Uint32 SADST;
    volatile Uint32 SABIDX;
    volatile Uint32 SAMPPRXY;
    volatile Uint32 SACNTRLD;
    volatile Uint32 SASRCBREF;
    volatile Uint32 SADSTBREF;
    volatile Uint8 RSVD4[28];
    volatile Uint32 DFCNTRLD;
    volatile Uint32 DFSRCBREF;
    volatile Uint32 DFDSTBREF;
    volatile Uint8 RSVD5[116];
    CSL_Edma3tcDfiregRegs DFIREG[4];
} CSL_Edma3tcRegs;

/**************************************************************************\
* Overlay structure typedef definition
\**************************************************************************/
typedef volatile CSL_Edma3tcRegs  *CSL_Edma3tcRegsOvly;

/**************************************************************************\
* Field Definition Macros
\**************************************************************************/

/* PID */

#define CSL_EDMA3TC_PID_PID_MASK         (0xFFFFFFFFu)
#define CSL_EDMA3TC_PID_PID_SHIFT        (0x00000000u)
#define CSL_EDMA3TC_PID_PID_RESETVAL     (0x00000000u)

#define CSL_EDMA3TC_PID_RESETVAL         (0x00000000u)

/* TCCFG */

#define CSL_EDMA3TC_TCCFG_DREGDEPTH_MASK (0x00000300u)
#define CSL_EDMA3TC_TCCFG_DREGDEPTH_SHIFT (0x00000008u)
#define CSL_EDMA3TC_TCCFG_DREGDEPTH_RESETVAL (0x00000000u)

/*----DREGDEPTH Tokens----*/
#define CSL_EDMA3TC_TCCFG_DREGDEPTH_2ENTRY (0x00000001u)
#define CSL_EDMA3TC_TCCFG_DREGDEPTH_4ENTRY (0x00000002u)

#define CSL_EDMA3TC_TCCFG_BUSWIDTH_MASK  (0x00000030u)
#define CSL_EDMA3TC_TCCFG_BUSWIDTH_SHIFT (0x00000004u)
#define CSL_EDMA3TC_TCCFG_BUSWIDTH_RESETVAL (0x00000000u)

/*----BUSWIDTH Tokens----*/
#define CSL_EDMA3TC_TCCFG_BUSWIDTH_16BYTE (0x00000002u)

#define CSL_EDMA3TC_TCCFG_FIFOSIZE_MASK  (0x00000007u)
#define CSL_EDMA3TC_TCCFG_FIFOSIZE_SHIFT (0x00000000u)
#define CSL_EDMA3TC_TCCFG_FIFOSIZE_RESETVAL (0x00000000u)

/*----FIFOSIZE Tokens----*/
#define CSL_EDMA3TC_TCCFG_FIFOSIZE_128BYTE (0x00000002u)
#define CSL_EDMA3TC_TCCFG_FIFOSIZE_256BYTE (0x00000003u)

#define CSL_EDMA3TC_TCCFG_RESETVAL       (0x00000000u)

/* TCSTAT */

#define CSL_EDMA3TC_TCSTAT_DFSTRTPTR_MASK (0x00003000u)
#define CSL_EDMA3TC_TCSTAT_DFSTRTPTR_SHIFT (0x0000000Cu)
#define CSL_EDMA3TC_TCSTAT_DFSTRTPTR_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_TCSTAT_DSTACTV_MASK  (0x00000070u)
#define CSL_EDMA3TC_TCSTAT_DSTACTV_SHIFT (0x00000004u)
#define CSL_EDMA3TC_TCSTAT_DSTACTV_RESETVAL (0x00000000u)

/*----DSTACTV Tokens----*/
#define CSL_EDMA3TC_TCSTAT_DSTACTV_EMPTY (0x00000000u)
#define CSL_EDMA3TC_TCSTAT_DSTACTV_1TR   (0x00000001u)
#define CSL_EDMA3TC_TCSTAT_DSTACTV_2TR   (0x00000002u)
#define CSL_EDMA3TC_TCSTAT_DSTACTV_3TR   (0x00000003u)
#define CSL_EDMA3TC_TCSTAT_DSTACTV_4TR   (0x00000004u)

#define CSL_EDMA3TC_TCSTAT_WSACTV_MASK   (0x00000004u)
#define CSL_EDMA3TC_TCSTAT_WSACTV_SHIFT  (0x00000002u)
#define CSL_EDMA3TC_TCSTAT_WSACTV_RESETVAL (0x00000000u)

/*----WSACTV Tokens----*/
#define CSL_EDMA3TC_TCSTAT_WSACTV_NONE   (0x00000000u)
#define CSL_EDMA3TC_TCSTAT_WSACTV_PEND   (0x00000001u)

#define CSL_EDMA3TC_TCSTAT_SRCACTV_MASK  (0x00000002u)
#define CSL_EDMA3TC_TCSTAT_SRCACTV_SHIFT (0x00000001u)
#define CSL_EDMA3TC_TCSTAT_SRCACTV_RESETVAL (0x00000000u)

/*----SRCACTV Tokens----*/
#define CSL_EDMA3TC_TCSTAT_SRCACTV_IDLE  (0x00000000u)
#define CSL_EDMA3TC_TCSTAT_SRCACTV_BUSY  (0x00000001u)

#define CSL_EDMA3TC_TCSTAT_PROGBUSY_MASK (0x00000001u)
#define CSL_EDMA3TC_TCSTAT_PROGBUSY_SHIFT (0x00000000u)
#define CSL_EDMA3TC_TCSTAT_PROGBUSY_RESETVAL (0x00000000u)

/*----PROGBUSY Tokens----*/
#define CSL_EDMA3TC_TCSTAT_PROGBUSY_IDLE (0x00000000u)
#define CSL_EDMA3TC_TCSTAT_PROGBUSY_BUSY (0x00000001u)

#define CSL_EDMA3TC_TCSTAT_RESETVAL      (0x00000100u)

/* ERRSTAT */

#define CSL_EDMA3TC_ERRSTAT_MMRAERR_MASK (0x00000008u)
#define CSL_EDMA3TC_ERRSTAT_MMRAERR_SHIFT (0x00000003u)
#define CSL_EDMA3TC_ERRSTAT_MMRAERR_RESETVAL (0x00000000u)

/*----MMRAERR Tokens----*/
#define CSL_EDMA3TC_ERRSTAT_MMRAERR_NONE (0x00000000u)
#define CSL_EDMA3TC_ERRSTAT_MMRAERR_ERROR (0x00000001u)

#define CSL_EDMA3TC_ERRSTAT_TRERR_MASK   (0x00000004u)
#define CSL_EDMA3TC_ERRSTAT_TRERR_SHIFT  (0x00000002u)
#define CSL_EDMA3TC_ERRSTAT_TRERR_RESETVAL (0x00000000u)

/*----TRERR Tokens----*/
#define CSL_EDMA3TC_ERRSTAT_TRERR_NONE   (0x00000000u)
#define CSL_EDMA3TC_ERRSTAT_TRERR_ERROR  (0x00000001u)

#define CSL_EDMA3TC_ERRSTAT_BUSERR_MASK  (0x00000001u)
#define CSL_EDMA3TC_ERRSTAT_BUSERR_SHIFT (0x00000000u)
#define CSL_EDMA3TC_ERRSTAT_BUSERR_RESETVAL (0x00000000u)

/*----BUSERR Tokens----*/
#define CSL_EDMA3TC_ERRSTAT_BUSERR_NONE  (0x00000000u)
#define CSL_EDMA3TC_ERRSTAT_BUSERR_ERROR (0x00000001u)

#define CSL_EDMA3TC_ERRSTAT_RESETVAL     (0x00000000u)

/* ERREN */

#define CSL_EDMA3TC_ERREN_MMRAERR_MASK   (0x00000008u)
#define CSL_EDMA3TC_ERREN_MMRAERR_SHIFT  (0x00000003u)
#define CSL_EDMA3TC_ERREN_MMRAERR_RESETVAL (0x00000000u)

/*----MMRAERR Tokens----*/
#define CSL_EDMA3TC_ERREN_MMRAERR_ENABLE (0x00000001u)
#define CSL_EDMA3TC_ERREN_MMRAERR_DISABLE (0x00000000u)

#define CSL_EDMA3TC_ERREN_TRERR_MASK     (0x00000004u)
#define CSL_EDMA3TC_ERREN_TRERR_SHIFT    (0x00000002u)
#define CSL_EDMA3TC_ERREN_TRERR_RESETVAL (0x00000000u)

/*----TRERR Tokens----*/
#define CSL_EDMA3TC_ERREN_TRERR_ENABLE   (0x00000001u)
#define CSL_EDMA3TC_ERREN_TRERR_DISABLE  (0x00000000u)

#define CSL_EDMA3TC_ERREN_BUSERR_MASK    (0x00000001u)
#define CSL_EDMA3TC_ERREN_BUSERR_SHIFT   (0x00000000u)
#define CSL_EDMA3TC_ERREN_BUSERR_RESETVAL (0x00000000u)

/*----BUSERR Tokens----*/
#define CSL_EDMA3TC_ERREN_BUSERR_ENABLE  (0x00000001u)
#define CSL_EDMA3TC_ERREN_BUSERR_DISABLE (0x00000000u)

#define CSL_EDMA3TC_ERREN_RESETVAL       (0x00000000u)

/* ERRCLR */

#define CSL_EDMA3TC_ERRCLR_MMRAERR_MASK  (0x00000008u)
#define CSL_EDMA3TC_ERRCLR_MMRAERR_SHIFT (0x00000003u)
#define CSL_EDMA3TC_ERRCLR_MMRAERR_RESETVAL (0x00000000u)

/*----MMRAERR Tokens----*/
#define CSL_EDMA3TC_ERRCLR_MMRAERR_CLEAR (0x00000001u)

#define CSL_EDMA3TC_ERRCLR_TRERR_MASK    (0x00000004u)
#define CSL_EDMA3TC_ERRCLR_TRERR_SHIFT   (0x00000002u)
#define CSL_EDMA3TC_ERRCLR_TRERR_RESETVAL (0x00000000u)

/*----TRERR Tokens----*/
#define CSL_EDMA3TC_ERRCLR_TRERR_CLEAR   (0x00000001u)

#define CSL_EDMA3TC_ERRCLR_BUSERR_MASK   (0x00000001u)
#define CSL_EDMA3TC_ERRCLR_BUSERR_SHIFT  (0x00000000u)
#define CSL_EDMA3TC_ERRCLR_BUSERR_RESETVAL (0x00000000u)

/*----BUSERR Tokens----*/
#define CSL_EDMA3TC_ERRCLR_BUSERR_CLEAR  (0x00000001u)

#define CSL_EDMA3TC_ERRCLR_RESETVAL      (0x00000000u)

/* ERRDET */

#define CSL_EDMA3TC_ERRDET_TCCHEN_MASK   (0x00020000u)
#define CSL_EDMA3TC_ERRDET_TCCHEN_SHIFT  (0x00000011u)
#define CSL_EDMA3TC_ERRDET_TCCHEN_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_ERRDET_TCINTEN_MASK  (0x00010000u)
#define CSL_EDMA3TC_ERRDET_TCINTEN_SHIFT (0x00000010u)
#define CSL_EDMA3TC_ERRDET_TCINTEN_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_ERRDET_TCC_MASK      (0x00003F00u)
#define CSL_EDMA3TC_ERRDET_TCC_SHIFT     (0x00000008u)
#define CSL_EDMA3TC_ERRDET_TCC_RESETVAL  (0x00000000u)

#define CSL_EDMA3TC_ERRDET_STAT_MASK     (0x0000000Fu)
#define CSL_EDMA3TC_ERRDET_STAT_SHIFT    (0x00000000u)
#define CSL_EDMA3TC_ERRDET_STAT_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_ERRDET_RESETVAL      (0x00000000u)

/* ERRCMD */

#define CSL_EDMA3TC_ERRCMD_EVAL_MASK     (0x00000001u)
#define CSL_EDMA3TC_ERRCMD_EVAL_SHIFT    (0x00000000u)
#define CSL_EDMA3TC_ERRCMD_EVAL_RESETVAL (0x00000000u)

/*----EVAL Tokens----*/
#define CSL_EDMA3TC_ERRCMD_EVAL_EVAL     (0x00000001u)

#define CSL_EDMA3TC_ERRCMD_RESETVAL      (0x00000000u)

/* RDRATE */

#define CSL_EDMA3TC_RDRATE_RDRATE_MASK   (0x00000007u)
#define CSL_EDMA3TC_RDRATE_RDRATE_SHIFT  (0x00000000u)
#define CSL_EDMA3TC_RDRATE_RDRATE_RESETVAL (0x00000000u)

/*----RDRATE Tokens----*/
#define CSL_EDMA3TC_RDRATE_RDRATE_AFAP   (0x00000000u)
#define CSL_EDMA3TC_RDRATE_RDRATE_4CYCLE (0x00000001u)
#define CSL_EDMA3TC_RDRATE_RDRATE_8CYCLE (0x00000002u)
#define CSL_EDMA3TC_RDRATE_RDRATE_16CYCLE (0x00000003u)
#define CSL_EDMA3TC_RDRATE_RDRATE_32CYCLE (0x00000004u)

#define CSL_EDMA3TC_RDRATE_RESETVAL      (0x00000000u)

/* SAOPT */

#define CSL_EDMA3TC_SAOPT_TCCHEN_MASK    (0x00400000u)
#define CSL_EDMA3TC_SAOPT_TCCHEN_SHIFT   (0x00000016u)
#define CSL_EDMA3TC_SAOPT_TCCHEN_RESETVAL (0x00000000u)

/*----TCCHEN Tokens----*/
#define CSL_EDMA3TC_SAOPT_TCCHEN_DISABLE (0x00000000u)
#define CSL_EDMA3TC_SAOPT_TCCHEN_ENABLE  (0x00000001u)

#define CSL_EDMA3TC_SAOPT_TCINTEN_MASK   (0x00100000u)
#define CSL_EDMA3TC_SAOPT_TCINTEN_SHIFT  (0x00000014u)
#define CSL_EDMA3TC_SAOPT_TCINTEN_RESETVAL (0x00000000u)

/*----TCINTEN Tokens----*/
#define CSL_EDMA3TC_SAOPT_TCINTEN_DISABLE (0x00000000u)
#define CSL_EDMA3TC_SAOPT_TCINTEN_ENABLE (0x00000001u)

#define CSL_EDMA3TC_SAOPT_TCC_MASK       (0x0003F000u)
#define CSL_EDMA3TC_SAOPT_TCC_SHIFT      (0x0000000Cu)
#define CSL_EDMA3TC_SAOPT_TCC_RESETVAL   (0x00000000u)

#define CSL_EDMA3TC_SAOPT_FWID_MASK      (0x00000700u)
#define CSL_EDMA3TC_SAOPT_FWID_SHIFT     (0x00000008u)
#define CSL_EDMA3TC_SAOPT_FWID_RESETVAL  (0x00000000u)

/*----FWID Tokens----*/
#define CSL_EDMA3TC_SAOPT_FWID_8BIT      (0x00000000u)
#define CSL_EDMA3TC_SAOPT_FWID_16BIT     (0x00000001u)
#define CSL_EDMA3TC_SAOPT_FWID_32BIT     (0x00000002u)
#define CSL_EDMA3TC_SAOPT_FWID_64BIT     (0x00000003u)
#define CSL_EDMA3TC_SAOPT_FWID_128BIT    (0x00000004u)
#define CSL_EDMA3TC_SAOPT_FWID_256BIT    (0x00000005u)

#define CSL_EDMA3TC_SAOPT_PRI_MASK       (0x00000070u)
#define CSL_EDMA3TC_SAOPT_PRI_SHIFT      (0x00000004u)
#define CSL_EDMA3TC_SAOPT_PRI_RESETVAL   (0x00000000u)

#define CSL_EDMA3TC_SAOPT_DAM_MASK       (0x00000002u)
#define CSL_EDMA3TC_SAOPT_DAM_SHIFT      (0x00000001u)
#define CSL_EDMA3TC_SAOPT_DAM_RESETVAL   (0x00000000u)

/*----DAM Tokens----*/
#define CSL_EDMA3TC_SAOPT_DAM_INCR       (0x00000000u)
#define CSL_EDMA3TC_SAOPT_DAM_CONST      (0x00000001u)

#define CSL_EDMA3TC_SAOPT_SAM_MASK       (0x00000001u)
#define CSL_EDMA3TC_SAOPT_SAM_SHIFT      (0x00000000u)
#define CSL_EDMA3TC_SAOPT_SAM_RESETVAL   (0x00000000u)

/*----SAM Tokens----*/
#define CSL_EDMA3TC_SAOPT_SAM_INCR       (0x00000000u)
#define CSL_EDMA3TC_SAOPT_SAM_CONST      (0x00000001u)

#define CSL_EDMA3TC_SAOPT_RESETVAL       (0x00000000u)

/* SASRC */

#define CSL_EDMA3TC_SASRC_SADDR_MASK     (0xFFFFFFFFu)
#define CSL_EDMA3TC_SASRC_SADDR_SHIFT    (0x00000000u)
#define CSL_EDMA3TC_SASRC_SADDR_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SASRC_RESETVAL       (0x00000000u)

/* SACNT */

#define CSL_EDMA3TC_SACNT_BCNT_MASK      (0xFFFF0000u)
#define CSL_EDMA3TC_SACNT_BCNT_SHIFT     (0x00000010u)
#define CSL_EDMA3TC_SACNT_BCNT_RESETVAL  (0x00000000u)

#define CSL_EDMA3TC_SACNT_ACNT_MASK      (0x0000FFFFu)
#define CSL_EDMA3TC_SACNT_ACNT_SHIFT     (0x00000000u)
#define CSL_EDMA3TC_SACNT_ACNT_RESETVAL  (0x00000000u)

#define CSL_EDMA3TC_SACNT_RESETVAL       (0x00000000u)

/* SADST */

#define CSL_EDMA3TC_SADST_DADDR_MASK     (0xFFFFFFFFu)
#define CSL_EDMA3TC_SADST_DADDR_SHIFT    (0x00000000u)
#define CSL_EDMA3TC_SADST_DADDR_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SADST_RESETVAL       (0x00000000u)

/* SABIDX */

#define CSL_EDMA3TC_SABIDX_DSTBIDX_MASK  (0xFFFF0000u)
#define CSL_EDMA3TC_SABIDX_DSTBIDX_SHIFT (0x00000010u)
#define CSL_EDMA3TC_SABIDX_DSTBIDX_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SABIDX_SRCBIDX_MASK  (0x0000FFFFu)
#define CSL_EDMA3TC_SABIDX_SRCBIDX_SHIFT (0x00000000u)
#define CSL_EDMA3TC_SABIDX_SRCBIDX_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SABIDX_RESETVAL      (0x00000000u)

/* SAMPPRXY */

#define CSL_EDMA3TC_SAMPPRXY_PRIV_MASK   (0x00000100u)
#define CSL_EDMA3TC_SAMPPRXY_PRIV_SHIFT  (0x00000008u)
#define CSL_EDMA3TC_SAMPPRXY_PRIV_RESETVAL (0x00000000u)

/*----PRIV Tokens----*/
#define CSL_EDMA3TC_SAMPPRXY_PRIV_USER   (0x00000000u)
#define CSL_EDMA3TC_SAMPPRXY_PRIV_SUPERVISOR (0x00000001u)

#define CSL_EDMA3TC_SAMPPRXY_PRIVID_MASK (0x0000000Fu)
#define CSL_EDMA3TC_SAMPPRXY_PRIVID_SHIFT (0x00000000u)
#define CSL_EDMA3TC_SAMPPRXY_PRIVID_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SAMPPRXY_RESETVAL    (0x00000000u)

/* SACNTRLD */

#define CSL_EDMA3TC_SACNTRLD_ACNTRLD_MASK (0x0000FFFFu)
#define CSL_EDMA3TC_SACNTRLD_ACNTRLD_SHIFT (0x00000000u)
#define CSL_EDMA3TC_SACNTRLD_ACNTRLD_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SACNTRLD_RESETVAL    (0x00000000u)

/* SASRCBREF */

#define CSL_EDMA3TC_SASRCBREF_SADDRBREF_MASK (0xFFFFFFFFu)
#define CSL_EDMA3TC_SASRCBREF_SADDRBREF_SHIFT (0x00000000u)
#define CSL_EDMA3TC_SASRCBREF_SADDRBREF_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SASRCBREF_RESETVAL   (0x00000000u)

/* SADSTBREF */

#define CSL_EDMA3TC_SADSTBREF_DADDRBREF_MASK (0xFFFFFFFFu)
#define CSL_EDMA3TC_SADSTBREF_DADDRBREF_SHIFT (0x00000000u)
#define CSL_EDMA3TC_SADSTBREF_DADDRBREF_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_SADSTBREF_RESETVAL   (0x00000000u)

/* DFCNTRLD */

#define CSL_EDMA3TC_DFCNTRLD_ACNTRLD_MASK (0x0000FFFFu)
#define CSL_EDMA3TC_DFCNTRLD_ACNTRLD_SHIFT (0x00000000u)
#define CSL_EDMA3TC_DFCNTRLD_ACNTRLD_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFCNTRLD_RESETVAL    (0x00000000u)

/* DFSRCBREF */

#define CSL_EDMA3TC_DFSRCBREF_SADDRBREF_MASK (0xFFFFFFFFu)
#define CSL_EDMA3TC_DFSRCBREF_SADDRBREF_SHIFT (0x00000000u)
#define CSL_EDMA3TC_DFSRCBREF_SADDRBREF_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFSRCBREF_RESETVAL   (0x00000000u)

/* DFDSTBREF */

#define CSL_EDMA3TC_DFDSTBREF_DADDRBREF_MASK (0xFFFFFFFFu)
#define CSL_EDMA3TC_DFDSTBREF_DADDRBREF_SHIFT (0x00000000u)
#define CSL_EDMA3TC_DFDSTBREF_DADDRBREF_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFDSTBREF_RESETVAL   (0x00000000u)

/* DFOPT */

#define CSL_EDMA3TC_DFOPT_TCCHEN_MASK    (0x00400000u)
#define CSL_EDMA3TC_DFOPT_TCCHEN_SHIFT   (0x00000016u)
#define CSL_EDMA3TC_DFOPT_TCCHEN_RESETVAL (0x00000000u)

/*----TCCHEN Tokens----*/
#define CSL_EDMA3TC_DFOPT_TCCHEN_DISABLE (0x00000000u)
#define CSL_EDMA3TC_DFOPT_TCCHEN_ENABLE  (0x00000001u)

#define CSL_EDMA3TC_DFOPT_TCINTEN_MASK   (0x00100000u)
#define CSL_EDMA3TC_DFOPT_TCINTEN_SHIFT  (0x00000014u)
#define CSL_EDMA3TC_DFOPT_TCINTEN_RESETVAL (0x00000000u)

/*----TCINTEN Tokens----*/
#define CSL_EDMA3TC_DFOPT_TCINTEN_DISABLE (0x00000000u)
#define CSL_EDMA3TC_DFOPT_TCINTEN_ENABLE (0x00000001u)

#define CSL_EDMA3TC_DFOPT_TCC_MASK       (0x0003F000u)
#define CSL_EDMA3TC_DFOPT_TCC_SHIFT      (0x0000000Cu)
#define CSL_EDMA3TC_DFOPT_TCC_RESETVAL   (0x00000000u)

#define CSL_EDMA3TC_DFOPT_FWID_MASK      (0x00000700u)
#define CSL_EDMA3TC_DFOPT_FWID_SHIFT     (0x00000008u)
#define CSL_EDMA3TC_DFOPT_FWID_RESETVAL  (0x00000000u)

/*----FWID Tokens----*/
#define CSL_EDMA3TC_DFOPT_FWID_8BIT      (0x00000000u)
#define CSL_EDMA3TC_DFOPT_FWID_16BIT     (0x00000001u)
#define CSL_EDMA3TC_DFOPT_FWID_32BIT     (0x00000002u)
#define CSL_EDMA3TC_DFOPT_FWID_64BIT     (0x00000003u)
#define CSL_EDMA3TC_DFOPT_FWID_128BIT    (0x00000004u)
#define CSL_EDMA3TC_DFOPT_FWID_256BIT    (0x00000005u)

#define CSL_EDMA3TC_DFOPT_PRI_MASK       (0x00000070u)
#define CSL_EDMA3TC_DFOPT_PRI_SHIFT      (0x00000004u)
#define CSL_EDMA3TC_DFOPT_PRI_RESETVAL   (0x00000000u)

#define CSL_EDMA3TC_DFOPT_DAM_MASK       (0x00000002u)
#define CSL_EDMA3TC_DFOPT_DAM_SHIFT      (0x00000001u)
#define CSL_EDMA3TC_DFOPT_DAM_RESETVAL   (0x00000000u)

/*----DAM Tokens----*/
#define CSL_EDMA3TC_DFOPT_DAM_INCR       (0x00000000u)
#define CSL_EDMA3TC_DFOPT_DAM_FIFO       (0x00000001u)

#define CSL_EDMA3TC_DFOPT_SAM_MASK       (0x00000001u)
#define CSL_EDMA3TC_DFOPT_SAM_SHIFT      (0x00000000u)
#define CSL_EDMA3TC_DFOPT_SAM_RESETVAL   (0x00000000u)

/*----SAM Tokens----*/
#define CSL_EDMA3TC_DFOPT_SAM_INCR       (0x00000000u)
#define CSL_EDMA3TC_DFOPT_SAM_FIFO       (0x00000001u)

#define CSL_EDMA3TC_DFOPT_RESETVAL       (0x00000000u)

/* DFSRC */

#define CSL_EDMA3TC_DFSRC_SADDR_MASK     (0xFFFFFFFFu)
#define CSL_EDMA3TC_DFSRC_SADDR_SHIFT    (0x00000000u)
#define CSL_EDMA3TC_DFSRC_SADDR_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFSRC_RESETVAL       (0x00000000u)

/* DFCNT */

#define CSL_EDMA3TC_DFCNT_BCNT_MASK      (0xFFFF0000u)
#define CSL_EDMA3TC_DFCNT_BCNT_SHIFT     (0x00000010u)
#define CSL_EDMA3TC_DFCNT_BCNT_RESETVAL  (0x00000000u)

#define CSL_EDMA3TC_DFCNT_ACNT_MASK      (0x0000FFFFu)
#define CSL_EDMA3TC_DFCNT_ACNT_SHIFT     (0x00000000u)
#define CSL_EDMA3TC_DFCNT_ACNT_RESETVAL  (0x00000000u)

#define CSL_EDMA3TC_DFCNT_RESETVAL       (0x00000000u)

/* DFDST */

#define CSL_EDMA3TC_DFDST_DADDR_MASK     (0xFFFFFFFFu)
#define CSL_EDMA3TC_DFDST_DADDR_SHIFT    (0x00000000u)
#define CSL_EDMA3TC_DFDST_DADDR_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFDST_RESETVAL       (0x00000000u)

/* DFBIDX */

#define CSL_EDMA3TC_DFBIDX_DSTBIDX_MASK  (0xFFFF0000u)
#define CSL_EDMA3TC_DFBIDX_DSTBIDX_SHIFT (0x00000010u)
#define CSL_EDMA3TC_DFBIDX_DSTBIDX_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFBIDX_SRCBIDX_MASK  (0x0000FFFFu)
#define CSL_EDMA3TC_DFBIDX_SRCBIDX_SHIFT (0x00000000u)
#define CSL_EDMA3TC_DFBIDX_SRCBIDX_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFBIDX_RESETVAL      (0x00000000u)

/* DFMPPRXY */

#define CSL_EDMA3TC_DFMPPRXY_PRIV_MASK   (0x00000100u)
#define CSL_EDMA3TC_DFMPPRXY_PRIV_SHIFT  (0x00000008u)
#define CSL_EDMA3TC_DFMPPRXY_PRIV_RESETVAL (0x00000000u)

/*----PRIV Tokens----*/
#define CSL_EDMA3TC_DFMPPRXY_PRIV_USER   (0x00000000u)
#define CSL_EDMA3TC_DFMPPRXY_PRIV_SUPERVISOR (0x00000001u)

#define CSL_EDMA3TC_DFMPPRXY_PRIVID_MASK (0x0000000Fu)
#define CSL_EDMA3TC_DFMPPRXY_PRIVID_SHIFT (0x00000000u)
#define CSL_EDMA3TC_DFMPPRXY_PRIVID_RESETVAL (0x00000000u)

#define CSL_EDMA3TC_DFMPPRXY_RESETVAL    (0x00000000u)

#endif
