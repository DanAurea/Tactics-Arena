#include "../../include/gameEngine.h"

/**
* Initialise l'unité
*/
void beastRiderInit(vector coordUnit, int noPlayer){
	grid[coordUnit.x][coordUnit.y].stat.HP = 38;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 19;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.15;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.45;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.22;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 1;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 4;
	
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
void beastRiderTarget(vector coordUnit){
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
