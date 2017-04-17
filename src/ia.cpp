#include "../lib/ia.h"

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

vector <int> IA::play()
/** Donne la case la plus importante**/
{
    vector <int> buff={0,0,0};
    for(unsigned int i=0; i<m_right_moves.size() ; i++)// pour toute les solutions
    {
        if(m_right_moves[i][2]>buff[2]) buff=m_right_moves[i]; // Si la solution modifie le plus de case le buffer prend la solution
    }
    buff[2]=m_col; // la solution prend la couleur de l'IA
    clear_moves(); // vider les solutions
    return buff;
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

/*-------------------------------------------------*/
