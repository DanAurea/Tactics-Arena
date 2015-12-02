#include <stdbool.h>
#include <string.h>

#define N 11 /**< Taille de la grille */
#define NB_MAX_EFFECT 6 /** Nombre total de status différent */
#define MAX_RANGE 36 /**< Portée max des actions */
#define NB_MAX_KNIGHT 3 /**< Nombre max de guerrier par joueur */
#define NB_MAX_UNIT 10 /**< Nombre max d'unité par joueur */


typedef enum{north, east, south, west}cardinal;
typedef enum{empty, decors, knight, scout, assassin, cleric, pyromancer, enchantress, 
			dragonborn, darkWitch, lightningTotem, barrierTotem, mudGolem, golemAmbusher,
			frostGolem, stunGolem, dragonTyrant, berserker, beastRider, poisonWisp, furgon}unitName; /**< Liste énumérée des noms d'unité */
typedef enum{none, POWER_BONUS, ARMOR_BONUS, BARRIER, POISON, PARALYSE, FOCUS}unitEffect; /**< Représentation des différents status */
typedef struct{int HP; int POWER; float ARMOR; int RECOVERY; float BLOCK[3]; int MOV_RANGE; int Area;}unitStat; /**< Représentation des statistiques d'une unité*/
typedef struct{int x; int y;}vector; /**< Représentation d'un vecteur */
typedef struct{unitName name; unitStat stat; vector unitTarget[MAX_RANGE]; unitEffect effect[NB_MAX_EFFECT];int direct;}unit; /**< */
typedef struct{vector coordUnit; vector fieldAction[MAX_RANGE];}unitAction; /**< Actions possibles par une unité */
extern unit grid[N][N]; /**< Représentation d'une grille d'unité globale */


bool lookAround(vector currentUnit);
void gameInit();
