// Traitement nom unité
char* get2Char(char name[]);
char* getNameUnit(unitName unit);
void printNameUnit(unitName unit);

// Vérification coordonnées
void getCoordS(char coordString[], vector * coordUnit);
bool correctCoord(char * coordString);
bool rightSide(char * coordString, short noPlayer);

// Saisie sécurisée
int read(char * string);
long readLong();
double readDouble();
void clearBuffer();