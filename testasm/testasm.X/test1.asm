
; PIC16F887 Configuration Bit Settings

; ASM source line config statements

#include "p16F887.inc"

; CONFIG1
; __config 0xECF2
 __CONFIG _CONFIG1, _FOSC_HS & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_OFF & _IESO_ON & _FCMEN_ON & _LVP_OFF
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF


     LIST p=16F887
     
var1 equ 0x20
 
    org	0x00

    MOVLW .25
    MOVWF var1
    

CONFIG_LED
    NOP
    INCFSZ var1,1
    goto CONFIG_LED
    nop
    
    end