/**
 @file engine.c
 @brief Moteur de jeu
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <stdio.h>
#include <time.h>
#include <math.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/pathList.h"
#include "../../include/game/listes.h"
#include "../../include/game/turn.h"
#include "../../include/display/grid.h"
#include "../../include/display/menu.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"
#include "../../include/controller/manageSignal.h"
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

	if(!isSurrounded(coordUnit) && range > 0){

		return true;

	}else if(canTeleport(grid[coordUnit.x][coordUnit.y].name) && range > 0){

		for(int x = coordUnit.x-range; x <= coordUnit.x + range; x++){
			for(int y = coordUnit.x - range; y <= coordUnit.x + range; y++){
				if(x >= 0 && x < N && y >= 0 && y < N){
					if(abs(coordUnit.x - x) + abs(coordUnit.y - y) <= range && grid[x][y].name == empty){
						return true;
					}
				}
			}
		}
	}

	return false;
}

/**
 * Trouve un chemin vers la position désirée
 * @param coordUnit Coordonnées de l'unité
 * @param coordTarget Coordonnées de la cible
 * @return Retourne vrai si chemin trouvé
 */
bool pathFind(vector coordUnit, vector coordTarget){
	int range = grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE;
	vector current, neighbour; // Coordonnées de la case
	int F = 9999; // Poids de la case

	if(!emptyPath(1)) dumpPath(1); // Vide liste fermée
	if(!emptyPath(0)) dumpPath(0); // Vide liste ouverte
	
	pathHead(0); // En tête liste ouverte
	toRightPath(0, coordUnit, F); // Ajoute le point de départ à la liste ouverte

	while(!emptyPath(0) && range >= 0){ // Parcours de la zone dans la portée de l'unité
			
			current = getCurrentNode(0); // On récupère le noeud ayant le plus petit F dans la liste ouverte
			range--;
			addCloseList(current, F); // Ajoute le noeud courant à la liste fermée

			if(current.x == coordTarget.x && current.y == coordTarget.y) return true; // Chemin trouvé

			for(int i = current.x -1; i <= current.x + 1; i++){ // Regarde les voisins sans prendre en compte la diagonale
				for(int j = current.y -1; j <= current.y + 1; j++){

					if(abs(current.x - i) + abs(current.y - j) == 1){ // 4 voisins

						neighbour.x = i;
						neighbour.y = j;

						if (i >= 0 && i < N && j >= 0 && j < N){

							// Cherche le voisin dans la liste fermée + vérifie que la case permet le passage
							if(!searchTile(1, neighbour) && (grid[i][j].name != decors 
								|| canTeleport(grid[coordUnit.x][coordUnit.y].name) 
								|| (grid[i][j].noPlayer == noPlayer && canGetPassed(&grid[i][j]))) ){ 
								
								F = abs(coordTarget.x - i) + abs(coordTarget.y -j); // Distance jusqu'à la destination

								if(!searchTile(0, neighbour)){ // Cherche dans la liste ouverte

									addOpenList(neighbour, F);
								}

							}
						}

					}
				}
			}
	}

	return false;
}

/**
 * Fait la liste des unités déplaçables
 * @param colorDisp Couleur d'affichage
 */
void movable(int colorDisp){
	vector coordUnit;
	unit * source;

	if(!liste_vide(noPlayer)){
		en_tete(noPlayer);

		while(!hors_liste(noPlayer)){
			valeur_elt(noPlayer, &coordUnit);
			suivant(noPlayer);

			source = &grid[coordUnit.x][coordUnit.y];
			if(canMove(source) && possiblePath(coordUnit) && !isSleeping(coordUnit)){ // Unité non entourée par ennemi + non paralysée et ayant un chemin possible
				source->unitColor= colorDisp;
			}
		}
	}
}

/**
 * Fait la liste des unités pouvant attaquer
 * @param colorDisp Couleur d'affichage
 */
