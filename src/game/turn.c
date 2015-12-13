#include <time.h>
#include <signal.h>
#include "../../include/game/engine.h"
#include "../../include/game/turn.h"
#include "../../include/game/listes.h"
#include "../../include/display/menu.h"
#include "../../include/controller/manageSignal.h"

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
 * Jouer un tour
 */
void playTurn(){
	time_t start;
	time(&start);

	int  totalTime = startTurn(noPlayer); // Temps total du tour
	int timeLeft   = totalTime; // Temps restant

	signal(SIGTERM, timeDown); // En fin de tour renvoie vers timeDown

	while(timeLeft > 0){

		gameMenu(); // Menu du joueur
		// Vérif si temps écoulé si oui fin du tour action non prise en compte

		timeLeft = endTurn(start, totalTime);
	}

	raise(SIGTERM); // Finis le tour par un signal
}