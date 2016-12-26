    /*****************************************
	This game is a Metal-Gear esque top-down 
	action game. The player has to pick up a 
	codec and reach the  exit door without 
	alerting the guards.

	NOTE:
	-Guards' vision reach quite far. Make sure to stay out of their line of sight!
	-Retrieving the codec is necessary to progress to the next level. If not, the next state will not be triggered.
	-Activating Cheat Mode will produce a sound.

	BUGS:
	-Not a bug necessarily, but I wanted to have a delay after the "!" sound and before transitioning to LOSE state.

	COOL STUFF:
	-Faithfulness to the original game (Codex dialogues, sounds from the original MGS)
	-There is a story
	-Smooth player movements
    ******************************************/
#include <stdio.h>
#include <stdlib.h>
#include "myLib.h"
#include "main.h"
#include "game.h"
#include "level1.h"
#include "level2.h"
#include "level1collision.h"
#include "level2collision.h"
#include "startscreen.h"
#include "instructions.h"
#include "storyscreen1.h"
#include "storyscreen2.h"
#include "storyscreen3.h"
#include "storyscreen4.h"
#include "storyscreen5.h"
#include "pausescreen.h"
#include "losescreen.h"
#include "winscreen.h"
#include "sprites.h"
#include "sound.h"
#include "openingtheme.h"
#include "crashsound.h"
#include "callsound.h"
#include "instructionstheme.h"
#include "level1audio.h"
#include "codecsound.h"
#include "wintheme.h"
#include "losetheme.h"
#include "alertsound.h"
#include "cheatsound.h"

int main()
{
	state = START;
	initStart();

	setupInterrupts();
	setupSounds();

	while(1)
	{
		oldButtons = buttons;
		buttons = BUTTONS;

		switch(state) {
			case START:
				updateStart();
				break;
			case STORY1:
				updateStory1();
				break;
			case STORY2:
				updateStory2();
				break;
			case STORY3:
				updateStory3();
				break;	
			case STORY4:
				updateStory4();
				break;		
			case STORY5:
				updateStory5();
				break;										
			case INSTRUCTIONS:
				updateInstructions();
				break;
			case LEVEL1:
				updateLevel1();
				break;
			case LEVEL2:
				updateLevel2();
				break;
			case PAUSE1:
				updatePause1();
				break;
			case PAUSE2:
				updatePause2();
				break;
			case LOSE:
				updateLose();
				break;
			case WIN:
				updateWin();
				break;
		}
	}
	return 0;
}

/**
Initializes Splash screen
**/
void initStart() {
	REG_DISPCTL = MODE4 | BG2_ENABLE;
	loadPalette(startscreenPal);
	drawBackgroundImage4(startscreenBitmap);
	playSoundA(openingtheme,OPENINGTHEMELEN,OPENINGTHEMEFREQ, 1);
}

/**
Proceeds to Instructions
**/
void updateStart() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		stopSound();
		playSoundA(crashsound,CRASHSOUNDLEN,CRASHSOUNDFREQ, 0);
		state = STORY1;
		initStory1();
	}
}

/**
This is the story screen with the helicopter.
**/
void initStory1() {
	loadPalette(storyscreen1Pal);
	drawBackgroundImage4(storyscreen1Bitmap);
}
void updateStory1() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		stopSound();
		playSoundB(callsound,CALLSOUNDLEN,CALLSOUNDFREQ, 0);
		state = STORY2;
		initStory2();
	}
}

/**
This is the beginning part of the codex dialogue with the Colonel
**/
void initStory2() {
	loadPalette(storyscreen2Pal);
	drawBackgroundImage4(storyscreen2Bitmap);
}
void updateStory2() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		stopSound();
		state = STORY3;
		initStory3();
	}	
}

/**
Codex dialogue continued
**/
void initStory3() {
	loadPalette(storyscreen3Pal);
	drawBackgroundImage4(storyscreen3Bitmap);
}
void updateStory3() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		state = STORY4;
		initStory4();
	}	
}

/**
Codex dialogue continued
**/
void initStory4() {
	loadPalette(storyscreen4Pal);
	drawBackgroundImage4(storyscreen4Bitmap);
}
void updateStory4() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		state = STORY5;
		initStory5();
	}	
}

