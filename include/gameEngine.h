#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


#define N 11 /**< Taille de la grille */
#define NB_LINES 2 /**< Limite du camp du joueur */
#define NB_MAX_EFFECT 6 /**< Nombre total de status différent */
#define MAX_RANGE 36 /**< Portée max des actions */
#define MANDATORY_STATS 8 /**< Nombre de stats obligatoire */

#define NB_MAX_KN 3 /**< Nombre max de Guerrier par joueur */
#define NB_MAX_SC 2 /**< Nombre max de Recrue par joueur */
#define NB_MAX_SG 2 /**< Nombre max de Golem de pierre par joueur */
#define NB_MAX_LT 1 /**< Nombre max de Lightning totem par joueur */
#define NB_MAX_DR 2 /**< Nombre max de Dragon par joueur */
#define NB_MAX_FU 2 /**< Nombre max de Furgon par joueur */
#define NB_MAX_UNIT 10 /**< Nombre max d'unité par joueur */
#define NB_MAX_DECOR 7 /**< Nombre max de décor */


typedef enum{north, east, south, west}cardinal;
typedef enum{empty, decors, knight, scout, assassin, cleric, pyromancer, enchantress, 
			dragonborn, darkWitch, lightningTotem, barrierTotem, mudGolem, golemAmbusher,
			frostGolem, stoneGolem, dragonTyrant, berserker, beastRider, poisonWisp, furgon}unitName; /**< Liste énumérée des noms d'unité */
typedef enum{none, POWER_BONUS, ARMOR_BONUS, BARRIER, POISON, PARALYSE, FOCUS}unitEffect; /**< Représentation des différents status */
typedef struct{int HP; int POWER; float ARMOR; int RECOVERY; float BLOCK[3]; int MOVE_RANGE; int Area;}unitStat; /**< Représentation des statistiques d'une unité*/
typedef struct{int x; int y;}vector; /**< Représentation d'un vecteur */
typedef struct{unitName name; unitStat stat; vector unitTarget[MAX_RANGE]; unitEffect effect[NB_MAX_EFFECT];short direct; short noPlayer; short unitColor;}unit; /**< */
typedef struct{vector coordUnit; vector fieldAction[MAX_RANGE];}unitAction; /**< Actions possibles par une unité */
extern unit grid[N][N]; /**< Représentation d'une grille d'unité globale */
extern unit * pawns;

bool lookAround(vector currentUnit);
void gameInit();
void createPawn(int * nbPawns, int nbParams, unitName name, ...);
