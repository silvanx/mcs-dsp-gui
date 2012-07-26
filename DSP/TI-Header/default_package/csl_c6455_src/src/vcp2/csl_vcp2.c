/* ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in
 *   the license agreement under which this software has been supplied.
 *  ===========================================================================
 */

/** ===========================================================================
 *   @file  csl_vcp2.c
 *
 *   @path  $(CSLPATH)\src\vcp2
 *
 *   @desc  VCP API implementation
 *
 */

/* ============================================================================
 *  Revision History
 *  ================
 *  30-March-2005   SPrasad     File Created.
 *  21-April-2005   Sprasad     Bug fix.
 *  27-May-2005     SPrasad     Updated with new requirements' specification.
 *  03-Aug-2005     Chandra     Minor beautification changes.
 *  20-Sep-2005     Chandra     Replaced the hardcodes with hash defines.
 *  8-dec-2005      sd          changed the maxSm and minSm to be signed 
 *                              integers
 *	3-Feb-2005      sd			Changes for the user guide changes
 * ============================================================================
 */

#include <csl_vcp2.h>
#include <csl_vcp2Aux.h>

/* Polynomials for different constraint lengths and
   code rates
   - All these are octal numbers
   - Default values
*/
#define VCP2_POLY0_FOR_CONST9_RATE_1_2 0561
#define VCP2_POLY1_FOR_CONST9_RATE_1_2 0753

#define VCP2_POLY0_FOR_CONST8_RATE_1_2 0712
#define VCP2_POLY1_FOR_CONST8_RATE_1_2 0476

#define VCP2_POLY0_FOR_CONST7_RATE_1_2 0554
#define VCP2_POLY1_FOR_CONST7_RATE_1_2 0744

#define VCP2_POLY0_FOR_CONST6_RATE_1_2 0650
#define VCP2_POLY1_FOR_CONST6_RATE_1_2 0570

#define VCP2_POLY0_FOR_CONST5_RATE_1_2 0460
#define VCP2_POLY1_FOR_CONST5_RATE_1_2 0720


#define VCP2_POLY0_FOR_CONST9_RATE_1_3_1_4 0557
#define VCP2_POLY1_FOR_CONST9_RATE_1_3_1_4 0663
#define VCP2_POLY2_FOR_CONST9_RATE_1_3_1_4 0711
#define VCP2_POLY3_FOR_CONST9_RATE_1_3_1_4 0557

#define VCP2_POLY0_FOR_CONST8_RATE_1_3_1_4 0452
#define VCP2_POLY1_FOR_CONST8_RATE_1_3_1_4 0662
#define VCP2_POLY2_FOR_CONST8_RATE_1_3_1_4 0756
#define VCP2_POLY3_FOR_CONST8_RATE_1_3_1_4 0452

#define VCP2_POLY0_FOR_CONST7_RATE_1_3_1_4 0544
#define VCP2_POLY1_FOR_CONST7_RATE_1_3_1_4 0624
#define VCP2_POLY2_FOR_CONST7_RATE_1_3_1_4 0764
#define VCP2_POLY3_FOR_CONST7_RATE_1_3_1_4 0544

#define VCP2_POLY0_FOR_CONST6_RATE_1_3_1_4 0470
#define VCP2_POLY1_FOR_CONST6_RATE_1_3_1_4 0530
#define VCP2_POLY2_FOR_CONST6_RATE_1_3_1_4 0750
#define VCP2_POLY3_FOR_CONST6_RATE_1_3_1_4 0470

#define VCP2_POLY0_FOR_CONST5_RATE_1_3_1_4 0520
#define VCP2_POLY1_FOR_CONST5_RATE_1_3_1_4 0660
#define VCP2_POLY2_FOR_CONST5_RATE_1_3_1_4 0760
#define VCP2_POLY3_FOR_CONST5_RATE_1_3_1_4 0520

/* Maxmimum frame sizes, maximum (reliability length +
   convergence distance) and the number of trellis stages
   processed in 2 passes for different constraint
   lengths of soft and hard decisions
*/

