#include "ia.h"
class game
{
<<<<<<< HEAD



=======
    protected:

        //PROTECTED METHODS
        char get_symbol(char input);
>>>>>>> 76cde11a25ab0e5a89999cbf68b86e669bfccbbe


    public:

        //CONSTRUCTORS & DESTRUCTORS
<<<<<<< HEAD
        char get_symbol(char input);
=======
>>>>>>> 76cde11a25ab0e5a89999cbf68b86e669bfccbbe
        game();
        ~game();

        //PUBLIC METHODS
        vector <vector <int> >  valid_move(int x, int y, char col); ///Fonction vérifiant que le mouvement est autorisé et retournant l'ensemble des cases a retourner
        int Place(int x, int y, char col); ///
        int Getwin(IA* ia=NULL);
        void display(int x=0, int y=0);
        vector <vector <char> > m_board;
    protected:
        game (vector <vector <char> > board);
        void deplacement (int* x, int* y,int direction);

};
