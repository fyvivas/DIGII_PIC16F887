#include    <xc.h>
#include    <pic16f887.h>
#include    "config.h"

unsigned int value_adc = 0;//16 bits
unsigned char counter_digito = 0;
double temp = 0.0;
unsigned char lm35 = 0;

void main(void) {
    //OSCCON = 0b01110001;
    OSCCON = 0x71;
    TRISD = 0x00;// salida puerto D
    TRISA0 = 1;
    ANSEL = 0x01; //  Configura el Puerto como Entrada Analógica.

    ADCON1bits.ADFM = 1; //  Justificación Derecha (modo-8bits).
    ADCON1bits.VCFG0 = 0; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON1bits.VCFG1 = 0;
    
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Analógico AN0.
    ADCON0bits.ADCS = 0b01; //  Tiempo de Conversión Fosc/8.
    
    ADCON0bits.ADON = 1; //  Habilita el Módulo AD.
    __delay_us(30);
    
    while (1) {
        
        ADCON0bits.GO_DONE = 1; //  Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        temp = (temp * 500.0) / 1023.0;
        lm35 = (char) temp;
        PORTD = (1 << 4) + (lm35 % 10);
        __delay_ms(50);
        PORTD = (1 << 5) + (lm35 / 10);
        __delay_ms(50);
    }
}
