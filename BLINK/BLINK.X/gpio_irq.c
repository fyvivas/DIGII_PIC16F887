/*!
\file   irq.c
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

#define CFG_LED_SEC TRISD
#define LED_SEC PORTD

   
void main(){
    CFG_LED_RED = OUTPUT;
    CFG_LED_SEC = 0x00;  // 0B'00000000'
    LED_SEC = 0b00000001; // 0x01
    CFG_BTN_P1 = INPUT;
  
    ANSELH = 0x00;
    
    INTCON= 0b11010000; //habilita el uso de las interrupciones
    
    //INTCONbits.GIE = 1;//habilita las interrupciones
    //INTCONbits.INTE =1;//habilita el uso de la interrupción externa
    //INTCONbits.INTF =0;//bandera a 0 para detectar las
                     //interrupciones externas
 
    OPTION_REGbits.INTEDG=1;//la interrupción externa en el pin ocurrirá 
                            //por flanco de subida
    
    while(1){
        
    }
    
}

void __interrupt() int_ext(){//rutina de atención a las interrupciones
    if(INTCONbits.INTF){//si la bandera de detección de la 
        LED_RED = ON;           //interrrrupción externa se pone a 1
        for(int i=0;i<8;i++){
            LED_SEC = LED_SEC << 1;
            if(LED_SEC == 0x00){
                LED_SEC = 0b00000001; // 0x01
            }
            __delay_ms(100);
        }
        INTCONbits.INTF=0;//bandera nuevamente a 0 para seguir detectando
                          //interrupciones externas
        LED_RED = OFF;
    }
    
}