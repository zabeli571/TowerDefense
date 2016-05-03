#include "Defense.h"
#include "Opponent.h"
#include "Play.h"
#include "Bullet.h"
using namespace std;


Defense::Defense(GameField *gameField, int hp): GameObject(gameField)
{
    cout<<"\tkonstruktor Defense"<<endl;
    this->hp=hp;
    code = DEFENSE_CODE;
    allegroColor=al_map_rgb(0,153,0);
    image = al_load_bitmap("bitmaps/defense.png");
}

Defense::Defense(GameField *gameField, ifstream *inputStream): GameObject(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor Defense"<<endl;
    code = DEFENSE_CODE;
    allegroColor=al_map_rgb(0,153,0);
    image = al_load_bitmap("bitmaps/defense.png");

    lastAttackTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
}

Defense::~Defense()
{
//    cout<<"destruktor Defense"<<endl;
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
    opponent->willMove = false;
}

void Defense::collisionWithObstacle(Obstacle *obstacle)
{

}

void Defense::collisionWithDefense(Defense *defense)
{

}

void Defense::doAction(Play *play)
{
    std::chrono::milliseconds eventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - lastAttackTime.count() >= ATTACK_INTERVAL)
    {
        play->addObject(new Bullet(gameField,gridYPos,gridXPos));
        lastAttackTime = eventTime;
    }
}

void Defense::collisionWithBullet(Bullet *bullet) {

}













