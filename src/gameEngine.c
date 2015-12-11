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
 * @param type     Type de ciblage
 * @param horizRange Portée horizontale
 * @param vertRange Portée verticale
 * @param minRange Portée minimale
 */
void setTarget(unitName name,char * type, int vertRange, int horizRange, int minRange)
{
	vector target;
	if(strcmp(type,"square") == 0)
	{
		for(int i=-vertRange;i<=vertRange;i++)
		{
			for(int j=-horizRange;j<=horizRange;j++)
			{
				if(((vertRange>horizRange && abs(i)+abs(j) <= vertRange-abs(j))||(vertRange<horizRange && abs(i)+abs(j) <= horizRange-abs(i)) || (vertRange==horizRange && abs(i)+abs(j)<= vertRange)) && abs(i)+abs(j) >= minRange)
				{
					target.x = i;
					target.y = j;
					addTarget(name,target);
				}
			}
		}
	}
	else
	{
		for(int i=-vertRange;i<=vertRange;i++)
		{
			if(abs(i) >= minRange)
			{
				target.x = i;
				target.y = 0;
				addTarget(name,target);
			}
		}
		for(int j=-horizRange;j<=horizRange;j++)
		{
			if(abs(j) >= minRange)
			{
				target.x = 0;
				target.y = j;
				addTarget(name,target);
			}
		}
	}
}

/**
 * Fait la liste des unités déplaçables
 * @param movableUnit Tableau des unités déplaçables
 * @param noPlayer    Joueur en cours
 */
