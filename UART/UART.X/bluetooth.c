/*!
\file   bluetooth.c
\date   2020-11-23
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example bluetooth HC-05.

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
#include <pic16f887.h>  /*Header file PIC18f4550 definitions*/
#include "fuses.h"

void USART_Init(long);
void USART_TransmitChar(char);
void USART_SendString(const char *);
char USART_ReceiveChar();

#define _XTAL_FREQ  8000000L

#define F_CPU 8000000/64
//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)

#define LED PORTD

void main()
{
    char data_in;
    TRISD = 0;                /* set PORT as output port */
    USART_Init(9600);         /* initialize USART operation with 9600 baud rate */ 
    __delay_ms(50);
    while(1)
    {
        data_in=USART_ReceiveChar();
        if(data_in=='1')
        {   
            LED = 0x00;                    /* turn ON LED */
            USART_SendString("LED_ON"); /* send LED ON status to terminal */
        }
        else if(data_in=='2')
                
        {
            LED = 0xFF;                    /* turn OFF LED */
            USART_SendString("LED_OFF");/* send LED ON status to terminal */
        }
        else
        {
            USART_SendString(" select 1 or 2");/* send msg to select proper option */
        }
        __delay_ms(100);
    
    }
    
}


/*****************************USART Initialization*******************************/
void USART_Init(long baud_rate)
{
    float temp;
    TRISC6=0;                       /*Make Tx pin as output*/
    TRISC7=1;                       /*Make Rx pin as input*/
    temp=Baud_value;     
    SPBRG=(int)temp;                /*baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    TXSTA=0x20;                     /*Transmit Enable(TX) enable*/ 
    RCSTA=0x90;                     /*Receive Enable(RX) enable and serial port enable */
}
/******************TRANSMIT FUNCTION*****************************************/ 
void USART_TransmitChar(char out)
{        
        while(TXIF==0);            /*wait for transmit interrupt flag*/
        TXREG=out;                 /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/    
}
/*******************RECEIVE FUNCTION*****************************************/
char USART_ReceiveChar()
{

    while(RCIF==0);                 /*wait for receive interrupt flag*/
    return(RCREG);                  /*receive data is stored in RCREG register and return to main program */
}

void USART_SendString(const char *out)
{
   while(*out!='\0')
   {            
        USART_TransmitChar(*out);
        out++;
   }
}

