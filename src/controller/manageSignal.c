#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/controller/terminal.h"
#include "../../include/game/listes.h"
#include <signal.h>
#include <stdio.h>

/**
 * Libère tout ce qui reste encore en mémoire
 */
void freeAll(){
	if(sizePawns > 0) free(pawns); // Libère les pions
	dumpAllLists(); // Libère les listes de la mémoire
}

/**
 * A l'interruption du programme libère
 * la mémoire et sauvegarde du jeu
 * @param signal Signal d'interruption
 */
void interrupt(int signal){
	freeAll();

	if(signal == SIGINT){
		color(red,"\n\nMais où allez vous ?!");
	}else{
		color(red, "\n\nC'est bête le jeu a cessé de fonctionner !");
	}
	fflush(stdout);
	
	// Ajouter fonction de sauvegarde
	
	reinitColor(); // Réinitialise les couleurs du terminal
	
	raise(SIGINT); // Envoie un signal d'interruption
}

/**
 * Action lors du décompte terminé
 */
void timeDown(int signal){
	/* 
	*	Vérif action -> Pas d'action -> Jeu fini joueur perdant
	*	Sinon Joueur suivant -> menu
	*/
}

/**
 * Libération de la mémoire lors de la fin du programme
 */
void terminator(){
	freeAll();
	reinitColor();
}

/**
 * Vérifie le type de signal envoyé au terminal
 */
void checkSignal(){
	signal(SIGINT, interrupt); // Interruption
	signal(SIGSEGV, interrupt); // Segmentation Fault
	signal(SIGTERM, terminator); // Fin du programme
}