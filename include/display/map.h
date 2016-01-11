
#ifndef _SDL_
	#define _SDL_
	
	#include <stdbool.h>
	#include <ESDL.h>

	#define SCREEN_WIDTH 1280 /**< Largeur de la fenêtre */
	#define SCREEN_HEIGHT 720 /**< Hauteur de la fenêtre */
	#define HEIGHT_DECOR 82 /**< Hauteur d'un décor */
	#define TILE_H 48 /**< Hauteur d'une tile */
	#define TILE_W 96 /**< Largeur d'une tile */
	#define N 11 /**< Taille de la map */

	#define DOWN_RIGHT 1
	#define DOWN_LEFT 2
	#define UP_LEFT 3
	#define UP_RIGHT 4

	typedef enum{diamond, staggered, slide}type_Map;


	bool drawMap(t_context * context, type_Map tMap);
	void getIndexMap(type_Map tMap, int posX, int posY, int * x, int * y);
	bool isOutGrid(int x, int y);
	void toIso(type_Map tMap, int * x, int * y);
	int offsetX(type_Map tMap);
	int offsetY();
	void initDisplay();
	int getUnit(int idSprite);
	void drawLimitPlayer(t_context * context, type_Map tMap);
	void deleteLimitPlayer(t_context * context, type_Map tMap);
	void delPawnsSprite(t_context * context, type_Map tMap);
	void moveSpriteTo(t_context * context, type_Map tMap, int to, int idSprite );

#endif

	extern t_context * ingame;
	extern type_Map tMap;