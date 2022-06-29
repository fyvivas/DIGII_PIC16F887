/*!
\file   KEYPAD.c
\date   2022-06-08
\author Fulvio Vivas <fyvivas@unicauca.edu.co>
\brief  Handler Keypad 4x4.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2022. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include <xc.h>
#include "KEYPAD.h"
#include "CONFIG.h"

/*F**************************************************************************
* NAME: keypad_init
*----------------------------------------------------------------------------
* PARAMS:   none
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Initialize KEYPAD 4x4
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/

void keypad_init(void){
   
    PTECLADO &= ~(1<<PB0) & ~(1<<PB1) & ~(1<<PB2) & ~(1<<PB3);   // FILAS    - SALIDA
    PTECLADO |= (1<<PB4) | (1<<PB5) | (1<<PB6) | (1<<PB7);       // COLUMNAS - ENTRADA
    OPTION_REGbits.nRBPU = 0;   //   PORTB pull-ups are enabled by individual port latch values 
}

/*F**************************************************************************
* NAME: keypad_getkey
*----------------------------------------------------------------------------
* PARAMS:   none
* return:   KEY Pressed in KEYPAD
*----------------------------------------------------------------------------
* PURPOSE:
* Get KEY
*----------------------------------------------------------------------------
* NOTE:
* 
*****************************************************************************/
char keypad_getkey(void){

char letras[4][4]={  {'1','2','3','A'},
                     {'4','5','6','B'},
                     {'7','8','9','C'},
                     {'*','0','#','D'}};
int  i=0;
char valor=0;

for(i=0;i<4;i++){

   if(i==0){

      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(1<<ROW3)|(1<<ROW2)|(0<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[0][0];}   //1
      while (!(COLUMNAS & (1<<COL2))){valor=letras[0][1];}   //2
      while (!(COLUMNAS & (1<<COL3))){valor=letras[0][2];}   //3
      while (!(COLUMNAS & (1<<COL4))){valor=letras[0][3];}   //A
   }

   if(i==1){
      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(1<<ROW3)|(0<<ROW2)|(1<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[1][0];}   //4
      while (!(COLUMNAS & (1<<COL2))){valor=letras[1][1];}   //5
      while (!(COLUMNAS & (1<<COL3))){valor=letras[1][2];}   //6
      while (!(COLUMNAS & (1<<COL4))){valor=letras[1][3];}   //B
   }

   if(i==2){
      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(1<<ROW4)|(0<<ROW3)|(1<<ROW2)|(1<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[2][0];}   //7
      while (!(COLUMNAS & (1<<COL2))){valor=letras[2][1];}   //8
      while (!(COLUMNAS & (1<<COL3))){valor=letras[2][2];}   //9
      while (!(COLUMNAS & (1<<COL4))){valor=letras[2][3];}  //C
   }

   if(i==3){
      FILAS = (1<<COL4)|(1<<COL3)|(1<<COL2)|(1<<COL1)|(0<<ROW4)|(1<<ROW3)|(1<<ROW2)|(1<<ROW1);
      __delay_us(100);
      while (!(COLUMNAS & (1<<COL1))){valor=letras[3][0];}   //*
      while (!(COLUMNAS & (1<<COL2))){valor=letras[3][1];}   //0
      while (!(COLUMNAS & (1<<COL3))){valor=letras[3][2];}   //+
      while (!(COLUMNAS & (1<<COL4))){valor=letras[3][3];}   //D
      }
   }

   return valor;
}


