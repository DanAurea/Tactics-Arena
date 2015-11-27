#include "../include/gameEngine.h"
#include "../include/Outil.h"
#include <stdbool.h>

bool canGetPassed(unit * target)
{
    bool out=true;
    for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]>2)
        {
            out=false;
        }
    }
    return out;
}

bool canBlock(unit * target)
{
    bool out=true;
    for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]>4)
        {
            out=false;
        }
    }
    return out;
}

bool canAttack(unit * target)
{
    bool out=true;
    for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]>3 && target-> effect[i]<6)
        {
            out=false;
        }
    }
    return out;
}

bool canMove(unit * target)
{
    bool out=true;
    for(int i=0;i<NB_MAX_EFFECT;i++)
    {
        if(target-> effect[i]==5)
        {
            out=false;
        }
    }
    return out;
}

void heal(unit* source, unit* target)
{
    target->stat.HP += source->stat.POWER;
}

int getSideAttacked(unit * source, unit * target )
{
	int sens = abs ( source->direct - target->direct);
	Assert1("getSideAttacked",bCroit(0,sens,2));
	return sens;
}

void attack(unit* source, vector pos)
{
    if(canAttack(source))
    {
        if(canBlock(target))
        {
            target->stat.HP-=(source->stat.POWER*target->stat.BLOCK[getSideAttacked(source,target)]);
        }
        else
        {
            target->stat.HP-=source->stat.POWER;
        }
    }
}

void copy(unit * destination, unit * source)
{
	destination->name=source->name;
	destination->stat.HP=source->stat.HP;
	destination->stat.POWER=source->stat.POWER;
	destination->stat.ARMOR=source->stat.ARMOR;
	destination->stat.RECOVERY=source->stat.RECOVERY;
	for(int i=0;i<3;i++)                          
	{                                     
		destination->stat.BLOCK[i]=source->stat.BLOCK[i];
	}
	destination->stat.MOV_RANGE=source->stat.MOV_RANGE;
	for(int i=0;i<NB_MAX_EFFECT;i++)
	{
		destination->effect[i]=source->effect[i];
	}
}

void move(unit grille[N][N],vector pos[])
{
	copy(&grille[pos[1].x][pos[1].y],&grille[pos[0].x][pos[0].y]);
	grille[pos[0].x][pos[0].y].name=empty;
}

void addEffect(unit * target, unitEffect effet)
{
	int i=0;
	while(target->effect[i]!=none || target->effect[i]==effet)
	{
		i++;
	}
	if(i<NB_MAX_EFFECT)
	{
		if(target->effect[i]!=effet)
		{
			target->effect[i]=effet;
		}
	}
}

void AoE(vector pos, int size, int dmg)
{
	for(int i = -size;i<=size;i++)
	{
		for(int j=-size;j<=size;j++
		{
			grille[pos+i][pos+j]->stat.HP-=dmg;
		}
	}
}
