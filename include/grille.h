/**
 * \file grille.h
 * Header pour les grilles
 * \author Samy MOSA
 */

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**Structure de données grille*/
typedef struct
{
    int nbl;        /**< Nombre de lignes*/
    int nbc;        /**< Nombre de colonnes*/
    int t;          /**< Temps d'évolution*/
    int v;          /**< Booléen pour le vieillissement des cellules*/
    int **cellules; /**< Tableau de tableaux de cellules*/
} grille;

void init_grille_from_file(char *filename, grille *g);
void copie_grille(grille gs, grille gd);
void alloue_grille(int l, int c, grille *g);
void libere_grille(grille *g);
int grilles_identiques(grille g1, grille g2);

static inline void set_vivante(int i, int j, grille g) { g.cellules[i][j] = 1; }
static inline void set_morte(int i, int j, grille g) { g.cellules[i][j] = 0; }
static inline void set_non_viable(int i, int j, grille g) { g.cellules[i][j] = -1; }

static inline int est_vivante(int i, int j, grille g) { return g.cellules[i][j] > 0; }
static inline int est_morte(int i, int j, grille g) { return g.cellules[i][j] == 0; }
static inline int est_non_viable(int i, int j, grille g) { return g.cellules[i][j] == -1; }

#endif
