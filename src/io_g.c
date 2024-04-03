/**
 * \file io_g.c
 * Code pour les I/O (entrées/sorties)
 * MODE Graphique
 * \author Samy MOSA
 */

#include "io_g.h"

/**
 * @brief Affiche un rectangle avec des coins arrondis
 *
 * @param cr Pointeur vers le masque cairo
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param w Largeur (en pixels)
 * @param h Hauteur (en pixels)
 * @param r	Rayon de courbure des coins
 * @param red Taux de rouge (flottant entre 0 et 1)
 * @param green Taux de vert (flottant entre 0 et 1)
 * @param blue Taux de bleu (flottant entre 0 et 1)
 * @param alpha Taux de transparence (flottant entre 0 et 1)
 */
void rounded_rectangle(cairo_t *cr, double x, double y, double w, double h, double r, double red, double green, double blue, double alpha)
{
	double degrees = M_PI / 180.0;

	cairo_new_sub_path(cr);
	cairo_arc(cr, x + w - r, y + r, r, -90 * degrees, 0 * degrees);
	cairo_arc(cr, x + w - r, y + h - r, r, 0 * degrees, 90 * degrees);
	cairo_arc(cr, x + r, y + h - r, r, 90 * degrees, 180 * degrees);
	cairo_arc(cr, x + r, y + r, r, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);

	cairo_set_source_rgba(cr, red, green, blue, alpha);
	cairo_fill_preserve(cr);
	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_set_line_width(cr, 1);
	cairo_stroke(cr);
}

/**
 * @brief Affiche les chaînes de caractères les unes en dessous des autres
 *
 * @param cr Pointeur vers le masque cairo
 * @param x Coordonnée x
 * @param y Coordonnée y
 * @param strings Tableau contenant les chaînes de caractères à afficher
 * @param nb_strings Nombre de chaînes de caractères à afficher
 */
void show_text_lines(cairo_t *cr, double x, double y, char strings[][MAX_FILEPATH], int nb_strings)
{
	cairo_font_extents_t fe;
	cairo_font_extents(cr, &fe);
	y += fe.ascent;
	for (int i = 0; i < nb_strings; i++)
	{
		cairo_move_to(cr, x, y);
		cairo_show_text(cr, strings[i]);
		y += fe.height;
	}
}

/**
 * @brief Redimensionne la surface cairo aux dimensions de la fenêtre \a win sur l'écran \a dpy
 *
 * @param cs Pointeur vers la surface cairo
 * @param dpy Pointeur vers l'écran
 * @param win Pointeur vers la fenêtre
 */
void resize_surface(cairo_surface_t *cs, Display *dpy, Window win)
{
	Window root_return;
	int x_return, y_return;
	unsigned int width, height, border_width_return, depth_return;
	XGetGeometry(dpy, win, &root_return, &x_return, &y_return, &width, &height, &border_width_return, &depth_return);
	cairo_xlib_surface_set_size(cs, width, height);
}

/**
 * @brief Affiche la grille \a g sur la surface \a cs
 *
 * @param g Pointeur vers la grille
 * @param cs Pointeur vers la surface
 */