/**
Codex dialogue continued
**/
void initStory5() {
	loadPalette(storyscreen5Pal);
	drawBackgroundImage4(storyscreen5Bitmap);
}
void updateStory5() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		playSoundA(instructionstheme,INSTRUCTIONSTHEMELEN,INSTRUCTIONSTHEMEFREQ, 1);
		state = INSTRUCTIONS;
		initInstructions();
	}	
}

/**
Initializes Instructions screen
**/
void initInstructions() {
	loadPalette(instructionsPal);
	drawBackgroundImage4(instructionsBitmap);
}

/**
Proceeds to Game 
OR
Goes back to Splash Screen
**/
void updateInstructions() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		state = LEVEL1;
		initLevel1();
	}
	if (BUTTON_PRESSED(BUTTON_SELECT)) {
		state = START;
		initStart();
	}	
}

/**
Initializes Pause screen
**/
void initPause() {
	loadPalette(pausescreenPal);
	drawBackgroundImage4(pausescreenBitmap);
}

/**
Proceeds to Game 
OR
Returns to Splash screen
**/
void updatePause1() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		state = LEVEL1;
		resumeLevel1();
	}

	if (BUTTON_PRESSED(BUTTON_SELECT)) {
		state = START;
		initStart();
	}
}

//Pause function for Level 2
void updatePause2() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		state = LEVEL2;
		resumeLevel2();
	}

	if (BUTTON_PRESSED(BUTTON_SELECT)) {
		state = START;
		initStart();
	}
}

/**
Initializes Lose screen
**/
void initLose() {
	loadPalette(losescreenPal);
	drawBackgroundImage4(losescreenBitmap);
}

/**
Proceeds to Splash screen
**/
void updateLose() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		state = START;
		initStart();
	}
}

/**
Initializes Win screen
**/
void initWin() {
	loadPalette(winscreenPal);
	drawBackgroundImage4(winscreenBitmap);
}

/**
Proceeds to Splash screen
**/
void updateWin() {
	if (BUTTON_PRESSED(BUTTON_START)) {
		state = START;
		initStart();
	}	
}

/**
Initializes player position and dimension.
**/
void initPlayer() {
	snake.width = 16;
	snake.height = 16;
	snake.rdel = 10;
	snake.cdel = 10;
	snake.bigRow = 80;
	snake.bigCol = 20;
	snake.row = 240/2-snake.width/2;
	snake.col = 70/2-snake.height/2;
	snake.aniCounter = 0;
	snake.currFrame = 0;
	snake.aniState = SNAKEFRONT;
	snake.isDetected = 0;
	snake.cheatMode = 0;
}

void initCodec1() {
	codec.width = 16;
	codec.height = 16;
	codec.rdel = 1;
	codec.cdel = 1;
	codec.bigRow = 312;
	codec.bigCol = 260;
	codec.aniCounter = 0;
	codec.currFrame = 10;
	codec.isActive = 1;
}

void initCodec2() {
	codec.width = 16;
	codec.height = 16;
	codec.rdel = 1;
	codec.cdel = 1;
	codec.bigRow = 496;
	codec.bigCol = 352;
	codec.aniCounter = 0;
	codec.currFrame = 10;
	codec.isActive = 1;
}

