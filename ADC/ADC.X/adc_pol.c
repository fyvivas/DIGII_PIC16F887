#include    <xc.h>
#include    <pic16f887.h>

#include    "config.h"


void main(void) {
    TRISD = 0x00;// salida puerto D
    TRISA0 = 1;
    ANSEL = 0x01; //  Configura el Puerto como Entrada Anal�gica.
    
    ADCON1bits.ADFM = 0; //  Justificaci�n Izquierda (modo-8bits).
    ADCON1bits.VCFG0 = 0; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON1bits.VCFG1 = 0; //  Selecciona Voltajes de Referencia (5v-0v). 
  
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Anal�gico AN0.
    ADCON0bits.ADCS = 0b01; //  Tiempo de Conversi�n Fosc/8.
   
    while (1) {
        ADCON0bits.ADON = 1; //  Habilita el M�dulo AD.
        __delay_us(30);
        ADCON0bits.GO = 1; //  Inicia la COnversi� AD.
        while (ADCON0bits.GO); //  Espera a que termine la conversi�n AD.
        ADCON0bits.ADON = 0; //  Habilita el M�dulo AD.
        PORTD = ADRESH;
        __delay_ms(500);
    }
}


