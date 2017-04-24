#include "ia.h"
class game{
/**
 *@file game.h
 *@brief Classe Game (Jeu) Permet de contrôler le plateau jeu
 *-Possède le plateau de jeu
 *-Permet de sauvegarder/ charger une partie.
 *-Afficher le jeu
*/



    public:

        //CONSTRUCTORS & DESTRUCTORS

        game();
        ~game();
        game(game* jeu);
          game (vector <vector <char> > board);

        //PUBLIC METHODS
        vector <vector <int> >  valid_move(int x, int y, char col); ///Fonction vérifiant que le mouvement est autorisé et retournant l'ensemble des cases a retourner.
        int Place(int x, int y, char col); /// Place un pion a une position donnée.
        int Getwin();/// Compte les cases vides et les pions. Permet de définir une victoire.
        void save(char play_col, int gamemode=0, int ia_lvl=0 );/// Sauvegarde la partie.
        void display(int x=0, int y=0);///Affiche le plateau.
        vector <vector <char> > m_board; /// Plateau de jeu.
        char get_symbol(char input); /// Permet d'afficher un symbole ASCII.
    protected:

        void deplacement (int* x, int* y,int direction); /// Modifie les coordonnées x ou y en fonction de la direction.

};
