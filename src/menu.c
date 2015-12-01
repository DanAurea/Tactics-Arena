#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/gameEngine.h"
#include "../include/menu.h"
#include "../include/terminal.h"

/**
 * Menu principal du jeu
 */
void mainMenu(){
	int choix;

    color(fred); // Change la couleur des caractères suivant en rouge
	printf("Bienvenue sur le jeu Tactics arena SPI deluxe edition \n");
    do{
        printf("\nMenu principal :\n");
		printf(" 1 - Nouvelle partie\n");
		printf(" 2 - Charger partie\n");
		printf(" 3 - Test de gameMenu \n");
        printf(" 4 - Quitter\n");
		printf("Votre choix : ");
        color(fwhite);
		
        scanf("%i",&choix);
        switch(choix){
            case 1: gameInit();
                break;
            case 2: //loadGame();
                break;
            case 3: //gameMenu();
                break;
            case 4: break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
        }
    }while(choix != 4);
	printf("A bientôt !");
    exit(1);
}

/**
 * Récupère le nom de l'unité à partir de la liste énumérée
 * @param  unit Nom de l'unité provenant de la liste énumérée
 * @return      Nom de l'unité sous forme de chaîne    
 */
char* getNameUnit(unitName unit){
    char* uName = NULL;
    
    uName = malloc(20 * sizeof(char));
    
    switch(unit){
        case 2: strcpy(uName,"Knight"); break;
        case 3: strcpy(uName,"Scout"); break;
        case 4: strcpy(uName,"Assassin"); break;
        case 5: strcpy(uName,"Cleric"); break;
        case 6: strcpy(uName,"Pyromancer"); break;
        case 7: strcpy(uName,"Enchantress"); break;
        case 8: strcpy(uName,"Dragonborn"); break;
        case 9: strcpy(uName,"Dark Witch"); break;
        case 10: strcpy(uName,"Lightning Totem"); break;
        case 11: strcpy(uName,"Barrier Totem"); break;
        case 12: strcpy(uName,"Mud Golem"); break;
        case 13: strcpy(uName,"Golem Ambusher"); break;
        case 14: strcpy(uName,"Frost Golem"); break;
        case 15: strcpy(uName,"Stun Golem"); break;
        case 16: strcpy(uName,"Dragon Tyrant"); break;
        case 17: strcpy(uName,"Berserker"); break;
        case 18: strcpy(uName,"Beast Rider"); break;
        case 19: strcpy(uName,"Poison Wisp"); break;
        case 20: strcpy(uName,"Furgon"); break;
            
        default: break;
    }
    return uName;
}


/**
 * Affiche le nom de l'unité
 * @param unit Nom de l'unité provenant de la liste énumérée
 */
void printNameUnit(unitName unit){
    printf("%s", getNameUnit(unit));
}

/**
 * Menu du joueur lors de la partie
 * @param movable    Tableau des déplacements possibles
 * @param attackable Tableau des attaques possibles
 */
void gameMenu(unitAction movable, unitAction attackable) {
    int choix;
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

/**
 * Menu de sélection de l'unité
 * @param choice     Choix de l'action pour l'unité
 * @param movable    Tableau des déplacements possibles
 * @param attackable Tableau des attaques possibles
 */
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







