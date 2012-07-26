/**  ===========================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005
 *
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.
 *   ===========================================================================
 */

/** ============================================================================
 * @file  csl_dat.c
 *
 * @desc  This file defines the functions in the DAT module.
 * 
 *  @path  $(CSLPATH)\src\dat
 */
  
/* =============================================================================
 *  Revision History
 *  ===============
 *  14-Nov-2005 ds File modified - In the APIs DAT_copy(), DAT_copy2d(), 
 *                                 DAT_fill() added macro to set the STATIC when
 *                                 OPT is programmed.   
 * =============================================================================
 */
 
#include <csl_dat.h>
#include <_csl_dat.h>

/** ============================================================================
 *   @n@b DAT_open 
 *
 *   @b Description
 *   @n This API 
 *        a. Sets up the channel to Parameter set mapping \n
 *        b. Sets up the priority. This is essentially done by specifying the  
 *           queue to which the channel is submitted to viz Queue0- Queue7. 
 *           Queue 0 being the highest priority. \n
 *        c. Enables the region access bit for the channel if a region is 
 *       specified.
 *
 *   @b Arguments
     @verbatim
            setup         Pointer to the DAT setup structure
     @endverbatim
 *
 *   <b> Return Value </b>  CSL_SOK
 *
 *   <b> Pre Condition </b> 
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  The EDMA registers are configured with the setup values passed. 
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (DAT_open, ".text:csl_section:dat");
Int16 DAT_open (
    DAT_Setup   *setup
)
{
    Uint32    cs;
    
    /* Enter critical section */
    cs = _disable_interrupts ();

    _CSL_datStateStruct.qchNum = setup->qchNum;
    _CSL_datStateStruct.regionNum = setup->regionNum;
    _CSL_datStateStruct.tccNum = setup->tccNum;
    _CSL_datStateStruct.priority = setup->priority;
    _CSL_datStateStruct.paramNum = setup->paramNum;
    _CSL_datStateStruct.pending = FALSE;

    /* the que entry number mapping */
    CSL_FINSR (((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->QDMAQNUM,
               setup->qchNum * 4 + 2, setup->qchNum * 4, setup->priority);

    /* The parameter set mapping */
    ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->QCHMAP[setup->qchNum] =
        CSL_FMK (EDMA3CC_QCHMAP_PAENTRY, setup->paramNum) |
        CSL_FMK (EDMA3CC_QCHMAP_TRWORD, 7);

    /* Enable the DRAE Bit */
    if (setup->regionNum != CSL_DAT_REGION_GLOBAL) {
        ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->QRAE[setup->regionNum] |=
            (1 << setup->qchNum);
        ((CSL_Edma3ccRegsOvly)
            CSL_EDMA3CC_0_REGS)->SHADOW[setup->regionNum].QEESR =
            (1 << setup->qchNum);
    }
    else {
        ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->QEESR =
            (1 << setup->qchNum);
    }
    
    /* Leave critical section */
    _restore_interrupts (cs);
    
    return CSL_SOK;
}

/** ============================================================================
 *   @n@b DAT_close 
 *
 *   @b Description
 *   @n This API 
 *         a. Disables the region access bit if specified.
 *
 *   @b Arguments
 *   @n None
 *
 *   <b> Return Value </b> 
 *   @n None
 *
 *   <b> Pre Condition </b> 
 *   @n  DAT_open() must be successfully invoked prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  None 
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
        ...
        DAT_close();    
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (DAT_close, ".text:csl_section:dat");
void DAT_close (void)
{
    Uint32    cs;

    if (_CSL_datStateStruct.regionNum != CSL_DAT_REGION_GLOBAL) {
        
        cs = _disable_interrupts ();
        
        ((CSL_Edma3ccRegsOvly)
            CSL_EDMA3CC_0_REGS)->QRAE[_CSL_datStateStruct.regionNum] &=
            ~(1 << _CSL_datStateStruct.qchNum);
            
        _restore_interrupts (cs);
    }
}

/** ============================================================================
 *   @n@b DAT_copy 
 *
 *   @b Description
 *   @n This API copies data from source to destination for one dimension 
 *    transfer. 
 *
 *   @b Arguments
     @verbatim
            src         Source memory address for the data transfer

            dst         Destination memory address of the data transfer

            byteCnt     Number of bytes to be transferred
     @endverbatim
 *
 *   <b> Return Value </b>  tccNum
 *
 *   <b> Pre Condition </b> 
 *   @n  DAT_open() must be successfully invoked prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  The EDMA registers are configured to transfer byteCnt bytes from the 
 *       source memory address to the destination memory address 
 *
 *   @b Modifies
 *   @n EDMA registers   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        Uint8 dst1d[8*16];
        Uint8 src1d[8*16];
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
        ...
        DAT_copy(&src1d,&dst1d,256);
        ...
        DAT_close();    
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (DAT_copy, ".text:csl_section:dat");
Uint32 DAT_copy (
    void      *src, 
    void      *dst,
    Uint16    byteCnt
)
{
    volatile    CSL_Edma3ccParamsetRegs *param;
    Uint32      cs;

    cs = _disable_interrupts ();

    param = &((CSL_Edma3ccRegsOvly)
        CSL_EDMA3CC_0_REGS)->PARAMSET[_CSL_datStateStruct.paramNum];
    if (_CSL_datStateStruct.pending)
        DAT_wait (_CSL_datStateStruct.tccNum);
        
    /* The options in the param set programmed need to have STATIC = 1.
     * If STATIC != 1 then when QDMA links to NULL SER will get set causing
     * further issue of Transfer requests
     */
    param->OPT = CSL_FMKT (EDMA3CC_OPT_TCINTEN, ENABLE) |
        CSL_FMK (EDMA3CC_OPT_TCC, _CSL_datStateStruct.tccNum) |
        CSL_FMKT (EDMA3CC_OPT_STATIC, STATIC);
        
    param->SRC = (Uint32) (src);
    param->A_B_CNT = CSL_FMK (EDMA3CC_A_B_CNT_ACNT, byteCnt) |
        CSL_FMK (EDMA3CC_A_B_CNT_BCNT, 1);
    param->DST = (Uint32) (dst);
    param->LINK_BCNTRLD = CSL_FMK (EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    param->CCNT = 0x00000001;
    _CSL_datStateStruct.pending = TRUE;
    _restore_interrupts (cs);
    return _CSL_datStateStruct.tccNum;
}

/** ============================================================================
 *   @n@b DAT_fill 
 *
 *   @b Description
 *   @n This API fill destination by given fill value.
 *
 *   @b Arguments
     @verbatim
            dst         Destination memory address to be filled

            byteCnt Number of bytes to be filled

            value       Value to be filled  
     @endverbatim
 *
 *   <b> Return Value </b>  tccNum
 *
 *   <b> Pre Condition </b> 
 *   @n  DAT_open() must be successfully invoked prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  The EDMA registers are configured to transfer a value to byteCnt bytes 
 *       of the destination memory address 
 *
 *   @b Modifies
 *   @n EDMA registers   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        Uint8 dst[8*16];
        Uint8 fillVal;
    
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
        ...
        fillVal = 0x5a;
        DAT_fill(&dst,256,&fillval);
        ...
        DAT_close();    

     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (DAT_fill, ".text:csl_section:dat");
Uint32 DAT_fill (
    void      *dst,
    Uint16    byteCnt, 
    Uint32    *value
)
{
    volatile CSL_Edma3ccParamsetRegs *param;
    Uint32 cs;

    cs = _disable_interrupts ();

    param = &((CSL_Edma3ccRegsOvly)
        CSL_EDMA3CC_0_REGS)->PARAMSET[_CSL_datStateStruct.paramNum];

    if (_CSL_datStateStruct.pending)
        DAT_wait (_CSL_datStateStruct.tccNum);
        
    /* The options in the param set programmed need to have STATIC = 1.
     * If STATIC != 1 then when QDMA links to NULL SER will get set causing
     * further issue of Transfer requests
     */
    param->OPT = CSL_FMKT (EDMA3CC_OPT_TCINTEN, ENABLE) |
        CSL_FMK (EDMA3CC_OPT_TCC, _CSL_datStateStruct.tccNum) |
        CSL_FMKT (EDMA3CC_OPT_SYNCDIM, ABSYNC) |
        CSL_FMKT (EDMA3CC_OPT_STATIC, STATIC);
        
    param->SRC = (Uint32) (value);
    param->A_B_CNT = CSL_FMK (EDMA3CC_A_B_CNT_ACNT, 1) |
        CSL_FMK (EDMA3CC_A_B_CNT_BCNT, byteCnt);
    param->DST = (Uint32) (dst);
    param->SRC_DST_BIDX = CSL_FMK (EDMA3CC_SRC_DST_BIDX_DSTBIDX, 1) |
        CSL_FMK (EDMA3CC_SRC_DST_BIDX_SRCBIDX, 0);
    param->LINK_BCNTRLD = CSL_FMK (EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    param->CCNT = 0x00000001;
    _CSL_datStateStruct.pending = TRUE;
    _restore_interrupts (cs);
    return _CSL_datStateStruct.tccNum;
}

/** ============================================================================
 *   @n@b DAT_wait 
 *
 *   @b Description
 *   @n This API Waits for completion of the ongoing transfer. 
 *
 *   @b Arguments
     @verbatim
            id         Channel number of the previous transfer
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n  None
 *
 *   <b> Pre Condition </b> 
 *   @n  DAT_copy()/DAT_fill must be successfully invoked prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  Indicates that the transfer ongoing is complete
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        Uint8 dst1d[8*16];
        Uint8 src1d[8*16];
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
        ...
        id = DAT_copy(&src1d,&dst1d,256);

        DAT_wait(id);
        ...
        DAT_close();

     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (DAT_wait, ".text:csl_section:dat");
void DAT_wait ( 
    Uint32    id
)
{
    Uint32 cs;

    cs = _disable_interrupts ();

    if (_CSL_datStateStruct.regionNum != CSL_DAT_REGION_GLOBAL) {
        if (_CSL_datStateStruct.tccNum < 32) {
            while (!(((CSL_Edma3ccRegsOvly)
                        CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.
                        regionNum].IPR & (1 << _CSL_datStateStruct.tccNum)));
            ((CSL_Edma3ccRegsOvly)
                CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.regionNum].ICR =
                (1 << _CSL_datStateStruct.tccNum);
        }
        else {
            while (!(((CSL_Edma3ccRegsOvly)
                        CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.
                        regionNum].IPRH & (1 << (_CSL_datStateStruct.tccNum -
                            32))));
            ((CSL_Edma3ccRegsOvly)
                CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.regionNum].
                ICRH = (1 << _CSL_datStateStruct.tccNum - 32);
        }
    }
    else {
        if (_CSL_datStateStruct.tccNum < 32) {
            while (!(((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->IPR &
                    (1 << _CSL_datStateStruct.tccNum)));
            ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->ICR =
                (1 << _CSL_datStateStruct.tccNum);
        }
        else {
            while (!(((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->IPRH &
                    (1 << (_CSL_datStateStruct.tccNum - 32))));
            ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->ICRH =
                (1 << _CSL_datStateStruct.tccNum - 32);
        }
    }
    _CSL_datStateStruct.pending = FALSE;
    _restore_interrupts (cs);
}

/** ============================================================================
 *   @n@b DAT_busy 
 *
 *   @b Description
 *   @n This API polls for transfer completion. 
 *
 *   @b Arguments
     @verbatim
            id         Channel number of the previous transfer
     @endverbatim
 *
 *   <b> Return Value </b>  Int16
 *                              TRUE/FALSE
 *
 *   <b> Pre Condition </b> 
 *   @n  DAT_copy()/DAT_fill must be successfully invoked prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  Indicates that the transfer ongoing is complete
 *
 *   @b Modifies
 *   @n None   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        Uint8 dst1d[8*16];
        Uint8 src1d[8*16];
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
        ...
        id = DAT_copy(&src1d,&dst1d,256);

        do {
            ... 
           }while (DAT_busy(id));
        ...
        DAT_close();

     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (DAT_busy, ".text:csl_section:dat");
Int16 DAT_busy (
    Uint32    id
)
{
    Bool        status = TRUE;
    Uint32      temp;
    Uint32      cs;

    cs = _disable_interrupts ();
    
     /* The number 32 signifies lower 32 channels */
    if (_CSL_datStateStruct.regionNum != CSL_DAT_REGION_GLOBAL) {
        if (_CSL_datStateStruct.tccNum < 32) {
            temp = ((CSL_Edma3ccRegsOvly)
                CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.regionNum].IPR &
                (1 << _CSL_datStateStruct.tccNum);
        }
        else {
            temp = ((CSL_Edma3ccRegsOvly)
                CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.regionNum].
                IPRH & (1 << (_CSL_datStateStruct.tccNum - 32));
        }
    }
    else {
        if (_CSL_datStateStruct.tccNum < 32) {
            temp = ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->IPR &
                (1 << _CSL_datStateStruct.tccNum);
        }
        else {
            temp = ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->IPRH &
                (1 << (_CSL_datStateStruct.tccNum - 32));
        }
    }
    
    if (temp) {
        if (_CSL_datStateStruct.regionNum != CSL_DAT_REGION_GLOBAL) {
            if (_CSL_datStateStruct.tccNum < 32) {
                ((CSL_Edma3ccRegsOvly)
                    CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.regionNum].
                    ICR = (1 << _CSL_datStateStruct.tccNum);
            }
            else {
                ((CSL_Edma3ccRegsOvly)
                    CSL_EDMA3CC_0_REGS)->SHADOW[_CSL_datStateStruct.regionNum].
                    ICRH = (1 << (_CSL_datStateStruct.tccNum - 32));
            }
        }
        else {
            if (_CSL_datStateStruct.tccNum < 32) {
                ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->ICR =
                    (1 << _CSL_datStateStruct.tccNum);
            }
            else {
                ((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->ICRH =
                    (1 << (_CSL_datStateStruct.tccNum - 32));
            }
        }
        
        _CSL_datStateStruct.pending = FALSE;
        status = FALSE;
    }
    
    _restore_interrupts (cs);
    
    return status;
}

/** ============================================================================
 *   @n@b DAT_copy2d 
 *
 *   @b Description
 *   @n This API copies data from source to destination for two dimension 
 *    transfer. 
 *
 *   @b Arguments
     @verbatim
            type        Indicates the type of the transfer
                            DAT_1D2D - 1 dimension to 2 dimension
                            DAT_2D1D - 2 dimension to 1 dimension
                            DAT_2D2D - 2 dimension to 2 dimension
                        
            src         Source memory address for the data transfer

            dst         Destination memory address of the data transfer

            lineLen     Number of bytes per line
            
            lineCnt     Number of lines
            
            linePitch   Number of bytes between start of one line to start 
                        of next line
                        
     @endverbatim
 *
 *   <b> Return Value </b>  tccNum
 *
 *   <b> Pre Condition </b> 
 *   @n  DAT_open() must be successfully invoked prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  The EDMA registers are configured for the transfer  
 *
 *   @b Modifies
 *   @n EDMA registers   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        Uint8 dst2d[8][20];
        Uint8 src1d[8*16];
    
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
        ...
        id = DAT_copy2d(DAT_1D2D,src1d,dst2d,16,8,20);  

        do {
        ... 
        }while (DAT_busy(id));
        ...
        DAT_close();
     @endverbatim
 * ===========================================================================
 */
#pragma CODE_SECTION (DAT_copy2d, ".text:csl_section:dat");
Uint32 DAT_copy2d (
    Uint32    type, 
    void      *src, 
    void      *dst, 
    Uint16    lineLen,
    Uint16    lineCnt,
    Uint16    linePitch
)
{
    volatile CSL_Edma3ccParamsetRegs *param;
    Uint32 cs;

    cs = _disable_interrupts ();

    param = &((CSL_Edma3ccRegsOvly)
        CSL_EDMA3CC_0_REGS)->PARAMSET[_CSL_datStateStruct.paramNum];
        
    if (_CSL_datStateStruct.pending) 
        DAT_wait (_CSL_datStateStruct.tccNum);
    
    /* The options in the param set programmed need to have STATIC = 1.
     * If STATIC != 1 then when QDMA links to NULL SER will get set causing
     * further issue of Transfer requests
     */    
    param->OPT = CSL_FMKT (EDMA3CC_OPT_TCINTEN, ENABLE) |
        CSL_FMK (EDMA3CC_OPT_TCC, _CSL_datStateStruct.tccNum) |
        CSL_FMKT (EDMA3CC_OPT_SYNCDIM, ABSYNC) |
        CSL_FMKT (EDMA3CC_OPT_STATIC, STATIC);

    param->SRC = (Uint32) (src);
    
    param->A_B_CNT = CSL_FMK (EDMA3CC_A_B_CNT_ACNT, lineLen) |
        CSL_FMK (EDMA3CC_A_B_CNT_BCNT, lineCnt);
        
    param->DST = (Uint32) (dst);
    
    if (type == DAT_2D2D) {
        param->SRC_DST_BIDX =
            CSL_FMK (EDMA3CC_SRC_DST_BIDX_DSTBIDX,
            linePitch) | CSL_FMK (EDMA3CC_SRC_DST_BIDX_SRCBIDX, linePitch);
    }
    else {
        if (type == DAT_1D2D) {
            param->SRC_DST_BIDX =
                CSL_FMK (EDMA3CC_SRC_DST_BIDX_DSTBIDX,
                linePitch) | CSL_FMK (EDMA3CC_SRC_DST_BIDX_SRCBIDX, lineLen);
        }
        else {
            if (type == DAT_2D1D) {
                param->SRC_DST_BIDX = 
                    CSL_FMK (EDMA3CC_SRC_DST_BIDX_DSTBIDX, lineLen) |
                    CSL_FMK (EDMA3CC_SRC_DST_BIDX_SRCBIDX, linePitch);
            }
        }
    }

    param->LINK_BCNTRLD = CSL_FMK (EDMA3CC_LINK_BCNTRLD_LINK, 0xFFFF);
    param->CCNT = 0x00000001;
    
    _CSL_datStateStruct.pending = TRUE;
    
    _restore_interrupts (cs);
    
    return _CSL_datStateStruct.tccNum;
}

/** ============================================================================
 *   @n@b DAT_setPriority 
 *
 *   @b Description
 *   @n Sets the priority bit value PRI of OPT register. The priority value 
 *      can be set by using the type CSL_DatPriority. 
 *
 *   @b Arguments
     @verbatim
            priority         priority value
     @endverbatim
 *
 *   <b> Return Value </b>  
 *   @n None
 *
 *   <b> Pre Condition </b> 
 *   @n  DAT_open must be successfully invoked prior to this call.
 *
 *   <b> Post Condition </b>
 *   @n  OPT register is set for the priority value
 *
 *   @b Modifies
 *   @n OPT register   
 *
 *   @b Example
 *   @verbatim
        DAT_Setup datSetup;
        Uint8 dst2d[8][20];
        Uint8 src1d[8*16];
    
        datSetup.qchNum = CSL_DAT_QCHA0;
        datSetup.regionNum = CSL_DAT_REGION_GLOBAL ;
        datSetup.tccNum = 1;
        datSetup.paramNum = 0 ;
        datSetup.priority = CSL_DAT_PRI_0;
    
        DAT_open(&datSetup);
        ...
        DAT_setPriority(CSL_DAT_PRI_3); 

     @endverbatim
 *  ============================================================================
 */
#pragma CODE_SECTION (DAT_setPriority, ".text:csl_section:dat");
void DAT_setPriority (
    Int    priority
)
{
    Uint32 cs;

    if (_CSL_datStateStruct.pending)
        DAT_wait (_CSL_datStateStruct.tccNum);
        
    cs = _disable_interrupts ();
    
    /* The que entry number mapping */
    /* The numbers 4 and 2 used to calculate the MSB and LSB of qdma Qnumber */
    CSL_FINSR (((CSL_Edma3ccRegsOvly) CSL_EDMA3CC_0_REGS)->QDMAQNUM,
        _CSL_datStateStruct.qchNum * 4 + 2,
        _CSL_datStateStruct.qchNum * 4, priority);
    
    _CSL_datStateStruct.priority = priority;
    
    _restore_interrupts (cs);
}
