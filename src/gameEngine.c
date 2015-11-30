#include <stdlib.h>
#include "../include/gameEngine.h"

unit grid[N][N] = {{{scout}},{{dragonTyrant}},{{knight}},{{knight}},{{knight}},{{assassin}}};

bool lookAround(vector currentUnit)
{
	bool surrounded = true;
	for(int i=-1;i<2 && surrounded;i++)
	{
		for(int j=-1;j<2 && surrounded;j++)
		{
			if(abs(i) + abs(j) == 1)
			{
				if(grid[currentUnit.x+i][currentUnit.y].name ==0)
				{
					//TODO
					// verif si unité ennemi.
					// verif si unité allié avec canGetPassed().
					surrounded=false;
				}
			}
		}
	}
	return surrounded;
}