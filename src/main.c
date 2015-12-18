/**
 @file main.c
 @brief Programme principal
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <stdio.h>
#include <signal.h>
#include <time.h>
#include "../include/game/engine.h"
#include "../include/game/pawns.h"
#include "../include/display/grid.h"
#include "../include/display/menu.h"
#include "../include/controller/manageString.h"
#include "../include/controller/manageSignal.h"
#include "../include/game/listes.h"

/**
 * Programme principal
 */
int main(){
	srand(time(NULL));
	checkSignal();
	
	mainMenu(grid);

	return 0;
}
