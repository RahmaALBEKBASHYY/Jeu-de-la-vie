La traduction française est ci-dessous. 👇
# Game of Life

<img src="https://media.giphy.com/media/u6Lych5DL1l1JJHNW8/giphy.gif">

## Introduction to the Original Game
The Game of Life is actually a cellular automaton defined in 1970 by the English mathematician John Conway in an attempt to solve a problem raised by mathematician and computer scientist John Von Neumann.

It is not strictly a game: it does not require the intervention of a human player, except to set the initial conditions of the game. It consists of a universe in which living cells evolve according to precise rules.

In the original version described by John Conway, the universe is defined on a two-dimensional grid, of variable size, where each square is a cell that can take two different states: dead or alive. The transition from one state to another is guided by the following evolution rules:
- A dead cell at time t becomes alive at time t+1 if and only if it has exactly 3 living cells in its neighborhood.
- A living cell at time t remains alive at time t+1 if and only if it has exactly 2 or 3 living cells in its neighborhood, otherwise, it dies.
- The neighborhood used is the 8-neighborhood: for a given cell, its neighbors are the 8 cells surrounding it.

From these basic rules, many extensions have been proposed but the game retains the same principle: it unfolds over a theoretically infinite number of time steps. At each time step t, for each cell, the state of the cell at time t+1 is evaluated based on the rules of cell evolution.

## Extensions
This version of the game (implemented in the C language) offers the following extensions:
- **Cyclic Neighbourhood**: The number of neighboring cells can be calculated cyclically or not.
- **Cell Aging**: The age of a cell is the number of consecutive time steps during which the cell is alive. A cell dies of old age when its age exceeds 8 time steps.
- **Non-viable Cells**: It is possible to add non-viable cells on which life cannot develop.

## Prerequisites
The following modules are necessary to compile and use the program in its entirety:
- **make** for generating the executable and other files
- **gcc** for compilation
- **doxygen** for generating documentation
- **cairo** for graphical display

You can install them using:
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install doxygen
sudo apt-get install libcairo2-dev
```

## Installation
To compile the program, use the command `make`.

By default, the display is done graphically. To compile in text mode, use `make MODE=TEXTE`.

## Usage / Commands
To launch the program, simply do `bin/main <grid_file>`

### Text Mode
- <kbd>Enter</kbd>: Advances the grid by one time step
- <kbd>q</kbd>: Quits the game
- <kbd>n</kbd>: Loads a new grid entered by the user
- <kbd>c</kbd>: Enables/Disables cyclic calculation of cell neighbors
- <kbd>v</kbd>: Enables/Disables cell aging
- <kbd>o</kbd>: Runs a colony oscillation test

### Graphical Mode
- <kbd>Left Click</kbd> or <kbd>Enter</kbd>: Advances the grid by one time step
- <kbd>Right Click</kbd> or <kbd>ESC</kbd>: Quits the game
- <kbd>n</kbd>: Loads a new grid entered by the user
- <kbd>c</kbd>: Enables/Disables cyclic calculation of cell neighbors
- <kbd>v</kbd>: Enables/Disables cell aging
- <kbd>o</kbd>: Runs a colony oscillation test


## Author
[ALBEKBASHY Rahma]

## Versioning System
Tags of the form `x.y.z` indicate project versions:
- `x`: Major version
- `y`: Minor version corresponding to the project's *level*
- `z`: Correction version

---

## Jeu de la Vie

<img src="https://media.giphy.com/media/u6Lych5DL1l1JJHNW8/giphy.gif">

## Présentation du jeu original
Le Jeu de la Vie est en réalité un automate cellulaire défini en 1970 par le mathématicien anglais John Conway dans le but de résoudre un problème soulevé par le mathématicien et informaticien John Von Neumann.

Il ne s'agit pas strictement d'un jeu : il ne nécessite pas l'intervention d'un joueur humain, sauf pour définir les conditions initiales du jeu. Il consiste en un univers dans lequel des cellules vivantes évoluent selon des règles précises.

Dans la version originale décrite par John Conway, l'univers est défini sur une grille à deux dimensions, de taille variable, où chaque case est une cellule pouvant prendre deux états différents : morte ou vivante. La transition d'un état à un autre est guidée par les règles d'évolution suivantes :
- Une cellule morte au temps t devient vivante au temps t+1 si et seulement si elle a exactement 3 cellules vivantes dans son voisinage.
- Une cellule vivante au temps t reste vivante au temps t+1 si et seulement si elle a exactement 2 ou 3 cellules vivantes dans son voisinage, sinon elle meurt.
- Le voisinage utilisé est le 8-voisinage : pour une cellule donnée, ses voisines sont les 8 cellules qui l'entourent.

À partir de ces règles de base, de nombreuses extensions ont été proposées, mais le jeu conserve le même principe : il se déroule sur un nombre théoriquement infini de pas de temps. À chaque pas de temps t, pour chaque cellule, l'état de la cellule au pas de temps t+1 est évalué en fonction des règles d'évolution cellulaire.

## Extensions
Cette version du jeu (implémentée en langage C) propose les extensions suivantes :
- **Voisinage cyclique** : Le nombre de cellules voisines peut être calculé de manière cyclique ou non.
- **Vieillissement des cellules** : L'âge d'une cellule est le nombre de pas de temps consécutifs pendant lesquels la cellule est vivante. Une cellule meurt de vieillesse lorsque son âge dépasse 8 pas de temps.
- **Cellules non viables** : Il est possible d'ajouter des cellules non viables sur lesquelles la vie ne peut pas se développer.

## Prérequis
Les modules suivants sont nécessaires pour compiler et utiliser le

 programme dans sa globalité :
- **make** pour la génération de l'exécutable et d'autres fichiers
- **gcc** pour la compilation
- **doxygen** pour la génération de la documentation
- **cairo** pour l'affichage graphique

Vous pouvez les installer en utilisant :
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install doxygen
sudo apt-get install libcairo2-dev
```

## Installation
Pour compiler le programme, utilisez la commande `make`.

Par défaut, l'affichage se fait graphiquement. Pour compiler en mode texte, utilisez `make MODE=TEXTE`.

## Usage / Commandes
Pour lancer le programme, faites simplement `bin/main <fichier_grille>`

### Mode Texte
- <kbd>Entrée</kbd> : Fais évoluer la grille d'un pas de temps
- <kbd>q</kbd> : Quitte le jeu
- <kbd>n</kbd> : Charge une nouvelle grille entrée par l'utilisateur
- <kbd>c</kbd> : Active/Désactive le calcul cyclique des voisins de cellule
- <kbd>v</kbd> : Active/Désactive le vieillissement des cellules
- <kbd>o</kbd> : Lance un test d'oscillation de la colonie

### Mode Graphique
- <kbd>Clic gauche</kbd> ou <kbd>Entrée</kbd> : Fais évoluer la grille d'un pas de temps
- <kbd>Clic droit</kbd> ou <kbd>ESC</kbd>: Quitte le jeu
- <kbd>n</kbd> : Charge une nouvelle grille entrée par l'utilisateur
- <kbd>c</kbd> : Active/Désactive le calcul cyclique des voisins de cellule
- <kbd>v</kbd> : Active/Désactive le vieillissement des cellules
- <kbd>o</kbd> : Lance un test d'oscillation de la colonie

## Auteur
[ALBEKBASHY Rahma]

## Système de versionnement
Des tags de la forme `x.y.z` indiquent les versions du projet :
- `x` : version majeure
- `y` : version mineure correspondant au *niveau* du projet 
- `z` : version de correction

---
