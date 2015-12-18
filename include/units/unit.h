/**
 @file unit.h
 @brief En-tête gestion des unités
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

bool canGetPassed(unit * target); /**< Vérifie si le passage est autorisé */
bool canBlock(unit * target); /**< Vérifie si l'unité peut bloquer */
bool canAttack(unit * target); /**< Vérifie si l'unité peut attaquer */
bool canMove(unit * target); /**< Vérifie si l'unité peut bouger */
bool canTeleport(unitName name); /**< Vérifie si l'unité peut se téléporter */
int getSideAttacked(vector source, vector target ); /**< Récupère le côté attaqué */
void heal(unitName name); /**< Soigne les unités */
void attack(vector source, vector target); /**< Attaque une unité*/
bool copy(unit * destination, unit * source); /**< Copie la structure source vers destination */
void move(vector destination, vector source); /**< Bouge une unité */
void addEffect(vector target, unitEffect effect); /**< Ajoute un effet à une unité */
void unitInit(short noPlayer, vector coordUnit); /**< Initialise une unité */
void setDirection(vector coordUnit, int dir); /**< Définis la direction d'une unité */
void erase(unit * ); /**< Efface une unité de la grille */
bool isSleeping(vector); /**< Vérifie si une unité est endormie */
void recover(); /**< Se réveille tour par tour */
bool allStatic(int numPlayer); /**< Vérifie si toutes les unités sont immobilisées */
void minusEffect(); /**< Diminue le temps de l'effet */
void poison(); /**< Empoisonne une unité */
void powerBonus(); /**< Octroie un bonus de puissance selon certaines conditions*/
void sleep(vector); /**< Endors une unité */