#include "../../include/display/map.h"
#include "../../include/game/engine.h"
#include "../../include/units/unit.h"
#include "../../include/game/listes.h"
#include "../../include/controller/manageString.h"

int idCursor = -1; /**< Identifiant du curseur */

/**
 * Glisser et déposer
 * @param context 		Contexte dans lequel dessiner
 * @param tMap    		Type de la carte
 * @param nbUnit  		Nombre d'unité
 * @param limitUnits 	Limites d'unités
 * @return 		  		Retourne true si déposé sinon false
 */
int dragNdrop(t_context * context, type_Map tMap, int * nbUnit, int limitUnits[]){
	int x, y, posX = 0, posY = 0;
	int mousePressed = SDL_isMousePressed(SDL_BUTTON_LEFT);
	int overObj = -1;
	char filename[150] = ""; // It's should be enough
	vector coordUnit;

	if(mousePressed){ // Clic sur une zone
			overObj = SDL_ismouseover(context, SPRITE);

			if(overObj >= 0){

				posX = context->contextSprite[overObj].x;
				posY = context->contextSprite[overObj].y;

				getIndexMap(tMap, posX + context->contextSprite[overObj].sp_width / 2, posY + context->contextSprite[overObj].sp_height / 2, &x, &y);

				if(tooMuchUnit(getUnit(overObj), limitUnits) && (isOutGrid(x, y))) return -1; // Unité surprésente sur le terrain

				sprintf(filename, "%s%s", getNameUnit(overObj + 2), ".png"); // Nom du fichier de l'unité

				if(isOutGrid(x, y)){
					
					// Recrée un nouveau sprite à l'emplacement initial si en dehors de la map
					SDL_newSprite(context, filename , colorGreenLight, context->contextSprite[overObj].sp_height, context->contextSprite[overObj].sp_width, posX, posY, context->contextSprite[overObj].position, 1, 0);
					overObj = context->nbSprite - 1; // Force le déplacement de la copie

					SDL_setOnLayer(context, SPRITE, context->nbSprite - 1, 10);

				}else if(grid[x][y].noPlayer != noPlayer) return -1;

				while(mousePressed){

					SDL_drag(context, SPRITE, overObj); // Glisse l'objet crée
					
					if(showMouseCursor(ingame, tMap))
						SDL_generate(ingame);
					
					SDL_Delay(20); // 50 FPS
					mousePressed = SDL_isMousePressed(SDL_BUTTON_LEFT);

				}
				mousePressed = -1;		
			}

	}

	if(mousePressed == - 1){ // Objet relaché

		if(overObj >= 0){

			if(!isOutGrid(x, y)){ // Objet pris de la map

				coordUnit.x = x;
				coordUnit.y = y;

				erase(&grid[x][y]); // Efface de la grille
				destroyUnit(coordUnit); // Efface de la liste du joueur courant
				* nbUnit = * nbUnit - 1;

				getIndexMap(tMap, SDL_getmousex(), SDL_getmousey(), &x, &y); // Récupère la nouvelle position

				if(!isOutGrid(x,y) && grid[x][y].name != empty){ // Si la nouvelle case n'est pas vide on remet le sprite à sa place initiale
					x = coordUnit.x;
					y = coordUnit.y;
				}

				if(isOutGrid(x, y)){ // Lâché hors de la map

					coordUnit.x = x;
					coordUnit.y = y;

					updateLimits(getUnit(overObj), limitUnits, coordUnit); // Remet à jour les limites 
					
					SDL_delSprite(context, overObj); // Supprime le sprite
					SDL_generate(context);

					return -1;

				}else if(noPlayer == FIRST_PLAYER){
					
					if(x < N - NB_LINES){
						x = coordUnit.x;
						y = coordUnit.y;
					}

				}else if(noPlayer == FIRST_PLAYER + 1){
					
					if(x > NB_LINES - 1){
						x = coordUnit.x;
						y = coordUnit.y;
					}

				}

			}else{
				getIndexMap(tMap, SDL_getmousex(), SDL_getmousey(), &x, &y);
			}


			if(!rightSide(x, y)){ // Vérifie que le placement est possible pour le joueur en cours
				
				SDL_delSprite(context, overObj); // Supprime le sprite
				SDL_generate(context);

				return -1;
			}

			if(!isOutGrid(x, y)){ // Lâché dans la map ou non

				posX = x * TILE_W;
				posY = y * TILE_H;

				toIso(tMap, &posX, &posY); // Convertis les coordonnées en coordonnées isométriques

				posX += offsetX(tMap);
				posY += offsetY() - context->contextSprite[overObj].sp_height / 2;

				if(grid[x][y].name != empty){ // Lors d'un remplacement d'unité déjà présente sur le terrain
					
					coordUnit.x = x;
					coordUnit.y = y;

					if(overObj > 0) overObj--; // Décalage vers la gauche des identifiants

					SDL_delSprite(context, grid[x][y].idSprite); // Supprime le sprite en place
					updateIdSprite(grid[x][y].idSprite, -1); // Met à jour les identifiants des sprites

					erase(&grid[x][y]); // Efface de la grille
					destroyUnit(coordUnit); // Efface de la liste du joueur courant
					* nbUnit = * nbUnit - 1;

				}

			}

			SDL_drop(context, SPRITE, overObj, posX, posY); // Dépose l'objet
			SDL_generate(context);

			if(!isOutGrid(x, y)) return overObj;
			else{
	
				SDL_delSprite(context, overObj); // Supprime le sprite
				SDL_generate(context);

				return -1;
			}

		}
	}else SDL_Delay(20); // 50 FPS

	return -1;
}

/**
 * Affiche un curseur à la position indiquée
 * @param context Contexte dans lequel dessiner
 * @param tMap Type de la map
 * @param x Indice X de la map
 * @param y Indice Y de la map
 */
void showCursor(t_context * context, type_Map tMap, int x, int y){
	int posX, posY;

	posX = x * TILE_W;
	posY = y * TILE_H;

	toIso(tMap, &posX, &posY);

	posX += offsetX(tMap);
	posY += offsetY();

	if(idCursor == - 1){
		idCursor = context->nbImg;
		SDL_newImage(context, NULL, "cursor.png", posX, posY); // Initialise le curseur si pas encore dessiné
	}else{
		SDL_editImage(context, idCursor, posX, posY); // Met à jour la position du curseur
	}
	SDL_setOnLayer(context, IMG, idCursor, 2);
}

/**
 * Affiche un curseur à la position pointée
 * @param context Contexte dans lequel dessiner
 * @param tMap    Type de la map
 */
int showMouseCursor(t_context * context, type_Map tMap){
	int x = 0, y = 0, mX = 0, mY = 0;

	if(idCursor == -1){
		showCursor(context, tMap, x, y); // Affiche en surbillance la zone pointée
		return 1;
	}

	if(idCursor < 0) return 0;

	getIndexMap(tMap, context->contextImg[idCursor].x + context->contextImg[idCursor].buffer->w / 2, context->contextImg[idCursor].y + context->contextImg[idCursor].buffer->h / 2, &x, &y);
	getIndexMap(tMap,  SDL_getmousex(),  SDL_getmousey(), &mX, &mY);

	if(mX != x || mY != y){

		if(mX >= 0 && mX < N && mY >= 0 && mY < N){
				showCursor(context, tMap, mX, mY); // Affiche en surbillance la zone pointée
				return 1;
		}
	}
	return 0;
}