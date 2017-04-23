
#include<windows.h>
 #include "../lib/deplacement.h"
 void JvsJ()
{
    game jeu;

  //  vector <int> buff;
    int x=0, y=0;
Joueur J1('b');
Joueur J2('w');
int fin =1;
while (fin)
{
 situation* test= new situation(jeu.m_board, J1.getcol());
        test->get_moves();
        if(test->m_moves.size())
        {
        do
        {
        jeu.display();
        cout<<endl<<"Au tour du joueur 1"<<endl;
        J1.deplacement(&x,&y,&jeu);

        }while (jeu.Place(x/2,y/3,J1.getcol()));
        }
        else
        {

            cout<<endl<< "Player 1 cannot play!"<<endl;
            jeu.valid_move(x,y,J1.getcol());
            jeu.Getwin();
            system("pause");
            fin =0;
        }
        jeu.display();


        test->m_col=J2.getcol();
        test->get_moves();
        if(test->m_moves.size())
        {
        do
        {
        jeu.display();
        cout<<endl<<"Au tour du joueur 2"<<endl;
        J2.deplacement(&x,&y,&jeu);

        }while (jeu.Place(x/2,y/3,J2.getcol()));
        }
        else
        {


            cout<<endl<< "Player 2 cannot play!"<<endl;
            jeu.valid_move(x,y,J2.getcol());
            jeu.Getwin();
            system("pause");
            fin =0;
        }
        jeu.display();
}
 }
