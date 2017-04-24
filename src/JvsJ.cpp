

 #include "../lib/deplacement.h"
 #include<windows.h>
int JvsJ(vector< vector <char> > board, char col_start)
{
    game* buffin= (board.size()? new game(board):new game());
    game jeu(buffin);
  //  vector <int> buff;
    int x=0, y=0;
    Joueur J1(col_start);
    Joueur J2((col_start=='b'? 'w':'b'));
    while (1)
    {
        situation* test= new situation(jeu.m_board, J1.getcol());
        test->get_moves();
        if(test->m_moves.size())
        {
        do
        {
        jeu.display();
        cout<<endl<<"Au tour du joueur 1"<<endl;
        if(J1.deplacement(&x,&y,&jeu, J1.getcol()))return 1;

        }while (jeu.Place(x/2,y/4,J1.getcol()));
        }
        else
        {

            cout<<endl<< "Player 1 cannot play!"<<endl;
            jeu.valid_move(x,y,J1.getcol());

            system("pause");
        }
        jeu.display();
        if(jeu.Getwin()) return 0;

        test->m_col=J2.getcol();
        test->get_moves();
        if(test->m_moves.size())
        {
        do
        {
        jeu.display();
        cout<<endl<<"Au tour du joueur 2"<<endl;
        if(J2.deplacement(&x,&y,&jeu, J2.getcol(),0)) return 1;

        }while (jeu.Place(x/2,y/4,J2.getcol()));
        }
        else
        {


            cout<<endl<< "Player 2 cannot play!"<<endl;
            jeu.valid_move(x,y,J2.getcol());

            system("pause");
        }
        jeu.display();
        if(jeu.Getwin()) return 0;
}
 }


 int JvsIA(vector< vector <char> > board, int ia_lvl, char play_col, int affichage)
 {
    game* buffin= (board.size()>1? new game(board):new game());
    game jeu(buffin);
    jeu.display();
    Joueur J1(play_col);
    IA joueur2((play_col=='b' ? 'w': 'b'));

    vector <int> buff;
    int x=0, y=0;
    class time timer;
    while (1)
    {
        situation* test= new situation(jeu.m_board, J1.getcol());
        test->get_moves();
        if(test->m_moves.size())
        {
        do
        {

        if(J1.deplacement(&x,&y,&jeu,J1.getcol(), 1, ia_lvl)) return 1;

        }while (jeu.Place(x/2,y/4,J1.getcol()));
        }
        else
        {
            cout<< "Player cannot play!";
            system("pause");
        }

        jeu.display();
        if(jeu.Getwin()) return 0;
        test->m_col=joueur2.m_col;
        test->get_moves();
        if(test->m_moves.size())
        {
        timer.start();


        buff=joueur2.play(ia_lvl, jeu.m_board, affichage);
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
        if(jeu.Getwin()) return 0;
    }

 }
