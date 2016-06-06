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
    initialHP = hp;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/opponent.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_halfHP.png");
    toNextAttackTime = ATTACK_INTERVAL;
}

Opponent::Opponent(GameField *gameField, int row, int column): GameObject(gameField,row,column)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
    cout<<"\tkonstruktor Opponent"<<endl;
    code = OPPONENT_CODE;
    hp=10;
    initialHP = hp;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/opponent.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_halfHP.png");
    lastAttackTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    toNextAttackTime = ATTACK_INTERVAL;
}

Opponent::Opponent(GameField *gameField, ifstream *inputStream): GameObject(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor Opponent"<<endl;
    code = OPPONENT_CODE;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/opponent.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_halfHP.png");
    lastAttackTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    toNextAttackTime = ATTACK_INTERVAL;
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
        std::chrono::milliseconds eventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
        if(eventTime.count() - freezeTimeStamp > toDefrostTime)
        {
            x--;
        }
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
    if(eventTime.count() - lastAttackTime.count() >= toNextAttackTime) //wykorzystuje roznice czasu tak jak w play::run
    {
        obstacle->hp--; //przeciwnik zabiera hp przeszkody
        lastAttackTime = eventTime;
        toNextAttackTime = ATTACK_INTERVAL;
    }
}

void Opponent::collisionWithOpponent(Opponent *opponent)
{
    //brak interakcji
}

void Opponent::collisionWithDefense(Defense *defense)
{
    std::chrono::milliseconds eventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - lastAttackTime.count() >= toNextAttackTime)
    {
        defense->hp--; //przeciwnik zabiera hp obrony
        lastAttackTime = eventTime;
        toNextAttackTime = ATTACK_INTERVAL;
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

void Opponent::freeze()
{
    toDefrostTime = FREEZE_INTERVAL;
    freezeTimeStamp = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Opponent::managePauseStart(chrono::milliseconds pauseStartTime)
{
    toDefrostTime -= pauseStartTime.count() - freezeTimeStamp;
    toNextAttackTime -= pauseStartTime.count() - lastAttackTime.count();
}

void Opponent::managePauseEnd(chrono::milliseconds pauseEndTime)
{
    lastAttackTime = pauseEndTime;
    freezeTimeStamp = pauseEndTime.count();
}


