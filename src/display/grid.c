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
		    color(grid[row][j].unitColor,"Screen");
			printf("    ");
			reinitColor();
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
 * @param x Point de départ coordonnÃ©e X
 * @param row Ligne de la grille actuellement en cours d'affichage
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
void dispTile (int x, int y)
{
    //int tileColor = grid[x][y].unitColor;
    char * uName; // Nom unité

    uName = get2Char(getNameUnit(grid[x][y].name)); // Copie une portion du nom de l'unité dans uName (mémoire dynamique)

    if(grid[x][y].noPlayer == FIRST_PLAYER){
        fontColor(red);
    }else if(grid[x][y].noPlayer == FIRST_PLAYER+1){
        fontColor(blue);
    }else
    fontColor(white);


    if((x == 0||x == N-1) && y != 0)
    {
        printf("%s",HL);
    }
        if((y == 0||y == N-1) && x != 0)
    {
        printf("%s",VL);
    }
    if(x+y == 0)
    {
        printf("%s",LT);
    }
    if(x == 0 && y == N-1)
    {
        printf("%s",RT);
    }
    if(x == N-1 && y == 0)
    {
        printf("%s",LB);
    }
    if(x == N-1 && y == N-1)
    {
        printf("%s",RB);
    }
    reinitColor();
    free(uName);
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

            if(y == 0) printf("  %s ", VL); // Affiche une bordure gauche


            color(grid[x][y].unitColor,"Screen");
            if(grid[x][y].noPlayer == FIRST_PLAYER)
            {
                fontColor(red);
            }
            else if(grid[x][y].noPlayer == FIRST_PLAYER+1)
            {
                fontColor(blue);
            }
            else
                fontColor(white);

			if(y == 0)
				printf("%s ", uName); // Affiche le nom de l'unité lorsque prés d'une bordure gauche
			else
				printf(" %s ", uName); // Affiche le nom de l'unité

			reinitColor();
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
		else
            borderRight(x); // Complète le creux sur la bordure droite

		printf("\n");
	}
	printf("\n");
}
