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
int prime = 1234567;
char textstring[] = "text, more text, and even more text!";
int timeout = 0;
/* Interrupt Service Routine */
void user_isr( void )
{

   if (IFS(0) & (1<<8)) { //interrupt flag. activated when an interrupt is detected. 8th bit is the important one
    timeout++;
    IFS(0) = 0;

     if (timeout >= 10) {

   timeout = 0;
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  return;
 }
  } 

}

/* Lab-specific initialization goes here */
void labinit( void )
{

 

 T2CON = 0x8070; // prescale = 256. bit 15 is on
 PR2 = 31250; // Period register: 80 000 000/256/10 (10 is the number of timeouts per second)
 TMR2 = 0; //start from zero

  IEC(0) |= 1 << 8; //to enable interrupts for timer 2. bit 8 of this register corresponds to timer2 enabler. | is used to preserve the rest of bits

  IPC(2) |= 0x28; //set priority to 7. bits 2-4 correspond to Timer2, set them to 111.

  IFS(0) = 0;//clear interrupt flag so no previous interrupt is handle when interrupts are enabled


  enable_interrupt(); //enable interrupt globally. code found in labwork.s
  return;
}

/* This function is called repetitively from the main program */

void labwork( void )
{

  prime = nextprime( prime );
 display_string( 0, itoaconv( prime ) );
 display_update();


}
