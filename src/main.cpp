#include <assert.h>

#include "Game.h"

int CALLBACK WinMain(HINSTANCE , HINSTANCE ,  LPSTR , int)                  
{                                                   
	Game *pGame = new Game("Charan Teja - Graphics System", 1000,800);
	pGame->run();                                  
                                   
	return 0;                                       
}

