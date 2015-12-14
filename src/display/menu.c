#include <stdio.h>
#include <ctype.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/turn.h"
#include "../../include/display/menu.h"
#include "../../include/display/grid.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"

/**
 * Menu principal du jeu
 */
void mainMenu(){
puts(
"_________ _______  _______ __________________ _______  _______ " "\n"
"\\__   __/(  ___  )(  ____ \\__   __/ \\__   __/(  ____ \\(  ____ \\ " "\n"
"   ) (   | (   ) || (    \\/   ) (      ) (   | (    \\/| (    \\/" "\n"
"   | |   | (___) || |         | |      | |   | |      | (_____ " "\n"
"   | |   |  ___  || |         | |      | |   | |      (_____  )" "\n"
"   | |   | (   ) || |         | |      | |   | |            ) |" "\n"
"   | |   | )   ( || (____/\\   | |   ___) (___| (____/\\/\\____) |" "\n"
"   )_(   |/     \\|(_______/   )_(   \\_______/(_______/\\_______)" "\n"
"                                                               " "\n"
" _______  _______  _______  _        _______ " "\n"
"(  ___  )(  ____ )(  ____ \\( (    /|(  ___  )" "\n"
"| (   ) || (    )|| (    \\/|  \\  ( || (   ) |" "\n"
"| (___) || (____)|| (__    |   \\ | || (___) |" "\n"
"|  ___  ||     __)|  __)   | (\\ \\) ||  ___  |" "\n"
"| (   ) || (\\ (   | (      | | \\   || (   ) |" "\n"
"| )   ( || ) \\ \\__| (____/\\| )  \\  || )   ( |" "\n"
"|/     \\||/   \\__/(_______/|/    )_)|/     \\|" "\n"
);



    int choix;
    color(red, "Bienvenue sur le jeu Tactics arena SPI deluxe edition \n"); // Change la couleur des caractères suivants en rouge
    do{
        printf("\nMenu principal :\n");

        printf(" 1 - Nouvelle partie\n");
        printf(" 2 - Charger partie\n");
        printf(" 3 - Test de gameMenu \n");
        printf(" 4 - Quitter\n");
        printf("Votre choix : ");   
        
        choix = readLong();	// Check = 1 si chiffre est rentré, 0 sinon
    	
        if(choix == 0) {
    		printf("Erreur : Veuillez rentrer un chiffre et non un caractère \n");
    	}

        switch(choix){
            case 1: gameInit();
                break;
            case 2: //loadGame();
                break;
            case 3: gameMenu();
                break;
            case 4: break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
        }
	
    }while(choix != 4 || choix != 1);
    printf("A bientôt !");
    exit(1);
}

/**
 * Menu du joueur lors de la partie
 */
void gameMenu(){
    int choix;
     
    do{
        printf("\nMenu :\n");
        printf(" 1 - Unités pouvant se déplacer\n");
        printf(" 2 - Unités pouvant attaquer\n");
        printf(" 3 - Changer de direction\n");
        printf(" 4 - Passer tour\n");
        printf(" 5 - Abandonner la partie\n");

        printf("Votre choix : ");
        choix = readLong();	
    	
        if(choix == 0) {
    		printf("Erreur : Veuillez rentrer un chiffre et non un caractère \n");
    	}

        switch(choix){

            case 1: unitMenu(1); break;
            case 2: unitMenu(2); break;
            case 3: unitMenu(3); break;
            case 4: passTurn(); break;
            case 5: //Abandonner partie
                break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 5\n");
        }
    }while(choix < 0 && choix > 5);
   
}

/**
 * Menu de sélection de l'unité
 * @param choice    Choix de l'action pour l'unité
 */
void unitMenu(int choice){
    char yn;
    vector movableUnits[NB_MAX_UNIT]; 

    switch(choice){
            case 1:
                    movable(movableUnits); // Fait la liste des unités pouvant se déplacer
        		    
                    printf("Se déplacer ? y/n\n");
        		    readS(&yn);
                  	
                    if(yn == 'y' || yn == 'Y') {
                       		 playMove(movableUnits);
                    }else{
                        printf("Saisie invalide\n");
                    }
                break;
            case 2:
        		    //Unités pouvant attaquer
        		    printf("Attaquer ? y/n\n");
        		    readS(&yn);
        		    
                    if(yn == 'y' || yn == 'Y') {
                        playAttack();
                    }else{
                        printf("Saisie invalide\n");
                    }
                break;
            case 3:
            //Change de direction
            break;  
        }
}


/**
 * Affiche la liste des unités inclus dans le jeu
 */
void unitList(){
    for(int i = knight; i < sizePawns; i++){
        printf("%i - %s\n", i - 1, getNameUnit(pawns[i].name));
    }
}