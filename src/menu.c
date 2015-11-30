#include <stdio.h>
#include <stdlib.h>
#include "../include/gameEngine.h"
#include "../include/unit.h"
#include "../include/menu.h"


void mainMenu(){
	int choix;
	printf("Bienvenue sur le jeu Tactics arena SPI deluxe edition \n");
    do{
        printf("\nMenu principal :\n");
		printf(" 1 - Nouvelle partie\n");
		printf(" 2 - Charger partie\n");
		printf(" 3 - test\n");
        printf(" 4 - Quitter\n");
		printf("Votre choix : ");
		scanf("%i",&choix);
        switch(choix){
            case 1: //gameUnit();
                break;
            case 2: //loadGame();
                break;
            case 3: gameMenu(); break;
            case 4: break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
        }
    }while(choix != 4);
	printf("A bientôt !");
    exit(1);
}


// Affiche le nom de l'unité
void printNameUnit(unitName unit){
    switch(unit){
        case 2: printf("Knight "); break;
        case 3: printf("Scout "); break;
        case 4: printf("Assassin "); break;
        case 5: printf("Cleric "); break;
        case 6: printf("Pyromancer "); break;
        case 7: printf("Enchantress "); break;
        case 8: printf("Dragonborn "); break;
        case 9: printf("darkWitch "); break;
        case 10: printf("lightningTotem "); break;
        case 11: printf("barrierTotem "); break;
        case 12: printf("mudGolem "); break;
        case 13: printf("golemAmbusher "); break;
        case 14: printf("frostGolem "); break;
        case 15: printf("stunGolem "); break;
        case 16: printf("dragonTyrant "); break;
        case 17: printf("Berserker "); break;
        case 18: printf("beastRider "); break;
        case 19: printf("poisonWisp "); break;
        case 20: printf("Furgon "); break;

        default: break;
    }
}


void gameMenu(unitAction movable, unitAction attackable) {
    do{
        printf("\nMenu :\n");
        printf(" 1 - Unités pouvant se déplacer\n");
        printf(" 2 - Unités pouvant attaquer\n");
        printf(" 3 - Changer de direction\n");
        printf(" 4 - Passer tour\n");
        printf(" 5 - Abandonner la partie\n");

        printf("Votre choix : ");
        scanf("%i",&choix);
        switch(choix){
            case 1: unitMenu(1, movable, attackable); break;
            case 2: unitMenu(2, movable, attackable); break;
            case 3: unitMenu(3, movable, attackable); break;
            case 4: // Passer tour
                break;
            case 5: //Abandonner partie
                break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 5\n");
        }
    }while(choix != 5);

    
}

void unitMenu(int choice, unitAction movable, unitAction attackable){
    switch(choice){
        case 1:
            //Unités pouvant se déplacer
            break;
        case 2:
            //Unités pouvant attaquer
            break;
        case 3:
            //Unités du joueur
            break;
        default: printf("Erreur fonction unitMenu");
            
    }
    
}







