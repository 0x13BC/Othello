
#include "game.h"
class situation : public game
{
    public:
        situation();
        situation(vector < vector <char> > board, char col, int depth=0, int x=-1, int y=-1);
        virtual ~situation();
        char m_col;
        int m_depth;
        situation* m_predecessor;
        int m_x,m_y;
        vector <situation*> m_succesors;

        vector < vector <vector <int> > > m_moves;
        vector < vector <int> > m_heuristique;



        void get_moves();
        int is_end();
        void get_all_succesors();
        int heuristique(char col);
       //Move played that induced the situation
        vector<int> assess(char col);
        vector <int> assess2(char col);
    protected:

    private:
};
