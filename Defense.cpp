#include "Defense.h"
#include "Opponent.h"
#include "Play.h"
#include "Bullet.h"
using namespace std;


Defense::Defense(GameField *gameField): GameObject(gameField)
{
    cout<<"\tkonstruktor Defense"<<endl;
    hp = 10;
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

void Defense::displayOnConsole()
{
    cout<<"Defense, dziedziczy po"<<endl;
    GameObject::displayOnConsole();
}

void Defense::saveToStream(ofstream *outputStream)
{
    GameObject::saveToStream(outputStream);
}

void Defense::move()
{
    willMove = true;
}

void Defense::collisionWith(GameObject *anotherObject) //do funkcji przekazany jest obiekt j
{
    anotherObject->collisionWithDefense(this); //poznamy typ j, wszystkie funkcje collision sa virtual, przekazuje siebie
}

void Defense::collisionWithOpponent(Opponent *opponent)
{
    opponent->willMove = false; //nie ruszy sie do momentu zniszczenia obrony
}

void Defense::collisionWithObstacle(Obstacle *obstacle)
{
    //brak interakcji
}

void Defense::collisionWithDefense(Defense *defense)
{
    //brak interakcji
}

void Defense::doAction(Play *play) //play zawiera wskaznik do wektora z gameobjectsami, do ktorego dodamy pociski
{
    std::chrono::milliseconds eventTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - lastAttackTime.count() >= ATTACK_INTERVAL) //nie czesciej niz co 3s
    {
        play->addObject(new Bullet(gameField,gridYPos,gridXPos)); //tworze pociski
        lastAttackTime = eventTime;
    }
}

void Defense::collisionWithBullet(Bullet *bullet)
{
    //brak interakcji
}