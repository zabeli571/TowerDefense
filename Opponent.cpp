#include "Opponent.h"
#include "Obstacle.h"
#include "Defense.h"
#include "Play.h"

using namespace std;



Opponent::Opponent(GameField *gameField): GameObject(gameField)
{
    cout<<"\tkonstruktor Opponent"<<endl;
    code = OPPONENT_CODE;
    hp=10;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/opponent.png");
}

Opponent::Opponent(GameField *gameField, int row, int column): GameObject(gameField,row,column)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
    cout<<"\tkonstruktor Opponent"<<endl;
    code = OPPONENT_CODE;
    hp=10;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/opponent.png");
}

Opponent::Opponent(GameField *gameField, ifstream *inputStream): GameObject(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor Opponent"<<endl;
    code = OPPONENT_CODE;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/opponent.png");

    lastAttackTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
}

Opponent::~Opponent()
{
//    cout<<"destruktor Opponent"<<endl;
}

void Opponent::displayOnConsole()
{
    cout<<"Opponent dziedziczy po"<<endl;
    GameObject::displayOnConsole();
}

void Opponent::saveToStream(ofstream *outputStream) {
    GameObject::saveToStream(outputStream);
}

void Opponent::move()
{
    if(willMove)
    {
        x--;
    }
    willMove = true;
}

void Opponent::collisionWith(GameObject *anotherObject)
{
    anotherObject->collisionWithOpponent(this);
}

void Opponent::collisionWithObstacle(Obstacle *obstacle)
{
    std::chrono::milliseconds eventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - lastAttackTime.count() >= ATTACK_INTERVAL) //wykorzystuje roznice czasu tak jak w play::run
    {
        obstacle->hp--; //przeciwnik zabiera hp przeszkody
        lastAttackTime = eventTime;
    }
}

void Opponent::collisionWithOpponent(Opponent *opponent)
{
    //brak interakcji
}

void Opponent::collisionWithDefense(Defense *defense)
{
    std::chrono::milliseconds eventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - lastAttackTime.count() >= ATTACK_INTERVAL)
    {
        defense->hp--; //przeciwnik zabiera hp obrony
        lastAttackTime = eventTime;
    }
}

void Opponent::doAction(Play *play)
{
    //brak interakcji
}

void Opponent::collisionWithBullet(Bullet *bullet)
{
    //interakcja opisana juz w Bullet::collisionWithOpponent
}

