#include <stdio.h>
#include <ctype.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/listes.h"
#include "../../include/game/turn.h"
#include "../../include/display/menu.h"
#include "../../include/display/grid.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"
#include "../../include/controller/saveNLoad.h"

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
    color(red, "\nBienvenue sur le jeu Tactics arena SPI deluxe edition \n"); // Change la couleur des caractères suivants en rouge
    color(cyan, "Pour une meilleure immersion, veuillez mettre la console en fullscreen, svp\n");
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
            case 1: gameInit(); break;
            case 2: load(); break;
            case 3: mainHelp(); break;
            case 4: clearScreen(); break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 4\n");
        }

    }while(choix != 4);
    printf("A bientôt ! Hope you enjoy this game ! \n");

    exit(1);
}


/**
* Menu d'aide principal
*/
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
					puts(   "    -Toutes les unités adverses sont détruites ou immobilisées\n"
						"    -L'opposant abandonne\n\n");
					color(cyan,"  Les conditions de jeu nul sont : \n");
					puts(	"    -Toutes les unités actives sont détruites ou immobilisées\n"
						"    -OU les joueurs passent leurs tours 3 fois d’affilé\n"
						"    -OU il n’y a eu aucun fight depuis les 30 derniers tours\n");
					color(yellow,"  Info : Le joueur qui commence est défini aléatoirement par le serveur au début de chaque partie\n\n");
					color(cyan,"  On peut contrôler une unité par tour pour :\n");
					puts(	"    -Se déplacer\n"
						"    -Et / ou attaquer\n"
						"    -Et / ou changer de direction\n"
						"    -Changer de direction doit être la dernière commande, si utilisée\n");
					color(red,"  Le temps limite par tour est compris entre 1 et 2 minutes, qui dépend du nombre d’unité restantes\n\n");
					color(cyan,"\n  Quand ce temps est dépassé:\n");
					
					puts(   "    -Finis le tour automatiquement si au moins une commande a été effectuée\n"
						"    -Si aucune commande effectuée, abandon automatique");
					color(red, "    -Important : on ne peut pas revenir en arrière sur une action déjà effectuée\n\n"); 

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
					puts(   "    -Détermine le nombre de tours qu’une unité doit attendre avant d’être réutilisée\n"
						"    -Est divisé par 2 et est sous-arrondis si une unité se déplace mais n’attaque pas\n"
						"    -OU est divisé par 2 et sur-arrondis si une unité attaque mais ne se déplace pas\n"
						"    -OU est annulé si une unité change uniquement de direction\n\n");

				break;

				case 3 : helpUnit();
				break;
				
				case 4 : color(cyan, "  TELEPORTATION \n"); 
					 puts("    -Permet de se déplacer vers une case libre sans être dérangé par les obstacles ou les autres unités \n\n");

					 color(cyan, "  ATTAQUES FURTIVES\n");
					 puts("    -Ne peuvent êtres bloqués sauf par les BARRIERES \n\n");

					 color(cyan, "  SOIN\n");
					 puts("    -Restore les HP des unités\n\n");

					 color(cyan, "  FOCUS\n");
					 puts("    -Cause un effet continue tant que lanceur maintient son sort \n"
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
					puts("    -Ne peut attaquer\n"
					     "    -ET ne peut s’écarter pour laisser le passage aux unités alliées\n"
					     "    -ET perd 4 HP à chaque tours\n");

					color(red, "Tout les Effets de Statuts peuvent se cumuler !\n\n");
					break;

				case 6 : mainMenu(); break;


		}
	}while(choix != 6);
}

