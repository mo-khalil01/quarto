#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdbool.h>

#define DIMENSION 4

typedef struct save_t* save;

typedef struct board_t* board;

typedef struct piece_t* piece;

typedef struct move_t* move;


// A METTRE DANS SAVE POUR CONNAITRE L'ACTION EN COURS 
enum action{
	
         CHOOSING_PIECE,
         CHOOSING_POSITION

};

// enum de debugage afin de connaitre si des action se sont dérouler correctement
enum return_code{
                
		 SUCCESS,
         
		 POSITION,
	
		 PIECE,
};

// struct utiliser par l'ia afin de connaitre ces meilleure coup
struct move_t{
	
	int lig, col;
	
};


// struct contenant les données d'une partie
struct save_t {
	
	char save_name[10];
	board game;
	int joueur_tour;
	char joueur_name[2][10];
	enum action g_action;
	int nb_tours;
	int ai;
};


// fonction permettant de retourner une nouvelle struct save
save new_save();


// fonction permettent de désallouer la memoire de l'instance de la fonction de save
void destroy_save(save game_save);



// fonction permettant de retourner une nouvelle struct board
board new_game();


// fonction permettent de désallouer la memoire de l'instance de la fonction de board
void destroy_game(board game);



// fonction permettent de savoir si une ligne de piece de meme characteristique a été faite
bool has_winner(board game);


// fonction permettent de demander a l'utilisateur une piece
piece ask_choose_piece(save game_save);


// fonction permettant aux joueur de plaçer la piece qui fut choisie
void ask_choose_emplacement(save game_save, piece a_piece);


// demande a l'utilisateur un nom (10 character max)
void ask_player_name(save game_save, int joueur);


// demande a l'utilisateur un nom de sauvegarde (10 character max)
void ask_save_name(save game_save);


// fonction qui demande d'entrer un nombre entre deux valeur donnée
int ask_number_between(int low_value, int high_value, int number);


// demande à l'utilisateur une valeur afin de continuer
int ask_to_quit();


// fonction qui affiche les choix possible du menu
void affichage_menu();


// fonction permettent l'affichage du titre du jeu
void affichage_titre();


// fonction permettent d'afficher le jeu 
void affiche_game(board game);


// fonction permettent d'afficher le jeu 
enum return_code place_piece(board game, int line, int column, piece a_piece);


// fonction permettent de sauvegarder une partie dans un fichier
void serialise_save(save game_save);


// fonction permettent de charger une partie depuis un fichier
void load_save(save game_save);


// fonction qui renvoie la meilleure position a jouer en fonction de l'etat d'une partie et d'une piece reçu
move find_best_pos(save game_save, piece a_piece);


// fonction qui renvoie la meilleure piece a jouer en fonction de l'etat d'une partie
piece find_best_piece(save game_save);


// fonction permettent d'afficher la piece choisi en parametre
void affiche_piece_choice(piece a_piece);


#endif /*_BOARD_H_*/
