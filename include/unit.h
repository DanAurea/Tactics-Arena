bool canGetPassed(unit * target);
bool canBlock(unit * target);
bool canAttack(unit * target);
bool canMove(unit * target);
int getSideAttacked();
void heal(unit* source, unit* target);
bool attack(unit* source, unit* target);
void move(unit grille[N][N],unit * source);
