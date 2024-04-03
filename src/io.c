/**
 * \file io.c
 * Code pour les I/O (entrées/sorties)
 * MODE Texte
 * \author Samy MOSA
 */

#include "io.h"

/**
 * @brief Affichage d'un trait horizontal
 *
 * @param[in] c Nombre de cases
 */
void affiche_trait(int c)
{
	int i;
	for (i = 0; i < c; ++i)
		printf("|---");
	printf("|\n");
	return;
}

/**
 * @brief Affichage d'une ligne de la grille
 *
 * @param[in] c Nombre de cases
 * @param[in] ligne Ligne à afficher sous forme de tableau d'entiers
 */
void affiche_ligne(int c, int *ligne)
{
	int i, v;
	for (i = 0; i < c; ++i)
	{
		v = ligne[i];
		if (v == 0)
			printf("|   ");
		else if (v == -1)
			printf("| X ");
		else
			printf("| %d ", v);
	}
	printf("|\n");
	return;
}

/**
 * @brief Affichage d'une grille
 *
 * @param[in] g Grille à afficher
 */
void affiche_grille(grille g)
{
	int i, l = g.nbl, c = g.nbc;
	char *mode = compte_voisins_vivants == compte_voisins_vivants_c ? "Oui" : "Non";
	char *v_str = g.v ? "Oui" : "Non";
	printf("Temps d'évolution : %3d\nCyclique          : %s\nVieillissement    : %s\n\n", g.t, mode, v_str);
	affiche_trait(c);
	for (i = 0; i < l; ++i)
	{
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

/**
 * @brief Effacement d'une grille
 *
 * @param g Grille à effacer
 */
void efface_grille(grille g)
{
	printf("\e[%dF", g.nbl * 2 + 6); // Déplacement du curseur vers le haut
	printf("\e[0J");				 // Effacement de tout ce qui est en dessous du curseur
}

/**
 * @brief Demande à l'utilisateur de saisir le chemin vers une nouvelle grille puis la charge dynamiquement
 *
 * @param[out] g Pointeur vers la grille de jeu
 * @param[out] gc Pointeur vers une copie temporaire de la grille de jeu
 */
void nouvelle_grille(grille *g, grille *gc)
{
	char filepath[MAX_FILEPATH];
	printf("Entrez le chemin vers la grille : ");
	scanf("%s", filepath);
	getchar();		   // Attrape le charactère "\n"
	printf("\e[1F");   // Compensation du "\n"
	efface_grille(*g); // Effacement de l'ancienne grille
	int v = g->v;	   // Sauvegarde de l'état du vieillissement de l'ancienne grille

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
	int running = 1;
	int d, p;
	while (running)
	{
		affiche_grille(*g);
		char c = getchar();
		if (c != '\n')
			flush_stdin(); // Vide l'input buffer pour ne prendre QUE le 1er caractère

		printf("\e[1F\e[0K"); // Effacement de l'entrée clavier

		switch (c)
		{
		case 'q':
			running = 0;
			break;

		case '\n':
			evolue(g, gc);
			break;

		case 'n':
			nouvelle_grille(g, gc);
			break;

		case 'c':
			compte_voisins_vivants = compte_voisins_vivants == compte_voisins_vivants_c ? compte_voisins_vivants_nc : compte_voisins_vivants_c;
			break;

		case 'v':
			g->v = !g->v;
			break;

		case 'o':
			printf("Test d'oscillation en cours...\n");
			test_oscillation(g, &d, &p);
			printf("\e[1F\e[0K");
			if (d < 0)
				printf("Cette colonie n'a pas l'air d'osciller...\n");
			else
				printf("Cette colonie oscille\nDelai : %d, Periode : %d\n", d, p);
			printf("Appuyez sur Entrée pour continuer\n");
			flush_stdin();
			printf("\e[%dF", d < 0 ? 3 : 4);
			break;
		}
		if (c != 'n') // Si la touche est n, la grille est déjà effacée
			efface_grille(*g);
	}
}
