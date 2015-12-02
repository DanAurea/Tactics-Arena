#include "../../include/gameEngine.h"

/**
* Initialise les cibles de l'unité
*/
void knightInit(vector coordUnit, int noPlayer){
	grid[coordUnit.x]grid[coordUnit.y].stat.HP = 56;
	grid[coordUnit.x]grid[coordUnit.y].stat.POWER = 30;
	grid[coordUnit.x]grid[coordUnit.y].stat.ARMOR = 0.18;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[0] = 1.0;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[1] = 1.0;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[2] = 1.0;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.RECOVERY = 4;
	grid[coordUnit.x]grid[coordUnit.y].stat.MOVE_RANGE = 0;
	
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
