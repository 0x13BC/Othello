
#include "ia.h"
class game
{
    public:
        game();
        ~game();

        int Getwin(IA* ia=NULL);
        int Place(int x, int y, char col);
        void display();

    protected:
        char get_symbol(char input);
        vector <vector <int> >  valid_move(int x, int y, char col);
        void deplacement (int* x, int* y,int direction);
        vector <vector <char> > m_board;
};
