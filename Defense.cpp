#include "Defense.h"

using namespace std;


Defense::Defense(GameField *gameField, int hp): GameObject(gameField)
{
    cout<<"\tkonstruktor Defense"<<endl;
    this->hp=hp;
    code = DEFENSE_CODE;
    allegroColor=al_map_rgb(0,153,0);
}

Defense::Defense(GameField *gameField, ifstream *inputStream): GameObject(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
    cout<<"\tkonstruktor Defense"<<endl;
    code = DEFENSE_CODE;
    allegroColor=al_map_rgb(0,153,0);
}

Defense::~Defense()
{
    cout<<"destruktor Defense"<<endl;
}

void Defense::displayOnConsole() {
    cout<<"Defense, dziedziczy po"<<endl;
    GameObject::displayOnConsole();
}

void Defense::saveToStream(ofstream *outputStream) {
    GameObject::saveToStream(outputStream);
}

void Defense::move() {
    willMove = true;
}

void Defense::collisionWith(GameObject *anotherObject) {
    anotherObject->collisionWithDefense(this);
}

void Defense::collisionWithOpponent(Opponent *opponent) {

}

void Defense::collisionWithObstacle(Obstacle *obstacle) {

}

void Defense::collisionWithDefense(Defense *defense) {

}

void Defense::doAction() {

}











