#include "../lib/situation.h"
#include <windows.h>

const vector < vector <int> >
///variable globale pour la table des valeurs strategiques des cases
m_heuristique=
{
    {500,-150, 30,10,10,30,-150, 500},
    {-150, -250, 0,0,0,0,-250,-150},
    {30,0,1,2,2,1,0,30},
    {10,0,2,16,16,2,0,10},
    {10,0,2,16,16,2,0,10},
    {30,0,1,2,2,1,0,30},
    {-150, -250, 0,0,0,0,-250,-150},
    {500,-150, 30,10,10,30,-150, 500}
};

situation::situation(vector< vector <char> > board, char col, int depth, int x, int y)
///@brief Constructeur surcharge
    :game(board), m_col(col), m_depth(depth), m_x(x), m_y(y)
{

}
situation::~situation()
{
    for (unsigned int i=0; i<m_succesors.size(); i++) delete m_succesors[i];
}

void situation::get_moves()
///@brief recupere l'ensemble des mouvs posssibles pour la situation
{
    m_moves.clear();
    vector < vector <int> > buff;
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            if(m_board[i][j]=='e')
            {

                if( (buff=valid_move(i,j,m_col)).size()>1)
                {
                    m_moves.push_back(buff);
                    m_moves[m_moves.size()-1].push_back(m_moves[m_moves.size()-1][0]);
                    m_moves[m_moves.size()-1][0]= {i,j};
                }
            }
        }
    }

}

int situation::is_end()
/// @brief verifie si la situation est de fin
{
    get_moves(); // r�cup�re les mouvs
    if(!m_moves.size())
    {
        return 1;
    }
    else return 0;
}


int situation::heuristique(char col)
/// @brief Fonction d'heuristique
{

    get_moves(); //r�cup�re les mouvements possibles
    //Variables locales
    int value=0;
    int val_cases=0;
    int pions_joues=0;
    int pions_col=0;

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(m_board[i][j]!='e') //si la case est pleine
            {
                pions_joues++; //augmente le nombre de pions en jeu
                if(m_board[i][j]==col) //si c'est la couleur demand�e
                {
                    pions_col++; //augmente les pions
                    val_cases+=m_heuristique[i][j]; //ajoute la valeur de la case
                }
            }
        }
    if(pions_joues>=50) //Fin de partie
        value= 90*pions_col + 10*m_moves.size() + 20 * val_cases;
    else if(pions_joues >=20) //milieu de partie
        value= 10*pions_col + 20*m_moves.size() + 90 * val_cases;
    else //d�but de partie
        value= 10*pions_col + 80*m_moves.size() + 30*val_cases;

    return value; //retourne l'heuristique
}
vector <int> situation::assess0(char ia_col)
///@brief Algorithme aleatoire
{
    get_all_successors(); //r�cup�re les successeurs
    vector<int> result;
    srand(time(NULL)); //initialise l'al�a
    int i=rand() % m_succesors.size(); //choisi un successeur au hasard
    result= {m_succesors[i]->m_x, m_succesors[i]->m_y};
    delete_successors(); //supprime les successeurs
    return result; //retourne le r�sultat
}
vector <int> situation::assess(char ia_col, int affichage)
///@brief Algorithme Min-Max
{
    vector <int> result= {0,0,(ia_col==m_col? MIN_HEURISTIC : MAX_HEURISTIC)}; //initialisation diff�rente selon qu'on cherhce un max ou un min
    vector <int> buff;

    Console* screen= screen->getInstance(); //ecran
    if (m_depth!=SEARCH_DEPTH) //Si on doi encore descendre dans l'arbre
    {
         get_all_successors(); //r�cup�rer les successeurs
        if(m_succesors.size()) //Si il y a des successeurs
        {
        for (unsigned int i=0; i<m_succesors.size(); i++) //pour chaque successeur
        {
            if(affichage) m_succesors[i]->display(0,(m_succesors[i]->m_depth)*SPACE_DISPLAY); //affichage si demand�

            buff=m_succesors[i]->assess(ia_col, affichage); //r�cursion
            if(ia_col == m_col) //si noeud max
            {
                if(result[2] <= buff[2]) //choisir le plus haut
                {
                    result=buff;
                }
            }
            else if(result[2] >= buff[2]) //si noeud min, choisir le plus petit
            {
                result=buff;

            }

        }
        if(m_depth!=0) result= {m_x,m_y,result[2]}; //retourner les coordon�es de jeu et la valeur heuristique
        }
        else result={m_x,m_y,heuristique(ia_col)}; // si il n'y a plus de successeurs retourner les coordon�es et l'heuristique
    }
    else
    {
        result= {m_x,m_y,heuristique(ia_col)}; //retourner les coordon�es et l'heuristique


    }
    screen->deleteInstance(); //lib�rer l'�cran
        delete_successors(); //lib�re les successeurs
        return result; //retourne le r�sultat
}

