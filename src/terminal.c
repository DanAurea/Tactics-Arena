#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/terminal.h"

/**
 * Récupère le code correspondant à la couleur
 * @param  color Couleur demandée
 * @return       Code correspondant, écran blanc si code incorrect
 */
char * getColor(int color){
	char * colorToUse = NULL;

	colorToUse = malloc(2 * sizeof(char));

	if(color == fblack) return strcpy(colorToUse, "30"); // Font color
	if(color == fred) return strcpy(colorToUse, "31");
	if(color == fgreen) return strcpy(colorToUse, "32");
	if(color == fyellow) return strcpy(colorToUse, "33");
	if(color == fblue) return strcpy(colorToUse, "34");
	if(color == fmagenta) return strcpy(colorToUse, "35");
	if(color == fcyan) return strcpy(colorToUse, "36");
	if(color == fwhite) return strcpy(colorToUse, "37");

	if(color == sblack) return strcpy(colorToUse, "40"); // Screen color
	if(color == sred) return strcpy(colorToUse, "41");
	if(color == sgreen) return strcpy(colorToUse, "42");
	if(color == syellow) return strcpy(colorToUse, "43");
	if(color == sblue) return strcpy(colorToUse, "44");
	if(color == smagenta) return strcpy(colorToUse, "45");
	if(color == scyan) return strcpy(colorToUse, "46");
	return strcpy(colorToUse, "47");
}


/**
 * Change la couleur de l'écran ou de la police
 * @param color Couleur à utiliser
 */
void color(int color){
	char colorToUse[3];

	strcpy(colorToUse, getColor(color));
	
	printf("\033[%sm",colorToUse);
}

/**
 * Efface l'écran
 */
void clearScreen(){
	printf("\033[H\033[2J");
}