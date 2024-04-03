/**
 * \file io.h
 * Header pour les I/O (entrées/sorties)
 * MODE Texte
 * \author Samy MOSA
 */

#ifndef __IO_H
#define __IO_H

#include "grille.h"
#include "jeu.h"

#define MAX_FILEPATH 4096 /**< Nombre maximum de caractères pour un chemin de fichier*/

void affiche_trait(int c);
void affiche_ligne(int c, int *ligne);
void affiche_grille(grille g);
void efface_grille(grille g);
void nouvelle_grille(grille *g, grille *gc);
void debut_jeu(grille *g, grille *gc);

/** Vide l'input buffer (Ne pas appeler cette fonction si le buffer est vide)*/
static inline void flush_stdin() { for (char c = getchar(); c != '\n' && c != EOF; c = getchar()); }

#endif
