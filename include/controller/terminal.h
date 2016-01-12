/**
 @file terminal.h
 @brief En-tête gestion du terminal
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

/**
 * @enum terminal terminal.h
 */
typedef enum{black, red, green, yellow, blue, magenta, cyan, white}terminal; /**< Colors */

 /**
 * @enum screen terminal.h
 */
typedef enum{reinit = 0, blink = 5, invertColor= 7}screenAction; /**< Set screen action */

void color(int color, char type[]); /**< Met en couleurs le texte ou l'écran */
void fontColor(int color); /**< Met en couleurs la police */
void clearScreen(); /**< Efface l'écran */
void reinitColor(); /**< Réinitialise les couleurs */