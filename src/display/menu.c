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
printf(
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
        printf(" 3 - Aide jeu \n");
        printf(" 4 - Quitter\n");
        printf("Votre choix : ");   
        
        choix = readLong();	// Choix = 1 si chiffre est rentré, 0 sinon
    	
        if(choix == 0) {
    		printf("Erreur : Veuillez rentrer un chiffre et non un caractère \n");
    	}

        switch(choix){
            case 1: gameInit();
                break;
            case 2: //loadGame();
                break;
            case 3: mainHelp();
                break;
            case 4: break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
        }
	
    }while(choix != 4);
    printf("A bientôt !");
    exit(1);
}

void mainHelp() {
	int choix;
	clearScreen();
	color(red,"\n Bienvenue dans l'aide de notre jeu tactics arena ! \n");
	do{
		color(green, "\n Dîtes-moi, que voulez vous savoir ? \n");
		printf( "  1 - Règles générales\n"
			"  2 - Vocabulaire\n"
			"  3 - Unités\n"
			"  4 - Capacités spéciales\n"
			"  5 - Effet de statut\n"
			"  6 - Revenir au menu principal \n\n");
		color(green, "Quel est votre choix ? : ");
		choix = readLong();
	    	
		if(choix == 0) {
	    		printf("Erreur : Veuillez rentrer un chiffre et non un caractère \n");
	    	}
		clearScreen();
		switch(choix){

				case 1 : color(cyan,"  Les conditions de victoire sont : \n");
					puts(   "    -Toutes les unités adverses sont détruites ou immobilisé\n"
						"    -L'opposant abandonne\n\n");
					color(cyan,"  Les conditions de jeu nul sont : \n");
					puts(	"    -Toutes les unités actives sont détruites ou immobilisé\n"
						"    -OU les joueurs passent leurs tours 3 fois d’affilé\n"
						"    -OU il n’y a eu aucun fight depuis les 30 derniers tours\n");
					color(yellow,"  Info : Le joueur qui commence est défini aléatoirement par le serveur au début de chaque partie\n\n");
					color(cyan,"  On peut contrôler une unité par tour pour :\n");
					puts(	"    -Se déplacer\n"
						"    -Et / ou attaquer\n"
						"    -Et / ou changer de direction\n"
						"    -Changer de direction doit être la dernière commande, si utilisé\n");
					color(red,"    Le temps limite par tour est compris entre 1 et 2 minutes, qui dépend du nombre d’unité restantes\n\n");
					color(cyan,"\n  Quand ce temps est dépassé:\n");
					puts(   "    -Finis le tour automatiquement si au moins une commande a été effectué\n"
						"    -Si aucune commande effectué, abandon automatique");
					color(red, "    -Important : on ne peut pas revenir en arrière sur une action déjà effectué\n\n"); 

				break;

				case 2 : color(cyan, "  POWER : \n");
					puts(   "    -Détermine combien de dégâts une unité peut infliger\n"
						"    -OU détermine combien de HP peut redonner un soigneur\n\n");
					color(cyan, "  ARMOR :\n");
					puts(   "    -Détermine le % de dégâts qui sera absorbé et réduit\n"
						"    -Ne réduit pas la valeur du soin ou du poison\n\n");

					color(cyan, "  MOVEMENT RANGE :\n");
					puts(   "    -Détermine le nombre maximum de cellules qu’une unité peut franchir par tour\n"
						"    -Certaines unités alliées peuvent s’écarter pour laisser passer une autre unité \n\n");

					color(cyan, "  RECOVERY TIME :\n");
					puts(   "    -Détermine le nombre de tours qu’une unité doit attendre avant d’être réutiliser\n"
						"    -Est divisé par 2 et est sous-arrondis si une unité se déplace mais n’attaque pas\n"
						"    -OU est divisé par 2 et sur-arrondis si une unité attaque mais ne se déplace pas\n"
						"    -OU est annulé si une unité change uniquement de direction\n\n");

				break;

				case 3 : helpUnit();
				break;
				
				case 4 : color(cyan, "  TELEPORTATION \n"); 
					 puts("    -Permet de ce déplacer vers une case libre sans être déranger par les obstacles ou les autres unités \n\n");

					 color(cyan, "  ATTAQUES FURTIVES\n");
					 puts("    -Ne peuvent êtres bloqués sauf par les BARRIERES \n\n");

					 color(cyan, "  SOIN\n");
					 puts("    -Restore les HP des unités\n\n");

					 color(cyan, "  FOCUS\n");
					 puts("    -Cause un effet continue tant que lanceur maintiens son sort \n"
					      "    -Est supprimé si le lanceur est attaqué ou paralisé \n"
					      "    -OU si la cible est détruite \n"
					      "    -OU si le lanceur reçoit une nouvelle instruction\n\n");

					color(cyan, "  BLOCK\n"); 
					puts("    -Rend une attaque inefficace \n"
					     "    -fixe 50% de bloquage sur les cotés \n"
					     "    -Ne peut bloquer derrière \n\n");

					color(red, "Les unités indestructibles ne peuvent être détruite ou endommagé \n\n");

					color(cyan, "  \n  Étourdissement \n");
					puts("    -Augmente d’un tour le RECOVERY TIME d’une unité\n"
					     "    -N’a aucun effet si l’attaque est BLOCK\n\n");

				break;

				case 5 : color(cyan, "  WAITING\n");
					puts("    -Indique qu’une unité est toujours en RECOVERY TIME et ne peut être commandé ce tour\n\n");

					color(cyan, "  BARRIER\n");
					puts("    -BLOCK toutes les attaques non-FOCUS et sorts de soin\n"
					     "    -Est perdu si vous bougez, attaquez ou changez de direction\n"
					     "    -Les unités sous l’effet BARRIER ne peuvent s’écarter pour laisser passer les unités alliées\n\n");

					color(cyan, "  FOCUS\n");
					puts("    -Les unités sous FOCUS ne peuvent bloquer\n"
					     "    -Les unités sous l’effet FOCUS ne peuvent s’écarter pour laisser passer les unités\n\n");

					color(cyan, "  PARALYSE\n");
					puts("    -Ne peuvent être commandé\n"
					     "    -Ne peuvent pas bloquer\n"
					     "    -Ne peuvent s’écarter pour laisser passer les unités\n\n");

					color(cyan, "  BONUS de PUISSANCE\n");
					puts("    -Augmente ou Diminue la PUISSANCE temporairement\n"
					     "    -Ne peut réduire la PUISSANCE sous 0\n"
					     "    -N’a aucun effet sur les unité qui n’attaquent pas ou sur les soigneurs\n\n");

					color(cyan, "  BONUS D’ARMURE\n");
					puts("    -Augmente ou Diminue l’ARMURE temporairement\n"
					     "    -Ne peut réduire l’ARMURE sous 0\n"
					     "    -Ne peut augmenté l’ARMURE au dessus de 100\n\n");

					color(cyan, "  POISON\n");
					puts("    -Ne peut ATTAQUER\n"
					     "    -ET ne peut s’écarter pour laisser le passage au unités allier\n"
					     "    -ET pert 4 HP à char TOURS\n");

					color(red, "Tout les Effets de Statuts peuvent se cumuler !\n\n");


		
		}
	}while(choix != 6);
}