/**
Initializes enemies for Level 1.
**/
void initEnemies1() {
	for (int i = 0; i < 7; i++) {
		enemies[i].frameDirection = 1;
	}
	enemies[0].width = 16;
	enemies[0].height = 16;
	enemies[0].rdel = 1;
	enemies[0].cdel = 1;
	enemies[0].bigRow = 58;
	enemies[0].bigCol = 308;
	enemies[0].aniCounter = 0;
	enemies[0].currFrame = 0;
	enemies[0].aniState = ENEMYBACK;

	enemies[1].width = 16;
	enemies[1].height = 16;
	enemies[1].rdel = 1;
	enemies[1].cdel = 1;
	enemies[1].bigRow = 50;
	enemies[1].bigCol = 50;
	enemies[1].aniCounter = 0;
	enemies[1].currFrame = 0;
	enemies[1].aniState = ENEMYBACK;

	enemies[2].width = 16;
	enemies[2].height = 16;
	enemies[2].rdel = 1;
	enemies[2].cdel = 1;
	enemies[2].bigRow = 194;
	enemies[2].bigCol = 200;
	enemies[2].aniCounter = 0;
	enemies[2].currFrame = 0;
	enemies[2].aniState = ENEMYBACK;

	enemies[3].width = 16;
	enemies[3].height = 16;
	enemies[3].rdel = 1;
	enemies[3].cdel = 1;
	enemies[3].bigRow = 445;
	enemies[3].bigCol = 256;
	enemies[3].aniCounter = 0;
	enemies[3].currFrame = 0;
	enemies[3].aniState = ENEMYBACK;

	enemies[4].width = 16;
	enemies[4].height = 16;
	enemies[4].rdel = 1;
	enemies[4].cdel = 1;
	enemies[4].bigRow = 453;
	enemies[4].bigCol = 441;
	enemies[4].aniCounter = 0;
	enemies[4].currFrame = 0;
	enemies[4].aniState = ENEMYBACK;

	enemies[5].width = 16;
	enemies[5].height = 16;
	enemies[5].rdel = 1;
	enemies[5].cdel = 1;
	enemies[5].bigRow = 285;
	enemies[5].bigCol = 380;
	enemies[5].aniCounter = 0;
	enemies[5].currFrame = 0;
	enemies[5].aniState = ENEMYBACK;

	enemies[6].width = 16;
	enemies[6].height = 16;
	enemies[6].rdel = 1;
	enemies[6].cdel = 1;
	enemies[6].bigRow = 58;
	enemies[6].bigCol = 470;
	enemies[6].aniCounter = 0;
	enemies[6].currFrame = 0;
	enemies[6].aniState = ENEMYBACK;
}

//Initializes sprite positions for Level 2
void initEnemies2() {
	enemies[0].width = 16;
	enemies[0].height = 16;
	enemies[0].rdel = 1;
	enemies[0].cdel = 1;
	enemies[0].bigRow = 55;
	enemies[0].bigCol = 205;
	enemies[0].aniCounter = 0;
	enemies[0].currFrame = 0;
	enemies[0].aniState = ENEMYFRONT;

	enemies[1].width = 16;
	enemies[1].height = 16;
	enemies[1].rdel = 1;
	enemies[1].cdel = 1;
	enemies[1].bigRow = 140;
	enemies[1].bigCol = 297;
	enemies[1].aniCounter = 0;
	enemies[1].currFrame = 0;
	enemies[1].aniState = ENEMYFRONT;

	enemies[2].width = 16;
	enemies[2].height = 16;
	enemies[2].rdel = 1;
	enemies[2].cdel = 1;
	enemies[2].bigRow = 466;
	enemies[2].bigCol = 399;
	enemies[2].aniCounter = 0;
	enemies[2].currFrame = 0;
	enemies[2].aniState = ENEMYFRONT;

	enemies[3].width = 16;
	enemies[3].height = 16;
	enemies[3].rdel = 1;
	enemies[3].cdel = 1;
	enemies[3].bigRow = 281;
	enemies[3].bigCol = 423;
	enemies[3].aniCounter = 0;
	enemies[3].currFrame = 0;
	enemies[3].aniState = ENEMYFRONT;

	enemies[4].width = 16;
	enemies[4].height = 16;
	enemies[4].rdel = 1;
	enemies[4].cdel = 1;
	enemies[4].bigRow = 96;
	enemies[4].bigCol = 116;
	enemies[4].aniCounter = 0;
	enemies[4].currFrame = 0;
	enemies[4].aniState = ENEMYFRONT;

	enemies[5].width = 16;
	enemies[5].height = 16;
	enemies[5].rdel = 1;
	enemies[5].cdel = 1;
	enemies[5].bigRow = 176;
	enemies[5].bigCol = 174;
	enemies[5].aniCounter = 0;
	enemies[5].currFrame = 0;
	enemies[5].aniState = ENEMYFRONT;

	enemies[6].width = 16;
	enemies[6].height = 16;
	enemies[6].rdel = 1;
	enemies[6].cdel = 1;
	enemies[6].bigRow = 70;
	enemies[6].bigCol = 470;
	enemies[6].aniCounter = 0;
	enemies[6].currFrame = 0;
	enemies[6].aniState = ENEMYFRONT;
}

