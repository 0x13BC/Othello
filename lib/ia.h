#ifndef IA_H
#define IA_H
#include <iostream>
#include <vector>
#include "./console.h"

using namespace std;

class IA
{
    private:

        //ATTRIBUTS
        vector < vector<int> > m_right_moves;

    public:

        //PUBLIC ATTRIBUTS
        char m_col;

        //CONSTRUCTORS & DESTRUCTORS
        IA(char col='w');
        ~IA();

        //METHODS
        void clear_moves();
        void add_right_move(int x, int y, int nb);
        vector <int> play();
        void get_heuristics (int x, int y, vector < vector<int> > plateau);



};

#endif // IA_H
