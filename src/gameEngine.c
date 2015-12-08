#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include "../include/gameEngine.h"
#include "../include/grid.h"
#include "../include/terminal.h"
#include "../include/unit.h"
#include "../include/menu.h"
#include "../include/listes.h"
#include "../include/manageString.h"

unit grid[N][N]; /**< Grille d'unités */
unit * pawns = NULL; /**< Pions initialisés avec leur valeurs */

/**
 * Initialise un pion
 * @param pawn Pion à initialiser
 */
void initPawn(unit * pawn){
	pawn->stat.HP = -1;
	pawn->stat.POWER = -1;
	pawn->stat.ARMOR = -1;
	
	pawn->stat.BLOCK[0] = -1;
	pawn->stat.BLOCK[1] = -1;
	pawn->stat.BLOCK[2] = -1;
	
	pawn->stat.RECOVERY = -1;
	pawn->stat.MOVE_RANGE = -1;
	
	for(int i = 0; i < NB_MAX_EFFECT; i++){
		pawn->effect[i] = none;
	}
}

/**
 * Vérifie que le pion est correct
 * @param  pawn Pion à vérifier
 * @return      Retourne vrai si le pion est correct
 */
bool checkPawn(unit pawn){
	if(pawn.stat.HP == -1 || pawn.stat.POWER == -1 
		|| pawn.stat.ARMOR == -1) return false;
	
	if(pawn.stat.BLOCK[0] == -1 || pawn.stat.BLOCK[1] == -1 
		|| pawn.stat.BLOCK[2] == -1) return false;
	if(pawn.stat.RECOVERY == -1 || pawn.stat.MOVE_RANGE == -1) return false;
	
	return true;
}

/**
 * Crée un pion pour le jeu
 * @param n Nombre de pions actuel
 * @param nbParams Nombre de stats pour le pion
 * @param name Nom du pion
 */
void createPawn(int * nbPawns, int nbParams, unitName name, ...){
	unit  pawn;
	va_list stats;

	if(* nbPawns == 0){ // Alloue de la mémoire pour les pions
		pawns = malloc( *nbPawns + 1 * sizeof(unit));
		if(pawns == NULL){
			puts("\nError allocating memory !\n");
		}
	}else{
		pawns = realloc(pawns, *nbPawns + 1 * sizeof(unit));
		if(pawns == NULL){
			puts("\nError reallocating memory !\n");
		}
	}

	if(pawns == NULL){ // Libère la mémoire en cas d'erreur
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
	}else{
		printf("\nError not enough parameters for pawn creation !\n");
	}

	va_end(stats);


	if(!checkPawn(pawn)){ // Vérifie les valeurs passées en paramètres
		printf("\n Error during pawn creation, %s couldn't be initialized correctly !\n",
				getNameUnit(pawn.name));
		exit(1);
	}else{
		pawns[* nbPawns] = pawn;
		* nbPawns = * nbPawns + 1; // Agrandis le tableau pour le prochain ajout
	}
}

/**
 * Permet de savoir si l'unité courante est entourée
 * @param  currentUnit Unité courante
 * @return             True si unité entourée
 */
bool lookAround(vector currentUnit)
{
	bool surrounded = true;

	for(int i = currentUnit.x - 1; i < currentUnit.x + 1 && surrounded; i++)
	{
		for(int j = currentUnit.y - 1; j < currentUnit.y + 1 && surrounded; j++)
		{
			if(abs(i) + abs(j) == 1)
			{
				if(grid[currentUnit.x+i][currentUnit.y].name == empty)
				{
					//TODO
					// verif si unité ennemi.
					// verif si unité allié avec canGetPassed().
					surrounded=false;
				}
			}
		}
	}
	return surrounded;
}

/**
 * Sélectionne une unité
 * @param  coordUnit [description]
 * @return           [description]
 */
