/**
 @file turn.h
 @brief En-tête gestion des tours
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#define TIME_BY_UNIT 12 /**< Temps par unité possédée par le joueur */
#define MIN_TIME 60 /**< Temps minimum par tour */
#define MAX_TIME 120 /**< Temps maximum par tour */

void playTurn(); /**< Joue un tour */
void playAttack(); /**< Joue une attaque */
void playMove(); /**< Joue une mouvement */
void passTurn(); /**< Passe le tour */
void changeDirection(); /**< Change la direction */
bool hasPlay(); /**< Vérifie si une action a été effectuée */
void surrender(); /**< Abandonne la partie */

extern int hasMoved; /**< Joueur a joué */
extern int hasAttacked; /**< Joueur a attaqué*/
extern int hasPassed; /**< Joueur a passé son tour */
extern int hasSurrender; /**< Joueur a abandonné la partie */