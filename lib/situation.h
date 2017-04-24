
#include "game.h"
class situation : public game
///@brief Simulation d'une situation de jeu
{
    public:
        situation(vector < vector <char> > board, char col, int depth=0, int x=-1, int y=-1);
        virtual ~situation();
        ///Couleur du joueur devant jouer a la situation
        char m_col;
        ///Profondeur de parcours de la situation
        int m_depth;
        ///Coordonées du dernier coup joue
        int m_x,m_y;
        ///Tableau de situation pouvant succeder a celle-ci
        vector <situation*> m_succesors;
        ///Tableau des mouvements disponibles a cette situation
        vector < vector <vector <int> > > m_moves;
        //vector < vector <int> > m_heuristique;

        void get_moves();
        int is_end();
        void get_all_successors();
        void delete_successors();
        int heuristique(char col);

       //Move played that induced the situation
       vector <int> assess0(char ia_col);
        vector<int> assess(char col, int affichage);
        vector <int> assess2(char col, int affichage);
        vector <int> assess3(char ia_col, int al=MIN_HEURISTIC, int be=MAX_HEURISTIC, int affichage=0);

};
