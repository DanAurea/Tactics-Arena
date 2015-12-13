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
{	if(n>=0&&n<=NB_UNITS)
	{
		drapeau[n] = malloc(sizeof(t_element));
		drapeau[n]->pred = drapeau[n];
		drapeau[n]->succ = drapeau[n];
		ec[n] = drapeau[n];
	}
}

void initLists(){
	for(int i = 0; i <= NB_UNITS; i++)
		init_liste(i);
}

int liste_vide(int n)
{	if(n>=0&&n<=NB_UNITS)
		return drapeau[n]->pred==drapeau[n];
    return -1;
}

int hors_liste(int n)
{	if(n>=0&&n<=NB_UNITS)
		return ec[n]==drapeau[n];
    return -1;
}

void en_tete(int n)
{	if(n>=0&&n<=NB_UNITS)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->succ;
}

void en_queue(int n)
{	if(n>=0&&n<=NB_UNITS)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->pred;
}

void precedent(int n)
{	if(n>=0&&n<=NB_UNITS)
		if (!hors_liste(n))
			ec[n] = ec[n]->pred;
}

void suivant(int n)
{	if(n>=0&&n<=NB_UNITS)
		if (!hors_liste(n))
			ec[n] = ec[n]->succ;
}

void valeur_elt(int n, vector * v)
{	if(n>=0&&n<=NB_UNITS)
		if (!hors_liste(n)){
			v->x = ec[n]->coordUnit.x;
            v->y = ec[n]->coordUnit.y;
		}
}

void modif_elt(int n, vector v)
{	if(n>=0&&n<=NB_UNITS)
		if (!hors_liste(n)){
			ec[n]->coordUnit.x = v.x;
            ec[n]->coordUnit.y = v.y;
		}
}

void oter_elt(int n)
{
	t_element * temp;

    	if(n>=0&&n<=NB_UNITS)
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

	if(n>=0&&n<=NB_UNITS)
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

	if(n>=0&&n<=NB_UNITS)
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
 * Vide une liste
 * @param nbList Numéro de la liste à vider
 */
void dumpList(short nbList){
	if(!liste_vide(nbList)){
		en_queue(nbList);
		while(!liste_vide(nbList)){
			oter_elt(nbList);
		}
	}
}

/**
 * Vide toutes les listes
 */
void dumpAllLists(){
	
	for(int list = 0; list <= NB_UNITS; list++){
		dumpList(list); // Libère la liste
		free(drapeau[list]); // Libère le drapeau
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

	if(liste_vide(noPlayer)) ajout_droit(noPlayer, coordUnit);
	else{
		en_queue(noPlayer);
		valeur_elt(noPlayer,&tmp);

		if(grid[tmp.x][tmp.y].name <= nameUnit){ // Optimise le traitement
			ajout_droit(noPlayer, coordUnit);
		}else{

			en_tete(noPlayer); // On se replace en tête si l'unité n'a pas été placée
			valeur_elt(noPlayer,&tmp);

			while(!hors_liste(noPlayer) && grid[tmp.x][tmp.y].name < nameUnit){ // Tri de la liste à la volée
				suivant(noPlayer);
				valeur_elt(noPlayer,&tmp);
			}
			ajout_gauche(noPlayer, coordUnit);

		}
	}

}

/**
 * Ajoute une cible pour une unité
 * @param name      Nom de l'unité
 * @param coordUnit Coordonnées de l'unité
 */
void addTarget(unitName name, vector coordUnit){
	if(!liste_vide(name)){
		en_queue(name);
	}
	ajout_droit(name, coordUnit);
}

/**
 * Affiche la liste désirée
 * @param numList Numéro de liste
 */
void printList(short numList){
	int i = 1;
	vector tmp;
	en_tete(numList);

	while(!hors_liste(numList) && !liste_vide(numList)){
		valeur_elt(numList, &tmp);

		if(numList <= FIRST_PLAYER + 1){
			printf("%i - %s - %c - %i\n", i,getNameUnit(grid[tmp.x][tmp.y].name), 'A' + tmp.x, tmp.y + 1); // Affiche le nom de l'unité
		}else{
			printf("%i - %s - %i - %i\n", i, getNameUnit(numList), tmp.x, tmp.y); // Affiche le nom de l'unité et ses cibles
		}
		suivant(numList);
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
