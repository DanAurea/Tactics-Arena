/**
 @file turn.c
 @brief Gestion des tours
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <time.h>
#include <stdio.h>
#include <signal.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/turn.h"
#include "../../include/game/listes.h"
#include "../../include/display/grid.h"
#include "../../include/display/menu.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageSignal.h"
#include "../../include/controller/manageString.h"
#include "../../include/units/unit.h"
int hasMoved     = 0;
int hasAttacked  = 0;
int hasPassed    = 0;
int hasSurrender = 0;

/**
 * Débute le tour du joueur
 */
int startTurn(){
	int startTurn = countUnits(noPlayer) * TIME_BY_UNIT;

	if(startTurn < MIN_TIME) startTurn = MIN_TIME;
	else if(startTurn > MAX_TIME) startTurn = MAX_TIME;

	return startTurn;
}

/**
 * Renvoie le temps restant avant la fin du tour
 * @param start Temps de début du tour
 * @param totalTime Temps total du tour
 */
int endTurn(time_t start, int totalTime){
	time_t countDown;
	int timeLeft;

	time(&countDown);
	timeLeft = start + totalTime - countDown;

	return timeLeft;
}

/**
 * Change la direction de l'unité
 */
void changeDirection(){
	int direct;
	bool selected = false;
	bool sleeping = false;
	vector coordUnit;
	unit * target;
	
	do{
		selected = selectUnit(&coordUnit); // Sélection de l'unité
		sleeping = isSleeping(coordUnit);
		target   = &grid[coordUnit.x][coordUnit.y];

		if(!selected)
			color(red, "Vous ne pouvez sélectionner cette unité !\n");

		else if(grid[coordUnit.x][coordUnit.y].noPlayer != noPlayer)
			color(red, "L'unité ne vous appartient pas !\n");

		else if(sleeping){
			fontColor(red);
			printf("Votre unité est endormie attendez : %i tours\n", pawns[target->name].stat.RECOVERY - target->stat.RECOVERY);
			reinitColor();
		}

	}while(grid[coordUnit.x][coordUnit.y].noPlayer != noPlayer || !selected || sleeping);

	grid[coordUnit.x][coordUnit.y].unitColor = white; // Couleur unité sélectionnée
	dispDirection();

	do{

		printf("Choisissez une direction: ");
		direct = readLong();

		if(direct < 1 && direct > 4) printf("Direction incorrecte !\n");

	}while(direct < 1 && direct > 4);

	grid[coordUnit.x][coordUnit.y].unitColor = black; // Couleur unité sélectionnée

	setDirection(coordUnit, direct) ;
	sleep(coordUnit);

	hasPassed = 1; // Passe le tour
}

/**
 * Jouer une attaque
 */
void playAttack(){
	bool selected = false;
	bool found 	  = false;
	bool sleeping = false;
	vector coordUnit, coordTarget;
	unit * target;

	do{
		selected = selectUnit(&coordUnit); // Sélection de l'unité attaquante
		sleeping = isSleeping(coordUnit);
		target   = &grid[coordUnit.x][coordUnit.y];

		if(!selected){
			color(red, "Vous ne pouvez sélectionner cette unité !\n");
		}else if(!canAttack(target)){
			
			fontColor(red);

			for(int i = 1; i < NB_MAX_EFFECT; i++){ // Affiche les effets sous lesquels est soumis l'unité
				
				if(target->effect[i-1] > 0) printf("Cette unité ne peut pas attaquer, elle est soumise à l'effet: %s\n", getNameEffect(i));

			}
			reinitColor();

		}else if(target->noPlayer != noPlayer)
			color(red, "Cette unité ne vous appartient pas !\n");
		else if(sleeping){
			fontColor(red);
			printf("Votre unité est endormie attendez : %i tours\n", pawns[target->name].stat.RECOVERY - target->stat.RECOVERY);
			reinitColor();
		}

	}while(target->noPlayer != noPlayer || !selected || !canAttack(target) || sleeping);

	attackable(black); // Attaquants en noir

	setTarget(grid[coordUnit.x][coordUnit.y].name, coordUnit, yellow); // Récupère les cibles potentielles -> Jaune

	grid[coordUnit.x][coordUnit.y].unitColor = white; // Couleur unité sélectionnée

    clearScreen(); // Met à jour une fois les cibles récupérées
    gridDisp();

    setTarget(grid[coordUnit.x][coordUnit.y].name, coordUnit, black); // Récupère les cibles potentielles -> Noir

	do{
		selected = selectUnit(&coordTarget); // Sélectionne une cible à attaquer

		found = searchTarget(targetList, coordTarget);

		if(!found) color(red, "Attaque impossible ! Portée insuffisante ou coordonnées incorrecte.\n");
		else if(!selected) color(red, "Vous ne pouvez sélectionner cette case !\n");

	}while(!found || !selected);

	grid[coordUnit.x][coordUnit.y].unitColor = black;
	clearScreen(); // Met à jour une fois l'attaque vérifiée
    gridDisp();

	launchAttack(coordUnit, coordTarget); // Lance une attaque
	sleep(coordUnit);


	hasAttacked = 1;

}

