#include <math.h>
#include "../include/gameEngine.h"
#include "../include/unit.h"
#include "../include/unitType.h"
#include "../include/Outil.h"


void unitInit(vector coordUnit, int noPlayer)
{
	int nomUnit = grid[coordUnit.x][coordUnit.y].name;
	switch(nomUnit)
	{
		case knight :
			knightInit(coordUnit, noPlayer);
		break;
		case scout :
			scoutInit(coordUnit, noPlayer);
		break;
		case assassin :
			assassinInit(coordUnit, noPlayer);
		break;
		case cleric :
			clericInit(coordUnit, noPlayer);
		break;
		case pyromancer :
			pyromancerInit(coordUnit, noPlayer);
		break;
		case enchantress :
			enchantressInit(coordUnit, noPlayer);
		break;
		case dragonborn :
			dragonbornInit(coordUnit, noPlayer);
		break;
		case darkWitch :
			darkWitchInit(coordUnit, noPlayer);
		break;
		case lightningTotem :
			lightningTotemInit(coordUnit, noPlayer);
		break;
		case barrierTotem :
			barrierTotemInit(coordUnit, noPlayer);
		break;
		case mudGolem :
			mudGolemInit(coordUnit, noPlayer);
		break;
		case golemAmbusher :
			ambusherGolemInit(coordUnit, noPlayer);
		break;
		case frostGolem :
			frostGolemInit(coordUnit, noPlayer);
		break;
		case stoneGolem :
			stoneGolemInit(coordUnit, noPlayer);
		break;
		case dragonTyrant :
			dragonTyrantInit(coordUnit, noPlayer);
		break;
		case berserker :
			berserkerInit(coordUnit, noPlayer);
		break;
		case beastRider :
			beastRiderInit(coordUnit, noPlayer);
		break;
		case poisonWisp :
			poisonWispInit(coordUnit, noPlayer);
		break;
		case furgon :
			furgonInit(coordUnit, noPlayer);
		break;
	}
}



/*
	renvoie faux si l'unité est soumis à un effet negatif, vrai sinon.
*/
bool canGetPassed(unit * target)
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT;i++)
    {
    	if(target-> effect[i]>2)
    	{
    		out = false;
    	}
    }

    return out;
}


/*
	renvoie faux si l'unité est soumis au effet PARALIZE ou FOCUS, vrai sinon.
*/
bool canBlock(unit * target)
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT;i++)
    {
    	if(target-> effect[i]>4)
        {
        	out = false;
        }
    }

    return out;
}


/*
	renvoie faux si l'unité est soumis au effet BARRIER, POISON ou PARALYSE, vrai sinon
*/
bool canAttack(unit * target)
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT;i++)
    {
    	if(target-> effect[i]>3 && target-> effect[i]<6)
        {
        	out = false;
        }
    }

    return out;
}


/*
	renvoie faux si l'unité est paralisée, vrai sinon
*/
bool canMove(unit * target)
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT;i++)
    {
    	if(target-> effect[i]<5)
        {
        	out = false;
        }
    }

    return out;
}


/*
	soigne l'unité target du montant du soin de l'unité cible
*/
void heal(vector source, vector target)
{
	unit * uTarget = &grid[target.x][target.y];
	unit * uSource = &grid[source.x][source.y];
    uTarget->stat.HP +=  uSource->stat.POWER;
}


/*
	Renvoie le coté de l'unité attaqué
*/
int getSideAttacked(vector source, vector target )
{
	unit * uTarget = &grid[target.x][target.y];
	unit * uSource = &grid[source.x][source.y];
	int sens = abs ( uSource->direct - uTarget->direct);
	Assert1("getSideAttacked",bCroit(0,sens,2));
	return sens;
}


