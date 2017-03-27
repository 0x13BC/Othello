#include <iostream>
#include <vector>
#include "console.h"
using namespace std;
class game
{
    public:
        game();
        ~game();

        int Getwin();
        int Place(int x, int y, char col);
        void display();

    protected:
        char get_symbol(char input);
        vector <vector <int> >  valid_move(int x, int y, char col);
        void deplacement (int* x, int* y,int direction);
        vector <vector <char> > m_board;
};
