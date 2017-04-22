
#include "../lib/deplacement.h"
#include <windows.h>
/*

*/
int main()
{
    game jeu;
    jeu.display();
    IA joueur2;
    Joueur J1('b');
    vector <int> buff;
    int x=0,y=0;

    while (1)
    {
        situation* test= new situation(jeu.m_board, J1.getcol());
        test->get_moves();
        if(test->m_moves.size())
        {
        do
        {

        J1.deplacement(&x,&y,&jeu);
        }while (jeu.Place(x/2,y/3,J1.getcol()));
        }
        else
        {
            cout<< "Player cannot play!";
            system("pause");
        }

        jeu.display();
        jeu.Getwin(&joueur2);
        test->m_col=joueur2.m_col;
        test->get_moves();
        if(test->m_moves.size())
        {
        buff=joueur2.play(1, jeu.m_board);
        cout << "IA plays in " << buff[0] << "  " << buff[1]<< endl;
        system("pause");
        }
        else
        {
            cout << "IA cannot play!" <<endl;
            system("pause");
        }
        jeu.Place(buff[0],buff[1],buff[2]);
        jeu.display();
        jeu.Getwin();

    }

    jeu.display();
    return 0;
}
