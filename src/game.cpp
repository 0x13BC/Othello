#include "../lib/game.h"
#include <stdlib.h>
#include <windows.h>
game::game()
{
    vector<char> buff;
    for(int i=0; i<BOARD_SIZE; i++) buff.push_back('e');
    for(int i=0; i<BOARD_SIZE; i++) m_board.push_back(buff);
    m_board[3][3]='b'; //carré de départ
    m_board[4][4]='b';
    m_board[3][4]='w';
    m_board[4][3]='w';
}

game::game(game* jeu)
:m_board(jeu->m_board)
{

}
game::game (vector< vector<char> > board)
:m_board(board)
{

}
game::~game()
{
    //dtor
}

void game::save(char play_col, int gamemode, int ia_lvl)
{
    ofstream myfile;
    string input;
    system("cls");
    cout << "Quel nom donner au fichier de sauvegarde? (sans extension)" << endl;
    cin >> input;
    input=input+".txt";
  myfile.open (input);
    for(int i=0; i<BOARD_SIZE; i++)
        for(int j=0; j<BOARD_SIZE; j++)
        {
            myfile.put(m_board[i][j]) ;
            myfile << " ";
        }
        myfile << play_col;
        if(gamemode) {
                myfile << " ";
                myfile << gamemode ;
                myfile << " ";
                myfile << ia_lvl;
        }
        myfile.close();
        cout << "Partie enregistree! A bientot!";
        Sleep(300);
}
char game::get_symbol(char input)
{
    switch (input)
    {
    case 'e':
        return 219;
    case 'b':
        return 208;
    case 'w':
        return 207;
    }
    return 0;
}
void game::display(int x, int y)
{
    Console* ecran;
    ecran->setColor(COLOR_GREEN);
    int line=1;
    char Column='A';

            //for(int k=0; k<=8; k++)std::cout<<"\xC4";
            //std::cout<<"\xBA";

    ecran= Console::getInstance();
    if(x==0 && y==0) system("cls");

    for(int i=0; i<BOARD_SIZE; i++)
    {
        ecran->gotoLigCol(2+x+i*2, y);
        std::cout<<line;
        ecran->gotoLigCol(2+x+i*2, 2+y+BOARD_SIZE*4);
        std::cout<<line;
        line++;
    }

    for(int j=0; j<BOARD_SIZE; j++)
    {
        ecran->gotoLigCol(x, 4*j+3+y);
        std::cout<<Column;
        ecran->gotoLigCol(2+x+BOARD_SIZE*2, 3+y+j*4);
       std::cout<<Column;
        Column++;
    }

    for(int i=0; i<=BOARD_SIZE; i++)
    for(int j=0; j<(BOARD_SIZE*4)-1; j++)
    {
        ecran->gotoLigCol(1+x+i*2, 2+y+j);
        std::cout<<"\xC4";
    }
    for(int i=0; i<=BOARD_SIZE*2; i++)
    for(int j=0; j<=(BOARD_SIZE); j++)
    {
        ecran->gotoLigCol(1+x+i, 1+y+j*4);
        std::cout<<"\xBA";
    }
    ecran->setColor(COLOR_DEFAULT);

    for(int i=0; i<BOARD_SIZE; i++)
        for(int j=0; j<BOARD_SIZE; j++)
        {
            ecran->gotoLigCol(2+x+2*i, 3+y+4*j);
            //switch(m_board[i][j])
            //ecran->setColor(COLOR_GREEN);
            cout << get_symbol(m_board[i][j]);
        }
        ecran->setColor(COLOR_DEFAULT);
}

int game::Place(int x, int y, char col)
{

    vector <vector <int> > direction=valid_move(x,y,col);
    if (!direction.empty())
    {
        for(unsigned int i=0; i<direction.size(); i++)
        {
            m_board[direction[i][0]][direction[i][1]]=col;
        }
        return 0;
    }
    else return 1;
}
void game::deplacement(int* x, int* y, int direction)
{
    switch (direction)
    {
    case 1:
        (*x)++;
        break;
    case 2:
        (*x)++;
        (*y)++;
        break;
    case 3:
        (*y)++;
        break;
    case -1:
        (*x)--;
        break;
    case -2:
        (*x)--;
        (*y)--;
        break;
    case -3:
        (*y)--;
        break;
    case 4:
        (*x)++;
        (*y)--;
        break;
    case -4:
        (*x)--;
        (*y)++;
        break;
    }
}
vector <vector <int> > game::valid_move(int x,int y, char col)
{
    int direction=-4;
    int base_include=0;
    int buffx= x;
    int buffy= y;
    int found=0;
    int test_void=0;
    vector <vector <int> > ret_val;
    vector <vector <int> > buff;
    vector <int> coord;
    ret_val.clear();
    coord.push_back(x);
    coord.push_back(y);
    if(m_board[x][y]=='e')
    {
        for (int i=0 ; i<BOARD_SIZE; i++ )
        {
            buff.clear();
            buffx= x;
            buffy= y;
            found=0;
            test_void=0;
            if(i==4) direction++;
            while (buffx<BOARD_SIZE && buffx>=0 && buffy<BOARD_SIZE && buffy >=0 && found==0)
            {
                deplacement(&buffx, &buffy, direction);
                coord[0]= buffx; coord[1]= buffy;

                if(buffx<BOARD_SIZE && buffx>=0 && buffy<BOARD_SIZE && buffy >=0)
                {
                    if(m_board[buffx][buffy]=='e') found=-1; //case vide, pas de chaine a ce niveau
                    else if (m_board[buffx][buffy]== col)  // case de la bonne couleur chaine trouvée ou deux pions adjacents
                    {
                        if(test_void)
                        {
                        found=1;
                        if(!base_include)
                        {
                            base_include=1;
                            coord[0]= x; coord[1]= y;
                            buff.push_back(coord);
                            coord[0]= buffx; coord[1]= buffy;
                        }
                        buff.push_back(coord);
                        // case de la couleur opposé, retenue pour changement le cas échéant
                        }
                        else found=-1;
                    }
                    else
                    {
                        test_void=1;
                        buff.push_back(coord);
                    }

                }
            }

            if(found ==1)
            {
                for (unsigned int j=0; j<buff.size(); j++ ) ret_val.push_back(buff[j]); // ajout des coord de cases a retourner à la liste
            }
            direction++;

        }
    }
    return ret_val;

}
int game::Getwin()
{


    int test=1;
    int countb=0, countw=0, counte=0;
    int buff;
    for(int i=0; i<BOARD_SIZE; i++)
        for(int j=0; j<BOARD_SIZE; j++)
        {
            if(m_board[i][j]=='e' && test==1)
            {
                if((buff=valid_move(i,j,'b').size()))
                {
                    test=0;
                }
                else if( (buff=valid_move(i,j,'w').size()))
                    {
                    test=0;
                }
            }
        }
    if (test)
    {

        for(int i=0; i<BOARD_SIZE; i++)
            for(int j=0; j<BOARD_SIZE; j++)
            {
                switch (m_board[i][j])
                {
                case 'b':
                    countb++;
                    break;
                case 'w':
                    countw++;
                    break;
                case 'e':
                    counte++;
                    break;
                }
            }
        if(countb>countw)
        {
            countb+=counte;

            cout << "Black " << get_symbol('b') << " wins " << countb << " to " << countw << endl << "Congratulations!";
            return 1;
        }
        else
        {
            countw+=counte;

            cout << "White " << get_symbol('w') << " wins " << countw << " to " << countb << endl << "Congratulations!";
            return 1;
        }

    }
    return 0;
}
