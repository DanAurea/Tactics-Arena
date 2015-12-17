#include <stdio.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/listes.h"
#include "../../include/game/turn.h"
#include "../../include/display/grid.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"

char key[] = "SPIBCTBEC";

/**
 * Récupère un caractère de la clé
 * @param pos Position dans la clé
 * @return     Retourne un caractère de la clé
 */
char getCharKey(char * dynamicKey, int * pos){
	if(sizeof(dynamicKey) == *pos) * pos = 0;
	else * pos = *pos +1;

	return dynamicKey[* pos];
}

/**
 * Récupère une clé de décryptage
 * @param  name Nom de l'unité
 * @return      Retourne une clé 
 */
char * getKey(unitName name){
	char * dynamicKey = NULL;
	int lenKey = strlen(key);
	int lenName = strlen(getNameUnit(name));
	int size = lenName + lenKey; // Taille de la clé dynamique

	dynamicKey = malloc(size * sizeof(char));

	if(dynamicKey != NULL){
		memcpy(dynamicKey, key, lenKey);
		memcpy(dynamicKey, getNameUnit(name), lenName);

		return dynamicKey; // Retourne la clé générée dynamiquement

	}else{
		free(dynamicKey);
		color(red, "Clé de décryptage incorrect !\n");
		exit(1);
	}
}

/**
 * Crypte les statistiques de l'unité pour 
 * la sauvegarde
 * @param unitSaved Unité sauvegardée
 */
void crypt(unit * unitSaved){
	int size = strlen(key) * 5; // Récupère la taille du nom de l'unité
	int pos = 0;
	char * dynamicKey;

	dynamicKey = getKey(unitSaved->name); // Récupère une clé dynamique

	unitSaved->name *= size;
	unitSaved->stat.ARMOR *= (float)(-size * getCharKey(dynamicKey, &pos));
	unitSaved->stat.POWER *= -size * getCharKey(dynamicKey, &pos);
	unitSaved->stat.HP *= -size * getCharKey(dynamicKey, &pos);
	unitSaved->stat.RECOVERY *= -size * getCharKey(dynamicKey, &pos);
	unitSaved->stat.MOVE_RANGE *= -size * getCharKey(dynamicKey, &pos);
	unitSaved->stat.BLOCK[0] *= (float)(-size * getCharKey(dynamicKey, &pos));
	unitSaved->stat.BLOCK[1] *= (float)(-size * getCharKey(dynamicKey, &pos));
	unitSaved->stat.BLOCK[2] *= (float)(-size * getCharKey(dynamicKey, &pos));
	unitSaved->unitColor *= -size * getCharKey(dynamicKey, &pos);
	unitSaved->noPlayer *= -size * getCharKey(dynamicKey, &pos);
	unitSaved->direct *= -size * getCharKey(dynamicKey, &pos);
	
	for(int k = 0; k <NB_MAX_EFFECT; k++) { // Effets de status liés à l'unité actuelle
		unitSaved->effect[k] /= -size - getCharKey(dynamicKey, &pos);
	}

	free(dynamicKey); // Libère la mémoire de la clé
}

/**
 * Décrypte les statistiques de l'unité pour
 * le chargement
 * @param unitLoaded Unité chargée
 */
