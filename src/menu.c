#include <stdio.h>
#include <stdlib.h>
#include "../include/gameEngine.h"
#include "../include/unit.h"
#include "../include/menu.h"


void mainMenu(unit grid[N][N]){
	int choix;
	printf("Bienvenue sur le jeu Tactics arena SPI deluxe edition \n");
    do{
        printf("\nMenu :\n");
		printf(" 1 - Nouvelle partie\n");
		printf(" 2 - Charger partie\n");
		printf(" 3 - Quitter\n");
		printf("Votre choix : ");
		scanf("%i",&choix);
        switch(choix){
            case 1: gridInitTest(grid); break;
            case 2: //loadGame();
            break;
            case 3: gameMenu(grid); break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 3\n");
        }
    }while(choix!=3);
	printf("A bientôt !");
}


// Affiche le nom de l'unité
void printNameUnit(unitName unit){
    switch(unit){
        case 2: printf("Knight"); break;
        case 3: printf("Scout"); break;
        case 4: printf("Assassin"); break;
        case 8: printf("Dragonborn"); break;
        default: printf("Ce n'est pas une unité");
    }
}


void gameMenu(unit grid[N][N]) {
    int row, col;
    printf("1) Unités pouvant se déplacer : \n");
    for(row=0; row < N; row++){
        for(col=0; col < N; col++){
            printNameUnit(grid[row][col].name);
        }
    }
    printf("\n");
    printf("2) Attaques : \n");
    
    printf("\n");
    printf("3) Passer tour");
    
}