/*!
\file   temporizador.c
\date   2021-19-22
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example temporizador.

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

#include    <xc.h>
#include    <pic16f887.h> //Header file PIC16f887 definitions
#include    "fuses.h"   //Header file Configurations bits Settings

//#define _XTAL_FREQ 1000000L

unsigned char count = 0;
unsigned char count_ms = 0;

int main(void) {
    
    TRISB0 = 0;  		//pinRB0 como salida digital, se colocará el led
    PORTB = 0;  		//El led se inicia apagado y parpadea cada 500ms
    ANSELH = 0x00;
    
    INTCONbits.GIE = 0;
    OPTION_REGbits.T0CS = 0;//mode temporizador
    OPTION_REGbits.PSA = 0; // prescaler enable
    OPTION_REGbits.PS = 0b111; // prescaler 256
    TMR0 = 60;
    
    TRISD = 0x00;
    PORTD = 0x00;
    
    TRISA4 = 1;//reset del contador
    ANSEL = 0x00;//digital
    
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    while (1) {
        //LATD = ((count / 10) << 4) + (count % 10);
        PORTD = (1 << 5) + (count % 10);
        __delay_ms(20);
        PORTD = (1 << 4) + (count / 10);
        __delay_ms(20);
        
        
        if (!PORTAbits.RA4) {
            __delay_ms(50);
            count = 0;
            TMR0 = 60;
            INTCONbits.T0IF = 0;
        }
    }
    return 1;
}

void interrupt ISR_TIMER_0(void) {
    if (INTCONbits.T0IE && INTCONbits.T0IF) {
        PORTB = ~PORTB;
        count_ms++;
        if(count_ms == 20){
            if (++count == 100) {
                count = 0;
            }
            count_ms = 0;
        }
        TMR0 = 60;
        INTCONbits.T0IF = 0;
    }
}

