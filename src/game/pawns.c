#include <stdio.h>
#include <stdarg.h>
#include "../../include/game/engine.h"
#include "../../include/game/listes.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"

unit * pawns = NULL; /**< Pions initialisés avec leur valeurs */
int sizePawns = 0;

/**
 * Initialise un pion
 * @param pawn Pion à initialiser
 */
void initPawn(unit * pawn){
	memset(pawn, -1, sizeof(unit));

	for(int i = 0; i < NB_MAX_EFFECT; i++){
		pawn->effect[i] = none;
	}
	pawn->unitColor = white;
}

/**
 * Initialise les cibles du pion
 * @param name     Nom du pion 
 * @param horizRange Portée horizontale
 * @param vertRange Portée verticale
 * @param minRange Portée minimale
 * @param line Attaque en ligne -> Possible de l'omettre si ciblage sur des lignes de 1 cases
 */
void setTarget(unitName name, short vertRange, short horizRange, short ringSize, short line)
{	short min, max;
	vector target;
	
	if(vertRange > horizRange){ // Détermine quelle est la portée min et max
		max = abs(vertRange);
		min = abs(horizRange);
	}else if(vertRange < horizRange){
		max = abs(horizRange);
		min = abs(vertRange);
	}else{
		max = abs(vertRange);
		min = abs(vertRange);
	}

	for(int i = -vertRange; i <= vertRange; i++){
		for(int j = -horizRange; j <= horizRange; j++){

			if( ((abs(i) + abs(j) <= min && line == 0) 
				|| (i == 0 && j <= max) 
				|| ( j == 0 && i <= max)) 
				&& abs(i) + abs(j) >= ringSize){ // Sélection des cibles de manière flexible et personnalisée
					
					target.x = i;
					target.y = j;
					addTarget(name,target); // Ajoute une cible pour le pion
			}

		}
	}
	
}

/**
 * Vérifie que le pion est correct
 * @param  pawn Pion à vérifier
 * @return      Retourne vrai si le pion est correct
 */
bool checkPawn(unit * pawn){

	if(pawn->stat.HP == -1 || pawn->stat.POWER == -1 || pawn->stat.ARMOR == -1) return false;
	if(pawn->stat.BLOCK[0] == -1 || pawn->stat.BLOCK[1] == -1 || pawn->stat.BLOCK[2] == -1) return false;
	if(pawn->stat.RECOVERY == -1 || pawn->stat.MOVE_RANGE == -1) return false;

	return true;
}

/**
 * Crée un pion pour le jeu
 * @param n Nombre de pions actuel
 * @param nbParams Nombre de stats pour le pion
 * @param name Nom du pion
 */
void createPawn(int nbParams, unitName name, ...){
	unit pawn;
	short line;
	short horizRange;
	short vertRange;
	short sizeRing;

	va_list stats;

	if(sizePawns == 0){ // Alloue de la mémoire pour les pions
		pawns = malloc( (sizePawns + 1) * sizeof(unit));
	}else{
		pawns = realloc(pawns, (sizePawns + 1) * sizeof(unit));
	}

	if(pawns == NULL){ // Libère la mémoire en cas d'erreur
		if(sizePawns > 0) color(red, "\nError reallocating memory !\n");
		else color(red, "\nError allocating memory !\n");
		free(pawns);
		exit(1);
	}

	initPawn(&pawn); // Initialise le pion
	pawn.name = name;

	va_start(stats, name);

	if(nbParams >= MANDATORY_STATS){
		for(int i = 0; i < MANDATORY_STATS; i++){ // Initialise le pion avec les paramètres désirés
			if(i == 0) pawn.stat.HP = va_arg(stats, int);
			if(i == 1) pawn.stat.POWER = va_arg(stats, int);
			if(i == 2) pawn.stat.ARMOR = va_arg(stats, double);
			if(i == 3) pawn.stat.BLOCK[0] = va_arg(stats, double);
			if(i == 4) pawn.stat.BLOCK[1] = va_arg(stats, double);
			if(i == 5) pawn.stat.BLOCK[2] = va_arg(stats, double);
			if(i == 6) pawn.stat.RECOVERY = va_arg(stats, int);
			if(i == 7) pawn.stat.MOVE_RANGE = va_arg(stats, int);
		}

		if(name != cleric && name != empty && name != decors){ // Récupère les données sur les cibles
			horizRange = va_arg(stats, int);
			vertRange  = va_arg(stats, int);
			sizeRing   = va_arg(stats, int);
			line       = va_arg(stats, int);
		}

	}else{
		printf("\nError not enough parameters for pawn creation !\n");
	}

	va_end(stats);


	if(!checkPawn(&pawn)){ // Vérifie les valeurs passées en paramètres
		printf("\n Error during pawn creation, %s couldn't be initialized correctly !\n",
				getNameUnit(pawn.name));
		exit(1);
	}else{
		pawns[sizePawns] = pawn;
		sizePawns++; // Agrandis le tableau pour le prochain ajout

		if(name != cleric && name != empty && name != decors) setTarget(name, horizRange, vertRange, sizeRing, line); // Définis les cibles
	}
}

