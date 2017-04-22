#include "../lib/situation.h"
#include <windows.h>
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
        situation* test= new situation(jeu.m_board, a);
        test->get_moves();
        if(test->m_moves.size())
        {
        do
        {

        cin >> x;
        cin >> y;
        jeu.display();

        }while (jeu.Place(x,y,a));
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
