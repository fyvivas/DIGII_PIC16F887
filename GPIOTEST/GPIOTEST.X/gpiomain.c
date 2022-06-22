/*!
\file   Gpio_Main.c
\date   2020-11-18
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example GPIO.

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

// CONFIG1
#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#define _XTAL_FREQ 8000000//frecuencia del oscilador


#include <xc.h>
#include <pic16f887.h>  /*Header file PIC18f4550 definitions*/

/*
#define INPUT 1
#define OUTPUT 0

#define s1 TRISBbits.TRISB7
#define s2 TRISBbits.TRISB6
#define s3 TRISBbits.TRISB5
#define s4 TRISBbits.TRISB4

#define s1_read PORTBbits.RB7
#define s2_read PORTBbits.RB6
#define s3_read PORTBbits.RB5
#define s4_read PORTBbits.RB4

#define ON_LED 1
#define OFF_LED 0
*/

int main(void) {
    OSCCON=0x71;       /* Use internal oscillator of 8MHz Frequency */
    //Configura los pines RD7-RD6-RD5-RD4 como salida digital
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD4 = 0;
    //Configura los pines RB7-RB6-RB5-RB4 como entrada digital
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB4 = 1;
    
    //ANSELH = 0x00;
    
    while (1) {
        if(!PORTBbits.RB4){
            PORTDbits.RD4=1;
        }
        else{
            PORTDbits.RD4=0;
        }
        if(!PORTBbits.RB5){PORTDbits.RD5=1;}else{PORTDbits.RD5=0;}
        if(!PORTBbits.RB6){PORTDbits.RD6=1;}else{PORTDbits.RD6=0;}
        if(!PORTBbits.RB7){PORTDbits.RD7=1;}else{PORTDbits.RD7=0;}
    }
    return 1;
}

