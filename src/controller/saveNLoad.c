#include <stdio.h>
#include <ctype.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/listes.h"
#include "../../include/game/turn.h"
#include "../../include/display/grid.h"
#include "../../include/controller/terminal.h"

/**
 * Sauvegarde la partie avec l'état actuel de la grille et les données
 * liées au joueur en cours
 */
void save(){
	FILE * fic1;
	unit uSave;
	int x, y;
	fic1 = fopen("assets/save/fileSave", "w");
	
	if(fic1 != NULL) {
		fprintf(fic1, "%i - %i - %i\n", noPlayer, hasMoved, hasAttacked); // Informations état joueur
		
		for(x = 0; x < N; x++) { // Grille actuelle
			for(y = 0; y < N; y++) {
				
				if(grid[x][y].name != empty){
					
					uSave = grid[x][y];
					fprintf(fic1, "(%i - %i){%i, %i, %i, %f, %i, %f, %f, %f, %i, %i, %i, %i, ", x, y, uSave.name, uSave.stat.HP,
							uSave.stat.POWER, uSave.stat.ARMOR, uSave.stat.RECOVERY, uSave.stat.BLOCK[0], uSave.stat.BLOCK[1],
							uSave.stat.BLOCK[2],uSave.stat.MOVE_RANGE, uSave.noPlayer, uSave.unitColor, uSave.direct); // Stats de l'unité
					
					for(int k = 0; k <NB_MAX_EFFECT; k++) { // Effets de status liés à l'unité actuelle
						if(k == NB_MAX_EFFECT - 1){
							fprintf(fic1, " %i}\n", uSave.effect[k]);
						}else{
							fprintf(fic1, " %i, ", uSave.effect[k]);
						}
					}

				}
			}
		}

	fclose(fic1); // Ferme le fichier
	}else{
		printf("Fichier introuvable, la sauvegarde n'a pas pu être créée");
	}
}

void load() {
	FILE * fic1;
	int x = -1, y = -1;
	int name, success, cardinal, tmp;
	int effectLoad[NB_MAX_EFFECT];
	unit uLoad;
	vector coordUnit;


	fic1 = fopen("assets/save/fileSave", "r");
	if(fic1 != NULL){

		success = fscanf(fic1, "%i - %i - %i\n", &noPlayer, &hasMoved, &hasAttacked); // Informations état joueur
		if(success){

			while(!feof(fic1)) {

				success = fscanf(fic1, "(%i - %i){%i, %i, %i, %f, %i, %f, %f, %f, %i, %i, %i, %i, ", &x, &y, &name, &uLoad.stat.HP, &uLoad.stat.POWER,
						 &uLoad.stat.ARMOR, &uLoad.stat.RECOVERY, &uLoad.stat.BLOCK[0],&uLoad.stat.BLOCK[1], &uLoad.stat.BLOCK[2], &uLoad.stat.MOVE_RANGE, 
						 &uLoad.noPlayer, &uLoad.unitColor, &cardinal); // Stats de l'unité

				uLoad.name = name;
				uLoad.direct = cardinal;

				for(int k = 0; k <NB_MAX_EFFECT; k++) { // Effets de status liés à l'unité actuelle
					if(k == NB_MAX_EFFECT - 1){
						success += fscanf(fic1, " %i}\n", &effectLoad[k]);
					}else{
						success += fscanf(fic1, " %i, ", &effectLoad[k]);
					}
					uLoad.effect[k] = effectLoad[k];
					uLoad.effect[k] = effectLoad[k];
				}

				if(success == 20 && x >= 0 && x < N && y >= 0 && y < N){ // Vérifie que les données sont valides
					coordUnit.x = x;
					coordUnit.y = y;

					grid[x][y] = uLoad;
					tmp        = noPlayer;
					noPlayer   = uLoad.noPlayer;
					addUnit(coordUnit); // Ajoute l'unité à la liste du joueur
					noPlayer   = tmp;

				}else{
					printf("%i",uLoad.name);
					color(red, "\nDonnées invalides, le chargement n'a pu être effectué\n");
					exit(1);
				}
			}
		}
		makePawns();
		startGame();

	}else{
		color(red, "Fichier introuvable, la sauvegarde n'a pas pu être chargée");
	}
}