#include "../../include/gameEngine.h"
#include "../../include/terminal.h"

/**
* Initialise l'unité
*/
void knightInit(short noPlayer, vector coordUnit)
{
	grid[coordUnit.x][coordUnit.y].stat.HP = 50;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 22;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.25;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.8;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.4;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 1;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 3;
	
	grid[coordUnit.x][coordUnit.y].noPlayer = noPlayer;
	
	for(int i = 0; i < NB_MAX_EFFECT; i++)
	{
		grid[coordUnit.x][coordUnit.y].effect[i] = none;
	}
	
	if(noPlayer == 1)
	{
		grid[coordUnit.x][coordUnit.y].direct = north;
		grid[coordUnit.x][coordUnit.y].unitColor = red;
	}
	else
	{
		grid[coordUnit.x][coordUnit.y].direct = south;
		grid[coordUnit.x][coordUnit.y].unitColor = blue;
	}
}

/*
*	Initialise les cibles de l'unité	
*/
void knightTarget(vector coordUnit)
{
	int k = 0;
	int allonge_max = 1;
	for(int i=-allonge_max;i<allonge_max;i++)
	{
		for(int j=-allonge_max;j<allonge_max;j++)
		{
			if(	abs(i)+abs(j)== 1)
			{
				if(coordUnit.x+i >= 0 && coordUnit.x+i >= N && coordUnit.y+j >= 0 && coordUnit.y+j >= N)
				{
					grid[coordUnit.x][coordUnit.y].unitTarget[0].x = coordUnit.x + i ;
					grid[coordUnit.x][coordUnit.y].unitTarget[0].y = coordUnit.y + j ;
					k++;
				}
			}
		}
	}
}

