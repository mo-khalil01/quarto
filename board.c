#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"





// enum definissant la taille d'une piece
enum size {
	TALL,
	SHORT
};

// enum definissant la forme d'une piece
enum shape {
	SQUARE,
	CIRCULAR
};

// enum definissant la couleur d'une piece
enum color {
	RED,
	BLUE
};

// enum definissant l'interieur d'une piece
enum top {
	HOLLOW,
	SOLID
};


// struct piece definissant une piece avec 4 characteristique
struct piece_t {
	
	enum size p_size;
	enum shape p_shape;
	enum color p_color;
	enum top p_top;
	
};


/** struct board definissant un plateau basé sur un tableau à 2 dimension  **/
struct board_t {
	
	piece tab[DIMENSION][DIMENSION];
	
};


// fonction permettant de retourner une nouvelle struct save
save new_save()
{	
	save game_save;
	
	// permet d'allouer les data en dehors de la pile de la fonction
	game_save = malloc(sizeof(struct save_t));
	
	// retourne la struct 
	return game_save;	
}

// fonction permettant de retourner une nouvelle struct board
board new_game()
{	
	board game;
	
	// permet d'allouer les data en dehors de la pile de la fonction
	game = malloc(sizeof(struct board_t));
	
	// remplis le tableau de board avec des NULL
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			game->tab[i][y] = NULL;
		}
	}
	
	// retourne la struct 
	return game;	
}



// fonction permettent de connaitre si une position du plateau est occuper
bool is_occupied(board game, int line, int column)
{
	// si la position du plateau n'est pas vide alors la place est occuper
	if (game->tab[line][column] != NULL)
	{
		return true;
	}

	// sinon la place est vide
	return false;
}



// fonction permettent de connaitre si une piece donnée est NULL
bool piece_is_null(piece a_piece)
{
	if (a_piece == NULL)
	{
		return true;
	}
	return false;
}



// fonction qui retourne true si 2 piece donné ont les meme characteristique
bool is_same_piece(piece a_piece, piece b_piece)
{
	// si une des piece est NULL alors retourne false
	if (piece_is_null(a_piece) || piece_is_null(b_piece)) return false;
	
	// si les piece ont les meme characteristique retourne true
	if (a_piece->p_size == b_piece->p_size && a_piece->p_shape == b_piece->p_shape
		&& a_piece->p_color == b_piece->p_color && a_piece->p_top == b_piece->p_top)
	{
		return true;
	}
	
	// sinon retourne false
	return false;
}

// fonction qui retourne la characteristique size d'une piece donné
enum size piece_size(piece a_piece)
{
	return a_piece->p_size;
}


// fonction qui retourne la characteristique top d'une piece donné
enum top piece_top(piece a_piece)
{
	return a_piece->p_top;
}


// fonction qui retourne la characteristique color d'une piece donné
enum color piece_color(piece a_piece)
{
	return a_piece->p_color;
}


// fonction qui retourne la characteristique shape d'une piece donné
enum shape piece_shape(piece a_piece)
{
	return a_piece->p_shape;
}


// fonction recevant 4 piece et retourne true si elle on toute au moins un characteristique commune
bool piece_min_one_chara(piece piece_a, piece piece_b, piece piece_c, piece piece_d)
{
	// regarde d'abord si la piece est NULL pour ne pas comparer du vide
	if (piece_is_null(piece_a) || piece_is_null(piece_b) || piece_is_null(piece_c) || piece_is_null(piece_d)) return false;
	
	// compare si chaque piece on l'a meme characteristique size
	if ((piece_size(piece_a) == piece_size(piece_b)) && (piece_size(piece_a) == piece_size(piece_c)) &&
		(piece_size(piece_a) == piece_size(piece_d)) && (piece_size(piece_b) == piece_size(piece_c)) &&
		(piece_size(piece_b) == piece_size(piece_b)) && (piece_size(piece_c) == piece_size(piece_d)))
	{
		return true;
	}
	// compare si chaque piece on l'a meme characteristique top
	if ((piece_top(piece_a) == piece_top(piece_b)) && (piece_top(piece_a) == piece_top(piece_c)) &&
		(piece_top(piece_a) == piece_top(piece_d)) && (piece_top(piece_b) == piece_top(piece_c)) &&
		(piece_top(piece_b) == piece_top(piece_b)) && (piece_top(piece_c) == piece_top(piece_d)))
	{
		return true;
	}
	// compare si chaque piece on l'a meme characteristique color
	if ((piece_color(piece_a) == piece_color(piece_b)) && (piece_color(piece_a) == piece_color(piece_c)) &&
		(piece_color(piece_a) == piece_color(piece_d)) && (piece_color(piece_b) == piece_color(piece_c)) &&
		(piece_color(piece_b) == piece_color(piece_b)) && (piece_color(piece_c) == piece_color(piece_d)))
	{
		return true;
	}
	// compare si chaque piece on l'a meme characteristique shape
	if ((piece_shape(piece_a) == piece_shape(piece_b)) && (piece_shape(piece_a) == piece_shape(piece_c)) &&
		(piece_shape(piece_a) == piece_shape(piece_d)) && (piece_shape(piece_b) == piece_shape(piece_c)) &&
		(piece_shape(piece_b) == piece_shape(piece_b)) && (piece_shape(piece_c) == piece_shape(piece_d)))
	{
		return true;
	}
	// si les piece n'ont aucune characteristique commune retourne false
	return false;
}