/**
This is where Level 1 is drawn.
IMPORTANT: Enemies/codec have not been implemented yet.
**/
void initLevel1()
{
	REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
	REG_BG0CNT = CBB(0) | SBB(25) | BG_SIZE3 | COLOR256;
	
	loadPalette(level1Pal);
	DMANow(3, level1Tiles, &CHARBLOCKBASE[0], level1TilesLen/2);
	DMANow(3, level1Map, &SCREENBLOCKBASE[25], level1MapLen/2);
	
	DMANow(3, spritesTiles, &CHARBLOCKBASE[4], spritesTilesLen/2);
    DMANow(3, spritesPal, SPRITE_PALETTE, spritesPalLen/2);
	
	hideSprites();
	
	hOff = 9;
	vOff = 96;

	initPlayer();
	initCodec1();
	initEnemies1();

	playSoundA(level1audio,LEVEL1AUDIOLEN,LEVEL1AUDIOFREQ, 1);
}

/**
This is where Level 2 is drawn
**/
void initLevel2() {
	REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
	REG_BG0CNT = CBB(0) | SBB(25) | BG_SIZE3 | COLOR256;
	
	loadPalette(level2Pal);
	DMANow(3, level2Tiles, &CHARBLOCKBASE[0], level2TilesLen/2);
	DMANow(3, level2Map, &SCREENBLOCKBASE[25], level2MapLen/2);
	
	DMANow(3, spritesTiles, &CHARBLOCKBASE[4], spritesTilesLen/2);
    DMANow(3, spritesPal, SPRITE_PALETTE, spritesPalLen/2);
	
	hideSprites();
	
	hOff = 9;
	vOff = 96;

	initPlayer();
	initCodec2();
	initEnemies2();
}

/**
* This is for resuming Level 1 after pausing. This makes sure that the character stays at the current spot and does not go back to his initial position.
*/
void resumeLevel1() {
	REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
	REG_BG0CNT = CBB(0) | SBB(25) | BG_SIZE3 | COLOR256;
	
	loadPalette(level1Pal);
	DMANow(3, level1Tiles, &CHARBLOCKBASE[0], level1TilesLen/2);
	DMANow(3, level1Map, &SCREENBLOCKBASE[25], level1MapLen/2);
	
	DMANow(3, spritesTiles, &CHARBLOCKBASE[4], spritesTilesLen/2);
    DMANow(3, spritesPal, SPRITE_PALETTE, spritesPalLen/2);
	
	hideSprites();
}

/**
Same as resumeLevel2
**/
void resumeLevel2() {
	REG_DISPCTL = MODE0 | BG0_ENABLE | SPRITE_ENABLE;
	REG_BG0CNT = CBB(0) | SBB(25) | BG_SIZE3 | COLOR256;

	loadPalette(level2Pal);
	DMANow(3, level2Tiles, &CHARBLOCKBASE[0], level2TilesLen/2);
	DMANow(3, level2Map, &SCREENBLOCKBASE[25], level2MapLen/2);
	
	DMANow(3, spritesTiles, &CHARBLOCKBASE[4], spritesTilesLen/2);
    DMANow(3, spritesPal, SPRITE_PALETTE, spritesPalLen/2);

   	hideSprites();
}

