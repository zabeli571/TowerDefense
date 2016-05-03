#include "Obstacle.h"
using namespace std;


Obstacle::Obstacle(GameField *gameField): GameObject(gameField)
{
    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    allegroColor=al_map_rgb(192,192,192);
}

Obstacle::Obstacle(GameField *gameField, int row, int column): GameObject(gameField,row,column)//uzywany do losowania
{
    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    allegroColor=al_map_rgb(192,192,192);
}

Obstacle::Obstacle(GameField *gameField, ifstream *inputStream): GameObject(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    allegroColor=al_map_rgb(192,192,192);
}

Obstacle::~Obstacle()
{
    cout<<"destruktor Obstacle"<<endl;
}

void Obstacle::displayOnConsole() {
    cout<<"Obstacle dziedziczy po"<<endl;
    GameObject::displayOnConsole();
}

void Obstacle::saveToStream(ofstream *outputStream) {
    GameObject::saveToStream(outputStream);
}