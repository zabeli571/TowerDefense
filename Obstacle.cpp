#include "Obstacle.h"
#include "Opponent.h"
using namespace std;


Obstacle::Obstacle(GameField *gameField): GameObject(gameField)
{
    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    hp=20;
    allegroColor=al_map_rgb(192,192,192);
}

Obstacle::Obstacle(GameField *gameField, int row, int column): GameObject(gameField,row,column)//uzywany do losowania
{
    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    hp=20;
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

void Obstacle::move() {
    willMove = true;
}

void Obstacle::collisionWith(GameObject *anotherObject) {
    anotherObject->collisionWithObstacle(this);
}

void Obstacle::collisionWithOpponent(Opponent *opponent) {
    opponent->willMove = false;
}

void Obstacle::collisionWithObstacle(Obstacle *obstacle) {

}

void Obstacle::collisionWithDefense(Defense *defense) {

}

void Obstacle::doAction() {

}











