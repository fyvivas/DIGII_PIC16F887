/* PIC16F887 USART Source File 
 * http://www.electronicwings.com
 */

#include "fuses.h"
#include "USART_Header_File.h"

/*****************************USART Initialization*******************************/
void USART_Init(long baud_rate)
{
    float temp;
    TRISC6=0;                       /*Make Tx pin as output*/
    TRISC7=1;                       /*Make Rx pin as input*/
    temp=(unsigned char) (((_XTAL_FREQ / baud_rate) / 64) - 1);    
    SPBRG=(int)temp;                /*baud rate=9600, SPBRG = (F_CPU /(64*9600))-1*/
    TXSTA=0x20;                     /*Transmit Enable(TX) enable*/ 
    RCSTA=0x90;                     /*Receive Enable(RX) enable and serial port enable */
}

#ifdef	SEND_UART

/******************TRANSMIT FUNCTION*****************************************/ 
void USART_TxChar(char out)
{        
        while(TXIF==0);            /*wait for transmit interrupt flag*/
        TXREG=out;                 /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/    
}
/*******************RECEIVE FUNCTION*****************************************/
char USART_RxChar()
{
   
    
    while(RCIF==0);                 /*wait for receive interrupt flag*/
    if(RCSTAbits.OERR)
    {           
        CREN = 0;
        NOP();
        CREN=1;
    }
    return(RCREG);                  /*receive data is stored in RCREG register and return to main program */
}

void USART_SendString(const char *out)
{
   while(*out!='\0')
   {            
        USART_TxChar(*out);
        out++;
   }
}

#endif