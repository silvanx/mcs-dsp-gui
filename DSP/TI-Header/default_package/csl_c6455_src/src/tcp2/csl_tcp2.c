/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 *   @file  csl_tcp2.c
 *
 *   @path  $(CSLPATH)\src\tcp2
 *
 *   @desc  File for functional layer of CSL API of TCP2
 *
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  15-Mar-2005  sd File Created.
 *  03-Aug-2005  sd Modifications for the requirements change.
 *  15-Sep-2005  sd Changed TCP to TCP2 in all the names
 *  07-Oct-2005  sd Changes during testing
 * =============================================================================
 */

#include <csl_tcp2.h>
#include <csl_tcp2Aux.h>

/* defines */

/* TCP number of extrinsic factors */
#define NUM_EXTRINSIC_FACTORS 	16

/* TCP data width */
#define DATA_WIDTH           	 6

/* forward declarations */
static void TCP2_calcSubBlocks (TCP2_Params *configParms);

/** ============================================================================
 *   @n@b TCP2_setParams 
 *
 *   @b Description
 *   @n This function sets up the TCP2 input configuration parameters in the
 *		TCP2_ConfigIc structure. The configuration values are passed in the 
 *		configParms input argument.
 *
 *   @b Arguments
     @verbatim
            configParms     Pointer to the structure holding the TCP 
                            configuration parameters.
                            
            configIc        Pointer to the TCP2_ConfigIc structure to be filled.

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
 *   @n The configIc argument passed.   
 *
 *   @b Example
 *   @verbatim 
		extern TCP2_Params *configParms;
		TCP2_ConfigIc *configIc;
		...
		TCP2_setParams(configParms, configIc);
     @endverbatim
 * ===========================================================================
 */
void TCP2_setParams (
 	TCP2_Params 		*restrict configParms,
    TCP2_ConfigIc 	*restrict configIc
) 
{
	/* IC0 parameters */
	TCP2_Mode mode          = configParms->mode;
	TCP2_NumSW  numSw       = configParms->numSlideWin;
	TCP2_Rate rate          = configParms->rate; 
	Uint32 intFlag         = configParms->intFlag;
	Uint32 outParmFlag     = configParms->outParmFlag;
	Uint32 frameLen        = configParms->frameLen;
	
	/* IC1 parameters */
	Uint32 relLen          = configParms->relLen;

	/* IC2 parameters */
	Uint32 prologSize      = configParms->prologSize;
	Uint32 numSubBlock     = configParms->numSubBlock;
	Uint32 maxIter         = configParms->maxIter;
	Uint32 snr             = configParms->snr;

	/* IC3 parameters */
	Bool maxStarEn		    = configParms->maxStarEn;
	Bool prologRedEn		= configParms->prologRedEn;
	Uint8 minIter			= configParms->minIter;
	TCP2_InputSign inputSign = configParms->inputSign;
	TCP2_OutputOrder  outputOrder = configParms->outputOrder;

	/* IC4 parameters */
	Uint8 numCrcPass 		= configParms->numCrcPass;
	Uint8 crcLen			= configParms->crcLen;

	/* IC5 parameters */
	Uint32 crcPoly			= configParms->crcPoly;	
	

	Uint32 ic0=0, ic1=0, ic2=0, ic3=0, ic4=0, ic5=0, 
					ic12=0, ic13=0, ic14=0, ic15=0;

	Uint32 gie;

	gie =  _disable_interrupts ();

	/* set the values for the TCPIC0 register */
	CSL_FINS (ic0, TCP2_TCPIC0_FL, 		frameLen);
	CSL_FINS (ic0, TCP2_TCPIC0_NUMSW, 	numSw);
	CSL_FINS (ic0, TCP2_TCPIC0_OUTF, 	outParmFlag);
	CSL_FINS (ic0, TCP2_TCPIC0_INTER, 	intFlag);
	CSL_FINS (ic0, TCP2_TCPIC0_RATE, 	rate);
	CSL_FINS (ic0, TCP2_TCPIC0_OPMOD,	mode);

	/* set the values for the TCPIC1 register */
	CSL_FINS (ic1, TCP2_TCPIC1_R, 		relLen);

	/* set the values for the TCPIC2 register */
	CSL_FINS (ic2, TCP2_TCPIC2_SNR, 	snr);  	
	CSL_FINS (ic2, TCP2_TCPIC2_MAXIT, 	maxIter);  	
	CSL_FINS (ic2, TCP2_TCPIC2_NSB, 	numSubBlock);  	
	CSL_FINS (ic2, TCP2_TCPIC2_P, 		prologSize);

	/* set the values for the TCPIC3 register */
	CSL_FINS (ic3, TCP2_TCPIC3_OUTORDER, 	outputOrder);  	
	CSL_FINS (ic3, TCP2_TCPIC3_INPUTSIGN, 	inputSign);  	
	CSL_FINS (ic3, TCP2_TCPIC3_MINITER,	 	minIter);  	
	CSL_FINS (ic3, TCP2_TCPIC3_EPRORED, 	prologRedEn);  	
	CSL_FINS (ic3, TCP2_TCPIC3_EMAXSTR, 	maxStarEn);  	

	/* set the values for the TCPIC4 register */
	CSL_FINS (ic4, TCP2_TCPIC4_CRCITERPASS, numCrcPass);  	
	CSL_FINS (ic4, TCP2_TCPIC4_CRCLEN, 		crcLen);  	

	/* set the values for the TCPIC5 register */
	CSL_FINS (ic5, TCP2_TCPIC5_CRCPOLY,		crcPoly);

	/* set the values for TCPIC12 to TCPIC15 */
	
	/* Form the value for the register TCPIC12 */
	ic12 = TCP2_setExtScaling (configParms->extrScaling [0], 
						configParms->extrScaling [1],
						configParms->extrScaling [2],
						configParms->extrScaling [3]);

	/* Form the value for the register TCPIC13 */
	ic13  = TCP2_setExtScaling (configParms->extrScaling [4], 
						configParms->extrScaling [5],
						configParms->extrScaling [6],
						configParms->extrScaling [7]);

	/* Form the value for the register TCPIC14 */
	ic14 = TCP2_setExtScaling (configParms->extrScaling [8], 
						configParms->extrScaling [9],
						configParms->extrScaling [10],
						configParms->extrScaling [11]);

	/* Form the value for the register TCPIC15 */
	ic15 = TCP2_setExtScaling (configParms->extrScaling [12], 
						configParms->extrScaling [13],
						configParms->extrScaling [14],
						configParms->extrScaling [15]);

	/* Assign the configIc values */
	configIc->ic0 = ic0;
	configIc->ic1 = ic1;
	configIc->ic2 = ic2;
	configIc->ic3 = ic3;
	configIc->ic4 = ic4;
	configIc->ic5 = ic5;

	configIc->ic12 = ic12;
	configIc->ic13 = ic13;
	configIc->ic14 = ic14;
	configIc->ic15 = ic15;

	_restore_interrupts (gie); 

    return;
} /* end TCP2_setParams */

/** ============================================================================
 *   @n@b TCP2_tailConfig 
 *
 *   @b Description
 *   @n This function generates the input control values IC6-IC11 based on the 
 *		processing to be performed by the TCP. These values consist of the tail 
 *  	data following the systematics and parities data. This function 
 *		calls specific tail generation functions depending on the
 *		standard followed.
 *
 *   @b Arguments
     @verbatim
            standard        3G standard to be decoded.

            mode            TCP processing mode (SA or SP)

            map             TCP shared processing MAP 

            rate            Code rate of the TCP

            tailData        Pointer to the tail data

            configIc        Pointer to the TCP_ConfigIc structure to be filled.

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
 *   @n The configIc argument passed.   
 *
 *   @b Example
 *   @verbatim
		extern TCP2_Params *configParms;
		TCP2_ConfigIc *configIc;
		TCP2_UserData *xabData = &userData[frameLen];		
		
		...
		TCP2_tailConfig (configParms->standard, configParms->mode, 
                configParms->map, configParms->rate,
					userData, configIc);
     @endverbatim
 * ===========================================================================
 */
void TCP2_tailConfig (
	TCP2_Standard 	standard,
    TCP2_Mode		mode,
    TCP2_Map 		map,
    TCP2_Rate 		rate,
    TCP2_TailData 	*restrict tailData,
    TCP2_ConfigIc 	*restrict configIc
) 
{
    /* Call the specific tail generation function */
	if (standard == TCP2_STANDARD_3GPP) 
		TCP2_tailConfig3GPP ( mode, map, rate, tailData, configIc);
	else 
		TCP2_tailConfigIs2000 (mode, map, rate, tailData, configIc);
 
    return;
} /* end TCP2_tailConfig() */


