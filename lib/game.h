#include "ia.h"
class game
{
    protected:

        //PROTECTED METHODS
        char get_symbol(char input);


    public:

        //CONSTRUCTORS & DESTRUCTORS
        game();
        ~game();

        //PUBLIC METHODS
        vector <vector <int> >  valid_move(int x, int y, char col);
        int Place(int x, int y, char col);
        int Getwin(IA* ia=NULL);
        void display(int x=0, int y=0);
        vector <vector <char> > m_board;
    protected:
        game (vector <vector <char> > board);
        void deplacement (int* x, int* y,int direction);

};
