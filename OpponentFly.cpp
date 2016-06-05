#include "OpponentFly.h"
#include "Opponent.h"

OpponentFly::OpponentFly(GameField *gameField): Opponent(gameField)
{
    cout<<"\tkonstruktor OpponentFly"<<endl;
    code = OPPONENT_FLY_CODE;
    image = al_load_bitmap("bitmaps/opponent_fly.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_fly_halfHP.png");
}

OpponentFly::OpponentFly(GameField *gameField, int row, int column): Opponent(gameField,row,column)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor OpponentFly"<<endl;
code = OPPONENT_FLY_CODE;
image = al_load_bitmap("bitmaps/opponent_fly.png");
imageHalfHP = al_load_bitmap("bitmaps/opponent_fly_halfHP.png");
}

OpponentFly::OpponentFly(GameField *gameField, ifstream *inputStream): Opponent(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor OpponentFly"<<endl;
    code = OPPONENT_FLY_CODE;
    image = al_load_bitmap("bitmaps/opponent_fly.png");
    imageHalfHP = al_load_bitmap("bitmaps/opponent_fly_halfHP.png");
}

OpponentFly::~OpponentFly()
{
//    cout<<"destruktor OpponentFly"<<endl;
}

void OpponentFly::displayOnConsole()
{
    cout<<"OpponentFly dziedziczy po"<<endl;
    Opponent::displayOnConsole();
}

void OpponentFly::move() {
    std::chrono::milliseconds eventTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
    if(eventTime.count() - freezeTimeStamp > 3000)
    {
        x-=2;
    }
}