/** ============================================================================
 *   @n@b TCP2_genIc 
 *
 *   @b Description
 *   @n This function sets up the TCP2 input configuration parameters in the
 *		TCP2_ConfigIc structure. The configuration values are passed in the 
 *		configParms input argument.
 *
 *   @b Arguments
     @verbatim
            configParms     Pointer to the structure holding the TCP 
                            configuration parameters.
	
            tailData        Tail data

            configIc        Pointer to the TCP2_ConfigIc structure to be filled.

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
 *   @n The configIc argument passed.   
 *
 *   @b Example
 *   @verbatim
        extern TCP2_UserData *userData;
        
	    TCP2_BaseParams	configBase;
	    TCP2_Params      configParams;
        TCP2_TailData    *xabData;
    	Uint32          frameLen = 40;

        xabData = &userData [frameLen];
        
        // assign the configuration parameters 
	    configBase.frameLen		= frameLen;
	    configBase.inputSign	= TCP2_INPUT_SIGN_POSITIVE;
	    configBase.intFlag		= 1;
	    configBase.maxIter		= 8;
	    configBase.maxStarEn	= TRUE;
	    configBase.standard		= TCP2_STANDARD_3GPP;
	    configBase.crcLen		= 0;
	    configBase.crcPoly		= 0;
	    configBase.minIter		= 1;
	    configBase.numCrcPass	= 1;
	    configBase.outParmFlag	= 0;
	    configBase.outputOrder	= TCP2_OUT_ORDER_0_31;
	    configBase.prologRedEn	= FALSE;
	    configBase.prologSize	= 24;
	    configBase.rate         = TCP2_RATE_1_3;
	    configBase.snr          = 0;

	    for (cnt = 0; cnt < 16; cnt++)
		    configBase.extrScaling [cnt] = 32;

	    // setup the TCP configuration registers parameters 
	    TCP2_genParams (&configBase, &configParams);

	    // generate the configuration register values 
	    TCP2_genIc (&configParams, xabData, &configIc); 

     @endverbatim
 * ===========================================================================
 */
void TCP2_genIc (
    TCP2_Params      *restrict configParms,
    TCP2_TailData    *restrict tailData,
    TCP2_ConfigIc    *restrict configIc
) 
{

	TCP2_Standard standard = configParms->standard;
	TCP2_Rate rate         = configParms->rate;
	TCP2_Mode mode		  = configParms->mode;
	TCP2_Map map		      = configParms->map;

	/* configuration parameters configuration */
	TCP2_setParams (configParms, configIc);

	/* TCP tail parameter configuration */
	TCP2_tailConfig(standard, mode, map, rate, tailData, configIc);

    return;
} /* end TCP2_genIc */


/** ============================================================================
 *   @n@b TCP2_genParams  
 *
 *   @b Description
 *   @n This function copies the basic parameters, to the configParams 
 *		parameters structure.
 *
 *   @b Arguments
     @verbatim
            configBase      Pointer to the TCP2_BaseParams structure 
            
            configParams    Pointer to the TCP configuration parameters 
                            structure.

     @endverbatim
 *
 *   <b> Return Value </b>  Uint32
 *   @n                     The number of sub frames for shared processing mode                       
 *
 *   <b> Pre Condition </b>
 *   @n  configBase is populated with all the configurtaion parameters
 *
 *   <b> Post Condition </b>
 *   @n  None 
 *
 *   @b Modifies
 *   @n The configParams argument passed.   
 *
 *   @b Example
 *   @verbatim
        extern TCP2_UserData *userData;
        
	    TCP2_BaseParams	configBase;
	    TCP2_Params      configParams;
        TCP2_TailData    *xabData;
    	Uint32          frameLen = 40;

        xabData = &userData [frameLen];
        
        // assign the configuration parameters 
	    configBase.frameLen		= frameLen;
	    configBase.inputSign	= TCP2_INPUT_SIGN_POSITIVE;
	    configBase.intFlag		= 1;
	    configBase.maxIter		= 8;
	    configBase.maxStarEn	= TRUE;
	    configBase.standard		= TCP2_STANDARD_3GPP;
	    configBase.crcLen		= 0;
	    configBase.crcPoly		= 0;
	    configBase.minIter		= 1;
	    configBase.numCrcPass	= 1;
	    configBase.outParmFlag	= 0;
	    configBase.outputOrder	= TCP2_OUT_ORDER_0_31;
	    configBase.prologRedEn	= FALSE;
	    configBase.prologSize	= 24;
	    configBase.rate         = TCP2_RATE_1_3;
	    configBase.snr          = 0;

	    for (cnt = 0; cnt < 16; cnt++)
		    configBase.extrScaling [cnt] = 32;

	    // setup the TCP configuration registers parameters 
	    TCP2_genParams (&configBase, &configParams);

     @endverbatim
 * ===========================================================================
 */
Uint32 TCP2_genParams (
    TCP2_BaseParams  *restrict configBase,
    TCP2_Params      *restrict configParams
) 
{
	Uint8 cnt;
	Uint32 numSubFrames = 0;
	Uint32 frameLen = configBase->frameLen;

    /* Assign the configuration parameters */
	configParams->standard    = configBase->standard;
	configParams->rate        = configBase->rate;
	configParams->intFlag     = configBase->intFlag;
	configParams->outParmFlag = configBase->outParmFlag;
	configParams->prologSize  = configBase->prologSize;
	configParams->maxIter     = configBase->maxIter;
	configParams->snr         = configBase->snr;
	configParams->maxStarEn	  = configBase->maxStarEn;
	configParams->prologRedEn = configBase->prologRedEn;
	configParams->minIter	  = configBase->minIter;
	configParams->inputSign	  = configBase->inputSign;	
	configParams->outputOrder = configBase->outputOrder;	
	configParams->numCrcPass	 = configBase->numCrcPass;	
	configParams->crcLen		 = configBase->crcLen;
	configParams->crcPoly	     = configBase->crcPoly;
	configParams->map		     = configBase->map;

	for (cnt = 0; cnt < NUM_EXTRINSIC_FACTORS; cnt++)
		configParams->extrScaling [cnt] = configBase->extrScaling [cnt];

	/* calculate the sub blocks */
    configParams->frameLen   = frameLen;

    if (frameLen <= TCP2_FLEN_MAX) {             
        /* Configure for Standalone processing */
        
	    /* to assign the frame length and mode */
        configParams->mode 		= TCP2_MODE_SA;

        /* Calculate the sub blocks, reliabilty length and 
         * num of sliding windows 
         */
		TCP2_calcSubBlocksSA (configParams);
	}
	else { /* Configure for Shared processing */
        /*for shared processing assign the paramemters for the second 
         * configuration structure 
         */
        TCP2_Params *configParms2 = &configParams [1];

        /* Assign the configuration parameters */
        configParms2->standard    = configBase->standard;
        configParms2->rate        = configBase->rate;
        configParms2->intFlag     = configBase->intFlag;
        configParms2->outParmFlag = configBase->outParmFlag;
        configParms2->prologSize  = configBase->prologSize;
        configParms2->maxIter     = configBase->maxIter;
        configParms2->snr         = configBase->snr;
        configParms2->maxStarEn	  = configBase->maxStarEn;
        configParms2->prologRedEn = configBase->prologRedEn;
        configParms2->minIter	  = configBase->minIter;
        configParms2->inputSign	  = configBase->inputSign;	
        configParms2->outputOrder = configBase->outputOrder;	
        configParms2->numCrcPass  = configBase->numCrcPass;	
        configParms2->crcLen	  = configBase->crcLen;
        configParms2->crcPoly	  = configBase->crcPoly;
        configParms2->map		  = configBase->map;

        for (cnt = 0; cnt < NUM_EXTRINSIC_FACTORS; cnt++)
            configParms2->extrScaling [cnt] = configBase->extrScaling [cnt];

        /* Calculate the number of sub frames, sub blocks, reliabilty length
         * and num of sliding windows 
         */
        numSubFrames = TCP2_calcSubBlocksSP (configParams);
	}

	return numSubFrames;
} /* end TCP2_genParams */

/** ============================================================================
 *   @n@b TCP2_calcSubBlocksSA 
 *
 *   @b Description
 *   @n This function calculates the number of sub blocks for the TCP 
 *		standalone processing. The reliability length is also calculated and the 
 *		configParms structure is populated.
 *
 *   @b Arguments
     @verbatim
            configParms     Pointer to the structure holding the TCP 
                            configuration parameters.

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
 *   @n The configParms argument passed.   
 *
 *   @b Example
 *   @verbatim
		extern TCP2_Params *configParms;
		...
		TCP2_calcSubBlocksSA (configParms);
     @endverbatim
 * ===========================================================================
 */
