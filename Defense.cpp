#include "Defense.h"

using namespace std;


Defense::Defense(GameField *gameField, int hp): GameObject(gameField)
{
    cout<<"\tkonstruktor Defense"<<endl;
    this->hp=hp;
    code = DEFENSE_CODE;
    allegroColor=al_map_rgb(0,153,0);
}

Defense::~Defense()
{
    cout<<"destruktor Defense"<<endl;
}

void Defense::displayOnConsole() {
    cout<<"Defense, atrybut HP: " << hp << ", dziedziczy po"<<endl;
    GameObject::displayOnConsole();
}

void Defense::saveToStream(ofstream *outputStream) {
    GameObject::saveToStream(outputStream);
    *outputStream << " " << hp;
}

void Defense::createFromStream(ifstream *inputStream) {
    GameObject::createFromStream(inputStream);
}











