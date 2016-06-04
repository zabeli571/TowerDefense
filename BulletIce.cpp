#include "BulletIce.h"
#include "Bullet.h"
#include "Opponent.h"

BulletIce::BulletIce(GameField *gameField, int row, int column) : Bullet(gameField,row,column)
{
    code = BULLET_ICE_CODE;
    image = al_load_bitmap("bitmaps/bullet_ice.png");
    imageHalfHP = al_load_bitmap("bitmaps/bullet_ice.png");
}

void BulletIce::collisionWithOpponent(Opponent *opponent)
{
    if(!alreadyPunched) //bullet uderza tylko raz i znika
    {
        opponent->hp-=1;
        opponent->freeze();
        hp--;
        alreadyPunched = true;
    }
}

BulletIce::~BulletIce()
{
//    cout<<"destruktor BulletIce"<<endl;
}
