/*******************************************************************************
* File Name: nIRQ.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_nIRQ_H) /* Pins nIRQ_H */
#define CY_PINS_nIRQ_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "nIRQ_aliases.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component cy_pins_v2_10 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 nIRQ__PORT == 15 && ((nIRQ__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

void    nIRQ_Write(uint8 value) ;
void    nIRQ_SetDriveMode(uint8 mode) ;
uint8   nIRQ_ReadDataReg(void) ;
uint8   nIRQ_Read(void) ;
uint8   nIRQ_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define nIRQ_DM_ALG_HIZ         PIN_DM_ALG_HIZ
#define nIRQ_DM_DIG_HIZ         PIN_DM_DIG_HIZ
#define nIRQ_DM_RES_UP          PIN_DM_RES_UP
#define nIRQ_DM_RES_DWN         PIN_DM_RES_DWN
#define nIRQ_DM_OD_LO           PIN_DM_OD_LO
#define nIRQ_DM_OD_HI           PIN_DM_OD_HI
#define nIRQ_DM_STRONG          PIN_DM_STRONG
#define nIRQ_DM_RES_UPDWN       PIN_DM_RES_UPDWN

/* Digital Port Constants */
#define nIRQ_MASK               nIRQ__MASK
#define nIRQ_SHIFT              nIRQ__SHIFT
#define nIRQ_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define nIRQ_PS                     (* (reg8 *) nIRQ__PS)
/* Data Register */
#define nIRQ_DR                     (* (reg8 *) nIRQ__DR)
/* Port Number */
#define nIRQ_PRT_NUM                (* (reg8 *) nIRQ__PRT) 
/* Connect to Analog Globals */                                                  
#define nIRQ_AG                     (* (reg8 *) nIRQ__AG)                       
/* Analog MUX bux enable */
#define nIRQ_AMUX                   (* (reg8 *) nIRQ__AMUX) 
/* Bidirectional Enable */                                                        
#define nIRQ_BIE                    (* (reg8 *) nIRQ__BIE)
/* Bit-mask for Aliased Register Access */
#define nIRQ_BIT_MASK               (* (reg8 *) nIRQ__BIT_MASK)
/* Bypass Enable */
#define nIRQ_BYP                    (* (reg8 *) nIRQ__BYP)
/* Port wide control signals */                                                   
#define nIRQ_CTL                    (* (reg8 *) nIRQ__CTL)
/* Drive Modes */
#define nIRQ_DM0                    (* (reg8 *) nIRQ__DM0) 
#define nIRQ_DM1                    (* (reg8 *) nIRQ__DM1)
#define nIRQ_DM2                    (* (reg8 *) nIRQ__DM2) 
/* Input Buffer Disable Override */
#define nIRQ_INP_DIS                (* (reg8 *) nIRQ__INP_DIS)
/* LCD Common or Segment Drive */
#define nIRQ_LCD_COM_SEG            (* (reg8 *) nIRQ__LCD_COM_SEG)
/* Enable Segment LCD */
#define nIRQ_LCD_EN                 (* (reg8 *) nIRQ__LCD_EN)
/* Slew Rate Control */
#define nIRQ_SLW                    (* (reg8 *) nIRQ__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define nIRQ_PRTDSI__CAPS_SEL       (* (reg8 *) nIRQ__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define nIRQ_PRTDSI__DBL_SYNC_IN    (* (reg8 *) nIRQ__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define nIRQ_PRTDSI__OE_SEL0        (* (reg8 *) nIRQ__PRTDSI__OE_SEL0) 
#define nIRQ_PRTDSI__OE_SEL1        (* (reg8 *) nIRQ__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define nIRQ_PRTDSI__OUT_SEL0       (* (reg8 *) nIRQ__PRTDSI__OUT_SEL0) 
#define nIRQ_PRTDSI__OUT_SEL1       (* (reg8 *) nIRQ__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define nIRQ_PRTDSI__SYNC_OUT       (* (reg8 *) nIRQ__PRTDSI__SYNC_OUT) 


#if defined(nIRQ__INTSTAT)  /* Interrupt Registers */

    #define nIRQ_INTSTAT                (* (reg8 *) nIRQ__INTSTAT)
    #define nIRQ_SNAP                   (* (reg8 *) nIRQ__SNAP)

#endif /* Interrupt Registers */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_nIRQ_H */


/* [] END OF FILE */
