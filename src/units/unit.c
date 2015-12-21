/**
 @file unit.c
 @brief Gestion des unités
 @author Cousin Brandon Chaudemanche Ewen Biardeau Tristan
 @version v1.00
 @date 18/12/2015
 */

#include <stdio.h>
#include <math.h>
#include "../../include/game/engine.h"
#include "../../include/game/pawns.h"
#include "../../include/game/listes.h"
#include "../../include/display/grid.h"
#include "../../include/controller/terminal.h"
#include "../../include/controller/manageString.h"
#include "../../include/units/unit.h"

/**
 * Initialise l'unité courante
 * @param noP Numéro du joueur
 * @param coordUnit Coordonnées de l'unité
 */
void unitInit(short noP, vector coordUnit)
{
	int unitName = grid[coordUnit.x][coordUnit.y].name;
    copy (&grid[coordUnit.x][coordUnit.y],&pawns[unitName]); //unitName à la place de 0
    grid[coordUnit.x][coordUnit.y].noPlayer = noP;

    grid[coordUnit.x][coordUnit.y].unitColor = black;
    if(noPlayer == FIRST_PLAYER)
    {
        setDirection(coordUnit,north);
    }
    else
    {
        setDirection(coordUnit,south);
    }
}

/**
 * Définis si le passage est permis
 * @param  target Unité à analyser
 * @return        Retourne vrai si passage autorisé
 */
bool canGetPassed(unit * target)
{
    bool out = true;
    for(int i = 1;i<NB_MAX_EFFECT && out;i++)
    {
    	if(i > ARMOR_BONUS  && target-> effect[i-1] > 0)
    	{
    		out = false;
    	}
    }

    return out;
}


/**
 * Définis si une unité peut bloquer
 * @param  target Unité à analyser
 * @return        Retourne vrai si l'unité peut bloquer
 */
bool canBlock(unit * target)
{
    bool out = true;
    for(int i = 1;i<NB_MAX_EFFECT && out;i++)
    {
    	if(i > POISON && target->effect[i-1] > 0)
        {
        	out = false;
        }
    }

    return out;
}


/**
 * Définis si une unité peut attaquer
 * @param  target Unité à analyser
 * @return        Retourne vrai si l'unité peut attaquer
 */
bool canAttack(unit * target)
{
    bool out = true;
    for(int i = 1;i<=NB_MAX_EFFECT && out;i++)
    {
    	if(i > BARRIER  && i < FOCUS && target->effect[i-1] > 0)
        {
        	out = false;
        }
    }

    return out;
}


/**
 * Définis si une unité peut bouger
 * @param  target Unité à analyser
 * @return        Retourne vraie si l'unité peut se mouvoir
 */
bool canMove(unit * target)
{
    bool out = true;

    if(pawns[target->name].stat.MOVE_RANGE == 0)
        out = false;

    for(int i = 0;i<NB_MAX_EFFECT && out;i++)
    {
    	if(target->effect[PARALYSE-1] > 0)
        {
        	out = false;
        }
    }

    return out;
}

/**
 * Détermine si une unité peut se téléporter
 * @param  name Nom de l'unité
 * @return      Retourne vraie si l'unité peut se déplacer
 */
bool canTeleport(unitName name){
    if(name == poisonWisp || name == dragonTyrant || name == mudGolem || name == dragonborn){
        return true;
    }
    return false;
}


/**
 * Soigne les unités
 * @param name Nom de l'unité soignant
 */
void heal(unitName name)
{
    vector pos;
    unitName target;
    if(!liste_vide(noPlayer))
    {
        en_tete(noPlayer);
        while(!hors_liste(noPlayer))
        {
            valeur_elt(noPlayer,&pos);
            target=grid[pos.x][pos.y].name;
            grid[pos.x][pos.y].stat.HP+=pawns[name].stat.POWER;
            
            if(grid[pos.x][pos.y].stat.HP > pawns[target].stat.HP)
            {
                grid[pos.x][pos.y].stat.HP=pawns[target].stat.HP;
            }else{
                printf("L'unité %s en %c - %i a été soignée de %i HP !\n",getNameUnit(target), 'A' + pos.x, pos.y +1, pawns[name].stat.POWER);
            }
            suivant(noPlayer);
        }
    }
}


