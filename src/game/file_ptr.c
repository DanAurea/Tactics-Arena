#include <stdlib.h>
#include "../../include/game/engine.h"

typedef struct element{vector coordTile; struct element* suivant;} t_element;
t_element * tete;
t_element * queue;

void initfile(void){
	tete=NULL;
	queue=NULL;
}

int filevide(void){
	return(tete == NULL);
}

void ajouter(vector coordTile){
	t_element* nouv;
	
	nouv = (t_element *)malloc(sizeof(t_element));
	nouv->coordTile.x = coordTile.x;
	nouv->coordTile.y = coordTile.y;
	nouv->suivant = NULL;
	if(filevide())
		tete = nouv;
	else
		queue->suivant = nouv;
	queue = nouv;
}

void retirer(vector * coordTile){
	t_element* premier;
	
	if(!filevide()){
		premier = tete;
		coordTile->x = premier->coordTile.x;
		coordTile->y = premier->coordTile.y;
		tete = premier->suivant;
		free(premier);
	}
}
