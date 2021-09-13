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


void delay_ms(int val_delay);
    
void main(){
    CFG_LED_RED = OUTPUT;
    while(1){
        LED_RED = ON;
        __delay_ms(500);
        LED_RED = OFF;
        __delay_ms(500);
    }
    
}

void delay_ms(int val_delay){
    for(int i=0;i<val_delay;i++){
        for(int j=0;j<45;j++);
    }
}