void TCP2_calcSubBlocksSA (
	TCP2_Params *configParms 
)
{
    /* calculate the sub blocks and other parameters */
	TCP2_calcSubBlocks (configParms);

    return;
} /* end TCP2_calcSubBlocksSA () */

/** ============================================================================
 *   @n@b TCP2_calcSubBlocksSP 
 *
 *   @b Description
 *   @n This function calculates the number of sub blocks for the TCP 
 *		shared processing. The reliability length is also calculated and the 
 *		configParms structure is populated.
 *
 *   @b Arguments
     @verbatim
            configParms     Pointer to the structure holding the TCP 
                            configuration parameters.

     @endverbatim
 *
 *   <b> Return Value </b>  Uint32
 *   @n                     Number of sub frames the frame is divided into
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None 
 *
 *   @b Modifies
 *   @n The configParms argument passed.   
 *
 *   @b Example
 *   @verbatim
		extern TCP2_Params *configParms;
		...
		TCP2_calcSubBlocksSP (configParms);
     @endverbatim
 * ===========================================================================
 */
Uint32 TCP2_calcSubBlocksSP (
	TCP2_Params *configParms 
)
{
	Uint16 numSubFrame;
	Uint16 subFrameLen;
	Uint16 subFrameLenLast;

	TCP2_Params *configParams1 = &configParms [0];
	TCP2_Params *configParams2 = &configParms [1];

	Uint16 frameLen   = configParms->frameLen;

	/* calculate the number of sub frames and their lengths */
    numSubFrame = TCP2_normalCeil (frameLen, TCP2_SUB_FRAME_SIZE_MAX);
	subFrameLen = (TCP2_normalCeil (frameLen, (numSubFrame * 256))) * 256;
	
	/* calculate the last sub frame length */
	while (frameLen > TCP2_SUB_FRAME_SIZE_MAX)
		frameLen = frameLen - subFrameLen;

	if (frameLen > 128)				
		subFrameLenLast = frameLen;
	else {
		numSubFrame--;
		subFrameLenLast = frameLen + TCP2_SUB_FRAME_SIZE_MAX;	
	}

	/* Assign the config parameters for the first and the middle subframes */
    configParams1->mode 		= TCP2_FIRST_SF;
	configParams1->frameLen		= subFrameLen;
	TCP2_calcSubBlocks (configParams1);

	/* Assign the config parameters for the first and the middle subframes */
    configParams2->mode 		= TCP2_LAST_SF;
	configParams2->frameLen		= subFrameLenLast;
	TCP2_calcSubBlocks (configParams2);

	return numSubFrame;
} /* end TCP2_calcSubBlocksSP () */

/* ============================================================================
 *   @n@b TCP2_calcSubBlocks 
 *
 *   @b Description
 *   @n This function calculates the number of sub blocks for the TCP 
 *		processing. The reliability length is also calculated and the 
 *		configParms structure is populated.
 *
 *   @b Arguments
     @verbatim
            configParms     Pointer to the structure holding the TCP 
                            configuration parameters.

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
 *   @n The configParms argument passed.   
 *
 *   @b Example
 *   @verbatim
		extern TCP2_Params *configParms;
		...
		TCP2_calcSubBlocks (configParms);
     @endverbatim
 * ===========================================================================
 */
void TCP2_calcSubBlocks (
	TCP2_Params *configParms 
)
{
	Uint16 frameLen   = configParms->frameLen;
	Uint16 winSize;
	Uint16 numSlidingWindow;
	Uint16 relLen;
	Uint16 numSubBlock = 1;
	Uint16 relLenMax = TCP2_RLEN_MAX;

    /*  calculate the number of sliding windows */
    if (frameLen <= 128) { 
    	numSlidingWindow = 1;
		relLen = frameLen;
	}
    else 
    	numSlidingWindow = 2;
    
    /* Calculate the reliability length and number of sub blocks */
    if (2 == numSlidingWindow) {
    	winSize 	= TCP2_normalCeil (frameLen, numSlidingWindow);	   	
        do {
            numSubBlock = TCP2_normalCeil (winSize, relLenMax);
	    	relLen 		= winSize / numSubBlock;
			
			if ((relLen * numSubBlock) < winSize)
				relLen++;

			relLenMax--;
		} while (((numSubBlock * relLen * numSlidingWindow) - frameLen) >= 
															(relLen - (configParms->prologSize)));
    }
    
    
    configParms->relLen          = relLen - 1;
    configParms->numSubBlock     = numSubBlock;
	configParms->numSlideWin	 = numSlidingWindow - 1;

    return;
} /* end TCP2_calcSubBlocks () */

/** ============================================================================
 *   @n@b TCP2_tailConfig3GPP 
 *
 *   @b Description
 *   @n This function generates the input control values IC6-IC11 for 3GPP
 *		channels. These values consist of the tail data following the 
 * 		systematics and parities data. This function is called from the generic 
 *		TCP2_tailConfig function.
 *
 *   @b Arguments
     @verbatim
            mode        TCP processing mode (SA or SP)

            map         TCP shared processing MAP 

            rate        TCP data code rate

            tailData    Pointer to the tail data

            configIc    Pointer to the IC values structure

     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The configIc structure is assigned the tail configuration values 
 *		 based on the tailData. 
 *
 *   @b Modifies
 *   @n The configIc argument passed.   
 *
 *   @b Example
 *   @verbatim
		extern TCP2_Params *configParms;
		TCP2_ConfigIc *configIc;
		TCP2_UserData *xabData = &userData[frameLen];		
		
		...
		TCP2_tailConfig3GPP (configParms->mode, configParms->map,
					configParms->rate,
					userData, configIc);

     @endverbatim
 * ===========================================================================
 */
