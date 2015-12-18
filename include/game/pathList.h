/**
 @file pathList.h
 @brief En-tête listes des chemins
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

void initPath(int); /**< Initialise le chemin */
void initPaths(); /**< Initialise les chemins */
int emptyPath(int n); /**< Vérifie si chemin vide */
int outPath(int n); /**< Vérifie si l'élément courant est en dehors de la liste */
void pathHead(int n); /**< Se met en tête de la liste */
void pathTail(int n); /**< Se met en queue de la liste */
void previous(int n); /**< Se positionne sur l'élément précédent */
void next(int n); /**< Se positionne sur l'élément suivant */
void getTile(int n, vector * v, int * F); /**< Récupère la valeur d'une case */
void setTile(int n, vector v, int F); /**< Modifie la valeur d'une case */
void eraseTile(int n); /**< Efface une case */
void toRightPath(int n, vector v, int F); /**< Ajoute une case à droite */
void dumpPath(short nbList); /**< Vide le chemin */
void dumpAllPaths(); /**< Vide les chemins */
bool searchTile(int n, vector); /**< Cherche une case */
vector getCurrentNode(int n); /**< Récupère la case ayant le plus petit poids */
void addCloseList(vector, int); /**< Ajoute la case à la liste fermée */
void addOpenList(vector, int); /**< Ajoute la case à la liste ouverte */