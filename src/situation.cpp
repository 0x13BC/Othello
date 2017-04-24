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
    get_moves(); // récupère les mouvs
    if(!m_moves.size())
    {
        return 1;
    }
    else return 0;
}


int situation::heuristique(char col)
/// @brief Fonction d'heuristique
{

    get_moves(); //récupère les mouvements possibles
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
                if(m_board[i][j]==col) //si c'est la couleur demandée
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
    else //début de partie
        value= 10*pions_col + 80*m_moves.size() + 30*val_cases;

    return value; //retourne l'heuristique
}
vector <int> situation::assess0(char ia_col)
///@brief Algorithme aleatoire
{
    get_all_successors(); //récupère les successeurs
    vector<int> result;
    srand(time(NULL)); //initialise l'aléa
    int i=rand() % m_succesors.size(); //choisi un successeur au hasard
    result= {m_succesors[i]->m_x, m_succesors[i]->m_y};
    delete_successors(); //supprime les successeurs
    return result; //retourne le résultat
}
vector <int> situation::assess(char ia_col, int affichage)
///@brief Algorithme Min-Max
{
    vector <int> result= {0,0,(ia_col==m_col? MIN_HEURISTIC : MAX_HEURISTIC)}; //initialisation différente selon qu'on cherhce un max ou un min
    vector <int> buff;

    Console* screen= screen->getInstance(); //ecran
    if (m_depth!=SEARCH_DEPTH) //Si on doi encore descendre dans l'arbre
    {
         get_all_successors(); //récupérer les successeurs
        if(m_succesors.size()) //Si il y a des successeurs
        {
        for (unsigned int i=0; i<m_succesors.size(); i++) //pour chaque successeur
        {
            if(affichage) m_succesors[i]->display(0,(m_succesors[i]->m_depth)*SPACE_DISPLAY); //affichage si demandé

            buff=m_succesors[i]->assess(ia_col, affichage); //récursion
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
        if(m_depth!=0) result= {m_x,m_y,result[2]}; //retourner les coordonées de jeu et la valeur heuristique
        }
        else result={m_x,m_y,heuristique(ia_col)}; // si il n'y a plus de successeurs retourner les coordonées et l'heuristique
    }
    else
    {
        result= {m_x,m_y,heuristique(ia_col)}; //retourner les coordonées et l'heuristique


    }
    screen->deleteInstance(); //libérer l'écran
        delete_successors(); //libère les successeurs
        return result; //retourne le résultat
}

vector <int> situation::assess2(char ia_col, int affichage)
///@brief Algorithme NegaMax
{
    vector <int> result= {0,0, MIN_HEURISTIC}; //vector de résultat
    vector <int> buff;

    Console* screen= screen->getInstance(); //console pour l'affichage
    if (m_depth!=SEARCH_DEPTH) //si il faut encore descendre en profondeur
    {
        get_all_successors(); //récupère tous les successeurs
        if(m_succesors.size()) //si il y a des successeurs
        {
        for (unsigned int i=0; i<m_succesors.size(); i++) //pour chaque successeur
        {
                if(affichage)m_succesors[i]->display(0,(m_succesors[i]->m_depth)*SPACE_DISPLAY); //afficher si il faut

            buff=m_succesors[i]->assess2(ia_col, affichage); // récursion
            if(result[2] <= buff[2]) //sélection du maximum
            {
                result=buff;
            }
        }
        if(m_depth!=0) result= {m_x,m_y,-result[2]}; //retourne l'opposé de l'heuristique
        }
        else result={m_x,m_y,-heuristique(ia_col)}; // si il n'ya plus de coups possibles retourne l'opposé de l'heuristique
    }
    else
    {
        result= {m_x,m_y,-heuristique(ia_col)}; //retourne l'opposé de l'heuristique


    }
   screen->deleteInstance(); //libère l'écran
        delete_successors(); //libère les succeseurs
        return result; // retourne le résultat
}

void situation::get_all_successors()
///@brief Recupere tous les successeurs possibles de la situation
{
    vector < vector <char> > board_save=m_board;
    if(is_end()) /*do nothing */; //vérifie que la sitution n'est pas une situation morte et récupère tous les mouvements possibles
    else
    {
        for(unsigned int i=0; i<m_moves.size(); i++)
        {
            m_board=board_save; //réinitialize le tableau de la situation
            for (unsigned int j=0; j<m_moves[i].size(); j++)
            {
                Place(m_moves[i][j][0], m_moves[i][j][1], m_col); //Place les pions sur le plateau de la situation
            }


            m_succesors.push_back(new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1])); //crée une nouvelle situation
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
        get_moves(); // génère les mouvements possibles
        if(m_moves.size()) //Si il y a des successeurs
        {
        for(unsigned int i=0; i<m_moves.size(); i++) //pour chaque mouvement possible dans la situation
        {


            if(ia_col != m_col) //cas où c'est un noeud Min
            {

                if(result[2]>alpha) // si le noeud Max dont il est issu peut prendre en compte la valeur
                {

                    for (unsigned int j=0; j<m_moves[i].size(); j++)
                    {
                        Place(m_moves[i][j][0], m_moves[i][j][1], m_col); //place les pions du mouvement i
                    }


                    buffer=new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1]); //génère une situation

                    if(affichage) buffer->display(0,(buffer->m_depth)*SPACE_DISPLAY); //affiche la simulation si c'est demandé
                    m_board=board_save; //réinitialisation du tableau de la situation actuelle

                    buff=buffer->assess3(ia_col,(result[2]==MAX_HEURISTIC-1 ? MIN_HEURISTIC: result[2])/*détermine la valeur de alpha a passer */, beta, affichage); //recursion

                    if(result[2] >= buff[2]) //choisis le plus petit résultat
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

                    buffer=new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1]);// génère la situation suivante
                    if(affichage)buffer->display(0,(buffer->m_depth)*SPACE_DISPLAY); //affiche si c'est requis


                    m_board=board_save; //réinitialise la situation actuelle
                    buff=buffer->assess3(ia_col,alpha, (result[2]==MIN_HEURISTIC+1? MAX_HEURISTIC: result[2]), affichage); // récursion

                    if(result[2] <= buff[2]) //choisis la valeur maximale
                    {

                        result=buff;

                    }
                }
            }


            if(m_depth!=0) result= {m_x,m_y,result[2]}; //remonte les coordonées du coup et la valeur
            if(buffer) //détruits la situation utilisée
            {
                delete buffer;
                buffer=NULL;
            }
        }
        }
        else result={m_x,m_y,heuristique(ia_col)}; //Si il n'y a plus de successeurs on remonte l'heuristique
    }
    else //Si on a atteint la profondeur demandée
    {
        result= {m_x,m_y,heuristique(ia_col)}; //On retourne l'heuristique demandée
        screen->deleteInstance(); //on libère l'écran
        return result; // et renvoie le résultat

    }
    screen->deleteInstance();//on libère l'écran

    return result;// et renvoie le résultat
}

void situation::delete_successors()
///@brief libere la memoire prise par les successeurs
{
    for (unsigned int i=0; i<m_succesors.size(); i++) {if(m_succesors[i])
    {
        delete(m_succesors[i]); //libère la mémoire
        m_succesors[i]=NULL; //met a NULL
    }
    }
}

