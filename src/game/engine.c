#include <stdio.h>
#include <time.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/listes.h"
#include "../../include/display/grid.h"
#include "../../include/display/menu.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"
#include "../../include/units/unit.h"

unit grid[N][N]; /**< Grille d'unités */
int targets[N][N]; /**< Matrice de cible potentielles voir pour une liste unique (moins de mémoire et traitement) */
int noPlayer = FIRST_PLAYER; /**< Joueur en cours */

/**
 * Trouve un chemin vers une quelconque position pour l'unité
 * @param coordUnit Coordonnées de l'unité
 * @return Retourne vrai si chemin possible vers une quelconque position
 */
bool possiblePath(vector coordUnit){
	int range = grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE;

	if(!isSurrounded(coordUnit)){

		return true;

	}else if(canTeleport(grid[coordUnit.x][coordUnit.y].name)){
		
		for(int x = -range; x <= range; x++){
			for(int y = -range; y <= range; y++){
				if(grid[x][y].name == empty && abs(x) + abs(y) <= 0 && x > 0 && x < N && y > 0 && y < N){
					return true;
				}
			}
		}
	}
	
	return false;
}

/**
 * Fait la liste des unités déplaçables
 * @param movableUnit Tableau des unités déplaçables
 */
void movable(vector movableUnit[]){
	vector coordUnit;
	en_tete(noPlayer);
	short currentUnit = 0;

	while(!hors_liste(noPlayer)){
		valeur_elt(noPlayer, &coordUnit);
		suivant(noPlayer);

		if(canMove(&grid[coordUnit.x][coordUnit.y]) && possiblePath(coordUnit)){ // Unité non entourée par ennemi + non paralysée
			movableUnit[currentUnit] = coordUnit;
			currentUnit++;
		}
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
 * Initialise les cibles potentielles
 */
void initTargets(){

	for(int x = 0; x < N; x++){
		for(int y = 0; y < N; y++){
			targets[x][y] = 0;
		}
	}

}

/**
 * Récupère les cibles possible de l'unité 
 * aux coordonnées du vecteur passé en 
 * paramètre. 
 * @param coordUnit Coordonnées de l'unité
 */
void getTargets(vector coordUnit){
	unitName name = grid[coordUnit.x][coordUnit.y].name;
	vector target;
	int x, y;

	if(!liste_vide(name)){
		initTargets();
		en_tete(name);

		while(!hors_liste(name)){
			valeur_elt(name, &target);
			x = coordUnit.x + target.x;
			y = coordUnit.y + target.y;

			if(x > 0 && x < N && y > 0 && y < N){
				targets[x][y] = 1; // Marque la case comme cible potentielle
			}
			suivant(name);
		}
	}
}

/**
 * Affiche la liste des cibles potentielles
 */
void printTargets(){
    for(int x = 0; x < N; x++){
        for(int y = 0; y < N; y++){
            if(targets[N][N] == 1){
                printf("%s - %c - %i\n", getNameUnit(grid[x][y].name), x + 'A', y + 1);
            }
        }
    }
}

/**
 * Lance une attaque selon l'unité
 * @param name        Nom de l'unité
 * @param coordTarget Coordonnées de la cible
 */
void launchAttack(unitName name, vector coordTarget){
	if(name == assassin || name == enchantress || name == poisonWisp){
		// Attaque toutes les cibles
	}else if(name == furgon || name == stoneGolem || name == dragonborn || name == pyromancer){
		// Attaque en croix
	}else if(name == beastRider || name == darkWitch){
		// Attaque en ligne
	}else if(name == cleric){
		// Heal
	}else{
		// Attaque sur une seule case
	}
}

/**
 * Sélectionne une unité
 * @param  coordUnit Coordoonnées de l'unité
 * @return           Retourne vrai si unité bien sélectionnée
 */
bool selectUnit(vector * coordUnit){
	char * coordString;
	unitName name;

	coordString = (char *) calloc(5, sizeof(char));

	if(coordString == NULL){

		color(red, "Error allocating memory for selection !\n");
		free(coordString);
		return false;

	}else{

		do{
			printf("Sélectionnez une unité par ses coordonnées: ");
			readS(coordString);
		}while(!correctCoord(coordString));

		getCoordS(coordString, coordUnit); // Récupère les coordonnées saisies sous forme de vecteur
		free(coordString);

		name = grid[coordUnit->x][coordUnit->y].name;

		if(name == decors) return false;

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
				if(rand() % 100 > 93){ // Ajoute un décor aléatoirement
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
 */
void askCoord(char coordString[]){
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
		if(!rightSide(coordString)){ // Mauvais placement
			printf("Unité non placée dans le bon camp !\n");
		}
	}
	while(!correctCoord(coordString) || !rightSide(coordString));
}


/**
 * Placement des unités par le joueur
 * @param limitUnits Limites d'unités
 * @param nbUnit   Nombre d'unités restantes à placer
 */
void playerAddUnit(int limitUnits[], int * nbUnit){
	int unitSelected;
	char coordString[5];
	vector coordUnit;

	unitList(); // Affiche la liste des unités du jeu
	askUnit(&unitSelected, limitUnits);

	askCoord(coordString);
	getCoordS(coordString, &coordUnit); // Récupère les coordonnées saisies sous forme de vecteur

	updateLimits(unitSelected + 1, limitUnits, coordUnit); // Met à jour le nombre d'unités limitées

	if(grid[coordUnit.x][coordUnit.y].name != 0){
		destroyUnit(coordUnit); // Détruit l'unité en place
		* nbUnit = * nbUnit - 1; // Remet à jour le nombre d'unités
	}

	grid[coordUnit.x][coordUnit.y].name = unitSelected + 1; // Place l'unité correspondante dans la grille

	unitInit(noPlayer, coordUnit); // Initialise l'unité ajoutée
	addUnit(coordUnit);

	clearScreen();
	gridDisp(); // Affiche la grille actualisée
}

/**
 * Initiliase la liste des unités du joueur
 */
void playerInit(){
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
		playerAddUnit(limitUnits, &i); // Ajout unité joueur 1
	}
}

/**
 * Initialise la partie
 */
void gameInit(){
	srand(time(NULL));

	makePawns(); // Crée les pions

	gridInit(); // Crée la grille
    gridDisp(); // Affiche la grille

	playerInit(); // Initialisation du joueur 1
	noPlayer++;
	playerInit();// Initialisation du joueur 2
	noPlayer = (rand() % (FIRST_PLAYER + 1)) + 1; // Tire le joueur débutant la partie aléatoirement
}