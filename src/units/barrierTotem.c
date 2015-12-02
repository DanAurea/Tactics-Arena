#include "../../include/gameEngine.h"

/**
* Initialise l'unité
*/
void barrierTotemInit(vector coordUnit, int noPlayer){
	grid[coordUnit.x][coordUnit.y].stat.HP = 32;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 0;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 1.0;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 1.0;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 1.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 2;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 0;
	
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
void barrierTotemTarget(vector coordUnit)
{
	int k = 0;
	int allonge_max = 6;
	for(int i=-allonge_max;i<allonge_max;i++)
	{
		for(int j=-allonge_max;j<allonge_max;j++)
		{
			if(	abs(i)+abs(j) <= allonge_max)
			{
				if(coordUnit.x+i >= 0 && coordUnit.x+i >= N && coordUnit.y+j >= 0 && coordUnit.y+j >= N)
				{
					grid[coordUnit.x][coordUnit.y].unitTarget[k].x = coordUnit.x + i ;
					grid[coordUnit.x][coordUnit.y].unitTarget[k].y = coordUnit.y + j ;
					k++;
				}
			}
		}
	}
}


