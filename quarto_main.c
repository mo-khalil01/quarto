#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#include "board.h"
#include "external.h"

/*

programme crée par: Khalil Mohammad et Prigent Alan
Inspiré du jeu de Quarto © Gigamic SARL 1991 du concept de Blaise Muller.
    
commencer le: 19/11/2021 et finis le: 14/01/2022
crée pour l'évaluation de la SAE 1.1 de 1ère année
Campus 3 de l'IUT Grand Ouest Normandie

*/

enum state { 
	MENU, // menu
	NGAM, // nouvelle partie
	LGAM, // charge partie
	IAGM, // partie vs ia
	HALL, // hall of fame
	CMTJ, // comment jouer 
	QUIT  // quitter
};

// variable de selection de page
enum state launcher;

// variable coontenant les donné de la partie
save game_save;

// fonction menu permettent de se deplacer dans les option du programme
void menu()
{
	int menu_choice = 0;
	
	// affichage du menu
	system("clear");
	affichage_menu();
	printf("Selection: ");
	
	// demande de choisir 
	menu_choice = ask_number_between(1, 6, menu_choice);
	
	// switch pour chaque selection dans le menu
	switch (menu_choice)
	{
		
		// changement de l'enum pour nouvelle partie joueur contre joueur
		case 1:
			launcher = NGAM;
			game_save = new_save();
			break;
			
		// changement de l'enum pour nouvelle partie joueur contre ia
		case 2:
			launcher = LGAM;
			game_save = new_save();
			break;
			
		// changement de l'enum pour chargement partie
		case 3:
			launcher = IAGM;
			game_save = new_save();
			break;
		
		// changement de l'enum pour l'affichage du hall of fame
		case 4:
			launcher = HALL;
			break;
		
		// changement de l'enum pour l'affichage des instruction de jeu
		case 5:
			launcher = CMTJ;
			break;
			
		// changement de l'enum pour quitter le programme
		case 6:
			launcher = QUIT;
			break;
		
		// si autre quitter ( normalement pas possible )
		default:
			launcher = QUIT;
	
	}
	
}



// fonction de jeu 2 joueurs
void player_vs_player()
{
		
	system("clear");
	affiche_game(game_save->game);
	
	game_save->nb_tours = 0;
	
	// tant que la partie n'a pas de gagnant et que le plateau n'est pas vide
    while (!(has_winner(game_save->game)) && game_save->nb_tours < 16)
    {
		
		// demande au joueur en cours de choisir une piece
		piece a_piece = ask_choose_piece(game_save);
		
		// sauvegarde de la partie puis quitte si l'utilisateur la demander
		if (a_piece == NULL)
		{
			serialise_save(game_save);
			break;
		}
		
		// changement du joueur en cours 
		game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
		
		// affiche la piece selectionner 
		affiche_piece_choice(a_piece);
		
		// demande au joueur en cours de choisir un emplacement sur le plateau
		ask_choose_emplacement(game_save, a_piece);
		
		// +1 au nombre de tours
		game_save->nb_tours++;
		
		// affichage de la partie
		system("clear");	
		affiche_game(game_save->game);
		
	}
	
	// affichage du gagnant de la partie en fonction de qui à jouer en dernier
	printf("le joueur %d a gagné\n", game_save->joueur_tour);
	
	if (!(!(has_winner(game_save->game)) && game_save->nb_tours < 16))
	{
		// reecrie les score du hall of fame
		hall_write(game_save->joueur_name[game_save->joueur_tour]);
	}
	
	// desalloue de la memoire les variable de jeu
	destroy_game(game_save->game);
	destroy_save(game_save);
	
	printf("suppression du plateau et sortie\n");
	
	sleep(3);
	
	// retour au menu
	launcher = MENU;
}