/**
 * Jouer un mouvement
 */
void playMove(){
	bool selected = false;
	bool possible = false;
	bool found    = false;
	bool sleeping = false;
	vector coordUnit, coordTarget;
	unit * target;

	do{
		selected = selectUnit(&coordUnit); // Sélection de l'unité à déplacer
		possible = possiblePath(coordUnit);
		sleeping = isSleeping(coordUnit);
		target   = &grid[coordUnit.x][coordUnit.y];

		if(!selected)
			color(red, "Vous ne pouvez sélectionner cette unité !\n");
		else if(!canMove(target) || !possible){
			color(red, "L'unité ne peut pas se déplacer !\n");
		}else if(target->name == empty){
			color(red, "Vous ne pouvez pas sélectionner une case vide\n");
		}else if(target->noPlayer != noPlayer){
			color(red, "Cette unité ne vous appartient pas !\n");
		}else if(sleeping){

			fontColor(red);
			printf("Votre unité est endormie attendez : %i tours\n", pawns[target->name].stat.RECOVERY - target->stat.RECOVERY);
			reinitColor();
		}

	}while(target->noPlayer != noPlayer || !selected || !possible || target->name == empty || sleeping);

	movable(black); // Réinitialise en noir les unités déplaçables

    grid[coordUnit.x][coordUnit.y].unitColor = white; // Couleur unité sélectionnée

	tileWalkable(coordUnit, green); // Affiche la liste des cases atteignables en vert

    clearScreen();
    gridDisp();

    tileWalkable(coordUnit, black); // Réinitialise la couleur en noir

	color(red, "\nVous pouvez maintenant déplacer votre unité :\n\n");
	do{
		selected = selectUnit(&coordTarget); // Sélection de l'endroit où déplacer l'unité
		
		if(grid[coordTarget.x][coordTarget.y].name == empty){
			found = pathFind(coordUnit, coordTarget);
		}

		if(!found) color(red, "Déplacement impossible !\n");
		else if(!selected) color(red, "Vous ne pouvez sélectionner cette unité !\n");

	}while(!selected || !found);
    
    grid[coordUnit.x][coordUnit.y].unitColor = black; // Réinitialise la couleur de l'unité sélectionnée
	sleep(coordUnit);
	move(coordTarget, coordUnit);

	hasMoved = 1;
}

/**
 * Passer tour
 */
void passTurn(){
	hasPassed = 1;
	clearScreen();
	gridDisp();
}

/**
 * Définis si le joueur a joué
 * @return Retourne vrai si le joueur a joué sinon faux
 */
bool hasPlay(){
	if(!hasPassed && !hasAttacked && !hasMoved) return false;
	return true;
}

/**
 * Abandonne la partie
 */
void surrender(){
	hasSurrender = 1;
}

/**
 * Définis si l'action est à prendre en compte
 * @param timeLeft Temps restant pour le tour
 */
void setAction(int timeLeft){ // A revoir -> Problème de logique
	if(timeLeft < 0){
		if(hasMoved) hasMoved = 0;
		else if(hasAttacked) hasAttacked = 0;
		else if(hasPassed) hasPassed = 0;
	}
}

/**
 * Jouer un tour
 */
void playTurn(){
	time_t start;
	time(&start);

	int  totalTime = startTurn(noPlayer); // Temps total du tour
	int timeLeft   = totalTime; // Temps restant
	int loop	   = 0;
	
	hasPassed    = 0;
	hasMoved     = 0; // Actions utilisateur lors du tour
	hasAttacked  = 0; // A faire à la fin pour éviter la triche lors du chargement
	
	poison(); // Met à jours les unités empoisonnées
	minusEffect(); // Met à jours le temps restant pour les effets
	recover(); // Met à jours le temps restant pour réutiliser une unité 

	signal(SIGUSR1, timeDown); // En fin de tour renvoie vers timeDown

	while(timeLeft > 0 && !hasPassed && !hasSurrender){
		
		gameMenu(); // Menu du joueur

		timeLeft = endTurn(start, totalTime);

		if(loop == 0 && timeLeft < 0){ // Détermine si aucune action n'a été faites pendant le temps impartis
			setAction(timeLeft); // Remets à zéro les actions
		}

		loop++;
	}

	if(!hasPlay() && !hasSurrender){ // Pas d'action donc temps écoulé
		raise(SIGUSR1); // Finis le tour et la partie car aucune action par un signal
	}

	if(noPlayer == FIRST_PLAYER && hasPlay() && !hasSurrender) noPlayer++;
	else if(noPlayer == FIRST_PLAYER +1 && hasPlay() && !hasSurrender) noPlayer--;

}