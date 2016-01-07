/**
 @file listes.h
 @brief En-tête listes de vecteurs
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#define MAX_JOUEUR 3 /**< Nombre max de listes */

extern int targetList; /**< Cibles potentielles */

// Primitives listes
void init_liste(int); /**< Initialise une liste */
void initLists(); /**< Initialise les listes */
int liste_vide(int); /**< Vérifie si une liste est vide */
int hors_liste(int); /**< Vérifie si l'élément courant est hors de la liste */
void en_tete(int); /**< Se met en tête de la liste */
void en_queue(int); /**< Se met en queue de la liste */
void precedent(int); /**< Se positionne sur l'élément précédent */
void suivant(int); /**< Se positionne sur l'élément suivant */
void valeur_elt(int, vector* v); /**< Récupère la valeur de l'élément */
void modif_elt(int,vector v); /**< Modifie la valeur de l'élément */
void oter_elt(int); /**< Supprime l'élément */
void ajout_droit(int,vector v); /**< Ajoute à droite l'élément */
void ajout_gauche(int,vector v); /**< Ajoute à gauche l'élément */
void dumpList(short nbList); /**< Vide une liste */
void dumpAllLists(); /**< Vide les listes*/

// Manipulation des listes d'unités
void addUnit(vector coordUnit); /**< Ajoute une unité */
void destroyUnit(vector coordUnit); /**< Détruit une unité */
void printList(short numList); /**< Affiche la liste */
int countUnits(); /**< Compte le nombre d'unités */

// Manipulation des listes de cible
void addTarget(unitName name, vector coordUnit); /**< Ajoute une cible */
bool searchTarget(int numList, vector coordTarget); /**< Cherche une cible */

// Mise à jour listes
void updateIdSprite(int idUpdated, int offset); /**< Met à jours les identifiants des sprites */