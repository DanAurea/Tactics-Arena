#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include "../include/gameEngine.h"
#include "../include/terminal.h"
#include "../include/menu.h"
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
	int unitSelected;
	char * coordString = NULL;
	vector coordUnit;

	unitList(); // Affiche la liste des unités du jeu
	printf("Choisissez le type d'unité: ");
	
	do{
		
		scanf("%i", &unitSelected);

		if(unitSelected < knight -1 || unitSelected > furgon -1)
			printf("Aucune unité de ce type ! \n");

	}while(unitSelected < knight -1 || unitSelected > furgon -1);

	coordString = (char *) malloc(4 * sizeof(char));
	
	/*do{
		printf("Quelles sont les coordonnées de l'unité à placer ?");
		scanf("%s", coordString);

		if(strlen(coordString) > 3 && !isalnum(coordString))
			printf("Coordonnées incorrecte !\n");

	}while(strlen(coordString) > 3 && !isalnum(coordString)); // Faire une fonction correctCoord(coordString);*/

	//getCoordS( coordString, &coordUnit); // A faire !
	free(coordString);

	grid[coordUnit.x][coordUnit.y].name = unitSelected + 1; // Place l'unité correspondante dans la grille

	//unitInit(coordUnit); // A faire !

	en_tete(noPlayer);
	//addUnit(noPlayer, coordUnit); // A faire !
}

/**
 * Initiliase la liste des unités du joueur
 */
void playersInit(){

	printf("Joueur 1: \n\n");
	for(int i = 0; i < NB_MAX_UNIT; i++){
		playerAddUnit(1, i); // Ajout unité joueur 1
	}

	printf("\nJoueur 2: \n\n");
	for(int i = 0; i < NB_MAX_UNIT; i++){
		playerAddUnit(2, i); // Ajout unité joueur 2
	}
}

/**
 * Initialise la partie
 * @param noPlayer Entier réprésentant le joueur
 */
void gameInit(int * noPlayer){
	srand(time(NULL));
	
	for(int i = 1; i < MAX_JOUEUR; i++)
		init_liste(i);

	playersInit();
	gridInit();
	//* noPlayer = (rand() % 2) + 1; // Tire le joueur débutant la partie aléatoirement -> Segmentation fault pour le moment
}
