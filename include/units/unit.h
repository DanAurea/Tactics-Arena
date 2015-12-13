bool canGetPassed(unit * target);
bool canBlock(unit * target);
bool canAttack(unit * target);
bool canMove(unit * target);
int getSideAttacked(vector source, vector target );
void heal(unitName name);
void attack(vector source, vector target);
bool copy(unit * destination, unit * source);
void move(vector destination, vector source);
void addEffect(vector target, unitEffect effect);
void AoE(vector pos, int size, int dmg, bool own);
void line(vector pos, int size, int dmg, int dir);
void unitInit(short noPlayer, vector coordUnit);
void setDirection(vector coordUnit, int dir);