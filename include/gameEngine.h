#include <stdbool.h>

#define N 11
#define NB_MAX_EFFECT 6


typedef enum{empty, decors, knight, scout, assassin, cleric, pyromancer, enchantress, dragonborn, darkWitch, lightningTotem, barrierTotem, mudGolem, golemAmbusher, frostGolem, stunGolem, dragonTyrant, berserker, beastRider, poisonWisp, furgon}unitName;

typedef enum{none, POWER_BONUS, ARMOR_BONUS, BARRIER, POISON, PARALYSE, FOCUS}unitEffect;

typedef struct{int HP; int POWER; float ARMOR; int RECOVERY; float BLOCK[3]; int MOV_RANGE; int Area;}unitStat;

typedef struct{int x; int y;}vector;

typedef struct{unitName name; unitStat stat; vector unitTarget[10]; unitEffect effect[NB_MAX_EFFECT];int direct;}unit;

typedef struct{vector coordUnit; vector fieldAction[36];}unitAction;

unit grid[N][N];

bool lookAround(vector currentUnit);