#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/gameEngine.h"
#include "../include/listes.h"

unit grid[N][N];

/**
 * Permet de savoir si l'unité courante est entourée
 * @param  currentUnit Unité courante
 * @return             True si unité entourée
 */
bool lookAround(vector currentUnit)
{
	bool surrounded = true;

	for(int i = currentUnit.x - 1; i < currentUnit.x + 1 && surrounded; i++)
	{
		for(int j = currentUnit.y - 1; j < currentUnit.y + 1 && surrounded; j++)
		{
			if(abs(i) + abs(j) == 1)
			{
				if(grid[currentUnit.x+i][currentUnit.y].name == empty)
				{
					//TODO
					// verif si unité ennemi.
					// verif si unité allié avec canGetPassed().
					surrounded=false;
				}
			}
		}
	}
	return surrounded;
}

/**
 * Initialise la grille
 */
void gridInit(){

}

/**
 * Placement des unités par le joueur
 */
void playerAddUnit(int noPlayer, int nbUnit){
	printf("Coordonnées unité %i: ", nbUnit + 1);
	
	en_tete(noPlayer);
	//ajout_droit(noPlayer, test);
}

/**
 * Initiliase la liste des unités du joueur
 */
void playersInit(){

	printf("Joueur 1: \n");
	for(int i = 0; i < 10; i++){
		playerAddUnit(1, i); // Ajout unité joueur 1
	}

	printf("\nJoueur 2: \n");
	for(int i = 0; i < 10; i++){
		playerAddUnit(2, i); // Ajout unité joueur 2
	}
}

/**
 * Initialise la partie
 * @param noPlayer Entier réprésentant le joueur
 */
void gameInit(int * noPlayer){
	srand(time(NULL));
	
	for(int i = 1; i < MAX_LISTE; i++)
		init_liste(i);

	playersInit();
	gridInit();
	//* noPlayer = (rand() % 2) + 1; // Tire le joueur débutant la partie aléatoirement -> Segmentation fault pour le moment
}