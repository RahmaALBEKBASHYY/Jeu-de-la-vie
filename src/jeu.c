/**
 * \file jeu.c
 * Code pour le jeu
 * \author Samy MOSA
 */

#include "jeu.h"

/**
 * @brief Compte le nombre de voisins vivants de la cellule (i,j). Les bords sont cycliques.
 *
 * @param[in] i Ligne de la cellule
 * @param[in] j Colonne de la cellule
 * @param[in] g Grille contenant la cellule
 * @return Le nombre de voisins vivants de la cellule (i,j)
 */
int compte_voisins_vivants_c(int i, int j, grille g)
{
	int v = 0, l = g.nbl, c = g.nbc;
	v += est_vivante(modulo(i - 1, l), modulo(j - 1, c), g);
	v += est_vivante(modulo(i - 1, l), modulo(j, c), g);
	v += est_vivante(modulo(i - 1, l), modulo(j + 1, c), g);
	v += est_vivante(modulo(i, l), modulo(j - 1, c), g);
	v += est_vivante(modulo(i, l), modulo(j + 1, c), g);
	v += est_vivante(modulo(i + 1, l), modulo(j - 1, c), g);
	v += est_vivante(modulo(i + 1, l), modulo(j, c), g);
	v += est_vivante(modulo(i + 1, l), modulo(j + 1, c), g);

	return v;
}

/**
 * @brief Compte le nombre de voisins vivants de la cellule (i,j). Les bords ne sont pas cycliques.
 *
 * @param[in] i Ligne de la cellule
 * @param[in] j Colonne de la cellule
 * @param[in] g Grille contenant la cellule
 * @return Le nombre de voisins vivants de la cellule (i,j)
 */
int compte_voisins_vivants_nc(int i, int j, grille g)
{
	int v = 0, l = g.nbl, c = g.nbc;
	v += i > 0 && est_vivante(i - 1, j, g);						 // Top
	v += i > 0 && j > 0 && est_vivante(i - 1, j - 1, g);		 // Top-left
	v += i > 0 && j < c - 1 && est_vivante(i - 1, j + 1, g);	 // Top-right
	v += j > 0 && est_vivante(i, j - 1, g);						 // Left
	v += j < c - 1 && est_vivante(i, j + 1, g);					 // Right
	v += i < l - 1 && est_vivante(i + 1, j, g);					 // Bottom
	v += i < l - 1 && j > 0 && est_vivante(i + 1, j - 1, g);	 // Bottom-left
	v += i < l - 1 && j < c - 1 && est_vivante(i + 1, j + 1, g); // Bottom-right

	return v;
}

/**
 * @brief Fait évoluer la grille g d'un pas de temps
 *
 * @param[in,out] g Pointeur vers la grille à faire évoluer
 * @param[in,out] gc Pointeur vers une copie temporaire de la grille
 */
void evolue(grille *g, grille *gc)
{
	copie_grille(*g, *gc); // Copie temporaire de la grille
	int i, j, l = g->nbl, c = g->nbc, v;
	for (i = 0; i < l; i++)
	{
		for (j = 0; j < c; ++j)
		{
			if (est_non_viable(i, j, *g))
				continue;

			v = compte_voisins_vivants(i, j, *gc);
			if (est_vivante(i, j, *g))
			{ // Evolution d'une cellule vivante
				if (g->v)
					g->cellules[i][j]++;
				if ((v != 2 && v != 3) || (g->v && g->cellules[i][j] > 8))
					set_morte(i, j, *g);
			}
			else
			{ // Evolution d'une cellule morte
				if (v == 3)
					set_vivante(i, j, *g);
			}
		}
	}
	g->t++; // Incrémentation du temps d'évolution
	return;
}

/**
 * @brief Teste si la grille est oscillante à partir d'un certain \a délai
 *
 * @param g Grille à tester
 * @param[out] delai Adresse de retour du délai avant oscillation
 * @param[out] periode Adresse de retour de la période d'oscillation
 */
void test_oscillation(grille *g, int *delai, int *periode)
{
	grille g1, g2, g3;
	alloue_grille(g->nbl, g->nbc, &g1); // Grille de référence
	alloue_grille(g->nbl, g->nbc, &g2); // Grille de test
	alloue_grille(g->nbl, g->nbc, &g3); // Grille temporaire

	copie_grille(*g, g1);
	copie_grille(*g, g2);
	g1.v = g->v;
	g2.v = g->v;
	*delai = -1;
	*periode = -1;

	int stop = 0;
	for (int i = 0; i <= MAX_DELAI; i++)
	{
		copie_grille(g1, g2);
		for (int j = 1; j <= MAX_PERIODE; j++)
		{
			evolue(&g2, &g3);
			if (grilles_identiques(g1, g2))
			{
				*delai = i;
				*periode = j;
				stop = 1;
				break;
			}
		}
		if (stop)
			break;
		evolue(&g1, &g3);
	}
	libere_grille(&g1);
	libere_grille(&g2);
	libere_grille(&g3);
}
