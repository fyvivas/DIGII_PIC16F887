; PIC16F887 Configuration Bit Settings

; ASM source line config statements

#include "p16F887.inc"

; CONFIG1
; __config 0xEFF1
 __CONFIG _CONFIG1, _FOSC_XT & _WDTE_OFF & _PWRTE_OFF & _MCLRE_ON & _CP_OFF & _CPD_OFF & _BOREN_ON & _IESO_ON & _FCMEN_ON & _LVP_OFF
; CONFIG2
; __config 0xFFFF
 __CONFIG _CONFIG2, _BOR4V_BOR40V & _WRT_OFF

    LIST p=16F887

var	equ	0x20	; Registro F
var2	equ	0x21    
count	equ	0x22
    
    org	0x00
    goto INIT

INIT
    ;BANK 0
    BCF STATUS,RP0
    BCF STATUS,RP1
    MOVLW 0x03
    MOVWF var
    BTFSS PORTB,0
    GOTO INIT
    
ESCAPE
    MOVLW 0x5
    MOVWF var2    
    MOVLW 0x8
    MOVWF count
    
LOOP
    MOVLW 0x03
    MOVWF var
    DECFSZ count,1
    GOTO LOOP
    
ESCAPE1
    MOVLW 0x5
    MOVWF var2
    XORWF PORTB,0
    BTFSS STATUS,Z
    GOTO ESCAPE1
    MOVLW 0x4
    MOVWF var2
    CLRF count
    
LOOP_INC
    INCF count,1
    MOVLW 0x0A
    XORWF count,0
    BTFSS STATUS,Z
    GOTO LOOP_INC
    MOVLW 0x7
    MOVWF var2
    
    
    END