/**
* Menu d'aide spéifique aux unités
*/

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
		"20 - Retour menu principal\n");

	do{
		
		color(green, "\nQuel est votre choix ? (20 pour menu principal, 21 pour afficher de nouveau le menu unité) : ");

		choix = readLong();

		if(choix == 0) {
	    		printf("Erreur : Veuillez rentrer un chiffre et non un caractère \n");
	    	}
		clearScreen();
		switch(choix){

			case 1 : color(cyan,"\n Caractéristiques du Knight : \n");
				 puts(  "  -HP : 50\n"
					"  -Power : 22\n"
					"  -Armor : 25%\n"
					"  -Blocking : 80% Devant 40% Côté\n"
					"  -Recovery : 1\n"
					"  -Movement : 3\n"
					"  -Information(s) supplémentaire(s) : Pas plus de 3 Knight sur le champ de bataille");
			break;

			case 2 : color(cyan,"\n Caractéristiques du Scout : \n");
				 puts(	"  -HP : 40\n"
					"  -Power : 18\n"
					"  -Armor : 8%\n"
					"  -Blocking : 60% Devant 30% Côté\n"
					"  -Recovery : 2\n"
					"  -Movement : 4\n"
					"  -Information(s) supplémentaire(s) : Pas plus de 2 Scout sur le champ de bataille");
			break;

			case 3 : color(cyan,"\n Caractéristiques de l'Assassin : \n");
				 puts(	"  -HP : 35\n"
					"  -Power : 18\n"
					"  -Armor : 12%\n"
					"  -Blocking : 70% Devant 35% Côté\n"
					"  -Recovery : 1\n"
					"  -Movement : 4\n"
					"  -Information(s) supplémentaire(s) : Quand l'assassin possède moins de 5 HP, il peut faire le kamikaze");
			break;

			case 4 : color(cyan,"\n Caractéristiques du Cleric : \n");
				 puts(	"  -HP : 24\n"
					"  -Power : 12 de soin\n"
					"  -Armor : Aucune\n"
					"  -Blocking : Aucun\n"
					"  -Recovery : 5\n"
					"  -Movement : 3\n"
					"  -Information(s) supplémentaire(s) : Soigne tout les alliés. Le sort de soin ne peut être bloqué sauf par les barrières");
			break;

			case 5 : color(cyan,"\n Caractéristiques du Pyromancer : \n");
				 puts(	"  -HP : 30\n"
					"  -Power : 15 Imblocable\n"
					"  -Armor : Aucune\n"
					"  -Blocking : 33% Devant 16% Côté\n"
					"  -Recovery : 3\n"
					"  -Movement : 3\n"
					"  -Information(s) supplémentaire(s) : Son sort ne peut être bloqué, excepté pas les barrières");
			break;

			case 6 : color(cyan,"\n Caractéristiques de l'Enchantress : \n");
				 puts(	"  -HP : 35\n"
					"  -Power : Sort de paralysie\n"
					"  -Armor : Aucune\n"
					"  -Blocking : Aucun\n"
					"  -Recovery : 3\n"
					"  -Movement : 3\n"
					"  -Information(s) supplémentaire(s) : Sort de paralysie maintenu tant que le Focus est maintenu");
			break;

			case 7 : color(cyan,"\n Caractéristiques du Dragonborn : \n");
				 puts(	"  -HP : 30\n"
					"  -Power : 15 Imblocable\n"
					"  -Armor : Aucune\n"
					"  -Blocking : 33% Devant 16% Côté\n"
					"  -Recovery : 3\n"
					"  -Movement : 3 TP\n"
					"  -Information(s) supplémentaire(s) : Draîne 12 Power d'un dragon vers chaque Pyromancer ou mage sous votre contrôle");
			break;

			case 8 : color(cyan,"\n Caractéristiques de la Dark Witch : \n");
				 puts(	"  -HP : 28\n"
					"  -Power : 24 Imblocable\n"
					"  -Armor : Aucune\n"
					"  -Blocking : 20% Devant 10% Côté\n"
					"  -Recovery : 3\n"
					"  -Movement : 3\n"
					"  -Information(s) supplémentaire(s) : Son sort ne peut être bloqué, excepté pas les barrières");
			break;

			case 9 : color(cyan,"\n Caractéristiques du Lightning Totem : \n");
				 puts(	"  -HP : 56\n"
					"  -Power : 30 Imblocable\n"
					"  -Armor : 18%\n"
					"  -Blocking : 100% Partout\n"
					"  -Recovery : 4\n"
					"  -Movement : Immobile\n"
					"  -Information(s) supplémentaire(s) : Pas plus de 1 Lightning Totem sur le champ de bataille. Il n'est pas nécessaire de détruire cette unité pour gagner");
			break;

			case 10 : color(cyan,"\n Caractéristiques du Barrier Totem : \n");
				  puts(	"  -HP : 32\n"
					"  -Power : Barrière\n"
					"  -Armor : Aucune\n"
					"  -Blocking : 100% Partout\n"
					"  -Recovery : 2\n"
					"  -Movement : Immobile\n"
					"  -Information(s) supplémentaire(s) : Il n'est pas nécessaire de détruire cette unité pour gagner");
			break;

			case 11 : color(cyan,"\n Caractéristiques du Mud Golem : \n");
				  puts(	"  -HP : 60\n"
					"  -Power : 20\n"
					"  -Armor : Aucune\n"
					"  -Blocking : Aucun\n"
					"  -Recovery : 2\n"
					"  -Movement : 5 TP\n");
			break;

			case 12 : color(cyan,"\n Caractéristiques du Golem Ambusher : \n");
				  puts(	"  -HP : 60\n"
					"  -Power : 20\n"
					"  -Armor : Aucune\n"
					"  -Blocking : Aucun\n"
					"  -Recovery : 3\n"
					"  -Movement : 2\n"
					"  -Information(s) supplémentaire(s) : Pas plus de 1 Golem Ambusher sur le champ de bataille");
			break;

			case 13 : color(cyan,"\n Caractéristiques du Frost Golem : \n");
				  puts(	"  -HP : 60\n"
					"  -Power : Paralyse\n"
					"  -Armor : Aucune\n"
					"  -Blocking : Aucun\n"
					"  -Recovery : 2\n"
					"  -Movement : 2\n"
					"  -Information(s) supplémentaire(s) : Paralysie maintenu tant que le Focus est maintenu");
			break;

			case 14 : color(cyan,"\n Caractéristiques du Stone Golem : \n");
				  puts(	"  -HP : 60\n"
					"  -Power : +30% Armor\n"
					"  -Armor : 30%\n"
					"  -Blocking : Aucun\n"
					"  -Recovery : 4\n"
					"  -Movement : 2\n"
					"  -Information(s) supplémentaire(s) : Buff d'armure maintenu tant que le Focus est maintenu. Pas plus de 2 Stone Golem sur le champ de bataille");
			break;

			case 15 : color(cyan,"\n Caractéristiques du Dragon Tyrant : \n");
				  puts(	"  -HP : 68\n"
					"  -Power : 28\n"
					"  -Armor : 16%\n"
					"  -Blocking : 40% Devant 20% Côtés\n"
					"  -Recovery : 3\n"
					"  -Movement : 4 TP\n"
					"  -Information(s) supplémentaire(s) : Ne laisse pas ses alliés passer à travers lui. Compte comme 2 unités sur le champ de bataille. Pas plus de 1 Dragon Tyrant sur le champ de bataille ");
			break;

			case 16 : color(cyan,"\n Caractéristiques du Berserker : \n");
				  puts(	"  -HP : 42\n"
					"  -Power : 22 + Etourdissement\n"
					"  -Armor : Aucune\n"
					"  -Blocking : 25% Devant 12% Côtés\n"
					"  -Recovery : 1\n"
					"  -Movement : 3\n"
					"  -Information(s) supplémentaire(s) : Ne laisse pas ses alliés passer à travers lui");
			break;

			case 17 : color(cyan,"\n Caractéristiques du Beast Rider : \n");
				  puts(	"  -HP : 38\n"
					"  -Power : 19\n"
					"  -Armor : 15%\n"
					"  -Blocking : 45% Devant 22% Côtés\n"
					"  -Recovery : 1\n"
					"  -Movement : 4\n"
					"  -Information(s) supplémentaire(s) : Ne laisse pas ses alliés passer à travers lui");
			break;

			case 18 : color(cyan,"\n Caractéristiques du Beast Rider : \n");
				  puts(	"  -HP : 34\n"
					"  -Power : Poison\n"
					"  -Armor : Aucune\n"
					"  -Blocking : Aucun\n"
					"  -Recovery : 2\n"
					"  -Movement : 6 TP\n");
			break;

			case 19 : color(cyan,"\n Caractéristiques du Furgon : \n");
				  puts(	"  -HP : 48\n"
					"  -Power : Invocation\n"
					"  -Armor : Aucune\n"
					"  -Blocking : 50% Devant 25% Côtés\n"
					"  -Recovery : 1\n"
					"  -Movement : 3\n"
					"  -Information(s) supplémentaire(s) : Les unités invoqués ne peuvent être placé que sur des cases vides, sont détruites dès qu'elles sont attaqués, ne peuvent être la cible d'un sort de soin ou de focus. Pas plus de 1 Dragon Tyrant sur le champ de bataille");
			break;

			case 20 : mainHelp(); break;
			case 21 : helpUnit(); break;
		}
	}while(choix != 20 || choix != 21);



}

