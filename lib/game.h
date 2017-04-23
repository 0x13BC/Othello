#include "ia.h"
class game{




    public:

        //CONSTRUCTORS & DESTRUCTORS

        game();
        ~game();
        game(game* jeu);
          game (vector <vector <char> > board);

        //PUBLIC METHODS
        vector <vector <int> >  valid_move(int x, int y, char col); ///Fonction vérifiant que le mouvement est autorisé et retournant l'ensemble des cases a retourner
        int Place(int x, int y, char col); ///
        int Getwin();
        void save(char play_col, int gamemode=0, int ia_lvl=0 );
        void display(int x=0, int y=0);
        vector <vector <char> > m_board;
        char get_symbol(char input);
    protected:

        void deplacement (int* x, int* y,int direction);

};
