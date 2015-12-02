#include "../../include/gameEngine.h"

/**
* Initialise les cibles de l'unité
*/
void knightInit(vector coordUnit, int noPlayer){
	grid[coordUnit.x]grid[coordUnit.y].stat.HP = 50;
	grid[coordUnit.x]grid[coordUnit.y].stat.POWER = 22;
	grid[coordUnit.x]grid[coordUnit.y].stat.ARMOR = 0.25;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[0] = 0.8;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[1] = 0.4;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[2] = 0;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.RECOVERY = 1;
	grid[coordUnit.x]grid[coordUnit.y].stat.MOVE_RANGE = 3;
	
	for(int i = 0; i < NB_MAX_EFFECT; i++){
		grid[coordUnit.x]grid[coordUnit.y].effect[i] = none;
	}
	
	if(noPlayer == 1){
		grid[coordUnit.x]grid[coordUnit.y].direct = north;
	}else{
		grid[coordUnit.x]grid[coordUnit.y].direct = west;
	}
}

/**
*	Initialise les cibles de l'unité	
*/
void knightAttack(vector coordUnit){

}