void paint(grille *g, cairo_surface_t *cs)
{
	// Création du masque cairo
	cairo_t *cr = cairo_create(cs);

	// Background
	cairo_set_source_rgb(cr, BG_COLOR);
	cairo_paint(cr);

	// Affichage de la grille
	double width = cairo_xlib_surface_get_width(cs), height = cairo_xlib_surface_get_height(cs);
	double line_width = 1, sizecell = MIN(width / g->nbc, height / g->nbl);
	double x_offset = (width - g->nbc * sizecell) / 2;
	double y_offset = (height - g->nbl * sizecell) / 2;
	for (int i = 0; i < g->nbl; i++)
		for (int j = 0; j < g->nbc; j++)
		{
			if (est_morte(i, j, *g))
				continue;

			if (est_non_viable(i, j, *g))
				cairo_set_source_rgb(cr, NOT_VIABLE_COLOR);
			else
				cairo_set_source_rgba(cr, CELL_COLOR, (9 - g->cellules[i][j]) / 8.0);

			cairo_rectangle(cr, j * sizecell + line_width + x_offset, i * sizecell + line_width + y_offset, sizecell - line_width * 2, sizecell - line_width * 2);
			cairo_fill(cr);
		}

	// Affichage du texte
	cairo_text_extents_t te;
	cairo_font_extents_t fe;
	double font_size = 0.03 * MIN(width, height);
	double box_x = 10, box_y = 10;
	double padding = 10;
	char strings[3][MAX_FILEPATH];
	sprintf(strings[0], "Temps d'évolution : %3d", g->t);
	sprintf(strings[1], "Cyclique          : %s", compte_voisins_vivants == compte_voisins_vivants_c ? "Oui" : "Non");
	sprintf(strings[2], "Vieillissement    : %s", g->v ? "Oui" : "Non");

	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, font_size);
	cairo_text_extents(cr, "Temps d'évolution : ....", &te);
	cairo_font_extents(cr, &fe);

	rounded_rectangle(cr, box_x, box_y, te.width + padding * 2, fe.ascent + fe.height * 2 + padding * 2, 5, TEXTBOX_COLOR, 0.9);
	cairo_set_source_rgb(cr, 1, 1, 1);
	show_text_lines(cr, box_x + padding, box_y + padding, strings, 3);

	// Destruction du masque cairo
	cairo_destroy(cr);
}

/**
 * @brief Demande à l'utilisateur d'entrer le chemin vers une nouvelle grille
 *
 * @param[out] filepath Chaîne de caractères où sera retourné le chemin
 * @param cs Pointeur vers la surface cairo
 * @param dpy Pointeur vers l'écran
 * @param win Pointeur vers la fenêtre
 * @return 0 si l'utilisateur appuie sur entrée, 1 s'il appuie sur Escape
 */
int ask_filepath(char *filepath, cairo_surface_t *cs, Display *dpy, Window win)
{
	XEvent e;
	KeySym keysym;
	int i, index = 0;
	while (1)
	{
		paint_filepath(filepath, cs);
		XNextEvent(dpy, &e);
		switch (e.type)
		{
		case Expose:
			if (e.xexpose.count < 1)
				resize_surface(cs, dpy, win);
			break;

		case KeyPress:
			i = XLookupString((XKeyEvent *)&e, filepath + index, 2, &keysym, 0);
			switch (keysym)
			{
			case XK_Return:
				filepath[index] = '\0';
				return 0;

			case XK_Escape:
				return 1;

			case XK_BackSpace:
				index = index == 0 ? 0 : index - 1;
				break;

			default:
				index += i;
				break;
			}
			filepath[index] = '\0';
			break;
		}
	}
}

/**
 * @brief Affiche l'écran de demande du chemin vers la nouvelle grille
 *
 * @param cs Pointeur vers la surface cairo
 * @param filepath Chaîne de caractères contenant le chemin
 */
