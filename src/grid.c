#include <stdio.h>
#include "../include/gameEngine.h"
#include "../include/grid.h"
#include "../include/terminal.h"
#include "../include/manageString.h"

/**
 * Affiche une bordure sur le côté droit sur les lignes vides et utiles
 * @param row Ligne actuelle 
 */
void borderRight(short row){
	int j;

	for(j = 0; j <= N; j++){
		if(j == 0 && row != N-1) // Affichage que les lignes utiles
			printf("  %s", VL);
		if(j < N )
			printf("    ");
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
		x = x +1;
	}
}

/**
 * Affiche les coordonnées verticales
 * @param x Point de départ coordonnÃ©e X
 * @param row Ligne de la grille actuellement en cours d'affichage
 */
void dispX(){
	for(short x = 1; x <= N; x++){
		
		// Affiche les coordonnées horizontales chiffrées
		printf("   %i", x);

		if(x == N){
			printf("\n  ");
			
			printf("%s", LT);
			borderHoriz(); // Affiche une bordure horizontale délimitant le plateau
			printf("%s", RT);

			printf("\n");

			borderRight(1); // Complète les bordures manquantes dû au saut de ligne

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

	printf("\n ");

	dispX(1); // Affiche les coordonnées horizontales

	for(x = 0; x < N; x++){
		for(y = 0; y < N; y++){
            
            uName = get2Char(getNameUnit(grid[x][y].name)); // Copie une portion du nom de l'unité dans uName (mémoire dynamique)

            if(y == 0) printf("  %s ", VL); // Affiche une bordure gauche

           	fontColor(grid[x][y].unitColor);

			if(y == 0)
				printf("%s ", uName); // Affiche le nom de l'unité lorsque prés d'une bordure gauche
			else
				printf(" %s ", uName); // Affiche le nom de l'unité

			fontColor(white);

			free(uName); // Libère la mémoire allouée

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

		borderRight(x); // Complète le creux sur la bordure droite
		
		printf("\n");
	}
	printf("\n");
}