// fonction permettent de savoir si une piece donné n'a pas été placé sur le plateau
bool piece_is_free(board game, piece a_piece)
{
	// parcours le tableau du board
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			// si la piece passé est sur le plateau alors retoune false
			if (is_same_piece(a_piece, game->tab[i][y]))
			{
				return false;
			}
		}
	}
	
	// si la piece n'est pas sur le plateau retourne true
	return true;
	
}



// fonction permettent de savoir si les piece sur une meme ligne
// on au moins une characteristique commmune
bool line_same_characteristic(board game, int line)
{
	// si les piece on au moins une charactéristique commune retourne true
	if (piece_min_one_chara(game->tab[line][0], game->tab[line][1], game->tab[line][2], game->tab[line][3]))
	{
		return true;
	}
	
	// sinon retourne false
	return false;
}



// fonction permettent de savoir si les piece sur une meme colonne
// on au moins une characteristique commmune
bool column_same_characteristic(board game, int column)
{
	// si les piece on au moins une charactéristique commune retourne true
	if (piece_min_one_chara(game->tab[0][column], game->tab[1][column], game->tab[2][column], game->tab[3][column]))
	{
		return true;
	}
	
	// sinon retourne false
	return false;
}



// fonction permettent de retourner une piece a une position donné
piece get_piece(board game, int line, int column)
{
	return game->tab[line][column];
}






// fonction permettent de savoir si une ligne de piece de meme characteristique a été faite
bool has_winner(board game)
{
	
	// retourne true si chaque piece des ligne horizontal et vertical ont au moins une characteristique commune
	for (int i = 0; i < DIMENSION; i++)
	{
		if (line_same_characteristic(game, i) || column_same_characteristic(game, i))
		{
			return true;
		}
	}
	
	// retourne true si les piece diagonale on au moins une characteristique commune
	if (piece_min_one_chara(game->tab[0][0], game->tab[1][1], game->tab[2][2], game->tab[3][3]))
	{
		return true;
	}
	
	if (piece_min_one_chara(game->tab[3][0], game->tab[2][1], game->tab[1][2], game->tab[0][3]))
	{
		return true;
	}
	
	// retourne false si aucune piece d'une meme ligne n'a de characteristique commune
	return false;
}



// fonction permettent de placer une piece donné sur le plateau a une position donné
enum return_code place_piece(board game, int line, int column, piece a_piece)
{
	// si la position est occupé retourne une erreur de type position
	if (is_occupied(game, line, column) )
	{
		return POSITION;
	}
	
	// si la piece a déja été joué retourne une erreur de type piece
	if (!(piece_is_free(game, a_piece)))
	{
		return PIECE;
	}
	
	// place la piece dans le tableau a la position donné
	game->tab[line][column] = a_piece;
	
	// retourne un enum SUCCESS designant que la piece a bien été placé
	return SUCCESS;
}



// fonction permettent de renvoyer une piece de caractéristique donnés si la piece est libre
piece get_piece_from_characteristics(board game, enum size a_size, enum shape a_shape, enum color a_color,  enum top a_top)
{
	// crée une struct piece
	piece a_piece;
	
	// permet d'allouer les data en dehors de la pile de la fonction
	a_piece = malloc(sizeof(struct piece_t));
	
	// définis la piece avec les characteristique donné 
	a_piece->p_size = a_size ;
	a_piece->p_shape = a_shape;
	a_piece->p_color = a_color;
	a_piece->p_top = a_top;
	
	// renvois NULL si la piece a déja été placé sur le bord
	if (!(piece_is_free(game, a_piece)))
	{
		free(a_piece);
		return NULL;
	}
	
	// renvoie la piece crée si la piece n'a pas déja été jouer
	return a_piece;
}

