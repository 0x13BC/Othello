/**
 *@file deplacement.h
 *@brief Classe Joueur. Utilisateur du jeu.
 *-Possède les coordonnées du curseur et la couleur des pions.
*/

#include "../lib/situation.h"
class Joueur
{

    private:
char m_col; /// Couleur du joueur.

public:
    int* x;/// Position du curseur x.
    int* y;/// Position du curseur y.
    int deplacement(int*x,int*y,game* jeu, char play_col, int gamemode=0, int ia_lvl=0);/// Permet de déplacer le curseur du joueur.
    char getcol();/// Donne la couleur.
    Joueur(char col);

};

