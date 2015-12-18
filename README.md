# Tactics Arena

Tactics Arena est un jeu de stratégie au tour par tour se jouant sur un plateau.
Chaque joueur déplace ses unités respectant des règles de déplacement propre à chaque unité, le but du jeu est d'éliminer ou paralyser toutes les unités ennemies.

## Sommaire
   **Tactics Arena**

   1. **[Règles](#markdown-header-regles)**
   2. **[Changelog](#markdown-header-changelog)**
     - **[Version 0.1](#markdown-header-version-01)**
     - **[Version 0.53](#markdown-header-version-053)**
     - **[Version 0.85](#markdown-header-version-085)**
     - **[Version 1.00](#markdown-header-version-100)**
   3. **[A faire](#markdown-header-a-faire)**
   4. **[Instructions de compilation](#markdown-header-instructions-de-compilation)**
   5. **[Utilisation](#markdown-header-utilisation)**
   6. **[Documentation](#markdown-header-documentation)**

## Règles


Les conditions d'égalité sont:

  - **Toutes les unités actives sont détruites ou immobilisée**
  - **Les joueurs passent leurs tours 3 fois d’affilé**
  - **Il n’y a eu aucune rencontre entre les deux unités ennemies depuis les 30 derniers tours.**
  

Le joueur qui commence est défini aléatoirement par l'ordinateur au début de chaque partie.

 Il n'est possible de déplacer qu'une seule unité par tour soit pour:
  
  1.  **Se déplacer**
  2.  **Et / ou attaquer**
  3.  **Et / ou changer de direction**

Le changement de direction impose d'être fait en dernier.

Chaque tour dure 1 à 2 minutes, dépendant du nombre d'unité restante.
Une fois ce temps expiré:

  - **Le tour se termine automatiquement si au moins une commande a été effectué**
  - **Si aucune commande n'a été effectuée alors abandon automatique**

#### Important : toute action est irréversible.

## A faire
 
 - [x]** Analyse préliminaire**
 - [x]** Analyse conceptuelle**
 - [x]** Implémentation**
  - [x]** Grille**
  - [x]** Menu**
  - [x]** Unités**
  - [x]** Statistiques**
  - [x]** Mouvements**
  - [x]** Gestion des tours**
  - [x]** Gestion du temps**
  - [x]** Capacités spéciales**
  - [x]** Etat unités**
 - [ ]** Test unitaires**
 - [x]** Test d'intégration**
 - [ ]** Ajout de fonctionnalités**
  - [ ]** Intégration IA**
  - [ ]** GUI**


## Changelog

### Version 0.1

 - Mise en place sommaire des TAD

### Version 0.53

 - Initialisation du jeu
 - Ajout des unités par le joueur
 - Manipulation du terminal
 - Grille flexible
 - Mise en place de modules pour chaque unité
 - Gestion des unités

### Version 0.85

- Gestion du temps
- Début gestion des tours
- Début mouvement des unités
- Début attaque des unités
- Etats unités
- Restructuration
- Correctifs divers

### Version 1.00

- Jeu sur Terminal complet
- Optimisation de l'architecture

## Instructions de compilation

Pour compiler:

> $ **make**
>

L'éxécutable se retrouve dans: bin/tacticsArena

Afin de recompiler le programme ou de nettoyer le dossier:

> $ **make clean**
>

## Utilisation

Lancer le programme avec la commande:

> $ **./bin/tacticsArena**
>

Les deux joueurs débutent la partie en ajoutant chacun leurs unités dans leur camp respectifs, une fois les unités placées dans le camp. La partie débute, l'ordinateur tire un joueur aléatoirement pour commencer à jouer.

Chaque joueur a 2 min de temps de jeu à chaque tour lorsque toutes les unités sont encore sur le terrain, chaque unité détruite réduira le temps de jeu cependant une limite minimum de 1 min est fixée.

Chaque unité ne peut faire qu'une action par tour obligeant ainsi l'utilisateur à jouer de manière stratégique, toute attaque touchent les cibles de l'adversaire tout autant que celle du joueur alors soyez vigilant sur les attaques de zones.
Chaque unité ayant agis doit se reposer pour pouvoir être utilisée à nouveau.

Des zones de couleurs indiqueront au fur et à mesure les actions possibles par chaque unité. Toute action est irréversible soyez donc prudent.

L'ordre des actions a une importance un déplacement n'est pas possible si une unité a attaqué, le changement de direction termine automatiquement le tour.

A tout moment au cours de la partie les joueurs pourront sauvegarder la partie, le fichier de sauvegarde se trouve dans :

> **assets/save/fileSave**

## Documentation

Une documentation peut être généré à l'aide de Doxygen pour recréer la documentation:

> $ make doc
>

Au cours de cette opération un document PDF récapitulant toutes l'architecture du projet sera généré dans:

> doc/man.pdf
>
