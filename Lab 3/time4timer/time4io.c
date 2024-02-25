#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h" 


int getsw( void ) {
    int swStatus = (PORTD >> 8) & 0x000F;
    
    return swStatus;
}

int getbtns(void) {
    int btns = (PORTD >> 5) & 0x7;
    return btns;
}

