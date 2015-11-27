#include <stdbool.h>


bool canGetPassed(unit * target);
bool canBlock(unit * target);
bool canAttack(unit * target);
bool canMove(unit * target);
int getSideAttacked(unit * source, unit * target );
void heal(unit* source, unit* target);
void attack(unit* source, unit* target);
void copy(unit * destination, unit * source);
void move(unit grille[N][N],vector pos[]);
