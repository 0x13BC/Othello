#ifndef IA_H
#define IA_H
#include <iostream>
#include <vector>
#include "./console.h"

using namespace std;

class IA
{
    public:
        IA(char col='w');
        virtual ~IA();
        void clear_moves();
        void add_right_move(int x, int y, int nb);
        vector <int> play();
        void get_heuristics (int x, int y, vector < vector<int> > plateau);
        char m_col;
    private:
        vector < vector<int> > m_right_moves;

};

#endif // IA_H