/*
	attaque depuis l'unité source vers les coordonées pos en prenant en compte le BLOCKAGE de l'unité ennemie
*/
void attack(vector source, vector target)
{
	float block = 1;
	float armor;
	unit * uTarget = &grid[target.x][target.y];
	unit * uSource = &grid[source.x][source.y];
    if(canAttack(uSource))
    {
    	armor = 1-uTarget->stat.ARMOR;
    	if(canBlock(uTarget))
    	{
    		block = 1-uTarget->stat.BLOCK[getSideAttacked(source,target)];
    	}
        if(uSource->stat.Area == 1)
        {
        	uTarget->stat.HP -= (uSource->stat.POWER*(block+armor));
        }
        else
        {
        	AoE(target,uSource->stat.Area,uSource->stat.POWER,false);
        }
    }
}


/*
	copie la structure unité source vers la structure unité destination
*/
void copy(unit * destination, unit * source)
{
	destination->name		 = 	source->name;
	destination->stat.HP	 = 	source->stat.HP;
	destination->stat.POWER	 = 	source->stat.POWER;
	destination->stat.ARMOR	 = 	source->stat.ARMOR;
	destination->stat.RECOVERY = 	source->stat.RECOVERY;
	for(int i = 0;i<3;i++)
	{
		destination->stat.BLOCK[i] = source->stat.BLOCK[i];
	}
	destination->stat.MOVE_RANGE = source->stat.MOVE_RANGE;
	for(int i = 0;i<NB_MAX_EFFECT;i++)
	{
		destination->effect[i] = source->effect[i];
	}
}


/*
	déplace l'unité se trouvant en pos[0] en pos[1].
*/
void move(vector destination, vector source)
{
	unit * uSource = &grid[source.x][source.y];
	if(canMove(uSource))
	{
		copy(&grid[destination.x][destination.y],&grid[source.x][source.y]);
		grid[source.x][source.y].name = empty;
	}
}

void setDirection(vector source, int dir)
{
	unit * uSource = &grid[source.x][source.y];
	uSource->direct = dir;
}

/*
	Ajoute sur l'unité target l'effet effect.
*/
void addEffect(vector target, unitEffect effect)
{
	unit * uTarget = &grid[target.x][target.y];
	int i = 0;
	While(5);
	while(bWhile(uTarget->effect[i] != none || uTarget->effect[i] != effect))
	{
		i++;
	}
	if(i<NB_MAX_EFFECT)
	{
		if(uTarget->effect[i] != effect)
		{
			uTarget->effect[i] = effect;
		}
	}
}


/*
	Area of Effect : attaque de zone centrée sur pos, de taille size et d'intensité dmg. Si own est vrai, ne touche pas l'unité au centre.
*/
void AoE(vector pos, int size, int dmg, bool own)
{
	for(int i = -size; i <= size; i++)
	{
		for(int j = -size; j <= size; j++)
		{
			if(abs(i)+abs(j) <= size)
			{
				if(!own)
				{
					grid[pos.x+i][pos.y+j].stat.HP -= dmg*(1-grid[pos.x+i][pos.y+j].stat.ARMOR);
				}
				else
				{
					if(i != 0 || j != 0)
					{
						grid[pos.x+i][pos.y+j].stat.HP -= dmg*(1-grid[pos.x+i][pos.y+j].stat.ARMOR);
					}
				}
			}
		}
	}
}


/*
	attaque en ligne de taille size, de sens dir et commancant à pos.
*/
void line(vector pos, int size, int dmg, int dir)
{
	int sens = 1;
	if(dir >= 2)
	{
		sens = -1;
	}
	if(dir%2)
	{
		for(int i = 0;i<size;i++)
		{
			grid[pos.x+(i*sens)][pos.y].stat.HP -= dmg*(1-grid[pos.x+(i*sens)][pos.y].stat.ARMOR);
		}
	}
	else
	{
		for(int j = 0;j<size;j++)
		{
			grid[pos.x][pos.y+(j*sens)].stat.HP -= dmg*(1-grid[pos.x][pos.y+(j*sens)].stat.ARMOR);
		}
	}
}