/**
Updates character movements and state switches in Level1.
**/ 
void updateLevel1()
{
	//Handle movement and collision logic using snake.bigRow and snake.bigCol
	if(BUTTON_HELD(BUTTON_UP))
	{
		//Move and check for collision
		if (((level1collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol, 512)] == BLUE)
			|| (level1collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol + snake.width - 1, 512)] == BLUE && snake.bigCol >= 0)) && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initLevel2();
			state = LEVEL2;
			hideSprites();
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level1collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol, 512)] == RED)
			|| (level1collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol + snake.width - 1, 512)] == RED && snake.bigCol >= 0)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		} 
		//Snakes stays inside the screen and does not go overboard
		if (level1collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol, 512)]
			&& level1collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol + snake.width - 1, 512)] && snake.bigCol >= 0) {
			if ((snake.row > SCREENHEIGHT / 2 || vOff == 0) && snake.row > 0) {
				snake.row--;
			} else if (vOff != 0) {
				vOff--;
			}
		}

	}
	if(BUTTON_HELD(BUTTON_DOWN))
	{
		//Move and check for collision
		if (((level1collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol, 512)] == BLUE)
			|| (level1collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol + snake.width - 1, 512)] == BLUE && snake.bigCol <= 512)) && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initLevel2();
			state = LEVEL2;
			hideSprites();
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level1collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol, 512)] == RED)
			|| (level1collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol + snake.width - 1, 512)] == RED && snake.bigCol <= 512)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		}
		//Snakes stays inside the screen and does not go overboard
		if (level1collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol, 512)]
			&& level1collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol + snake.width - 1, 512)] && snake.bigCol <= 512) {
			if ((snake.row < SCREENHEIGHT / 2 || vOff == 512 - SCREENHEIGHT) && snake.row < SCREENHEIGHT - snake.height) {
				snake.row++;
			} else if (vOff != 512 - SCREENHEIGHT) {
				vOff++;
			}
		}

	}
	if(BUTTON_HELD(BUTTON_LEFT))
	{
		//Move and check for collision
		if (((level1collisionBitmap[OFFSET(snake.bigRow, snake.bigCol - 1, 512)] == BLUE)
			|| (level1collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol - 1, 512)] == BLUE && snake.bigRow >= 0)) && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initLevel2();
			state = LEVEL2;
			hideSprites();
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level1collisionBitmap[OFFSET(snake.bigRow, snake.bigCol - 1, 512)] == RED)
			|| (level1collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol - 1, 512)] == RED && snake.bigRow >= 0)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		}
		//Snakes stays inside the screen and does not go overboard
		if (level1collisionBitmap[OFFSET(snake.bigRow, snake.bigCol - 1, 512)] && level1collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol - 1, 512)] && snake.bigRow >= 0) {
			if ((snake.col > SCREENWIDTH / 2 || hOff == 0) && snake.col > 0) {
				snake.col--;
			} else if (hOff != 0){
				hOff--;
			}
		}

	}
	if(BUTTON_HELD(BUTTON_RIGHT))
	{
		//Move and check for collision
		if (((level1collisionBitmap[OFFSET(snake.bigRow, snake.bigCol + snake.width, 512)] == BLUE)
			|| (level1collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol + snake.width, 512)] == BLUE && snake.bigRow <= 512)) && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initLevel2();
			state = LEVEL2;	
			hideSprites();		
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level1collisionBitmap[OFFSET(snake.bigRow, snake.bigCol + snake.width, 512)] == RED)
			|| (level1collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol + snake.width, 512)] == RED && snake.bigRow <= 512)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		}
		//Snakes stays inside the screen and does not go overboard
		if (level1collisionBitmap[OFFSET(snake.bigRow, snake.bigCol + snake.width, 512)] && level1collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol + snake.width, 512)] && snake.bigRow <= 512) {
			if ((snake.col < SCREENWIDTH / 2 || hOff == 512 - SCREENWIDTH) && snake.col < SCREENWIDTH - snake.width) {
				snake.col++;
			} else if (hOff != 512 - SCREENWIDTH) {
				hOff++;
			}
		}
	
	}

	//PAUSE state
	if (BUTTON_PRESSED(BUTTON_START)) {
		REG_DISPCTL = MODE4 | BG2_ENABLE;
		state = PAUSE1;
		initPause();
	}

	/**
	CHEAT MODE
	**/
	if (BUTTON_PRESSED(BUTTON_A)) {
		playSoundB(cheatsound, CHEATSOUNDLEN, CHEATSOUNDFREQ,0);
		snake.cheatMode = 1;	
	}
	
	REG_BG0HOFS = hOff;
	REG_BG0VOFS = vOff;

	//Updates snake's world position based on its row/col movement
	snake.bigRow = snake.row + vOff;
	snake.bigCol = snake.col + hOff;

	codec.row = codec.bigRow - vOff;
	codec.col = codec.bigCol - hOff;
	
	//This makes sure the enemies stay in their spots regardless of screen movement
	for (int i = 0; i < 7; i++) {
		enemies[i].row = enemies[i].bigRow - vOff;
		enemies[i].col = enemies[i].bigCol - hOff;		
	}

	animatePlayer();
	animateEnemies();
	updateOAM();
	DMANow(3, shadowOAM, OAM, 512);
	waitForVblank();

	//Cheat mode. Only triggered when the player pressed the A Button.
	if (snake.cheatMode == 0) {
		checkDetection();
		if (snake.isDetected == 1) {
			gameOver();
		}		
	}
}