void movable(vector movableUnit[], short noPlayer){
	vector coordUnit;
	en_tete(noPlayer);
	short currentUnit = 0;

	while(!hors_liste(noPlayer)){
		valeur_elt(noPlayer, &coordUnit);
		suivant(noPlayer);

		if(!isSurrounded(coordUnit) && canMove(&grid[coordUnit.x][coordUnit.y])){ // Unité non entourée par ennemi + non paralysée
			movableUnit[currentUnit] = coordUnit;
			currentUnit++;
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
void createPawn(int * nbPawns, int nbParams, unitName name, ...){
	unit pawn;
	char * type;
	short horizRange;
	short vertRange;
	short sizeRing;

	va_list stats;

	if(* nbPawns == 0){ // Alloue de la mémoire pour les pions
		pawns = malloc( (*nbPawns + 1) * sizeof(unit));
	}else{
		pawns = realloc(pawns, (*nbPawns + 1) * sizeof(unit));
	}

	if(pawns == NULL){ // Libère la mémoire en cas d'erreur
		if(*nbPawns > 0) puts("\nError reallocating memory !\n");
		else puts("\nError allocating memory !\n");
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

		if(name != cleric && name != empty && name != decors){
			type = va_arg(stats, char *);
			horizRange = va_arg(stats, int);
			vertRange  = va_arg(stats, int);
			sizeRing   = va_arg(stats, int);
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
		pawns[* nbPawns] = pawn;
		* nbPawns = * nbPawns + 1; // Agrandis le tableau pour le prochain ajout

		if(name != cleric && name != empty && name != decors) setTarget(name, type, horizRange, vertRange, sizeRing); // Définis les cibles
	}
}

void makePawns(){
	createPawn(&sizePawns, 8, empty, 0, 0, 0, 0, 0, 0, 0, 0);
	createPawn(&sizePawns, 8, decors, 0, 0, 0, 0, 0, 0, 0, 0);
	/*
		Ordre params: Nombre de pions, nombre paramètres, nom unité,
					HP, Power, Armor, Block[0], Block[1], Block[2],
					Recovery, Move_range, type targetZone, horizRange,
					vertRange, sizeRing
	*/
	createPawn(&sizePawns, 8, knight, 50, 22, 0.25, 0.8, 0.4, 0.0, 1, 3, "line", 1, 1, 1);
	createPawn(&sizePawns, 8, scout, 40, 18, 0.08, 0.6, 0.3, 0.0, 2, 4, "square", 6, 6, 1);
	createPawn(&sizePawns, 8, assassin, 35, 18, 0.12, 0.7, 0.35, 0.0, 1, 4, "line", 1, 1, 1);
	createPawn(&sizePawns, 8, cleric, 24, 12, 0.0, 0.0, 0.0, 0.0, 5, 3);
	createPawn(&sizePawns, 8, pyromancer, 30, 15, 0.0, 0.33, 0.16, 0.0, 3, 3, "square", 3, 3, 0);
	createPawn(&sizePawns, 8, enchantress, 35, 0, 0.0, 0.0, 0.0, 0.0, 3, 3, "square", 2, 2, 1);
	createPawn(&sizePawns, 8, dragonborn, 30, 22, 0.0, 0.33, 0.16, 0.0, 3, 3, "square", 3, 3, 0);
	createPawn(&sizePawns, 8, darkWitch, 28, 24, 0.0, 0.2, 0.1, 0.0, 3, 3, "line", 4, 4, 1);
	createPawn(&sizePawns, 8, lightningTotem, 56, 30, 0.18, 1.0, 1.0, 1.0, 4, 0, "square", 3, 3, 0);
	createPawn(&sizePawns, 8, barrierTotem, 32, 0, 0.0, 1.0, 1.0, 1.0, 2, 0, "square", 6, 6, 0);
	createPawn(&sizePawns, 8, mudGolem, 60, 20, 0.0, 0.0, 0.0, 0.0, 2, 5, "line", 1, 1, 1);
	createPawn(&sizePawns, 8, golemAmbusher, 60, 20, 0.0, 0.0, 0.0, 0.0, 3, 2, "square", 6, 6, 5);
	createPawn(&sizePawns, 8, frostGolem, 60, 0, 0.0, 0.0, 0.0, 0.0, 2, 2, "square", 4, 4, 1);
	createPawn(&sizePawns, 8, stoneGolem, 60, 0, 0.3, 0.0, 0.0, 0.0, 4, 2, "line", 1, 1, 0);
	createPawn(&sizePawns, 8, dragonTyrant, 28, 24, 0.0, 0.2, 0.1, 0.0, 3, 3, "line", 3, 3, 1);
	createPawn(&sizePawns, 8, berserker, 42, 22, 0.0, 0.25, 0.12, 0.0, 1, 3, "line", 1, 1, 1);
	createPawn(&sizePawns, 8, beastRider, 38, 19, 0.15, 0.45, 0.22, 0.0, 1, 4, "line", 2, 2, 1);
	createPawn(&sizePawns, 8, poisonWisp, 34, 0, 0.0, 0.0, 0.0, 0.0, 2, 6, "line", 2, 2, 1);
	createPawn(&sizePawns, 8, furgon, 48, 0, 0.0, 0.5, 0.25, 0.0, 1, 3, "square", 2, 2, 0);

}

/**
 * Permet de savoir si l'unité courante est entourée
 * @param  currentUnit Unité courante
 * @return             Retourne vrai si unité entourée
 */
bool isSurrounded(vector currentUnit){
	bool surrounded = true;
	unit * source = &grid[currentUnit.x][currentUnit.y];
	unit * target = NULL;

	for(int x = - 1; x <=  1 && surrounded; x++)
	{
		for(int y =  -1; y <= 1 && surrounded; y++)
		{
			if(abs(x) + abs(y) == 1 && currentUnit.x+x >= 0 && currentUnit.x+x < N && currentUnit.y+y >= 0 && currentUnit.y+y < N){ // Croix centrée sur l'unité courante
				target = &grid[currentUnit.x+x][currentUnit.y+y];

				if(target->name == empty){
					surrounded=false;
				}else if(target->name != decors){
					if(source->noPlayer == target->noPlayer && canGetPassed(target)){ // Unité allié pouvant être traversée
						surrounded=false;
					}
				}
			}
		}
	}

	return surrounded;
}

/**
 * Sélectionne une unité
 * @param  coordUnit Coordoonnées de l'unité
 * @return           Retourne vrai si unité bien sélectionnée
 */
bool selectUnit(vector * coordUnit, short noPlayer){
	char * coordString;
	unitName name;

	coordString = (char *) calloc(5, sizeof(char));

	if(coordString == NULL){
		free(coordString);
		return false;
	}else{

		do{
			read(coordString, 5);
		}while(!correctCoord(coordString));

		getCoordS(coordString, coordUnit); // Récupère les coordonnées saisies sous forme de vecteur
		free(coordString);

		name = grid[coordUnit->x][coordUnit->y].name;

		if( name == empty || name == decors) return false;
		else if(coordUnit->x < 0 || coordUnit->x > N || coordUnit->y < 0 || coordUnit->y > N) return false;
		else if(grid[coordUnit->x][coordUnit->y].noPlayer != noPlayer) return false;

		return true;
	}
}

/**
 * Initialise la grille
 */
void gridInit(){
	int x, y, nbDecors = 0;
	vector coordUnit;

	for(x = 0; x < N; x++){
		for(y = 0; y < N; y++){
			coordUnit.x = x;
			coordUnit.y = y;

			grid[x][y].name = empty; // Initialise à vide

			if(x >= 0 + NB_LINES && x < N - NB_LINES && nbDecors < 7){
				if(rand() % 100 > 94){ // Ajoute un décor aléatoirement
					grid[x][y].name = decors;
					nbDecors++;
				}
			}

			unitInit(-1, coordUnit); // Initialise avec les données par défaut
			grid[x][y].unitColor = white;

		}
	}
}


/**
 * Placement des unités par le joueur
 * @param noPlayer Joueur en cours
 * @param nbUnit   Nombre d'unités restantes à placer
 */
void playerAddUnit(short noPlayer, int * nbUnit){
	int unitSelected;
	char * coordString = NULL;
	vector coordUnit;
	vector movableUnit[NB_MAX_UNIT];

	unitList(); // Affiche la liste des unités du jeu

	do{
		printf("Choisissez le type d'unité: ");
		scanf("%i", &unitSelected);

		if(unitSelected < knight -1 || unitSelected > furgon -1)
			printf("Aucune unité de ce type ! \n");

	}while(unitSelected < knight -1 || unitSelected > furgon -1);

	coordString = calloc(5, sizeof(char));

	clearBuffer(); // Vide stdin

	do{
		fontColor(red);
		if(noPlayer == FIRST_PLAYER){
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i au format a/A 01 \n",'A' + N - 1, 'A' + N - NB_LINES, N);
		}else{
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i au format a/A 01 \n",'A', 'A' + NB_LINES - 1, N);
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

	if(grid[coordUnit.x][coordUnit.y].name != 0){
		destroyUnit(noPlayer, coordUnit); // Détruit l'unité en place
		* nbUnit = * nbUnit - 1; // Remet à jour le nombre d'unités
	}

	grid[coordUnit.x][coordUnit.y].name = unitSelected + 1; // Place l'unité correspondante dans la grille

	unitInit(noPlayer, coordUnit); // Initialise l'unité ajoutée

	addUnit(noPlayer, coordUnit);

	movable(movableUnit, noPlayer);
	clearScreen();
	gridDisp(); // Affiche la grille actualisée
}

/**
 * Initiliase la liste des unités du joueur
 */
void playerInit(short noPlayer){

	printf("\nJoueur %i: \n\n", noPlayer + 1); // Initialisation du joueur 1
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);
		printf("Il reste %i unités.\n", NB_MAX_UNIT - i);
		fontColor(white);

		playerAddUnit(noPlayer, &i); // Ajout unité joueur 1
	}
}

/**
 * Initialise la partie
 * @param noPlayer Entier réprésentant le joueur
 */
void gameInit(short * noPlayer){
	srand(time(NULL));

	for(int i = 0; i < NB_UNITS; i++)
		init_liste(i);

	makePawns(); // Crée les pions

	gridInit(); // Crée la grille
    gridDisp(); // Affiche la grille

	playerInit(FIRST_PLAYER); // Initialisation du joueur 1
	playerInit(FIRST_PLAYER + 1);
	* noPlayer = (rand() % (FIRST_PLAYER + 1)) + 1; // Tire le joueur débutant la partie aléatoirement
}
