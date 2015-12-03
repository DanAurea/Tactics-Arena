#include <stdio.h>
#include <time.h>
#include "../include/gameEngine.h"
#include "../include/grid.h"
#include "../include/terminal.h"
#include "../include/unit.h"
#include "../include/menu.h"
#include "../include/listes.h"
#include "../include/manageString.h"

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
 * @param noPlayer Joueur en cours 
 * @param nbUnit   
 */
void playerAddUnit(int noPlayer, int nbUnit){
	int unitSelected;
	char * coordString = NULL;
	vector coordUnit;

	unitList(); // Affiche la liste des unités du jeu
	
	do{
		printf("Choisissez le type d'unité: ");
		scanf("%i", &unitSelected);

		if(unitSelected < knight -1 || unitSelected > furgon -1)
			printf("Aucune unité de ce type ! \n");

	}while(unitSelected < knight -1 || unitSelected > furgon -1);

	coordString = (char *) malloc(4 * sizeof(char));
	
	do{
		fontColor(red);
		if(noPlayer == 1){
			printf("\nVous pouvez placer vos unités de %c à %c\n",'A' + N - 1, 'A' + N - NB_LINES);
		}else{
			printf("\nVous pouvez placer vos unités de %c à %c\n",'A', 'A' + NB_LINES - 1);
		}
		fontColor(white);
		
		printf("Quelles sont les coordonnées de l'unité à placer ?");
		scanf("%s", coordString); // Saisie des coordonnées de l'unité

		if(!correctCoord(coordString, noPlayer)){
			printf("Coordonnées incorrectes !\n");
		}
		
	}while(!correctCoord(coordString, noPlayer)); // Faire une fonction correctCoord(coordString);

	getCoordS(coordString, &coordUnit); // Récupère les coordonnées saisies sous forme de vecteur
	free(coordString);

	grid[coordUnit.x][coordUnit.y].name = unitSelected + 1; // Place l'unité correspondante dans la grille
	
	clearScreen();
	gridDisp(); // Affiche la grille actualisée
	
	unitInit(coordUnit, noPlayer);

	en_tete(noPlayer);
	//addUnit(noPlayer, coordUnit); // A faire !
}

/**
 * Initiliase la liste des unités du joueur
 */
void playersInit(){

	printf("Joueur 1: \n\n"); // Initialisation du joueur 1
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);
		printf("Il reste %i unités.\n", NB_MAX_UNIT - i);
		fontColor(white);

		playerAddUnit(1, i); // Ajout unité joueur 1
	}

	printf("\nJoueur 2: \n\n"); // Initialisation du joueur 2
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);
		printf("Il reste %i unités.\n", NB_MAX_UNIT - i);
		fontColor(white);

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
