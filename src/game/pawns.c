/**
 @file pawns.c
 @brief Gestion des pions
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

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
		pawn->effect[i] = 0;
	}
	pawn->unitColor = white;
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
 * @param nbParams Nombre de stats pour le pion
 * @param name Nom du pion
 */
void createPawn(int nbParams, unitName name, ...){
	unit pawn;

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
			if(i == 8) pawn.stat.target.vertRange = va_arg(stats, int);
			if(i == 9) pawn.stat.target.horizRange = va_arg(stats, int);
			if(i == 10) pawn.stat.target.ringSize = va_arg(stats, int);
			if(i == 11) pawn.stat.target.line = va_arg(stats, int);
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
	}
}

/**
 * Crée tout les pions utiles au jeu
 */
void makePawns(){

	if(sizePawns == 0){ // On ne crée les pions qu'en cas de nécessité -> 1 er lancement du jeu
		createPawn(12, empty, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0);
		createPawn(12, decors, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0);
		/*
			Ordre params: Nombre paramètres obligatoires, nom unité,
						HP, Power, Armor,
						Block[0], Block[1], Block[2],
						Recovery, Move_range,
						horizRange, vertRange, sizeRing, line
		*/
		createPawn(12, knight, 50, 22, 0.25,           0.8, 0.4, 0.0,       1, 3,          1, 1, 1, 1);
		createPawn(12, scout, 40, 18, 0.08,            0.6, 0.3, 0.0,       2, 4,          6, 6, 1, 0);
		createPawn(12, assassin, 35, 18, 0.12,         0.7, 0.35, 0.0,      1, 4,          1, 1, 1, 1);
		createPawn(12, cleric, 24, 12, 0.0,            0.0, 0.0, 0.0,       5, 3,		   0, 0, 0, 0); // Unité n'ayant pas besoin de cible
		createPawn(12, pyromancer, 30, 15, 0.0,        0.33, 0.16, 0.0,     3, 3,          3, 3, 0, 0);
		createPawn(12, enchantress, 35, 0, 0.0,        0.0, 0.0, 0.0,       3, 3,          2, 2, 1, 0);
		createPawn(12, dragonborn, 30, 22, 0.0,        0.33, 0.16, 0.0,     3, 3,          3, 3, 0, 0);
		createPawn(12, darkWitch, 28, 24, 0.0,         0.2, 0.1, 0.0,       3, 3,          4, 4, 1, 1);
		createPawn(12, lightningTotem, 56, 30, 0.18,   1.0, 1.0, 1.0,       4, 0,          3, 3, 0, 0);
		createPawn(12, barrierTotem, 32, 0, 0.0,       1.0, 1.0, 1.0,       2, 0,          6, 3, 0, 0);
		createPawn(12, mudGolem, 60, 20, 0.0,          0.0, 0.0, 0.0,       2, 5,          1, 1, 1, 1);
		createPawn(12, golemAmbusher, 60, 20, 0.0,     0.0, 0.0, 0.0,       3, 2,          6, 6, 5, 0);
		createPawn(12, frostGolem, 60, 0, 0.0,         0.0, 0.0, 0.0,       2, 2,          4, 4, 1, 0);
		createPawn(12, stoneGolem, 60, 0, 0.3,         0.0, 0.0, 0.0,       4, 2,          1, 1, 0, 1);
		createPawn(12, dragonTyrant, 28, 24, 0.16,      0.2, 0.1, 0.0,       3, 4,          3, 3, 1, 1);
		createPawn(12, berserker, 42, 22, 0.0,         0.25, 0.12, 0.0,     1, 3,          1, 1, 1, 1);
		createPawn(12, beastRider, 38, 19, 0.15,       0.45, 0.22, 0.0,     1, 4,          2, 2, 1, 1);
		createPawn(12, poisonWisp, 34, 0, 0.0,         0.0, 0.0, 0.0,       2, 6,          2, 2, 1, 1);
		createPawn(12, furgon, 48, 0, 0.0,             0.5, 0.25, 0.0,      1, 3,          2, 2, 0, 0);
	}

}