/**
 * Crée tout les pions utiles au jeu
 */
void makePawns(){

	if(sizePawns == 0){ // On ne crée les pions qu'en cas de nécessité -> 1 er lancement du jeu
		createPawn(8, empty, 0, 0, 0, 0, 0, 0, 0, 0);
		createPawn(8, decors, 0, 0, 0, 0, 0, 0, 0, 0);
		/*
			Ordre params: Nombre paramètres obligatoires, nom unité,
						HP, Power, Armor, 
						Block[0], Block[1], Block[2],
						Recovery, Move_range, TP,
						horizRange, vertRange, sizeRing, line
		*/
		createPawn(8, knight, 50, 22, 0.25,           0.8, 0.4, 0.0,       1, 3,          1, 1, 1, 1);
		createPawn(8, scout, 40, 18, 0.08,            0.6, 0.3, 0.0,       2, 4,          6, 6, 1, 0);
		createPawn(8, assassin, 35, 18, 0.12,         0.7, 0.35, 0.0,      1, 4,          1, 1, 1, 1);
		createPawn(8, cleric, 24, 12, 0.0,            0.0, 0.0, 0.0,       5, 3); // Unité n'ayant pas besoin de cible
		createPawn(8, pyromancer, 30, 15, 0.0,        0.33, 0.16, 0.0,     3, 3,          3, 3, 0, 0);
		createPawn(8, enchantress, 35, 0, 0.0,        0.0, 0.0, 0.0,       3, 3,          2, 2, 1, 0);
		createPawn(8, dragonborn, 30, 22, 0.0,        0.33, 0.16, 0.0,     3, 3,          3, 3, 0, 0);
		createPawn(8, darkWitch, 28, 24, 0.0,         0.2, 0.1, 0.0,       3, 3,          4, 4, 1, 1);
		createPawn(8, lightningTotem, 56, 30, 0.18,   1.0, 1.0, 1.0,       4, 0,          3, 3, 0, 0);
		createPawn(8, barrierTotem, 32, 0, 0.0,       1.0, 1.0, 1.0,       2, 0,          6, 6, 0, 0);
		createPawn(8, mudGolem, 60, 20, 0.0,          0.0, 0.0, 0.0,       2, 5,          1, 1, 1, 1);
		createPawn(8, golemAmbusher, 60, 20, 0.0,     0.0, 0.0, 0.0,       3, 2,          6, 6, 5, 0);
		createPawn(8, frostGolem, 60, 0, 0.0,         0.0, 0.0, 0.0,       2, 2,          4, 4, 1, 0);
		createPawn(8, stoneGolem, 60, 0, 0.3,         0.0, 0.0, 0.0,       4, 2,          1, 1, 0, 1);
		createPawn(8, dragonTyrant, 28, 24, 0.0,      0.2, 0.1, 0.0,       3, 3,          3, 3, 1, 1);
		createPawn(8, berserker, 42, 22, 0.0,         0.25, 0.12, 0.0,     1, 3,          1, 1, 1, 1);
		createPawn(8, beastRider, 38, 19, 0.15,       0.45, 0.22, 0.0,     1, 4,          2, 2, 1, 1);
		createPawn(8, poisonWisp, 34, 0, 0.0,         0.0, 0.0, 0.0,       2, 6,          2, 2, 1, 1);
		createPawn(8, furgon, 48, 0, 0.0,             0.5, 0.25, 0.0,      1, 3,          2, 2, 0, 0);
	}

}