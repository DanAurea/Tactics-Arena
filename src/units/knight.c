#include "../../include/gameEngine.h"

/**
* Initialise les cibles de l'unité
*/
void knightInit(vector coordUnit, int noPlayer)
{
	grid[coordUnit.x]grid[coordUnit.y].stat.HP = 50;
	grid[coordUnit.x]grid[coordUnit.y].stat.POWER = 22;
	grid[coordUnit.x]grid[coordUnit.y].stat.ARMOR = 0.25;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[0] = 0.8;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[1] = 0.4;
	grid[coordUnit.x]grid[coordUnit.y].stat.BLOCK[2] = 0;
	
	grid[coordUnit.x]grid[coordUnit.y].stat.RECOVERY = 1;
	grid[coordUnit.x]grid[coordUnit.y].stat.MOVE_RANGE = 3;
	
	for(int i = 0; i < NB_MAX_EFFECT; i++)
	{
		grid[coordUnit.x]grid[coordUnit.y].effect[i] = none;
	}
	
	if(noPlayer == 1)
	{
		grid[coordUnit.x]grid[coordUnit.y].direct = north;
	}
	else
	{
		grid[coordUnit.x]grid[coordUnit.y].direct = south;
	}
}

/**
*	Initialise les cibles de l'unité	
*/
void knightTarget(vector coordUnit)
{
	for(int k=0;k<4;k++)
	{
		for(int i=-1;i<1;i++)
		{
			for(int j=-1;j<1;j++)
			{
				if(	abs(i)+abs(j)== 1)
				{
					grid[coordUnit.x]grid[coordUnit.y].unitTarget[0].x = coordUnit.x + i ;
					grid[coordUnit.x]grid[coordUnit.y].unitTarget[0].y = coordUnit.y + j ;
				}
			}
		}
	}
}
