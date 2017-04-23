
#include "../lib/situation.h"
class Joueur
{
    private:
char m_col;

public:
    int* x;
    int* y;
    int deplacement(int*x,int*y,game* jeu, char play_col, int gamemode=0, int ia_lvl=0);
    char getcol();
    Joueur(char col);

};

