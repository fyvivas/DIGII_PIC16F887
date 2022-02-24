/*!
\file   reloj.c
\date   2022-02-24
\author Fulvio Vivas <fyvivas@unicauca.edu.co>
\brief  Reloj digital with PIC16F887 using Timer1 with Interrupt Service Routine ISR.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2022. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include "fuses.h"		/* Configuration header file */
#include <xc.h>
#include <pic16f887.h>  /*Header file PIC18f4550 definitions*/

unsigned char flag_run = 0;
unsigned char counter_digito = 0;
unsigned int counter_segundos = 0;
unsigned char counter_20ms = 0;

int main(void) {
    INTCONbits.GIE = 0; //Deshabilita la interrupción global
    //T1CONbits.RD16 = 1; //Timer1 en modo 16bits
    T1CONbits.TMR1CS = 0; //Timer1 reloj interno = Fosc÷4
    T1CONbits.T1CKPS = 0b01; //Timer1 prescaler = 2
    TMR1H = 0xD8; //Registro TMR1 =  55535
    TMR1L = 0xEF;
    T1CONbits.TMR1ON = 1; //Timer1 ON
    PIR1bits.TMR1IF = 0; //Borra flag de TIMER1
    PIE1bits.TMR1IE = 1; //Habilita interrupción TIMER1
    INTCONbits.PEIE = 1; //Habilitara interrupción periféricas
    INTCONbits.GIE = 1; //Habilita interrupción global
    TRISD = 0; //PORTD como salida digital
    TRISA0 = 1;
    TRISA1 = 1;
    ANSEL = 0x00;//digital
    //CMCON = 0x07;
    while (1) {
        if (!PORTAbits.RA0) {
            __delay_ms(50);
            flag_run = !flag_run;
            while (!PORTAbits.RA0);
            __delay_ms(50);
        }
        if (!PORTAbits.RA1) {
            __delay_ms(50);
            counter_segundos = 0;
            flag_run = 0;
        }
    }
    return 1;
}

void interrupt ISR_TIMER_1(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        TMR1H = 0xD8;
        TMR1L = 0xEF;

        if (++counter_20ms == 100 && flag_run) {
            counter_20ms = 0;
            if (++counter_segundos == 3600) {
                counter_segundos = 0;
            }
        }

        switch (counter_digito) {
            case 0:
                PORTD = (counter_digito << 4) + (counter_segundos / 60) / 10;
                counter_digito = 1;
                break;
            case 1:
                PORTD = (counter_digito << 4) + (counter_segundos / 60) % 10;
                counter_digito = 2;
                break;
            case 2:
                PORTD = (counter_digito << 4) + (counter_segundos % 60) / 10;
                counter_digito = 3;
                break;
            case 3:
                PORTD = (counter_digito << 4) + (counter_segundos % 60) % 10;
                counter_digito = 0;
                break;
        }

        PIR1bits.TMR1IF = 0;
    }
}

