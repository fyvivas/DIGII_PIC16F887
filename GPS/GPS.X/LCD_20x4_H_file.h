/*
 * LCD_20x4_H_file.h
 * http://www.electronicwings.com
 *
 */

#ifndef LCD_20x4_H_H_					/* Define library H file if not defined */
#define LCD_20x4_H_H_

#include<pic16f887.h>

#define LCD_Data_Dir TRISB				/* Define LCD data port direction */
#define LCD_Command_Dir TRISC			/* Define LCD command port direction register */
#define LCD_Data_Port PORTB				/* Define LCD data port */
#define LCD_Command_Port PORTC			/* Define LCD data port */
#define EN RC2							/* Define Enable signal pin */
#define RW RC1							/* Define Read/Write signal pin */
#define RS RC0							/* Define Register Select (data reg./command reg.) signal pin */

void LCD_Command (char);				/* LCD command write function */
void LCD_Char (char);					/* LCD data write function */
void LCD_Init (void);					/* LCD Initialize function */
void LCD_String (const char*);				/* Send string to LCD function */
void LCD_String_xy (char,char,const char*);	/* Send row, position and string to LCD function */
void LCD_Clear (void);					/* LCD clear function */
void MSdelay(unsigned int);             /* delay function */

#endif									/* LCD_20x4_H_FILE_H_ */