/**
Updates character movements & state switches in Level2
**/
void updateLevel2()
{
	//Handle movement and collision logic using snake.bigRow and snake.bigCol
	if(BUTTON_HELD(BUTTON_UP))
	{
		//Move and check for collision
		if (level2collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol, 512)] == BLUE
			&& level2collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol + snake.width - 1, 512)] == BLUE && snake.bigCol >= 0 && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initWin();
			state = WIN;
			playSoundA(wintheme, WINTHEMELEN, WINTHEMEFREQ, 0);
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level2collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol, 512)] == RED)
			|| (level2collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol + snake.width - 1, 512)] == RED && snake.bigCol >= 0)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		} 
		//Snakes stays inside the screen and does not go overboard
		if (level2collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol, 512)]
			&& level2collisionBitmap[OFFSET(snake.bigRow - 1 , snake.bigCol + snake.width - 1, 512)] && snake.bigCol >= 0) {
			if ((snake.row > SCREENHEIGHT / 2 || vOff == 0) && snake.row > 0) {
				snake.row--;
			} else if (vOff != 0) {
				vOff--;
			}
		}

	}
	if(BUTTON_HELD(BUTTON_DOWN))
	{
		//Move and check for collision
		if (level2collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol, 512)] == BLUE
			&& level2collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol + snake.width - 1, 512)] == BLUE && snake.bigCol <= 512 && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initWin();
			state = WIN;
			playSoundA(wintheme, WINTHEMELEN, WINTHEMEFREQ, 0);
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level2collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol, 512)] == RED)
			|| (level2collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol + snake.width - 1, 512)] == RED && snake.bigCol <= 512)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		}
		//Snakes stays inside the screen and does not go overboard
		if (level2collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol, 512)]
			&& level2collisionBitmap[OFFSET(snake.bigRow + snake.height, snake.bigCol + snake.width - 1, 512)] && snake.bigCol <= 512) {
			if ((snake.row < SCREENHEIGHT / 2 || vOff == 512 - SCREENHEIGHT) && snake.row < SCREENHEIGHT - snake.height) {
				snake.row++;
			} else if (vOff != 512 - SCREENHEIGHT) {
				vOff++;
			}
		}

	}
	if(BUTTON_HELD(BUTTON_LEFT))
	{
		//Move and check for collision
		if (level2collisionBitmap[OFFSET(snake.bigRow, snake.bigCol - 1, 512)] == BLUE
			&& level2collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol - 1, 512)] == BLUE && snake.bigRow >= 0 && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initWin();
			state = WIN;
			playSoundA(wintheme, WINTHEMELEN, WINTHEMEFREQ, 0);
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level2collisionBitmap[OFFSET(snake.bigRow, snake.bigCol - 1, 512)] == RED)
			|| (level2collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol - 1, 512)] == RED && snake.bigRow >= 0)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		}
		//Snakes stays inside the screen and does not go overboard
		if (level2collisionBitmap[OFFSET(snake.bigRow, snake.bigCol - 1, 512)] && level2collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol - 1, 512)] && snake.bigRow >= 0) {
			if ((snake.col > SCREENWIDTH / 2 || hOff == 0) && snake.col > 0) {
				snake.col--;
			} else if (hOff != 0){
				hOff--;
			}
		}

	}
	if(BUTTON_HELD(BUTTON_RIGHT))
	{
		//Move and check for collision
		if (level2collisionBitmap[OFFSET(snake.bigRow, snake.bigCol + snake.width, 512)] == BLUE
			&& level2collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol + snake.width, 512)] == BLUE && snake.bigRow <= 512 && (codec.isActive == 0)) {
			REG_DISPCTL = MODE4 | BG2_ENABLE;
			initWin();
			state = WIN;	
			playSoundA(wintheme, WINTHEMELEN, WINTHEMEFREQ, 0);		
		}
		//Codec collision
		//If the player steps on the red part on the collision map, it triggers the SFX and the codec image disappears. 
		if ((level2collisionBitmap[OFFSET(snake.bigRow, snake.bigCol + snake.width, 512)] == RED)
			|| (level2collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol + snake.width, 512)] == RED && snake.bigRow <= 512)) {
			codec.isActive = 0;
			playSoundB(codecsound,CODECSOUNDLEN,CODECSOUNDFREQ, 0);
		}
		//Snakes stays inside the screen and does not go overboards
		if (level2collisionBitmap[OFFSET(snake.bigRow, snake.bigCol + snake.width, 512)] && level2collisionBitmap[OFFSET(snake.bigRow + snake.height - 1, snake.bigCol + snake.width, 512)] && snake.bigRow <= 512) {
			if ((snake.col < SCREENWIDTH / 2 || hOff == 512 - SCREENWIDTH) && snake.col < SCREENWIDTH - snake.width) {
				snake.col++;
			} else if (hOff != 512 - SCREENWIDTH) {
				hOff++;
			}
		}
	
	}

	//PAUSE
	if (BUTTON_PRESSED(BUTTON_START)) {
		REG_DISPCTL = MODE4 | BG2_ENABLE;
		state = PAUSE2;
		initPause();
	}

	//CHEATMODE
	if (BUTTON_PRESSED(BUTTON_A)) {
		playSoundB(cheatsound, CHEATSOUNDLEN, CHEATSOUNDFREQ,0);
		snake.cheatMode = 1;		
	}
	
	REG_BG0HOFS = hOff;
	REG_BG0VOFS = vOff;

	//Updates snake's world position based on its row/col movement
	snake.bigRow = snake.row + vOff;
	snake.bigCol = snake.col + hOff;

	codec.row = codec.bigRow - vOff;
	codec.col = codec.bigCol - hOff;
	
	for (int i = 0; i < 7; i++) {
		enemies[i].row = enemies[i].bigRow - vOff;
		enemies[i].col = enemies[i].bigCol - hOff;		
	}
	
	animatePlayer();
	animateEnemies();
	updateOAM();
	DMANow(3, shadowOAM, OAM, 512);
	waitForVblank();

	//Cheat mode. Only triggered when the player pressed the A Button.
	if (snake.cheatMode == 0) {
		checkDetection();
		if (snake.isDetected == 1) {
			gameOver();
		}		
	}
}