void TCP2_tailConfig3GPP (
		TCP2_Mode		mode,
		TCP2_Map 		map,
        TCP2_Rate        rate,
        TCP2_TailData    *restrict tailData,
        TCP2_ConfigIc    *restrict configIc
) 
{
	Uint32 tail1 = 0, tail2 = 0, tail3 = 0, tail4 = 0, tail5 = 0, tail6 = 0;

	Uint32 gie;

    if (TCP2_MODE_SA == mode) { /* set the tail bits for SA mode */
		switch (rate) {
			case TCP2_RATE_1_2:
			case TCP2_RATE_1_3:
			case TCP2_RATE_3_4: {
                /* tail1 = x10(2), x10(1), x10(0) */
			    /* tail2 = p10(2), p10(1), p10(0) */
			    /* tail3 =   0,   0,   0 */
			    /* tail4 = x20(2), x20(1), x20(0) */
			    /* tail5 = p20(2), p20(1), p20(0) */
			    /* tail6 =   0,   0,   0 */

			    tail1 = TCP2_makeTailArgs(tailData [4], tailData [2], 
                                                            tailData [0]);
			    tail2 = TCP2_makeTailArgs(tailData [5], tailData [3], 
                                                            tailData [1]);
			    tail3 = 0;
			    tail4 = TCP2_makeTailArgs(tailData [10], tailData [8], 
                                                            tailData [6]);
			    tail5 = TCP2_makeTailArgs(tailData [11], tailData [9], 
                                                            tailData [7]);
			    tail6 = 0;
				break;
            }
			case TCP2_RATE_1_4:
			case TCP2_RATE_1_5: {
                /* tail1 = x10(2), x10(1), x10(0) */
			    /* tail2 = p10(2), p10(1), p10(0) */
			    /* tail3 = p11(2), p11(1), p11(0) */
			    /* tail4 = x20(2), x20(1), x20(0) */
			    /* tail5 = p20(2), p20(1), p20(0) */
			    /* tail6 = p21(2), p21(1), p21(0) */

			    tail1 = TCP2_makeTailArgs(tailData [6], tailData [3], 
                                                                tailData [0]);
			    tail2 = TCP2_makeTailArgs(tailData [7], tailData [4], 
                                                                tailData [1]);
			    tail3 = TCP2_makeTailArgs(tailData [8], tailData [5], 
                                                                tailData [2]);
			    tail4 = TCP2_makeTailArgs(tailData [15], tailData [12], 
                                                                tailData [9]);
			    tail5 = TCP2_makeTailArgs(tailData [16], tailData [13], 
                                                                tailData [10]);
			    tail6 = TCP2_makeTailArgs(tailData [17], tailData [14], 
                                                                tailData [11]);
				break;
            }
			default:
				break;
		} /* end of switch */
	} /* end of if (TCP2_MODE_SA == mode) */

	if (TCP2_LAST_SF == mode) { /* set the tail bits for SP last sub frame */
		switch (rate) {
			case TCP2_RATE_1_2:
			case TCP2_RATE_1_3:
			case TCP2_RATE_3_4: {
                /* SP MAP1 - non interleaved tail bits */
				/* tail1 = x10(2), x10(1), x10(0) */
			    /* tail2 = p10(2), p10(1), p10(0) */
			    /* tail3 =   0,   0,   0 */
				/* SP MAP2 - interleaved tail bits */
			    /* tail1 = x20(2), x20(1), x20(0) */
			    /* tail2 = p20(2), p20(1), p20(0) */
			    /* tail3 =   0,   0,   0 */
				if (TCP2_MAP_MAP1 == map) {
				    tail1 = TCP2_makeTailArgs(tailData [4], tailData [2], 
				    										tailData [0]);
				    tail2 = TCP2_makeTailArgs(tailData [5], tailData [3], 
				    										tailData [1]);
				    tail3 = 0;
				} 
				else {
			    	tail1 = TCP2_makeTailArgs(tailData [10], tailData [8], 
			    											tailData [6]);
			    	tail2 = TCP2_makeTailArgs(tailData [11], tailData [9],
			    											tailData [7]);
			    	tail3 = 0;
				}

			    tail4 = 0;
			    tail5 = 0;
			    tail6 = 0;
				break;
            }
			case TCP2_RATE_1_4:
			case TCP2_RATE_1_5: {
                /* SP MAP1 - non interleaved tail bits */
				/* tail1 = x10(2), x10(1), x10(0) */
			    /* tail2 = p10(2), p10(1), p10(0) */
			    /* tail3 = p11(2), p11(1), p11(0) */
				/* SP MAP2 - interleaved tail bits */
			    /* tail1 = x20(2), x20(1), x20(0) */
			    /* tail2 = p20(2), p20(1), p20(0) */
			    /* tail3 = p21(2), p21(1), p21(0) */

				if (TCP2_MAP_MAP1 == map) {
				    tail1 = TCP2_makeTailArgs(tailData [6], tailData [3], 
                                                                tailData [0]);
				    tail2 = TCP2_makeTailArgs(tailData [7], tailData [4], 
                                                                tailData [1]);
				    tail3 = TCP2_makeTailArgs(tailData [8], tailData [5], 
                                                                tailData [2]);
				}
				else {
				    tail1 = TCP2_makeTailArgs(tailData [15], tailData [12], 
                                                                tailData [9]);
				    tail2 = TCP2_makeTailArgs(tailData [16], tailData [13], 
                                                                tailData [10]);
				    tail3 = TCP2_makeTailArgs(tailData [17], tailData [14], 
                                                                tailData [11]);
				}
			    tail4 = 0;
			    tail5 = 0;
			    tail6 = 0;
				break;
            }
			default:
				break;
		} /* end of switch */
	} /* end of if (TCP2_LAST_SF == mode) */

	gie =  _disable_interrupts ();
    
    /* Assign the tail data values */
    configIc->ic6  = tail1;
    configIc->ic7  = tail2;
    configIc->ic8  = tail3;
    configIc->ic9  = tail4;
    configIc->ic10 = tail5;
    configIc->ic11 = tail6;
    
	_restore_interrupts (gie); 

    return;

} /* end TCP2_tailConfig3GPP */

/** ============================================================================
 *   @n@b TCP2_tailConfigIs2000 
 *
 *   @b Description
 *   @n This function generates the input control values IC6-IC11 for IS2000
 *		channels. These values consist of the tail data following the 
 * 		systematics and parities data. This function is called from the generic 
 *		TCP2_tailConfig function.
 *
 *   @b Arguments
     @verbatim
			mode		TCP processing mode (SA or SP)

            map         TCP shared processing MAP 

			rate 		TCP data code rate

			tailData 	Pointer to the tail data

			configIc 	Pointer to the IC values structure

     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The configIc structure is assigned the tail configuration values 
 *		 based on the taildata. 
 *
 *   @b Modifies
 *   @n The configIc argument passed.   
 *
 *   @b Example
 *   @verbatim
		extern TCP2_Params *configParms;
		TCP2_ConfigIc *configIc;
		TCP2_UserData *xabData = &userData[frameLen];		
		
		...
		TCP2_tailConfigIs2000 (configParms->mode, configParms->map,
					configParms->rate,
					userData, configIc);

     @endverbatim
 * ===========================================================================
 */
