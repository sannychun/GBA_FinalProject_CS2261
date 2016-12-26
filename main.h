/* 
SPRITE struct. This will be used for Player and Enemies
*/
typedef struct  
{
	int row;
	int col;
	int bigRow;
	int bigCol;
	int rdel;
	int cdel;
	int width;
	int height;
	int aniCounter;
	int aniState;
	int prevAniState;
	int frameDirection;
    int currFrame;
    int isActive;
    int isDetected;
    int cheatMode;
} SPRITE;

SPRITE snake;
SPRITE enemies[7];
SPRITE codec;

enum {SNAKEFRONT, SNAKEBACK, SNAKERIGHT, SNAKELEFT, SNAKEIDLE};
enum {ENEMYFRONT = 10, ENEMYBACK = 12, ENEMYRIGHT = 14, ENEMYLEFT = 16};

enum { START, STORY1, STORY2, STORY3, STORY4, STORY5, INSTRUCTIONS, LEVEL1, LEVEL2, PAUSE1, PAUSE2, LOSE, WIN};
int state;

int hOff=0;
int vOff=0;

OBJ_ATTR shadowOAM[128];

#define ROWMASK 0xFF
#define COLMASK 0x1FF

unsigned int buttons;
unsigned int oldButtons;