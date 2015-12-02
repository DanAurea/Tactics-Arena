#include "../../include/gameEngine.h"

/**
* Initialise l'unité
*/
void furgonInit(vector coordUnit, int noPlayer){
	grid[coordUnit.x][coordUnit.y].stat.HP = 48;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 0;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.5;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.25;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 1;
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
void furgonTotem(vector coordUnit){
	int k = 0;
	int allonge_max = 2;
	for(int i=-allonge_max;i<allonge_max;i++)
	{
		for(int j=-allonge_max;j<allonge_max;j++)
		{
			if(abs(i)+abs(j) == allonge_max)
			{
				grid[coordUnit.x][coordUnit.y].unitTarget[k].x = coordUnit.x + i ;
				grid[coordUnit.x][coordUnit.y].unitTarget[k].y = coordUnit.y + j ;
				k++;
			}
		}
	}
}
