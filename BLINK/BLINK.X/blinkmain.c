/*!
\file   blink.c
\date   2021-09-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example Blink

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2021. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include <xc.h>
#include <pic16f887.h>
#include "config.h"

/*
unsigned char 8 bits, 0 - 255
char 8 bits -127 +127 (0 - 127)
byte 8 bits 0 - 255
boolean 8 bits (1 y 0)
int 16 bits 32 bits 
uint8_t
uint16_t
short 16 bits
float 32 bits
double 32 bits
long 32 bits
*/

#define INPUT 1
#define OUTPUT 0

#define ON 1
#define OFF 0

#define CFG_LED_RED TRISB7
#define LED_RED RB7

#define CFG_BTN_P1 TRISB0
#define BTN_P1 RB0

#define CFG_S1 TRISB0
#define S1 RB0
#define CFG_S2 TRISB1
#define S2 RB1
#define CFG_S3 TRISB2
#define S3 RB2

#define CFG_LED_SEC TRISD
#define LED_SEC PORTD

void delay_ms(int val_delay);
    
void main(){
    CFG_LED_RED = OUTPUT;
    CFG_LED_SEC = 0x00;  // 0B'00000000'
    //CFG_LED_SEC = 0b11111111;
    LED_SEC = 0b00000011; // 0x01
    CFG_BTN_P1 = INPUT;
    
    CFG_S1 = INPUT;
    CFG_S2 = INPUT;
    CFG_S3 = INPUT;
    
    ANSELH = 0x00;
    while(1){
        if((S1 == 1) && (S2 == 1) && (S3 == 0)){
            LED_RED = ON;
        }
        else if((S1 == 1) && (S2 == 1) && (S3 == 0)){
            LED_RED = ON;
        }
        else if((S1 == 1) && (S2 == 1) && (S3 == 0)){
            LED_RED = ON;
        }
        else{
            LED_RED = OFF;
        }
        
        
        
        if(BTN_P1 == 1){
            LED_RED = ON;
            LED_SEC = 0b00000000; // 0x01
        }
        else{
            LED_RED = OFF;
            LED_SEC = LED_SEC << 2;
            if(LED_SEC == 0x00){
                LED_SEC = 0b00000011; // 0x01
            }
            __delay_ms(500);
        }
        
        
        /*
        __delay_ms(500);
        LED_SEC = LED_SEC << 2;
        if(LED_SEC == 0x00){
            LED_SEC = 0b00000011; // 0x01
        }
        
        LED_RED = ON;
        __delay_ms(500);
        LED_RED = OFF;
        __delay_ms(500);
        */
    }
    
}

void secuencia_1(){
    
    while(1){
    __delay_ms(500);
    LED_SEC = LED_SEC << 2;
    if(LED_SEC == 0x00){
        LED_SEC = 0b00000011; // 0x01
    }
    }
}


void delay_ms(int val_delay){
    for(int i=0;i<val_delay;i++){
        for(int j=0;j<45;j++);
    }
}
