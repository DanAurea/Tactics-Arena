/**
 @file manageString.h
 @brief En-tête gestion des chaînes de caractères
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

// Traitement nom unité
char* get2Char(char name[]); /**< Récupère 2 caractères du nom de l'unité */
char* getNameUnit(unitName unit); /**< Récupère le nom de l'unité */
int   getNumber(char name[]); /**< Récupère l'entier de l'unité d'après le nom de l'unité */
void printNameUnit(unitName unit); /**< Affiche le nom de l'unité */

// Vérification coordonnées
void getCoordS(char coordString[], vector * coordUnit); /**< Récupère les coordonnées d'une chaîne de caractères */

// Saisie sécurisée
int readS(char * string); /**< Lecture sécurisée d'une chaîne */
long readLong(); /**< Lecture sécurisée d'un long */
double readDouble(); /**< Lecture sécurisée d'un double */
void clearBuffer(); /**< Vide la mémoire tampon */

// Direction
char* getDirectionUnit(cardinal direct); /**< Récupère le nom de la direction */

// Traitement nom effet
char* getNameEffect(unitEffect effect); /**< Récupère le nom de l'effet */