/**
Animates Player movements
**/
void animatePlayer()
{
    if (snake.aniState != SNAKEIDLE) snake.prevAniState = snake.aniState;
		
    snake.aniState = SNAKEIDLE;

    if(snake.aniCounter % 5 == 0) 
    {
		snake.aniCounter = 0;
		if (snake.currFrame == 8) {
			snake.currFrame = 1;
		} else {
			snake.currFrame++;
		}
    }

    if(BUTTON_HELD(BUTTON_UP))
	{
		snake.aniState = SNAKEBACK;
	}
    if(BUTTON_HELD(BUTTON_DOWN))
	{
		snake.aniState = SNAKEFRONT;
	}
    if(BUTTON_HELD(BUTTON_LEFT))
	{
		snake.aniState = SNAKELEFT;
	}
    if(BUTTON_HELD(BUTTON_RIGHT))
	{
		snake.aniState = SNAKERIGHT;
	}
		
    if(snake.aniState == SNAKEIDLE)
	{
        snake.currFrame = 0;
	}
    else
	{
        snake.aniCounter++;
	}
}

//Turns around the enemies every 101 frames
void animateEnemies() {
	for (int i = 0; i < 7; i++) {
    	if(enemies[i].aniCounter % 101 == 0) {	//Makes sure the following code occurrs every 101 frames
    		enemies[i].aniState = ENEMYRIGHT;
    	}
    	if (enemies[i].aniCounter % 202 == 0) {
    		enemies[i].aniState = ENEMYFRONT;
    	}
    	if (enemies[i].aniCounter % 303 == 0) {
    		enemies[i].aniState = ENEMYLEFT;
    	}
    	if (enemies[i].aniCounter % 404 == 0) {
    		enemies[i].aniState = ENEMYBACK;
    	}
    	enemies[i].aniCounter++;	// increases anicounter every frame so that the above code runs every 100 frames
	}
}

