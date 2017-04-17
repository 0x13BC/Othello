#include "../lib/game.h"
#include <stdlib.h>
#include <windows.h>

/*------------CONSTRUCTORS-&-DESTRUCTORS------------*/
game::game()
{
    /*Initialisation en memoire du plateau*/
    vector<char> buff;
    for(int i=0; i<8; i++) buff.push_back('e'); //Case vide
    for(int i=0; i<8; i++) m_board.push_back(buff);
    /*-----------------------------------*/

    m_board[3][3]='b'; //carré de départ
    m_board[4][4]='b';
    m_board[3][4]='w';
    m_board[4][3]='w';
}

game::~game()
{
    //dtor
}
/*-------------------------------------------------*/


/*----------------PROTECTED METHODS----------------*/
char game::get_symbol(char input)
/** Permet d'afficher des symboles a la place des lettres**/
{
    switch (input)
    {
    case 'e':
        return 219; //Carre blanc
    case 'b':
        return 208; // Black
    case 'w':
        return 207; // White
    }
    return 0;
}



void game::deplacement(int* x, int* y, int direction)
/** Deplace les coordonnees de 1, en fonction de la direction **/
{
    switch (direction)
    {
    case 1: //Bas
        (*x)++;
        break;
    case 2: //Bas et Droite
        (*x)++;
        (*y)++;
        break;
    case 3: //Droite
        (*y)++;
        break;
    case -4: //Haut et Droite
        (*x)--;
        (*y)++;
        break;
    case -1: //Haut
        (*x)--;
        break;
    case -2: //Haut et Gauche
        (*x)--;
        (*y)--;
        break;
    case -3: // Gauche
        (*y)--;
        break;
    case 4: //Bas et Gauche
         (*x)++;
         (*y)--;
         break;

    }
}
vector <vector <int> > game::valid_move(int x,int y, char col)
/** Renvoie un vecteur des coordonnees des mouvements corrects**/
{
    int direction=-4;   //Direction de la verification
    int base_include=0; // coordonnees initiales inclu (0:non ,1:oui)
    int buffx= x;       // x temporaire
    int buffy= y;       // y temporaire
    int found=0;        // Information case vide(-1) ou pion (1)
    int test_void=0;
    vector <vector <int> > ret_val; // valeur de retour
    vector <vector <int> > buff;    // Buffer de coordonnees buff{ coord(x,y),...}
    vector <int> coord;             // coord{x,y}
    ret_val.clear();
    coord.push_back(x);             // Push x a coord[0]
    coord.push_back(y);             // Push y a coord[1]
    if(m_board[x][y]=='e')          // Si la case est vide
    {
        for (int i=0 ; i<8; i++ )   //Pour toute les directions
        {
            buff.clear();           // Vider le buffer
            buffx= x;               // Buffx prend la valeur de départ (x)
            buffy= y;               // Buffy prend la valeur de départ (y)
            found=0;                // Valeur initial
            while (buffx<8 && buffx>=0 && buffy<8 && buffy >=0 && found==0) // Tant qu'on est dans le plateau et que rien n'est trouve
            {
                deplacement(&buffx, &buffy, direction); // Deplacer les valeurs x du Bufferx et y du Buffery par rapport à la direction
                coord[0]= buffx; coord[1]= buffy; // Insertion du bufferx et buffery dans Coord

                if(buffx<8 && buffx>=0 && buffy<8 && buffy >=0) // Si on est bien dans le plateau
                {
                    if(m_board[buffx][buffy]=='e') found=-1; // Si case vide, pas de chaine a ce niveau
                    else if (m_board[buffx][buffy]== col && test_void)  // Si case de la bonne couleur trouvée ou deux pions adjacents
                    {
                        found=1; // Case trouvee
                        if(!base_include) // Si il y a aucune base
                        {
                            base_include=1; // base defini
                            coord[0]= x; coord[1]= y; //Insere x et y dans les coordonnees
                            buff.push_back(coord);    //Push les coordonnees dans le buffer de coordonnees
                            coord[0]= buffx; coord[1]= buffy;// mettre les coordonees du buffer dans les coordonnees
                        }
                        buff.push_back(coord);// Insertion des coordonnees dans le buffer
                        // case de la couleur opposé, retenue pour changement le cas échéant
                    }
                    else // Sinon
                    {
                        test_void=1; // Case adjacente
                        buff.push_back(coord); // Push des coordonnees
                    }
                }
            }

            if(found ==1) // Si une case a ete trouvee
            {
                for (unsigned int j=0; j<buff.size(); j++ ) ret_val.push_back({buff[j][0], buff[j][1]}); // ajout des coord des cases a retourner à la liste
            }                                                                   //  x           y
            direction++; // Changer de direction
        }
    }
    return ret_val; // retourner

}
/*-------------------------------------------------*/

/*-----------------PUBLIC-METHODS------------------*/
int game::Place(int x, int y, char col)
/** Modifie les cases en fonction des mouvements valides**/
{

    vector <vector <int> > direction=valid_move(x,y,col); // case possible (vecteur{coord[x,y],...}
    if (!direction.empty())// Si il y a une case valide
    {
        for(unsigned int i=0; i<direction.size(); i++) // Pour toute les cases possibles
        {
            m_board[direction[i][0]][direction[i][1]]=col;// Met les cases valides de la même couleur
        }               //x                 y
        return 0;
    }
    else return 1;
}

int game::Getwin(IA* ia)
/** Donne les solutions pour L'IA et compte le nombre de case vide, blanche et noire **/
{
    int test=1;
    int countb=0, countw=0, counte=0;
    int buff;
        // Recherche de solution pour l'ia
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
        {
            if(m_board[i][j]=='e') // Si il y a une case vide
            {
                if((buff=valid_move(i,j,'b').size())) // Si il y a une solution pour les cases noirs
                {
                    test=0;
                    if(ia) if(ia->m_col=='b') ia->add_right_move(i,j,buff); // Donne la solution avec le nombre de case gagnee
                }
                if( (buff=valid_move(i,j,'w').size())) // Si il y a une solution pour les cases blanches
                    {
                    test=0;
                    if(ia) if(ia->m_col=='w') ia->add_right_move(i,j,buff);// Donne la solution avec le nombre de case gagnee
                }
            }
        }
    if (test)   // Si l'IA ne peut plus jouer
    {

        for(int i=0; i<8; i++) // Compte les différentes couleurs
            for(int j=0; j<8; j++)
            {
                switch (m_board[i][j])
                {
                case 'b':
                    countb++;
                    break;
                case 'w':
                    countw++;
                    break;
                case 'e':
                    counte++;
                    break;
                }
            }
        if(countb>countw)
        {
            countb+=counte;
            //return countb;
            cout << "Black wins " << countb << " to " << countw << endl << "Congratulations!";
        }
        else
        {
            countw+=counte;
            //return countw;
            cout << "White wins " << countw << " to " << countb << endl << "Congratulations!";
        }

    }
    return 0;
}

void game::display()
/** Affiche la grille **/
{
    Console* ecran;
    ecran= Console::getInstance();
    system("cls");
    for(int y=0; y<8; y++) //Affichage des colonnes
        cout<< y<<"   ";
    for(int i=0; i<8; i++)
    {
        for(int j=0; j<8; j++)
        {
            ecran->gotoLigCol((2*i)+2, 4*j);// retour a la ligne
            cout << get_symbol(m_board[i][j]);
        }cout<<"    "<< i; //Affichage des lignes
    }
}

/*-------------------------------------------------*/
