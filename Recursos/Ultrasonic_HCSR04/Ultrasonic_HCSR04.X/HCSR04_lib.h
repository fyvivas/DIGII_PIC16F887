/* 
 * File:   HCSR04_lib.h
 * Author: ASUS
 *
 * Created on 4 de octubre de 2021, 08:09 AM
 */

#ifndef HCSR04_LIB_H
#define	HCSR04_LIB_H

#ifdef	__cplusplus
extern "C" {
#endif

#define _XTAL_FREQ 20000000
#include <xc.h>
#define Trigger RB1 //34 is Trigger
#define Echo RB2//35 is Echo 
    
void hcsr04_init();
int hcsr04_read(void);


#ifdef	__cplusplus
}
#endif

#endif	/* HCSR04_LIB_H */

