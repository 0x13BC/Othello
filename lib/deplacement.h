
#include "../lib/situation.h"
class Joueur
{
    private:
char m_col;

public:
    int* x;
    int* y;
    void deplacement(int*x,int*y,game* jeu);
    char getcol();
    Joueur(char col);

};

