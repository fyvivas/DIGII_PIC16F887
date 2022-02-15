
#include "HCSR04_lib.h"

void hcsr04_init(){
    TRISB1 = 0; //Trigger pin of US sensor is sent as output pin
    TRISB2 = 1; //Echo pin of US sensor is set as input pin       
    TRISB3 = 0; //RB3 is output pin for LED
    
    T1CON=0x20;
    
}

int hcsr04_read(void){

    int time_taken;
    di();//disable interrupt
    TMR1H =0; TMR1L =0; //clear the timer bits
    
        Trigger = 1; 
        __delay_us(10);           
        Trigger = 0;  
        
        while (Echo==0);
            TMR1ON = 1;
        while (Echo==1);
            TMR1ON = 0;
        
        time_taken = (TMR1L | (TMR1H<<8)); 

        ei();//enable interrupt
        return time_taken;
}    