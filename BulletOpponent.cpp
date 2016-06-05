#include "BulletOpponent.h"
#include "Opponent.h"
#include "Obstacle.h"
#include "Defense.h"

BulletOpponent::BulletOpponent(GameField *gameField, int x, int y) : Bullet(gameField,x,y,true)
{
    code = BULLET_OPPONENT_CODE;
    image = al_load_bitmap("bitmaps/bullet_opponent.png");
    imageHalfHP = al_load_bitmap("bitmaps/bullet_opponent.png");
}

void BulletOpponent::collisionWithOpponent(Opponent *opponent)
{

}

BulletOpponent::~BulletOpponent()
{
//    cout<<"destruktor BulletOpponent"<<endl;
}

void BulletOpponent::move() {
    x-=5;
}

void BulletOpponent::collisionWithObstacle(Obstacle *obstacle)
{
    attackObject(obstacle);
}

void BulletOpponent::collisionWithDefense(Defense *defense)
{
    attackObject(defense);
}

void BulletOpponent::attackObject(GameObject *gameObject)
{
    if(!alreadyPunched) //bullet uderza tylko raz i znika
    {
        gameObject->hp-=1;
        hp--;
        alreadyPunched = true;
    }
}
