#include "../lib/menu.h"
#include "../lib/situation.h"
#include <windows.h>
void menu ()
{
  int fin =1;
  while (fin)
{
cout<<"L'Othello"<<endl;
cout<<endl;
cout<<"MENU"<<endl;
cout<<endl;
cout<<"1-Jouer contre l'IA"<<endl;
cout<<"2-Jouer contre un autre joueur"<<endl;
cout<<"3-Regle du jeu"<<endl;
cout<<"4-Quitter"<<endl;
int a;





    cin>>a;
switch (a)
{
case 1:
    ///faire un autre menu avec tous les autres paramètres des IA.
    system("cls");
    break;
case 2:
    ///lancer le jeu J vs J
    system("cls");
    break;
case 3:
    ///lancer les règle s'affiche.
    system("cls");
    break;
case 4:
    fin =0;
    break;
default:
    {

    }
}
}
}
