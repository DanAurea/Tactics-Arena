#include "../../include/gameEngine.h"
#include "../../include/terminal.h"

/**
* Initialise l'unité
*/
void poisonWispInit(short noPlayer, vector coordUnit){
	grid[coordUnit.x][coordUnit.y].stat.HP = 34;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 0;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.0;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.0;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 2;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 6;
	
	grid[coordUnit.x][coordUnit.y].noPlayer = noPlayer;
	
	for(int i = 0; i < NB_MAX_EFFECT; i++){
		grid[coordUnit.x][coordUnit.y].effect[i] = none;
	}
	
	if(noPlayer == 1){
		grid[coordUnit.x][coordUnit.y].direct = north;
		grid[coordUnit.x][coordUnit.y].unitColor = red;
	}else{
		grid[coordUnit.x][coordUnit.y].direct = south;
		grid[coordUnit.x][coordUnit.y].unitColor = blue;
	}
}

/**
*	Initialise les cibles de l'unité	
*/
void Attack(vector coordUnit){
	grid[coordUNit.x][coordUNit.y].unitTarget;
	for(){
		coordUnit.x+
	}
}
