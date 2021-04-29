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
CHIGH	equ	127	
CLOW	equ	64	
	
    org	0x00
    goto INIT

INIT
    ;BANK 0
    BCF STATUS,RP0
    BCF STATUS,RP1
    CLRF PORTB ;PORTB = 0X00
    BSF STATUS, RP0 ; BANK1
    MOVLW B?11111000? ;Set RB<7:3> as inputs and RB<2:0> as outputs
    MOVWF TRISB 
    BSF STATUS, RP1
    MOVLW B?00101010? ;ANSELH = 0X2A 
    MOVWF ANSELH
    ;BANK 0
    BCF STATUS,RP0
    BCF STATUS,RP1
    
    
    GOTO LED_VERDE
    GOTO LED_ROJO
    GOTO LED_AMARILLO
    
    
LED_VERDE
    BSF PORTB,2
    BCF PORTB,0
    BCF PORTB,1
    
LED_ROJO
    BSF PORTB,0
    BCF PORTB,2
    BCF PORTB,1
    
    
LED_AMARILLO
    BSF PORTB,1
    BCF PORTB,2
    BCF PORTB,0
    
    movlw 0x03
    ADDLW 0x04
    MOVWF VAR
    NOP
    MOVLW 0xB5
    XORLW 0xAF
    NOP
    MOVLW 0xB5
    XORLW 0xB5
    NOP
    goto result
    
result    
    MOVWF VAR
   end