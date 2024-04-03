# Jeu de la vie
<img src="https://media.giphy.com/media/u6Lych5DL1l1JJHNW8/giphy.gif">

## Présentation du jeu original
Le Jeu de la Vie (ou Game of Life) est, en realité, un automate cellulaire défini en 1970 par le mathématicien anglais John Conway afin de tenter de résoudre un problème soulevé par un mathématicien, père de l'informatique, John Von Neumann.

Ce n'est pas a proprement parler un jeu : il ne nécessite pas l'intervention d'un joueur humain, hormis pour fixer les conditions initiales du jeu. Il se compose d'un univers dans lequel évoluent des cellules vivantes suivant des regles d'évolution précises.

Dans la version originale décrite par John Conway, l'univers est défini sur une grille à deux dimensions, de taille variable, ou chaque case est une cellule pouvant prendre deux états différents : morte ou vivante. Le passage d'un état à l'autre est guidé par les règles d'évolution suivantes :
- Une cellule morte au temps t devient vivante au temps t+1 si et seulement si elle a exactement 3 cellules vivantes dans son voisinage.
- Une cellule vivante au temps t reste vivante au temps t+1 si et seulement si elle a exactement 2 ou 3 cellules vivantes dans son voisinage, sinon elle meurt.
- Le voisinage utilisé est le 8-voisinage : pour une cellule donnée, ses voisines sont les 8 cellules qui l'entourent.

A partir de ces règles de base, beaucoup d'extensions ont été proposées mais le jeu garde le même principe : il se déroule suivant un nombre de pas de temps théoriquement infini. A chaque pas de temps t, on evalue, pour chaque cellule, l'état de la cellule au pas de temps t+1 en fonction des règles d'évolution des cellules.

## Extensions
Cette version du jeu (implémentée en langage C) propose les extensions suivantes :
- **Voisinage cyclique** : Le nombre de cellules voisines peut être calculé de manière cyclique ou non.
- **Vieillisssement des cellules** :  L'âge d'une cellule est le nombre de pas de temps consécutifs durant lesquels la cellule est vivante. Une cellule meurt de viellesse quand son âge dépasse 8 pas de temps.
- **Cellules non viables** : Il est possible de rajouter des cellules non-viables sur lesquelles la vie ne peut pas se développer.

## Prérequis
Les modules suivants sont nécessaires pour compiler et utiliser le programme dans sa globalité :
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

## Documentation
Vous trouverez [ici la documentation complète](https://mosa.pages.unistra.fr/cairo-game-of-life/) générée via doxygen. Le magnifique thème utilisé est [Doxygen Awesome](https://jothepro.github.io/doxygen-awesome-css/index.html).

## Auteur
[Samy MOSA](https://git.unistra.fr/mosa)

## Système de versionnement
Des tags de la forme `x.y.z` indiquent les versions du projet :
- `x` : version majeure
- `y` : version mineure correspondant au *niveau* du projet 
- `z` : version de correction
