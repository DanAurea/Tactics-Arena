#define TIME_BY_UNIT 12 /**< Temps par unité possédée par le joueur */
#define MIN_TIME 60 /**< Temps minimum par tour */
#define MAX_TIME 120 /**< Temps maximum par tour */

void playTurn();
void playAttack();
void playMove();
void passTurn();
void changeDirection();
bool hasPlay();

extern int hasMoved;
extern int hasAttacked;
extern int hasPassed;