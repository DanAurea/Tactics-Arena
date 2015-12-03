#include <stdio.h>
#include "../include/gameEngine.h"
#include "../include/manageString.h"

/**
 * Affiche une bordure sur le côté droit sur les lignes vides et utiles
 * @param row Ligne actuelle 
 */
void borderRight(int row){
	int j;

	for(j = 0; j <= N; j++){
		if(j == 0 && row != N-1) // Affichage que les lignes utiles
			printf("%2c|",' ');
		if(j < N )
			printf("%4c", ' ');
		else if (row != N-1) // Affichage sur les lignes utiles
			printf("|");
	}
}

/**
 * Affiche une bordure horizontale
 */
void borderHoriz(){
	int x = 0; // Initialisation pour barre de séparation
	while( x < N){ // Affiche une barre de séparation
		printf("____");
		x = x +1;
	}
}

/**
 * Affiche les coordonnées verticales
 * @param x Point de départ coordonnée X
 * @param row Ligne de la grille actuellement en cours d'affichage
 */
void dispX(int * x, int row){
	while(* x <= N && row == 0){
		
		// Affiche les coordonnées horizontales	chiffrées
		printf("%4s", nToS(*x));
		
		if(* x == N){
			printf("\n   ");

			borderHoriz(); // Affiche une bordure horizontale délimitant le plateau
			
			printf("\n");

			borderRight(row); // Complète les bordures manquantes dû au saut de ligne

			printf("\n");
		}
		* x = * x +1;
	}
}

/**
 * Affiche la grille avec les coordonnées
 */
void gridDisp(){
	int row, col, x = 1;
	char lettre = 'A';
    char uName[3];
    
	printf("\n ");

	for(row = 0; row < N; row++){
		for(col = 0; col < N; col++){
			
            
			dispX(&x, row); // Affiche les coordonnées horizontales
            if(grid[row][col].name == empty){
                strcpy(uName, "  ");
            }else{
                strcpy(uName, get2Char(getNameUnit(grid[row][col].name))); // Copie une portion du nom de l'unité dans uName
            }
            
			if(col == 0)
				printf("%2c| %2s",' ', uName); // Affiche à la fois la bordure gauche et le nom de l'unité
			else
				printf("%4s", uName); // Affiche le nom de l'unité
			
			// Affiche les coordonnées verticales
			if(col == N-1){
				printf(" |%4c", lettre);
				lettre++;
			}

		}
		
		printf("\n");
		
		if(row == N-1){
			printf("%2c|", ' ');
			borderHoriz();
			printf("|");
		}

		borderRight(row); // Complète le creux sur la bordure droite
		printf("\n");
	}
	printf("\n");
}