void TCP2_tailConfigIs2000 (
		TCP2_Mode		mode,
		TCP2_Map 		map,
        TCP2_Rate        rate,
        TCP2_TailData    *restrict tailData,
        TCP2_ConfigIc    *restrict configIc
) 
{
	Uint32 tail1 = 0, tail2 = 0, tail3 = 0, tail4 = 0, tail5 = 0, tail6 = 0;

	Uint32 gie;

	if (TCP2_MODE_SA == mode) { /* set the tail bits for SA mode */
		switch (rate) {
			case TCP2_RATE_1_2: {
                /* tail1 = x10(2), x10(1), x10(0) */
			    /* tail2 = p10 (2), p10 (1), p10 (0) */
			    /* tail3 =   0,   0,   0 */
			    /* tail4 = x20 (2), x20 (1), x20 (0) */
			    /* tail5 = p20 (2), p20 (1), p20 (0) */
			    /* tail6 =   0,   0,   0 */

			    tail1 = TCP2_makeTailArgs(tailData [4], tailData [2], 
                                                            tailData [0]);
			    tail2 = TCP2_makeTailArgs(tailData [5], tailData [3], 
                                                            tailData [1]);
			    tail3 = 0;
			    tail4 = TCP2_makeTailArgs(tailData [10], tailData [8], 
                                                            tailData [6]);
			    tail5 = TCP2_makeTailArgs(tailData [11], tailData [9], 
                                                            tailData [7]);
			    tail6 = 0;
				break;
            }
			case TCP2_RATE_3_4: {
            	/* tail1 = x10 (2), x10 (1), x10 (0) */
			    /* tail2 =   0,   0, p10 (0) */
			    /* tail3 =   0,   0,   0 */
			    /* tail4 = x20 (2), x20 (1), x20 (0) */
			    /* tail5 =   0,   0, p20 (0) */
			    /* tail6 =   0,   0,   0 */

			    tail1 = TCP2_makeTailArgs(tailData [4], tailData [2], 
                                                            tailData [0]);
			    tail2 = TCP2_makeTailArgs(  0,   0, tailData [1]);
			    tail3 = 0;
			    tail4 = TCP2_makeTailArgs(tailData [10], tailData [8], 
                                                            tailData [6]);
			    tail5 = TCP2_makeTailArgs(  0,   0, tailData [7]);
			    tail6 = 0;
				break;
            }
			case TCP2_RATE_1_3: {
                /* tail1 = (x10 + x10)/2, (x10 + x10)/2, (x10 + x10)/2 */
			    /* tail2 = p10, p10, p10 */
			    /* tail3 =   0,   0,   0 */
			    /* tail4 = (x20 + x20)/2, (x20 + x20)/2, (x20 + x20)/2 */
			    /* tail5 = p20, p20, p20 */
			    /* tail6 =   0,   0,   0 */

			    tail1 = TCP2_makeTailArgs((tailData [7] + tailData [6]) / 2, 
			    	(tailData [4] + tailData [3]) / 2, 
			    	(tailData [1] + tailData [0]) / 2);
			    tail2 = TCP2_makeTailArgs(tailData [8], tailData [5], 
                                                            tailData [2]);
			    tail3 = 0;
			    tail4 = TCP2_makeTailArgs((tailData [15] + tailData [16]) / 2, 
			    	(tailData [12] + tailData [13]) / 2, 
			    	(tailData [9] + tailData [10]) / 2);
			    tail5 = TCP2_makeTailArgs(tailData [17], tailData [14], 
                                                            tailData [11]);
			    tail6 = 0;
				break;
            }
			case TCP2_RATE_1_4: {
                /* tail1 = (x10 + x10)/2, (x10 + x10)/2, (x10 + x10)/2 */
			    /* tail2 = p10, p10, p10 */
			    /* tail3 = p11, p11, p11 */
			    /* tail4 = (x20 + x20)/2, (x20 + x20)/2, (x20 + x20)/2 */
			    /* tail5 = p20, p20, p20 */
			    /* tail6 = p21, p21, p21 */

			    tail1 = TCP2_makeTailArgs((tailData [8] + tailData [9]) / 2, 
			    						(tailData [4] + tailData [5]) / 2, 
			    						(tailData [0] + tailData [1]) / 2);
			    tail2 = TCP2_makeTailArgs(tailData [10], tailData [6], 
                                                                tailData [2]);
			    tail3 = TCP2_makeTailArgs(tailData [11], tailData [7], 
                                                                tailData [3]);
			    tail4 = TCP2_makeTailArgs((tailData [20] + tailData [21]) / 2, 
			    						(tailData [17] + tailData [16]) / 2, 
			    						(tailData [12] + tailData [13]) / 2);
			    tail5 = TCP2_makeTailArgs(tailData [22], tailData [18], 
                                                                tailData [14]);
			    tail6 = TCP2_makeTailArgs(tailData [23], tailData [19], 
                                                                tailData [15]);
				break;
            }
			case TCP2_RATE_1_5: {
                /* tail1 = (x10 + x10 + x10)/3, (x10 + x10 + x10)/3, 
                                                    (x10 + x10 + x10)/3 */
			    /* tail2 = p10, p10, p10 */
			    /* tail3 = p11, p11, p11 */
			    /* tail4 = (x20 + x20 + x20)/3, (x20 + x20 + x20)/3, 
                                                    (x20 + x20 + x20)/3 */
			    /* tail5 = p20, p20, p20 */
			    /* tail6 = p21, p21, p21 */

			    tail1 = TCP2_makeTailArgs(
                            (tailData [10] + tailData [11] + tailData [12]) / 3, 
			    			(tailData [5] + tailData [6] + tailData [7]) / 3, 
		    				(tailData [0] + tailData [1] + tailData [2]) / 3
                            );
			    tail2 = TCP2_makeTailArgs(tailData [13], tailData [8], 
                                                                tailData [3]);
			    tail3 = TCP2_makeTailArgs(tailData [14], tailData [9], 
                                                                tailData [4]);
			    tail4 = TCP2_makeTailArgs(
                        (tailData [25] + tailData [26] + tailData [27]) / 3, 
    					(tailData [20] + tailData [21] + tailData [22]) / 3, 
    					(tailData [15] + tailData [16] + tailData [17]) / 3
                        );
			    tail5 = TCP2_makeTailArgs(tailData [28], tailData [23], 
                                                                tailData [18]);
			    tail6 = TCP2_makeTailArgs(tailData [29], tailData [24], 
                                                                tailData [19]);
				break;
            }
			default:
				break;
		}
	} /* end of if (TCP2_MODE_SA == mode) */
    
	if (TCP2_LAST_SF == mode) { /* set the tail bits for SP last sub frame */
		switch (rate) {
			case TCP2_RATE_1_2: {
            	/* SP MAP1 non interleaved data */
				/* tail1 = x10(2), x10(1), x10(0) */
			    /* tail2 = p10 (2), p10 (1), p10 (0) */
			    /* tail3 =   0,   0,   0 */
				/* SP MAP2 interleaved data */
				/* tail1 = x20 (2), x20 (1), x20 (0) */
			    /* tail2 = p20 (2), p20 (1), p20 (0) */
			    /* tail3 =   0,   0,   0 */

				if (TCP2_MAP_MAP1 == map) {
				    tail1 = TCP2_makeTailArgs(tailData [4], tailData [2], 
                                                                tailData [0]);
				    tail2 = TCP2_makeTailArgs(tailData [5], tailData [3], 
                                                                tailData [1]);
				    tail3 = 0;
				}
				else {
				    tail1 = TCP2_makeTailArgs(tailData [10], tailData [8], 
                                                                tailData [6]);
				    tail2 = TCP2_makeTailArgs(tailData [11], tailData [9], 
                                                                tailData [7]);
				    tail3 = 0;
				}

				tail4 = 0;
				tail5 = 0;
				tail6 = 0;
				break;
            }
			case TCP2_RATE_3_4: {
            	/* SP MAP1 non interleaved data */
				/* tail1 = x10 (2), x10 (1), x10 (0) */
			    /* tail2 =   0,   0, p10 (0) */
			    /* tail3 =   0,   0,   0 */
				/* SP MAP2 interleaved data */
			    /* tail1 = x20 (2), x20 (1), x20 (0) */
			    /* tail2 =   0,   0, p20 (0) */
			    /* tail3 =   0,   0,   0 */

				if (TCP2_MAP_MAP1 == map) {
				    tail1 = TCP2_makeTailArgs(tailData [4], tailData [2], 
                                                                tailData [0]);
				    tail2 = TCP2_makeTailArgs(  0,   0, tailData [1]);
				    tail3 = 0;
				}
				else {
				    tail1 = TCP2_makeTailArgs(tailData [10], tailData [8], 
                                                                tailData [6]);
				    tail2 = TCP2_makeTailArgs(  0,   0, tailData [7]);
				    tail3 = 0;
				}
				tail4 = 0;
				tail5 = 0;
				tail6 = 0;
				break;
            }
			case TCP2_RATE_1_3: {
                /* SP MAP1 non interleaved data */
				/* tail1 = (x10 + x10)/2, (x10 + x10)/2, (x10 + x10)/2 */
			    /* tail2 = p10, p10, p10 */
			    /* tail3 =   0,   0,   0 */
				/* SP MAP2 interleaved data */
			    /* tail1 = (x20 + x20)/2, (x20 + x20)/2, (x20 + x20)/2 */
			    /* tail2 = p20, p20, p20 */
			    /* tail3 =   0,   0,   0 */

				if (TCP2_MAP_MAP1 == map) {
				    tail1 = TCP2_makeTailArgs((tailData [7] + tailData [6]) / 2, 
				    	(tailData [4] + tailData [3]) / 2, 
				    	(tailData [1] + tailData [0]) / 2);
				    tail2 = TCP2_makeTailArgs(tailData [8], tailData [5], 
                                                                tailData [2]);
				    tail3 = 0;
				}
				else {
				    tail1 = TCP2_makeTailArgs(
                        (tailData [15] + tailData [16]) / 2, 
				    	(tailData [12] + tailData [13]) / 2, 
				    	(tailData [9] + tailData [10]) / 2
                        );
				    tail2 = TCP2_makeTailArgs(tailData [17], tailData [14], 
                                                               tailData [11]);
				    tail3 = 0;
				}
				tail4 = 0;
				tail5 = 0;
				tail6 = 0;
				break;
            }
			case TCP2_RATE_1_4: {
                /* SP MAP1 non interleaved data */
				/* tail1 = (x10 + x10)/2, (x10 + x10)/2, (x10 + x10)/2 */
			    /* tail2 = p10, p10, p10 */
			    /* tail3 = p11, p11, p11 */
				/* SP MAP2 interleaved data */
			    /* tail1 = (x20 + x20)/2, (x20 + x20)/2, (x20 + x20)/2 */
			    /* tail2 = p20, p20, p20 */
			    /* tail3 = p21, p21, p21 */

				if (TCP2_MAP_MAP1 == map) {
				    tail1 = TCP2_makeTailArgs((tailData [8] + tailData [9]) / 2, 
				    						(tailData [4] + tailData [5]) / 2, 
				    						(tailData [0] + tailData [1]) / 2);
				    tail2 = TCP2_makeTailArgs(tailData [10], tailData [6], 
                                                                tailData [2]);
				    tail3 = TCP2_makeTailArgs(tailData [11], tailData [7], 
                                                                tailData [3]);
				}
				else {
				    tail1 = TCP2_makeTailArgs(
                                            (tailData [20] + tailData [21]) / 2, 
				    						(tailData [17] + tailData [16]) / 2, 
				    						(tailData [12] + tailData [13]) / 2
                                            );
				    tail2 = TCP2_makeTailArgs(tailData [22], tailData [18], 
                                                                tailData [14]);
				    tail3 = TCP2_makeTailArgs(tailData [23], tailData [19], 
                                                                tailData [15]);
				}
				tail4 = 0;
				tail5 = 0;
				tail6 = 0;

				break;
            }
			case TCP2_RATE_1_5: {
                /* SP MAP1 non interleaved data */
				/* tail1 = (x10 + x10 + x10)/3, (x10 + x10 + x10)/3, 
                                                    (x10 + x10 + x10)/3 */
			    /* tail2 = p10, p10, p10 */
			    /* tail3 = p11, p11, p11 */
				/* SP MAP2 interleaved data */
			    /* tail4 = (x20 + x20 + x20)/3, (x20 + x20 + x20)/3, 
                                                    (x20 + x20 + x20)/3 */
			    /* tail5 = p20, p20, p20 */
			    /* tail6 = p21, p21, p21 */

				if (TCP2_MAP_MAP1 == map) {
				    tail1 = TCP2_makeTailArgs(
                            (tailData [10] + tailData [11] + tailData [12]) / 3, 
				    		(tailData [5] + tailData [6] + tailData [7]) / 3, 
			    			(tailData [0] + tailData [1] + tailData [2]) / 3
                            );
				    tail2 = TCP2_makeTailArgs(tailData [13], tailData [8], 
                                                                tailData [3]);
				    tail3 = TCP2_makeTailArgs(tailData [14], tailData [9], 
                                                                tailData [4]);
				}
				else {
				    tail1 = TCP2_makeTailArgs(
                            (tailData [25] + tailData [26] + tailData [27]) / 3, 
				    		(tailData [20] + tailData [21] + tailData [22]) / 3, 
				    		(tailData [15] + tailData [16] + tailData [17]) / 3
                            );
				    tail2 = TCP2_makeTailArgs(tailData [28], tailData [23], 
                                                                tailData [18]);
				    tail3 = TCP2_makeTailArgs(tailData [29], tailData [24], 
                                                                tailData [19]);
				}
				tail4 = 0;
				tail5 = 0;
				tail6 = 0;
				break;
            }
			default:
				break;
		}
	} /* end of else */
    
    /* Assign the tail data values */
 	gie =  _disable_interrupts ();
    
    configIc->ic6  = tail1;
    configIc->ic7  = tail2;
    configIc->ic8  = tail3;
    configIc->ic9  = tail4;
    configIc->ic10 = tail5;
    configIc->ic11 = tail6;
    
	_restore_interrupts (gie); 

    return;
    
} /* end TCP2_tailConfigIs2000 */

