#ifndef TOWERDEFENSE_BULLETICE_H
#define TOWERDEFENSE_BULLETICE_H

#include <iostream>
#include <allegro5/allegro.h>
#include "MainObject.h"
#include "GameObject.h"
#include "Bullet.h"

class BulletIce : public Bullet
{
protected:
    static const int BULLET_ICE_CODE = 2001;
    void collisionWithOpponent(Opponent *opponent);
public:
    BulletIce(GameField *gameField, int row, int column);
    ~BulletIce();
};


#endif //TOWERDEFENSE_BULLETICE_H
