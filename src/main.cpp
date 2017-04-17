#include "../lib/game.h"
/*

*/
int main()
{

    /** Initialisation **/
    game jeu;                       //Instanciation du Jeu par défaut
    IA joueur2;                     //Instanciation de L'IA (Blanc)
    vector <int> buff;              //Buffer {x,y,couleur}
    int x,y;                        // [0;7]
    char a='b';                     // Couleur du joueur b: Black et w: White

    jeu.display();                  //Affichage du plateau

    /** Boucle de jeu **/
    while (1)
    {

        do                          // Boucle de saisie: Fait cette boucle...
        {
        cin >> x;                   // Saisie ligne
        cin >> y;                   // Saisie colonne
        jeu.display();              //Affichage du plateau --Suppr
        }while (jeu.Place(x,y,a));  // Tant que la saisie du joueur est incorrecte

        jeu.display();              //Affichage du plateau
        jeu.Getwin(&joueur2);       // L'IA prend les solutions
        buff=joueur2.play();        // L'IA compare les solutions et joue
        jeu.Place(buff[0],buff[1],buff[2]); // Le choix de l'ia est placé
        jeu.display(); // Affichage de la grille
        jeu.Getwin();  // Vérification de win

    }
    /**Fin de la boucle de jeu **/

    jeu.display();
    return 0;
}
