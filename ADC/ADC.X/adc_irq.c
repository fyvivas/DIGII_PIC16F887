#include    <xc.h>
#include    <pic16f887.h>

#include    "config.h"


void main(void) {
    TRISD = 0x00;// salida puerto D
    TRISA0 = 1;
    ANSEL = 0x00; //  Configura el Puerto como Entrada Analógica.
    
    INTCON= 0b11000000; //habilita el uso de las interrupciones
    PIE1bits.ADIE = 1;//el bit 6 del registro PIE1 habilita la irq del ADC
    PIR1bits.ADIF=0;//El bit 6 del registro PIR la bandera del ADC
    
    
    ADCON1bits.ADFM = 0; //  Justificación Izquierda (modo-8bits).
    ADCON1bits.VCFG0 = 0; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON1bits.VCFG1 = 0; //  Selecciona Voltajes de Referencia (5v-0v). 
  
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Analógico AN0.
    ADCON0bits.ADCS = 0b01; //  Tiempo de Conversión Fosc/8.
    
   
    while (1) {
        ADCON0bits.ADON = 1; //  Habilita el Módulo AD.
        __delay_us(30);
        ADCON0bits.GO_DONE = 1; //  Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
    }
}

void interrupt adc_irq(void){
    if(PIR1bits.ADIF == 1){
        ADCON0bits.ADON = 0;
        PORTD = ADRESH;
        PIR1bits.ADIF=0;//El bit 6 del registro PIR a 0 para que vuelvan a ocurrir mas interrupciones del ADC
    }
} 
    
}



