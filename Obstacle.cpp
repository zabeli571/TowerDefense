#include "Obstacle.h"
#include "Opponent.h"
#include "Play.h"

using namespace std;


Obstacle::Obstacle(GameField *gameField): GameObject(gameField)
{
    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    hp=20;
    initialHP = hp;
    image = al_load_bitmap("bitmaps/obstacle.png");
    imageHalfHP = al_load_bitmap("bitmaps/obstacle_halfHP.png");
}

Obstacle::Obstacle(GameField *gameField, int row, int column): GameObject(gameField,row,column)//uzywany do losowania
{
    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    hp=20;
    initialHP = hp;
    image = al_load_bitmap("bitmaps/obstacle.png");
    imageHalfHP = al_load_bitmap("bitmaps/obstacle_halfHP.png");
}

Obstacle::Obstacle(GameField *gameField, ifstream *inputStream): GameObject(gameField,inputStream)
{
//    cout<<"\tkonstruktor Obstacle"<<endl;
    code = OBSTACLE_CODE;
    initialHP = hp;
    image = al_load_bitmap("bitmaps/obstacle.png");
    imageHalfHP = al_load_bitmap("bitmaps/obstacle_halfHP.png");
}

Obstacle::Obstacle(GameField *gameField, ifstream *inputStream, bool exact) : GameObject(gameField,inputStream,exact)
{
    code = OBSTACLE_CODE;
    image = al_load_bitmap("bitmaps/obstacle.png");
    imageHalfHP = al_load_bitmap("bitmaps/obstacle_halfHP.png");
}

Obstacle::~Obstacle()
{
//    cout<<"destruktor Obstacle"<<endl;
}

void Obstacle::displayOnConsole()
{
    cout<<"Obstacle dziedziczy po"<<endl;
    GameObject::displayOnConsole();
}

void Obstacle::saveToStream(ofstream *outputStream)
{
    GameObject::saveToStream(outputStream);
}

void Obstacle::move()
{
    willMove = true; //nie rusza sie
}

void Obstacle::collisionWith(GameObject *anotherObject)
{
    anotherObject->collisionWithObstacle(this);
}

void Obstacle::collisionWithOpponent(Opponent *opponent)
{
    opponent->willMove = false; //przeszkoda zatrzymuje przeciwnika
}

void Obstacle::collisionWithObstacle(Obstacle *obstacle)
{
    //brak interakcji
}

void Obstacle::collisionWithDefense(Defense *defense)
{
    //brak interakcji
}

void Obstacle::doAction(Play *play)
{
    //brak interakcji
}

void Obstacle::collisionWithBullet(Bullet *bullet)
{
    //brak interakcji
}