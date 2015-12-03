/* Mise en oeuvre contigue d'un tableau de listes de vecteurs */
#include <stdio.h>
#include "../include/gameEngine.h"
#include "../include/listes.h"

/* Definition du type d'un element de liste */
typedef struct element {vector coordUnit; struct element* pred; struct element* succ;} t_element;

/* Declaration des listes (drapeau et element courant) */
t_element* drapeau[MAX_JOUEUR];
t_element* ec[MAX_JOUEUR];


/* Primitives de manipulation des listes */

void init_liste(int n)
{	if(n>0&&n<MAX_JOUEUR)
	{		
		drapeau[n] = malloc(sizeof(t_element));
		drapeau[n]->pred = drapeau[n];
		drapeau[n]->succ = drapeau[n];
		ec[n] = drapeau[n];
	}
}

int liste_vide(int n)
{	if(n>0&&n<MAX_JOUEUR)
		return drapeau[n]->pred==drapeau[n];
    return -1;
}

int hors_liste(int n)
{	if(n>0&&n<MAX_JOUEUR)
		return ec[n]==drapeau[n];
    return -1;
}

void en_tete(int n)
{	if(n>0&&n<MAX_JOUEUR)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->succ;
}

void en_queue(int n)
{	if(n>0&&n<MAX_JOUEUR)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->pred;
}

void precedent(int n)
{	if(n>0&&n<MAX_JOUEUR)
		if (!hors_liste(n))
			ec[n] = ec[n]->pred;
}

void suivant(int n)
{	if(n>0&&n<MAX_JOUEUR)
		if (!hors_liste(n))
			ec[n] = ec[n]->succ;
}

void valeur_elt(int n, vector * v)
{	if(n>0&&n<MAX_JOUEUR)
		if (!hors_liste(n))
			v->x = ec[n]->coordUnit.x;
            v->y = ec[n]->coordUnit.y;
}

void modif_elt(int n, vector v)
{	if(n>0&&n<MAX_JOUEUR)
		if (!hors_liste(n))
			ec[n]->coordUnit.x = v.x;
            ec[n]->coordUnit.y = v.y;
}

void oter_elt(int n)
{	
	t_element * temp;

    	if(n>0&&n<MAX_JOUEUR)
		if (!hors_liste(n))
		{	
			(ec[n]->succ)->pred = ec[n]->pred;
			(ec[n]->pred)->succ = ec[n]->succ;
			temp = ec[n];
			ec[n] = ec[n]->pred;
			free(temp);
		}
}

void ajout_droit(int n, vector v)
{	
	t_element* nouv;
	
	if(n>0&&n<MAX_JOUEUR)
		if (liste_vide(n) || !hors_liste(n))
		{	
			nouv = malloc(sizeof(t_element));
			nouv->coordUnit.x = v.x;
            nouv->coordUnit.y = v.y;
			nouv->pred = ec[n];
			nouv->succ = ec[n]->succ;
			(ec[n]->succ)->pred = nouv;
			ec[n]->succ = nouv;
			ec[n] = nouv;
		}
}

void ajout_gauche(int n, vector v)
{	
	t_element* nouv;
	
	if(n>0&&n<MAX_JOUEUR)
		if (liste_vide(n) || !hors_liste(n))
		{	
			nouv = malloc(sizeof(t_element));
            nouv->coordUnit.x = v.x;
            nouv->coordUnit.y = v.y;
			nouv->succ = ec[n];
			nouv->pred = ec[n]->pred;
			(ec[n]->pred)->succ = nouv;
			ec[n]->pred = nouv;
			ec[n] = nouv;
		}
}

/**
 * Ajoute une unité dans la liste des unités du joueur
 * @param noPlayer  Joueur en cours       
 * @param coordUnit Coordonnées de l'unité
 */
void addUnit(int noPlayer, vector coordUnit){
	vector tmp;
	int name = grid[coordUnit.x][coordUnit.y].name;

	if(!liste_vide(noPlayer)){ // Vérifie que des unités sont dans la liste
		en_queue(noPlayer);
		valeur_elt(noPlayer, &tmp);

		if(grid[tmp.x][tmp.y].name / 2 > name ){ // Optimisation sur le traitement
			en_tete(noPlayer);
			valeur_elt(noPlayer, &tmp);
			while(!hors_liste(noPlayer) && grid[tmp.x][tmp.y].name < name){
				valeur_elt(noPlayer, &tmp);
				suivant(noPlayer);
			}
			ajout_droit(noPlayer, coordUnit);

		}else{
			en_queue(noPlayer);
			valeur_elt(noPlayer, &tmp);
			while(!hors_liste(noPlayer) && grid[tmp.x][tmp.y].name > name){
				valeur_elt(noPlayer, &tmp);
				precedent(noPlayer);
			}
			ajout_gauche(noPlayer, coordUnit);
		}

	}else{
		en_tete(noPlayer);
		ajout_droit(noPlayer, coordUnit);
	}
}

void printList(int noPlayer){
	vector tmp;
	en_tete(noPlayer);

	while(!hors_liste(noPlayer)){
		valeur_elt(noPlayer, &tmp);
		suivant(noPlayer);
		printf("Val:%i x -> %i y -> %i\n",grid[tmp.x][tmp.y].name ,tmp.x, tmp.y);
	}
}

