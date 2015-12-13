#include <stdio.h>
#include <signal.h>
#include "../include/gameEngine.h"
#include "../include/grid.h"
#include "../include/menu.h"
#include "../include/manageString.h"
#include "../include/manageSignal.h"
#include "../include/listes.h"

int main(){
	initLists();
	checkSignal();

	mainMenu(grid);

	free(pawns);
	return 0;
}
