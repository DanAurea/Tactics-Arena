#include "../../include/gameEngine.h"

/**
* Initialise l'unité
*/
void clericInit(int noPlayer, vector coordUnit){
	grid[coordUnit.x][coordUnit.y].stat.HP = 24;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 12;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.0;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.0;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 5;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 3;
	
	grid[coordUnit.x][coordUnit.y].noPlayer = noPlayer;
	
	for(int i = 0; i < NB_MAX_EFFECT; i++){
		grid[coordUnit.x][coordUnit.y].effect[i] = none;
	}
	
	if(noPlayer == 1){
		grid[coordUnit.x][coordUnit.y].direct = north;
	}else{
		grid[coordUnit.x][coordUnit.y].direct = south;
	}
}

/**
*	Initialise les cibles de l'unité	
*/
void clericTarget(vector coordUnit){

}
