#include <sys/stat.h>
#include <signal.h>
#include <math.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/controller/manageString.h"
#include "../../include/controller/manageSignal.h"
#include "../../include/display/map.h"

t_context * ingame = NULL; /**< Contexte dans lequel dessiner */
type_Map tMap = diamond; /**< Type de carte */

/**
 * Convertis les coordonnées cartésiennes en coordonnées isométriques
 * @param tMap Type de la carte
 * @param x Position horizontale cartésienne
 * @param y Position verticale cartésienne
 */
void toIso(type_Map tMap, int * x, int * y){

	if(tMap == diamond){
		* x = (* x - * y * 2) / 2;
		* y = (* x + * y * 2) / 2;
	}else if(tMap == slide || tMap == staggered){

		if(tMap == slide){
			* x = (* x + * y);
		}else{
			* x = * x + ((* y / TILE_H % 2 == 0) ? 0 : 1 ) * (TILE_W/2);
		}

		* y = (* y / 2);
	}

}

/**
 * Décalage en X
 * @param tMap Type de la carte
 */
int offsetX(type_Map tMap){

	if(tMap == diamond)
		return (SCREEN_WIDTH - TILE_W) / 2; // Diamond map
	else
		return (SCREEN_WIDTH - (N + 1)  * TILE_W) / 2; // Slide AND Staggered map
}

/**
 * Décalage en Y
 */
int offsetY(){
	return (SCREEN_HEIGHT - N * TILE_H) /2;
}

/**
 * Récupère les indices x et y de la tile en posX / posY
 * @param tMap Type de la carte
 * @param posX Coordonnée X pointée
 * @param posY Coordonnée Y pointée
 * @param x Pointeur sur l'indice x
 * @param x Pointeur sur l'indice y
 */
void getIndexMap(type_Map tMap, int posX, int posY, int * x, int * y){
	posX -= offsetX(tMap);

	if(tMap == diamond){
		posX -= TILE_W / 2; // Diamond map
		posY -= offsetY();

		* x = floor( ( (float)posX/ (TILE_W/2) + (float)posY/(TILE_H/2)) / 2 );;
		* y = floor( ( (float)posY/ (TILE_H/2) - (float)posX/(TILE_W/2)) / 2 );;

	}

}

/**
 * Récupère le type d'unité
 * @param idSprite Identifiant du sprite
 */
int getUnit(int idSprite){
	char name[70] = " ";

	if(idSprite >= ingame->nbSprite) return -1;

	if(!ingame->contextSprite[idSprite].file) return -1;

	for(int i = 0; i < strlen(ingame->contextSprite[idSprite].file); i ++){

		if(ingame->contextSprite[idSprite].file[i] == '.') return getNumber(name);
		
		name[i] = ingame->contextSprite[idSprite].file[i];

	}

	return -1;
}

/**
 * Vérifie que les coordonnées sont dans la grille
 * @param  x Coordonnées x
 * @param  y Coordonnées y
 * @return   Retourne false si pas en dehors
 */
bool isOutGrid(int x, int y){
    return !(x >= 0 && x < N && y >= 0 && y < N);
}

/**
 * Dessine une tile aux coordonnées posX et posY
 * @param context Contexte dans lequel dessiner
 * @param tMap Type de la carte
 * @param posX Coordonnées X de la tile à dessiner
 * @param posY Coordonnées Y de la tile à dessiner
 */
bool drawTile(t_context * context , type_Map tMap, int posX, int posY){
	int x = posX / TILE_W, y = posY / TILE_H;

	toIso(tMap, &posX, &posY); // Convertis les coordonnées en coordonnées isométriques

	posX += offsetX(tMap);
	posY += offsetY();

	if(y == N-1 || ( x == 0 && (tMap == slide || tMap == staggered) )){
		return SDL_newImage(context, NULL, "base_Cube.png", posX, posY);
	}

	if(tMap == diamond){

		if(x == N-1){
			return SDL_newImage(context, NULL, "base_Cube.png", posX, posY);
		}else{
			return SDL_newImage(context, NULL, "base_Tile.png", posX, posY);
		}

	}else if(tMap == slide){

		if(x != 0){
			return SDL_newImage(context, NULL, "base_Tile.png", posX, posY);
		}

	}else if(tMap == staggered){

		if((x == N - 1 && y % 2 != 0)){
			return SDL_newImage(context, NULL, "base_Cube.png", posX, posY);
		}else{
			return SDL_newImage(context, NULL, "base_Tile.png", posX, posY);
		}

	}

	return true;
}

/**
 * Dessine les limites de placements d'unités
 * @param context Contexte dans lequel dessiner
 * @param tMap    Type de la carte
 */
void drawLimitPlayer(t_context * context, type_Map tMap){
	int posX = 0, posY = 0;

	if(noPlayer == FIRST_PLAYER){
		
		for(int x = N - 1; x >= N - NB_LINES; x--){
			for(int y = 0; y < N; y++){

				posX = x * TILE_W;
				posY = y * TILE_H;

				toIso(tMap, &posX, &posY); // Convertis les coordonnées en coordonnées isométriques

				posX += offsetX(tMap);
				posY += offsetY();

				SDL_newImage(context, NULL, "red_Tile.png", posX, posY);

			}
		}

	}else if(noPlayer == FIRST_PLAYER + 1){

		for(int x = 0; x < NB_LINES; x++){
			for(int y = 0; y < N; y++){

				posX = x * TILE_W;
				posY = y * TILE_H;

				toIso(tMap, &posX, &posY); // Convertis les coordonnées en coordonnées isométriques

				posX += offsetX(tMap);
				posY += offsetY();

				SDL_newImage(context, NULL, "red_Tile.png", posX, posY);

			}
		}

	}

}