/* For Hard Decisions */
#define VCP2_MAX_FRAME_SIZE_FOR_HD_CONST9          120
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST9    124
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST9  4

#define VCP2_MAX_FRAME_SIZE_FOR_HD_CONST8          217
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST8    217
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST8  7

#define VCP2_MAX_FRAME_SIZE_FOR_HD_CONST7          378
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST7    378
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST7  6

#define VCP2_MAX_FRAME_SIZE_FOR_HD_CONST6          635
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST6    635
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST6  5

#define VCP2_MAX_FRAME_SIZE_FOR_HD_CONST5          2044
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST5    2044
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST5  4

/* For Soft Decisions */
#define VCP2_MAX_FRAME_SIZE_FOR_SD_CONST9          56
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST9    60
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST9  4

#define VCP2_MAX_FRAME_SIZE_FOR_SD_CONST8          105
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST8    105
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST8  7

#define VCP2_MAX_FRAME_SIZE_FOR_SD_CONST7          186
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST7    186
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST7  6

#define VCP2_MAX_FRAME_SIZE_FOR_SD_CONST6          315
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST6    315
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST6  5

#define VCP2_MAX_FRAME_SIZE_FOR_SD_CONST5          1020
#define VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST5    1020
#define VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST5  4

/* Limit on sliding window length in case more than 1 sliding
   window is required. (see section 2.4.5.4) */
#define VCP2_REL_LEN_LIMIT_FOR_A_SILDING_WINDOW 248

/* Branch metrics buffer length and branch metrics per
   trellis state for different code rates */
#define VCP2_BM_PER_TRL_FOR_RATE_1_4                8
#define VCP2_SYMX_FOR_128_BYTE_PER_RXEVENT_RATE_1_4 3

#define VCP2_BM_PER_TRL_FOR_RATE_1_3                4
#define VCP2_SYMX_FOR_128_BYTE_PER_RXEVENT_RATE_1_3 7

#define VCP2_BM_PER_TRL_FOR_RATE_1_2                2
#define VCP2_SYMX_FOR_128_BYTE_PER_RXEVENT_RATE_1_2 15

/* Number of bytes transfered to the VCP2 per receive event */
#define VCP2_BYTE_COUNT_PER_RXEVENT  128

/* Maximum hard decisions in out FIFO */
#define VCP2_MAX_HD_IN_OUTFIFO       2048

/* Number of hard decisions per FIFO word */
#define VCP2_HD_PER_OUTFIFO_WORD     64

/* Maximum soft decisions in out FIFO */
#define VCP2_MAX_SD_IN_OUTFIFO       256

/* Number of hard decisions per FIFO word */
#define VCP2_SD_PER_OUTFIFO_WORD     8

/* Number of words in out FIFO */
#define VCP2_OUTFIFO_WORDS           32


