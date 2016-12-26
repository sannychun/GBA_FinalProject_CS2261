#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"

typedef struct{
    const unsigned char* data;
    int length;
    int frequency;
    int isPlaying;
    int loops;
    int duration;
    int priority;
    int vbCount;
}SOUND;

SOUND soundA;
SOUND soundB;

void setupSounds();
void playSoundA( const unsigned char* sound, int length, int frequency, int loops);
void playSoundB( const unsigned char* sound, int length, int frequency, int loops);
void pauseSound();
void unpauseSound();
void stopSound();

void setupInterrupts();
void interruptHandler();

//const unsigned char* spaceSound;
//int* spaceSoundLen;
//int spaceSoundToPlay = 0;