//Every time enemies turn directions this checks for detection.
//The enemy is able to see 3 times further than his width/height (16 pixels)
void checkDetection() {
	for (int i = 0; i < 7; i++) {
		if ((enemies[i].aniState == ENEMYBACK) && (snake.bigRow >= enemies[i].bigRow - 48) && (snake.bigRow <= enemies[i].bigRow) && (snake.bigCol + 8 >= enemies[i].bigCol) && (snake.bigCol <= enemies[i].bigCol + 24)) {
			snake.isDetected = 1;
		}
		if (enemies[i].aniState == ENEMYFRONT && (snake.bigRow <= enemies[i].bigRow + 64) && (snake.bigRow >= enemies[i].bigRow + 16) && (snake.bigCol + 8 >= enemies[i].bigCol) && (snake.bigCol <= enemies[i].bigCol + 24)) {
			snake.isDetected = 1;
		}
		if ((enemies[i].aniState == ENEMYLEFT) && (snake.bigCol >= enemies[i].bigCol - 48) && (snake.bigCol <= enemies[i].bigCol) && (snake.bigRow >= enemies[i].bigRow - 8) && (snake.bigRow <= enemies[i].bigRow + 8)) {
			snake.isDetected = 1;
		}
		if ((enemies[i].aniState == ENEMYRIGHT) && (snake.bigCol <= enemies[i].bigCol + 64) && (snake.bigCol > enemies[i].bigCol + 16) && (snake.bigRow >= enemies[i].bigRow - 8) && (snake.bigRow <= enemies[i].bigRow + 8)) {
			snake.isDetected = 1;
		}
	}
}

/**
Called when player gets detected
**/
void gameOver() {
	REG_DISPCTL = MODE4 | BG2_ENABLE;
	initLose();
	state = LOSE;
	playSoundB(alertsound, ALERTSOUNDLEN, ALERTSOUNDFREQ,0);
	playSoundA(losetheme, LOSETHEMELEN, LOSETHEMEFREQ,0);
}

/**
Updates OAM
**/
void updateOAM()
{
	hideSprites();

	/**
	Player OAM
	**/
	shadowOAM[0].attr0 = (ROWMASK & snake.row) | ATTR0_4BPP | ATTR0_SQUARE;
	shadowOAM[0].attr1 = (COLMASK & snake.col) | ATTR1_SIZE16;
	shadowOAM[0].attr2 = SPRITEOFFSET16(2*snake.currFrame,2*snake.prevAniState);

	/**
	Codec OAM
	**/
	if ((codec.row) > 160 + codec.height || (codec.row) < codec.height || (codec.col) > 240 + codec.height || (codec.col) < codec.height) {
		shadowOAM[1].attr0 = ATTR0_HIDE;
	} else {
		if (codec.isActive) {
			shadowOAM[1].attr0 = (ROWMASK & (codec.row)) | ATTR0_4BPP | ATTR0_SQUARE;
		} else {
			shadowOAM[1].attr0 = ATTR0_HIDE;
		}
		shadowOAM[1].attr1 = (COLMASK & (codec.col)) | ATTR1_SIZE16;
		shadowOAM[1].attr2 = SPRITEOFFSET16(0, 8);
	}

	/**
	Enemies OAM
	**/
	int enemiesOAMTracker = 2;
	for (int i = 0; i < 7; i++) {
		if ((enemies[i].row) > 160 || (enemies[i].row) < 0 || (enemies[i].col) > 240 || (enemies[i].col) < 0) {
			shadowOAM[enemiesOAMTracker].attr0 = ATTR0_HIDE;
		} else {
			shadowOAM[enemiesOAMTracker].attr0 = (ROWMASK & (enemies[i].row)) | ATTR0_4BPP | ATTR0_SQUARE;
			shadowOAM[enemiesOAMTracker].attr1 = (COLMASK & (enemies[i].col)) | ATTR1_SIZE16;
			shadowOAM[enemiesOAMTracker].attr2 = SPRITEOFFSET16(2*enemies[i].currFrame, enemies[i].aniState);
		}
		enemiesOAMTracker++;
	}
}

/**
Initially hides all sprites
**/
void hideSprites()
{
    int i;for(i = 0; i < 128; i++)
    {
         shadowOAM[i].attr0 = ATTR0_HIDE;
    }
}