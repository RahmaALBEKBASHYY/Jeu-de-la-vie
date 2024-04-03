/**
 * \file grille.c
 * Code pour les grilles
 * \author Samy MOSA
 */

#include "grille.h"

/**
 * @brief Alloue et initalise la grille g à partir d'un fichier
 *
 * @param[in] filename Nom du fichier d'entrée
 * @param[out] g Pointeur vers la grille à initialiser
 */
void init_grille_from_file(char *filename, grille *g)
{
	FILE *pfile = NULL;
	pfile = fopen(filename, "r");
	assert(pfile != NULL);

	int i, j, n, l, c, vivantes, non_viables = 0;

	fscanf(pfile, "%d", &l);
	fscanf(pfile, "%d", &c);

	alloue_grille(l, c, g);

	fscanf(pfile, "%d", &vivantes);
	for (n = 0; n < vivantes; ++n)
	{
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_vivante(i, j, *g);
	}

	fscanf(pfile, "%d", &non_viables);
	for (n = 0; n < non_viables; ++n)
	{
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_non_viable(i, j, *g);
	}

	fclose(pfile);
	return;
}

/**
 * @brief Recopie la grille gs dans la grille gd (sans allocation)
 *
 * @param[in] gs Grille source
 * @param[out] gd Grille destination
 */
void copie_grille(grille gs, grille gd)
{
	int i, j;
	for (i = 0; i < gs.nbl; ++i)
		for (j = 0; j < gs.nbc; ++j)
			gd.cellules[i][j] = gs.cellules[i][j];
	return;
}

/**
 * @brief Alloue une grille de taille l*c, et initialise toutes les cellules à mortes
 *
 * @param[in] l Nombre de lignes
 * @param[in] c Nombre de colonnes
 * @param[out] g Pointeur vers la grille à allouer
 */
void alloue_grille(int l, int c, grille *g)
{
	g->nbl = l;
	g->nbc = c;
	g->t = 0;
	g->v = 0; // Vieillissement désactivé par défaut
	g->cellules = malloc(l * sizeof(int *));
	assert(g->cellules != NULL);
	for (int i = 0; i < l; i++)
	{
		g->cellules[i] = malloc(c * sizeof(int));
		assert(g->cellules[i] != NULL);
		for (int j = 0; j < c; j++)
			g->cellules[i][j] = 0;
	}
};

/**
 * @brief Libère complètement une grille
 *
 * @param g Grille à libérer
 */
void libere_grille(grille *g)
{
	for (int i = 0; i < g->nbl; i++)
		free(g->cellules[i]);
	free(g->cellules);
};

/**
 * @brief Testes si les grilles \a g1 et \a g2 sont identiques
 *
 * @param g1 Grille 1
 * @param g2 Grille 2
 * @return 1 si elles sont identiques, 0 sinon
 */
int grilles_identiques(grille g1, grille g2)
{
	if (g1.nbc != g2.nbc || g1.nbl != g2.nbl)
		return 0;

	for (int i = 0; i < g1.nbl; ++i)
		for (int j = 0; j < g1.nbc; ++j)
			if (g1.cellules[i][j] != g2.cellules[i][j])
				return 0;
	return 1;
}