void decrypt(unit * unitLoaded){
	int size = strlen(key) * 5; // Récupère la taille du nom de l'unité
	int pos = 0;
	char * dynamicKey;

	unitLoaded->name /= size;
	dynamicKey = getKey(unitLoaded->name);

	unitLoaded->stat.ARMOR /= (float)(-size * getCharKey(dynamicKey, &pos));
	unitLoaded->stat.POWER /= -size * getCharKey(dynamicKey, &pos);
	unitLoaded->stat.HP /= -size * getCharKey(dynamicKey, &pos);
	unitLoaded->stat.RECOVERY /= -size * getCharKey(dynamicKey, &pos);
	unitLoaded->stat.MOVE_RANGE /= -size * getCharKey(dynamicKey, &pos);
	unitLoaded->stat.BLOCK[0] /= (float)(-size * getCharKey(dynamicKey, &pos));
	unitLoaded->stat.BLOCK[1] /= (float)(-size * getCharKey(dynamicKey, &pos));
	unitLoaded->stat.BLOCK[2] /= (float)(-size * getCharKey(dynamicKey, &pos));
	unitLoaded->unitColor /= -size * getCharKey(dynamicKey, &pos);
	unitLoaded->noPlayer /= -size * getCharKey(dynamicKey, &pos);
	unitLoaded->direct /= -size * getCharKey(dynamicKey, &pos);
	
	for(int k = 0; k <NB_MAX_EFFECT; k++) { // Effets de status liés à l'unité actuelle
		unitLoaded->effect[k] *= -size - getCharKey(dynamicKey, &pos);
	}

	free(dynamicKey); // Libère la mémoire de la clé
}

/**
 * Vérifie que le décryptage s'est bien passé
 * @param unitLoaded Unité chargée
 * @return Retourne vrai si données correctes sinon faux
 */
bool checkDecrypt(unit * unitLoaded){
	
	if(unitLoaded->name < empty || unitLoaded->name > NB_UNITS) return false;
	else if(unitLoaded->stat.ARMOR < 0.0) return false;
	else if(unitLoaded->stat.POWER < 0) return false;
	else if(unitLoaded->stat.HP < 0 ) return false;
	else if(unitLoaded->stat.RECOVERY < 0 ) return false;
	else if(unitLoaded->stat.MOVE_RANGE < 0 ) return false;
	else if(unitLoaded->stat.BLOCK[0] < 0.0 ) return false;
	else if(unitLoaded->stat.BLOCK[1] < 0.0 ) return false;
	else if(unitLoaded->stat.BLOCK[2] < 0.0 ) return false;
	else if(unitLoaded->unitColor < 0 ) return false;
	else if(unitLoaded->noPlayer < -1 ) return false;
	else if(unitLoaded->direct < 0 ) return false;

	for(int k = 0; k <NB_MAX_EFFECT; k++) { // Effets de status liés à l'unité actuelle
		if(unitLoaded->effect[k] < 0) return false;
	}

	return true;
}

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
					crypt(&uSave); // Crypte les informations de l'unité

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
		printf("Fichier introuvable, la sauvegarde n'a pas pu être créée.\n");
	}
}

/**
 * Charge la partie précédemment enregistré
 */
void load() {
	FILE * fic1;
	int x = -1, y = -1;
	int name, success, cardinal, tmp;
	int effectLoad[NB_MAX_EFFECT];
	unit uLoad;
	vector coordUnit;


	fic1 = fopen("assets/save/fileSave", "r");
	if(fic1 != NULL){
		initLists();

		success = fscanf(fic1, "%i - %i - %i\n", &noPlayer, &hasMoved, &hasAttacked); // Informations état joueur
		if(success == 3){

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

				decrypt(&uLoad); // Décrypte les informations liées à l'unité chargée

				if(success == 20 && x >= 0 && x < N && y >= 0 && y < N && checkDecrypt(&uLoad)){ // Vérifie que les données sont valides
					coordUnit.x = x;
					coordUnit.y = y;

					grid[x][y] = uLoad;
					tmp        = noPlayer;
					noPlayer   = uLoad.noPlayer;

					addUnit(coordUnit); // Ajoute l'unité à la liste du joueur
					noPlayer   = tmp;

				}else{
					fclose(fic1);
					dumpAllLists(); // Libère les listes de la mémoire

					color(red, "\nDonnées invalides, le chargement n'a pu être effectué\n");
					exit(1);
				}
			}
		}else{
			fclose(fic1);
			dumpAllLists(); // Libère les listes de la mémoire

			color(red, "\nDonnées invalides, le chargement n'a pu être effectué\n");
			exit(1);
		}
		fclose(fic1);
		
		makePawns(); // Recrée les pions pour le chargement
		startGame(); // Débute la partie

	}else{
		color(red, "Fichier introuvable, la sauvegarde n'a pas pu être chargée\n");
	}
}