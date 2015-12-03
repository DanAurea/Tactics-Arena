#define MAX_TAB 10 
#define MAX_JOUEUR 3 /**< Nombre max de listes */

void init_liste(int);
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
void printList(int noPlayer);