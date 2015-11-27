#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/gameEngine.h"


/**
 * Convertis un entier en chaîne de caractère (maximum 2 chiffres)
 * @param  n Entier à convertir
 * @return   Retourne la chaîne de caractère contenant l'entier convertis
 */
char* nToS(int n) {
    char* nString = NULL;
    
    nString = malloc(3 * sizeof(char)); // Crée une zone mémoire contenant le nombre sous forme de chaîne
    
    if(n < 10){
    	nString[0] = n + 48; // Conversion sur entier d'un chiffre
    	nString[1] = '\0';
    }else{
    	nString[0] = (n / 10) + 48; // Conversion sur entier de deux chiffres
    	nString[1] = (n % 10) + 48;
    	nString[2] = '\0';
    }
    
    return nString;
}

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
 * @param grid Grille à afficher
 */
void gridDisp(char grid[N][N]){
	int row, col, x = 1;
	char lettre = 'A';

	printf("\n ");

	for(row = 0; row < N; row++){
		for(col = 0; col < N; col++){
			
			dispX(&x, row); // Affiche les coordonnées horizontales
			
			if(col == 0)
				printf("%2c|%2c",' ', grid[row][col]);
			else
				printf("%4c", grid[row][col]); // Affiche le contenu de la grille
			
			// Affiche les coordonnées verticales
			if(col == N-1){
				printf("  |%4c", lettre);
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

int rand_a_b(int min,int max){
    return rand()%(max-min)+min;
}

void gridInitTest(unit grid[N][N]){
	int row, col, i=0;
    srand(time(NULL));
	for(row = 0; row < N; row++){
		for(col = 0; col <= N; col++){
            grid[row][col].name = rand_a_b(2,9);
        }
        i++;
	}
}