// retourne vrai si la piece donné via base de 10 n'est pas jouée
piece get_piece_by_number(board game, int val)
{
	// get_piece renvoie NULL si la piece a deja été jouée
	return get_piece_from_characteristics(game, val / 8, (val % 8) / 4, (val % 4 / 2), val % 2);
}

void clear_buffer()
{
	while ((getchar()) != '\n');
}


// fonction permettent de demander a l'utilisateur une piece
piece ask_choose_piece(save game_save)
{
	/// primaire
	
	int a = 2;
	int b = 2; 
	int c = 2;
	int d = 2;
	
	piece a_piece = NULL;
	
	// affiche le nom de l'utilisateur qui dois choisir une piece
	printf("\nentrer 9 pour quitter et sauvegarder la partie\n");
	printf("%s choisiser une piece", game_save->joueur_name[game_save->joueur_tour]);
	printf("\nveuiller entrer 4 nombre de 0 ou 1:");
	
	// demande une piece tant que la piece choisie n'est pas correct
	while (a_piece == NULL)
	{
	
		// permet de n'ecrire que 4 int
		scanf("%1d", &a);
		
		if (a == 9)
		{
			return NULL;
		}
		
		scanf("%1d%1d%1d", &b, &c, &d);
		
		while (!((a == 0 || a == 1) && (b == 0 || b == 1) && (c == 0 || c == 1) && (d == 0 || d == 1)))
		{
			printf("\nveuiller reesayer avec les bonne valeur\n");
			printf("veuiller entrer 4 nombre de 0 ou 1:");
			// nettoye le buffer si l'utilisateur a trop ecris
			clear_buffer();
			
			scanf("%1d", &a);
		
			if (a == 9)
			{
				return NULL;
			}
			
			scanf("%1d%1d%1d", &b, &c, &d);
		}
		
		clear_buffer();
		
		a_piece = get_piece_from_characteristics(game_save->game, a, b, c, d);
		
		// si piece est null alors demande de réessayer
		if (a_piece == NULL)
		{
			printf("\npiece deja placer veuiller reesayer:");
		}
	}
	
	return a_piece;

}

// fonction permettant aux joueur de plaçer la piece qui fut choisie
void ask_choose_emplacement(save game_save, piece a_piece)
{
	int a = 5;
	int b = 5; 
	enum return_code valid;
	
	printf("%s choisiser un emplacement", game_save->joueur_name[game_save->joueur_tour]);
	printf("\nveuiller entrer 2 nombre de 1 a 4:");
	
	// demande de choisir un emplacement tant que l'emplacement n'est pas correct
	while (valid != SUCCESS)
	{
		scanf("%1d%1d", &a, &b);
		
		// si les valeur ne sont pas dans la zone demander alors redemende
		while (!((a >= 1 && a <= 4) && (b >= 1 && b <= 4)))
		{
			printf("\nveuiller reesayer avec les bonne valeur\n");
			printf("veuiller entrer 2 nombre de 1 a 4:");
			// nettoye le buffer si l'utilisateur a trop ecris
			clear_buffer();
			
			scanf("%1d%1d", &a, &b);
		}
		
		clear_buffer();

		// SUCCESS:  la pose c'est bien effectuer
		// POSITION: l'emplacement choisie a déja été pris
		// PIECE: piece deja pris mais normalement pas possible
		valid = place_piece(game_save->game, a-1, b-1, a_piece);
		
		if (valid != SUCCESS)
		{
			printf("\nemplacement pris veuiller reesayer:");
		}
		
	 }
}

// demande a l'utilisateur un nom de joueur (10 character max)
void ask_player_name(save game_save, int joueur)
{
	char name[10];
	scanf("%s", name);
	strcpy(game_save->joueur_name[joueur], name);
	clear_buffer();
}

// demande a l'utilisateur un nom de sauvegarde (10 character max)
void ask_save_name(save game_save)
{
	char name[10];
	scanf("%s", name);
	strcpy(game_save->save_name, name);
	clear_buffer();
}


// fonction qui demande d'entrer un nombre entre deux valeur donnée
int ask_number_between(int low_value, int high_value, int number)
{
	scanf("%1d", &number);
	
	while (!(number >= low_value && number <= high_value))
	{
		printf("\reesayer avec les bonne valeur\n");
		printf("veuiller entrer 1 nombre de %d a %d:", low_value, high_value);
		scanf("%1d", &number);
		clear_buffer();
	}
	
	clear_buffer();
	
	return number;
}

