programme crée par: Khalil Mohammad et Prigent Alan
Inspiré du jeu de Quarto © Gigamic SARL 1991 du concept de Blaise Muller.
    
commencer le: 19/11/2021 et finis le: 14/01/2022
crée pour l'évaluation de la SAE 1.1 de 1ère année
Campus 3 de l'IUT Grand Ouest Normandie


!! avant d'entrer les commande veuiller vous placer  !!
!! dans le repertoire du jeu: /quarto_project_full$       !!



Commande de compilation a effectuer si "main_affiche.o" n'existe pas:

gcc board.c -c

gcc external.c -c

gcc -Wall quarto_main.c board.o external.o -o quarto_main.o



Commande pour lancer le jeu:

./quarto_main.o 