/**
 * Supprimme les limites de placements d'unités
 * @param context Contexte dans lequel dessiner
 * @param tMap    Type de la carte
 */
void deleteLimitPlayer(t_context * context, type_Map tMap){
	
	for (int i = 0; i < N  * NB_LINES; i++){
		SDL_delImage(context, context->nbImg - 1); // Supprime la dernière image ajoutée au jeu
	}
}

/**
 * Dessine un décor
 * @param context Contexte dans lequel dessiner
 * @param tMap    Type de la carte
 * @param posX Coordonnées X de la tile à dessiner
 * @param posY Coordonnées Y de la tile à dessiner
 */
bool drawDecor(t_context * context , type_Map tMap, int posX, int posY){
	
	toIso(tMap, &posX, &posY); // Convertis les coordonnées en coordonnées isométriques

	posX += offsetX(tMap);
	posY += offsetY() - HEIGHT_DECOR / 2;

	return SDL_newImage(context, NULL, "rock.png", posX, posY);
}

/**
 * Dessine une carte
 * @param context Contexte dans lequel dessiner
 * @param tMap    Type de la carte
 */
bool drawMap(t_context * context, type_Map tMap){
	int x, y;
	int posX = 0, posY = 0;

	for (x = 0; x < N; x++){
			for (y = 0; y < N; y++){

				posX =  x * TILE_W;
				posY =  y * TILE_H;

				if(!drawTile(context, tMap, posX, posY)) return false;

				if(grid[x][y].name == decors){
					if(!drawDecor(context, tMap, posX, posY)) return false;
				}

			}
	}

	return true;
}

/**
 * Check if a file exist
 * @return true if and only if the file exists, false else
 */
bool fileExist(const char* file) {
    struct stat buffer;

    return (stat(file, &buffer) == 0);
}

/**
 * Dessine les pions du jeu
 * @param context Contexte dans lequel dessiner
 * @param tMap    Type de la carte
 * @return		  Retourne true en cas de succès sinon false
 */
bool drawPawns(t_context * context, type_Map tMap){
	int x = 0, y = 0, nbTiles = 0;
	int posX = 0, posY = 20;
	SDL_Surface * tmp = NULL;
	char fileDir[250];
	char filename[150]; // It's should be enough

	for(int i = 0; i < 4; i++){

		if(i != empty && i != decors){

			if(strlen(getNameUnit(i)) + strlen(".png") > 149){

				fprintf(stderr, "Le nom du fichier est trop long.");
				return false;
			
			}

			sprintf(filename, "%s%s", getNameUnit(i), ".png");

			sprintf(fileDir, "%s%s", "ressources/images/", filename);

			if(!fileExist(fileDir)){

				fprintf(stderr, "Le fichier %s n'existe pas.", filename);
				return false;

			}
			
			tmp = IMG_Load(fileDir);

			if(!tmp){

				fprintf(stderr, "Le fichier %s n'a pu être chargé.", filename);
				return false;

			}

			posX = nbTiles * TILE_W;

			getIndexMap(tMap, posX + tmp->w, posY + tmp->h, &x, &y);

			while( (x >= 0 && x <= N && y >= 0 && y <= N) || nbTiles * TILE_W + tmp->w > SCREEN_WIDTH - 10){ // Tant qu'une unité est dessinée sur la carte
				

				if(nbTiles * TILE_W + tmp->w > SCREEN_WIDTH - 10){ // Remet en début de ligne si hors de l'écran et passe à la ligne suivante
					
					nbTiles = 0;
					posX = nbTiles * TILE_W;
					posY += tmp->h * 1.2;
				
				}else	nbTiles++;

				if(x < N )	getIndexMap(tMap, nbTiles * TILE_W + tmp->w, posY + tmp->h, &x, &y); // Vérifie le coin inférieur droit
				else	getIndexMap(tMap, nbTiles * TILE_W, posY + tmp->h, &x, &y); // Vérifie le coin inférieur gauche

			}

			posX = nbTiles * TILE_W; // Remet à jour la position au cas où la position a changé entre temps

			if(!SDL_newSprite(context, filename, colorGreenLight, tmp->h, tmp->w, posX, posY, 1, 1, 0))	return false;

			SDL_newText(context, NULL, getNameUnit(i), colorWhite, posX + abs(tmp->w - strlen(getNameUnit(i)) * 7) / 2 , posY + tmp->h);

			SDL_FreeSurface(tmp);
			tmp = NULL;

			nbTiles++;
		}

    }

    return true;
}

/**
 * Efface les sprites des pions du jeu
 */
void delPawnsSprite(t_context * context, type_Map tMap){
	
	for(int i = 0; i < 1; i++){
		SDL_delSprite(context, i);
	}

}

/**
 * Initialise l'affichage du jeu
 */
void initDisplay(){

	SDL_initWindow(SCREEN_WIDTH, SCREEN_HEIGHT, 0, "Tactics Arena", "M_ICON.png", 1, "global.ttf", 20, 0);

	ingame = SDL_newContext("Tactics Arena", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	if(!drawMap(ingame, tMap) || !drawPawns(ingame, diamond)) raise(SIGINT);

	SDL_generate(ingame);

}