// demande à l'utilisateur une valeur afin de continuer
int ask_to_quit()
{
	int a;
	printf("entrer une valeur pour quitter:");
	scanf("%d", &a);
	clear_buffer();
	
	return a;
}



// fonction permettent de désallouer la memoire de l'instance de la fonction de board
void destroy_game(board game)
{
	free(game);
}

// fonction permettent de désallouer la memoire de l'instance de la fonction de save
void destroy_save(save game_save)
{
	free(game_save);
}

/** 
 * 
 * 
 * 
 *           affichage 
 * 
 * 
 * 
 *
**/

// fonction permettent l'affichage du titre du jeu
void affichage_titre()
{
	for (int i = 0; i < 5; i++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (i == 0 || i == 4) printf("\033[9m \033[m");
		
			else if (y == 0 || y == 39) printf("|");
			
			else if (i == 2 && y == 13) {
				printf("PROJECT-QUARTO");
				y += 13;
			}
			
			else printf("\033[95m \033[m");
		}
		printf("\n");
	}
	printf("\n");
}

// fonction qui affiche les choix possible du menu
void affichage_menu()
{
	affichage_titre();
	
	printf("Bienvenue sur Quarto project\n\n");
	printf("1: Lancer une partie\n");
	printf("2: Charger une partie\n");
	printf("3: Affronter l'invincible\n");
	printf("4: Regarder le Hall of Fame\n");
	printf("5: Explication du jeu\n");
	printf("6: Quitter le jeu\n\n");
}

// fonction qui permet de print un symbole representent une piece en fonction d'un int donné
void print_symbol(int a_piece)
{
	
	switch (a_piece)
	{
		case 0:
			printf("\033[31m□\033[m");
			break;
		case 1:
			printf("\033[31m■\033[m");
			break;
		case 2:
			printf("\033[34m□\033[m");
			break;
		case 3:
			printf("\033[34m■\033[m");
			break;
		case 4:
			printf("\033[31m◯\033[m");
			break;
		case 5:
			printf("\033[31m⬤\033[m");
			break;
		case 6:
			printf("\033[34m◯\033[m");
			break;
		case 7:
			printf("\033[34m⬤\033[m");
			break;
		case 8:
			printf("\033[31m▫\033[m");
			break;
		case 9:
			printf("\033[31m▪\033[m");
			break;
		case 10:
			printf("\033[34m▫\033[m");
			break;
		case 11:
			printf("\033[34m▪\033[m");
			break;
		case 12:
			printf("\033[31m○\033[m");
			break;
		case 13:
			printf("\033[31m●\033[m");
			break;
		case 14:
			printf("\033[34m○\033[m");
			break;
		case 15:
			printf("\033[34m●\033[m");
			break;
		default:
			printf("error");
			break;
	}													
}

// fonction permettent de print le symbole en fonction de la piece
void print_symbol_by_piece(piece a_piece)
{
	
	int val;
	
	val = a_piece->p_size * 8;
	val += a_piece->p_shape * 4;
	val += a_piece->p_color * 2;
	val += a_piece->p_top;
	

	print_symbol(val);
	
}

// fonction peremettent d'afficher le tableau
void print_board(board game, int ligne, int colonne)
{
	// affiche une barre vertical toute les 4 colonne
	if ((colonne + 1) % 4 == 0)
	{
		printf("|");
	}
	else
	{
		// affiche une barre horizontal toute les 4 ligne
		if ((ligne + 1) % 4 == 0)
		{
			printf("-");	
		}
		else
		{
			// si la position est correct est que la case est occuper alors print la piece
			if ((ligne - 1) % 4 == 0 && (colonne - 1) % 4 == 0 && is_occupied(game, (ligne - 1) / 4, (colonne - 1) / 4))
			{
				print_symbol_by_piece(game->tab[(ligne - 1) / 4][(colonne - 1) / 4]);
			}
			// sinon afiiche rien
			else
			{
				printf(" ");
			}
		}
	}
}

// retourne vrai si la piece donné via base de 10 n'est pas jouée
int piece_is_free_by_num(board game, int val)
{
	// get_piece renvoie NULL si la piece a deja été jouée
	return (get_piece_from_characteristics(game, val / 8, (val % 8) / 4, (val % 4 / 2), val % 2) != NULL);
}


