/**
 @file manageString.c
 @brief Gestions des chaînes de caractères
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <ctype.h>
#include <stdio.h>
#include "../../include/game/engine.h"

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
    
    partName = malloc(3 * sizeof(char));
    
    if(partName == NULL){
        free(partName);
        return "Error when allocating memory !";
    }else{
        if(strcmp(name, "Dragonborn") == 0){
            strcpy(partName, "Db");
        }
        else if(strcmp(name, "Empty") == 0){
            strcpy(partName, "  ");
        }
        else if(strcmp(name, "Decors") == 0){
            strcpy(partName, "xx");
        }
        else if(strcmp(name, "Dark Witch") == 0){
            strcpy(partName, "Dw");
        }
        else if(strcmp(name, "Dragon Tyrant") == 0){
            strcpy(partName, "Dt");
        }
        else if(strcmp(name, "Beast Rider") == 0){
            strcpy(partName, "Br");
        }
        else if(strcmp(name, "Berserker") == 0){
            strcpy(partName, "Bk");
        }
        else if(strcmp(name, "Lightning Totem") == 0){
            strcpy(partName, "Lt");
        }
        else if(strcmp(name, "Barrier Totem") == 0){
            strcpy(partName, "Bt");
        }
        else if(strcmp(name, "Mud Golem") == 0){
            strcpy(partName, "Mg");
        }
        else if(strcmp(name, "Golem Ambusher") == 0){
            strcpy(partName, "Ga");
        }
        else if(strcmp(name, "Frost Golem") == 0){
            strcpy(partName, "Fg");
        }
        else if(strcmp(name, "Stone Golem") == 0){
            strcpy(partName, "Sg");
        }
        else if(strcmp(name, "Poison Wisp") == 0){
            strcpy(partName, "Pw");
        }
        else{
            partName[0] = name[0];
            partName[1] = name[1];
            partName[2] = '\0';
        }
        
        return partName;
    }
}

/**
 * Récupère l'entier de l'unité par rapport à son nom
 * @param  name Nom de l'unité
 * @return      Retourne l'entier correspondant sinon -1
 */
int getNumber(char name[]){

    if(strcmp(name, "Empty" )                == 0) return empty;
    else if(strcmp(name, "Decors" )          == 0) return decors; 
    else if(strcmp(name, "Knight")           == 0) return knight;
    else if(strcmp(name, "Scout")            == 0) return scout;
    else if(strcmp(name, "Assassin" )        == 0) return assassin;
    else if(strcmp(name, "Cleric" )          == 0) return cleric;
    else if(strcmp(name, "Pyromancer" )      == 0) return pyromancer;
    else if(strcmp(name, "Enchantress" )     == 0) return enchantress;
    else if(strcmp(name, "Dragonborn" )      == 0) return dragonborn;
    else if(strcmp(name, "Dark Witch" )      == 0) return darkWitch;
    else if(strcmp(name, "Lightning Totem" ) == 0) return lightningTotem;
    else if(strcmp(name, "Barrier Totem" )   == 0) return barrierTotem;
    else if(strcmp(name, "Mud Golem")        == 0) return mudGolem;
    else if(strcmp(name, "Golem Ambusher" )  == 0) return golemAmbusher;
    else if(strcmp(name, "Frost Golem" )     == 0) return frostGolem;
    else if(strcmp(name, "Stone Golem" )     == 0) return stoneGolem;
    else if(strcmp(name, "Dragon Tyrant" )   == 0) return dragonTyrant;
    else if(strcmp(name, "Berserker" )       == 0) return berserker;
    else if(strcmp(name, "Beast Rider" )     == 0) return beastRider;
    else if(strcmp(name, "Poison Wisp" )     == 0) return poisonWisp;
    else if(strcmp(name, "Furgon" )          == 0) return furgon;

    return -1;
}

/**
 * Récupère le nom de l'unité à partir de la liste énumérée
 * @param  name Nom de l'unité provenant de la liste énumérée
 * @return      Nom de l'unité sous forme de chaîne    
 */
char* getNameUnit(unitName name){    
  
    if(name == empty) return "Empty";
    else if(name == decors) return "Decors"; 
    else if(name == knight) return "Knight";
    else if(name == scout) return "Scout";
    else if(name == assassin) return "Assassin";
    else if(name == cleric) return "Cleric";
    else if(name == pyromancer) return "Pyromancer";
    else if(name == enchantress) return "Enchantress";
    else if(name == dragonborn) return "Dragonborn";
    else if(name == darkWitch) return "Dark Witch";
    else if(name == lightningTotem) return "Lightning Totem";
    else if(name == barrierTotem) return "Barrier Totem";
    else if(name == mudGolem) return "Mud Golem";
    else if(name == golemAmbusher) return "Golem Ambusher";
    else if(name == frostGolem) return "Frost Golem";
    else if(name == stoneGolem) return "Stone Golem";
    else if(name == dragonTyrant) return "Dragon Tyrant";
    else if(name == berserker) return "Berserker";
    else if(name == beastRider) return "Beast Rider";
    else if(name == poisonWisp) return "Poison Wisp";
    else if(name == furgon) return "Furgon";
    return "Blank";
}

/**
 * Récupère le nom de l'effet à partir de la liste énumérée
 * @param  effect Effet provenant de la liste énumérée
 * @return        Nom de l'effet sous forme de chaîne de caractère
 */
char* getNameEffect(unitEffect effect){    
    if(effect      == POWER_BONUS) return "Bonus de puissance";
    else if(effect == ARMOR_BONUS) return "Bonus d'armure";
    else if(effect == BARRIER) return "Barrière";
    else if(effect == POISON) return "Poison";
    else if(effect == PARALYSE) return "Paralysé";
    else if(effect == FOCUS) return "Focus";
    return "None";
}

/**
 * Retourne la direction 
 * @param  direct Direction de l'unité
 * @return        Retourne La direction sous forme de chaîne
 */
char* getDirectionUnit(cardinal direct){
    if(direct == north) return "Nord";
    else if(direct == east) return "Est";
    else if(direct == south) return "Sud";
    return "Ouest";
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
    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Lit la chaîne de caractère passée en paramètre et vérifie
 * qu'elle ne soit pas trop longue
 * @param  string Chaîne de caractère à vérifier
 * @return        Retourne 1 si chaîne correcte
 */
int readS(char * string)
{
    char *enter = NULL;

    if (fgets(string, sizeof(string), stdin) != NULL){
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

/**
 * Lit un long de manière sécurisée
 * @return Retourne le long saisie ou 0 en cas d'erreur
 */
long readLong(){
    char nbString[100] = {0};

    if(readS(nbString)){
        return strtol(nbString, NULL, 10);
    }else{
        return 0;
    }
}

/**
 * Lit un double de manière sécurisée
 * @return Retourne le double saisie ou 0.0 en cas d'erreur
 */
double readDouble(){
    char nbString[100] = {0};

    if(readS(nbString)){
        return strtod(nbString, NULL);
    }else{
        return 0.0;
    }
}