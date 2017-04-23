
#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "console.h"
#include "time.hpp"
#define SEARCH_DEPTH 7
#define MIN_HEURISTIC -10000000
#define MAX_HEURISTIC 1000000
#define BOARD_SIZE 8
#define SPACE_DISPLAY 25
using namespace std;

class IA
{
    public:
        IA(char col='w');
        virtual ~IA();
        void clear_moves();
        void add_right_move(int x, int y, int nb);
        vector <int> play(int mode=0, vector < vector <char> > board={{}}, int affichage=0 );
        void get_heuristics (int x, int y, vector < vector<int> > plateau);
        ///Couleur de l'IA
        char m_col;
        ///tableau des mouvements possibles
        vector < vector<int> > m_right_moves;
    private:


};