void attackable(int colorDisp){
	vector coordUnit;
	unit * source;

	if(!liste_vide(noPlayer)){
		en_tete(noPlayer);

		while(!hors_liste(noPlayer)){
			valeur_elt(noPlayer, &coordUnit);
			suivant(noPlayer);

			source = &grid[coordUnit.x][coordUnit.y];
			if(canAttack(source) && !isSleeping(coordUnit)){
				source->unitColor = colorDisp;
			}
		}
	}
}

/**
 * Fait la liste des cases pouvant être atteintes par l'unité
 * @param coordUnit Coordonnées de l'unité
 * @param colorDisp Couleur d'affichage
 */
void tileWalkable(vector coordUnit, int colorDisp){
	unit * source;
	vector coordTarget;
	int moveRange = grid[coordUnit.x][coordUnit.y].stat.MOVE_RANGE;

	for(int x = coordUnit.x - moveRange; x <= moveRange + coordUnit.x; x++){
		for(int y = coordUnit.y -moveRange; y <= moveRange + coordUnit.y; y++){

			coordTarget.x = x;
			coordTarget.y = y;
			if(pathFind(coordUnit,coordTarget)){

				source = &grid[x][y];

				if(source->name == empty){ // Case vide
					source->unitColor = colorDisp;
				}
			}
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
 * Initialise les cibles du pion
 * @param name     Nom du pion
 * @param coordUnit Coordonnées de l'unité
 * @param colorDisp Couleur d'affichage
 */
void setTarget(unitName name, vector coordUnit,int colorDisp)
{	short min, max;
	vector target;
	int vertRange = pawns[name].stat.target.vertRange;
	int horizRange = pawns[name].stat.target.vertRange;
	int ringSize = pawns[name].stat.target.ringSize;
	int line = pawns[name].stat.target.line;

	if(!liste_vide(targetList)) dumpList(targetList);

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

			if(coordUnit.x + i >=0 && coordUnit.x + i < N && coordUnit.y + j >= 0 && coordUnit.y < N){
				
				if( ((abs(i) + abs(j) <= min && line == 0)
					|| (i == 0 && j <= max)
					|| ( j == 0 && i <= max))
					&& abs(i) + abs(j) >= ringSize){ // Sélection des cibles de manière flexible et personnalisée

						target.x = i + coordUnit.x;
						target.y = j + coordUnit.y;
						grid[target.x][target.y].unitColor = colorDisp;
						addTarget(targetList,target); // Ajoute une cible pour le pion
				}
			}
		}
	}

}

/**
 * Déclenche une capacité spéciale selon l'unité
 * @param coordSource Coordonnées de l'unité source (déclenchant une capacité)
 * @param coordTarget Coordonnées de l'unité affectée par la capacité spéciale
 */
void specialBoons(vector coordSource, vector coordTarget){
	unitName name  = grid[coordSource.x][coordSource.y].name;
	unit * uTarget = &grid[coordTarget.x][coordTarget.y];
	int tmp;

	if(name == assassin && grid[coordSource.x][coordSource.y].stat.HP <= 5) {
		if(name != barrierTotem){
			uTarget->stat.HP = -99;
			
			printf("\nL'unité %s en %c - %i a subi 99 dégâts !\n",getNameUnit(uTarget->name), 'A' + coordTarget.x, coordTarget.y +1);

			if(uTarget->stat.HP <= 0) {
				tmp = noPlayer;
				noPlayer = grid[coordTarget.x][coordTarget.y].noPlayer; //Détruit l'unité dans la liste du joueur correspondant
				destroyUnit(coordTarget); // noPlayer en variable globale donc il faut changer noPlayer avant
				erase(&grid[coordTarget.x][coordTarget.y]); //Efface de la grille
				noPlayer = tmp; // Remet noPlayer au joueur qui était en train de jouer

				color(red, "L'unité est morte !\n");
			}else{
				grid[coordTarget.x][coordTarget.y].stat.HP -= 99;
			}

		}		
	}else if(name == enchantress && uTarget->name != empty) {
		addEffect(coordTarget, PARALYSE);
	}else if(name == poisonWisp && uTarget->name != empty) {
		addEffect(coordTarget, POISON);
	}

}

/**
 * Lance une attaque selon l'unité
 * @param coordSource	Nom de l'unité source
 * @param coordTarget	Coordonnées de la cible
 */
void launchAttack(vector coordSource, vector coordTarget){
	unitName name = grid[coordSource.x][coordSource.y].name;
	int HP 	      = grid[coordSource.x][coordSource.y].stat.HP;
	vector targetAttack;

	if(name == assassin || name == enchantress || name == poisonWisp){

		if(!liste_vide(targetList)){
			en_tete(targetList);

			if(name == assassin && HP <= 5){
				color(red, "L'assassin déclenche sa capacité spéciale kamikaze !\n");
			}else if(name == enchantress){
				color(red, "L'enchantress déclenche sa capacité spéciale et paralyse tout le monde aux alentours !\n");
			}

			while(!hors_liste(targetList)){ // Attaque toutes les cibles
				valeur_elt(targetList, &targetAttack);

				attack(coordSource, targetAttack); // Attaque l'unité présente dans la liste
				specialBoons(coordSource, targetAttack); // Effet de statut - Capacité spécial

				suivant(targetList);
			}
			if(name == assassin && HP <= 5){
				destroyUnit(coordSource); // Détruit l'assassin de la liste du joueur en cours
				erase(&grid[coordSource.x][coordSource.y]); // Efface l'assassin de la grille
			}
		}

	}else if(name == furgon || name == stoneGolem || name == dragonborn || name == pyromancer){

		powerBonus(); // Octroie un bonus de puissance sous certaines conditions
		
		for(int x = coordTarget.x - 1; x <= coordTarget.x + 1; x++){
			for(int y = coordTarget.y - 1; y <= coordTarget.y + 1; y++){

				if(abs(coordTarget.x - x) + abs(coordTarget.y - y) <= 1 && x >=0 && x < N && y >= 0 && y < N){ // Croix centrée sur la cible désirée
					targetAttack.x = x;
					targetAttack.y = y;
					attack(coordSource, targetAttack);
				}

			}
		}

	}else if(name == beastRider || name == darkWitch){
		if(!liste_vide(targetList)){
			en_tete(targetList);

			while(!hors_liste(targetList)){
				valeur_elt(targetList, &targetAttack);

				if((coordTarget.x > coordSource.x && targetAttack.x > coordSource.x) || (coordTarget.x < coordSource.x && targetAttack.x < coordSource.x)){ // N'attaque sur une moitié de ligne
					if(targetAttack.x == coordTarget.x || targetAttack.y == coordTarget.y  ){ // Même ligne / colonne
						attack(coordSource, targetAttack); // Attaque l'unité présente dans la liste
					}
				}else if((coordTarget.y > coordSource.y && targetAttack.y > coordSource.y) || (coordTarget.y < coordSource.y && targetAttack.y < coordSource.y)){
					if(targetAttack.x == coordTarget.x || targetAttack.y == coordTarget.y  ){ // Même ligne / colonne
						attack(coordSource, targetAttack); // Attaque l'unité présente dans la liste
					}
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
 * @param limitUnits 	Tableau des limites pour chaque unité
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

		if(* unitSelected < knight -1 || * unitSelected > NB_UNITS - 1)
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

	}while(* unitSelected < knight -1 ||  * unitSelected > NB_UNITS - 1 || tooMuchUnit(* unitSelected + 1, limitUnits));

}

/**
 * Demande les coordonnées de l'unité à placer
 * @param coordString Coordonnées sous forme de chaîne
 */
void askCoord(char coordString[]){
	do{
		fontColor(cyan);
		if(noPlayer == FIRST_PLAYER){
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i (Exemple : K 2 ) \n", 'A' + N - NB_LINES, 'A' + N - 1, N);
		}else{
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i (Exemple : B 5 ) \n", 'A', 'A' + NB_LINES - 1, N);
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

	if(grid[coordUnit.x][coordUnit.y].name != empty){
		destroyUnit(coordUnit); // Détruit l'unité en place
		* nbUnit = * nbUnit - 1; // Remet à jour le nombre d'unités
	}

	if((strstr(getNameUnit(unitSelected + 1), "Dragon Tyrant") && * nbUnit <= NB_MAX_UNIT - 2)
		|| !strstr(getNameUnit(unitSelected + 1), "Dragon Tyrant") 
		){ // Dragon Tyrant compte comme 2 unités
		grid[coordUnit.x][coordUnit.y].name = unitSelected + 1; // Place l'unité correspondante dans la grille

		unitInit(noPlayer, coordUnit); // Initialise l'unité ajoutée
		addUnit(coordUnit);

		clearScreen();
		gridDisp(); // Affiche la grille actualisée

		if(strstr(getNameUnit(unitSelected + 1), "Dragon Tyrant")){ // Dragon Tyrant compte comme 2 unités
			* nbUnit = * nbUnit + 1;
		}
	}else{
		gridDisp(); // Affiche la grille actualisée

		color(red, "Pas assez d'unités disponible pour placer le Dragon tyrant !\n");
		* nbUnit = * nbUnit - 1;
	}

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
	bool static1 = allStatic(FIRST_PLAYER);
	bool static2 = allStatic(FIRST_PLAYER + 1);
	
	if(liste_vide(noPlayer) || !hasPlay() || hasSurrender || static1 || static2){
		fontColor(red);

		if(hasSurrender){
			printf("\nLe joueur %i a perdu par abandon (bouuuhhh) !\n", noPlayer + 1);
		}else if(liste_vide(noPlayer)){
			printf("Le joueur %i a perdu car toutes les unités ont été détruites !\n", noPlayer + 1);
		}else if(!hasPlay() && !hasSurrender){
			printf("Le joueur %i a perdu car aucune action n'a été faites dans le temps impartis !\n", noPlayer + 1);
		}else if(static1 && static2){
			printf("Match nul !\n");
		}else if(static1 && !static2){
			printf("Joueur 1 vous avez perdu, toutes vos unités sont paralysées !\n");
		}else if(!static1 && static2){
			printf("Joueur 2 vous avez perdu, toutes vos unités sont paralysées !\n");
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
	time_t start, countDown;
	int totalTime = 11; // Temps total du tour
	int tLeft   = totalTime; // Temps restant
	int tmp 	   = -1;

	clearScreen();
	gridDisp();

	do{
		playTurn();
	}
	while(!endGame());

	time(&start);
	while(tLeft > 0){ // Décompte avant de réafficher le menu principal si partie finie
		time(&countDown);
		tLeft = start + totalTime - countDown;

		if(tmp != tLeft){ // N'affiche le message qu'une fois toutes les secondes
			tmp = tLeft;
			
			if(tLeft < totalTime)
				printf("\033[A\033[K"); // Efface la ligne

			printf("Vous allez être redirigé vers le menu principal dans %i ", tLeft);
			if(tLeft > 1){
				printf("secondes\n");
			}else{
				printf("seconde\n");
			}
			
			printf("\x0d"); // Replace début ligne
		}
	}

	freeAll();
	clearScreen();
	mainMenu();
}

/**
 * Initialise la partie
 */
void gameInit(){
	initLists();
	initPaths();

	noPlayer = FIRST_PLAYER; // Réinitialise pour nouvelle partie
	makePawns(); // Crée les pions

	gridInit(); // Crée la grille
    gridDisp(); // Affiche la grille

	playerInit(); // Initialisation du joueur 1
	noPlayer++;
	playerInit();// Initialisation du joueur 2

	noPlayer = (rand() % (FIRST_PLAYER + 2)); // Tire le joueur débutant la partie aléatoirement

	startGame();
}
