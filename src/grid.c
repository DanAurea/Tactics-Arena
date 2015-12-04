#include <stdio.h>
#include "../include/gameEngine.h"
#include "../include/grid.h"
#include "../include/terminal.h"
#include "../include/manageString.h"

/**
 * Affiche une bordure sur le cÃ´tÃ© droit sur les lignes vides et utiles
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
	int x = 0; // Initialisation pour barre de sÃ©paration
	while( x < N){ // Affiche une barre de sÃ©paration
		printf("%s%s%s%s", HL, HL, HL, HL);
		x = x +1;
	}
}

/**
 * Affiche les coordonnÃ©es verticales
 * @param x Point de dÃ©part coordonnÃ©e X
 * @param row Ligne de la grille actuellement en cours d'affichage
 */
void dispX(){
	for(short x = 1; x <= N; x++){
		
		// Affiche les coordonnÃ©es horizontales chiffrées
		if(x < 10)	printf("   %i", x);
		else		printf("  %i", x);

		if(x == N){
			printf("\n  ");
			
			printf("%s", LT);
			borderHoriz(); // Affiche une bordure horizontale dÃ©limitant le plateau
			printf("%s", RT);

			printf("\n");

			borderRight(1); // ComplÃ¨te les bordures manquantes dÃ» au saut de ligne

			printf("\n");
		}
	}
}

/**
 * Affiche la grille avec les coordonnÃ©es
 */
void gridDisp(){
	int x, y;
	char lettre = 'A';
    char uName[3];
    
	printf("\n ");

	dispX(1); // Affiche les coordonnÃ©es horizontales

	for(x = 0; x < N; x++){
		for(y = 0; y < N; y++){
            
            if(grid[x][y].name == empty){
                strcpy(uName, "  ");
            }else if(grid[x][y].name == decors){
            	strcpy(uName, "xx");
            }else{
                strcpy(uName, get2Char(getNameUnit(grid[x][y].name))); // Copie une portion du nom de l'unitÃ© dans uName
            }
            
            if(y == 0) printf("  %s ", VL); // Affiche une bordure gauche

           	fontColor(grid[x][y].unitColor);

			if(y == 0)
				printf(" %s", uName); // Affiche le nom de l'unitÃ© lorsque prÃ¨s d'une bordure gauche
			else
				printf(" %s ", uName); // Affiche le nom de l'unitÃ©

			fontColor(white);
			
			// Affiche les coordonnÃ©es verticales
			if(y == N-1){
				printf("%s   %c", VL, lettre);
				lettre++;
			}

		}
		
		printf("\n");
		
		if(x == N-1){ // Affiche la bordure base de la grille
			printf("  %s", LB);
			borderHoriz();
			printf("%s", RB);
		}

		borderRight(x); // Complète le creux sur la bordure droite
		
		printf("\n");
	}
	printf("\n");
}