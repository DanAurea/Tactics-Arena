#include <stdio.h>
#include "../include/gameEngine.h"
#include "../include/menu.h"
#include "../include/terminal.h"
#include "../include/manageString.h"

/**
 * Menu principal du jeu
 */
void mainMenu(){
	int choix;

    color(red, "Bienvenue sur le jeu Tactics arena SPI deluxe edition \n"); // Change la couleur des caractères suivants en rouge
    
    do{
        printf("\nMenu principal :\n");
		printf(" 1 - Nouvelle partie\n");
		printf(" 2 - Charger partie\n");
		printf(" 3 - Test de gameMenu \n");
        	printf(" 4 - Quitter\n");
		printf("Votre choix : ");	
        scanf("%i",&choix);
        switch(choix){
            case 1: gameInit();
                break;
            case 2: //loadGame();
                break;
            case 3: //gameMenu(movable, attackable);
                break;
            case 4: break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
        }
    }while(choix != 4);
	printf("A bientôt !");
    exit(1);
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
            case 1: //unitMenu(1, movable, attackable); 
break;
            case 2: //unitMenu(2, movable, attackable); 
break;
            case 3: //unitMenu(3, movable, attackable);
break;
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
	char yn;
	switch(choice){
        	case 1:
		    	//Unités pouvant se déplacer
			printf("Se déplacer ? y/n");
			read(&yn, 1);
			if(yn == 'y' || yn == 'Y') {
				//Déplace
			}else{
				printf("Saisie invalide");
			}
		    	break;
        	case 2:
			//Unités pouvant attaquer
			printf("Attaquer ? y/n");
			read(&yn, 1);
			if(yn == 'y' || yn == 'Y') {
				//Attaque
			}else{
				printf("Saisie invalide");
			}
			break;
        	case 3:
			//Change de direction
			break;
		default: printf("Erreur fonction unitMenu");      
    	}
	gameMenu(movable, attackable);
}


/**
 * Affiche la liste des unités inclus dans le jeu
 */
void unitList(){
    for(int i = knight; i <= furgon; i++){
        printf("%i - %s\n", i - 1, getNameUnit(i));
    }
}







