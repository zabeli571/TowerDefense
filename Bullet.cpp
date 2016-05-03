#include "Bullet.h"
#include "Opponent.h"
#include "Play.h"


Bullet::Bullet(GameField *gameField, int row, int column) : GameObject(gameField,row,column)
{
//    cout<<"\tkonstruktor Bullet"<<endl;
    code = BULLET_CODE;
    hp=1;
    allegroColor=al_map_rgb(204,0,0);
    image = al_load_bitmap("bitmaps/bullet.png");
    alreadyPunched = false;
}

Bullet::~Bullet() {
//    cout<<"destruktor Bullet"<<endl;
}

void Bullet::collisionWith(GameObject *anotherObject) {
    anotherObject->collisionWithBullet(this);
}

void Bullet::collisionWithObstacle(Obstacle *obstacle) {
}

void Bullet::collisionWithOpponent(Opponent *opponent) {
    if(!alreadyPunched)
    {
        opponent->hp-=2;
        hp--;
        alreadyPunched = true;
    }
}

void Bullet::collisionWithDefense(Defense *defense) {
}

void Bullet::doAction(Play *play) {
}

void Bullet::collisionWithBullet(Bullet *bullet) {
}

void Bullet::move() {
    x+=5;
}