
#include <iostream>
#include <vector>
#include "./console.h"
#define SEARCH_DEPTH 4
#define MIN_HEURISTIC -10000000
#define MAX_HEURISTIC 1000000
using namespace std;

class IA
{
    public:
        IA(char col='w');
        virtual ~IA();
        void clear_moves();
        void add_right_move(int x, int y, int nb);
        vector <int> play(int mode=0, vector < vector <char> > board={{}} );
        void get_heuristics (int x, int y, vector < vector<int> > plateau);
        char m_col;
    private:
        vector < vector<int> > m_right_moves;

};