/** ============================================================================
 *   @n@b TCP2_calculateHd
 *
 *   @b Description
 *   @n This function calculates the hard decisions following multiple MAP 
 *		decodings in shared processing mode.
 *
 *   @b Arguments
     @verbatim
            extrinsicsMap1      Extrinsics data following MAP1 decode

            apriori             Apriori data following MAP2 decode

            channelData         Input channel data

            hardDecisions       Hard decisions

            numExt              Number of extrinsics

     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The hardDecisions will contain the calculated hard decisions. 
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
            void TCP2_calculateHd(extrinsicsMap1, apriori,
                      channelData, hardDecisions, numExt);
     @endverbatim
 * ===========================================================================
 */
void TCP2_calculateHd (
    const TCP2_ExtrinsicData     *extrinsicsMap1,
    const TCP2_ExtrinsicData     *apriori,
    const TCP2_UserData          *channelData,
    Uint32                      *hardDecisions,
    Uint16                      numExt
)
{
	Uint32 i;
	Int32  extInt;
	Int32  apInt;
	Int32  inputInt;
	Int32  softDecision;
	Uint32 wordCount = 0;
	Uint32 hdCount = 0;

	hardDecisions[0] = 0;

	for (i = 0; i < numExt; i++) {
     
	  if((extrinsicsMap1[i]<<1)&0x80) 
	    extInt = (extrinsicsMap1[i]<<1) | 0xffffff00; 
	  else 
	    extInt = (Int32)(extrinsicsMap1[i]<<1); 
	         
	  if((apriori[i]<<1)&0x80) 
	    apInt = (apriori[i]<<1) | 0xffffff00; 
	  else 
	    apInt = (Int32)(apriori[i]<<1); 

	  inputInt = (Int32)channelData[i / 5]; /*  i * rate( = 1/5) */
	      
	  if(inputInt & 0x80) inputInt |= 0xFFFFFF00;
	               
	  softDecision = inputInt + extInt + apInt; 
	          
	  if(hdCount == 32) {    
	      hdCount = 0;
	      wordCount++;
	      hardDecisions[wordCount] = 0;
	    }
	      
	  if((softDecision & 0x200) == 0)
	    hardDecisions[wordCount] |= 1 << hdCount; 
	     
	  hdCount++; 
	      
	} 

    return;
}

/** ============================================================================
 *   @n@b TCP2_deinterleaveExt 
 *
 *   @b Description
 *   @n This function de-interleaves the MAP2 extrinsics data to generate 
 *		apriori data for the MAP1 decode. This function is for use in 
 *		performing shared processing.
 *
 *   @b Arguments
     @verbatim
            aprioriMap1         Apriori data for MAP1 decode

            extrinsicsMap2      Extrinsics data 

            interleaverTable    Interleaver data table

            numExt              Number of Extrinsics
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The aprioriMap1 will contain the deinterleaved data. 
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
            <...MAP 2 decode...>

            TCP2_deinterleaveExt(aprioriMap1, extrinsicsMap2,

                      interleaverTable, numExt);

            <...MAP 1 decode...>
     @endverbatim
 * ===========================================================================
 */
void TCP2_deinterleaveExt (
    TCP2_ExtrinsicData           *aprioriMap1,
    const TCP2_ExtrinsicData     *extrinsicsMap2,
    const Uint16                *interleaverTable,
    Uint32                      numExt
)
{
	Uint32 cnt;
    
    /* deinterleave extrinsics */
    for (cnt = 0; cnt < numExt; cnt++) {
        aprioriMap1[interleaverTable[cnt]] = *(extrinsicsMap2 + cnt);
    }

    return;
}

/** ============================================================================
 *   @n@b TCP2_interleaveExt 
 *
 *   @b Description
 *   @n This function interleaves the MAP1 extrinsics data to generate 
 *		apriori data for the MAP2 decode. This function is for used in 
 *		performing shared processing.
 *
 *   @b Arguments
     @verbatim
            aprioriMap2          Apriori data for MAP2 decode

            extrinsicsMap1       Extrinsics data 

            interleaverTable     Interleaver data table

            numExt               Number of Extrinsics
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The aprioriMap2 will contain the interleaved data. 
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
            <...MAP 1 decode...>

            TCP2_interleaveExt(aprioriMap2, extrinsicsMap1,

                         interleaverTable, numExt);

            <...MAP 2 decode...>
     @endverbatim
 * ===========================================================================
 */
void TCP2_interleaveExt (
    TCP2_ExtrinsicData           *aprioriMap2,
    const TCP2_ExtrinsicData     *extrinsicsMap1,
    const Uint16                *interleaverTable,
    Uint32                      numExt
)
{
	Uint32 cnt;
    
     /* interleaving extrinsics */
    for (cnt=0; cnt < numExt; cnt++) {
      aprioriMap2[cnt] = *(extrinsicsMap1 + interleaverTable[cnt]);
    }

    return;
}

/** ============================================================================
 *   @n@b TCP2_demuxInput 
 *
 *   @b Description
 *   @n This function splits the input data into two working sets. One set 
 *		contains the non-interleaved input data and is used with the MAP 1 
 *		decoding. The other contains the interleaved input data and is used 
 *		with the MAP2 decoding. This function is used in shared processing mode.
 *
 *   @b Arguments
     @verbatim
            rate                TCP data code rate

            frameLen            Frame length

            input               Input channel data

            interleaver         Interleaver data table

            nonInterleaved      Non Interleaved data for SP MAP0

            interleaved         Interleaved data for SP MAP1
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None 
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n The nonInterleaved will contain the non-interleaved 
 *		data and the interleaved will contain the interleaved data. 
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
             TCP2_demuxInput (frameLen, input,
                       interleaver, interleaved, nonInterleaved);
     @endverbatim
 * ===========================================================================
 */
