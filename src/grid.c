#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/gameEngine.h"
#include "../include/menu.h"


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
 *  Récupère 2 caractères du nom de l'unité
 *  @param name Nom de l'unité
 *  @return Retourne 2 caractères liés au nom de l'unité
 */
char* get2Char(char name[]){
    char* partName = NULL;
    
    partName = malloc(3 * sizeof(char));
    
    if(strcmp(name, "Dragonborn") == 0){
        strcpy(partName, "Db");
    }
    else if(strcmp(name, "Dragon Tyrant") == 0){
        strcpy(partName, "Dt");
    }
    else if(strcmp(name, "Beast Rider") == 0){
        strcpy(partName, "Br");
    }
    else if(strcmp(name, "Berserker") == 0){
        strcpy(partName, "Bk");
    }
    else if(strcmp(name, "Lightning Totem") == 0){
        strcpy(partName, "Lt");
    }
    else if(strcmp(name, "Barrier Totem") == 0){
        strcpy(partName, "Bt");
    }
    else if(strcmp(name, "Mud Golem") == 0){
        strcpy(partName, "Mg");
    }
    else if(strcmp(name, "Golem Ambusher") == 0){
        strcpy(partName, "Ag");
    }
    else if(strcmp(name, "Frost Golem") == 0){
        strcpy(partName, "Fg");
    }
    else if(strcmp(name, "Stun Golem") == 0){
        strcpy(partName, "Sg");
    }
    else if(strcmp(name, "Poison Wisp") == 0){
        strcpy(partName, "Pw");
    }
    else{
        partName[0] = name[0];
        partName[1] = name[1];
        partName[2] = '\0';
    }
    
    return partName;
}


/**
 * Affiche la grille avec les coordonnées
 * @param grid Grille à afficher
 */
void gridDisp(){
	int row, col, x = 1;
	char lettre = 'A';
    char uName[3];
    
	printf("\n ");
	grid[0][1].name = poisonWisp;
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
