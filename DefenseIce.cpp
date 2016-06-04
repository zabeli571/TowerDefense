#include "DefenseIce.h"
#include "Play.h"
#include "Bullet.h"
#include "BulletIce.h"

DefenseIce::DefenseIce(GameField *gameField): Defense(gameField)
{
    cout<<"\tkonstruktor DefenseIce"<<endl;
    code = DEFENSE_ICE_CODE;
    image = al_load_bitmap("bitmaps/defense_ice.png");
    imageHalfHP = al_load_bitmap("bitmaps/defense_ice_halfHP.png");
}

DefenseIce::DefenseIce(GameField *gameField, ifstream *inputStream): Defense(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor Defense"<<endl;
    code = DEFENSE_ICE_CODE;
    image = al_load_bitmap("bitmaps/defense_ice.png");
    imageHalfHP = al_load_bitmap("bitmaps/defense_ice_halfHP.png");
}

void DefenseIce::displayOnConsole()
{
    cout<<"DefenseIce, dziedziczy po"<<endl;
    Defense::displayOnConsole();
}

void DefenseIce::doAction(Play *play) //play zawiera wskaznik do wektora z gameobjectsami, do ktorego dodamy pociski
{
    std::chrono::milliseconds eventTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - lastAttackTime.count() >= ATTACK_INTERVAL) //nie czesciej niz co 3s
    {
        play->addObject(new BulletIce(gameField,gridYPos,gridXPos)); //tworze pociski
        lastAttackTime = eventTime;
    }
}

DefenseIce::~DefenseIce()
{
//    cout<<"destruktor DefenseIce"<<endl;
}