void paint_filepath(char *filepath, cairo_surface_t *cs)
{
	// Création du masque cairo
	cairo_t *cr = cairo_create(cs);

	// Background
	cairo_set_source_rgb(cr, BG_COLOR);
	cairo_paint(cr);

	// Texte
	double width = cairo_xlib_surface_get_width(cs), height = cairo_xlib_surface_get_height(cs);
	double padding = 10;
	double box_x, box_y;
	cairo_font_extents_t fe;
	cairo_text_extents_t te;

	// Chemin de fichier
	double filepath_font_size = 0.03 * MIN(width, height);
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, filepath_font_size);
	cairo_font_extents(cr, &fe);

	box_x = width * 0.1;
	box_y = height / 2 - fe.ascent - padding;
	rounded_rectangle(cr, box_x, box_y, width * 0.8, fe.ascent + padding * 2, 5, TEXTBOX_COLOR, 0.9);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_text_extents(cr, filepath, &te);
	cairo_move_to(cr, width * 0.5 - te.width / 2, height / 2);
	cairo_show_text(cr, filepath);

	// Titre
	double header_font_size = 0.03 * MIN(width, height);
	char *header = "ENTREZ LE CHEMIN VERS LA NOUVELLE GRILLE";
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_set_font_size(cr, header_font_size);
	cairo_font_extents(cr, &fe);

	cairo_set_source_rgb(cr, 1, 1, 1);
	cairo_text_extents(cr, header, &te);
	cairo_move_to(cr, width * 0.5 - te.width / 2, box_y - fe.height);
	cairo_show_text(cr, header);

	// Destruction du masque cairo
	cairo_destroy(cr);
}

/**
 * @brief Affiche l'écran du test d'oscillations
 *
 * @param d Entier représentant le délai avant oscillation
 * @param p Entier représentant la période d'oscillation
 * @param cs Pointeur vers la surface cairo
 */
