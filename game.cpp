#include "game.h"
#include <stdlib.h>
#include <windows.h>
game::game()
{
    vector<char> buff;
    for(int i=0; i<8; i++) buff.push_back('e');
    for(int i=0; i<8; i++) m_board.push_back(buff);
    m_board[3][3]='b'; //carr� de d�part
    m_board[4][4]='b';
    m_board[3][4]='w';
    m_board[4][3]='w';
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
void game::display()
{
    Console* ecran;
    ecran= Console::getInstance();
    system("cls");
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
    {
        ecran->gotoLigCol(i, 3*j);
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
vector <vector <int> > game::valid_move(int x ,int y, char col)
{
    int direction=-4;
    int base_include=0;
    int buffx= x;
    int buffy= y;
    int found=0;
    vector <vector <int> > ret_val;
    vector <vector <int> > buff;
    vector <int> coord;
    coord.push_back(x);
    coord.push_back(y);
    for (int i=0 ; i<8; i++ )
    {
        buff.clear();
        buffx= x;
        buffy= y;
        found=0;
        while (buffx<8 && buffx>=0 && buffy<8 && buffy >=0 && found==0)
        {
            deplacement(&buffx, &buffy, direction);
            coord = {buffx, buffy};

            if(buffx<8 && buffx>=0 && buffy<8 && buffy >=0)
            {
            if(m_board[buffx][buffy]=='e') found=-1; //casse vide, pas de chaine a ce niveau
            else if (m_board[buffx][buffy]== col) found=1; // case de la bvonne couleur chaine trouv�e ou deux poions adjacents
            else
            {
                if(!base_include)
                {
                    base_include=1;
                    buff.push_back({x,y});
                }
                buff.push_back(coord); // case de la couleur oppos�, retenue pour changement le cas �ch�ant
            }
            }
        }
        if(found ==1) ret_val.insert(ret_val.end(), buff.begin(), buff.end()); // ajout des coord de cases a retourner � la liste
        direction++;
    }
    return ret_val;
}
int game::Getwin()
{
    int test=1;
    int countb=0, countw=0, counte=0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(m_board[i][j]=='e')
            {
                if(!valid_move(i,j,'b').empty() || !valid_move(i,j,'w').empty()) test=0;
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
            return countb;
            //cout << "Black wins " << countb << " to " << countw << endl << "Congratulations!";
        }
        else
        {
            countw+=counte;
            return countw;
            //cout << "White wins " << countw << " to " << countb << endl << "Congratulations!";
        }

}
}
