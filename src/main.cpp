#include "./lib/game.h"
/*

*/
int main()
{
    game jeu;
    jeu.display();
    IA joueur2;
    vector <int> buff;
    int x,y;
    char a='b';
    while (1)
    {

        do
        {
        cin >> x;
        cin >> y;
        jeu.display();
        }while (jeu.Place(x,y,a));

        jeu.display();
        jeu.Getwin(&joueur2);
        buff=joueur2.play();
        jeu.Place(buff[0],buff[1],buff[2]);
        jeu.display();
        jeu.Getwin();

    }

    jeu.display();
    return 0;
}
