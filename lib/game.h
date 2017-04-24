#include "ia.h"
class game
/**
 *@brief Classe Game (Jeu) Permet de controler le plateau jeu
 *-Possede le plateau de jeu
 *-Permet de sauvegarder/ charger une partie.
 *-Afficher le jeu
*/
{



    public:

        //CONSTRUCTORS & DESTRUCTORS

        game();
        ~game();
        ///Constructeur par copie
        game(game* jeu);
        ///Constructeur surcharge
          game (vector <vector <char> > board);

        //PUBLIC METHODS
        ///Fonction verifiant que le mouvement est autorise et retournant l'ensemble des cases a retourner.
       vector <vector <int> >  valid_move(int x, int y, char col);
       /// Place un pion a une position donnee et retourne les pions concernes
        int Place(int x, int y, char col);
        /// Compte les cases vides et les pions. Permet de definir une victoire.
        int Getwin();
        /// Sauvegarde la partie.
        void save(char play_col, int gamemode=0, int ia_lvl=0 );
        ///Affiche le plateau.
        void display(int x=0, int y=0);
        /// Plateau de jeu.
        vector <vector <char> > m_board;
        /// Permet d'afficher le symbole ASCII en fonction de la couleur entree
        char get_symbol(char input);
    protected:
    /// Modifie les coordonnees x ou y en fonction de la direction.
        void deplacement (int* x, int* y,int direction);

};
