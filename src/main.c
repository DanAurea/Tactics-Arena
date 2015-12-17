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

int main(){
	srand(time(NULL));
	checkSignal();
	
	mainMenu(grid);

	return 0;
}
