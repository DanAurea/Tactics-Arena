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


// Découpage de l'affichage des cellules
void top(){
	printf("%s", LT);
	printf("%s%s%s%s", HL, HL, HL, HL);
	printf("%s", RT);
}

void center(unitName name){
	printf("%s", VL);
	printf(" %s ", getNameUnit(name));
	printf("%s", VL);
}

void bottom(){
	printf("%s", LB);
	printf("%s%s%s%s", HL, HL, HL, HL);
	printf("%s", RB);
}

//Utilise les fonctions précédentes pour créer des cases individuelles
void dispTile (int row) {
	
	int i, col;
	for(i=0; i<N; i++) {
		top();
	}
	printf("\n");
	for(col=0; col < N; col++){
		center(grid[row][col].name);	
	}
	printf("\n");
	for( i = 0; i < N; i++){
		bottom();
	}
}

/**
 * Affiche la grille avec les coordonnées
 */
void gridDisp(){
	int x, y;
	char lettre = 'A';
    	char uName[3];
    
	printf("\n ");

	dispX(1); // Affiche les coordonnées horizontales

	for(x = 0; x < N; x++){
		dispTile(x);
	}
	printf("\n");
}


