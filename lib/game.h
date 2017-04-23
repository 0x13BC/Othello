#include "ia.h"
class game{




    public:

        //CONSTRUCTORS & DESTRUCTORS
        char get_symbol(char input);
        game();
        ~game();

        //PUBLIC METHODS
        vector <vector <int> >  valid_move(int x, int y, char col); ///Fonction vérifiant que le mouvement est autorisé et retournant l'ensemble des cases a retourner
        int Place(int x, int y, char col); ///
        int Getwin();
        void save(char play_col, int gamemode=0, int ia_lvl=0 );
        void display(int x=0, int y=0);
        vector <vector <char> > m_board;
        game (vector <vector <char> > board);
    protected:

        void deplacement (int* x, int* y,int direction);

};
