/*!
\file   gpioinput.c
\date   2021-09-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example GPIO.

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

// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = ON         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <pic16f887.h>
#define _XTAL_FREQ 4000000//frecuencia del oscilador

void delay_ms(int);//prototipo de función para utilizar variables en 
                   //la función de los tiempos
void main(void) {
    TRISAbits.TRISA0=1;//el pin RA0 como entrada digital  
    TRISBbits.TRISB3=0;//el pin RB3 como salida digital
    TRISBbits.TRISB4=0;//el pin RB4 como salida digital
    
    PORTBbits.RB3=0;//el led en el pin RB3 inicia apagado
    PORTBbits.RB4=0;//el led en el pin RB4 inicia encendido
    
    while(1){
        if(PORTAbits.RA0==1){//si la entrada en el pin RA0 es un alto
            TRISBbits.TRISB3=~TRISBbits.TRISB3;//el pin RB3 cambia de estado
            TRISBbits.TRISB4=~TRISBbits.TRISB4;//el pin RB4 cambia de estado
            __delay_ms(100);
        }
        else{
            TRISBbits.TRISB3=~TRISBbits.TRISB3;//el pin RB3 cambia de estado
            TRISBbits.TRISB4=~TRISBbits.TRISB4;//el pin RB4 cambia de estado
            __delay_ms(1000);
        }
    }
    return;
}