#include "../../include/gameEngine.h"

/**
* Initialise l'unité
*/
void ambusherGolemInit(vector coordUnit, int noPlayer){
	grid[coordUnit.x]grid[coordUnit.y].stat.HP = 60;
	grid[coordUnit.x]grid[coordUnit.y].stat.POWER = 20;
	grid[coordUnit.x]grid[coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[0] = 0.0;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[1] = 0.0;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.RECOVERY = 3;
	grid[coordUnit.x]grid[coordUnit.y].stat.MOVE_RANGE = 2;
	
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
void ambusherGolemTarget(vector coordUnit){
	int k = 0;
	int allonge_max = 6;
	int allonge_min = 5;
	for(int i=-allonge_max;i<allonge_max;i++)
	{
		for(int j=-allonge_max;j<allonge_max;j++)
		{
			if(abs(i)+abs(j) <= allonge_max && abs(i)+abs(j) >= allonge_min)
			{
				grid[coordUnit.x][coordUnit.y].unitTarget[k].x = coordUnit.x + i ;
				grid[coordUnit.x][coordUnit.y].unitTarget[k].y = coordUnit.y + j ;
				k++;
			}
		}
	}	
}
