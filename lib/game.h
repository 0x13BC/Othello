#include "ia.h"
class game{
/**
 *@file game.h
 *@brief Classe Game (Jeu) Permet de contr�ler le plateau jeu
 *-Poss�de le plateau de jeu
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
        vector <vector <int> >  valid_move(int x, int y, char col); ///Fonction v�rifiant que le mouvement est autoris� et retournant l'ensemble des cases a retourner.
        int Place(int x, int y, char col); /// Place un pion a une position donn�e.
        int Getwin();/// Compte les cases vides et les pions. Permet de d�finir une victoire.
        void save(char play_col, int gamemode=0, int ia_lvl=0 );/// Sauvegarde la partie.
        void display(int x=0, int y=0);///Affiche le plateau.
        vector <vector <char> > m_board; /// Plateau de jeu.
        char get_symbol(char input); /// Permet d'afficher un symbole ASCII.
    protected:

        void deplacement (int* x, int* y,int direction); /// Modifie les coordonn�es x ou y en fonction de la direction.

};
