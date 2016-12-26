#include "myLib.h"

unsigned short *videoBuffer = (u16 *)0x6000000;

unsigned short *frontBuffer = (u16 *)0x6000000;
unsigned short *backBuffer =  (u16 *)0x600A000;

DMA *dma = (DMA *)0x40000B0;


//This function is to be used ONLY IF we are setting up a map with a custom palette index
void loadMap(const unsigned short * map, unsigned short mapLen, unsigned short palIndex, unsigned short sbb)
{
	//We are editing the actual map data, so this array is what we are going to use to replace the existing oen
	unsigned short newMap[mapLen];

	//We are going to iterate through every entry in this new map, and edit the entry to use a custom palette
	for(int i = 0; i < mapLen; i++)
	{
		// Here we mask the value in the current spot so we don't lose information
		unsigned short mask = map[i] & ~(PALBANK(0xF));
		newMap[i] = mask | PALBANK(palIndex);
	}
	// Finally we DMA in the new map to the appropriate sbb
	DMANow(3, newMap, &SCREENBLOCKBASE[sbb], mapLen);
}

void setPixel3(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row, col, SCREENWIDTH)] = color;
}

void drawRect3(int row, int col, int height, int width, unsigned short color)
{
	volatile unsigned short c = color;
	
	int i;
	for(i = 0; i < height; i++)
	{
		DMANow(3, &c, &videoBuffer[OFFSET(row+i, col, SCREENWIDTH)], (width) | DMA_SOURCE_FIXED);
	}
}

void drawImage3(const unsigned short* image, int row, int col, int height, int width)
{
	int i;
	for(i = 0; i < height; i++)
	{
		DMANow(3, &image[OFFSET(i,0, width)], &videoBuffer[OFFSET(row+i, col, SCREENWIDTH)], (width));
	}
}

void fillScreen3(unsigned short color)
{
	volatile unsigned short c = color;

	DMANow(3, &c, videoBuffer, (240*160) | DMA_SOURCE_FIXED);
	
}

void setPixel4(int row, int col, unsigned char colorIndex)
{
	unsigned short pixels = videoBuffer[OFFSET(row, col, SCREENWIDTH)/2];

	if(col & 1) // odd
	{
		pixels &= 0xFF;
		videoBuffer[OFFSET(row, col, SCREENWIDTH)/2] = pixels | colorIndex << 8;
	}
	else // even
	{
		pixels &= 0xFF << 8;
		videoBuffer[OFFSET(row, col, SCREENWIDTH)/2] = pixels | colorIndex;
	}
}

void drawRect4(int row, int col, int height, int width, unsigned char colorIndex)
{
	volatile unsigned short pixels = colorIndex << 8 | colorIndex;

	int r;
	for(r = 0; r < height; r++)
	{
		if(col & 1) // odd starting col
		{
			setPixel4(row+r, col, colorIndex);

			if(width & 1) // if width is odd
			{
				DMANow(3, &pixels, &videoBuffer[OFFSET(row + r, (col+1)/2, SCREENWIDTH/2)], (width/2) | DMA_SOURCE_FIXED);
			}
			else  // width is even
			{
				DMANow(3, &pixels, &videoBuffer[OFFSET(row + r, (col+1)/2, SCREENWIDTH/2)], ((width/2)-1) | DMA_SOURCE_FIXED);
				setPixel4(row+r, col+width - 1, colorIndex);
			}
		}
		else // even starting col
		{
			DMANow(3, &pixels, &videoBuffer[OFFSET(row + r, col/2, SCREENWIDTH/2)], (width/2) | DMA_SOURCE_FIXED);	
			if(width & 1) // if width is odd
			{
				setPixel4(row+r, col+width - 1, colorIndex);
			}
		}
	}	
}

void fillScreen4(unsigned char colorIndex)
{
	volatile unsigned short pixels = colorIndex << 8 | colorIndex;
	DMANow(3, &pixels, videoBuffer, 19200 | DMA_SOURCE_FIXED);
}

void drawBackgroundImage4(const unsigned short* image)
{
	DMANow(3, image, videoBuffer, 19200);
}

void drawImage4(const unsigned short* image, int row, int col, int height, int width)
{
	int r;
	for(r = 0; r < height; r++)
	{
		DMANow(3, &image[OFFSET(r,0,width)/2], &videoBuffer[OFFSET(row + r, col, SCREENWIDTH)/2], width/2);
	}
}

void loadPalette(const unsigned short* palette)
{
	DMANow(3, palette, PALETTE, 256);
}


void DMANow(int channel, volatile const void* source, volatile const void* destination, unsigned int control)
{
	dma[channel].src = source;
	dma[channel].dst = destination;
	dma[channel].cnt = DMA_ON | control;
}

void waitForVblank()
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}


void flipPage()
{
    if(REG_DISPCTL & BACKBUFFER)
    {
        REG_DISPCTL &= ~BACKBUFFER;
        videoBuffer = backBuffer;
    }
    else
    {
        REG_DISPCTL |= BACKBUFFER;
        videoBuffer = frontBuffer;
    }
}