/**
 * Afficher les directions
 */
void dispDirection(){
    printf("\nDirection :\n");

	printf(" 1 - Nord\n");
    printf(" 2 - Est\n");
    printf(" 3 - Sud\n");
    printf(" 4 - Ouest\n");
}

/**
 * Menu du joueur lors de la partie
 */
void gameMenu(){
    int choix;

    if(noPlayer == FIRST_PLAYER) fontColor(red);
    else fontColor(blue);

    printf("\nJoueur no %i à vous de jouer !\n", noPlayer + 1);
    reinitColor();

    do{
        printf("\nMenu :\n");
        printf(" 1 - Unités pouvant se déplacer\n");
        printf(" 2 - Unités pouvant attaquer\n");
        printf(" 3 - Changer de direction\n");
        printf(" 4 - Passer tour\n");
		printf(" 5 - Sauvegarder\n");
        printf(" 6 - Abandonner la partie\n");

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
            case 5: save(); 
            		clearScreen();
            		gridDisp();
            		break;
            case 6: surrender(); break;
            default: printf("Erreur: votre choix doit etre compris entre 1 et 5\n");
        }
    }while(choix < 0 || choix > 6);
}

/**
 * Menu de sélection de l'unité
 * @param choice    Choix de l'action pour l'unité
 */
