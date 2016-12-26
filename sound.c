#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "sound.h"

void setupSounds()
{
    REG_SOUNDCNT_X = SND_ENABLED;

	REG_SOUNDCNT_H = SND_OUTPUT_RATIO_100 | 
                     DSA_OUTPUT_RATIO_100 | 
                     DSA_OUTPUT_TO_BOTH | 
                     DSA_TIMER0 | 
                     DSA_FIFO_RESET |
                     DSB_OUTPUT_RATIO_100 | 
                     DSB_OUTPUT_TO_BOTH | 
                     DSB_TIMER1 | 
                     DSB_FIFO_RESET;

	REG_SOUNDCNT_L = 0;
}

void playSoundA( const unsigned char* sound, int length, int frequency, int loops) {
        dma[1].cnt = 0;
    
        int ticks = PROCESSOR_CYCLES_PER_SECOND/frequency;
    
        DMANow(1, sound, REG_FIFO_A, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);
    
        REG_TM0CNT = 0;
    
        REG_TM0D = -ticks;
        REG_TM0CNT = TIMER_ON;
    
        //TODO: FINISH THIS FUNCTION
        // Assign all the appropriate struct values
        soundA.data = sound;
        soundA.duration = ((VBLANK_FREQ * length) / frequency);
        soundA.frequency = frequency;
        soundA.length = length;
        soundA.isPlaying = 1;
        soundA.vbCount = 0;
        soundA.loops = loops;
        soundA.priority = 0;
}

void playSoundB( const unsigned char* sound, int length, int frequency, int loops) {
        dma[2].cnt = 0;

        int ticks = PROCESSOR_CYCLES_PER_SECOND/frequency;

        DMANow(2, sound, REG_FIFO_B, DMA_DESTINATION_FIXED | DMA_AT_REFRESH | DMA_REPEAT | DMA_32);

        REG_TM1CNT = 0;
    
        REG_TM1D = -ticks;
        REG_TM1CNT = TIMER_ON;
    
        // TODO: FINISH THIS FUNCTION
        // Assign all the appropriate struct values
        soundB.data = sound;
        soundB.duration = ((VBLANK_FREQ * length) / frequency);
        soundB.frequency = frequency;
        soundB.length = length;
        soundB.isPlaying = 1;
        soundB.vbCount = 0;
        soundB.loops = loops;
        soundB.priority = 0;
}


void pauseSound()
{
    // TODO: WRITE THIS FUNCTION
        soundA.isPlaying = 0;
        soundB.isPlaying = 0;
        REG_TM0CNT = 0;
        REG_TM1CNT = 0;     
}

void unpauseSound()
{
    // TODO: WRITE THIS FUNCTION
    soundA.isPlaying = 1;
    soundB.isPlaying = 1;
    REG_TM0CNT = TIMER_ON;
    REG_TM1CNT = TIMER_ON;
}

void stopSound()
{
    // TODO: WRITE THIS FUNCTION
    REG_TM0CNT = 0;
    REG_TM1CNT = 0;
    dma[1].cnt = 0;
    soundA.isPlaying = 0;
    soundB.isPlaying = 0;
}

void setupInterrupts()
{
    REG_IME = 0;
    // TODO: SET UP THE INTERRUPT HANDLER HERE
    // HINT: THERE IS A REGISTER THAT NEEDS TO POINT TO A INTERRUPT FUNCTION
    // HINT: THAT INTERRUPT FUNCTION HAS TO BE CAST TO SOMETHING...

    REG_INTERRUPT = (unsigned int) interruptHandler;//-----------------what function to call
    REG_IE |= INT_VBLANK;//---------------what to listen
    REG_DISPSTAT |= INT_VBLANK_ENABLE;//---------------what interrupt to call
    REG_IME = 1; //----------------------ON/OFF
}

void interruptHandler()
{
    REG_IME = 0;
    if(REG_IF & INT_VBLANK)
    {
        //TODO: FINISH THIS FUNCTION
        // This should be where you determine if a sound if finished or not
        if (soundA.isPlaying) {
            soundA.vbCount++;
            if (soundA.vbCount >= soundA.duration) {
                if (soundA.loops) {
                    playSoundA(soundA.data, soundA.length, soundA.frequency, 1);
                } else {
                    dma[1].cnt = 0;
                    soundA.isPlaying = 0;
                    REG_TM0CNT = 0;
                }
            }
        }
        if (soundB.isPlaying) {
            soundB.vbCount++;
            if (soundB.vbCount >= soundB.duration) {
                if (soundB.loops) {
                    playSoundB(soundB.data, soundB.length, soundB.frequency, 1);
                } else {
                    dma[2].cnt = 0;
                    soundB.isPlaying = 0;
                    REG_TM1CNT = 0;
                }
            }
        }
        REG_IF = INT_VBLANK; 
    }

    REG_IME = 1;
}