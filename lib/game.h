#include "./ia.h"
class game
{
    protected:

        //ATTRIBUTS
        vector <vector <char> > m_board;

        //PROTECTED METHODS
        char get_symbol(char input);
        void deplacement (int* x, int* y,int direction);
        vector <vector <int> >  valid_move(int x, int y, char col);

    public:

        //CONSTRUCTORS & DESTRUCTORS
        game();
        ~game();

        //PUBLIC METHODS
        int Place(int x, int y, char col);
        int Getwin(IA* ia=NULL);
        void display();


};