void helpUnit() {
	int choix;
	color(green, "Veuillez choisir une unité dont vous voulez connaître des informations : \n");
	printf( "1 - Knight\n"
		"2 - Scout\n"
		"3 - Assassin\n"
		"4 - Cleric\n"
		"5 - Pyromancer\n"
		"6 - Enchantress\n"
		"7 - Dragonborn\n"
		"8 - Dark Witch\n"
		"9 - Lightning Totem\n"
		"10 - Barrier Totem\n"
		"11 - Mud Golem\n"
		"12 - Golem Ambusher\n"
		"13 - Frost Golem\n"
		"14 - Stone Golem\n"
		"15 - Dragon Tyrant\n"
		"16 - Berserker\n"
		"17 - Beast Rider\n"
		"18 - Poison Wisp\n"
		"19 - Furgon\n"
		"20 - Retour menu principal\n\n");
	color(green, "Quel est votre choix ? : ");
	choix = readLong();
    	
        if(choix == 0) {
    		printf("Erreur : Veuillez rentrer un chiffre et non un caractère \n");
    	}
	switch(choix){

		case 1 : puts("\nCaractéristiques du Knight : \n"
			 	"HP : 50\n"
				"Power : 22\n" 
				"Armor : 25%\n"
				"Blocking : 80% Devant 40% Côté\n"
				"Recovery : 1\n"
				"Movement : 3\n"
				"Information(s) supplémentaire(s) : Pas plus de 3 Knight sur le champ de bataille.");
		break;

		case 2 : puts("\nCaractéristiques du Scout : \n"
			 	"HP : 40\n"
				"Power : 18\n" 
				"Armor : 8%\n"
				"Blocking : 60% Devant 30% Côté\n"
				"Recovery : 2\n"
				"Movement : 4\n"
				"Information(s) supplémentaire(s) : Pas plus de 2 Scout sur le champ de bataille.");
		break;

		case 3 : puts("\nCaractéristiques de l'Assassin : \n"
			 	"HP : 35\n"
				"Power : 18\n" 
				"Armor : 12%\n"
				"Blocking : 70% Devant 35% Côté\n"
				"Recovery : 1\n"
				"Movement : 4\n"
				"Information(s) supplémentaire(s) : Quand l'assassin possède moins de 5 HP, il peut faire le kamikaze");
		break;

		case 3 : puts("\nCaractéristiques du Cleric : \n"
			 	"HP : 24\n"
				"Power : 12 de soin\n" 
				"Armor : Aucune\n"
				"Blocking : Aucun\n"
				"Recovery : 5\n"
				"Movement : 3\n"
				"Information(s) supplémentaire(s) : Soigne tout les alliés. Le sort de soin ne peut être bloqué sauf par les barrières.");
		break;



	}

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
