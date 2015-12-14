#include <stdio.h>
#include <ctype.h>
#include "../../include/game/engine.h"
#include "../../include/display/grid.h"
#include "../../include/controller/terminal.h"

void save(){
	FILE * fic1;
	unit uSave;
	int x, y;
	fic1 = fopen("assets/save/fileSave", "w");
	if(fic1 != NULL) {
		for(x = 0; x < N; x++) {
			for(y = 0; y < N; y++) {
				if(grid[x][y].name != empty){
					uSave = grid[x][y];
					fprintf(fic1, "(%i - %i){%i, %i, %i, %f, %i, %f, %f, %f, %i, %i, %i, %i, ", x, y, uSave.name, uSave.stat.HP, 								uSave.stat.POWER, uSave.stat.ARMOR, uSave.stat.RECOVERY, uSave.stat.BLOCK[0], 									uSave.stat.BLOCK[1], uSave.stat.BLOCK[2],uSave.stat.MOVE_RANGE, uSave.noPlayer, 								uSave.unitColor, uSave.direct);
					for(int k = 0; k <NB_MAX_EFFECT; k++) {
						if(k == NB_MAX_EFFECT - 1){
							fprintf(fic1, " %i ", uSave.effect[k]);
						}else{
							fprintf(fic1, " %i, ", uSave.effect[k]);
						}
					}
				fprintf(fic1, "}\n");
				} 
			}
		}
	fclose(fic1);
	}else{
		printf("Fichier introuvable, la sauvegarde n'a pas pu être créée");
	}

}

void load() {
	FILE * fic1;
	int x = -1, y = -1;
	int name, success;
	int effectLoad[NB_MAX_EFFECT] = {0};
	unit uLoad;

	fic1 = fopen("assets/save/fileSave", "r");
	if(fic1 != NULL){
		while(!feof(fic1)) {
			success = fscanf(fic1, "(%i - %i){%i, %i, %i, %f, %i, %f, %f, %f, %i, %i, %i, %i, ", &x, &y, &name, &uLoad.stat.HP, 					        &uLoad.stat.POWER, &uLoad.stat.ARMOR, &uLoad.stat.RECOVERY, &uLoad.stat.BLOCK[0],
					&uLoad.stat.BLOCK[1], &uLoad.stat.BLOCK[2], &uLoad.stat.MOVE_RANGE, &uLoad.noPlayer,
					&uLoad.unitColor, &uLoad.direct);
			
			uLoad.name = name;
			for(int k = 0; k <NB_MAX_EFFECT; k++) {
				if(k == NB_MAX_EFFECT - 1){
					success = fscanf(fic1, " %i }\n", &effectLoad[k]);
				}else{
					success = fscanf(fic1, " %i, ", &effectLoad[k]);
				}
				uLoad.effect[k] = effectLoad[k];
			}

			if(success == 1){
				grid[x][y] = uLoad;
			}else{
				printf("Données invalide, le chargement n'a pu être effectué");
				exit(1);
			}
		}
		//startGame();


	}else{
		printf("Fichier introuvable, la sauvegarde n'a pas pu être chargée");

	}
}

void save2() {

	FILE * fic1;
	unit uSave[(NB_MAX_UNIT*2) + NB_MAX_DECOR];
	int x, y, k = 0;
	fic1 = fopen("assets/save/fileSave2", "wb");
	if(fic1 != NULL) {
		for(x = 0; x < N; x++) {
			for(y = 0; y < N; y++) {
				if(grid[x][y].name != empty){
					uSave[k] = grid[x][y];
					k++;
				} 
			}
		}
		fwrite(&uSave, sizeof(unit), k, fic1);
	fclose(fic1);
	}else{
		printf("Fichier introuvable, la sauvegarde n'a pas pu être créée");
	}

}

// Go faire cette fonction je comprend rien au binaire stp :(

void load2() {
	FILE * fic1;
	int x = -1, y = -1;
	int name, success;
	int effectLoad[NB_MAX_EFFECT] = {0};
	unit uLoad;

	fic1 = fopen("assets/save/fileSave", "rb");
	if(fic1 != NULL){
		while(!feof(fic1)) {
			fread(&uLoad, sizeof(uLoad), 
			
			uLoad.name = name;
			for(int k = 0; k <NB_MAX_EFFECT; k++) {
				if(k == NB_MAX_EFFECT - 1){
					success = fscanf(fic1, " %i }\n", &effectLoad[k]);
				}else{
					success = fscanf(fic1, " %i, ", &effectLoad[k]);
				}
				uLoad.effect[k] = effectLoad[k];
			}

			if(success == 1){
				grid[x][y] = uLoad;
			}else{
				printf("Données invalide, le chargement n'a pu être effectué");
				exit(1);
			}
		}
		//startGame();


	}else{
		printf("Fichier introuvable, la sauvegarde n'a pas pu être chargée");

	}
}