/**
 * Retourne le côté attaqué
 * @param  source Position unité source
 * @param  target Position unité cible
 * @return        Le côté attaqué
 */
int getSideAttacked(vector source, vector target )
{
	unit * uTarget = &grid[target.x][target.y];
	unit * uSource = &grid[source.x][source.y];

    if(uSource->direct == uTarget->direct) return 2; // Par derrière
    else if((uSource->direct == west || uSource->direct == east) && (uTarget->direct == west || uTarget->direct == east)) return 1; // Côté
    else return 0; // Face à face
}


/**
 * Attaque une unité en prenant en compte son taux de blocage
 * @param source Unité attaquante
 * @param target Unité cible
 */
void attack(vector source, vector target)
{
    int tmp  = 0;
    int miss = 0;
	float block = 0;
	float armor;
	unit * uTarget = &grid[target.x][target.y];
	unit * uSource = &grid[source.x][source.y];
    if(canAttack(uSource) && uTarget->name != empty && uTarget->name != decors)
    {
    	armor = 1-uTarget->stat.ARMOR;
    	if(canBlock(uTarget))
    	{
    		block = 1-uTarget->stat.BLOCK[getSideAttacked(source,target)];

            miss  = (rand() % 101); // Raté -> Tire un chiffre entre 0 et 100
    	}

        if(miss >= 100 - 100 * (1 - block)){
            printf("L'attaque sur %s en %c - %i a raté !\n", getNameUnit(uTarget->name),'A' + target.x, target.y +1);
        }else{
            uTarget->stat.HP -= uSource->stat.POWER * block * armor;

            if(uSource->stat.POWER * block * armor > 0){
                printf("\nL'unité %s en %c - %i a subi %i dégâts !\n",getNameUnit(uTarget->name), 'A' + target.x, target.y +1,
                    (int)(uSource->stat.POWER* block * armor));
            }

            if(uTarget->stat.HP <= 0){
                tmp = noPlayer;
                noPlayer = uTarget->noPlayer; //Détruit l'unité dans la liste du joueur correspondant
                destroyUnit(target);
                erase(uTarget);
                noPlayer = tmp;

                fontColor(red);
                printf("L'unité est morte !\n");
                reinitColor();
            }
        }
    }

}


/**
 * Copie la structure source vers la structure destination
 * @param  destination Structure destination
 * @param  source      Structure source
 * @return             Retourne vrai si copie bien déroulée
 */
bool copy(unit * destination, unit * source)
{
    if(destination != NULL && source != NULL)
    {
        destination->name		 = 	source->name;
        destination->stat.HP	 = 	source->stat.HP;
        destination->stat.POWER	 = 	source->stat.POWER;
        destination->stat.ARMOR	 = 	source->stat.ARMOR;
        destination->stat.RECOVERY = 	source->stat.RECOVERY;

        for(int i = 0;i<3;i++)
        {
            destination->stat.BLOCK[i] = source->stat.BLOCK[i];
        }
        destination->stat.MOVE_RANGE = source->stat.MOVE_RANGE;
        
        for(int i = 0;i<NB_MAX_EFFECT;i++){
            destination->effect[i] = source->effect[i];
        }

        destination->direct    = source->direct;
        destination->noPlayer  = source->noPlayer;
        destination->unitColor = source->unitColor;
    }
    else
    {
        return false;
    }
    return true;
}

/**
 * Efface une unité de la grille
 * @param source Source à effacer
 */
void erase(unit * source)
{
    memset(source, -1, sizeof(unit));
    source->name          = empty;

	for(int i = 0;i<NB_MAX_EFFECT;i++)
	{
		source->effect[i] = 0;
	}
	source->unitColor= black;
}

