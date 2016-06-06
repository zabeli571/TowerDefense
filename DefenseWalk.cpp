#include "DefenseWalk.h"
#include "Play.h"
#include "Opponent.h"


DefenseWalk::DefenseWalk(GameField *gameField): Defense(gameField)
{
    cout<<"\tkonstruktor DefenseIce"<<endl;
    code = DEFENSE_WALK_CODE;
    image = al_load_bitmap("bitmaps/defense_walk.png");
    imageHalfHP = al_load_bitmap("bitmaps/defense_walk_halfHP.png");
    hp = 10000;
    initialHP=hp;
}

DefenseWalk::DefenseWalk(GameField *gameField, ifstream *inputStream): Defense(gameField,inputStream)//przy losowaniu korzystam z drugiego konstruktora gameobjectu
{
//    cout<<"\tkonstruktor Defense"<<endl;
    code = DEFENSE_WALK_CODE;
    image = al_load_bitmap("bitmaps/defense_walk.png");
    imageHalfHP = al_load_bitmap("bitmaps/defense_walk_halfHP.png");
    hp = 10000;
    initialHP=hp;
}

DefenseWalk::DefenseWalk(GameField *gameField, ifstream *inputStream, bool exact) : Defense(gameField,inputStream,exact)
{
    code = DEFENSE_WALK_CODE;
    image = al_load_bitmap("bitmaps/defense_walk.png");
    imageHalfHP = al_load_bitmap("bitmaps/defense_walk_halfHP.png");
}

void DefenseWalk::displayOnConsole()
{
    cout<<"DefenseWalk, dziedziczy po"<<endl;
    Defense::displayOnConsole();
}

void DefenseWalk::collisionWithOpponent(Opponent *opponent)
{
    opponent->hp -= 1000;
}

void DefenseWalk::move()
{
    x+=10;
}

void DefenseWalk::doAction(Play *play) //play zawiera wskaznik do wektora z gameobjectsami, do ktorego dodamy pociski
{

}

DefenseWalk::~DefenseWalk()
{
//    cout<<"destruktor DefenseWalk"<<endl;
}