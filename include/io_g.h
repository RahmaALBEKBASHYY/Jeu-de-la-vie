/**
 * \file io_g.h
 * Header pour les I/O (entrées/sorties)
 * MODE Graphique
 * \author Samy MOSA
 */

#ifndef __IO_G_H
#define __IO_G_H

#include <stdio.h>
#include <math.h> // Contient M_PI utilisé dans rounded_rectangle
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>             // Contient XLookupString
#include <X11/keysym.h>            // Contient KeySyms
#include <fontconfig/fontconfig.h> // Contient FcFini()
#include "grille.h"
#include "jeu.h"

#define SIZEX 400                    /**< Largeur de la fenêtre*/
#define SIZEY 400                    /**< Hauteur de la fenêtre*/
#define LEFT_CLICK Button1           /**< Alias pour le clic gauche*/
#define RIGHT_CLICK Button3          /**< Alias pour le clic droit*/
#define MAX_FILEPATH 4096            /**< Nombre maximum de caractères pour un chemin de fichier*/
#define MIN(X, Y) (X < Y ? X : Y)    /**< Renvoie le minimum de deux nombres*/
#define BG_COLOR 0.1, 0, 0.2         /**< Couleur de fond d'écran*/
#define CELL_COLOR 1, 1, 0.8         /**< Couleur des cellules vivantes*/
#define NOT_VIABLE_COLOR 1, 0.2, 0.2 /**< Couleur des cellules non-viables*/
#define TEXTBOX_COLOR 0.1, 0.1, 0.1  /**< Couleur des zones de texte*/

void rounded_rectangle(cairo_t *cr, double x, double y, double w, double h, double r, double red, double green, double blue, double alpha);
void show_text_lines(cairo_t *cr, double x, double y, char strings[][MAX_FILEPATH], int nb_strings);
void resize_surface(cairo_surface_t *cs, Display *dpy, Window win);
void paint(grille *g, cairo_surface_t *cs);
void paint_filepath(char *filepath, cairo_surface_t *cs);
void paint_oscillation(int d, int p, cairo_surface_t *cs);
void oscillation(grille *g, cairo_surface_t *cs, Display *dpy, Window win);
void nouvelle_grille(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy, Window win);
int ask_filepath(char *filepath, cairo_surface_t *cs, Display *dpy, Window win);
void debut_jeu(grille *g, grille *gc);
#endif
