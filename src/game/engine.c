#include <stdio.h>
#include <time.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/listes.h"
#include "../../include/game/turn.h"
#include "../../include/display/grid.h"
#include "../../include/display/menu.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"
#include "../../include/units/unit.h"

unit grid[N][N]; /**< Grille d'unités */
int noPlayer = FIRST_PLAYER; /**< Joueur en cours */

/**
 * Trouve un chemin vers une quelconque position pour l'unité
 * @param coordUnit Coordonnées de l'unité
 * @return Retourne Vrai si chemin possible vers une quelconque position
 */
bool possiblePath(vector coordUnit){
	int range = grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE;

	if(!isSurrounded(coordUnit)){

		return true;

	}else if(canTeleport(grid[coordUnit.x][coordUnit.y].name)){

		for(int x = -range; x <= range; x++){
			for(int y = -range; y <= range; y++){
				if(grid[x][y].name == empty && x >= 0 && x < N && y >= 0 && y < N){
					return true;
				}
			}
		}
	}

	return false;
}

/**
 * Fait la liste des unités déplaçables
 */
void movable(){
	vector coordUnit;
	unit * source;
	int i = 1;

	if(!liste_vide(noPlayer)){
		en_tete(noPlayer);

		while(!hors_liste(noPlayer)){
			valeur_elt(noPlayer, &coordUnit);
			suivant(noPlayer);

			source = &grid[coordUnit.x][coordUnit.y];
			if(canMove(source) && possiblePath(coordUnit)){ // Unité non entourée par ennemi + non paralysée et ayant un chemin possible
				printf("%i - %s - %c-%i - %i HP - %s\n", i,getNameUnit(source->name),
						'A' + coordUnit.x, coordUnit.y + 1, source->stat.HP,
						getDirectionUnit(source->direct)); // Affiche le nom de l'unité
				i++;
				source->unitColor=white;
			}
		}
	}
}

/**
 * Fait la liste des unités pouvant attaquer
 */
void attackable(){
	vector coordUnit;
	unit * source;
	int i = 1;

	if(!liste_vide(noPlayer)){
		en_tete(noPlayer);

		while(!hors_liste(noPlayer)){
			valeur_elt(noPlayer, &coordUnit);
			suivant(noPlayer);

			source = &grid[coordUnit.x][coordUnit.y];
			if(canAttack(source)){
				printf("%i - %s - %c-%i - %i HP - %s\n", i,getNameUnit(source->name),
						'A' + coordUnit.x, coordUnit.y + 1, source->stat.HP,
						getDirectionUnit(source->direct)); // Affiche le nom de l'unité
				i++;
				source->unitColor=white;
			}
		}
	}
}

/**
 * Fait la liste des cases pouvant être atteintes par l'unité
 * @param coordUnit Coordonnées de l'unité
 */
void tileWalkable(vector coordUnit){
	unit * source;
	int moveRange = grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE;
	int i = 1;

	for(int x = -moveRange + coordUnit.x; x <= moveRange + coordUnit.x; x++){
		for(int y = -moveRange + coordUnit.y; y <= moveRange + coordUnit.y; y++){

			if(x >= 0 && x < N && y >= 0 && y < N){
				source = &grid[x][y];

				if(source->name == empty){ // Case vide
					printf("%i - %s - %c-%i\n", i,getNameUnit(source->name),
							'A' + x, y + 1); // Affiche le nom de l'unité
					i++;
					source->unitColor=green;
				}
			}
		}
	}
}

/**
 * Trouve un chemin vers la position désirée
 * @param coordUnit Coordonnées de l'unité
 * @param coordTarget Coordonnées de la cible
 */
