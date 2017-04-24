
#include "../lib/situation.h"
class Joueur
/**
 *@brief Classe Joueur. Utilisateur du jeu.
 *-Possede les coordonnees du curseur et la couleur des pions.
*/

{

    private:
        /// Couleur du joueur.
char m_col;

public:
    /// Position du curseur x.
    int* x;
    /// Position du curseur y.
    int* y;
    /// Permet de deplacer le curseur du joueur.

    int deplacement(int*x,int*y,game* jeu, char play_col, int gamemode=0, int ia_lvl=0);
    /// Donne la couleur.
    char getcol();
    Joueur(char col);

};