vector <int> situation::assess2(char ia_col, int affichage)
///@brief Algorithme NegaMax
{
    vector <int> result= {0,0, MIN_HEURISTIC}; //vector de r�sultat
    vector <int> buff;

    Console* screen= screen->getInstance(); //console pour l'affichage
    if (m_depth!=SEARCH_DEPTH) //si il faut encore descendre en profondeur
    {
        get_all_successors(); //r�cup�re tous les successeurs
        if(m_succesors.size()) //si il y a des successeurs
        {
        for (unsigned int i=0; i<m_succesors.size(); i++) //pour chaque successeur
        {
                if(affichage)m_succesors[i]->display(0,(m_succesors[i]->m_depth)*SPACE_DISPLAY); //afficher si il faut

            buff=m_succesors[i]->assess2(ia_col, affichage); // r�cursion
            if(result[2] <= buff[2]) //s�lection du maximum
            {
                result=buff;
            }
        }
        if(m_depth!=0) result= {m_x,m_y,-result[2]}; //retourne l'oppos� de l'heuristique
        }
        else result={m_x,m_y,-heuristique(ia_col)}; // si il n'ya plus de coups possibles retourne l'oppos� de l'heuristique
    }
    else
    {
        result= {m_x,m_y,-heuristique(ia_col)}; //retourne l'oppos� de l'heuristique


    }
   screen->deleteInstance(); //lib�re l'�cran
        delete_successors(); //lib�re les succeseurs
        return result; // retourne le r�sultat
}

void situation::get_all_successors()
///@brief Recupere tous les successeurs possibles de la situation
{
    vector < vector <char> > board_save=m_board;
    if(is_end()) /*do nothing */; //v�rifie que la sitution n'est pas une situation morte et r�cup�re tous les mouvements possibles
    else
    {
        for(unsigned int i=0; i<m_moves.size(); i++)
        {
            m_board=board_save; //r�initialize le tableau de la situation
            for (unsigned int j=0; j<m_moves[i].size(); j++)
            {
                Place(m_moves[i][j][0], m_moves[i][j][1], m_col); //Place les pions sur le plateau de la situation
            }


            m_succesors.push_back(new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1])); //cr�e une nouvelle situation
        }
    }
}

vector <int> situation::assess3(char ia_col, int al, int be, int affichage)
///@brief Fonction Alpha_Beta
{

    vector <int> result= {0,0,(ia_col==m_col? MIN_HEURISTIC+1 : MAX_HEURISTIC-1)};
    vector <int> buff;
    int alpha= al; //alpha et beta
    int beta= be;
    situation* buffer=NULL;

    vector < vector <char> > board_save=m_board; //buffer de plateau

    Console* screen= screen->getInstance(); //console pour l'affichage

    if (m_depth!=SEARCH_DEPTH) //si on dois encore plonger plus profond dans l'arbre
    {
        get_moves(); // g�n�re les mouvements possibles
        if(m_moves.size()) //Si il y a des successeurs
        {
        for(unsigned int i=0; i<m_moves.size(); i++) //pour chaque mouvement possible dans la situation
        {


            if(ia_col != m_col) //cas o� c'est un noeud Min
            {

                if(result[2]>alpha) // si le noeud Max dont il est issu peut prendre en compte la valeur
                {

                    for (unsigned int j=0; j<m_moves[i].size(); j++)
                    {
                        Place(m_moves[i][j][0], m_moves[i][j][1], m_col); //place les pions du mouvement i
                    }


                    buffer=new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1]); //g�n�re une situation

                    if(affichage) buffer->display(0,(buffer->m_depth)*SPACE_DISPLAY); //affiche la simulation si c'est demand�
                    m_board=board_save; //r�initialisation du tableau de la situation actuelle

                    buff=buffer->assess3(ia_col,(result[2]==MAX_HEURISTIC-1 ? MIN_HEURISTIC: result[2])/*d�termine la valeur de alpha a passer */, beta, affichage); //recursion

                    if(result[2] >= buff[2]) //choisis le plus petit r�sultat
                    {
                        result=buff;
                    }
                }
            }
            else //Cas d'un noeud max
            {

                if(result[2]<beta) //Si le noeud min dont il est issu peut accepter la valeur
                {
                    for (unsigned int j=0; j<m_moves[i].size(); j++)
                    {
                        Place(m_moves[i][j][0], m_moves[i][j][1], m_col); //place les pions du mouvement i
                    }

                    buffer=new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1]);// g�n�re la situation suivante
                    if(affichage)buffer->display(0,(buffer->m_depth)*SPACE_DISPLAY); //affiche si c'est requis


                    m_board=board_save; //r�initialise la situation actuelle
                    buff=buffer->assess3(ia_col,alpha, (result[2]==MIN_HEURISTIC+1? MAX_HEURISTIC: result[2]), affichage); // r�cursion

                    if(result[2] <= buff[2]) //choisis la valeur maximale
                    {

                        result=buff;

                    }
                }
            }


            if(m_depth!=0) result= {m_x,m_y,result[2]}; //remonte les coordon�es du coup et la valeur
            if(buffer) //d�truits la situation utilis�e
            {
                delete buffer;
                buffer=NULL;
            }
        }
        }
        else result={m_x,m_y,heuristique(ia_col)}; //Si il n'y a plus de successeurs on remonte l'heuristique
    }
    else //Si on a atteint la profondeur demand�e
    {
        result= {m_x,m_y,heuristique(ia_col)}; //On retourne l'heuristique demand�e
        screen->deleteInstance(); //on lib�re l'�cran
        return result; // et renvoie le r�sultat

    }
    screen->deleteInstance();//on lib�re l'�cran

    return result;// et renvoie le r�sultat
}

void situation::delete_successors()
///@brief libere la memoire prise par les successeurs
{
    for (unsigned int i=0; i<m_succesors.size(); i++) {if(m_succesors[i])
    {
        delete(m_succesors[i]); //lib�re la m�moire
        m_succesors[i]=NULL; //met a NULL
    }
    }
}

