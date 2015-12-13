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
	short line;
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
		if(*nbPawns > 0) color(red, "\nError reallocating memory !\n");
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
			line   = va_arg(stats, int);
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

		if(name != cleric && name != empty && name != decors) setTarget(name, horizRange, vertRange, sizeRing, line); // Définis les cibles
	}
}

void makePawns(){

	if(sizePawns == 0){ // On ne crée les pions qu'en cas de nécessité -> 1 er lancement du jeu
		createPawn(&sizePawns, 8, empty, 0, 0, 0, 0, 0, 0, 0, 0);
		createPawn(&sizePawns, 8, decors, 0, 0, 0, 0, 0, 0, 0, 0);
		/*
			Ordre params: Nombre de pions, nombre paramètres, nom unité,
						HP, Power, Armor, 
						Block[0], Block[1], Block[2],
						Recovery, Move_range, 
						horizRange, vertRange, sizeRing, line
		*/
		createPawn(&sizePawns, 8, knight, 50, 22, 0.25,           0.8, 0.4, 0.0,       1, 3,         1, 1, 1, 1);
		createPawn(&sizePawns, 8, scout, 40, 18, 0.08,            0.6, 0.3, 0.0,       2, 4,         6, 6, 1, 0);
		createPawn(&sizePawns, 8, assassin, 35, 18, 0.12,         0.7, 0.35, 0.0,      1, 4,         1, 1, 1, 1);
		createPawn(&sizePawns, 8, cleric, 24, 12, 0.0,            0.0, 0.0, 0.0,       5, 3); // Unité n'ayant pas besoin de cible
		createPawn(&sizePawns, 8, pyromancer, 30, 15, 0.0,        0.33, 0.16, 0.0,     3, 3,         3, 3, 0, 0);
		createPawn(&sizePawns, 8, enchantress, 35, 0, 0.0,        0.0, 0.0, 0.0,       3, 3,         2, 2, 1, 0);
		createPawn(&sizePawns, 8, dragonborn, 30, 22, 0.0,        0.33, 0.16, 0.0,     3, 3,         3, 3, 0, 0);
		createPawn(&sizePawns, 8, darkWitch, 28, 24, 0.0,         0.2, 0.1, 0.0,       3, 3,         4, 4, 1, 1);
		createPawn(&sizePawns, 8, lightningTotem, 56, 30, 0.18,   1.0, 1.0, 1.0,       4, 0,         3, 3, 0, 0);
		createPawn(&sizePawns, 8, barrierTotem, 32, 0, 0.0,       1.0, 1.0, 1.0,       2, 0,         6, 6, 0, 0);
		createPawn(&sizePawns, 8, mudGolem, 60, 20, 0.0,          0.0, 0.0, 0.0,       2, 5,         1, 1, 1, 1);
		createPawn(&sizePawns, 8, golemAmbusher, 60, 20, 0.0,     0.0, 0.0, 0.0,       3, 2,         6, 6, 5, 0);
		createPawn(&sizePawns, 8, frostGolem, 60, 0, 0.0,         0.0, 0.0, 0.0,       2, 2,         4, 4, 1, 0);
		createPawn(&sizePawns, 8, stoneGolem, 60, 0, 0.3,         0.0, 0.0, 0.0,       4, 2,         1, 1, 0, 1);
		createPawn(&sizePawns, 8, dragonTyrant, 28, 24, 0.0,      0.2, 0.1, 0.0,       3, 3,         3, 3, 1, 1);
		createPawn(&sizePawns, 8, berserker, 42, 22, 0.0,         0.25, 0.12, 0.0,     1, 3,         1, 1, 1, 1);
		createPawn(&sizePawns, 8, beastRider, 38, 19, 0.15,       0.45, 0.22, 0.0,     1, 4,         2, 2, 1, 1);
		createPawn(&sizePawns, 8, poisonWisp, 34, 0, 0.0,         0.0, 0.0, 0.0,       2, 6,         2, 2, 1, 1);
		createPawn(&sizePawns, 8, furgon, 48, 0, 0.0,             0.5, 0.25, 0.0,      1, 3,         2, 2, 0, 0);
	}

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
				
				target = &grid[currentUnit.x+x][currentUnit.y+y]; // Case ciblée

				if(target->name == empty){

					surrounded=false; // Case libre donc non entourée

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

		color(red, "Error allocating memory for selection !\n");
		free(coordString);
		return false;

	}else{

		do{
			printf("Sélectionnez une unité: ");
			readS(coordString);
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
 * Vérifie que l'unité sélectionnée n'est pas en trop 
 * grand nombre sur le plateau
 * @param unitSelected 	Unité sélectionnée
 * @return          	Retourne vrai si unité en surnombre
 */
bool tooMuchUnit(int unitSelected, int limitUnits[]){
	
	if(strstr(getNameUnit(unitSelected), "Dragon")){
		
		if(limitUnits[4] == 0) return true; // Limite de dragon
		return false;

	}else{
		
		if(unitSelected == knight){ // Limite de knight

			if(limitUnits[0] == 0) return true;
			return false;

		}else if(unitSelected == scout){ // Limite de scout
			
			if(limitUnits[1] == 0) return true;
			return false;

		}else if(unitSelected == stoneGolem){ // Limite de stone Golem
			
			if(limitUnits[2] == 0) return true;
			return false;

		}else if(unitSelected == lightningTotem){ // Limite de lightning Totem

			if(limitUnits[3] == 0) return true;
			return false;

		}else if(unitSelected == furgon){ // Limite de furgon

			if(limitUnits[5] == 0) return true;
			return false;

		}

	}

	return false;
}

/**
 * Met à jour les limites d'unités
 * @param unitSelected 	Unité sélectionnée
 * @param limitUnits 	Limites liées aux unités sur le plateau
 * @param coordUnit  	Coordonnées de l'unité
 */
void updateLimits(int unitSelected, int limitUnits[], vector coordUnit){
	unitName name = grid[coordUnit.x][coordUnit.y].name;

	if(strstr(getNameUnit(name), "Dragon")){
		if(!strstr(getNameUnit(unitSelected), "Dragon")) limitUnits[4]++;  // Mise à jour limite dragons
	}else{
		if(strstr(getNameUnit(unitSelected), "Dragon")) limitUnits[4]--;
	}

	if(name != unitSelected){

		if(unitSelected == knight) limitUnits[0]--; // Met à jours les unités lors d'un ajout
		if(unitSelected == scout) limitUnits[1]--;
		if(unitSelected == stoneGolem) limitUnits[2]--;
		if(unitSelected == lightningTotem) limitUnits[3]--;
		if(unitSelected == furgon) limitUnits[5]--;

	}
		
	if(name == knight && unitSelected != knight) limitUnits[0]++; // Met à jours les unités lors d'un remplacement
	
	else if(name == scout && unitSelected != scout) limitUnits[1]++;
	
	else if(name == stoneGolem && unitSelected != stoneGolem) limitUnits[2]++;
	
	else if(name == lightningTotem && unitSelected != lightningTotem) limitUnits[3]++;
	
	else if(name == furgon && unitSelected != furgon) limitUnits[5]++;

}

/**
 * Demande de choisir une unité
 * @param unitSelected
 * @param Nombre limite pour chaque unité
 */
void askUnit(int * unitSelected, int limitUnits[]){
	do{
		printf("Choisissez le type d'unité: ");
		* unitSelected = readLong();

		if(* unitSelected < knight -1 || * unitSelected > furgon -1)
			color(red, "Aucune unité de ce type !\n\n");

		if(tooMuchUnit(* unitSelected + 1, limitUnits)){ // En cas de surnombre pour l'unité choisie
			fontColor(red);

			if(!strstr(getNameUnit(* unitSelected + 1), "Dragon")){ // Message d'erreur en cas de surnombre
				printf("Trop de %s dans vos unités !\n", getNameUnit(* unitSelected + 1));
			}else{
				printf("Trop de dragons dans vos unités !\n");
			}

			reinitColor();
		}

	}while(* unitSelected < knight -1 ||  * unitSelected > furgon -1 || tooMuchUnit(* unitSelected + 1, limitUnits));

}

/**
 * Demande les coordonnées de l'unité à placer
 * @param coordString Coordonnées sous forme de chaîne
 * @param noPlayer    Joueur en cours
 */
void askCoord(char coordString[], short noPlayer){
	do{
		fontColor(red);
		if(noPlayer == FIRST_PLAYER){
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i au format a/A 01 \n", 'A' + N - NB_LINES, 'A' + N - 1, N);
		}else{
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i au format a/A 01 \n", 'A', 'A' + NB_LINES - 1, N);
		}
		reinitColor();

		printf("Quelles sont les coordonnées de l'unité à placer ?\n");

		readS(coordString); // Saisie sécurisée

		if(!correctCoord(coordString)){ // Coordonnées incorrectes
			printf("Coordonnées incorrectes !\n");
		}
		if(!rightSide(coordString, noPlayer)){ // Mauvais placement
			printf("Unité non placée dans le bon camp !");
		}
	}
	while(!correctCoord(coordString) || !rightSide(coordString, noPlayer));
}


/**
 * Placement des unités par le joueur
 * @param noPlayer Joueur en cours
 * @param nbUnit   Nombre d'unités restantes à placer
 */
void playerAddUnit(short noPlayer, int limitUnits[], int * nbUnit){
	int unitSelected;
	char coordString[5];
	vector coordUnit;

	unitList(); // Affiche la liste des unités du jeu
	askUnit(&unitSelected, limitUnits);

	askCoord(coordString, noPlayer);
	getCoordS(coordString, &coordUnit); // Récupère les coordonnées saisies sous forme de vecteur

	updateLimits(unitSelected + 1, limitUnits, coordUnit); // Met à jour le nombre d'unités limitées

	if(grid[coordUnit.x][coordUnit.y].name != 0){
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
void playerInit(short noPlayer){
	int limitUnits[6] = {NB_MAX_KN, NB_MAX_SC, 
					 	NB_MAX_SG, NB_MAX_LT,
					 	NB_MAX_DR, NB_MAX_FU}; // Limite en nombre pour certaines unités

	printf("\nJoueur %i: \n\n", noPlayer + 1); // Initialisation du joueur 1
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);

		if(i < NB_MAX_UNIT - 1)
			printf("Il reste %i unités à placer.\n", NB_MAX_UNIT - i);
		else
			printf("Il reste 1 unité à placer.\n");
		
		reinitColor();
		playerAddUnit(noPlayer, limitUnits, &i); // Ajout unité joueur 1
	}
}

/**
 * Initialise la partie
 * @param noPlayer Entier réprésentant le joueur
 */
void gameInit(short * noPlayer){
	srand(time(NULL));

	makePawns(); // Crée les pions

	gridInit(); // Crée la grille
    gridDisp(); // Affiche la grille

	playerInit(FIRST_PLAYER); // Initialisation du joueur 1
	playerInit(FIRST_PLAYER + 1);
	* noPlayer = (rand() % (FIRST_PLAYER + 1)) + 1; // Tire le joueur débutant la partie aléatoirement
}