void findPath(vector coordUnit, vector coordTarget){

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
 * Récupère les cibles possible de l'unité
 * aux coordonnées du vecteur passé en
 * paramètre.
 * @param coordUnit Coordonnées de l'unité
 */
void getTargets(vector coordUnit){
	unitName name = grid[coordUnit.x][coordUnit.y].name;
	vector target;
	vector newTarget;

	en_tete(targetList);
	if(!liste_vide(targetList)){
		dumpList(targetList); // Vide la liste
	}

	if(!liste_vide(name)){
		en_tete(name);

		while(!hors_liste(name)){
			valeur_elt(name, &target);
			newTarget.x = coordUnit.x + target.x;
			newTarget.y = coordUnit.y + target.y;

			if(newTarget.x >= 0 && newTarget.x < N && newTarget.y >= 0 && newTarget.y < N)
			{
				if(grid[newTarget.x][newTarget.y].name != decors)
				{
				    addTarget(targetList, newTarget); // Marque les coordonnées comme cible potentielle
				    grid[newTarget.x][newTarget.y].unitColor=yellow;
				}

			}
			suivant(name);
		}
	}
}

/**
 * Lance une attaque selon l'unité
 * @param coordSource	Nom de l'unité source
 * @param coordTarget	Coordonnées de la cible
 */
void launchAttack(vector coordSource, vector coordTarget){
	unitName name = grid[coordSource.x][coordSource.y].name;
	vector targetAttack;

	if(name == assassin || name == enchantress || name == poisonWisp){

		if(!liste_vide(targetList)){
			en_tete(targetList);

			while(!hors_liste(targetList)){ // Attaque toutes les cibles
				valeur_elt(targetList, &targetAttack);

				attack(coordSource, targetAttack); // Attaque l'unité présente dans la liste

				suivant(targetList);
			}
		}

	}else if(name == furgon || name == stoneGolem || name == dragonborn || name == pyromancer){

		for(int x = coordTarget.x - 1; x <= coordTarget.x + 1; x++){
			for(int y = coordTarget.y - 1; y <= coordTarget.y + 1; y++){

				if(abs(x) + abs(y) <= 1 && x >=0 && x < N && y >= 0 && y < N){ // Croix centrée sur la cible désirée
					targetAttack.x = coordTarget.x + x;
					targetAttack.y = coordTarget.y + y;
					attack(coordSource, targetAttack);
				}

			}
		}

	}else if(name == beastRider || name == darkWitch){
		if(!liste_vide(targetList)){
			en_tete(targetList);

			while(!hors_liste(targetList)){
				valeur_elt(targetList, &targetAttack);

				if(targetAttack.x == coordTarget.x || targetAttack.y == coordTarget.y){ // Même ligne / colonne
					attack(coordSource, targetAttack); // Attaque l'unité présente dans la liste
				}

				suivant(targetList);
			}
		}
	}else if(name == cleric){
		heal(name);
	}else{
		attack(coordSource, coordTarget);
	}
}

/**
 * Sélectionne une unité
 * @param  coordUnit Coordoonnées de l'unité
 * @return           Retourne vrai si unité bien sélectionnée
 */
bool selectUnit(vector * coordUnit){
	char coordString[5];
	unitName name;

	do{
		printf("Sélectionnez une unité ou une case par ses coordonnées au format a/A 01/11: ");
		readS(coordString);
	}while(!correctCoord(coordString));

	getCoordS(coordString, coordUnit); // Récupère les coordonnées saisies sous forme de vecteur

	name = grid[coordUnit->x][coordUnit->y].name;

	if(name == decors) return false;

	return true;
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
					grid[x][y] = pawns[decors];
					nbDecors++;
				}
			}

			unitInit(-1, coordUnit); // Initialise avec les données par défaut

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
 * @param unitSelected Unité sélectionnée
 * @param limitUnits Nombre limite pour chaque unité
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

	if(strstr(getNameUnit(unitSelected + 1), "Dragon Tyrant") ){ // Dragon Tyrant compte comme 2 unités
		* nbUnit = * nbUnit + 1;
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

		if(i < NB_MAX_UNIT -1)
			printf("Il reste %i unités à placer.\n", NB_MAX_UNIT - i);
		else
			printf("Il reste 1 unité à placer.\n");

		reinitColor();
		playerAddUnit(limitUnits, &i); // Ajout unité joueur 1
	}
}

/**
 * Fin de la partie
 */
bool endGame(){
	if(liste_vide(noPlayer) || !hasPlay()){
		fontColor(red);

		if(!hasPlay()){
			printf("Le joueur %i a perdu car aucune action n'a été faites dans le temps impartis !", noPlayer + 1);
		}else{
			printf("Le joueur %i a perdu car toutes les unités ont été détruites !", noPlayer + 1);
		}

		reinitColor();
		return true;
	}else{
		return false;
	}
}

/**
 * Débute la partie
 */
void startGame(){
	do{
		playTurn();
	}
	while(!endGame());
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

	startGame();
}
