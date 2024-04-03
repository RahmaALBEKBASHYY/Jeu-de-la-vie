/**
 * \file jeu.h
 * Header pour le jeu
 * \author Samy MOSA
 */

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"
#define MAX_DELAI 100   /**< Limite de vérification du délai dans test_oscillation*/
#define MAX_PERIODE 100 /**< Limite de vérification de la période dans test_oscillation*/

int compte_voisins_vivants_c(int i, int j, grille g);
int compte_voisins_vivants_nc(int i, int j, grille g);
void evolue(grille *g, grille *gc);
void test_oscillation(grille *g, int *delai, int *periode);

static inline int modulo(int i, int m) { return (i + m) % m; }

// Pointeur vers la fonction à utiliser pour compter les voisins vivants
extern int (*compte_voisins_vivants)(int, int, grille);

#endif
