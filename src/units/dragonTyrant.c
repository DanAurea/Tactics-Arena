#include "../../include/gameEngine.h"

/**
* Initialise l'unité
*/
void dragonTyrantInit(int noPlayer, vector coordUnit){
	grid[coordUnit.x][coordUnit.y].stat.HP = 28;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 24;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.2;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.1;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 3;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 3;
	
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
void dragonTyrantTarget(vector coordUnit){
	int k = 0;
	int allonge_max = 3;
	for(int i=-allonge_max;i<allonge_max;i++)
	{
		if(i!=0)
		{
			grid[coordUnit.x][coordUnit.y].unitTarget[k].x = coordUnit.x + i ;
				grid[coordUnit.x][coordUnit.y].unitTarget[k].y = coordUnit.y ;
			k++;
		}
	}
	for(int j=-allonge_max;j<allonge_max;j++)
	{
		if(j!=0)
		{
			grid[coordUnit.x][coordUnit.y].unitTarget[k].x = coordUnit.x ;
				grid[coordUnit.x][coordUnit.y].unitTarget[k].y = coordUnit.y + j;
			k++;
		}
	}
	
}
