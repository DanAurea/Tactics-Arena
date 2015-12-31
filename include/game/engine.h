/**
 @file engine.h
 @brief En-tête moteur de jeu
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#ifndef _ENGINE_
 	
 	#include "../display/map.h"
 	#include "../controller/mouse.h"

 	#define _ENGINE_

	// Constantes jeu
	#define NB_LISTS_ENGINE 2 /**< Nombre de liste additionnelles nécessaires pour le jeu */
	#define NB_PLAYERS 2 /**< Nombre de joueurs */
	#define NB_LINES 3 /**< Limite du camp du joueur */
	#define NB_UNITS 21	 /**< Nombre d'unités dans le jeu */
	#define NB_MAX_EFFECT 6 /**< Nombre total de status différent */
	#define MANDATORY_STATS 12 /**< Nombre de stats obligatoire */

	// Constantes joueurs
	#define FIRST_PLAYER 0 /**< Définis la valeur du premier joueur */
	#define NB_MAX_KN 3 /**< Nombre max de Guerrier par joueur */
	#define NB_MAX_SC 2 /**< Nombre max de Recrue par joueur */
	#define NB_MAX_SG 2 /**< Nombre max de Golem de pierre par joueur */
	#define NB_MAX_LT 1 /**< Nombre max de Lightning totem par joueur */
	#define NB_MAX_DR 2 /**< Nombre max de Dragon par joueur */
	#define NB_MAX_FU 2 /**< Nombre max de Furgon par joueur */
	#define NB_MAX_UNIT 10 /**< Nombre max d'unité par joueur */
	#define NB_MAX_DECOR 7 /**< Nombre max de décor */

	/**
	 * @enum cardinal engine.h
	 */
	typedef enum{north, east, south, west}cardinal; /**< Liste des directions */

	/**
	 * @enum unitName engine.h
	 */
	typedef enum{empty, decors, knight, scout, assassin, cleric, pyromancer, enchantress,
				dragonborn, darkWitch, lightningTotem, barrierTotem, mudGolem, golemAmbusher,
				frostGolem, stoneGolem, dragonTyrant, berserker, beastRider, poisonWisp, furgon}unitName; /**< Liste énumérée des noms d'unité */

	/**
	 * @enum unitEffect engine.h
	 */
	typedef enum{none, POWER_BONUS, ARMOR_BONUS, BARRIER, POISON, PARALYSE, FOCUS}unitEffect; /**< Représentation des différents status */

	/**
	 * @struct targetStat engine.h
	 * Représente les informations liées aux cibles
	 */
	typedef struct{
		short vertRange; /**< Portée verticale */
		short horizRange;  /**< Portée horizontale */
		short ringSize;  /**< Taille de l'anneau */
		short line; /**< Ciblage en ligne */
	}targetStat;

	/**
	 * @struct unitStat engine.h
	 * Représente les statistiques d'une unité
	 */
	typedef struct{
		int HP; /**< Points de vie */
		int POWER; /**< Puissance */
		float ARMOR; /**< Armure */
		int RECOVERY; /**< Repos */
		float BLOCK[3]; /**< Blocage */
		targetStat target; /**< Ciblage */
		int MOVE_RANGE; /**< Portée mouvement */
	}unitStat;

	/**
	 * @struct vector engine.h
	 * Représente les coordonnées d'un vecteur
	 */
	typedef struct{
		int x; /**< Position x */
		int y; /**< Position y */
	}vector; 

	/**
	 * @struct unit engine.h
	 * Représente une unité
	 */
	typedef struct{
		unitName name; /**< Nom de l'unité */
		unitStat stat; /**< Statistiques de l'unité */
		unitEffect effect[NB_MAX_EFFECT]; /**< Effets sur l'unité*/
		cardinal direct; /**< Direction de l'unité */
		int noPlayer; /**< Propriétaire de l'unité */
		int unitColor; /**< Couleur de l'unité */
	}unit;

	extern unit grid[N][N]; /**< Représentation d'une grille d'unité globale */
	extern int noPlayer; /**< Représentation du joueur */

	bool isSurrounded(vector currentUnit); /**< Vérifie si une unité est entourée */
	void gameInit(); /**< Initialise le jeu */
	bool selectUnit(vector * coordUnit); /**< Sélectionne une unité */
	void setTarget(unitName name,vector coordUnit, int colorDisp); /**< Définis les cibles */
	void launchAttack(vector coordSource, vector coordTarget); /**< Lance une attaque */
	void movable(int colorDisp); /**< Fait la liste des unités déplaçables */
	void attackable(int colorDisp); /**< Fait la liste des unités pouvant attaquer */
	void tileWalkable(vector coordUnit, int colorDisp); /**< Fait la liste des cases atteignables par l'unité */
	bool possiblePath(vector coordUnit); /**< Vérifie qu'un chemin est possible */
	bool pathFind(vector, vector); /**< Trouve une chemin vers la destination */
	void startGame(); /**< Débute la partie */

#endif