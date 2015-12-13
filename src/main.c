#include <stdio.h>
#include <signal.h>
#include "../include/game/engine.h"
#include "../include/game/pawns.h"
#include "../include/display/grid.h"
#include "../include/display/menu.h"
#include "../include/controller/manageString.h"
#include "../include/controller/manageSignal.h"
#include "../include/game/listes.h"

int main(){
	initLists();
	checkSignal();

	mainMenu(grid);

	free(pawns);
	return 0;
}
