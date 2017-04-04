#include "game.h"
/*

*/
int main()
{
    game jeu;
    jeu.display();
    jeu.Place(4, 5, 'w');
    jeu.Getwin();
    jeu.display();
    int x,y;
    char a='b';
    while (1)
    {
        cin >> x;
        cin >> y;
        if (!jeu.Place(x,y,a))
        {

            if(a=='b') a='w';
            else a='b';
        }
        jeu.display();

    }

    jeu.display();
    return 0;
}