void TCP2_demuxInput (
    Uint32                  rate,
    Uint32                  frameLen,
    const TCP2_UserData      *input,
    const Uint16            *interleaver,
    TCP2_ExtrinsicData    	*nonInterleaved,
    TCP2_ExtrinsicData 	   	*interleaved
)
{
    Uint32  inCnt;
	Uint32  outCnt;
   	Uint32  cnt;
    Uint16  iter;
    Uint32  *output0 = (Uint32 *)nonInterleaved;
    Uint32  *output1 = (Uint32 *)interleaved;
    Uint16  *deInterleaveTbl;
    Uint16  dataIndex;
    Uint16  tableIndex;
    Uint16  numPar;
    
    /* allocate memory for deinterleave table */
    deInterleaveTbl = (Uint16*) malloc (sizeof (Uint16) * frameLen);
    /*
	'interleaver' is a buffer of frameLen 16-bit indices
	'input' is a buffer of frameLen * rate 8-bit elements
	'output[2]' is the 2 de-multiplexed buffers :
	            .out[0] buffer which is the TCP input buffer for LOG-MAP 1 decoding
	            .out[1] buffer which is the TCP input buffer for LOG-MAP 2 decoding
	*/
     /* For shared processing, TCP2 only executes the non-interleaved MAP 
      * decoder. Therefore, p20 and p21 are not used in the input data. When 
      * processing a non-interleaved MAP(as MAP1 in SA mode) x10, p10, and 
      * p11 must be non-interleaved data. And when processing the interleaved 
      * MAP (As MAP2 in SA mode) x10, p10, and p11 must be the interleaved data 
      * that has been deinterleaved.
      */
      
    /* Form the de-interleave table */
    for (cnt = 0; cnt < frameLen; cnt++)
        deInterleaveTbl [ interleaver [cnt] ] = cnt;
        
	/* Form the output for MAP1 and MAP2 */ 
    

    switch (rate) {
        case TCP2_RATE_1_5: {
            /* for code rate = 1/5 */
            /* Set of 5 symbols are processed at once */
            
             /* input (Uint8):
              * x0a0b0a0'b0'x1a1b1a1'b1'
              * 
              * output (Uint32)
              * non interleaved: 
              *  b0 a0 x0       
              *  b1 a1 x1
              *   
              * interleaved: 
              *  b0' a0' x0       
              *  b1' a1' x1
              */
        
            outCnt = 0;
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                /*  Form the non interleaved data */                  
                output0 [outCnt] = input [inCnt + 2] << 12 |
                                input [inCnt + 1] << 6 | 
                                input [inCnt];  
            
                /*  Form the interleaved data */  
                tableIndex = inCnt / rate;
                dataIndex =  deInterleaveTbl [tableIndex] * rate;
                               
                output1 [outCnt] = input [dataIndex + 4] << 12 |
                                input [dataIndex + 3] << 6 | 
                                input [inCnt];  
                                
                /* Fill the next Uint32 value */
                outCnt++;
            }
            break; 
        }/* TCP2_RATE_1_5 */

        case TCP2_RATE_1_4: {
            /* for code rate = 1/4 */
            /* Set of 4 symbols are processed at once */
            
             /* input (Uint8):
              * x0a0b0b0'x1a1a1'b1'
              * 
              * output (Uint32)
              * non interleaved: 
              *  b0 a0 x0       (even)
              *  0 a1 x1        (odd)
              *   
              * interleaved: 
              *  b0' 0  x0       
              *  b1' a1' x1
              */
        
            outCnt = 0;

             /* Used to handle the  difference in the input data symbols for 
              * 2 consecutive set of 4 symbols
              */
            iter = 0;  
            
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                if (0 == iter) {
                    /*  Form the non interleaved data */                  
                    output0 [outCnt] = input [inCnt + 2] << 12 |
                                    input [inCnt + 1] << 6 | 
                                    input [inCnt];  
            
                    /*  Form the interleaved data */  
                    tableIndex = inCnt / rate;

                    dataIndex =  deInterleaveTbl [tableIndex] * rate;
                    
                    if ((deInterleaveTbl [tableIndex] % 2) == 0) {                                  
                        output1 [outCnt] = input [dataIndex + 3] << 12 | 
                                    input [inCnt];  
                    }
                    else {
                        output1 [outCnt] = input [dataIndex + 3] << 12 |
                                          input [dataIndex + 2] << 6 | 
                                          input [inCnt];  
                    }
                    
                    iter = 1;
                } /* end of if (0 == iter) */   
                else {
                
                    /*  Form the non interleaved data */                  
                    output0 [outCnt] = input [inCnt + 1] << 6 | 
                                    input [inCnt];  
                
                    /*  Form the interleaved data */  
                    tableIndex = inCnt / rate;
                    
                    dataIndex =  deInterleaveTbl [tableIndex] * rate;
                    
                    if ((deInterleaveTbl [tableIndex] % 2) == 0) {                                  
                        output1 [outCnt] = input [dataIndex + 3] << 12 | 
                                    input [inCnt];  
                    }
                    else {
                        output1 [outCnt] = input [dataIndex + 3] << 12 |
                                          input [dataIndex + 2] << 6 | 
                                          input [inCnt];  
                    }
                    
                    iter = 0;
                } /* end of else of if (0 == iter) */                             
                
                /* Fill the next Uint32 value */
                outCnt++;
            }
            break; 
        }/* TCP2_RATE_1_4 */

        case TCP2_RATE_1_3: {
            /* for code rate = 1/3 */
            /* Set of 3 symbols are processed at once */
            
             /* input (Uint8):
              * x0a0a0'x1a1a1'
              * 
              * output (Uint32)
              * non interleaved: 
              *   a0 x0       
              *   a1 x1
              *   
              * interleaved: 
              *   a0' x0       
              *   a1' x1
              */
        
            outCnt = 0;
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                /*  Form the non interleaved data */                  
                output0 [outCnt] = input [inCnt + 1] << 6 | 
                                input [inCnt];  
            
                /*  Form the interleaved data */  
                tableIndex = inCnt / rate;
                
                dataIndex =  deInterleaveTbl [tableIndex] * rate;
                               
                output1 [outCnt] = input [dataIndex + 2] << 6 | 
                                input [inCnt];  
                                
                /* Fill the next Uint32 value */
                outCnt++;
            }
            break; 
        }/* TCP2_RATE_1_3 */
        
        case TCP2_RATE_1_2: {
            /* for code rate = 1/2 */
            /* Set of 2 symbols are processed at once */
            
             /* input (Uint8):
              * x0a0x1a1'x2a2x3a3'
              * 
              * output (Uint32)
              * non interleaved: 
              *  a0 x0       (even)
              *  0  x1        (odd)
              *   
              * interleaved: 
              *  0  x0       
              *  a1' x1
              */
        
            outCnt = 0;

             /* Used to handle the  difference in the input data symbols for 
              * 2 consecutive set of 2 symbols
              */
            iter = 0;  
            
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                if (0 == iter) {
                    /*  Form the non interleaved data */                  
                    output0 [outCnt] = input [inCnt + 1] << 6 | 
                                    input [inCnt];  
            
                    /*  Form the interleaved data */  
                    tableIndex = inCnt / rate;
                    dataIndex =  deInterleaveTbl [tableIndex] * rate;
                    
                    if ((deInterleaveTbl [tableIndex] % 2) == 0) {                                  
                        output1 [outCnt] = input [inCnt];  
                    }
                    else {
                        output1 [outCnt] = input [dataIndex + 1] << 6 | 
                                          input [inCnt];  
                    }
                    
                    iter = 1;
                } /* end of if (0 == iter) */   
                else {
                
                    /*  Form the non interleaved data */                  
                    output0 [outCnt] = input [inCnt];  
                
                    /*  Form the interleaved data */  
                    tableIndex = inCnt / rate;
                    dataIndex =  deInterleaveTbl [tableIndex] * rate;
                    
                    if ((deInterleaveTbl [tableIndex] % 2) == 0) {                                  
                        output1 [outCnt] = input [inCnt];  
                    }
                    else {
                        output1 [outCnt] = input [dataIndex + 1] << 6 | 
                                          input [inCnt];  
                    }
                    
                    iter = 0;
                } /* end of else of if (0 == iter) */                             
                
                /* Fill the next Uint32 value */
                outCnt++;
            }
            break; 
        }/* TCP2_RATE_1_2 */
        
        case TCP2_RATE_3_4: {
            /* for code rate = 3/4 */
             /* input (Uint8):
              * x0a0x1x2x3a3'x4x5
              * 
              * output (Uint32)
              * non interleaved: 
              *  a0 x0       (even)
              *  0  x1        (odd)
              *  0  x2
              *   
              * interleaved: 
              *  0   x0       
              *  0   x1
              *  0   x2
              *  a3' x3
              */
             
            /* Set of 4 symbols are processed at once to get 3 output data */
            outCnt = 0;
            
             /* Used to handle the  difference in the input data symbols for 
              * 2 consecutive set of 4 symbols
              */
            iter = 0;  
            
            /* to calculate the symbols added for rate 3/4 */
            
            for (inCnt = 0; inCnt < frameLen; inCnt += 1) {
                 /* Shift the data and convert to the 32 bit TCP input 
                  * data format 
                  */        
                  if (((inCnt % 2) == 0) && ((inCnt % 3) == 0))  {
                    /*  Form the non interleaved data - 3 */                  
                    output0 [outCnt] = (
                                (input [inCnt + numPar + 1] << 6) |                                
                                (input [inCnt + numPar] << 0)                                 
                                );
                    }
                    else {
                      output0 [outCnt ] = input [inCnt  + numPar];                                
                    }
                    
                    /*  Form the interleaved data */  
                    dataIndex =  deInterleaveTbl [inCnt] + numPar;
                    
                    if (((deInterleaveTbl [inCnt] % 2) != 0) && 
                        ((deInterleaveTbl [inCnt] % 3) == 0)) {                                  
                        output1 [outCnt] = input [dataIndex + 1] << 6 | 
                                          input [inCnt + numPar];  
                    }
                    else {
                        output1 [outCnt] = input [inCnt + numPar];  
                    }
                    
                     /* adjust for the parity data, required as the inCnt is 
                      * incremented by 1 and not rate 
                      */
                    if ((inCnt % 3) == 0) {
                        numPar++; /* offset to get the data index */
                    }
                    
                    outCnt += 1;
            } /* end of for */

            break;
        }/* TCP2_RATE_3_4 */

        default:
            break;  

    }/* end of switch */
    
    /* Free the memory allocated for de interleave table */
    free (deInterleaveTbl);

    return;
} /* end TCP2_demuxInput() */