// fonction permettent d'afficher les piece du jeu
void print_all_piece(board game, int ligne, int colonne)
{
	if (piece_is_free_by_num(game, ligne))
	{
		// si sur la colonne chosis
		switch (colonne)
		{
			case 25:
				printf("%d", ligne / 8);
				break;
				
			case 26:
				printf("%d", (ligne % 8) / 4);
				break;
				
			case 27:
				printf("%d", (ligne % 4) / 2);
				break;
				
			case 28:
				printf("%d", ligne % 2);
				break;
				
			case 30:
				print_symbol(ligne);
				break;
			
			default:
				printf(" ");
		}
	}
}

// fonction permettent d'afficher le jeu 
void affiche_game(board game)
{
	
	// affichage du titre
	affichage_titre();
	
	
	// affichage du plateau est des piece restante
	for (int ligne = 0; ligne < 16; ligne++)
	{
		// decale l'affichage sur la droite
		printf("    ");
		for (int colonne = 0; colonne < 40; colonne++)
		{
			// affichage du tableau sur la gauche
			if (colonne < 15 && ligne < 15)
			{
				print_board(game, ligne, colonne);
			}
			else 
			{
				// affiche d'est piece sur la droite
				if (colonne > 24 && colonne < 31)
				{
					print_all_piece(game, ligne, colonne);
				}
				else
				{
					printf(" ");		
				}
			}
			
		}
		printf("\n");
	}
	printf("\n");
}

// fonction permettent de sauvegarder une partie dans un fichier
void serialise_save(save game_save)
{
	
	// ouverture du fichier hall en mode lecture
	FILE *ft;
	int ch;
	ft = fopen("save.txt", "w");
	
	// si le fichier est null affiche une erreur
	if (ft == NULL)
	{
		fprintf(stderr, "erreur ficher:  ne s'ouvre pas\n");
		exit(1);
	}
	
	
	
	
	// remplis le fichier avec les donnée du plateau de jeu
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			
			piece a_piece = game_save->game->tab[i][y];
			 
			if (a_piece != NULL)
			{
		    	ch = a_piece->p_size;
				fputc(ch + '0', ft);
				ch = a_piece->p_shape;
				fputc(ch + '0', ft);
				ch = a_piece->p_color;
				fputc(ch + '0', ft);
				ch = a_piece->p_top;
				fputc(ch + '0', ft);
			}
			
			fputc('\n', ft);
			 
		}
	}
	
	// ecris le tour de jeu
	fprintf(ft, "%d\n", game_save->joueur_tour);
	
	// ecris le nom des joueurs
	fprintf(ft, "%s\n", game_save->joueur_name[0]);
	fprintf(ft, "%s\n", game_save->joueur_name[1]);
	
	fclose(ft);

}

// fonction permettent de charger une partie depuis un fichier
void load_save(save game_save)
{
	
	// ouverture du fichier hall en mode lecture
	FILE *ft;
	int ch;
	ft = fopen("save.txt", "r");
	
	printf("wtf1\n");
	
	// si le fichier est null affiche une erreur
	if (ft == NULL)
	{
		fprintf(stderr, "erreur ficher: ne s'ouvre pas\n");
		exit(1);
	}
	
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			printf("wtf2\n");
			ch = fgetc(ft);
			printf("%c, %d, %d\n", ch, i, y);
			if (ch == '0' || ch == '1')
			{	
				fseek(ft, -1, SEEK_CUR);	
				
				piece a_piece;
				
				a_piece = malloc(sizeof(struct piece_t));
				
				
				ch = fgetc(ft);
				a_piece->p_size = ch - '0';
				ch = fgetc(ft);
				a_piece->p_shape = ch - '0';
				ch = fgetc(ft);
				a_piece->p_color = ch - '0';
				ch = fgetc(ft);
				a_piece->p_top = ch - '0';
				
				fseek(ft, 1, SEEK_CUR);
				
				game_save->game->tab[i][y] = a_piece;
			}
		}
	}
	
	printf("wtf3\n");
	ch = fgetc(ft);
	game_save->joueur_tour = ch - '0';
	fseek(ft, 1, SEEK_CUR);	
	
	int i = 0;
	while ((ch = fgetc(ft)) != '\n')
	{ 
		game_save->joueur_name[0][i] = ch;
		i++;
	}
	game_save->joueur_name[0][i] = '\0';
	
	i = 0;
	while ((ch = fgetc(ft)) != '\n')
	{ 
		game_save->joueur_name[1][i] = ch;
		i++;
	}
	game_save->joueur_name[1][i] = '\0';

	fclose(ft);

}



