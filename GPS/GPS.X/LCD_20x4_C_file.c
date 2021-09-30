/*
 * LCD_20x4_C_file.c
 * http://www.electronicwings.com
 *
 */

#include<xc.h>
#include "LCD_20x4_H_file.h"						/* Include LCD header file */


void LCD_Command (char cmd)							/* LCD command write function */
{
	LCD_Data_Port = cmd;							/* Write command data to LCD data port */
	RS = 0;                                			/* Make RS LOW (command reg.), RW LOW (Write) */
	RW = 0;
    EN = 1;					/* High to Low transition on EN (Enable) */
	NOP();
	EN = 0;
	MSdelay(3);									/* Wait little bit */
}

void LCD_Char (char char_data)						/* LCD data write function */
{
	LCD_Data_Port = char_data;						/* Write data to LCD data port */
	RS = 1;                                			/* Make RS LOW (command reg.), RW LOW (Write) */
	RW = 0;
    EN = 1;					/* High to Low transition on EN (Enable) */
	NOP();
	EN = 0;
	MSdelay(3);									/* Wait little bit */									/* Wait little bit */
}

void LCD_Init (void)								/* LCD Initialize function */
{
	LCD_Command_Dir = 0;		/* Make LCD command port direction as o/p */
	LCD_Data_Dir = 0;							/* Make LCD data port direction as o/p */
	
	MSdelay(20);									/* LCD power up time to get things ready, it should always >15ms */
	LCD_Command (0x38);								/* Initialize 16X2 LCD in 8bit mode */
	LCD_Command (0x0C);								/* Display ON, Cursor OFF command */
	LCD_Command (0x06);								/* Auto Increment cursor */
	LCD_Command (0x01);								/* Clear LCD command */
	MSdelay(3);
	LCD_Command (0x80);								/* 8 is for first line and 0 is for 0th position */
}

void LCD_String (const char *str)							/* Send string to LCD function */
{
	int i;
	while((*str)!=0)							/* Send each char of string till the NULL */
	{
		LCD_Char (*str);							/* Call LCD data write */
        str++;
    }
}

void LCD_String_xy (char row, char pos,const char *str)	/* Send string to LCD function */
{
	if (row == 1)
		LCD_Command((pos & 0x0F)|0x80);				/* Command of first row and required position<16 */
	else if (row == 2)
		LCD_Command((pos & 0x0F)|0xC0);				/* Command of Second row and required position<16 */
	else if (row == 3)
		LCD_Command((pos & 0x0F)|0x94);				/* Command of Third row and required position<16 */
	else if (row == 4)
		LCD_Command((pos & 0x0F)|0xD4);				/* Command of Fourth row and required position<16 */
	LCD_String(str);								/* Call LCD string function */
}

void LCD_Clear (void)								/* LCD clear function */
{
	LCD_Command (0x01);								/* Clear LCD command */
	MSdelay(3);
	LCD_Command (0x80);								/* 8 is for first line and 0 is for 0th position */
	MSdelay(1);
}

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }
