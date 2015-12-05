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
 * Sélectionne une unité
 * @param  coordUnit [description]
 * @return           [description]
 */
bool selectUnit(vector * coordUnit, short noPlayer){
	char * coordString;
	unitName name;

	coordString = (char *) calloc(5, sizeof(char));
	read(coordString, 5);

	getCoordS(coordString, coordUnit); // Récupère les coordonnées saisies sous forme de vecteur

	name = grid[coordUnit->x][coordUnit->y].name;

	if( name == empty || name == decors) return false;
	else if(coordUnit->x < 0 || coordUnit->x > N || coordUnit->y < 0 || coordUnit->y > N) return false;
	else if(grid[coordUnit->x][coordUnit->y].noPlayer != noPlayer) return false;
	
	return true;
}

/**
 * Initialise la grille
 */
void gridInit(){
	int x, y, nbDecors = 0;

	for(x = 0; x < N; x++){
		for(y = 0; y < N; y++){
			grid[x][y].name = empty; // Initialise à vide
			grid[x][y].noPlayer = -1;
			
			if(x >= 0 + NB_LINES && x < N - NB_LINES && nbDecors < 7){
				if(rand() % 100 > 92){ // Ajoute un décor aléatoirement
					grid[x][y].name = decors;
					nbDecors++;
				}
			}

		}
	}
}

/**
 * Placement des unités par le joueur
 * @param noPlayer Joueur en cours 
 * @param nbUnit   
 */
void playerAddUnit(short noPlayer, int * nbUnit){
	int unitSelected;
	char * coordString;
	vector coordUnit;

	unitList(); // Affiche la liste des unités du jeu
	
	do{
		printf("Choisissez le type d'unité: ");
		scanf("%i", &unitSelected);

		if(unitSelected < knight -1 || unitSelected > furgon -1)
			printf("Aucune unité de ce type ! \n");

	}while(unitSelected < knight -1 || unitSelected > furgon -1);

	coordString = (char *) calloc(5, sizeof(char));
	
	clearBuffer(); // Vide stdin
	
	while(!correctCoord(coordString, noPlayer)){
		fontColor(red);
		if(noPlayer == 1){
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i\n",'A' + N - 1, 'A' + N - NB_LINES, N);
		}else{
			printf("\nVous pouvez placer vos unités de %c à %c et de 1 à %i\n",'A', 'A' + NB_LINES - 1, N);
		}
		fontColor(white);
		
		printf("Quelles sont les coordonnées de l'unité à placer ?\n");

		read(coordString, 5); // Saisie sécurisée

		if(!correctCoord(coordString, noPlayer)){
			printf("Coordonnées incorrectes !\n");
		}
	}

	getCoordS(coordString, &coordUnit); // Récupère les coordonnées saisies sous forme de vecteur
	free(coordString);
	
	if(grid[coordUnit.x][coordUnit.y].name != empty){ 
		destroyUnit(noPlayer, coordUnit); // Détruit l'unité en place
		* nbUnit = * nbUnit - 1; // Remet à jour le nombre d'unités
	}

	grid[coordUnit.x][coordUnit.y].name = unitSelected + 1; // Place l'unité correspondante dans la grille
	
	unitInit(noPlayer, coordUnit); // Initialise l'unité ajoutée
	addUnit(noPlayer, coordUnit);

	clearScreen();
	gridDisp(); // Affiche la grille actualisée
}

/**
 * Initiliase la liste des unités du joueur
 */
void playersInit(){

	printf("\nJoueur 1: \n\n"); // Initialisation du joueur 1
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);
		printf("Il reste %i unités.\n", NB_MAX_UNIT - i);
		fontColor(white);

		playerAddUnit(1, &i); // Ajout unité joueur 1
	}
	
	printf("\nJoueur 2: \n\n"); // Initialisation du joueur 2
	for(int i = 0; i < NB_MAX_UNIT; i++){
		fontColor(red);
		printf("Il reste %i unités.\n", NB_MAX_UNIT - i);
		fontColor(white);

		playerAddUnit(2, &i); // Ajout unité joueur 2
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

	gridInit();
	playersInit();
	* noPlayer = (rand() % 2) + 1; // Tire le joueur débutant la partie aléatoirement -> Segmentation fault pour le moment
}
