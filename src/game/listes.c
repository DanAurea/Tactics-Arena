/**
 @file listes.c
 @brief Listes de vecteurs
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <stdio.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/controller/manageString.h"
#include "../../include/game/listes.h"

/**
 * @struct element
 * Représente un élément de la liste
 */
typedef struct element {
	vector coordUnit; /**< Coordonnées de l'unité */
	struct element* pred; /**< Élément précédent */
	struct element* succ; /**< Élément suivant */
} t_element; /**< Définis un élément */


t_element* drapeau[NB_UNITS]; /**< Tableaux de drapeau */
t_element* ec[NB_UNITS]; /**< Tableau d'élément courant */
int targetList = NB_PLAYERS + 1; /**< Numéro de la liste des cibles */


/* Primitives de manipulation des listes */

void init_liste(int n)
{	if(n>=0&&n<= NB_PLAYERS + NB_LISTS_ENGINE)
	{
		drapeau[n] = malloc(sizeof(t_element));
		drapeau[n]->pred = drapeau[n];
		drapeau[n]->succ = drapeau[n];
		ec[n] = drapeau[n];
	}
}

void initLists(){
	for(int i = 0; i <= NB_PLAYERS + NB_LISTS_ENGINE; i++)
		init_liste(i);
}

int liste_vide(int n)
{	if(n>=0&&n<= NB_PLAYERS + NB_LISTS_ENGINE)
		return drapeau[n]->pred==drapeau[n];
    return -1;
}

int hors_liste(int n)
{	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
		return ec[n]==drapeau[n];
    return -1;
}

void en_tete(int n)
{	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->succ;
}

void en_queue(int n)
{	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
		if (!liste_vide(n))
			ec[n] = drapeau[n]->pred;
}

void precedent(int n)
{	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
		if (!hors_liste(n))
			ec[n] = ec[n]->pred;
}

void suivant(int n)
{	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
		if (!hors_liste(n))
			ec[n] = ec[n]->succ;
}

void valeur_elt(int n, vector * v)
{	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
		if (!hors_liste(n)){
			v->x = ec[n]->coordUnit.x;
            v->y = ec[n]->coordUnit.y;
		}
}

void modif_elt(int n, vector v)
{	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
		if (!hors_liste(n)){
			ec[n]->coordUnit.x = v.x;
            ec[n]->coordUnit.y = v.y;
		}
}

void oter_elt(int n)
{
	t_element * temp;

    	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
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

	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
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

	if(n>=0&&n<=NB_PLAYERS + NB_LISTS_ENGINE)
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
	if(drapeau != NULL && !liste_vide(nbList)){
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

	for(int list = 0; list <= NB_PLAYERS + NB_LISTS_ENGINE; list++){
		dumpList(list); // Libère la liste
		free(drapeau[list]); // Libère le drapeau
	}
}

/**
 * Ajoute une unité dans la liste des unités du joueur
 * @param coordUnit Coordonnées de l'unité
 */
void addUnit(vector coordUnit){
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
	unit source;

	if(!liste_vide(numList)){
		en_tete(numList);
		printf("No - Nom - X-Y - HP - Direction -  Puissance -  Recovery\n\n");

		while(!hors_liste(numList)){
			valeur_elt(numList, &tmp);
			source = grid[tmp.x][tmp.y];

			if(source.name != empty && source.name != decors){
				printf("%i - %s - %c%i - %i HP - %s - %i - %i", i,getNameUnit(source.name), 'A' + tmp.x, tmp.y + 1,
					 source.stat.HP, getDirectionUnit(source.direct), source.stat.POWER, source.stat.RECOVERY); // Affiche le nom de l'unité
			}else{
				printf("%i - %s - %c%i", i,getNameUnit(source.name), 'A' + tmp.x, tmp.y + 1); // Affiche case vide ou décor
			}


			for(int j = 0; j < NB_MAX_EFFECT; j++){
				if(source.effect[j] > 0){
					printf(" - %i", source.effect[j]);
				}
			}
			printf("\n");

			suivant(numList);
			i++;
		}
	}
}

/**
 * Détruit une unité dans la liste
 * @param coordUnit Coordonnées de l'unité à détruire
 */
void destroyUnit(vector coordUnit){
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

/**
 * Compte le nombre d'unité
 * @return          Retourne le nombre d'unité
 */
int countUnits(){
	int nbUnits = 0;

	if(!liste_vide(noPlayer)){
		en_tete(noPlayer);

		while(!hors_liste(noPlayer)){
			nbUnits++;
			suivant(noPlayer);
		}
	}

	return nbUnits;
}

/**
 * Cherche une cible dans la liste
 * @param numList Numéro de la liste
 * @param coordTarget Coordonnées de la cible
 * @return Retourne vrai si cible trouvée
 */
bool searchTarget(int numList, vector coordTarget){
	vector tmp = {-1, -1};

	if(!liste_vide(numList)){
		en_tete(numList);

		while(!hors_liste(numList) && (tmp.x != coordTarget.x || tmp.y != coordTarget.y)){ // Cherche la cible
			valeur_elt(numList, &tmp);
			
			if(tmp.x == coordTarget.x && tmp.y == coordTarget.y){ // Cible trouvée
				return true;
			}
			suivant(numList);
		}
	}

	return false;
}