/** ===========================================================================
 *   @n@b VCP2_genParams
 *
 *   @b Description
 *   @n This function calculates the VCP parameters based on the input 
 *      VCP2_BaseParams object values and set the values to the output
 *      VCP2_Params parameters structure.
 *
 *   @b Arguments
     @verbatim
            pConfigBase     Pointer to VCP base parameters structure.
            
            pConfigParams   Pointer to output VCP channel parameters structure.
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
 *   @b  Modifies
 *   @n  Input VCP2_Params structure instance pointed by pConfigParams.  
 *
 *   @b Example
 *   @verbatim
            VCP2_Params      vcpParam;
            VCP2_BaseParams  vcpBaseParam;
            ...
            vcpBaseParam.rate           =   VCP2_RATE_1_4;
            vcpBaseParam.constLen       =   5;
            vcpBaseParam.frameLen       =   2042;
            vcpBaseParam.yamTh          =   50;
            vcpBaseParam.stateNum       =   2048;
            vcpBaseParam.tbConvrgMode   =   FALSE;
            vcpBaseParam.decision       =   VCP2_DECISION_HARD;
            vcpBaseParam.readFlag       =   VCP2_OUTF_YES;
            vcpBaseParam.tailBitEnable  =   FALSE;
            vcpBaseParam.traceBackIndex =   0x0;
            vcpBaseParam.outOrder       =   VCP2_OUTORDER_0_31;
            vcpBaseParam.perf           =   VCP2_SPEED_CRITICAL;
            ... 
            VCP2_genParams (&vcpBaseParam, &vcpParam);
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (VCP2_genParams, ".text:csl_section:vcp2");
void
VCP2_genParams (
	VCP2_BaseParams * restrict pConfigBase,
	VCP2_Params * restrict pConfigParams
)
{
    VCP2_Rate rate = pConfigBase->rate;
    Bool tbConvrgMode = pConfigBase->tbConvrgMode;
    Bool tailBitEnable = pConfigBase->tailBitEnable;
    Uint8 constLen = pConfigBase->constLen;
    Uint8 decision = pConfigBase->decision;
    Uint8 readFlag = pConfigBase->readFlag;
    Uint8 stateNum = pConfigBase->stateNum;
    Uint8 outOrder = pConfigBase->outOrder;
    Uint8 perf = pConfigBase->perf;
    Uint16 frameLen = pConfigBase->frameLen;
    Uint16 yamTh = pConfigBase->yamTh;
    Uint16 traceBackIndex = pConfigBase->traceBackIndex;

    Uint8 poly0 = 0;
    Uint8 poly1 = 0;
    Uint8 poly2 = 0;
    Uint8 poly3 = 0;
    Uint16 relLen = 0;
    Uint16 convDist = 0;
    Int16 minSm = 0;
    Int16 maxSm = 0x400; /* Select a maximum value for initial state metric */
    Uint8 bmBuffLen;
    Uint8 decBuffLen;
    Uint16 numBmFrames;
    Uint16 numDecFrames;
    Uint8 traceBack;

    Uint8 i;
    Uint8 convMultiplier;
    Uint16 polynomes[4];
    Uint16 fMax;
    Uint16 rcMax;
    Uint16 multiple;
    Uint16 nsw;
    Uint16 mask;
    Uint16 bmNum;
    Uint32 bmCnt;

    /* VCPIC0 parameters */
    if (rate == VCP2_RATE_1_2) {
        if (constLen == 9) {
            polynomes[0] = VCP2_POLY0_FOR_CONST9_RATE_1_2;
            polynomes[1] = VCP2_POLY1_FOR_CONST9_RATE_1_2;
        }                       /* end if constLen == 9 */
        else if (constLen == 8) {
            polynomes[0] = VCP2_POLY0_FOR_CONST8_RATE_1_2;
            polynomes[1] = VCP2_POLY1_FOR_CONST8_RATE_1_2;
        }                       /* end if constLen == 8 */
        else if (constLen == 7) {
            polynomes[0] = VCP2_POLY0_FOR_CONST7_RATE_1_2;
            polynomes[1] = VCP2_POLY1_FOR_CONST7_RATE_1_2;
        }                       /* end if constLen == 7 */
        else if (constLen == 6) {
            polynomes[0] = VCP2_POLY0_FOR_CONST6_RATE_1_2;
            polynomes[1] = VCP2_POLY1_FOR_CONST6_RATE_1_2;
        }                       /* end if constLen == 6 */
        else {                  /* (constLen == 5) */
            polynomes[0] = VCP2_POLY0_FOR_CONST5_RATE_1_2;
            polynomes[1] = VCP2_POLY1_FOR_CONST5_RATE_1_2;
        }                       /* end if constLen == 5 */
    }                           /* end if rate 1/2 */
    else {                      /* if rate 1/3 or 1/4 */
        if (constLen == 9) {
            polynomes[0] = VCP2_POLY0_FOR_CONST9_RATE_1_3_1_4;
            polynomes[1] = VCP2_POLY1_FOR_CONST9_RATE_1_3_1_4;
            polynomes[2] = VCP2_POLY2_FOR_CONST9_RATE_1_3_1_4;
            polynomes[3] = VCP2_POLY3_FOR_CONST9_RATE_1_3_1_4;
        }                       /* end if constLen == 9 */
        else if (constLen == 8) {
            polynomes[0] = VCP2_POLY0_FOR_CONST8_RATE_1_3_1_4;
            polynomes[1] = VCP2_POLY1_FOR_CONST8_RATE_1_3_1_4;
            polynomes[2] = VCP2_POLY2_FOR_CONST8_RATE_1_3_1_4;
            polynomes[3] = VCP2_POLY3_FOR_CONST8_RATE_1_3_1_4;
        }                       /* end if constLen == 8 */
        else if (constLen == 7) {
            polynomes[0] = VCP2_POLY0_FOR_CONST7_RATE_1_3_1_4;
            polynomes[1] = VCP2_POLY1_FOR_CONST7_RATE_1_3_1_4;
            polynomes[2] = VCP2_POLY2_FOR_CONST7_RATE_1_3_1_4;
            polynomes[3] = VCP2_POLY3_FOR_CONST7_RATE_1_3_1_4;
        }                       /* end if constLen == 7 */
        else if (constLen == 6) {
            polynomes[0] = VCP2_POLY0_FOR_CONST6_RATE_1_3_1_4;
            polynomes[1] = VCP2_POLY1_FOR_CONST6_RATE_1_3_1_4;
            polynomes[2] = VCP2_POLY2_FOR_CONST6_RATE_1_3_1_4;
            polynomes[3] = VCP2_POLY3_FOR_CONST6_RATE_1_3_1_4;
        }                       /* end if constLen == 6 */
        else {                  /* (constLen == 5) */
            polynomes[0] = VCP2_POLY0_FOR_CONST5_RATE_1_3_1_4;
            polynomes[1] = VCP2_POLY1_FOR_CONST5_RATE_1_3_1_4;
            polynomes[2] = VCP2_POLY2_FOR_CONST5_RATE_1_3_1_4;
            polynomes[3] = VCP2_POLY3_FOR_CONST5_RATE_1_3_1_4;
        }                       /* end if constLen == 5 */
    }                           /* end if rate 1/3 or 1/4 */

    /* zero out any unneeded polynomials, based on the data rate */
    for (i = VCP2_RATE_1_4; i > rate; i--) {
        polynomes[i - 1] = 0;
    }
    /* the polynome sent to the coprocessor has always the most
       significant bit masked */
    mask = 0x00FF;

    /* Polynomes coefficients */
    poly0 = polynomes[0] & mask;
    poly1 = polynomes[1] & mask;
    poly2 = polynomes[2] & mask;
    poly3 = polynomes[3] & mask;


    /* Calculation of reliability length */
    /* Identify Fmax for a given constraint length and decision type */
    if (decision == VCP2_DECISION_HARD) {
        if (constLen == 9) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_HD_CONST9;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST9;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST9;
        }                       /* end if constLen == 9 */
        if (constLen == 8) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_HD_CONST8;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST8;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST8;
        }                       /* end if constLen == 8 */
        if (constLen == 7) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_HD_CONST7;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST7;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST7;
        }                       /* end if constLen == 7 */
        if (constLen == 6) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_HD_CONST6;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST6;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST6;
        }                       /* end if constLen == 6 */
        if (constLen == 5) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_HD_CONST5;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_HD_CONST5;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_HD_CONST5;
        }                       /* end if constLen == 5 */
    }                           /* end if hard decision */
    else {                      /* if soft decision */
        if (constLen == 9) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_SD_CONST9;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST9;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST9;
        }                       /* end if constLen == 9 */
        if (constLen == 8) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_SD_CONST8;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST8;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST8;
        }                       /* end if constLen == 8 */
        if (constLen == 7) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_SD_CONST7;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST7;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST7;
        }                       /* end if constLen == 7 */
        if (constLen == 6) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_SD_CONST6;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST6;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST6;
        }                       /* end if constLen == 6 */
        if (constLen == 5) {
            fMax = VCP2_MAX_FRAME_SIZE_FOR_SD_CONST5;
            rcMax = VCP2_MAX_RELLEN_CONV_DIST_FOR_SD_CONST5;
            multiple = VCP2_TRL_STAGES_IN_2_PASSES_FOR_SD_CONST5;
        }                       /* end if constLen == 5 */
    }                           /* end if soft decision */

    /* If mixed or convergent traceback mode */
    if ((tbConvrgMode == TRUE) || (frameLen > fMax)) {
        if (perf == VCP2_SPEED_MOST_CRITICAL) {  /* Speed most critical */
            convMultiplier = 3;                 /* convMultiplier
			                                       values  - as
			                                       specified in the
			                                       'TPC2_VCP2_API_
			                                       Requirements_v1.4'
			                                       spread sheet */
        }
        else if (perf == VCP2_PERF_CRITICAL) {   /* Performance critical */
            if (constLen == 9) {
                convMultiplier = 6;
            }
            else {
                convMultiplier = 9;
            }

        }
        else if (perf == VCP2_PERF_MOST_CRITICAL) {
	              /* Performance most critical */
            if (constLen == 9) {
                convMultiplier = 6;
            }
            else if (constLen == 8) {
                convMultiplier = 12;
            }
            else {
                convMultiplier = 18;
            }
        }
        else {                  /* for speed critical and default case */

            if (constLen == 9) {
                convMultiplier = 3;
            }
            else {
                convMultiplier = 6;
            }
        }
		/* Calculation of Reliability length and Convergence distance */
        convDist = convMultiplier * (constLen - 1);
        nsw = VCP2_normalCeil (frameLen, rcMax - convDist);
        relLen = multiple * VCP2_normalCeil (frameLen, nsw * multiple);

        if ((decision == VCP2_DECISION_SOFT) & (constLen < 7)) {
            while (relLen > VCP2_REL_LEN_LIMIT_FOR_A_SILDING_WINDOW) {
                nsw++;
                relLen = multiple * VCP2_normalCeil (frameLen, nsw * multiple);
            }
        }
    }                          /* end if mixed or convergent traceback modes */


    /* Trace back mode */
    if (tbConvrgMode == TRUE) {
        traceBack = VCP2_TRACEBACK_CONVERGENT;
    }
    else {
        if (frameLen > fMax)
            traceBack = VCP2_TRACEBACK_MIXED;
        else
            traceBack = VCP2_TRACEBACK_TAILED;
    }


    /* Calculation of branch metric buffer length */
    /* Number of branch metrics per trellis stage */
    if (rate == VCP2_RATE_1_4) {
        bmNum = VCP2_BM_PER_TRL_FOR_RATE_1_4;
        bmBuffLen = VCP2_SYMX_FOR_128_BYTE_PER_RXEVENT_RATE_1_4;
    }
    else if (rate == VCP2_RATE_1_3) {
        bmNum = VCP2_BM_PER_TRL_FOR_RATE_1_3;
        bmBuffLen = VCP2_SYMX_FOR_128_BYTE_PER_RXEVENT_RATE_1_3;
    }
    else if (rate == VCP2_RATE_1_2) {
        bmNum = VCP2_BM_PER_TRL_FOR_RATE_1_2;
        bmBuffLen = VCP2_SYMX_FOR_128_BYTE_PER_RXEVENT_RATE_1_2;
    }

    /* Maximum number of branch metrics */
    if (traceBack == VCP2_TRACEBACK_CONVERGENT)
        bmCnt = bmNum * (frameLen + convDist);
    else
        bmCnt = bmNum * (frameLen + constLen - 1);
    /* Number of frame transfers */
    numBmFrames = VCP2_normalCeil (bmCnt, VCP2_BYTE_COUNT_PER_RXEVENT);


    /* Calculation of Decision buffer length */
    if (decision == VCP2_DECISION_HARD) {
        if (frameLen > VCP2_MAX_HD_IN_OUTFIFO)
            decBuffLen = (VCP2_OUTFIFO_WORDS) - 1;
        else {
			decBuffLen = VCP2_normalCeil (frameLen, VCP2_HD_PER_OUTFIFO_WORD)
			               - 1;
            numDecFrames = 1;  /* Not being used here */
        }
    }
    else {
        if (frameLen > VCP2_MAX_SD_IN_OUTFIFO)
            decBuffLen = (VCP2_OUTFIFO_WORDS) - 1;
        else {
			decBuffLen = VCP2_normalCeil (frameLen, VCP2_SD_PER_OUTFIFO_WORD)
			   - 1;
            numDecFrames = 1;  /* Not being used here */
        }
    }

    pConfigParams->rate = rate;
    pConfigParams->constLen = constLen;
    pConfigParams->poly0 = poly0;
    pConfigParams->poly1 = poly1;
    pConfigParams->poly2 = poly2;
    pConfigParams->poly3 = poly3;
    pConfigParams->yamTh = yamTh;
    pConfigParams->frameLen = frameLen;
    pConfigParams->relLen = relLen;
    pConfigParams->convDist = convDist;
    pConfigParams->traceBackEn = tailBitEnable;
    pConfigParams->traceBackIndex = traceBackIndex;
    pConfigParams->outOrder = outOrder;
    pConfigParams->maxSm = maxSm;
    pConfigParams->minSm = minSm;
    pConfigParams->stateNum = stateNum;
    pConfigParams->bmBuffLen = bmBuffLen;
    pConfigParams->decBuffLen = decBuffLen;
    pConfigParams->traceBack = traceBack;
    pConfigParams->readFlag = readFlag;
    pConfigParams->decision = decision;
    pConfigParams->numBmFrames = numBmFrames;
    pConfigParams->numDecFrames = numDecFrames;

}

 /** ==========================================================================
 *   @n@b VCP2_genIc
 *
 *   @b Description
 *   @n This function generates the required input configuration registers' 
 *      values needed to program the VCP based on the parameters provided by
 *      VCP2_Params object values.
 *
 *   @b Arguments
     @verbatim
            pConfigParams   Pointer to channel parameters structure.
            
            pConfigIc       Pointer to input configuration structure.
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b>
 *   @n  The members of the channel parameter structure should
 *       be populated by calling the function 'VCP2_genParams()'
 *       before calling this function.
 *
 *   <b> Post Condition </b>
 *   @n  None 
 *
 *   @b  Modifies
 *   @n  Input VCP2_ConfigIc structure instance pointed by pConfigIc.  
 *
 *   @b Example
 *   @verbatim
            VCP2_Params      vcpParam;
            VCP2_BaseParams  vcpBaseParam;
            ...
            vcpBaseParam.rate           =   VCP2_RATE_1_4;
            vcpBaseParam.constLen       =   5;
            vcpBaseParam.frameLen       =   2042;
            vcpBaseParam.yamTh          =   50;
            vcpBaseParam.stateNum       =   2048;
            vcpBaseParam.tbConvrgMode   =   FALSE;
            vcpBaseParam.decision       =   VCP2_DECISION_HARD;
            vcpBaseParam.readFlag       =   VCP2_OUTF_YES;
            vcpBaseParam.tailBitEnable  =   FALSE;
            vcpBaseParam.traceBackIndex =   0x0;
            vcpBaseParam.outOrder       =   VCP2_OUTORDER_0_31;
            vcpBaseParam.perf           =   VCP2_SPEED_CRITICAL;
            ... 
            VCP2_genParams (&vcpBaseParam, &vcpParam);
  
            VCP2_genIc (&vcpParam, &vcpConfig);
     @endverbatim
 * ============================================================================
 */
