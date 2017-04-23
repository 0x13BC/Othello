
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


 void JvsIA(int ia_lvl)
 {
     game jeu;
    jeu.display();
    IA joueur2;
    Joueur J1('b');
    vector <int> buff;
    int x=0, y=0;
    class time timer;
    while (!jeu.Getwin())
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
        jeu.Getwin();
        test->m_col=joueur2.m_col;
        test->get_moves();
        if(test->m_moves.size())
        {
        timer.start();
        buff=joueur2.play(ia_lvl, jeu.m_board);
        cout << "IA plays in " << buff[0] << "  " << buff[1]<< endl;
        cout << "COMPUTE TIME " ;
        timer.stop();
         timer.GetSec();
        system("pause");
        }
        else
        {
            cout << "IA cannot play!" <<endl;
            system("pause");
        }
        jeu.Place(buff[0],buff[1],buff[2]);
        jeu.display();

    }
 }
