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
void unitInit(short noP, vector coordUnit)
{
	int unitName = grid[coordUnit.x][coordUnit.y].name;
    copy (&grid[coordUnit.x][coordUnit.y],&pawns[unitName]); //unitName à la place de 0
    grid[coordUnit.x][coordUnit.y].noPlayer = noP;

    grid[coordUnit.x][coordUnit.y].unitColor = black;
    if(noPlayer == FIRST_PLAYER)
    {
        setDirection(coordUnit,north);
    }
    else
    {
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
    	if(target-> effect[0][i] > 2)
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
    	if(target-> effect[0][i]>4)
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
    	if(target-> effect[0][i]>3 && target-> effect[0][i]<6)
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
    	if(target-> effect[0][i] == 5)
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
            erase(uTarget);
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
            destination->effect[0][i] = source->effect[0][i];
            destination->effect[1][i] = source->effect[1][i];
        }

        destination->visited   = source->visited;
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
		source->effect[0][i] = none;
		source->effect[1][i] = 0;
	}
	source->unitColor= black;
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
		destroyUnit(source);
		addUnit(destination);
        grid[source.x][source.y].unitColor = black;
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
{
	unit * uTarget = &grid[target.x][target.y];
	uTarget->effect[0][effect-1]=effect;
	if(effect==FOCUS)
	{
	    uTarget->effect[0][effect-1]=1;
	}
	else
	{
	    uTarget->effect[0][effect-1]=3;
	}
}

void minusEffect()
{
    vector pos;
    if(!liste_vide(noPlayer))
    {
        en_tete(noPlayer);
        while(!hors_liste(noPlayer))
        {
            valeur_elt(noPlayer,&pos);
            for(int i=0;i<NB_MAX_EFFECT;i++)
            {
                if(grid[pos.x][pos.y].effect[0][i]!=none)
                {
                    grid[pos.x][pos.y].effect[1][i]--;
                    if(grid[pos.x][pos.y].effect[1][i]==0)
                    {
                        grid[pos.x][pos.y].effect[0][i]=none;
                    }
                }
            }
        }
    }
}

/*
    Met à 0 le recovery de l'unité passée en paramètre
*/
void sleep(vector pos)
{
    grid[pos.x][pos.y].stat.RECOVERY=0;
}

bool isSleeping(vector pos)
{
    unit uTarget = grid[pos.x][pos.y];
    if(uTarget.stat.RECOVERY<pawns[uTarget.name].stat.RECOVERY)
    {
        return true;
    }
    return false;
}

void recover(vector pos)
{
    unit uTarget = grid[pos.x][pos.y];
    if(uTarget.stat.RECOVERY<pawns[uTarget.name].stat.RECOVERY)
    {
        uTarget.stat.RECOVERY++;
    }
}

//true > toutes unité du joueur imobile sinon false
bool allStatic(int numPlayer)
{
    int uMovable=0;
    vector pos;
    if(!liste_vide(numPlayer))
    {
        en_tete(numPlayer);
        while(!hors_liste(numPlayer) && uMovable==0)
        {
            valeur_elt(numPlayer,&pos);
            if(canMove(&grid[pos.x][pos.y]) || !isSurrounded(pos))
            {
                uMovable++;
            }
        }
    }
    if(uMovable>0)
    {
        return false;
    }
    return true;
}


