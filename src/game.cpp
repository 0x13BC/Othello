#include "../lib/game.h"
#include <stdlib.h>
#include <windows.h>
game::game()
{
    vector<char> buff;
    for(int i=0; i<8; i++) buff.push_back('e');
    for(int i=0; i<8; i++) m_board.push_back(buff);
    m_board[3][3]='b'; //carré de départ
    m_board[4][4]='b';
    m_board[3][4]='w';
    m_board[4][3]='w';
}

game::game (vector< vector<char> > board)
:m_board(board)
{

}
game::~game()
{
    //dtor
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
    ecran= Console::getInstance();
    if(x==0 && y==0) system("cls");
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            ecran->gotoLigCol(x+2*i, y+3*j);
            //switch(m_board[i][j])
            //ecran->setColor(COLOR_GREEN);
            cout << get_symbol(m_board[i][j]);
        }
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
        for (int i=0 ; i<8; i++ )
        {
            buff.clear();
            buffx= x;
            buffy= y;
            found=0;
            test_void=0;
            if(i==4) direction++;
            while (buffx<8 && buffx>=0 && buffy<8 && buffy >=0 && found==0)
            {
                deplacement(&buffx, &buffy, direction);
                coord[0]= buffx; coord[1]= buffy;

                if(buffx<8 && buffx>=0 && buffy<8 && buffy >=0)
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
    IA* ia=NULL;

    int test=1;
    int countb=0, countw=0, counte=0;
    int buff;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(m_board[i][j]=='e')
            {
                if((buff=valid_move(i,j,'b').size()))
                {
                    test=0;
                    if(ia) if(ia->m_col=='b') ia->add_right_move(i,j,buff);
                }
                if( (buff=valid_move(i,j,'w').size()))
                    {
                    test=0;
                    if(ia) if(ia->m_col=='w') ia->add_right_move(i,j,buff);
                }
            }
        }
    if (test)
    {

        for(int i=0; i<8; i++)
            for(int j=0; j<8; j++)
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
            //return countb;
            cout << "Black wins " << countb << " to " << countw << endl << "Congratulations!";
        }
        else
        {
            countw+=counte;
            //return countw;
            cout << "White wins " << countw << " to " << countb << endl << "Congratulations!";
        }

    }
    return 0;
}
