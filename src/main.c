/**
 * \file main.c
 * Code principal
 * \author Samy MOSA
 */

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

#ifdef MODE_GRAPHIQUE
#include "io_g.h"
#else
#include "io.h"
#endif

/** Pointeur de fonction de calcul des voisins (cyclique par défaut)*/
int (*compte_voisins_vivants)(int, int, grille) = compte_voisins_vivants_c;

/**
 * @brief Fonction principale. Initialise les grilles, lance le jeu et libère les grilles.
 *
 * @param argc Nombre d'arguments
 * @param argv Tableau d'arguments sous forme de chaînes de caractères
 * @return int : 0 si tout si aucune erreur ne s'est produite.
 */
int main(int argc, char **argv)
{

	if (argc != 2)
	{
		printf("usage : main <fichier grille>");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1], &g);
	alloue_grille(g.nbl, g.nbc, &gc);

	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