///    AI     ///


int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}
	return b;
}


int min(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	return b;
}

int lol = 0;

int minimax(save game_save, int profondeur)
{
	lol++;
	

	
	if (profondeur >= 2)
	{
		if (has_winner(game_save->game) && game_save->joueur_tour)
		{
			return 1;
		}
	
		if (has_winner(game_save->game) && !(game_save->joueur_tour))
		{
			return -1;
		}
		return 0;
	}
	
	if (has_winner(game_save->game) && game_save->joueur_tour)
		{
			return 1;
		}
	
		if (has_winner(game_save->game) && !(game_save->joueur_tour))
		{
			return -1;
		}
	
	
	
	
	if (game_save->joueur_tour)
	{
		piece a_piece;
		
		int best_val = -1000;
		
		for (int lig = 0; lig < 4; lig++)
		{
			for (int col = 0; col < 4; col++)
			{
				for (int num_piece = 0; num_piece < 16; num_piece++)
				{
					if (!(is_occupied(game_save->game, lig, col) || ((a_piece = get_piece_by_number(game_save->game, num_piece)) == NULL)))
					{
						
						place_piece(game_save->game, lig, col, a_piece);
						
						game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
						
						best_val = max(best_val, minimax(game_save, profondeur+1));
						
						game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
						
						game_save->game->tab[lig][col] = NULL;
						
						if (best_val == 1)
						{
							return best_val;
						} 
					}
				}
			
			}
			
		}
		// if it's choosing place or piece do 
		
		return 0;
		
	}
	else
	{
		
		piece a_piece;
		
		int best_val = 1000;
		
		for (int lig = 0; lig < 4; lig++)
		{
			for (int col = 0; col < 4; col++)
			{
				for (int num_piece = 0; num_piece < 16; num_piece++)
				{
					if (!(is_occupied(game_save->game, lig, col) || ((a_piece = get_piece_by_number(game_save->game, num_piece)) == NULL)))
					{
				
						place_piece(game_save->game, lig, col, a_piece);
						
						game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
						
						best_val = min(best_val, minimax(game_save, profondeur+1));
						
						game_save->game->tab[lig][col] = NULL;
						
						if (best_val == -1)
						{
							return best_val;
						} 
					}
				}
			
			}
			
		}
		
		return 0;
		
	}
}


// fonction qui renvoie la meilleure position a jouer en fonction de l'etat d'une partie et d'une piece reçu
move find_best_pos(save game_save, piece a_piece)
{
	move bestmove;
	bestmove = malloc(sizeof(struct move_t));
	bestmove->lig = 5;
	bestmove->col = 5;
	int bestval = -1000;
	
	for (int i = 0; i < 4; i++)
	{
	
		for(int y = 0; y < 4; y++)
		{
			
			if (!(is_occupied(game_save->game, i, y)))
			{
				place_piece(game_save->game, i, y, a_piece);
				
				int moveval = minimax(game_save, 0);
				
				game_save->game->tab[i][y] = NULL;
				
				if (moveval > bestval)
				{
					bestmove->lig = i;
					bestmove->col = y;
					bestval = moveval;
					
				}
			}
		}
	}
	
	return bestmove;
}

// fonction qui renvoie la meilleure piece a jouer en fonction de l'etat d'une partie
piece find_best_piece(save game_save)
{
	piece a_piece;
	piece best_piece;
	
	move best_move;
	
	int best_val = 1000;
	
	for (int i = 0; i < 16; i++)
	{
		
		if ((a_piece = get_piece_by_number(game_save->game, i)) != NULL)
		{
			best_move = find_best_pos(game_save, a_piece);
			
			place_piece(game_save->game, best_move->lig, best_move->col, a_piece);
			
			int moveval = minimax(game_save, 0);
			
			game_save->game->tab[best_move->lig][best_move->col] = NULL;
			
			if (moveval < best_val)
			{
				best_piece = a_piece;
				best_val = moveval;
			}
		}	
	}
	return best_piece;
}

// fonction permettent d'afficher la piece choisi en parametre
void affiche_piece_choice(piece a_piece)
{
	
	printf("piece selectionné: %d%d%d%d ", piece_size(a_piece), piece_shape(a_piece), piece_color(a_piece), piece_top(a_piece));
	print_symbol_by_piece(a_piece);
	printf("\n");
}
