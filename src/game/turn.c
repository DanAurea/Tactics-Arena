#include <time.h>
#include <signal.h>
#include "../../include/game/engine.h"
#include "../../include/game/turn.h"
#include "../../include/game/listes.h"
#include "../../include/display/grid.h"
#include "../../include/display/menu.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageSignal.h"
int hasMoved    = 0;
int hasAttacked = 0;
int hasDirected = 0;
int hasPassed   = 0;

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
 * Attaquer
 */
void playAttack(){
	bool selected = false;
	vector coordUnit, coordTarget;

	do{
		selected = selectUnit(&coordUnit); // Sélection de l'unité attaquante
	}while(grid[coordUnit.x][coordUnit.y].noPlayer != noPlayer || selected == false);

	getTargets(coordUnit); // Récupère les cibles potentielles
	printTargets(); // Affiche les cibles potentielles

	do{
		selected = selectUnit(&coordTarget); // Sélectionne une cible à attaquer
	}while(targets[coordTarget.x][coordTarget.y] == 0 || selected == false);

	launchAttack(grid[coordUnit.x][coordUnit.y].name, coordTarget); // Lance une attaque
	// Déclencher capacité spéciale

	clearScreen();
	gridDisp();
}

/**
 * Déplacer une unité
 */
void playMove(vector movableUnits[]){

}

/**
 * Passer tour
 */
void passTurn(){
	hasPassed = 1;
}

/**
 * Jouer un tour
 */
void playTurn(){
	time_t start;
	time(&start);

	int  totalTime = startTurn(noPlayer); // Temps total du tour
	int timeLeft   = totalTime; // Temps restant

	signal(SIGTERM, timeDown); // En fin de tour renvoie vers timeDown

	while(timeLeft > 0 && hasPassed == 0){

		gameMenu(); // Menu du joueur
		// Vérif si temps écoulé si oui fin du tour action non prise en compte

		timeLeft = endTurn(start, totalTime);
	}

	raise(SIGTERM); // Finis le tour par un signal
}