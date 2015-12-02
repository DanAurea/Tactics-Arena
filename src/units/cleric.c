#include "../../include/gameEngine.h"

/**
* Initialise l'unité
*/
void clericInit(vector coordUnit, int noPlayer){
	grid[coordUnit.x]grid[coordUnit.y].stat.HP = 24;
	grid[coordUnit.x]grid[coordUnit.y].stat.POWER = 12;
	grid[coordUnit.x]grid[coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[0] = 0.0;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[1] = 0.0;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.RECOVERY = 5;
	grid[coordUnit.x]grid[coordUnit.y].stat.MOVE_RANGE = 3;
	
	for(int i = 0; i < NB_MAX_EFFECT; i++){
		grid[coordUnit.x]grid[coordUnit.y].effect[i] = none;
	}
	
	if(noPlayer == 1){
		grid[coordUnit.x]grid[coordUnit.y].direct = north;
	}else{
		grid[coordUnit.x]grid[coordUnit.y].direct = south;
	}
}

/**
*	Initialise les cibles de l'unité	
*/
void clericTarget(vector coordUnit){

}