/**
 * Octroie un bonus de puissance
 */
void powerBonus(){
    vector source;
    int d = 0, s = 0;
    int totalBonus = 0;
    unit * setBonus[NB_MAX_UNIT];
    unit * drain[NB_MAX_UNIT];

    if(!liste_vide(noPlayer)){
        en_tete(noPlayer);

        while(!hors_liste(noPlayer)){
            valeur_elt(noPlayer, &source);

            if(strstr(getNameUnit(grid[source.x][source.y].name), "Dragon")){
                drain[d] = &grid[source.x][source.y];

                d++; // Drain en plus
            }

            if(grid[source.x][source.y].name == pyromancer || grid[source.x][source.y].name == cleric){
                setBonus[s] = &grid[source.x][source.y];

                s++; // Définis un bonus en plus
            }

            suivant(noPlayer);
        }
    }

    if(d > 0 && s > 0){ // Si drain + unité pouvant recevoir un bonus
        color(red, "Vos mages drainent la puissance de vos dragons sur le terrain !\n");
        for(int i = 0; i < d; i++){ // Draine les unités
            
            if(drain[i]->stat.POWER == pawns[drain[i]->name].stat.POWER){
                drain[i]->stat.POWER -= 12;
                totalBonus += 12;
            }
        }

        for(int j = 0; j < s; j++){ // Amplifie la puissance des unités

            if(setBonus[j]->stat.POWER == pawns[setBonus[j]->name].stat.POWER){
                setBonus[j]->stat.POWER += totalBonus/s; // Répartis le bonus total sur les unités compatibles
            }
            
            if(totalBonus/s > (setBonus[j]->stat.POWER - pawns[setBonus[j]->name].stat.POWER)){ // Si jamais le nombre de drain a changé
                setBonus[j]->stat.POWER = pawns[setBonus[j]->name].stat.POWER + totalBonus/s; // Mise à jour de la puissance
            }
        }
    }else if(s > 0 && d == 0){ // Plus de drain disponible

        color(red, "Vos mages ne subissent plus les effets du drain!\n");

        for(int j = 0; j < s; j++){ // Amplifie la puissance des unités
            if(setBonus[j]->stat.POWER != pawns[setBonus[j]->name].stat.POWER){

                setBonus[j]->stat.POWER = pawns[setBonus[j]->name].stat.POWER;
            
            }
        }
    }
}

/**
 * Déplace une unité vers la destination
 * @param destination Destination souhaitée
 * @param source      Position de l'unité
 */
void move(vector destination, vector source)
{   
    unitName name = grid[source.x][source.y].name;
	unit * uSource = &grid[source.x][source.y];
	if(canMove(uSource))
	{
		copy(&grid[destination.x][destination.y],uSource);
		erase(uSource);
		destroyUnit(source);
		addUnit(destination);
        grid[source.x][source.y].unitColor = black;
        
        clearScreen(); // Met à jour la grille actualisée
        gridDisp();

        fontColor(red);
        printf("L'unité %s en %c - %i a été déplacée en %c - %i\n", getNameUnit(name), 'A' + source.x, source.y + 1, 'A' + destination.x, destination.y + 1);
        reinitColor();
	}
}

/**
 * Définis la direction de l'unité
 * @param source Unité à tourner
 * @param dir    Direction dans laquelle tourner
 */
void setDirection(vector source, int dir)
{
	unit * uSource = &grid[source.x][source.y];
	uSource->direct = dir;
}

/**
 * Gère le statut empoisonnement
 */
