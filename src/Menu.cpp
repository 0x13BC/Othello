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
    menuDifficulte();
    system("cls");
    menuTypeIA();
    break;
case 2:
    ///lancer le jeu J vs J
    system("cls");
    menuDifficulte();
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

void menuTypeIA()
{
    cout<<"Quel type de type de jeu voulez vous faire "<<endl<<endl;
    cout<<"1- niveau (1)"<<endl;
    cout<<"2- Niveau (2)"<<endl;
    cout<<"3- Niveau (3)"<<endl;
    ///et mettre les bonus
    int a;
    cin>>a;
    switch(a)
    {
    case 1:
        system("cls");
        break;
    case 2:
        system("cls");
        break;
    case 3:
        system("cls");
        break;
    }
}

void menuDifficulte() ///bonus
{
    cout<<"Quel type de difficulter voulez vous?"<<endl<<endl;
    cout<<"1-facile"<<endl;
    cout<<"2-normal"<<endl;
    int a;
    cin>>a;
    switch(a)
    {
case 1:
    ///implémenter le jeu en voyant les cases ou le joueur peut jouer
    system("cls");
    break;
case 2:
    ///implémenter le jeu sans que je joueur voit les cases ou il peut jouer
    system("cls");
    break;

    }

}
