/**
 @file grid.c
 @brief Gestion de la grille
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <stdio.h>
#include "../../include/game/engine.h"
#include "../../include/display/grid.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"

/**
 * Affiche une bordure sur le côté droit sur les lignes vides et utiles
 * @param row Ligne actuelle
 */
void borderRight(short row){
	int j;

	for(j = 0; j <= N; j++)
	{
		if(j == 0 && row != N-1) // Affichage que les lignes utiles
			printf("  %s", VL);
		if(j < N ){
			color(grid[row + 1][j].unitColor,"Screen"); // Prend la couleur du pion en dessous pour toute une case
			printf("    ");
		}

		else if (row != N-1) // Affichage sur les lignes utiles
			printf("%s", VL);
	}
}

/**
 * Affiche une bordure horizontale
 */
void borderHoriz(){
	int x = 0; // Initialisation pour barre de séparation
	while( x < N){ // Affiche une barre de séparation
		printf("%s%s%s%s", HL, HL, HL, HL);
		x +=1;
	}
}

/**
 * Affiche les coordonnées verticales
 */
void dispX(){
	for(short x = 1; x <= N; x++){

		// Affiche les coordonnées horizontales chiffrées
		if(x < 10)
			printf("   %i", x);
		else
			printf("  %i", x);

		if(x == N){
			printf("\n  ");

			printf("%s", LT);
			borderHoriz(); // Affiche une bordure horizontale délimitant le plateau
			printf("%s", RT);

			printf("\n");

			borderRight(-1); // Complète les bordures manquantes dû au saut de ligne + prend la couleur des pions en dessous (donc -1)

			printf("\n");
		}
	}
}

/**
 * Affiche la grille avec les coordonnées
 */
void gridDisp(){
	int x, y;
	char lettre = 'A';
    char * uName; // Nom unité


	printf("\n  ");

	dispX(); // Affiche les coordonnées horizontales
	for(x = 0; x < N; x++)
	{

		for(y = 0; y < N; y++)
		{

            uName = get2Char(getNameUnit(grid[x][y].name)); // Copie une portion du nom de l'unité dans uName (mémoire dynamique)

            if(y == 0) printf("  %s", VL); // Affiche une bordure gauche


            color(grid[x][y].unitColor,"Screen");
            if(grid[x][y].noPlayer == FIRST_PLAYER)
            {
                fontColor(red);
            }
            else if(grid[x][y].noPlayer == FIRST_PLAYER + 1)
            {
                fontColor(blue);
            }

			printf(" %s ", uName);

			free(uName); // Libère la mémoire allouée
			reinitColor();

			// Affiche les coordonnées verticales
			if(y == N-1){
				printf("%s   %c", VL, lettre);
				lettre++;
			}

		}

		printf("\n");

		if(x == N-1){ // Affiche la bordure basse de la grille
			printf("  %s", LB);
			borderHoriz();
			printf("%s", RB);
		}
		else
            borderRight(x); // Complète le creux sur la bordure droite

		printf("\n");
	}

	for(int i = 0; i < N + N / 1.5; i++){
		printf(" ");
	}
    printf("xx : décors\n\n   ");

    color(yellow,"Screen");
    printf("   ");
    reinitColor();
    printf(" Cibles  ");

    color(green,"Screen");
    printf("   ");
    reinitColor();
    printf(" Mouvements possibles  ");

    color(white,"Screen");
    printf("   ");
    reinitColor();
    printf(" Sélection / Unité pouvant agir\n");

	printf("\n");
}
