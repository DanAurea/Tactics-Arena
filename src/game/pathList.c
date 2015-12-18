/* Mise en oeuvre contigue d'un tableau de listes de vecteurs */
#include <stdio.h>
#include "../../include/game/engine.h"

/* Definition du type d'un elem de liste */
typedef struct elem {vector coordParent; int F; struct elem* pred; struct elem* succ;} tile;

/* Declaration des listes (flag et elem courant) */
tile* flag[2]; // Open and closed lists for path finding ( A *)
tile* elemC[2];


/* Primitives de manipulation des listes */

void initPath(int n)
{	if(n >= 0 && n < 2)
	{
		flag[n] = malloc(sizeof(tile));
		flag[n]->pred = flag[n];
		flag[n]->succ = flag[n];
		elemC[n] = flag[n];
	}
}

void initPaths(){
	for(int i = 0; i < 2; i++)
		initPath(i);
}

int emptyPath(int n)
{	if(n>=0&&n< 2 )
		return flag[n]->pred==flag[n];
    return -1;
}

int outPath(int n)
{	if(n>=0&&n<2)
		return elemC[n]==flag[n];
    return -1;
}

void pathHead(int n)
{	if(n>=0&&n< 2)
		if (!emptyPath(n))
			elemC[n] = flag[n]->succ;
}

void pathTail(int n)
{	if(n>=0&&n<2)
		if (!emptyPath(n))
			elemC[n] = flag[n]->pred;
}

void previous(int n)
{	if(n>=0&&n<2)
		if (!outPath(n))
			elemC[n] = elemC[n]->pred;
}

void next(int n)
{	if(n>=0&&n<2)
		if (!outPath(n))
			elemC[n] = elemC[n]->succ;
}

void getTile(int n, vector * v, int * F)
{	if(n>=0&&n<2)
		if (!outPath(n)){
			v->x = elemC[n]->coordParent.x;
            v->y = elemC[n]->coordParent.y;
            * F = elemC[n]->F;
		}
}

/**
 * Récupère le noeud ayant le plus petit F
 */
vector getCurrentNode(int n){
	int F = 99999, F2;
	vector tmp, tmp2 = {-1, -1};

	pathHead(n);

	while(!outPath(n)){
		F2 = F;
		getTile(n, &tmp, &F);

		if(F < F2){
			tmp2.x = tmp.x;
			tmp2.y = tmp.y;
		}

		next(n);
	}
	return tmp2;

}

void setTile(int n, vector v, int F)
{	if(n>=0&&n<2)
		if (!outPath(n)){
			elemC[n]->coordParent.x = v.x;
            elemC[n]->coordParent.y = v.y;
            elemC[n]->F = F;
		}
}

void eraseTile(int n)
{
	tile * temp;

    	if(n>=0&&n<2)
		if (!outPath(n))
		{
			(elemC[n]->succ)->pred = elemC[n]->pred;
			(elemC[n]->pred)->succ = elemC[n]->succ;
			temp = elemC[n];
			elemC[n] = elemC[n]->pred;
			free(temp);
		}
}

void toRightPath(int n, vector v, int F)
{
	tile* nouv;

	if(n>=0&&n<2)
		if (emptyPath(n) || !outPath(n))
		{
			nouv = malloc(sizeof(tile));
			nouv->coordParent.x = v.x;
            nouv->coordParent.y = v.y;
            nouv->F = F;
			nouv->pred = elemC[n];
			nouv->succ = elemC[n]->succ;
			(elemC[n]->succ)->pred = nouv;
			elemC[n]->succ = nouv;
			elemC[n] = nouv;
		}
}

/**
 * Vide une liste
 * @param nbList Numéro de la liste à vider
 */
void dumpPath(short nbList){
	if(flag != NULL && !emptyPath(nbList)){
		pathTail(nbList);
		while(!emptyPath(nbList)){
			eraseTile(nbList);
		}
	}
}

/**
 * Vide toutes les listes
 */
void dumpAllPaths(){

	for(int list = 0; list <2; list++){
		dumpPath(list); // Libère la liste
		free(flag[list]); // Libère le flag
	}
}

/**
 * Cherche si un vecteur est présent dans la liste fermée ou ouverte
 */
bool searchTile(int n, vector coordTile){
	vector tmp;
	int F;

	if(!emptyPath(n)){
		pathHead(n);

		while(!outPath(n)){
			getTile(n, &tmp, &F);
			if(tmp.x == coordTile.x && tmp.y == coordTile.y)
				return true;
			next(n);
		}
	}

	return false;
}

/**
 * Ajoute à la liste fermée
 * @param coordTarget Destination
 */
void addCloseList(vector current, int F){
	vector tmp = {0, 0};
	int F2 = 0;

	pathHead(0); // Tête liste ouverte
	pathTail(1); // Queue liste fermée

	while(!outPath(0) && (tmp.x != current.x || tmp.y != current.y)){
		getTile(0, &tmp, &F2);
		if(tmp.x == current.x && tmp.y == current.y){
			eraseTile(0); // Supprime de la liste ouverte
		}
		next(0);
	}

	toRightPath(1, current, F);
}

/**
 * Ajoute à la liste ouverte
 * @param coordTarget Destination
 */
void addOpenList(vector current, int F){
	vector tmp = {0, 0};
	int F2 = 0;

	pathHead(1); // Tête liste ouverte
	pathTail(0); // Queue liste fermée

	while(!outPath(1) && (tmp.x != current.x || tmp.y != current.y)){
		getTile(1, &tmp, &F2);
		if(tmp.x == current.x && tmp.y == current.y){
			eraseTile(1); // Supprime de la liste ouverte
		}
		next(1);
	}

	toRightPath(0, current, F);
}