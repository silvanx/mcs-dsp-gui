/*  ============================================================================
 *   Copyright (c) Texas Instruments Inc 2002, 2003, 2004, 2005                 
 *                                                                              
 *   Use of this software is controlled by the terms and conditions found in the
 *   license agreement under which this software has been supplied.             
 *   ===========================================================================
 */

/**
 *  @file  csl_intcGetHwStatus.c
 *
 *  @brief    File for functional layer of CSL API @a CSL_intcGetHwStatus()
 *
 *  PATH  $(CSLPATH)\src\intc
 */
 
/* =============================================================================
 *  Revision History
 *  ===============
 *  12-Jun-2004 Ruchika Kharwar File Created
 *
 *  16-Mar-2005 brn modified for doxygen documentation
 * =============================================================================
 */
 
#include <csl_intc.h>
#include <_csl_intc.h>
#include <csl_intcAux.h>

/** ============================================================================
 *   @n@b CSL_intcGetHwStatus
 *
 *   @b Description
 *   @n Queries the peripheral for status. The CSL_intcGetHwStatus(..) API
 *      could be used to retrieve status or configuration information from
 *      the peripheral. The user must allocate an object that would hold
 *      the retrieved information and pass a pointer to it to the function.
 *      The type of the object is specific to the query-command.
 *
 *   @b Arguments
 *   @verbatim
            hIntc           Handle identifying the event

            query           The query to this API of INTC which indicates the
                            status to be returned.

            answer          Placeholder to return the status.
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK               - Status info return successful
 *   @li                   CSL_ESYS_INVQUERY     - Invalid query
 *   @li                   CSL_ESYS_INVPARAMS    - Invalid parameter
 *
 *   <b> Pre Condition </b>
 *   @n  None
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 * @b Example:
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intStat;
            CSL_IntcParam               vectId;
            CSL_IntcObj                 intcObj20;
            CSL_IntcHandle              hIntc20;
            CSL_IntcEventHandlerRecord  recordTable[10];
            CSL_IntcGlobalEnableState   state;
            Uint32                      intrStat;
            
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK)
               exit;
            // Opening a handle for the Event 20 at vector id 4
            
            vectId = CSL_INTC_VECTID_4;
            hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , 
                                   NULL);
            
            // NMI Enable   
            CSL_intcGlobalNmiEnable();
            
            // Enable Global Interrupts 
            intStat = CSL_intcGlobalEnable(&state);
            
            do {
                CSL_intcGetHwStatus(hIntc20,CSL_INTC_QUERY_PENDSTATUS, \
                                    (void*)&intrStat);
            } while (!stat);
            
            // Close handle
            CSL_IntcClose(hIntc20);

    @endverbatim
 * =============================================================================
 */
#pragma CODE_SECTION (CSL_intcGetHwStatus, ".text:csl_section:intc");
CSL_Status  CSL_intcGetHwStatus (
    CSL_IntcHandle            hIntc,
    CSL_IntcHwStatusQuery     myQuery,
    void                      *answer
)
{


    CSL_Status status = CSL_SOK;
    
    if (hIntc && answer) {
        switch (myQuery) {
            case CSL_INTC_QUERY_PENDSTATUS:
                if (hIntc->vectId < CSL_INTC_VECTID_EXCEP) {
                    if (hIntc->eventId < 4)
                        *((Uint32*)answer) = \
                             (Uint32)(CSL_intcCombinedEventGet(hIntc->eventId));
                    else    
                        *((Bool*)answer) = \
                               (Bool)(CSL_intcQueryEventStatus(hIntc->eventId));
                }   
                break;  
            default:
                status = CSL_ESYS_INVQUERY;
                break;
        }       
    } 
    else
        status = CSL_ESYS_INVPARAMS;
        
    return status;
}

/** ============================================================================
 *   @n@b CSL_intcQueryDropStatus
 *
 *   @b Description
 *   @n Queries the peripheral for Drop status. The CSL_intcQueryDropStatus(..) 
 *      API could be used to retrieve drop status
 *
 *   @b Arguments
 *   @verbatim
            drop           Pointer to drop status structure
     @endverbatim
 *
 *   <b> Return Value </b> CSL_Status
 *   @li                   CSL_SOK               - Status info return successful
 *   @li                   CSL_ESYS_INVPARAMS    - Invalid handle
 *
 *   <b> Pre Condition </b>
 *   @n  CSL_intcInit(), CSL_intcOpen() must be invoked before this call
 *
 *   <b> Post Condition </b>
 *   @n  None
 *
 *   @b Modifies
 *   @n None
 *
 *   @b Example:
 *   @verbatim
            CSL_IntcContext             context; 
            CSL_Status                  intStat;
            CSL_IntcParam               vectId;
            CSL_IntcObj                 intcObj20;
            CSL_IntcHandle              hIntc20;
            CSL_IntcDropStatus          drop;
            CSL_IntcEventHandlerRecord  recordTable[10];
            CSL_IntcGlobalEnableState   state;
            Uint32                      intrStat;
            
            context.numEvtEntries = 10;
            context.eventhandlerRecord = &recordTable;
            
            // Init Module
            ...
            if (CSL_intcInit(&context) != CSL_SOK)
               exit;
            // Opening a handle for the Event 20 at vector id 4
            
            vectId = CSL_INTC_VECTID_4;
            hIntc20 = CSL_intcOpen (&intcObj20, CSL_INTC_EVENTID_20, &vectId , 
                                    NULL);
            
            // Drop Enable
            CSL_intHwControl(hIntc20,CSL_INTC_CMD_EVTDROPENABLE,NULL);
            // Query Drop status
            CSL_intcQueryDropStatus(&drop);
                
            // Close handle
            CSL_IntcClose(hIntc20);

    @endverbatim
 * =============================================================================
 */

#pragma CODE_SECTION (CSL_intcQueryDropStatus, ".text:csl_section:intc");
CSL_Status CSL_intcQueryDropStatus (
    CSL_IntcDropStatus      *drop        
)
{
    Uint32      dropVal;
    CSL_Status status = CSL_ESYS_INVPARAMS ;
    if (drop) {
        dropVal = ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->INTXSTAT;
        drop->drop = (Bool)(CSL_FEXT(dropVal,INTC_INTXSTAT_DROP));
        drop->eventId = (CSL_IntcEventId)(CSL_FEXT(dropVal,INTC_INTXSTAT_SYSINT));
        drop->vectId = (CSL_IntcVectId)(CSL_FEXT(dropVal,INTC_INTXSTAT_CPUINT));
        
        /* Clear the drop condition */
        ((CSL_IntcRegsOvly)CSL_INTC_0_REGS)->INTXCLR = 1;
        status = CSL_SOK;    
    } 
    return status;
}
