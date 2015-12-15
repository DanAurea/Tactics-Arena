#include <stdio.h>
#include <math.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/listes.h"
#include "../../include/controller/terminal.h"
#include "../../include/units/unit.h"

/**
 * Initialise l'unité courante
 * @param noPlayer  Joueur propriétaire
 * @param coordUnit Coordonnées de l'unité
 */
void unitInit(short noPlayer, vector coordUnit)
{
	int unitName = grid[coordUnit.x][coordUnit.y].name;
    copy (&grid[coordUnit.x][coordUnit.y],&pawns[unitName]); //unitName à la place de 0
    grid[coordUnit.x][coordUnit.y].noPlayer=noPlayer;
    if(noPlayer == FIRST_PLAYER)
    {
        grid[coordUnit.x][coordUnit.y].unitColor=red;
        setDirection(coordUnit,north);
    }
    else
    {
        grid[coordUnit.x][coordUnit.y].unitColor=blue;
        setDirection(coordUnit,south);
    }
}

/*
	renvoie faux si l'unité est soumis à un effet negatif, vrai sinon.
*/
bool canGetPassed(unit * target)
//tester
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT && out;i++)
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
//tester
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT && out;i++)
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
//tester
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT && out;i++)
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
//tester
{
    bool out = true;
    for(int i = 0;i<NB_MAX_EFFECT && out;i++)
    {
    	if(target-> effect[i] == 5)
        {
        	out = false;
        }
    }

    return out;
}

/**
 * Déterminé si une unité peut se téléporter
 * @param  name Nom de l'unité
 * @return      Retourne vraie si l'unité peut se déplacer
 */
bool canTeleport(unitName name){
    if(name == poisonWisp || name == dragonTyrant || name == mudGolem || name == dragonborn){
        return true;
    }
    return false;
}


/*
	soigne l'unité target du montant du soin de l'unité cible
*/
void heal(unitName name)
//tester
{
    vector pos;
    unitName target;
    if(!liste_vide(noPlayer))
    {
        en_tete(noPlayer);
        while(!hors_liste(noPlayer))
        {
            valeur_elt(noPlayer,&pos);
            target=grid[pos.x][pos.y].name;
            grid[pos.x][pos.y].stat.HP+=pawns[name].stat.POWER;
            if(grid[pos.x][pos.y].stat.HP > pawns[target].stat.HP)
            {
                grid[pos.x][pos.y].stat.HP=pawns[target].stat.HP;
            }
            suivant(noPlayer);
        }
    }
}


/*
	Renvoie le coté de l'unité attaqué
*/
int getSideAttacked(vector source, vector target )
{
	unit * uTarget = &grid[target.x][target.y];
	unit * uSource = &grid[source.x][source.y];
	int sens = abs ( uSource->direct - uTarget->direct);
	return sens;
}


/*
	attaque depuis l'unité source vers les coordonées pos en prenant en compte le BLOCKAGE de l'unité ennemie
*/
void attack(vector source, vector target)
{   
    int tmp = 0;
	float block = 1;
	float armor;
	unit * uTarget = &grid[target.x][target.y];
	unit * uSource = &grid[source.x][source.y];
    if(canAttack(uSource) && uTarget->name != empty && uTarget->name != decors)
    {
    	armor = 1-uTarget->stat.ARMOR;
    	if(canBlock(uTarget))
    	{
    		block = 1-uTarget->stat.BLOCK[getSideAttacked(source,target)];
    	}
        uTarget->stat.HP -= (uSource->stat.POWER*(block+armor));

        if(uTarget->stat.HP <= 0){
            tmp = noPlayer;
            noPlayer = uTarget->noPlayer; //Détruit l'unité dans la liste du joueur correspondant
            destroyUnit(target);

            noPlayer = tmp;
        }
    }
}


/*
	copie la structure unité source vers la structure unité destination
*/
bool copy(unit * destination, unit * source)
{
    if(destination != NULL && source != NULL)
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
        for(int i = 0;i<NB_MAX_EFFECT;i++){
            destination->effect[i] = source->effect[i];
        }

        destination->direct    = source->direct;
        destination->noPlayer  = source->noPlayer;
        destination->unitColor = source->unitColor;
    }
    else
    {
        return false;
    }
    return true;
}

void erase(unit * source)
//tester
{   
    memset(source, -1, sizeof(unit));
    source->name          = empty;

	for(int i = 0;i<NB_MAX_EFFECT;i++)
	{
		source->effect[i] = none;
	}
	source->unitColor=white;
}

/*
	déplace l'unité se trouvant en pos[0] en pos[1].
*/
void move(vector destination, vector source)
//tester
{
	unit * uSource = &grid[source.x][source.y];
	if(canMove(uSource))
	{
		copy(&grid[destination.x][destination.y],uSource);
		erase(uSource);
	}
}

void setDirection(vector source, int dir)
//tester
{
	unit * uSource = &grid[source.x][source.y];
	uSource->direct = dir;
}

/*
	Ajoute sur l'unité target l'effet effect.
*/
void addEffect(vector target, unitEffect effect)
//tester
{
	unit * uTarget = &grid[target.x][target.y];
	int i = 0;
	while(i<NB_MAX_EFFECT && (uTarget->effect[i] != none && uTarget->effect[i] != effect ))
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
