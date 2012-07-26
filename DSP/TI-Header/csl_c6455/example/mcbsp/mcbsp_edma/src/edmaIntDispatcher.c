/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005, 2006
 *
 *   Use of this software is controlled by the terms and conditions found in 
 *   the license agreement under which this software has been supplied.
 *   ===========================================================================
 */
 
 /** ===========================================================================
 *
 *   @file  edmaIntDispacher.c
 *
 *   @path  $(CSLPATH)\example\mcbsp\mcbsp_edma\src
 *
 *   @desc  Edma interrupt handler for the Example of MCBSP
 * ============================================================================
 */
 
 /* ===========================================================================
 *  Revision History
 *  ===============
 *  9-Aug-2006 RR File Created.
 *  ============================================================================
 */
 
#include <edmaCommon.h>

/* Global Edma Tcc handler table */
#pragma DATA_SECTION(TccHandlerTable,".testMem");
EdmaTccHandler TccHandlerTable[64];


void eventEdmaHandler(void *handle)
{
    CSL_Edma3Handle hModule = (CSL_Edma3Handle)handle;
    CSL_BitMask32 maskVal;
    CSL_Edma3CmdIntr regionIntr;
    Uint32 tcc, intr,intrh;
    
    /* Read the IPR */
    regionIntr.region = CSL_EDMA3_REGION_0;
    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND, &regionIntr);
    
    while (regionIntr.intr || regionIntr.intrh) 
    {
        intr = regionIntr.intr;
        intrh = regionIntr.intrh;
        tcc = 0;
        while (intr) 
        {
            maskVal = 1 << tcc;
            if (intr & maskVal) 
            {
                InvokeHandle(tcc);
                intr &= ~maskVal;
            }
            tcc++;      
        }       
        tcc = 0;
        while (intrh) 
        {
            maskVal = 1 << tcc;
            if (intrh & maskVal) 
            {
                InvokeHandle((tcc+32));
                intrh &= ~maskVal;
            }       
            tcc++;
        }
        CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR,&regionIntr);       
        CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);         
    }           
}
void EdmaEventHook(int tcc, EdmaTccHandler fxn)
{
    TccHandlerTable[tcc] = (fxn);
}


void eventGlobalEdmaHandler(void *handle)
{
    CSL_BitMask32  mask,maskVal;
    CSL_Edma3CmdIntr regionIntr;
    Uint32 tcc, intr,intrh;
    Int region;
    CSL_Edma3Handle hModule = (CSL_Edma3Handle)handle;

    /* Read the IPR */
    regionIntr.region = CSL_EDMA3_REGION_GLOBAL;

    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);
    intr = regionIntr.intr;
    intrh = regionIntr.intrh;
    mask = 1;
    tcc = 0;
    while (intr) 
    {
        maskVal = mask << tcc;
        if (regionIntr.intr & maskVal) 
        {
            InvokeHandle(tcc);
            intr &= ~maskVal;
        }       
        tcc++;
    }       
    mask = 1;
    tcc = 0;
    while (intrh) 
    {
        maskVal = mask << tcc;
        if (intrh & maskVal) 
        {
            InvokeHandle((tcc+32));
            intrh &= ~maskVal;
        }       
        tcc++;
    }
    CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTRPEND_CLEAR,&regionIntr);       
    CSL_edma3GetHwStatus(hModule,CSL_EDMA3_QUERY_INTRPEND,&regionIntr);         
    if ((regionIntr.intr !=0)||(regionIntr.intrh !=0))
    {
        region = CSL_EDMA3_REGION_GLOBAL;
        CSL_edma3HwControl(hModule,CSL_EDMA3_CMD_INTR_EVAL,&region);        
    }

}