void unitMenu(int choice){
    char yn[2];

    printf("\n");
    switch(choice){
            case 1:

            		clearScreen(); // Met à jour l'affichage pour le tour
					gridDisp();
            		if(!hasAttacked && !hasMoved){
            			movable(white); // Fait la liste des unités pouvant se déplacer

	                    clearScreen(); // Met à jours les couleurs des unités déplaçables
						gridDisp();
	                    
	                    printf("\nSe déplacer ? y/n\n");
	        		    readS(yn);
	                  	printf("\n");

	                    if(strcmp(yn,"y") == 0 || strcmp(yn,"Y") == 0) {
	                    	playMove();
	                    }else if(strcmp(yn,"n") != 0 || strcmp(yn,"N") != 0){
                        	printf("Saisie invalide\n");
                    	}

                    	movable(black);
            		}else if(hasAttacked){
            			color(red, "Vous ne pouvez pas déplacer votre unité après avoir attaqué !\n");
            		}else{
            			color(red, "Vous ne pouvez pas déplacer une unité à nouveau !\n");
            		}

                break;
            case 2:

            		clearScreen(); // Met à jour l'affichage pour le tour
					gridDisp();
        		    if(!hasAttacked){
        		    	attackable(white); // Attaquants en blanc
	        		    
        		    	clearScreen(); // Met à jours les couleurs des unités pouvant attaquer
						gridDisp();

	        		    printf("\nAttaquer ? y/n\n");
	        		    readS(yn);
	        		    printf("\n");

	                    if(strcmp(yn,"y") == 0 || strcmp(yn,"Y") == 0) {
	                        playAttack();
	                    }else if(strcmp(yn,"n") != 0 || strcmp(yn,"N") != 0){
	                        printf("Saisie invalide\n");
	                    }

	                    attackable(black); // Attaquants en noir
                	}else{
                		color(red, "Vous ne pouvez pas réattaquer !\n");
                	}
                break;
            case 3:
            	movable(white);

            	clearScreen();
				gridDisp();
            	
            	changeDirection();
            	movable(black);
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