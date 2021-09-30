
/* PIC16F887 USART Header File 
 * http://www.electronicwings.com
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef USART_HEADER_FILE_H
#define	USART_HEADER_FILE_H

#include <pic16f887.h>
#include <xc.h>
void USART_Init(long);
void USART_TxChar(char);
void USART_SendString(const char *);
char USART_RxChar();

#define F_CPU 8000000/64
//#define Baud_value(baud_rate) (((float)(F_CPU)/(float)baud_rate)-1)
#define Baud_value (((float)(F_CPU)/(float)baud_rate)-1)

#endif	/* USART_HEADER_FILE_H */