/** ============================================================================
 *   @n@b TCP2_depunctInputs
 *
 *   @b Description
 *   @n This function scales and sorts input data into a code rate 1/5 format.
 *
 *   @b Arguments
     @verbatim
            frameLen            Input data length in bytes
            
            inputData           Input data
            
            rate                Input data code rate

            scalingFact         Scaling factor

            depunctData         Depunctured data
            
      @endverbatim
 *
 *   <b> Return Value </b>  None
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The depunctData will contain the data depunctured to rate 1/5. 
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim

            TCP2_depunctInputs (length, inputData, rate

                      scalingFact, depunctData);

     @endverbatim
 * ===========================================================================
 */
void TCP2_depunctInputs (
    Uint32              frameLen,
    TCP2_UserData*       inputData,
    TCP2_Rate            rate,
    Uint32              scalingFact,
    TCP2_InputData*      depunctData       
)
{
	Uint32  inCnt;
	Uint32  outCnt;
   	Uint32  cnt;
    Uint32  modLen;
    Uint16  iter;
    
    switch (rate) {
        case TCP2_RATE_1_5: {
            /* for code rate = 1/5 */
            /* Set of 5 symbols are processed at once */
            
             /* input (Uint8):
              * x0a0b0a0'b0'x1a1b1a1'b1'
              * 
              * output (Uint32)
              * b0' a0' b0 a0 x0       
              * b1' a1' b1 a1 x1
              */
        
            outCnt = 0;
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                /* Shift the data and convert to the 32 bit TCP input 
                  * data format 
                  */        
                for (cnt = 0; cnt < rate; cnt++) {
                    depunctData [outCnt] |= (
                            (inputData [inCnt + cnt] * scalingFact ) << 
                                                        DATA_WIDTH * cnt);
                }
            
                /* Fill the next Uint32 value */
                outCnt++;
            }
            break; 
        }/* TCP2_RATE_1_5 */
        
        case TCP2_RATE_1_4: {
            /* for code rate = 1/4 */
             /* input (Uint8):
              * x0a0b0b0'x1a1a1'b1'
              * 
              * output (Uint32)
              * b0' 0   b0 a0 x0       
              * b1' a1'  0 a0 x1
              */
            /* Set of 4 symbols are processed at once */
            outCnt = 0;
            
             /* Used to handle the  difference in the input data symbols for 
              * 2 consecutive set of 4 symbols
              */
            iter = 0;  
            
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                 /* Shift the data and convert to the 32 bit TCP input 
                  * data format 
                  */        
                if (0 == iter) {
                    depunctData [outCnt] = (
                                ((inputData [inCnt + 3] * scalingFact)  << 24) |
                                ((inputData [inCnt + 2] * scalingFact) << 12) |
                                ((inputData [inCnt + 1] * scalingFact) << 6) |                                
                                ((inputData [inCnt] * scalingFact))                                 
                                );
                    iter = 1;                                
                }                                                       
                else {
                    depunctData [outCnt] = (
                                ((inputData [inCnt + 3] * scalingFact) << 24) |
                                ((inputData [inCnt + 2] * scalingFact) << 18) |
                                ((inputData [inCnt + 1] * scalingFact) << 6) |                                
                                ((inputData [inCnt] * scalingFact))                                 
                                );
                    iter = 0;
                } 
                /* Fill the next Uint32 value */
                outCnt++;
            } /* end of for */
            
            break;    
        }/* TCP2_RATE_1_4 */

        case TCP2_RATE_1_3: {
            /* for code rate = 1/3 */
            /* Set of 4 symbols are processed at once */
            
             /* input (Uint8):
              * x0a0a0'x1a1a1'
              * 
              * output (Uint32)
              * 0 a0' 0 a0 x0       
              * 0 a1' 0 a1 x1
              */
        
            outCnt = 0;
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                 /* Shift the data and convert to the 32 bit TCP input 
                  * data format 
                  */        
                depunctData [outCnt] = (
                            ((inputData [inCnt + 2] * scalingFact) << 18) |
                            ((inputData [inCnt + 1] * scalingFact) << 6) |                                
                            ((inputData [inCnt] * scalingFact))                                 
                            );
                /* Fill the next Uint32 value */
                outCnt++;
            }
            
            break; 
        }/* TCP2_RATE_1_3 */

        case TCP2_RATE_1_2: {
            /* for code rate = 1/2 */
             /* input (Uint8):
              * x0a0x1a1'
              * 
              * output (Uint32)
              * b0' 0   b0 a0 x0       
              * b1' a1'  0 a1 x1
              */
            /* Set of 2 symbols are processed at once */
            outCnt = 0;
            
             /* Used to handle the  difference in the input data symbols for 
              * 2 consecutive set of 2 symbols
              */
            iter = 0;  
            
            for (inCnt = 0; inCnt < frameLen * rate; inCnt += rate) {
                 /* Shift the data and convert to the 32 bit TCP input 
                  * data format 
                  */        
                if (0 == iter) {
                    depunctData [outCnt] = (
                                ((inputData [inCnt + 1] * scalingFact) << 6) |                                
                                ((inputData [inCnt] * scalingFact))                                 
                                );
                    iter = 1;                                
                }                                                       
                else {
                    depunctData [outCnt] = (
                                ((inputData [inCnt + 1] * scalingFact) << 18) |                                
                                ((inputData [inCnt] * scalingFact))                                 
                                );
                    iter = 0;
                } 
                /* Fill the next Uint32 value */
                outCnt++;
            }
            break;
        }/* TCP2_RATE_1_2 */
        
        case TCP2_RATE_3_4: {
            /* for code rate = 3/4 */
             /* input (Uint8):
              * x0a0x1x2x3a3'x4x5
              * 
              * output (Uint32)
              * b0' 0   b0 a0 x0       
              * b1' a1'  0 a1 x1
              */
             
            /* Set of 4 symbols are processed at once to get 3 output data */
            outCnt = 0;
            
             /* Used to handle the  difference in the input data symbols for 
              * 2 consecutive set of 4 symbols
              */
            iter = 0;  
            
            /* to calculate the symbols added for rate 3/4 */
            modLen = (frameLen * 4) / 3;
            
            for (inCnt = 0; inCnt < modLen; inCnt += 4) {
                 /* Shift the data and convert to the 32 bit TCP input 
                  * data format 
                  */        
                if (0 == iter) {
                    /* 3 output data are got */
                    depunctData [outCnt++] = (
                                ((inputData [inCnt + 1] * scalingFact) << 6) |                                
                                ((inputData [inCnt] * scalingFact))                                 
                                );
                                
                    depunctData [outCnt++] = (inputData [inCnt + 2] * scalingFact);                                
                    depunctData [outCnt++] = (inputData [inCnt + 3] * scalingFact);   
                    
                    iter = 1;                                
                }                                                       
                else {
                    /* 3 output data are got */
                    depunctData [outCnt++] = (
                                ((inputData [inCnt + 1] * scalingFact) << 18) |                                
                                ((inputData [inCnt] * scalingFact))                                 
                                );
                                
                    depunctData [outCnt++] = (inputData [inCnt + 2] * scalingFact);                                
                    depunctData [outCnt++] = (inputData [inCnt + 3] * scalingFact);   
                    iter = 0;
                } 
            } /* end of for */
            break;
        }/* TCP2_RATE_3_4 */
        
        default:
            break;  
    }/* end of switch (rate)*/

    return;
}

