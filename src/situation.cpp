#include "../lib/situation.h"
#include <windows.h>
situation::situation()
{
    //ctor
}
situation::situation(vector< vector <char> > board, char col, int depth, int x, int y)
    :game(board), m_col(col), m_depth(depth), m_x(x), m_y(y)
{
   /* vector <int> buff1= {500,-150, 30,10,10,30,-150, 500}; //source de la table d'heuristique: Université de Valenciennes
    m_heuristique.push_back(buff1);
    vector <int> buff2= {-150, -250, 0,0,0,0,-250,-150};
    m_heuristique.push_back(buff2);
    vector <int> buff3= {30,0,1,2,2,1,0,30};
    m_heuristique.push_back(buff3);
    vector <int> buff4= {10,0,2,16,16,2,0,10};
    m_heuristique.push_back(buff4);
    m_heuristique.push_back(buff4);
    m_heuristique.push_back(buff3);
    m_heuristique.push_back(buff2);
    m_heuristique.push_back(buff1);*/



}
situation::~situation()
{
    for (unsigned int i=0; i<m_succesors.size(); i++) delete m_succesors[i];
}

void situation::get_moves()
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
{
    get_moves();
    if(!m_moves.size())
    {
        return 1;
    }
    else return 0;
}


int situation::heuristique(char col)
{

    //get_moves();
    int value=0;
    int val_cases=0;
    int pions_joues=0;
    int pions_col=0;
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(m_board[i][j]!='e')
            {
                pions_joues++;
                if(m_board[i][j]==col)
                {
                    pions_col++;
                    //val_cases+=m_heuristique[i][j];
                }
            }
        }
    if(pions_joues>=50)
        value= 90*pions_col + 10*m_moves.size() + 20 * val_cases;
    else if(pions_joues >=20)
        value= 10*pions_col + 20*m_moves.size() + 90 * val_cases;
    else value= 10*pions_col + 80*m_moves.size() + 30*val_cases;

    return value;
}
vector <int> situation::assess0(char ia_col)
{
    get_all_successors();
    vector<int> result;
    srand(time(NULL));
    int i=rand() % m_succesors.size();
    result= {m_succesors[i]->m_x, m_succesors[i]->m_y};
    delete_successors();
    return result;
}
vector <int> situation::assess(char ia_col, int affichage)
{
    vector <int> result= {0,0,(ia_col==m_col? MIN_HEURISTIC : MAX_HEURISTIC)};
    vector <int> buff;

    Console* screen= screen->getInstance();
    if (m_depth!=SEARCH_DEPTH)
    {
         get_all_successors();
        if(m_succesors.size())
        {
        for (unsigned int i=0; i<m_succesors.size(); i++)
        {
            if(affichage) m_succesors[i]->display(0,(m_succesors[i]->m_depth)*SPACE_DISPLAY);

            buff=m_succesors[i]->assess(ia_col, affichage);
            if(ia_col == m_col)
            {
                if(result[2] <= buff[2])
                {
                    result=buff;
                }
            }
            else if(result[2] >= buff[2])
            {
                result=buff;

            }

        }
        if(m_depth!=0) result= {m_x,m_y,result[2]};
        }
        else result={m_x,m_y,heuristique(ia_col)};
    }
    else
    {
        result= {m_x,m_y,heuristique(ia_col)};
        screen->deleteInstance();
        delete_successors();
        return result;

    }
    screen->deleteInstance();
    delete_successors();
    return result;
}

vector <int> situation::assess2(char ia_col, int affichage)
{
    vector <int> result= {0,0, MIN_HEURISTIC};
    vector <int> buff;

    Console* screen= screen->getInstance();
    if (m_depth!=SEARCH_DEPTH)
    {
        get_all_successors();
        if(m_succesors.size())
        {
        for (unsigned int i=0; i<m_succesors.size(); i++)
        {
                if(affichage)m_succesors[i]->display(0,(m_succesors[i]->m_depth)*SPACE_DISPLAY);

            buff=m_succesors[i]->assess2(ia_col, affichage);
            if(result[2] <= buff[2])
            {
                result=buff;
            }
        }
        if(m_depth!=0) result= {m_x,m_y,-result[2]};
        }
        else result={m_x,m_y,-heuristique(ia_col)};
    }
    else
    {
        result= {m_x,m_y,-heuristique(ia_col)};
        screen->deleteInstance();
        delete_successors();
        return result;

    }
    screen->deleteInstance();
    delete_successors();
    return result;
}

void situation::get_all_successors()
{
    vector < vector <char> > board_save=m_board;
    if(is_end()) /*do nothing */;
    else
    {
        for(unsigned int i=0; i<m_moves.size(); i++)
        {
            m_board=board_save;
            for (unsigned int j=0; j<m_moves[i].size(); j++)
            {
                Place(m_moves[i][j][0], m_moves[i][j][1], m_col);
            }


            m_succesors.push_back(new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1]));
            m_board=board_save;
        }
    }
}

vector <int> situation::assess3(char ia_col, int al, int be, int affichage)
{

    vector <int> result= {0,0,(ia_col==m_col? MIN_HEURISTIC+1 : MAX_HEURISTIC-1)};
    vector <int> buff;
    int alpha= al;
    int beta= be;
    situation* buffer=NULL;

    vector < vector <char> > board_save=m_board;

    Console* screen= screen->getInstance();

    if (m_depth!=SEARCH_DEPTH)
    {
        get_moves();
        if(m_moves.size())
        {
        for(unsigned int i=0; i<m_moves.size(); i++)
        {


            if(ia_col != m_col)
            {

                if(result[2]>alpha)
                {

                    for (unsigned int j=0; j<m_moves[i].size(); j++)
                    {
                        Place(m_moves[i][j][0], m_moves[i][j][1], m_col);
                    }


                    buffer=new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1]);

                    if(affichage) buffer->display(0,(buffer->m_depth)*SPACE_DISPLAY);
                    m_board=board_save;

                    buff=buffer->assess3(ia_col,(result[2]==MAX_HEURISTIC-1 ? MIN_HEURISTIC: result[2]), beta, affichage);

                    if(result[2] >= buff[2])
                    {
                        result=buff;
                    }
                }
                //else system("pause");
            }
            else
            {

                if(result[2]<beta)
                {
                    for (unsigned int j=0; j<m_moves[i].size(); j++)
                    {
                        Place(m_moves[i][j][0], m_moves[i][j][1], m_col);
                    }

                    buffer=new situation(m_board, (m_col== 'w' ? 'b' : 'w'), m_depth+1, m_moves[i][0][0], m_moves[i][0][1]);
                    if(affichage)buffer->display(0,(buffer->m_depth)*SPACE_DISPLAY);


                    m_board=board_save;
                    buff=buffer->assess3(ia_col,alpha, (result[2]==MIN_HEURISTIC+1? MAX_HEURISTIC: result[2]), affichage);

                    if(result[2] <= buff[2])
                    {

                        result=buff;

                    }
                }
                //else system("pause");
            }


            if(m_depth!=0) result= {m_x,m_y,result[2]};
            if(buffer)
            {
                delete buffer;
                buffer=NULL;
            }
        }
        }
        else result={m_x,m_y,heuristique(ia_col)};
    }
    else
    {
        result= {m_x,m_y,heuristique(ia_col)};
        delete_successors();
        return result;

    }
    screen->deleteInstance();
    delete_successors();
    return result;
}

void situation::delete_successors()
{
    for (unsigned int i=0; i<m_succesors.size(); i++) {if(m_succesors[i])
    {
        delete(m_succesors[i]);
        m_succesors[i]=NULL;
    }
    }
}

