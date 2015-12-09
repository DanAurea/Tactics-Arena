/* Mise en oeuvre contigue d'un tableau de listes de vecteurs */
#include <stdio.h>
#include "../include/gameEngine.h"
#include "../include/manageString.h"
#include "../include/listes.h"

/* Definition du type d'un element de liste */
typedef struct element {vector coordUnit; struct element* pred; struct element* succ;} t_element;

/* Declaration des listes (drapeau et element courant) */
t_element* drapeau[NB_UNITS];
t_element* ec[NB_UNITS];


/* Primitives de manipulation des listes */

void init_liste(int n)
{	if(n>=0&&n<NB_UNITS)
	{		
		drapeau[n] = malloc(sizeof(t_element));
		drapeau[n]->pred = drapeau[n];
		drapeau[n]->succ = drapeau[n];
		ec[n] = drapeau[n];
	}
}

int liste_vide(int n)
{	if(n>=0&&n<NB_UNITS)
		return drapeau[n]->pred==drapeau[n];
    return -1;
}

int hors_liste(int n)
{	if(n>=0&&n<NB_UNITS)
		return ec[n]==drapeau[n];
    return -1;
}

void en_tete(int n)
{	if(n>=0&&n<NB_UNITS)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->succ;
}

void en_queue(int n)
{	if(n>=0&&n<NB_UNITS)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->pred;
}

void precedent(int n)
{	if(n>=0&&n<NB_UNITS)
		if (!hors_liste(n))
			ec[n] = ec[n]->pred;
}

void suivant(int n)
{	if(n>=0&&n<NB_UNITS)
		if (!hors_liste(n))
			ec[n] = ec[n]->succ;
}

void valeur_elt(int n, vector * v)
{	if(n>=0&&n<NB_UNITS)
		if (!hors_liste(n))
			v->x = ec[n]->coordUnit.x;
            v->y = ec[n]->coordUnit.y;
}

void modif_elt(int n, vector v)
{	if(n>=0&&n<NB_UNITS)
		if (!hors_liste(n))
			ec[n]->coordUnit.x = v.x;
            ec[n]->coordUnit.y = v.y;
}

void oter_elt(int n)
{	
	t_element * temp;

    	if(n>=0&&n<NB_UNITS)
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
	
	if(n>=0&&n<NB_UNITS)
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
	
	if(n>=0&&n<NB_UNITS)
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
void addUnit(short noPlayer, vector coordUnit){
	vector tmp;
	int nameUnit = grid[coordUnit.x][coordUnit.y].name;

	en_tete(noPlayer);

	if(liste_vide(noPlayer)) ajout_droit(noPlayer, coordUnit);
	else{
		valeur_elt(noPlayer,&tmp);

		while(!hors_liste(noPlayer) && grid[tmp.x][tmp.y].name < nameUnit){ // Tri de la liste à la volée
			suivant(noPlayer);
			valeur_elt(noPlayer,&tmp);
		}

		if(hors_liste(noPlayer)){ // Sortie de liste
			en_queue(noPlayer);
			ajout_droit(noPlayer, coordUnit);
		}else{
			ajout_gauche(noPlayer, coordUnit);
		}
	}

}

/**
 * Affiche la liste des unités
 * @param noPlayer [description]
 */
void printList(short noPlayer){
	int i = 1;
	vector tmp;
	en_tete(noPlayer);

	while(!hors_liste(noPlayer) && !liste_vide(noPlayer)){
		valeur_elt(noPlayer, &tmp);
		printf("%i - %s - %c - %i\n", i,getNameUnit(grid[tmp.x][tmp.y].name), 'A' + tmp.x, tmp.y + 1); // Affiche le nom de l'unité
		suivant(noPlayer);
		i++;
	}
}

/**
 * Détruit une unité dans la liste
 * @param noPlayer  Joueur en cours
 * @param coordUnit Coordonnées de l'unité à détruire
 */
void destroyUnit(short noPlayer, vector coordUnit){
	vector tmp;

	en_tete(noPlayer);
	valeur_elt(noPlayer, &tmp);

	while(!hors_liste(noPlayer) && (tmp.x != coordUnit.x || tmp.y != coordUnit.y) ){ // Cherche l'unité dans la liste
		suivant(noPlayer);
		valeur_elt(noPlayer, &tmp);
	}
	
	if(tmp.x == coordUnit.x && tmp.y == coordUnit.y){ // Unité trouvée
		oter_elt(noPlayer);
	}
}
