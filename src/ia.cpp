/**
 *@file ia.cpp
 *@brief Cpp de la classe IA
*/

#include "../lib/situation.h"

/*------------CONSTRUCTORS-&-DESTRUCTORS------------*/
IA::IA(char col)
:m_col(col)
{
}

IA::~IA()
{
    //dtor
}
/*-------------------------------------------------*/

/*----------------------METHODS--------------------*/
void IA::clear_moves()
{
    m_right_moves.clear(); /// Supprime toutes les solutions
}

void IA::add_right_move(int x, int y, int nb)
{
    m_right_moves.push_back({x,y, nb}); /// Ajout d'une solution nb: nombre de case modifie
}

/// @brief IA joue en lançant un algo.
vector <int> IA::play(int mode, vector < vector <char> > board, int affichage )
{
    vector <int> buff={0,0,0};
    situation initiale(board, m_col, 0);
    switch(mode)
    {
        case 0:
        buff=initiale.assess0(m_col); ///Aleatoire
        break;
        case 1:
        buff=initiale.assess(m_col, affichage); ///MinMax
        break;
        case 2:
        buff=initiale.assess2(m_col, affichage); ///NegaMax
        break;
        case 3:
        buff=initiale.assess3(m_col,MIN_HEURISTIC, MAX_HEURISTIC, affichage); ///AlphaBeta
        break;

    }



    buff[2]=m_col;
    clear_moves();
    return buff;
}
