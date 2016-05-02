#include "Opponent.h"
using namespace std;



Opponent::Opponent(GameField *gameField): GameObject(gameField)
{
    cout<<"\tkonstruktor Opponent"<<endl;
    code = OPPONENT_CODE;
    allegroColor=al_map_rgb(204,0,0);
}

Opponent::Opponent(GameField *gameField, int row, int column): GameObject(gameField,row,column)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
    cout<<"\tkonstruktor Opponent"<<endl;
    code = OPPONENT_CODE;
    allegroColor=al_map_rgb(204,0,0);
}

Opponent::~Opponent()
{
    cout<<"destruktor Opponent"<<endl;
}

void Opponent::displayOnConsole()
{
    cout<<"Opponent dziedziczy po"<<endl;
    GameObject::displayOnConsole();
}

void Opponent::saveToStream(ofstream *outputStream) {
    GameObject::saveToStream(outputStream);
}

void Opponent::createFromStream(ifstream *inputStream) {

}


