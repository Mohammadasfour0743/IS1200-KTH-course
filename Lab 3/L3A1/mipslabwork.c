/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  //part c
  volatile int* trise = (volatile int*) 0xbf886100;
  *trise = *trise & ~0xff;
  //part e
  TRISDSET = 0xFE0;
  
  return;
}

/* This function is called repetitively from the main program */
volatile int tickCount = 0;
void labwork( void )
{
  
  
  int swStatus = getsw();
  int btnStatus = getbtns();
  
    char btn2 = btnStatus & 0x1;
    char btn3 = (btnStatus >> 1) & 0x1;
    char btn4 = (btnStatus >> 2) & 0x1;

    if (btn2 == 1){
      mytime &= 0xFF0F;
      mytime |= (swStatus & 0x0F) << 4; // | is used to preserve the rest of the bits
    }
    if (btn3 == 1){
      mytime &= 0xF0FF;
      mytime |= (swStatus & 0x0F) << 8; 
    }
    if (btn4 == 1){
      mytime &= 0x0FFF;
      mytime |= (swStatus & 0x0F) << 12;
    }
  
  
  //part d
  volatile int* porte = (volatile int*) 0xbf886110;
  *porte &= ~0xff;

  *porte = tickCount;

  
 delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  tickCount += 1;
  display_image(96, icon);
  


}