bool selectUnit(vector * coordUnit, short noPlayer){
	char * coordString;
	unitName name;

	do{
		coordString = (char *) calloc(5, sizeof(char));
		read(coordString, 5);
	}while(!correctCoord(coordString));

	getCoordS(coordString, coordUnit); // Récupère les coordonnées saisies sous forme de vecteur

	name = grid[coordUnit->x][coordUnit->y].name;

	if( name == empty || name == decors) return false;
	else if(coordUnit->x < 0 || coordUnit->x > N || coordUnit->y < 0 || coordUnit->y > N) return false;
	else if(grid[coordUnit->x][coordUnit->y].noPlayer != noPlayer) return false;
	
	return true;
}

/**
 * Initialise la grille
 */
void gridInit(){
	int x, y, nbDecors = 0;

	for(x = 0; x < N; x++){
		for(y = 0; y < N; y++){
			grid[x][y].name = empty; // Initialise à vide
			grid[x][y].noPlayer = -1;
			grid[x][y].unitColor = white;

			if(x >= 0 + NB_LINES && x < N - NB_LINES && nbDecors < 7){
				if(rand() % 100 > 92){ // Ajoute un décor aléatoirement
					grid[x][y].name = decors;
					nbDecors++;
				}
			}

		}
	}
}

/**
 * Placement des unités par le joueur
 * @param noPlayer Joueur en cours 
 * @param nbUnit   
 */
void playerAddUnit(short noPlayer, int * nbUnit){
	int unitSelected;
	char * coordString;
	vector coordUnit;

	unitList(); // Affiche la liste des unités du jeu
	
	do{
		printf("Choisissez le type d'unité: ");
		scanf("%i", &unitSelected);

		if(unitSelected < knight -1 || unitSelected > furgon -1)
			printf("Aucune unité de ce type ! \n");

	}while(unitSelected < knight -1 || unitSelected > furgon -1);

	coordString = (char *) calloc(5, sizeof(char));
	
	clearBuffer(); // Vide stdin
	
	do{
		fontColor(red);
		if(noPlayer == 1){
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i au format A 01 \n",'A' + N - 1, 'A' + N - NB_LINES, N);
		}else{
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i au format A 01 \n",'A', 'A' + NB_LINES - 1, N);
		}
		fontColor(white);
		
		printf("Quelles sont les coordonnées de l'unité à placer ?\n");

		read(coordString, 5); // Saisie sécurisée

		if(!correctCoord(coordString)){
			printf("Coordonnées incorrectes !\n");
		}
		if(!rightSide(coordString, noPlayer)){
			printf("Unité non placée dans le bon camp !");
		}
	}
	while(!correctCoord(coordString) || !rightSide(coordString, noPlayer));

	getCoordS(coordString, &coordUnit); // Récupère les coordonnées saisies sous forme de vecteur
	free(coordString);
	
	if(grid[coordUnit.x][coordUnit.y].name != empty){ 
		destroyUnit(noPlayer, coordUnit); // Détruit l'unité en place
		* nbUnit = * nbUnit - 1; // Remet à jour le nombre d'unités
	}

	grid[coordUnit.x][coordUnit.y].name = unitSelected + 1; // Place l'unité correspondante dans la grille
	
	unitInit(noPlayer, coordUnit); // Initialise l'unité ajoutée
	addUnit(noPlayer, coordUnit);

	clearScreen();
	gridDisp(); // Affiche la grille actualisée
}

/**
 * Initiliase la liste des unités du joueur
 */
void playersInit(){

	printf("\nJoueur 1: \n\n"); // Initialisation du joueur 1
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);
		printf("Il reste %i unités.\n", NB_MAX_UNIT - i);
		fontColor(white);

		playerAddUnit(1, &i); // Ajout unité joueur 1
	}
	
	printf("\nJoueur 2: \n\n"); // Initialisation du joueur 2
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);
		printf("Il reste %i unités.\n", NB_MAX_UNIT - i);
		fontColor(white);

		playerAddUnit(2, &i); // Ajout unité joueur 2
	}
}

/**
 * Initialise la partie
 * @param noPlayer Entier réprésentant le joueur
 */
void gameInit(short * noPlayer){
	srand(time(NULL));

	for(int i = 1; i < MAX_JOUEUR; i++)
		init_liste(i);

	gridInit();
	playersInit();
	* noPlayer = (rand() % 2) + 1; // Tire le joueur débutant la partie aléatoirement
}
