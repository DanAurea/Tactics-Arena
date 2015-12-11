#include <stdio.h>
#include <ctype.h>
#include "../include/gameEngine.h"
#include "../include/menu.h"
#include "../include/grid.h"
#include "../include/terminal.h"
#include "../include/manageString.h"

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
            case 3: //gameMenu(noPlayer);
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
 * @param shortPlayer    Joueur en cours
 */
void gameMenu(short noPlayer){
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

            case 1: //unitMenu(1, noPlayer); 
break;
            case 2: //unitMenu(2, noPlayer); 
break;
            case 3: //unitMenu(3, noPlayer);
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
 * @param choice    Choix de l'action pour l'unité
 * @param noPlayer  Joueur en cours
 */
void unitMenu(int choice, short noPlayer){
    char yn;
    //vector movableUnits[]; 
    //vector attackableUnits[];

    switch(choice){
            case 1:
                    //Unités pouvant se déplacer
        		    printf("Se déplacer ? y/n");
        		    read(&yn);
                  	
                    if(yn == 'y' || yn == 'Y') {
                       		 //Déplace
                    }else{
                        printf("Saisie invalide");
                    }
                break;
            case 2:
        		    //Unités pouvant attaquer
        		    printf("Attaquer ? y/n");
        		    read(&yn);
        		    
                    if(yn == 'y' || yn == 'Y') {
        		        //Attaque
                    }else{
                        printf("Saisie invalide");
                    }
                break;
            case 3:
            //Change de direction
            break;  
        }
    clearScreen();
    gridDisp();
    gameMenu(noPlayer);
}


/**
 * Affiche la liste des unités inclus dans le jeu
 */
void unitList(){
    for(int i = knight; i < sizePawns; i++){
        printf("%i - %s\n", i - 1, getNameUnit(pawns[i].name));
    }
}