#pragma CODE_SECTION (VCP2_genIc, ".text:csl_section:vcp2");
void
VCP2_genIc (
	VCP2_Params * restrict pConfigParams,
    VCP2_ConfigIc * restrict pConfigIc
)
{
    Uint8 poly0 = pConfigParams->poly0;
    Uint8 poly1 = pConfigParams->poly1;
    Uint8 poly2 = pConfigParams->poly2;
    Uint8 poly3 = pConfigParams->poly3;
    Uint16 yamTh = pConfigParams->yamTh;
    Uint16 frameLen = pConfigParams->frameLen;
    Uint16 relLen = pConfigParams->relLen;
    Uint16 convDist = pConfigParams->convDist;
    Uint16 traceBackIndex = pConfigParams->traceBackIndex;
    Bool traceBackEn = pConfigParams->traceBackEn;
    Uint8 outOrder = pConfigParams->outOrder;
    Int16 minSm = pConfigParams->minSm;
    Int16 maxSm = pConfigParams->maxSm;
    Uint8 stateNum = pConfigParams->stateNum;
    Uint8 bmBuffLen = pConfigParams->bmBuffLen;
    Uint8 decBuffLen = pConfigParams->decBuffLen;
    Uint8 traceBack = pConfigParams->traceBack;
    Uint8 readFlag = pConfigParams->readFlag;
    Uint8 decision = pConfigParams->decision;
    Uint32 ic0 = 0;
    Uint32 ic1 = 0;
    Uint32 ic2 = 0;
    Uint32 ic3 = 0;
    Uint32 ic4 = 0;
    Uint32 ic5 = 0;

    /* VCPIC0 parameters */
    ic0 = CSL_FMK (VCP2_VCPIC0_POLY0, poly0) |
        CSL_FMK (VCP2_VCPIC0_POLY1, poly1) |
        CSL_FMK (VCP2_VCPIC0_POLY2, poly2) |
        CSL_FMK (VCP2_VCPIC0_POLY3, poly3);

    /* VCPIC1 parameters */
    if (yamTh) {
        CSL_FINST (ic1, VCP2_VCPIC1_YAMEN, ENABLE);
        CSL_FINS (ic1, VCP2_VCPIC1_YAMT, yamTh);
    }

    /* VCPIC2 parameters */
    ic2 = CSL_FMK (VCP2_VCPIC2_FL, frameLen) |
        CSL_FMK (VCP2_VCPIC2_R, relLen);

    /* VCPIC3 parameters */
    ic3 = CSL_FMK (VCP2_VCPIC3_C, convDist) |
        CSL_FMK (VCP2_VCPIC3_ITBI, traceBackIndex) |
        CSL_FMK (VCP2_VCPIC3_ITBEN, traceBackEn) |
        CSL_FMK (VCP2_VCPIC3_OUT_ORDER, outOrder);

    /* VCPIC4 parameters */
    ic4 = CSL_FMK (VCP2_VCPIC4_IMAXS, maxSm) |
        CSL_FMK (VCP2_VCPIC4_IMINS, minSm);

    /* VCPIC5 parameters */
    ic5 = CSL_FMK (VCP2_VCPIC5_IMAXI, stateNum) |
        CSL_FMK (VCP2_VCPIC5_SYMX, bmBuffLen) |
        CSL_FMK (VCP2_VCPIC5_SYMR, decBuffLen) |
        CSL_FMK (VCP2_VCPIC5_TB, traceBack) |
        CSL_FMK (VCP2_VCPIC5_OUTF, readFlag) |
        CSL_FMK (VCP2_VCPIC5_SDHD, decision);

    pConfigIc->ic0 = ic0;
    pConfigIc->ic1 = ic1;
    pConfigIc->ic2 = ic2;
    pConfigIc->ic3 = ic3;
    pConfigIc->ic4 = ic4;
    pConfigIc->ic5 = ic5;

}
