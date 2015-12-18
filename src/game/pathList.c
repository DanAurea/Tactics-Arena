/**
 @file pathList.c
 @brief Listes de cases sur un chemin définis
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <stdio.h>
#include "../../include/game/engine.h"

/**
 * @struct elem pathList.c
 * Représente une case de la grille
 */
typedef struct elem {
	vector coordParent; /**< Coordonnées de la case */
	int F; /**< Poids de la case */
	struct elem* prev; /**< Elément précédent */
	struct elem* next; /**< Elément suivant */
} t_tile; /**< Définis la case */


t_tile* flag[2]; /**< Tableau de drapeaux */
t_tile* elemC[2]; /**< Tableau d'éléments courants */

/**
 * Initialise le chemin
 * @param n Chemin
 */
void initPath(int n)
{	if(n >= 0 && n < 2)
	{
		flag[n] = malloc(sizeof(t_tile));
		flag[n]->prev = flag[n];
		flag[n]->next = flag[n];
		elemC[n] = flag[n];
	}
}

/**
 * Initialise les chemins
 */
void initPaths(){
	for(int i = 0; i <= 2; i++)
		initPath(i);
}

/**
 * Vérifie si un chemin est vide
 * @param  n Chemin
 * @return   Retourne le drapeau si pas vide
 */
int emptyPath(int n)
{	if(n>=0&&n< 2 )
		return flag[n]->prev==flag[n];
    return -1;
}

/**
 * Vérifie si l'élément courant est hors liste
 * @param  n Liste
 * @return   Retourne l'élément courant si pas hors liste
 */
int outPath(int n)
{	if(n>=0&&n<2)
		return elemC[n]==flag[n];
    return -1;
}

/**
 * Se met en tête du chemin
 * @param n Chemin
 */
void pathHead(int n)
{	if(n>=0&&n< 2)
		if (!emptyPath(n))
			elemC[n] = flag[n]->next;
}

/**
 * Se met en queue du chemin
 * @param n Chemin
 */
void pathTail(int n)
{	if(n>=0&&n<2)
		if (!emptyPath(n))
			elemC[n] = flag[n]->prev;
}

/**
 * Se positionne sur l'élément précédent
 * @param n Chemin
 */
void previous(int n)
{	if(n>=0&&n<2)
		if (!outPath(n))
			elemC[n] = elemC[n]->prev;
}

/**
 * Se positionne sur l'élémént suivant
 * @param n Chemin
 */
void next(int n)
{	if(n>=0&&n<2)
		if (!outPath(n))
			elemC[n] = elemC[n]->next;
}

/**
 * Récupère une case du chemin
 * @param n Chemin
 * @param v Position de la case
 * @param F Poids de la case
 */
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
 * @param n Liste dans laquelle chercher
 */
vector getCurrentNode(int n){
	int F = 9999999, F2;
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

/**
 * Modifie les infos d'une case dans la liste
 * @param n Liste
 * @param v Nouvelle position
 * @param F Nouveau poids
 */
void setTile(int n, vector v, int F)
{	if(n>=0&&n<2)
		if (!outPath(n)){
			elemC[n]->coordParent.x = v.x;
            elemC[n]->coordParent.y = v.y;
            elemC[n]->F = F;
		}
}

/**
 * Efface une case de la grille
 * @param n Liste
 */
void eraseTile(int n)
{
	t_tile * temp;

    	if(n>=0&&n<2)
		if (!outPath(n))
		{
			(elemC[n]->next)->prev = elemC[n]->prev;
			(elemC[n]->prev)->next = elemC[n]->next;
			temp = elemC[n];
			elemC[n] = elemC[n]->prev;
			free(temp);
		}
}

/**
 * Ajoute une case à droite
 * @param n Liste
 * @param v Position à ajouter
 * @param F Poids à ajouter
 */
void toRightPath(int n, vector v, int F)
{
	t_tile* nouv;

	if(n>=0&&n<2)
		if (emptyPath(n) || !outPath(n))
		{
			nouv = malloc(sizeof(t_tile));
			nouv->coordParent.x = v.x;
            nouv->coordParent.y = v.y;
            nouv->F = F;
			nouv->prev = elemC[n];
			nouv->next = elemC[n]->next;
			(elemC[n]->next)->prev = nouv;
			elemC[n]->next = nouv;
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

	for(int list = 0; list < 2; list++){
		dumpPath(list); // Libère la liste
		free(flag[list]); // Libère le flag
	}
}

/**
 * Cherche si un vecteur est présent dans la liste fermée ou ouverte
 * @param n Liste
 * @param coordTile Position de la case
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
 * @param current Destination
 * @param F Poids de la case
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
 * @param current Destination
 * @param F Poids de la case
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