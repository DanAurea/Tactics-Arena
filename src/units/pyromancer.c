#include "../../include/gameEngine.h"
#include "../../include/terminal.h"

/**
* Initialise l'unité
*/
void pyromancerInit(int noPlayer, vector coordUnit){
	grid[coordUnit.x][coordUnit.y].stat.HP = 30;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 15;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.33;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.16;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 3;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 3;
	
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
void pyromancerTarget(vector coordUnit)
{
	int k = 0;
	int allonge_max = 3;
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
