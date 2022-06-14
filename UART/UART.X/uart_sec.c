/*!
\file   uart.c
\date   2020-11-23
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example uart.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2020. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include <xc.h>
#include <pic16f887.h>  /*Header file PIC16f887 definitions*/
#include "fuses.h"

#define     BAUD        9600

unsigned char var = 0x31; //0x30 en hexadecimal, 48 en decimal

void main(void) {
    //Configura UART a 9600 baudios
    RC6 = 0; //  Pin RC6 como salida digital para TX.
    
    TXSTAbits.TX9 = 0; //  Modo-8bits.
    TXSTAbits.TXEN = 1; //  Habilita Transmisión.
    TXSTAbits.SYNC = 0; //  Modo-Asíncrono.
    TXSTAbits.BRGH = 0; //  Modo-Baja Velocidad de Baudios.
    BAUDCTLbits.BRG16 = 0; //  Baudios modo-8bits.
    RCSTAbits.SPEN = 1; //  Hbilita el Módulo SSP como UART.
    //  Escribe el valor necesario para configurar los Baudios a 9600.
    SPBRG = (unsigned char) (((_XTAL_FREQ / BAUD) / 64) - 1);
    while (1) {
        //  espera a que el registro de transmisión este disponible o vacio.
        while (!TXSTAbits.TRMT) {
        }
        //  escribe el dato que se enviará a través de TX.
        TXREG = var;
        
        
        //PORTCbits.RC0 = !PORTCbits.RC0;
        //if (++var > 122) { //  0,1,2,3,4.......122 (z))
            while (!TXSTAbits.TRMT) {
            }
            TXREG = 13;
        //    var = 48;
        //}
        
        __delay_ms(100);
    }
}

