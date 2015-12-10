#include <ctype.h>
#include <stdio.h>
#include "../include/gameEngine.h"

/**
*   Récupère les coordonnées d'une chaîne de caractère sous
*	forme de vecteur x et y
*   @param coordString Coordonnées saisie par l'utilisateur
*   @param coordUnit Coordonnées de l'unité récupérées de la saisie utilisateur
*/
void getCoordS(char coordString[], vector * coordUnit){
	int sizeS = strlen(coordString);
	int iCount = 0;
	char iString[3];
	
	for(int i = 0; i < sizeS; i++){

		if(coordString[i] >= 'a' && coordString[i] <= 'z' ){
			coordUnit->x = coordString[i] - 'a';
		}else if(coordString[i] >= 'A' && coordString[i] <= 'Z' ){
			coordUnit->x = coordString[i] - 'A';	
		}else{
				if(isdigit(coordString[i])){
					iString[iCount] = coordString[i]; // Récupère l'entier sous forme de chaîne de caractère
					iCount++;
					iString[iCount] = '\0';
				}
		}
	}
    coordUnit->y = atoi(iString)-1;

}

/**
 *  Récupère 2 caractères du nom de l'unité
 *  @param name Nom de l'unité
 *  @return Retourne 2 caractères liés au nom de l'unité
 */
char* get2Char(char name[]){
    char* partName = NULL;
    
    
    if(strcmp(name, "Dragonborn") == 0){
        return "Db";
    }
     if(strcmp(name, "Dark Witch") == 0){
        return "Dw";
    }
    else if(strcmp(name, "Dragon Tyrant") == 0){
        return "Dt";
    }
    else if(strcmp(name, "Beast Rider") == 0){
        return "Br";
    }
    else if(strcmp(name, "Berserker") == 0){
        return "Bk";
    }
    else if(strcmp(name, "Lightning Totem") == 0){
        return "Lt";
    }
    else if(strcmp(name, "Barrier Totem") == 0){
        return "Bt";
    }
    else if(strcmp(name, "Mud Golem") == 0){
        return "Mg";
    }
    else if(strcmp(name, "Golem Ambusher") == 0){
        return "Ag";
    }
    else if(strcmp(name, "Frost Golem") == 0){
        return "Fg";
    }
    else if(strcmp(name, "Stone Golem") == 0){
        return "Sg";
    }
    else if(strcmp(name, "Poison Wisp") == 0){
        return "Pw";
    }
    else{
        if(strlen(name) >= 2){
            partName[0] = name[0];
            partName[1] = name[1];
            partName[2] = '\0';
        }else{
            strcpy(partName, "  ");
        }
    }
    
    return partName;
}

/**
 * Vérifie que les coordonnées sont dans la grille
 * @param  coordString Coordonnées sous forme de chaîne
 * @return             Retourne false si pas en dehors
 */
bool isOutGrid(char * coordString){
    int sizeS = strlen(coordString);
    char iString[3];
    int countNumbers = 0;

    for(int i = 0; i < sizeS; i++){
        if((coordString[i] > 'A' + N -1 && coordString[i] < 'a') || coordString[i] > 'a' + N -1) return true; // Débordement lignes

        if(isdigit(coordString[i])){
            iString[countNumbers] = coordString[i]; // Forme l'entier
            countNumbers++;
            iString[countNumbers] = '\0';
        }
    }
    if(atoi(iString) < 1 || atoi(iString) > N) return true; // Débordements colonnes

    return false;
}

/**
 * Sélectionne une coordonnée et vérifie son format
 * @param coordString Chaîne de caractère à vérifier
 * @return Vraie si les coordonnées saisies sont correctes
 */
bool correctCoord(char * coordString){

    if( (coordString[0] >= 'a' && coordString[0] <= 'z') || (coordString[0] >= 'A' && coordString[0] <= 'Z')){
        
        if(coordString[1] != ' '){
            return false;
        }

        if( ((coordString[2] >= '9' && coordString[2] <= '0') || (coordString[3] >= '9' && coordString[3] <= '0')) && coordString[4] != '\n'){
            return false;    
        }

        if( ((coordString[1] >= '9' && coordString[1] <= '0') || (coordString[2] >= '9' && coordString[2] <= '0')) && coordString[3] != '\n'){
            return false;
        }
    }

    return !isOutGrid(coordString); // Retourne vrai si pas en dehors de la grille
}

/**
 * Vérifie que l'unité est du bon côté
 * @param  coordString Coordonnées sous forme de chaîne
 * @param  noPlayer    Joueur en cours
 * @return             Retourne vrai si du bon côté 
 */
bool rightSide(char * coordString, short noPlayer){
    int sizeS = strlen(coordString);

    for(int i = 0; i < sizeS; i++){
        if(isalpha(coordString[i])){ // Test sur la ligne de l'unité
            
            if(noPlayer == FIRST_PLAYER){ // Délimite le camp du joueur 1
                printf("%i", N - NB_LINES);
                //if((coordString[i] >= 'a' && coordString[i] < 'a' + N - NB_LINES) || coordString[i] < ('A' + N - NB_LINES)) return false;
            }
            
            if(noPlayer == FIRST_PLAYER + 1){ // Délimite le camp du joueur 2
                if((coordString[i] < 'a' && coordString[i] >= 'A' + NB_LINES) || coordString[i] >= 'a' + NB_LINES) return false;
            }
        }
    }

    return true;
}

/**
 * Récupère le nom de l'unité à partir de la liste énumérée
 * @param  unit Nom de l'unité provenant de la liste énumérée
 * @return      Nom de l'unité sous forme de chaîne    
 */
char* getNameUnit(unitName unit){    
    switch(unit){
        case 0: return "Em"; break;
        case 1: return "Dc"; break;
        case 2: return "Knight"; break;
        case 3: return "Scout"; break;
        case 4: return "Assassin"; break;
        case 5: return "Cleric"; break;
        case 6: return "Pyromancer"; break;
        case 7: return "Enchantress"; break;
        case 8: return "Dragonborn"; break;
        case 9: return "Dark Witch"; break;
        case 10: return "Lightning Totem"; break;
        case 11: return "Barrier Totem"; break;
        case 12: return "Mud Golem"; break;
        case 13: return "Golem Ambusher"; break;
        case 14: return "Frost Golem"; break;
        case 15: return "Stone Golem"; break;
        case 16: return "Dragon Tyrant"; break;
        case 17: return "Berserker"; break;
        case 18: return "Beast Rider"; break;
        case 19: return "Poison Wisp"; break;
        case 20: return "Furgon"; break;
    }
    return "";
}

/**
 * Affiche le nom de l'unité
 * @param unit Nom de l'unité provenant de la liste énumérée
 */
void printNameUnit(unitName unit){
    printf("%s", getNameUnit(unit));
}

/**
 * Vide le tampon mémoire
 */
void clearBuffer()
{
    short c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}

/**
 * Lit la chaîne de caractère passée en paramètre et vérifie
 * qu'elle ne soit pas trop longue
 * @param  string Chaîne de caractère à vérifier
 * @param  length Taille désirée
 * @return        Retourne 1 si chaîne correcte
 */
int read(char * string, short length)
{
    char *enter = NULL;

    if (fgets(string, length, stdin) != NULL){
        enter = strchr(string, '\n');
        
        if (enter != NULL){
            *enter = '\0';
        }
        else{
            clearBuffer();
        }

        return 1;
    }
    else{
        clearBuffer();
        return 0;
    }
}