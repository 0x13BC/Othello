
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
    m_right_moves.clear(); // Supprime toutes les solutions
}

void IA::add_right_move(int x, int y, int nb)
{
    m_right_moves.push_back({x,y, nb}); // Ajout d'une solution nb: nombre de case modifie
}


void IA::get_heuristics(int x, int y, vector < vector<int> > plateau)
{
    vector <int> values;
    //int buff;
    for(unsigned int i=0; i<m_right_moves.size() ; i++)
    {
        // fonction heuristique complexe pour plus tard
        // pour l'instant c'est jamais appelé
    }

}
vector <int> IA::play(int mode, vector < vector <char> > board )
{
    vector <int> buff={0,0,0};
    if(!mode)
    {
    for(unsigned int i=0; i<m_right_moves.size() ; i++)
    {
        if(m_right_moves[i][2]>buff[2]) buff=m_right_moves[i];
    }
    }
    else
    {
    situation initiale(board, m_col, 0);
    buff=initiale.assess2(m_col);
    }

    buff[2]=m_col;
    clear_moves();
    return buff;
}
