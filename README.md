# Tactics Arena

Tactics Arena est un jeu de stratégie au tour par tour se jouant sur un plateau.
Chaque joueur déplace ses unités respectant des règles de déplacement propre à chaque unité, le but du jeu est d'éliminer ou paralyser toutes les unités ennemies.

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


## Sommaire
   **Tactics Arena**

   1. **[Règles](#règles)**
   2. **[Changelog](#changelog)**
     - **[Version 0.1](#version-01)**
   3. **[A faire](#a-faire)**
   4. **[Instructions de compilation](#instructions-de-compilation)**
   5. **[Utilisation](#utilisation)**
   6. **[Documentation](#documentation)**

## A faire
 
 - [x] Analyse préliminaire
 - [ ] Compte rendu mécaniques du jeu
 - [x] Analyse conceptuelle
 - [ ] Implémentation
  - [x] Grille
  - [ ] Menu
  - [ ] Unités
  - [ ] Statistiques
  - [ ] Mouvements
  - [ ] Gestion des tours
  - [ ] Gestion du temps
  - [ ] Capacités spéciales
  - [ ] Etat unités
 - [ ] Test unitaires
 - [ ] Test d'intégration
 - [ ] Ajout de fonctionnalités
  - [ ] Intégration IA
  - [ ] GUI

## Changelog

### Version 0.1

 - Mise en place sommaire des TAD

## Instructions de compilation


## Utilisation


## Documentation