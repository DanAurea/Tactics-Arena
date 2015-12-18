/**
 @file manageSignal.c
 @brief Gestion des signaux
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/controller/saveNLoad.h"
#include "../../include/controller/terminal.h"
#include "../../include/game/listes.h"
#include "../../include/game/pathList.h"
#include <signal.h>
#include <stdio.h>

/**
 * Libère tout ce qui reste encore en mémoire
 */
void freeAll(){
	if(sizePawns > 0){
		free(pawns); // Libère les pions
		sizePawns = 0;
		dumpAllLists(); // Libère les listes de la mémoire
		dumpAllPaths(); // Libère les chemins de la mémoire
	}
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

	if(sizePawns > 0){
		save();
	}
	
	reinitColor(); // Réinitialise les couleurs du terminal
	
	raise(SIGINT); // Envoie un signal d'interruption
}

/**
 * Petit message sympa lors du temps écoulé
 * @param signal Signal d'interruption
 */
void timeDown(int signal){
	fontColor(red);
	printf("\nTemps écoulé, même Jabba le Hutt fait mieux !\n");
	reinitColor();
}

/**
 * Libération de la mémoire lors de la fin du programme
 * @param signal Signal d'interruption  
 */
void terminator(int signal){
	freeAll();
	save();
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