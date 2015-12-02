#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/gameEngine.h"

/**
 * Convertis un entier en chaîne de caractère (maximum 2 chiffres)
 * @param  n Entier à convertir
 * @return   Retourne la chaîne de caractère contenant l'entier convertis
 */
char* nToS(int n) {
    char* nString = NULL;
    
    nString = malloc(3 * sizeof(char)); // Crée une zone mémoire contenant le nombre sous forme de chaîne
    
    if(n < 10){
    	nString[0] = n + 48; // Conversion sur entier d'un chiffre
    	nString[1] = '\0';
    }else{
    	nString[0] = (n / 10) + 48; // Conversion sur entier de deux chiffres
    	nString[1] = (n % 10) + 48;
    	nString[2] = '\0';
    }
    
    return nString;
}

/**
*	Récupère les coordonnées d'une chaîne de caractère sous
*	forme de vecteur x et y
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
				coordUnit->y = atoi(iString);
		}
	}
}

/**
 *  Récupère 2 caractères du nom de l'unité
 *  @param name Nom de l'unité
 *  @return Retourne 2 caractères liés au nom de l'unité
 */
char* get2Char(char name[]){
    char* partName = NULL;
    
    partName = malloc(3 * sizeof(char));
    
    if(strcmp(name, "Dragonborn") == 0){
        strcpy(partName, "Db");
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
        strcpy(partName, "Ag");
    }
    else if(strcmp(name, "Frost Golem") == 0){
        strcpy(partName, "Fg");
    }
    else if(strcmp(name, "Stun Golem") == 0){
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
