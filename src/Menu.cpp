#include "../lib/menu.h"
#include "../lib/situation.h"
#include "../lib/JvsJ.h"

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
cout<<"3-Charger une partie"<<endl;
cout<<"4-Regle du jeu"<<endl;
cout<<"5-Quitter"<<endl;
int a;
    cin>>a;
switch (a)
{
case 1:
    ///faire un autre menu avec tous les autres paramètres des IA.
    system("cls");
    menuAide();
    system("cls");
    menuTypeIA();
    JvsIA(a);
    break;
case 2:
    ///lancer le jeu J vs J
    JvsJ();
    system("cls");
    menuAide();
    break;
case 3:
    ///lancer le jeu sauvegardé
    system("cls");
    break;
case 4:
    ///Afficher les règles
    break;
case 5:
    fin =0;
    break;
default:
    system("cls");
    break;

}
}}


int menuTypeIA()
{
    cout<<"Quel type de type de jeu voulez vous faire "<<endl<<endl;
    cout<<"1- niveau (1)"<<endl;
    cout<<"2- Niveau (2)"<<endl;
    cout<<"3- Niveau (3)"<<endl;
    ///et mettre les bonus
    int a=0;
    do
    {
        cin>>a;
        if (a<=0 && a>=4) cout << "Entree invalide";
    }while (a<=0 && a>=4);
    return a;
}

void menuAide() ///bonus
{
    cout<<"QVoulez vous activer l'aide ?"<<endl<<endl;
    cout<<"1-Oui"<<endl;
    cout<<"2-Non"<<endl;
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
