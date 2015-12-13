#define MAX_JOUEUR 3 /**< Nombre max de listes */

// Primitives listes
void init_liste(int);
void initLists();
int liste_vide(int);
int hors_liste(int);
void en_tete(int);
void en_queue(int);
void precedent(int);
void suivant(int);
void valeur_elt(int, vector* v);
void modif_elt(int,vector v);
void oter_elt(int);
void ajout_droit(int,vector v);
void ajout_gauche(int,vector v);
void dumpList(short nbList);
void dumpAllLists();

void addUnit(short noPlayer, vector coordUnit);
void addTarget(unitName name, vector coordUnit);
void destroyUnit(short noPlayer, vector coordUnit);
void printList(short noPlayer);
void printTarget(unitName);