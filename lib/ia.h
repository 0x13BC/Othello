


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
 *@brief Classe IA (Intelligence) Coeur de L'IA.
 *-Possede les solution du plateau de jeu.
 *-Jouer.
*/
{
    public:
        IA(char col='w');
        virtual ~IA();
        ///Supprime les solutions possibles.
        void clear_moves();
        ///Ajoute une solution.
        void add_right_move(int x, int y, int nb);
        /// Fait jouer l'IA
        vector <int> play(int mode=0, vector < vector <char> > board={{}}, int affichage=0 );
        ///Couleur de l'IA
        char m_col;
        ///tableau des mouvements possibles
        vector < vector<int> > m_right_moves;
    private:


};

