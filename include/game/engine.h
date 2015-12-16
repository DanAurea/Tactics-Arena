#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Constantes jeu
#define N 11 /**< Taille de la grille */
#define NB_LISTS_ENGINE 1 /**< Nombre de liste additionnelles nécessaires pour le jeu */
#define NB_PLAYERS 2 /**< Nombre de joueurs */
#define NB_LINES 2 /**< Limite du camp du joueur */
#define NB_UNITS 21	 /**< Nombre d'unités dans le jeu */
#define NB_MAX_EFFECT 6 /**< Nombre total de status différent */
#define MANDATORY_STATS 8 /**< Nombre de stats obligatoire */

// Constantes joueurs
#define FIRST_PLAYER 0 /**< Définis la valeur du premier joueur */
#define NB_MAX_KN 3 /**< Nombre max de Guerrier par joueur */
#define NB_MAX_SC 2 /**< Nombre max de Recrue par joueur */
#define NB_MAX_SG 2 /**< Nombre max de Golem de pierre par joueur */
#define NB_MAX_LT 1 /**< Nombre max de Lightning totem par joueur */
#define NB_MAX_DR 2 /**< Nombre max de Dragon par joueur */
#define NB_MAX_FU 2 /**< Nombre max de Furgon par joueur */
#define NB_MAX_UNIT 5 /**< Nombre max d'unité par joueur */
#define NB_MAX_DECOR 7 /**< Nombre max de décor */


typedef enum{north, east, south, west}cardinal;
typedef enum{empty, decors, knight, scout, assassin, cleric, pyromancer, enchantress,
			dragonborn, darkWitch, lightningTotem, barrierTotem, mudGolem, golemAmbusher,
			frostGolem, stoneGolem, dragonTyrant, berserker, beastRider, poisonWisp, furgon}unitName; /**< Liste énumérée des noms d'unité */
typedef enum{none, POWER_BONUS, ARMOR_BONUS, BARRIER, POISON, PARALYSE, FOCUS}unitEffect; /**< Représentation des différents status */
typedef struct{int HP; int POWER; float ARMOR; int RECOVERY; float BLOCK[3]; int MOVE_RANGE;}unitStat; /**< Représentation des statistiques d'une unité*/
typedef struct{int x; int y;}vector; /**< Représentation d'un vecteur */
typedef struct{unitName name; unitStat stat; unitEffect effect[NB_MAX_EFFECT]; cardinal direct; int noPlayer; int unitColor;}unit; /**< */
extern unit grid[N][N]; /**< Représentation d'une grille d'unité globale */
extern int noPlayer; /**< Représentation du joueur */

bool isSurrounded(vector currentUnit);
void gameInit();
bool selectUnit(vector * coordUnit);
void getTargets(vector coordUnit, int colorDisp);
void launchAttack(vector coordSource, vector coordTarget);
void movable(int colorDisp);
void attackable(int colorDisp);
void tileWalkable(vector coordUnit, int colorDisp);
bool possiblePath(vector coordUnit);
bool findPath(vector, int, int, int, vector);
void startGame();