#include "../../include/gameEngine.h"
#include "../../include/terminal.h"

/**
 * Initialise un Scout
 * @param coordUnit Coordonnées de l'unité
 * @param noPlayer  Propriétaire de l'unité
 */
void scoutInit(short noPlayer, vector coordUnit){
	grid[coordUnit.x][coordUnit.y].stat.HP = 40;
	grid[coordUnit.x][coordUnit.y].stat.POWER = 18;
	grid[coordUnit.x][coordUnit.y].stat.ARMOR = 0.08;
	
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[0] = 0.6;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[1] = 0.3;
	grid[coordUnit.x][coordUnit.y].stat.BLOCK[2] = 0.0;
	
	grid[coordUnit.x][coordUnit.y].stat.RECOVERY = 2;
	grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE = 4;
	
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
 * Initialise le champ de visée d'un Scout
 * @param coordUnit Coordonnées de l'unité
 */
void scoutTarget(vector coordUnit)
{
	int k = 0;
	int allonge_max = 6;
	for(int i=-allonge_max;i<allonge_max;i++)
	{
		for(int j=-allonge_max;j<allonge_max;j++)
		{
			if(	abs(i) + abs(j) <= allonge_max && abs(i) + abs(j) > 0)
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
