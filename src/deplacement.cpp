/**
 *@file deplacement.cpp
 *@brief Cpp de la classe Joueur
*/

#include "../lib/deplacement.h"
#include <stdlib.h>
#include <windows.h>



Joueur::Joueur(char col) : m_col(col), x(0), y(0)
{
    //cstr surchargé
}
///@brief Obtenir la couleur du joueur
char Joueur::getcol()
{
    return m_col;
}
///@brief Permet au joueur de se déplacer
int Joueur::deplacement(int* x, int* y, game* jeu, char play_col, int gamemode, int ia_lvl)
{
    Console* truc = Console::getInstance();

int test=1;
while(test!=0)
{
    truc->gotoLigCol(2+(*x),3+(*y));
    switch (truc->getInputKey())
    {
    case 'z':

          if ((*x)>0)
          {
              (*x)-=2;
              truc->gotoLigCol(2+(*x),3+(*y));
          }
        break;

    case 's':

            if ((*x)<14)
            {
                (*x)+=2;
            truc->gotoLigCol(2+(*x),3+(*y));
            }

           break;

    case 'q':

            if ((*y)>0){
                    (*y)-=4;
            truc->gotoLigCol(2+(*x),3+(*y));
            }
            break;

    case 'd':

            if ((*y)<25){
                    (*y)+=4;
            truc->gotoLigCol(2+(*x),3+(*y));

            }
            break;

    case '\r':

            test=0;
        break;
    case 'r':
        jeu->save(play_col, gamemode, ia_lvl);
        return 1;
    break;
    case 'p':
        return -1;
        break;
        }
        cout<< " ";
        Sleep(300);
        truc->gotoLigCol(2+(*x),3+(*y));
        cout<< jeu->get_symbol(jeu->m_board[*x/2][*y/4]);
        truc->gotoLigCol(2+(*x),3+(*y));

    }
    return 0;
}

