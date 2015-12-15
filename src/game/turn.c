#include <time.h>
#include <stdio.h>
#include <signal.h>
#include "../../include/game/engine.h"
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
	vector coordUnit;

	do{
		selected = selectUnit(&coordUnit); // Sélection de l'unité
	}while(grid[coordUnit.x][coordUnit.y].noPlayer != noPlayer || !selected);

	dispDirection();

	do{

		printf("Choisissez une direction: ");
		direct = readLong();

		if(direct < 1 && direct > 4) printf("Direction incorrecte !\n");

	}while(direct < 1 && direct > 4);

	grid[coordUnit.x][coordUnit.y].direct = direct;

	hasPassed = 1; // Passe le tour
}

/**
 * Jouer une attaque
 */
void playAttack(){
	bool selected = false;
	vector coordUnit, coordTarget;
	unit * target;

	do{
		selected = selectUnit(&coordUnit); // Sélection de l'unité attaquante
		target   = &grid[coordUnit.x][coordUnit.y];

		if(!canAttack(target)){
			color(red, "Cette unité ne peut pas attaquer, elle est soumise à l'effet: \n");
		}else if(target->noPlayer != noPlayer){
			color(red, "Cette unité ne vous appartient pas !");
		}

	}while((target->noPlayer != noPlayer || !selected) && !canAttack(target));

	if(liste_vide(targetList)){
		getTargets(coordUnit); // Récupère les cibles potentielles
	}

	printList(targetList); // Affiche les cibles potentielles

    clearScreen();
    gridDisp();
    reinitUnitColor();

	do{
		selected = selectUnit(&coordTarget); // Sélectionne une cible à attaquer

		if(!searchTarget(targetList, coordTarget)){ // Cible impossible
			printf("Attaque impossible ! Portée insuffisante ou coordonnées incorrecte.\n");
		}
	}while(!searchTarget(targetList, coordTarget) || !selected);

	launchAttack(coordUnit, coordTarget); // Lance une attaque
	// Déclencher capacité spéciale

	hasAttacked = 1;
}

/**
 * Jouer un mouvement
 */
void playMove(){
	bool selected = false;
	vector coordUnit, coordTarget;
	unit source;

	do{
		selected = selectUnit(&coordUnit); // Sélection de l'unité à déplacer
		source   = grid[coordUnit.x][coordUnit.y];

		if(!canMove(&source) || !possiblePath(coordUnit)){
			color(red, "L'unité ne peut pas se déplacer !\n");
		}else if(source.name == empty){
			color(red, "Vous ne pouvez sélectionner une case vide");
		}else if(source.noPlayer != noPlayer){
			color(red, "Cette unité ne vous appartient pas !\n");
		}

	}while((source.noPlayer != noPlayer || !selected) && (!canMove(&source) || !possiblePath(coordUnit)));

    grid[coordUnit.x][coordUnit.y].unitColor=white;

	color(red, "\nCases atteignables par votre unité: \n\n");
	tileWalkable(coordUnit); // Affiche la liste des cases atteignables -> Prendre en compte les obstacles

    clearScreen();
    gridDisp();
    reinitUnitColor();

	color(red, "\nVous pouvez maintenant déplacer votre unité :\n\n");
	do{
		selected = selectUnit(&coordTarget); // Sélection de l'endroit où déplacer l'unité
		// findPath(coordUnit, coordTarget); -> Cherche un chemin vers la cible
	}while(!selected);
    grid[coordUnit.x][coordUnit.y].unitColor=black;
	move(coordTarget, coordUnit);

	hasMoved = 1;
}

/**
 * Passer tour
 */
void passTurn(){
	hasPassed = 1;
}

/**
 * Définis si le joueur a joué
 * @return Retourne vrai si le joueur a joué sinon faux
 */
bool hasPlay(){
	if(hasPassed == 0 && hasAttacked == 0 && hasMoved == 0 && hasSurrender == 0) return false;
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

	signal(SIGUSR1, timeDown); // En fin de tour renvoie vers timeDown

	hasMoved    = 0; // Actions utilisateur lors du tour
	hasAttacked = 0;
	hasPassed   = 0;

	while(timeLeft > 0 && hasPassed == 0 && hasSurrender == 0){

		clearScreen();
		gridDisp();
		reinitUnitColor();

		gameMenu(); // Menu du joueur

		timeLeft = endTurn(start, totalTime);

		if(loop == 0){ // Détermine si aucune action n'a été faites pendant le temps impartis
			setAction(timeLeft); // Remets à zéro les actions
		}

		loop++;
	}

	if(noPlayer == FIRST_PLAYER && hasPlay()) noPlayer++;
	else if(noPlayer == FIRST_PLAYER +1 && hasPlay()) noPlayer--;

	if(!hasPlay()){ // Pas d'action donc temps écoulé
		raise(SIGUSR1); // Finis le tour et la partie car aucune action par un signal
	}
}
