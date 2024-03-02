/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   this file was modified by Mohammad Asfour and Sami Al Saati in 1/3/2024

   For copyright and licensing, see file COPYING */


#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
int menu = 1;
int page = 0;
int speed = 0;
int spawn2 = 0;
int score = 0;

static unsigned long int next = 1;

void ssrand(unsigned int seed){
	next = seed;
}

char diffdis[] = "dif    text, texttexttext"; //to display difficulty

char clear[] = " ";

char line1[] = " Welcome Aboard";
char line2[] = "   3 - start";
char line3[] = "Difficulty: ";

char lost1[] = "   YOU DIED";
char lost2[] = "Your Score:";
char lost3[] = "  3 - continue";

char won1[] = "VICTORY ACHIEVED";
int win;

int gameOver = 0;

int timeout = 0;
int diff = 1;
/* Interrupt Service Routine */
void user_isr( void )
{

  if (IFS(0) & (1<<8)) { //interrupt flag. activated when an interrupt is detected. 8th bit is the important one
    
    IFS(0) = 0;
	
	timeout++;
	speed++;
	spawn2++;

	//winning screen, written by Sami Al Saati
	win = hasWon(score); // checks if count has reached 15s, will enter loop
    while (win){
      T2CONCLR = 0x8000;
      display_string(0, won1);  
	  display_string(3, lost3);
      display_update();
	  
      if (getbtns() == 0x2){
		win = 0;
        
        menu = 1;
		speed = 0;
		spawn2 = 0;
		score = 0;
		PORTE &= ~0xff;
		page = 0;
		
        int i;
        for (i = 0; i < 512; i++){
          battlefield[i] = Reset[i];
        }
        delay(200);
        T2CONSET = 0x8000;
      }  
    }

	//gameOver screen, written by Mohammad Asfour
	gameOver = crash(page);
    while (gameOver){
      T2CONCLR = 0x8000;
      display_string(0, lost1); 
	  display_string(1, lost2);
	  display_string(2, itoaconv(score)); 
	  display_string(3, lost3);
      display_update();
	  
      if (getbtns() == 0x2){
        gameOver = 0;
        menu = 1;
		speed = 0;
		spawn2 = 0;
		score = 0;
		PORTE &= ~0xff;
		page = 0;
		
        int i;
        for (i = 0; i < 512; i++){
          battlefield[i] = Reset[i];
        }
        delay(200);
        T2CONSET = 0x8000;
      }  
    }

	//menu screen, written by Mohammad Asfour
	while(menu){
      T2CONCLR = 0x8000;
	  display_string(0, line1);
      display_string(3, line2);
	  display_string(1, line3);
	  time2string(diffdis, diff);
	  display_string(2, diffdis);
      display_update();

	  switch (getbtns()) {
		case 0x1:
			if (diff > 1){
				diff -= 1;
				delay(200);
			}
			break;

		case 0x4:
			if (diff < 3){
				diff += 1;
				delay(200);
			}
	  }

      if (getbtns() == 0x02){
        display_string(0, clear);
        display_string(1, clear);
		display_string(2, clear);
		display_string(3, clear);
        menu = 0;
        T2CONSET = 0x8000;
		display_image(0, battlefield); 
      }
    }
		/*difficulty system written by Mohammad Asfour*/

	    
		switch (diff) {
		case 1:
			if (speed == 5){		
				rocketsmove();
				speed = 0;			
			}
			if (spawn2 == 10){			
				rocketsspawn(rand() % 4);
				spawn2 = 0;			
			}
			break;
		
		case 2:
			if (speed == 2){
				
				rocketsmove();
				speed = 0;				
			}
			if (spawn2 == 4){
				rocketsspawn(rand() % 4);	
				spawn2 = 0;
			}
			break;
		case 3:
			if (speed == 1){
				rocketsmove();
				speed = 0;	
			}
			if (spawn2 == 2){
				rocketsspawn(rand() % 4);
				spawn2 = 0;
				
			}
	}
	 
  } 
	//Score system, written by Sami Al Saati
	if (timeout == 10){ 
		score++;
		PORTE = score;
		timeout = 0;
	}

  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
	/*all initialization was done in Lab 3 of the course*/

   //part c
  volatile int* trise = (volatile int*) 0xbf886100;
  *trise = *trise & ~0xff;
  PORTE &= ~0xff;
  //part e
  TRISDSET = 0xFE0;


 T2CON = 0x8070; // control register: prescale = 256, bit 15 is on
 PR2 = 31250; // Period register: 80 000 000/256/10 (10 is the number of timeouts per second)
 TMR2 = 0; //to start from 0
//seed initialzation for rand()
 ssrand(TMR2);

 IEC(0) |= 1 << 8; //to enable interrupts for timer 2. bit 8 of this register corresponds to timer2 enabler. | is used to preserve the rest of bits

 IPC(2) |= 0x28; //set priority to 7. bits 2-4 correspond to Timer2, set them to 111.

 IFS(0) = 0;//clear interrupt flag so no previous interrupt is handle when interrupts are enabled

  enable_interrupt(); //enable interrupt globally. code found in labwork.s
  return;  
  
}

/* This function is called repetitively from the main program ###############################################################################################*/
void labwork( void )
{

	//button input, written by Mohammad Asfour and Sami Al Saati
  switch (getbtns())
  {
  case 0x4: //move up if page is not at the top
    if (page > 0){
      page--;
      moveup(page);
      delay(150); 
    }
    break;

  case 0x1: //move down if the page is not at the bottom
    if (page < 3) {
      page++;
      movedown(page);
      delay(150);  
    }
    break;
  }
  
	//Switch input, written by Mohammad Asfour 
  if (getsw() == 0x1){
	 speed = 0;
	  spawn2 = 0;
	  page = 0;
	  score = 0;
	  PORTE &= ~0xff;
	  int i;
	  for (i = 0; i < 512; i++){
          battlefield[i] = Reset[i];
        }
	menu = 1;		
  }
}

/*random system based on the linear congruential generator. Written by Mohammad Asfour*/
int rand(void) {
	next = next * 1664525 + 1013904223;
	return (unsigned int)(next / 65536) % 36685;
}