void paint_oscillation(int d, int p, cairo_surface_t *cs)
{
	// Création du masque cairo
	cairo_t *cr = cairo_create(cs);

	// Background
	cairo_set_source_rgb(cr, BG_COLOR);
	cairo_paint(cr);

	// Texte
	double width = cairo_xlib_surface_get_width(cs), height = cairo_xlib_surface_get_height(cs);
	double padding = 10;
	double box_x, box_y, box_w, box_h;
	cairo_font_extents_t fe;
	cairo_text_extents_t te;
	char strings[3][MAX_FILEPATH];
	int i;

	double font_size = 0.03 * MIN(width, height);
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
	cairo_set_font_size(cr, font_size);

	if (d < 0)
	{
		sprintf(strings[0], "Cette colonie n'a pas l'air d'osciller...");
		cairo_text_extents(cr, strings[0], &te);
		i = 1;
	}
	else
	{
		sprintf(strings[0], "Cette colonie oscille");
		sprintf(strings[1], "Délai : %d, Période : %d", d, p);
		cairo_text_extents(cr, strings[1], &te);
		i = 2;
	}
	sprintf(strings[i], "Cliquez pour continuer");
	cairo_font_extents(cr, &fe);

	box_w = te.width + padding * 2;
	box_h = fe.ascent + fe.height * i + padding * 2;
	box_x = (width - box_w) / 2;
	box_y = (height - box_h) / 2;
	rounded_rectangle(cr, box_x, box_y, box_w, box_h, 5, TEXTBOX_COLOR, 0.9);
	cairo_set_source_rgb(cr, 1, 1, 1);
	show_text_lines(cr, box_x + padding, box_y + padding, strings, i + 1);

	// Titre
	char *header = "TEST D'OSCILLATION";
	cairo_select_font_face(cr, "Courier", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
	cairo_font_extents(cr, &fe);
	cairo_text_extents(cr, header, &te);
	cairo_move_to(cr, width * 0.5 - te.width / 2, box_y - fe.height);
	cairo_show_text(cr, header);

	// Destruction du masque cairo
	cairo_destroy(cr);
}

/**
 * @brief Lance le test d'oscillation de la grille et affiche graphiquement le résultat
 *
 * @param g Grille à tester
 * @param cs Surface Cairo
 * @param dpy Ecran
 * @param win Fenêtre
 */
void oscillation(grille *g, cairo_surface_t *cs, Display *dpy, Window win)
{
	int d, p;
	test_oscillation(g, &d, &p);

	XEvent e;
	while (1)
	{
		paint_oscillation(d, p, cs);
		XNextEvent(dpy, &e);
		switch (e.type)
		{
		case Expose:
			if (e.xexpose.count < 1)
				resize_surface(cs, dpy, win);
			break;

		case ButtonPress:
			if (e.xbutton.button == LEFT_CLICK || e.xbutton.button == RIGHT_CLICK)
				return;
		}
	}
}

/**
 * @brief Demande à l'utilisateur de saisir une grille puis charge la nouvelle grille
 *
 * @param g Pointeur vers la grille de jeu
 * @param gc Pointeur vers une copie temporaire de la grille de jeu
 * @param cs Pointeur vers la surface cairo
 * @param dpy Pointeur vers l'écran
 * @param win Pointeur vers la fenêtre
 */
void nouvelle_grille(grille *g, grille *gc, cairo_surface_t *cs, Display *dpy, Window win)
{
	char filepath[MAX_FILEPATH] = "";
	if (ask_filepath(filepath, cs, dpy, win) != 0)
		return;

	// Sauvegarde de l'état du vieillissement de l'ancienne grille
	int v = g->v;

	// Libération des anciennes grilles
	libere_grille(g);
	libere_grille(gc);

	// Initialisation des nouvelles grilles
	init_grille_from_file(filepath, g);
	alloue_grille(g->nbl, g->nbc, gc);

	// Restauration de l'état du viellissement
	g->v = v;
	gc->v = v;
}

/**
 * @brief Débute le jeu
 *
 * @param[in,out] g Pointeur vers la grille de jeu
 * @param[in,out] gc Pointeur vers une copie temporaire de la grille de jeu
 */
void debut_jeu(grille *g, grille *gc)
{
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;

	// Initialisation de l'écran
	if (!(dpy = XOpenDisplay(NULL)))
	{
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr = DefaultScreen(dpy);
	rootwin = RootWindow(dpy, scr);

	win = XCreateSimpleWindow(dpy, rootwin, 0, 0, SIZEX, SIZEY, 0, 0, 0);

	XStoreName(dpy, win, "Jeu de La Vie");
	XSelectInput(dpy, win, ExposureMask | ButtonPressMask | KeyPressMask);
	XMapWindow(dpy, win);

	// Pour la fermeture propre avec la croix
	Atom wmDeleteWindow = XInternAtom(dpy, "WM_DELETE_WINDOW", 1);
	XSetWMProtocols(dpy, win, &wmDeleteWindow, 1);

	// Création de la surface cairo
	cairo_surface_t *cs = cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// Boucle d'événements
	int running = 1;
	while (running)
	{
		if (!XPending(dpy)) // Pour éviter l'effet stroboscope quand on redimensionne la fenêtre
			paint(g, cs);
		XNextEvent(dpy, &e);
		switch (e.type)
		{
		case ClientMessage:
			if (e.xclient.data.l[0] == wmDeleteWindow)
				running = 0;
			break;

		case Expose:
			if (e.xexpose.count < 1)
				resize_surface(cs, dpy, win);
			break;

		case ButtonPress:
			switch (e.xbutton.button)
			{
			case LEFT_CLICK:
				evolue(g, gc);
				break;

			case RIGHT_CLICK:
				running = 0;
				break;
			}
			break;

		case KeyPress:
			switch (XLookupKeysym((XKeyEvent *)&e, 0))
			{
			case XK_c:
				compte_voisins_vivants = compte_voisins_vivants == compte_voisins_vivants_c ? compte_voisins_vivants_nc : compte_voisins_vivants_c;
				break;

			case XK_v:
				g->v = !g->v;
				break;

			case XK_n:
				nouvelle_grille(g, gc, cs, dpy, win);
				break;

			case XK_o:
				oscillation(g, cs, dpy, win);
				break;

			case XK_Return:
				evolue(g, gc);
				break;

			case XK_Escape:
				running = 0;
				break;
			}
			break;
		}
	}

	XCloseDisplay(dpy); // Fermeture de l'écran

	// Gestion de mémoire
	cairo_surface_destroy(cs);
	cairo_debug_reset_static_data();
	FcFini();
}
