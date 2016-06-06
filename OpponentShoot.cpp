#include "OpponentShoot.h"
#include "Opponent.h"
#include "BulletOpponent.h"
#include "Play.h"

OpponentShoot::OpponentShoot(GameField *gameField): Opponent(gameField)
{
    cout<<"\tkonstruktor OpponentShoot"<<endl;
    code = OPPONENT_SHOOT_CODE;
    image = al_load_bitmap("bitmaps/opponent_shoot.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_shoot_halfHP.png");
}

OpponentShoot::OpponentShoot(GameField *gameField, int row, int column): Opponent(gameField,row,column)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor OpponentShoot"<<endl;
    code = OPPONENT_SHOOT_CODE;
    image = al_load_bitmap("bitmaps/opponent_shoot.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_shoot_halfHP.png");
    lastShootTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    toNextShootTime = SHOOT_INTERVAL;
}

OpponentShoot::OpponentShoot(GameField *gameField, ifstream *inputStream): Opponent(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor OpponentShoot"<<endl;
    code = OPPONENT_SHOOT_CODE;
    image = al_load_bitmap("bitmaps/opponent_shoot.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_shoot_halfHP.png");
    lastShootTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    toNextShootTime = SHOOT_INTERVAL;
}

OpponentShoot::~OpponentShoot()
{
//    cout<<"destruktor OpponentFly"<<endl;
}

void OpponentShoot::displayOnConsole()
{
    cout<<"OpponentShoot dziedziczy po"<<endl;
    Opponent::displayOnConsole();
}

void OpponentShoot::doAction(Play *play) //play zawiera wskaznik do wektora z gameobjectsami, do ktorego dodamy pociski
{
    std::chrono::milliseconds eventTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - lastShootTime.count() >= toNextShootTime) //nie czesciej niz co 3s
    {
        play->addObject(new BulletOpponent(gameField,x,y)); //tworze pociski
        lastShootTime = eventTime;
        toNextShootTime = SHOOT_INTERVAL;
    }
}

void OpponentShoot::managePauseStart(chrono::milliseconds pauseStartTime) {
    Opponent::managePauseStart(pauseStartTime);
    toNextShootTime -= pauseStartTime.count() - lastShootTime.count();
}

void OpponentShoot::managePauseEnd(chrono::milliseconds pauseEndTime) {
    Opponent::managePauseEnd(pauseEndTime);
    lastShootTime = pauseEndTime;
}