// fonction de jeu 1 joueur
void player_vs_ia()
{
		
	system("clear");
	affiche_game(game_save->game);
	
	game_save->nb_tours = 0;
	game_save->ai = 1;
	
	piece a_piece;
	
	// tant que la partie n'a pas de gagnant et que le plateau n'est pas vide
    while (!(has_winner(game_save->game)) && game_save->nb_tours < 16)
    {
		
		// demande au joueur de choisir une piece
		if (game_save->joueur_tour == 0) 
		{
			a_piece = ask_choose_piece(game_save);
		}
		// demande a l'ia de choisir une piece
		else 
		{
			a_piece = find_best_piece(game_save);
		}
		
		// sauvegarde de la partie puis quitte si l'utilisateur la demander
		if (a_piece == NULL)
		{
			serialise_save(game_save);
			break;
		}
		
		// affiche la piece selectionner par l'ia
		if (game_save->joueur_tour == 1)
		{
			affiche_piece_choice(a_piece);
		}
		
		// changement du joueur en cours 
		game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
		
		// demande au joueur de choisir un emplacement sur le plateau
		if (game_save->joueur_tour == 0) 
		{
			ask_choose_emplacement(game_save, a_piece);
		}
		// demande a l'ia de choisir un emplacement sur le plateau
		else
		{
			move best_move = find_best_pos(game_save, a_piece);
			place_piece(game_save->game, best_move->lig, best_move->col, a_piece);
		}
		
		// +1 au nombre de tours
		game_save->nb_tours++;
	
		// affichage de la partie
		system("clear");
		affiche_game(game_save->game);
		
	}
	
	// affichage du gagnant de la partie en fonction de qui à jouer en dernier
	printf("le joueur %d a gagné\n", game_save->joueur_tour);
	
	if (!(!(has_winner(game_save->game)) && game_save->nb_tours < 16))
	{
		// reecrie les score du hall of fame
		hall_write(game_save->joueur_name[game_save->joueur_tour]);
	}
	
	// desalloue de la memoire les variable de jeu
	destroy_game(game_save->game);
	destroy_save(game_save);
	
	printf("suppression du plateau et sortie\n");
	
	sleep(3);
	
	// retour au menu
	launcher = MENU;
}


// fonction permettent de lancer une nouvelle partie
void launch_game()
{
	
	system("clear");
	affichage_titre();
	
	// creation d'une sauvegarde vide
	game_save->game = new_game();
	
	printf("choisiser un nom de partie (10 caractère max) :");
	ask_save_name(game_save);
	
	// demande a l'utilisateur d'entrer un nom de 10 character max
	printf("choisiser un nom pour joueur 1 (10 caractère max) :");
	ask_player_name(game_save, 0);
	
	// lancement d'une partie 2 joueur
	if (launcher == NGAM)
	{
		printf("choisiser un nom pour joueur 2 (10 caractère max) :");
		ask_player_name(game_save, 1);
		
		player_vs_player();
	}
	// lancement d'une partie contre l'ia
	else
	{
		
		player_vs_ia();
		
	}
	
}

// fonction permettent de charger et lancer une partie depuis un fichier
void load_game()
{
	// chargement de la partie 
	game_save->game = new_game();
	load_save(game_save);
	
	// lancement d'une partie joueur contre joueur
	player_vs_player();
	
}

// fonction permettent d'afficher les score des joueurs
void hall_of_fame()
{
	
	system("clear");
	affichage_titre();
	
	// affiche le contenue du hall of fame
	hall_read("hall_of_fame.txt");
    
    // demande a l'utilisateur une valeur quelconque pour continuer
    ask_to_quit();
	
	// retour au menu
	launcher = MENU;
}

// fonction permettent d'afficher les instruction du jeu
void how_to_play()
{
	system("clear");
	affichage_titre();
	
	// affiche le contenue du how to play 
	hall_read("how_to_play.txt");
    
    // demande a l'utilisateur une valeur quelconque pour continuer
    ask_to_quit();
	
	// retour au menu
	launcher = MENU;
}


int main(int argc, char **argv)
{
	// variable bool de la boucle principale
	bool run = true;
	
	// direction menu au demmarage
	launcher = MENU;
	
	// boucle principale du programme
	while (run)
	{
		printf("a\n");
		
			
		switch (launcher)
		{
			
			// lancement du menu
			case 0: 
				menu();
				break;
			
			// lancement d'une partie joueur vs joueur
			case 1: 
				launch_game();
				break;
			
			// lancement d'une partie joueur vs ai
			case 2: 
				launch_game();
				break;
			
			// chargement d'une partie
			case 3: 
				load_game();
				break;
			
			// lancement du hall of fame
			case 4: 
				hall_of_fame();
				break;
			
			// lancement des instruction de jeux
			case 5: 
				how_to_play();
				break;
			
			// fin du programme
			case 6: 
				run = false;;
				break;
			
			default:
				run = false;;
				break;
		}
		
	}
	
	system("clear");
	return 0;
}

