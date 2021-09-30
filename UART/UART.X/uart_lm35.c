#include <xc.h>
#include <pic16f887.h>  /*Header file PIC18f4550 definitions*/
#include "fuses.h"

//#define _XTAL_FREQ  8000000L

char buffer_TX[] = "Temp: xxx grados\r";
int value_adc;
double temp;
char lm35;

void main(void) {

    //Configura UART a 9600 baudios
    RC6 = 0; //  Pin RC6 como salida digital para TX.
    TXSTAbits.TX9 = 0; //  Modo-8bits.
    TXSTAbits.TXEN = 1; //  Habilita Transmisión.
    TXSTAbits.SYNC = 0; //  Modo-Asíncrono.
    TXSTAbits.BRGH = 0; //  Modo-Baja Velocidad de Baudios.
    BAUDCTLbits.BRG16 = 0; //  Baudios modo-8bits.
    RCSTAbits.SPEN = 1; //  Hbilita el Módulo SSP como UART.
    SPBRG = (unsigned char) (((_XTAL_FREQ / 9600) / 64) - 1); //baudios  = 9600


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
        //Inicia el proceso de conversión ADC.
        ADCON0bits.GO_DONE = 1; //Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        temp = (temp * 500.0) / 1023.0;
        lm35 = (char) temp;
        buffer_TX[6] = (lm35 / 100) + '0';
        buffer_TX[7] = (lm35 % 100) / 10 + '0';
        buffer_TX[8] = (lm35 % 100) % 10 + '0';
        //Inicia el proceso de transmisión TX.
        for (int i = 0; i < 17; i++) {
            //  espera a que el registro de transmisión este disponible o vacio.
            while (!TXSTAbits.TRMT) {
            }
            //  escribe el dato que se enviará a través de TX.
            TXREG = buffer_TX[i];
        }
        __delay_ms(100);
    }
}

