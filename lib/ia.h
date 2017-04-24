


#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "console.h"
#include "time.hpp"
#define SEARCH_DEPTH 3
#define MIN_HEURISTIC -10000000
#define MAX_HEURISTIC 1000000
#define BOARD_SIZE 8
#define SPACE_DISPLAY 34
using namespace std;

class IA
/**
 *@file ia.h
 *@brief Classe IA (Intelligence) Coeur de L'IA.
 *-Poss�de les solution du plateau de jeu.
 *-Jouer.
*/
{
    public:
        IA(char col='w');
        virtual ~IA();
        void clear_moves();///Supprime les solutions possibles.
        void add_right_move(int x, int y, int nb);///Ajoute une solution.
        vector <int> play(int mode=0, vector < vector <char> > board={{}}, int affichage=0 );/// Fait jouer l'IA
        ///Couleur de l'IA
        char m_col;
        ///tableau des mouvements possibles
        vector < vector<int> > m_right_moves;
    private:


};

