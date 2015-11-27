#include "../include/gameEngine.h"
#include "../include/Outil.h"

/*
	renvoie faux si l'unité est soumis à un effet negatif, vrai sinon.
*/
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


/*
	renvoie faux si l'unité est soumis au effet PARALIZE ou FOCUS, vrai sinon.
*/
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


/*
	renvoie faux si l'unité est soumis au effet BARRIER, POISON ou PARALYSE, vrai sinon
*/
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


/*
	renvoie faux si l'unité est paralisée, vrai sinon
*/
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

/*
	soigne l'unité target du montant du soin de l'unité cible
*/
void heal(unit* source, unit* target)
{
    target->stat.HP += source->stat.POWER;
}


/*
	Renvoie le coté de l'unité attaqué
*/
int getSideAttacked(unit * source, unit * target )
{
	int sens = abs ( source->direct - target->direct);
	Assert1("getSideAttacked",bCroit(0,sens,2));
	return sens;
}


/*
	DEPRECATED
	attaque depuis l'unité source vers les coordonées pos en prenant en compte le BLOCKAGE de l'unité ennemie
*/
void attack(unit * grid[N][N], vector source, vector target)
{
	unit * uTarget = grid[target.x][target.y];
	unit * uSource = grid[source.x][source.y];
    if(canAttack(uSource))
    {
        if(canBlock(uTarget))
        {
            uTarget->stat.HP-=(uSource->stat.POWER*uTarget->stat.BLOCK[getSideAttacked(uSource,uTarget)]);
        }
        else
        {
            uTarget->stat.HP-=uSource->stat.POWER;
        }
    }
}

/*
	copie la structure unité source vert la structure unité destination
*/
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


/*
	déplace l'unité se trouvant en pos[0] en pos[1].
*/
void move(unit * grille[N][N],vector pos[])
{
	copy(grille[pos[1].x][pos[1].y],grille[pos[0].x][pos[0].y]);
	grille[pos[0].x][pos[0].y]->name=empty;
}

/*
	Ajoute sur l'unité target l'effet effect.
*/
void addEffect(unit * target, unitEffect effect)
{
	int i=0;
	while(target->effect[i]!=none || target->effect[i]==effect)
	{
		i++;
	}
	if(i<NB_MAX_EFFECT)
	{
		if(target->effect[i]!=effect)
		{
			target->effect[i]=effect;
		}
	}
}


/*
	Area of Effect : attaque de zone centrée sur pos, de taille size et d'intensité dmg.
*/
void AoE(unit * grid[N][N], vector pos, int size, int dmg)
{
	for(int i = -size;i<=size;i++)
	{
		for(int j=-size;j<=size;j++)
		{
			grid[pos.x+i][pos.y+j]->stat.HP-=dmg;
		}
	}
}
