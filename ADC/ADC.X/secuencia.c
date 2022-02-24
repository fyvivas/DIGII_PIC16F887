#include    <xc.h>
#include    <pic16f887.h>
#include    "config.h"

void main (void){
    OSCCON = 0x71;
    TRISD = 0x00;
    PORTD = 0x81;
    __delay_ms(500);
    
    while(1){
        PORTD = 0xF0;
        __delay_ms(500);
        for(int i=0;i<8;i++){
            PORTD = 1 << i;
            __delay_ms(500);
        }
        PORTD = 0xAA;
        __delay_ms(500);
        
    }
}