void poison(){
    vector coordUnit;
    int x = 0;
    vector poisoned[NB_MAX_UNIT] = {{-1}};
    vector dead[NB_MAX_UNIT] = {{-1}};

    if(!liste_vide(noPlayer)){
        en_tete(noPlayer);

        while(!hors_liste(noPlayer)){
            valeur_elt(noPlayer, &coordUnit);

            if(grid[coordUnit.x][coordUnit.y].effect[POISON-1] > 0){
                grid[coordUnit.x][coordUnit.y].stat.HP -= 4;

                if(grid[coordUnit.x][coordUnit.y].stat.HP <= 0){
                    erase(&grid[coordUnit.x][coordUnit.y]);
                    destroyUnit(coordUnit);
                    
                    dead[x] = coordUnit;

                    clearScreen(); // Met à jour la grille
                    gridDisp();
                }else{
                    poisoned[x] = coordUnit;
                }
                x++;
            }

            suivant(noPlayer);
        }

        for(int i = 0; i < NB_MAX_UNIT; i++){
            fontColor(red);
            
            if(dead[i].x > 0 || dead[i].y > 0){
                printf("L'unité en %c - %i est morte d'empoisonnement !\n", 'A' + dead[i].x, dead[i].y + 1);
            }else if(poisoned[i].x > 0 || poisoned[i].y > 0){
                printf("L'unité en %c - %i a perdu 4 HP par empoisonnement !\n", 'A' + poisoned[i].x, poisoned[i].y + 1);
            }

            reinitColor();
        }
    }
}

/**
 * Ajoute un effect sur l'unité cible
 * @param target Position unité cible
 * @param effect Effet à appliquer sur la cible
 */
void addEffect(vector target, unitEffect effect)
{
	unit * uTarget = &grid[target.x][target.y];
	if(effect==FOCUS)
	{
	    uTarget->effect[effect-1]=1;
	}
	else
	{
	    uTarget->effect[effect-1]=3;
	}

    printf("L'unité est sous l'effet de %s\n", getNameEffect(effect));
}

/**
 * Décrémente les effets
 */
void minusEffect()
{
    vector pos;
    if(!liste_vide(noPlayer))
    {
        en_tete(noPlayer);
        while(!hors_liste(noPlayer))
        {
            valeur_elt(noPlayer,&pos);
            for(int i = 1; i <= NB_MAX_EFFECT;i++)
            {
                if(grid[pos.x][pos.y].effect[i-1] > 0){
                    grid[pos.x][pos.y].effect[i-1]--;
                    printf("%s - %i", getNameEffect(i), grid[pos.x][pos.y].effect[i-1]);
                }
            }
            suivant(noPlayer);
        }
    }
}

/**
 * Endors l'unité
 * @param pos Position de l'unité
 */
void sleep(vector pos)
{
    grid[pos.x][pos.y].stat.RECOVERY = 0;
}

/**
 * Vérifie si l'unité est endormie
 * @param  pos Position de l'unité
 * @return     Retourne vrai si endormi
 */
bool isSleeping(vector pos)
{
    unit uTarget = grid[pos.x][pos.y];
    if(uTarget.stat.RECOVERY < pawns[uTarget.name].stat.RECOVERY)
    {
        return true;
    }
    return false;
}

/**
 * Réveille l'unité tour par tour
 */
void recover()
{
    vector pos;
    
    if(!liste_vide(noPlayer))
    {   
        en_tete(noPlayer);

        while(!hors_liste(noPlayer)){
            valeur_elt(noPlayer, &pos);

            if(isSleeping(pos))
            {   
                grid[pos.x][pos.y].stat.RECOVERY++;
            }

            suivant(noPlayer);
        }
    }
}

/**
 * Vérifie si toutes les unités sont immobilisés
 * @param  numPlayer Numéro du joueur
 * @return           Retourne vrai si toutes les unités sont immobilisés
 */
bool allStatic(int numPlayer)
{
    vector pos;
    if(!liste_vide(numPlayer))
    {
        en_tete(numPlayer);
        while(!hors_liste(numPlayer))
        {
            valeur_elt(numPlayer,&pos);
            if(canMove(&grid[pos.x][pos.y]) || !isSurrounded(pos))
            {
                return false;
            }
            suivant(numPlayer);
        }
    }
    
    return true;
}