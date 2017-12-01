/* gameRunning.c
   Written by johvh & davidjo2.
*/

#include <stdint.h>
#include <pic32mx.h>
#include "gameHeader.h"

int timeoutcount = 0;
int lastNumber = 0;  // last number generated by getRandomInt

/* Interrupt Service Routine */
void user_isr( void ) {
    if (timeoutcount>9 && (IFS(0) & 0x100)>>8) {
        PORTE += 1;
        timeoutcount = 0;
    }
    IFS(0) &= 0xFFFFFEFF;
    timeoutcount++;
}

/*
* Generate random integer depending
* on how many switches are activated
* @param switchAmount
* @return random int
*/
/*
int getRandomInt(int switchAmount){
    int random = lastNumber;
    while(lastNumber == random){
        switch(switchAmount){
            case 2:
                random = rand() % 4;
                break;
            case 3:
                random = rand() % 5 + 3;
                break;
            case 4:
                random = rand() % 11 + 5;
                break;
        }
    }
    lastNumber = random;
    return random;
}
*/

/**
 * set memory with a val
*/
void gameScreen(int val, int size) {
    unsigned char hex[16] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
    int upsideDownIndex = ((31 - upsideDownValue)/8) + 1;
    int i;
    for (i = 0; i < size; i++) {
        if(i >= ((upsideDownIndex * 128) - 128) && i < (upsideDownIndex * 128)){
            dataArray[i] = hex[((31 - upsideDownValue) % 8)];
        } else{
            dataArray[i] = 0;
        }
    }
}

/**
 * Update game, this is the game loop.
 */
void updateRunning() {
    gameScreen(0,512);
    entities_update();
    display_update();
}
